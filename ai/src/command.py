##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## command dataclass
##

from dataclasses import dataclass
from typing import Optional, Any


@dataclass
class Command:
    command: str
    argument: str = None
    response: Any = None

    def __str__(self) -> str:
        return " ".join(filter(None, [self.command, self.argument]))


@dataclass
class Event:
    name: str
    direction: Optional[int] = None
    argument: Optional[Any] = None

    def __str__(self):
        return " ".join(filter(None, [self.name, self.argument, self.direction]))
