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

FOOD_DECAY_TIME_UNITS = 126
TIME_UNIT = 10

COMMAND_TIME = {
    "Forward": 7,
    "Right": 7,
    "Left": 7,
    "Look": 7,
    "Inventory": 1,
    "Broadcast": 7,
    "Fork": 42,
    "Eject": 7,
    "Take": 7,
    "Set": 7,
    "Incantation": 300
}

RESOURCES = ["food", "linemate", "deraumere", "sibur",
             "mendiane", "phiras", "thystame"]

class BackpackModule:
    def __init__(self) -> None:
        """! Initialisation of the backpack module.

        @return  An instance of the backpack module.

        """
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0,
                          "mendiane": 0, "phiras": 0, "thystame": 0}
        self.food_decay = 0

    def tick(self, action: str) -> None:
        """! Function to call at each action in the AI when it has the backpack.

        @param action: The action took as string (example: "Forward")
        @return None
        """
        self.food_decay += COMMAND_TIME[action]
        self._update()

    def _update(self) -> None:
        """! Function to update the backpack module.

        @return None
        """
        if self.food_decay >= FOOD_DECAY_TIME_UNITS * TIME_UNIT:
            self.inventory["food"] -= 1
            self.food_decay -= FOOD_DECAY_TIME_UNITS * TIME_UNIT

    def add_to_inventory(self, objects: list) -> None:
        """! Function to add the objects to the inventory.

        @param objects: The list of objects to add to the inventory.
        @return None
        """
        for o in objects:
            self.inventory[o] += 1

    def del_from_inventory(self, objects: list) -> None:
        """! Function to remove the objects to the inventory.

        @param objects: The list of objects to remove from the inventory.
        @return None
        """
        for o in objects:
            self.inventory[o] -= 1
