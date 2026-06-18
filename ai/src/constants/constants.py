##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Constants
##

from src.command import (
    forward,
    right,
    left,
    look,
    take,
    set_down,
    inventory,
    broadcast,
    fork,
    eject,
    incantation,
    connect_nbr,
)

NB_TILES_OBS = 16


COMMAND_FACTORY: dict = {
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
