##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Common AI
##

"""@package docstring
Documentation for the Common AI.

Common algorithm. Looks for food and picks it up when it have a low ammount of food and then collect stones
needed to incantate.

Uses BackpackModule for materials tracking and uses autoGatherModule to collect materials easier.

example:

    handler = ConnectionHandler(team, port, host)
    handler.client.connect()
    handler.start_session()

    ai = CommonAI(handler)
    ai.run()
"""

import random

from src.constants.resources import (
    INCANTATION_PREREQUISITES,
    INCANTATION_PLAYERS_NEEDED,
)
from src.command import take, set_down, broadcast
from src.constants.constants import COMMAND_FACTORY, MOVE
from src.algorithms.modules.backpack_module import BackpackModule
from src.connection_handler import ConnectionHandler
import src.algorithms.modules.auto_gather_module as ag


def fuse_dicts(d1: dict, d2: dict) -> dict:
    result = d1.copy()
    for key, value in d2.items():
        result[key] = result.get(key, 0) + value
    return result


def sub_dict(d1, d2):
    result = {}
    for k in d1.keys() | d2.keys():
        diff = d1.get(k, 0) - d2.get(k, 0)
        if diff > 0:
            result[k] = diff
    return result


class CommonAI:
    def __init__(self, handler: ConnectionHandler) -> None:
        """! Initialisation of the Common AI

        @param handler: ConnectionHandler instance
        @return An instance of CommonAI
        """
        self._handler = handler
        self._backpack = BackpackModule(handler)
        self._turn = 0
        self._level = 0
        self._followed_id = 0
        self._id = random.randint(0, 9999999999)

    def run(self) -> None:
        """! Runs the common loop until the player dies

        Stops when the backpack registers zero food remaining

        @return None
        """
        while True:
            self._tick()

    def _tick(self) -> None:
        needed = sub_dict(
            INCANTATION_PREREQUISITES[self._level + 1], self._backpack.inventory
        )
        print(needed)
        if self._backpack.inventory["food"] < 20:
            print("FIND FOOD")
            self._seek_objects({"food": 20})
            return
        elif not bool(needed) and self._backpack.inventory["food"] >= 40:
            self._incantate()
            return
        elif self._backpack.inventory["food"] >= 60 and len(self._handler.events) != 0:
            self._follow_call()
            return
        print("FIND MATS")
        self._seek_objects(fuse_dicts({"food": 20}, needed))
        self._handler.events.clear()

    def _seek_objects(self, objects: dict) -> None:
        obs = self._exec_func("Look")
        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(obs=obs, aimed_materials=objects, max_time=300)
        for action in plan:
            self._exec_func(action)
        self._step_ahead()

    def _incantate(self):
        objects = INCANTATION_PREREQUISITES[self._level + 1]
        for o in objects:
            for _ in range(INCANTATION_PREREQUISITES[self._level + 1][o]):
                self._exec_func(f"Set {o}")
        while self._backpack.inventory["food"] > 10:
            vision = self._exec_func("Look")
            print("NB: ", vision[0].count("player"))
            print(vision)
            print("EXPECTED: ", INCANTATION_PLAYERS_NEEDED[self._level])
            print("LEVEL: ", self._level)
            if vision[0].count("player") >= INCANTATION_PLAYERS_NEEDED[self._level]:
                result = self._exec_func("Incantation")
                if result:
                    print("aaaaa aaaaa")
                    self._level += 1
                break
            self._exec_func(f"Broadcast Incantation;{self._level + 1};{self._id}")

        self._handler.events.clear()

    def _follow_call(self):
        print("FOLLOWING")
        found = False
        self._handler.entrypoint()
        self._handler.events.clear()
        for i in range(2):
            self._exec_func("Look")
        self._handler.entrypoint()
        calls = [
            i
            for i in self._handler.events
            if str(i.argument) == f"Incantation;{self._level + 1};{self._followed_id}"
        ]
        if not calls:
            while self._handler.events:
                event = self._handler.consume_event()
                if str(event.argument).startswith(f"Incantation;{self._level + 1}"):
                    self._followed_id = str(event.argument).strip(";")[2]
                    if self._followed_id == self._id:
                        self._followed_id = 0
                        continue
                    found = True
                    for i in MOVE[event.direction]:
                        self._exec_func(i)
                    break
            if not found:
                return
        self._handler.events.clear()
        self._handler.entrypoint()
        for i in range(2):
            self._exec_func("Look")
        self._handler.entrypoint()
        calls = [
            i
            for i in self._handler.events
            if str(i.argument) == f"Incantation;{self._level + 1};{self._followed_id}"
        ]
        while calls:
            if not calls:
                return
            for i in calls:
                for j in MOVE[i.direction]:
                    self._exec_func(j)
            self._handler.events.clear()
            self._handler.entrypoint()
            for i in range(2):
                self._exec_func("Look")
            self._handler.entrypoint()
            calls = [
                i
                for i in self._handler.events
                if str(i.argument)
                == f"Incantation;{self._level + 1};{self._followed_id}"
            ]

    def _step_ahead(self):
        self._exec_func("Forward")
        if self._turn > 0 and self._turn % random.randint(3, 10) == 0:
            self._exec_func(random.choice(["Right", "Left"]))
        self._turn += 1

    def _exec_func(self, command: str):
        self._backpack.tick(command)
        if command.startswith("Take"):
            result = take(self._handler, command.split(" ")[1])
            if result:
                self._backpack.add_to_inventory([command.split(" ")[1]])
            return result
        elif command.startswith("Set"):
            result = set_down(self._handler, command.split(" ")[1])
            if result:
                self._backpack.del_from_inventory([command.split(" ")[1]])
            return result
        elif command.startswith("Broadcast"):
            return broadcast(self._handler, command.split(" ")[1])
        else:
            return COMMAND_FACTORY[command](self._handler)
