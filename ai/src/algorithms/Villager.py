##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Villager AI
##

import json
from uuid import UUID, uuid4
from enum import Enum
from collections import deque
from typing import Callable, Optional, Any

from src.connection_handler import ConnectionHandler
from src.dataclasses_models import Command, Event
from src.algorithms.modules.backpack_module import BackpackModule
from src.algorithms.modules.auto_gather_module import AutoGatherModule
from src.command import send_and_recv, broadcast, look, incantation
from src.constants.resources import INCANTATION_PREREQUISITES, INCANTATION_PLAYERS_NEEDED
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

def check_incantations(tile: list[str], level: int) -> bool:
    players: int =  tile.count("player")

    if (players < INCANTATION_PLAYERS_NEEDED[level]):
        return False
    for ressource, quantity in INCANTATION_PREREQUISITES[level].items():
        if (tile.count(ressource) < quantity):
            return False
    return True

class Villager:
    backpack: BackpackModule
    orientation: int
    id: UUID
    status: bool = True
    level: int = 1
    master: Optional[UUID] = None
    followers: list[str] = []
    mode: MODE = MODE.SURVIVE
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
        self.status = False

    def handle_message_as_surviver(self, event: Event) -> None:
        pass

    def handle_message_as_researcher(self, event: Event) -> None:
        sender, _, level, receiver = event.argument
        receivers: list[str] = json.loads(receiver)

        if int(level) != self.level:
            return
        if str(self.id) not in receivers and "*" not in receivers:
            return
        self.backpack.tick("Broadcast")
        broadcast(self.handler, f"{str(self.id)};yes;{self.level};{sender}")
        self.mode = MODE.FOLLOWER
        self.master = sender
        self.plan.clear()
        self.append_to_plan(MOVE[event.direction], MODE.FOLLOWER)

    def handle_message_as_master(self, event: Event) -> None:
        sender, type, _, receiver = event.argument
        receivers: list[str] = json.loads(receiver)

        if str(self.id) not in receivers or type != "yes":
            return
        self.followers.append(str(sender))

    def call_followers(self):
        receivers: str = json.dumps(self.followers if self.followers else ["*"])
        broadcast(self.handler, f"{str(self.id)};incantation;{self.level + 1};{receivers}")
        ressource = get_common_key(
            self.backpack.inventory, INCANTATION_PREREQUISITES[self.level + 1]
        )
        if ressource:
            self.append_to_plan([f"Set {ressource}"])
            self.backpack.del_from_inventory([f"Set {ressource}"])

    def manage_incantations(self):
        if check_incantations(look(self.handler)[0], self.level + 1) is True:
            send_and_recv(self.handler, "Incantation")
            self.mode = MODE.RESEARCH
        else:
            self.call_followers()

    def handle_message_as_follower(self, event: Event) -> None:
        _, _, _, receiver = event.argument
        receivers: list[str] = json.loads(receiver)

        if any(mode == self.mode for mode, _ in self.plan):
            return
        if str(self.id) not in receivers:
            return
        self.append_to_plan(MOVE[event.direction], MODE.FOLLOWER)

    def handle_message(self, event: Event) -> None:
        self.BROADCAST_COMPORTEMENT[self.mode](event)

    def handle_eject(self, event: Event) -> None:
        pass

    def handle_level(self, event: Event) -> None:
        self.level = event.argument
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
        if any(mode == self.mode for mode, _ in self.plan):
            return
        auto_gather: AutoGatherModule = AutoGatherModule()
        self.append_to_plan(
            auto_gather.auto_gather(COMMAND_FACTORY["Look"](self.handler), ressources, max_time),
            self.mode,
        )

    def handle_response(self, command: Command):
        send_and_recv(self.handler, command)
        self.backpack.tick(command.command)
        if command.command == "Take" and command.response == "ok":
            self.backpack.add_to_inventory([command.argument])
        if command.command == "Set" and command.response == "ok":
            self.backpack.del_from_inventory([command.argument])
        if command.command == "Inventory":
            self.backpack.refresh_inventory(command.response)

    def handle_events(self):
        event: Event = self.handler.consume_event()
    
        if event is not None:
            self.EVENTS[event.name](event)

    def update_mode(self):
        if self.backpack.inventory["food"] < 10:
            self.mode = MODE.SURVIVE
            return
        if self.mode == MODE.SURVIVE:
            self.mode = MODE.RESEARCH
        if self.mode == MODE.RESEARCH:
            missing: dict[str, int] = get_missing_resources(
                self.backpack.inventory, self.level + 1
            )
            if not missing:
                self.mode = MODE.MASTER

    def execute_mode(self):
        if self.mode == MODE.SURVIVE:
            self.search_ressources({"food": 20}, 300)
        elif self.mode == MODE.RESEARCH:
            missing: dict[str, int] = get_missing_resources(
                self.backpack.inventory, self.level + 1
            )
            if missing:
                self.search_ressources(missing, 300)
        elif self.mode == MODE.MASTER:
            self.manage_incantations()

    def execute_action(self):
        if self.plan:
            self.handle_response(self.plan.popleft()[1])
        self.handle_events()

    def run(self):
        while self.status:
            self.update_mode()
            self.execute_mode()
            self.execute_action()
