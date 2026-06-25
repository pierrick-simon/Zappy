##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Worker AI
##

"""@package docstring
Documentation for the Worker AI.

Ai that focuses on collecting every resources

Uses BackpackModule for food tracking

example:

    handler = ConnectionHandler(team, port, host)
    handler.client.connect()
    handler.start_session()

    ai = WorkerAi(handler)
    ai.run()
"""

import random

from src.algorithms.modules import auto_gather_module as ag
from src.connection_handler import ConnectionHandler
from src.algorithms.modules.backpack_module import BackpackModule
from src.command import take, set_down, broadcast
from src.constants.constants import COMMAND_FACTORY


class WorkerAi:
    def __init__(self, handler: ConnectionHandler) -> None:
        """! Initialisation of the WorkerAi

        @param handler: ConnectionHandler instance
        @return An instance of WorkerAi
        """
        self._handler = handler
        self._backpack = BackpackModule(handler)
        self._turn = 0
        self._alive = True

    def run(self) -> None:
        """! Runs the worker loop until the player dies

        @return None
        """
        while self._alive:
            self._tick()

    def _tick(self) -> None:
        if self._backpack.inventory["food"] < 15:
            self._seek_objects({"food": 100})
        else:
            self._seek_objects({"food": 99, "linemate": 99, "deraumere": 99, "sibur": 99,
                                "mendiane": 99, "phiras": 99, "thystame": 99})

    def _seek_objects(self, objects: dict) -> None:
        obs = self._exec_func("Look")
        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(obs=obs, aimed_materials=objects, max_time=300)
        for action in plan:
            self._exec_func(action)
        self._explore()


    def _explore(self) -> None:
        """! Moves forward and randomly turns to avoid looping

        @return None
        """
        self._exec_func("Forward")
        if self._turn > 0 and self._turn % random.randint(3, 10) == 0:
            self._exec_func(random.choice(["Right", "Left"]))

    def _exec_func(self, command: str):
        """! Calls a command function and ticks the backpack

        @param command: Full command as str

        @return the returns of the command function
        """
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
