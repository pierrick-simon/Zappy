##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## resources
##

RESOURCES = ["player", "food", "linemate", "deraumere", "sibur",
             "mendiane", "phiras", "thystame"]

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
    "Incantation": 300,
}

INCANTATION_PREREQUISITES = {
    1: {"player": 1, "linemate": 1},
    2: {"player": 2, "linemate": 1, "deraumere": 1, "sibur": 1},
    3: {"player": 2, "linemate": 2, "sibur": 1, "phiras": 2},
    4: {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
    5: {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
    6: {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
    7: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
}

FOOD_DECAY_TIME_UNITS = 126
TIME_UNIT = 10
