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

from src.connection_handler import ConnectionHandler
from src.algorithms.modules.backpack_module import BackpackModule
from src.command import forward, right, left, look, take

FOOD_LOW = 20


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
        """! Executes one tick

        @return None
        """
        tiles = self._exec(look)
        food_tile = next((i for i, t in enumerate(tiles) if "food" in t), None)

        if food_tile is not None:
            self._go_and_take(food_tile)
            self._turn = 0
        else:
            self._explore()
            self._turn += 1

    def _go_and_take(self, tile_idx: int) -> None:
        """! Navigates to a tile and picks up food

        @param tile_idx: Tile with the food
        @return None
        """
        row = 0
        while (row + 1) ** 2 <= tile_idx:
            row += 1

        offset = (tile_idx - row * row) - row

        for _ in range(row):
            self._exec(forward)

        for _ in range(abs(offset)):
            self._exec(right if offset > 0 else left)
            self._exec(forward)

        if self._exec(take, "food"):
            self._backpack.add_to_inventory(["food"])

    def _explore(self) -> None:
        """! Moves forward and randomly turns to avoid looping

        @return None
        """
        self._exec(forward)
        if self._turn > 0 and self._turn % random.randint(3, 10) == 0:
            self._exec(right)

    def _exec(self, fn, *args):
        """! Calls a command function and ticks the backpack

        @param fn: Command function from commands
        @param args: Arguments given to the function
        @return the returns of the command function
        """
        result = fn(self._handler, *args)
        self._backpack.tick(fn.__name__.capitalize())
        return result
