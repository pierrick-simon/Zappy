##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Villager AI
##

import json
from random import randint
from uuid import UUID, uuid4
from enum import Enum
from collections import deque
from typing import Callable, Optional, Any

from src.connection_handler import ConnectionHandler
from src.dataclasses_models import Command, Event
from src.algorithms.modules.backpack_module import BackpackModule
from src.algorithms.modules.auto_gather_module import AutoGatherModule
from src.command import send_and_recv, broadcast, look, connect_nbr, fork, take
from src.constants.resources import (
    INCANTATION_PREREQUISITES,
    INCANTATION_PLAYERS_NEEDED,
)
from src.constants.constants import COMMAND_FACTORY, MOVE


class MODE(Enum):
    SURVIVE: int = 1
    RESEARCH: int = 2
    MASTER: int = 3
    FOLLOWER: int = 4


def get_missing_resources(inventory: dict[str, int], level: int) -> dict[str, int]:
    return {
        ressource: quantity - inventory.get(ressource, 0)
        for ressource, quantity in INCANTATION_PREREQUISITES[level].items()
        if inventory.get(ressource, 0) < quantity
    }


def get_common_key(dict_one: dict, dict_two: dict) -> Optional[Any]:
    common: set = dict_one.keys() & dict_two.keys()

    if common:
        return common.pop()
    else:
        return None


def format_receivers(receivers: list[str]) -> str:
    return json.dumps(receivers if receivers else ["*"]).replace('"', "'")


def parse_receivers(receiver: str) -> list[str]:
    return receiver.strip('"')


