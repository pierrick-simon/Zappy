##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Ejector AI
##

"""@package docstring
Documentation for the Ejector AI.

This algorithm focus and surviving and laying eggs around the map.

Uses BackpackModule for food tracking

example:

    handler = ConnectionHandler(team, port, host)
    handler.client.connect()
    handler.start_session()

    ai = Ejector(handler)
    ai.run()
"""

import random

from src.algorithms.modules import backpack_module
from src.command import take, set_down, broadcast
from src.algorithms.modules import auto_gather_module as ag
from src.constants.constants import COMMAND_FACTORY


class EjectorAi:
    def __init__(self, handler):
        """! Initialisation of the LayerAi

        @param handler: ConnectionHandler instance
        @return An instance of LayerAi
        """
        self._handler = handler
        self._turn = 0
        self._backpack = backpack_module.BackpackModule(handler)

    def run(self):
        """! Runs the common loop until the player dies

        @return None
        """

        while True:
            self._tick()

    def _tick(self):
        """! Runs a tick/decision of the ai

        Under 20 food, the AI will seek and take food while the its food is under 35.
        Then it will step_ahead and randomly lay an egg.

        @return None
        """
        if self._backpack.inventory["food"] < 20:
            while self._backpack.inventory["food"] < 35:
                self._seek_food()
            return
        self._push_players()

    def _seek_food(self) -> None:
        """! Look and take all the food it sees

        @return None
        """
        obs = self._exec_func("Look")
        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(obs=obs, aimed_materials={"food": 30}, max_time=300)
        for action in plan:
            self._exec_func(action)
        self._step_ahead()

    def _push_players(self):
        """! Look for players and go to their tile and push them if they
             are still here

        @return None
        """
        obs = list(self._exec_func("Look"))
        obs[0].remove("player")
        auto_gather = ag.AutoGatherModule()
        plan = auto_gather.auto_gather(obs=obs, aimed_materials={"player": 30}, max_time=300)
        for action in plan:
            if str(action).startswith("Take"):
                self._exec_func("Eject")
                continue
            self._exec_func(action)
        self._step_ahead()

    def _step_ahead(self):
        """! Go Forward and randomly turn in a random direction

        @return None
        """
        self._exec_func("Forward")
        if self._turn > 0 and self._turn % random.randint(4, 10) == 0:
            self._exec_func(random.choice(["Right", "Left"]))
        self._turn += 1

    def _exec_func(self, command: str):
        """! Calls a command function and ticks the backpack

        @param command: Full command as str

        @return the returns of the command function
        """
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
