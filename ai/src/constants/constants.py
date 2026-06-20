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

MOVE = {
    0: ["Incantation"],
    1: ["Forward"],
    2: ["Forward", "Right", "Forward"],
    3: ["Left", "Forward"],
    4: ["Left", "Forward", "Left", "Forward"],
    5: ["Left", "Left", "Forward"],
    6: ["Right", "Forward", "Right", "Forward"],
    7: ["Right", "Forward"],
    8: ["Forward", "Right", "Forward"],
}
