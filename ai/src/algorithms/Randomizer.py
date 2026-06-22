##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Randomizer AI
##

"""@package docstring
Documentation for the Randomizer AI.

This algorithm is fully random

example:

    handler = ConnectionHandler(team, port, host)
    handler.client.connect()
    handler.start_session()

    ai = Randomizer(handler)
    ai.run()
"""

import random
import string

from src.constants.resources import RESOURCES
from src.command import take, set_down, broadcast
from src.constants.constants import COMMAND_FACTORY


class RandomizerAi:
    def __init__(self, handler):
        """! Initialisation of the RandomizerAi

        @param handler: ConnectionHandler instance
        @return An instance of RandomizerAi
        """
        self._handler = handler
        self._turn = 0

    def run(self):
        """! Runs the common loop until the player dies

        @return None
        """

        while True:
            self._tick()

    def _tick(self):
        """! Runs a tick/decision of the ai

        choose random event

        @return None
        """
        self._exec_func(random.choice(list(COMMAND_FACTORY.keys())))


    def _exec_func(self, command: str):
        """! Calls a command function and ticks the backpack

        @param command: Full command as str

        @return the returns of the command function
        """
        print(command)
        if command.startswith("Take"):
            resource = random.choice([r for r in RESOURCES if r != "player"])
            return take(self._handler, resource)
        elif command.startswith("Set"):
            resource = random.choice([r for r in RESOURCES if r != "player"])
            return set_down(self._handler, resource)
        elif command.startswith("Broadcast"):
            message = ""
            for i in range(random.randint(1, 500)):
                message += random.choice(string.ascii_letters + string.digits + string.punctuation)
            return broadcast(self._handler, message)
        else:
            return COMMAND_FACTORY[command](self._handler)