class Villager:
    backpack: BackpackModule
    orientation: int
    id: UUID
    status: bool = True
    level: int = 1
    master: str = str()
    followers: set[str] = set()
    mode: MODE = MODE.SURVIVE
    stones_deposited: bool = False
    plan: deque[tuple[MODE, Command]]

    def __init__(self, handler: ConnectionHandler) -> None:
        self.handler = handler
        self.id = uuid4()
        self.backpack = BackpackModule(self.handler)
        self.plan = deque()
        self.EVENTS: dict[str, Callable[["Villager", Event], None]] = {
            "dead": self.handle_dead,
            "message": self.handle_message,
            "eject": self.handle_eject,
            "Current level": self.handle_level,
        }

        self.BROADCAST_COMPORTEMENT: dict[MODE, Callable[["Villager", Event], None]] = {
            MODE.SURVIVE: self.handle_message_as_surviver,
            MODE.RESEARCH: self.handle_message_as_researcher,
            MODE.MASTER: self.handle_message_as_master,
            MODE.FOLLOWER: self.handle_message_as_follower,
        }

    def handle_dead(self, _: Event) -> None:
        print("DEAD")
        self.status = False

    def handle_message_as_surviver(self, event: Event) -> None:
        pass

    def handle_message_as_researcher(self, event: Event) -> None:
        sender, _, level, _ = event.argument

        if int(level) != self.level:
            return
        master_id: str = sender
        self.mode = MODE.FOLLOWER
        self.master = master_id
        self.plan.clear()
        broadcast(self.handler, f"{self.id};yes;{self.level};{format_receivers([master_id])}")
        self.backpack.tick("Broadcast")
        self.append_to_plan(MOVE[event.direction], self.mode)

    def handle_message_as_follower(self, event: Event) -> None:
        sender, _, _, _ = event.argument

        if sender != self.master:
            print(f"{self.master} != {sender=}")
            return
        if event.direction == 0:
            self.deposit_stones()
            return
        if not self.plan:
            self.append_to_plan(MOVE[event.direction], MODE.FOLLOWER)
        print(f"After: {self.plan=}")

    def handle_message_as_master(self, event: Event) -> None:
        sender, type, level, receiver = event.argument
        print(f"{sender}")
        receivers: list[str] = parse_receivers(receiver)

        if int(level) != self.level:
            return
        if type == "incantation":
            if sender < str(self.id):
                self.handler.client.disconnect()
                self.mode = MODE.FOLLOWER
                self.master = sender
                self.followers.clear()
                return
        if not receivers or str(self.id) not in receivers or type != "yes":
            return
        self.followers.add(str(sender))

    def call_followers(self):
        receivers: str = format_receivers(list(self.followers))
        broadcast(self.handler, f"{self.id};incantation;{self.level};{receivers}")
        self.backpack.tick("Broadcast")

    def deposit_stones(self):
        for ressource, quantity in INCANTATION_PREREQUISITES[self.level - 1].items():
            for _ in range(quantity):
                send_and_recv(self.handler, Command("Set", ressource))

    def check_incantations(self, tile: list[str]) -> bool:
        players: int = tile.count("player")

        print(f"Looking for an incantations {tile=}, {players=}")
        if players < INCANTATION_PLAYERS_NEEDED[self.level - 1]:
            return False
        for ressource, quantity in INCANTATION_PREREQUISITES[self.level - 1].items():
            if self.backpack.inventory.get(ressource, 0) < quantity:
                return False
        return True

    def take_food_to_wait(self, tile: list[str]):
        if "food" in tile:
            take(self.handler, "food")
            return

    def manage_incantations(self):
        tile: list[str] = look(self.handler)[0]
        players_present: int = tile.count("players")
        players_needed: int = INCANTATION_PLAYERS_NEEDED[self.level - 1]

        if self.check_incantations(tile) is True:
            self.plan.clear()
            self.deposit_stones()
            print("Incantation")
            send_and_recv(self.handler, Command("Incantation"))
            self.mode = MODE.RESEARCH
        if connect_nbr(self.handler) < players_needed:
            fork(self.handler)
            return
        if players_present < players_needed:
            self.call_followers()
            self.take_food_to_wait(tile)
            return

    def handle_message(self, event: Event) -> None:
        print(f"message={event}")
        self.BROADCAST_COMPORTEMENT[self.mode](event)

    def handle_eject(self, event: Event) -> None:
        pass

    def handle_level(self, event: Event) -> None:
        self.level = int(event.direction)
        self.stones_deposited = False
        self.master = str()
        self.mode = MODE.RESEARCH
        self.plan.clear()
        self.backpack.refresh_inventory()

    def append_to_plan(self, commands: list[str], mode: MODE):
        tokens: list[str] = []

        for cmd in commands:
            tokens = cmd.split(" ")
            if tokens and tokens[0] in COMMAND_FACTORY:
                arg = tokens[1] if len(tokens) > 1 else None
                self.plan.append((mode, Command(tokens[0], arg)))

    def search_ressources(self, ressources: dict[str, int], max_time: int) -> None:
        auto_gather: AutoGatherModule = AutoGatherModule()
        self.append_to_plan(
            auto_gather.auto_gather(
                COMMAND_FACTORY["Look"](self.handler), ressources, max_time
            ),
            self.mode,
        )
        if not self.plan:
            self.append_to_plan(MOVE[randint(1, 8)], self.mode)
        while self.plan:
            self.execute_action()

    def handle_response(self, command: tuple[MODE, Command]):
        send_and_recv(self.handler, command[1])
        print(f"{command=}")
        self.backpack.tick(command[1].command)
        if command[1].command == "Take" and command[1].response == "ok":
            self.backpack.add_to_inventory([command[1].argument])
        if command[1].command == "Set" and command[1].response == "ok":
            self.backpack.del_from_inventory([command[1].argument])

    def handle_events(self):
        while True:
            event = self.handler.consume_event()
            if event is None:
                break
            self.EVENTS[event.name](event)

    def update_mode(self):
        previous_mode = self.mode

        if self.backpack.inventory["food"] < 10:
            self.mode = MODE.SURVIVE
        elif self.mode == MODE.SURVIVE and self.backpack.inventory["food"] >= 25:
            self.mode = MODE.RESEARCH
        if self.mode == MODE.RESEARCH:
            missing = get_missing_resources(self.backpack.inventory, self.level - 1)
            if not missing:
                self.mode = MODE.MASTER
        if previous_mode != self.mode:
            self.plan.clear()

    def execute_mode(self):
        if self.mode == MODE.SURVIVE:
            self.search_ressources({"food": 100}, 176)
        elif self.mode == MODE.RESEARCH:
            missing: dict[str, int] = get_missing_resources(
                self.backpack.inventory, (self.level - 1)
            )
            if missing and not self.plan:
                missing["food"] = 10
                self.search_ressources(missing, 176)
        elif self.mode == MODE.MASTER:
            self.manage_incantations()

    def execute_action(self):
        if self.plan:
            self.handle_response(self.plan.popleft())
        else:
            self.backpack.refresh_inventory()
        self.handle_events()

    def run(self):
        while self.status:
            self.update_mode()
            self.execute_mode()
            self.execute_action()
