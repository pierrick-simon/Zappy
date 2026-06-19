##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Survivor AI
##

"""@package docstring
Documentation for the Survivor AI.

Minimal survival algorithm. Looks for food and picks it up.

Uses BackpackModule for food tracking

example:

    handler = ConnectionHandler(team, port, host)
    handler.client.connect()
    handler.start_session()

    ai = SurvivalAI(handler)
    ai.run()
"""

import random

from src.algorithms.modules import auto_gather_module as ag
from src.connection_handler import ConnectionHandler
from src.algorithms.modules.backpack_module import BackpackModule
from src.command import take, set_down, broadcast
from src.constants.constants import COMMAND_FACTORY


class SurvivalAI:
    def __init__(self, handler: ConnectionHandler) -> None:
        """! Initialisation of the SurvivalAI

        @param handler: ConnectionHandler instance
        @return An instance of SurvivalAI
        """
        self._handler = handler
        self._backpack = BackpackModule(handler)
        self._turn = 0

    def run(self) -> None:
        """! Runs the survival loop until the player dies

        Stops when the backpack registers zero food remaining

        @return None
        """
        while self._backpack.inventory["food"] > 0:
            self._tick()

    def _tick(self) -> None:
        tiles = self._exec_func("Look")

        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(
            obs=tiles, aimed_materials={"food": 100}, max_time=1000
        )

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
