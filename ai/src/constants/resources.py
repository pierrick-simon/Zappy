##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## resources
##

RESOURCES = [
    "player",
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
]

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

INCANTATION_PREREQUISITES: dict[int, dict] = {
    0: {"linemate": 1},
    1: {"linemate": 1, "deraumere": 1, "sibur": 1},
    2: {"linemate": 2, "sibur": 1, "phiras": 2},
    3: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
    4: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
    5: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
    6: {
        "linemate": 2,
        "deraumere": 2,
        "sibur": 2,
        "mendiane": 2,
        "phiras": 2,
        "thystame": 1,
    },
}

INCANTATION_PLAYERS_NEEDED = [1, 2, 2, 4, 4, 6, 6]

FOOD_DECAY_TIME_UNITS = 126
TIME_UNIT = 10
