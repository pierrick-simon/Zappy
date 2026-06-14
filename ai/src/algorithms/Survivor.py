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
from src.command import forward, right, left, look
from src.constants.constants import COMMAND_FACTORY

class SurvivalAI:
    def __init__(self, handler: ConnectionHandler) -> None:
        """! Initialisation of the SurvivalAI

        @param handler: ConnectionHandler instance
        @return An instance of SurvivalAI
        """
        self._handler = handler
        self._backpack = BackpackModule()
        self._turn = 0

    def run(self) -> None:
        """! Runs the survival loop until the player dies

        Stops when the backpack registers zero food remaining

        @return None
        """
        while self._backpack.inventory["food"] > 0:
            self._tick()

    def _tick(self) -> None:
        tiles = self._exec(look)

        food_count = sum(t.count("food") for t in tiles)

        if food_count == 0:
            self._explore()
            self._turn += 1
            return

        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(
            obs=tiles,
            aimed_materials={"food": food_count},
            max_time=1000
        )

        for action in plan:
            parts = action.split()
            fn = COMMAND_FACTORY[parts[0]]
            result = self._exec(fn, *parts[1:])

            if parts[0] == "Take" and result:
                self._backpack.add_to_inventory([parts[1]])

        if not auto_gather.is_complete():
            self._explore()
            self._turn += 1
        else:
            self._turn = 0

    def _explore(self) -> None:
        """! Moves forward and randomly turns to avoid looping

        @return None
        """
        self._exec(forward)
        if self._turn > 0 and self._turn % random.randint(3, 10) == 0:
            self._exec(random.choice([right, left]))

    def _exec(self, fn, *args):
        """! Calls a command function and ticks the backpack

        @param fn: Command function from commands
        @param args: Arguments given to the function
        @return the returns of the command function
        """
        result = fn(self._handler, *args)
        self._backpack.tick(fn.__name__.capitalize())
        return result
