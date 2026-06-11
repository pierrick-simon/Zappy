from dataclasses import dataclass
from collections.abc import Callable


@dataclass
class Command:
    name: str
    callback: Callable[[None], None]
    argument: str = None

    def __str__(self):
        return self.name + " " + self.argument
