##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## command dataclass
##

from dataclasses import dataclass
from collections.abc import Callable


@dataclass
class Command:
    name: str
    callback: Callable[[None], None]
    argument: str = None

    def __str__(self) -> str:
        return self.name + " " + self.argument
