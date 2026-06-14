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

from src.command import take, set_down, broadcast
from src.constants.constants import COMMAND_FACTORY
from src.algorithms.modules.backpack_module import BackpackModule
from src.connection_handler import ConnectionHandler
import src.algorithms.modules.auto_gather_module as ag

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
        if self._backpack.inventory["food"] < 20:
            self._seek_food()

        COMMAND_FACTORY["Forward"](self._handler)
        self._backpack.tick("Forward")
        pass

    def _seek_food(self) -> None:
        obs = self._exec_func("Look")
        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(obs=obs, aimed_materials={"food": 20}, max_time=300)
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