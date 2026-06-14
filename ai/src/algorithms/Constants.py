##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Constants
##

from src.command import (forward, right, left, look, take, set_down, inventory, broadcast,
                         fork, eject, incantation, connect_nbr)
from src.algorithms.Survivor import SurvivalAI

RESOURCES = ["food", "linemate", "deraumere", "sibur",
             "mendiane", "phiras", "thystame"]

NB_TILES_OBS = 16

FOOD_DECAY_TIME_UNITS = 126
TIME_UNIT = 10

COMMAND_FACTORY = {
    "Forward": forward,
    "Right": right,
    "Left": left,
    "Look": look,
    "Take": take,
    "Set": set_down,
    "Inventory": inventory,
    "Broadcast": broadcast,
    "Connect_nbr": connect_nbr,
    "Fork": fork,
    "Eject": eject,
    "Incantation": incantation,
}

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

AI_LIST = {
    SurvivalAI
}

