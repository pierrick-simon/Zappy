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

from src.constants.constants import COMMAND_FACTORY
from src.algorithms.modules.backpack_module import BackpackModule
from src.connection_handler import ConnectionHandler


class CommonAI:
    def __init__(self, handler: ConnectionHandler) -> None:
        """! Initialisation of the Common AI

        @param handler: ConnectionHandler instance
        @return An instance of CommonAI
        """
        self._handler = handler
        self._backpack = BackpackModule(handler)
        self._turn = 0

    def run(self) -> None:
        """! Runs the common loop until the player dies

        Stops when the backpack registers zero food remaining

        @return None
        """
        while True:
            self._tick()


    def _tick(self) -> None:
        COMMAND_FACTORY["Forward"](self._handler)
        self._backpack.tick("Forward")
        pass
