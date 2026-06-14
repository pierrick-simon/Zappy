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
from collections import Counter

from src.constants.resources import INCANTATION_PREREQUISITES
from src.command import take, set_down, broadcast
from src.constants.constants import COMMAND_FACTORY
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

    def run(self) -> None:
        """! Runs the common loop until the player dies

        Stops when the backpack registers zero food remaining

        @return None
        """
        while True:
            self._tick()


    def _tick(self) -> None:
        needed = sub_dict(Counter(INCANTATION_PREREQUISITES[self._level + 1]), Counter(self._backpack.inventory))
        print(needed)
        if self._backpack.inventory["food"] < 20:
            self._seek_objects({"food": 20})
        if not bool(needed):
            self._incantate()
        if self._backpack.inventory["food"] < 60:
            self._seek_objects(Counter({"food": 20}) + Counter(needed))

        COMMAND_FACTORY["Forward"](self._handler)
        self._backpack.tick("Forward")
        pass

    def _seek_objects(self, objects: dict) -> None:
        obs = self._exec_func("Look")
        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(obs=obs, aimed_materials=objects, max_time=300)
        for action in plan:
            self._exec_func(action)

    def _exec_func(self, command: str):
        self._backpack.tick(command)
        if command.startswith("Take"):
            result = take(self._handler, command.split(' ')[1])
            if result:
                self._backpack.add_to_inventory([command.split(' ')[1]])
            return result
        elif command.startswith("Set"):
            result = set_down(self._handler, command.split(' ')[1])
            if result:
                self._backpack.del_from_inventory([command.split(' ')[1]])
            return result
        elif command.startswith("Broadcast"):
            return broadcast(self._handler, command.split(' ')[1])
        else:
            return COMMAND_FACTORY[command](self._handler)

    def _incantate(self):
        pass