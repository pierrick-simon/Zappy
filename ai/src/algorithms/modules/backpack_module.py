##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## main
##

import random

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

class BackPackModule:
    def __init__(self):
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0,
                          "mendiane": 0, "phiras": 0, "thystame": 0}
        self.food_decay = 0

    def tick(self, action: str):
        self.food_decay += COMMAND_TIME[action]
        self._update()

    def _update(self):
        if self.food_decay >= FOOD_DECAY_TIME_UNITS * TIME_UNIT:
            self.inventory["food"] -= 1
            self.food_decay -= FOOD_DECAY_TIME_UNITS * TIME_UNIT

    def add_to_inventory(self, objects: list):
        for o in objects:
            self.inventory[o] += 1

    def del_from_inventory(self, objects: list):
        for o in objects:
            self.inventory[o] -= 1
