##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## BackpackModule
##

"""@package docstring
Documentation for the BackPack module.

The backpack module aims to create a self-hosted inventory in the AI to avoid
calling inventory to the maximum to not waste time.

example:

*Creation of the AI*
backpack = BackPackModule()

while AI.alive:
    action = AI.get_action()
    backpack.tick(action)
"""

from src.connection_handler import ConnectionHandler
from src.constants.resources import COMMAND_TIME, FOOD_DECAY_TIME_UNITS
from src.constants.constants import COMMAND_FACTORY



class BackpackModule:
    def __init__(self, handler: ConnectionHandler) -> None:
        """! Initialisation of the backpack module.

        @return An instance of the backpack module.
        """
        self._handler = handler
        self.inventory = {
            "food": 9,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
        }
        self.food_decay = 0

    def tick(self, action: str) -> None:
        """! Advance the food decay counter by the time cost of action.

        IMPORTANT: this method only tracks TIME (food decay).
        Inventory changes (Take/Set) are handled exclusively by
        add_to_inventory() / del_from_inventory(), called by the AI
        after confirming the server accepted the command.

        @param action: Command string (e.g. "Forward", "Take food")
        @return None
        """
        print(action)

        if action.startswith("Take"):
            self.food_decay += COMMAND_TIME["Take"]
        elif action.startswith("Set"):
            self.food_decay += COMMAND_TIME["Set"]
        elif action.startswith("Broadcast"):
            self.food_decay += COMMAND_TIME["Broadcast"]
        elif action in COMMAND_TIME:
            self.food_decay += COMMAND_TIME[action]

        self._update()

    def _update(self) -> None:
        """! Consume one food unit per FOOD_DECAY_TIME_UNITS elapsed.

        @return None
        """
        while self.food_decay >= FOOD_DECAY_TIME_UNITS:
            if self.inventory["food"] > 0:
                self.inventory["food"] -= 1
            self.food_decay -= FOOD_DECAY_TIME_UNITS

    def add_to_inventory(self, objects: list) -> None:
        """! Add objects to the tracked inventory (call after a successful Take).

        @param objects: List of resource name strings.
        @return None
        """
        for o in objects:
            self.inventory[o] += 1

    def del_from_inventory(self, objects: list) -> None:
        """! Remove objects from the tracked inventory (call after a successful Set).

        @param objects: List of resource name strings.
        @return None
        """
        for o in objects:
            if self.inventory[o] > 0:
                self.inventory[o] -= 1

    def refresh_inventory(self) -> None:
        """! Overwrite the tracked inventory with a real server Inventory response.

        Use this when the tracked state may have drifted (e.g. after an
        incantation strips stones from the tile, or after being ejected).

        @return None
        """
        self.inventory = COMMAND_FACTORY["Inventory"](self._handler)
        self.food_decay += COMMAND_TIME["Inventory"]