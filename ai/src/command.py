##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## command dataclass
##

from dataclasses import dataclass
from typing import Optional, Any
from src.connexion_handler import ConnectionHandler

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



def send_and_recv(handler: ConnectionHandler, cmd: Command) -> str:
    """! Sends a command and blocks until its response is received

    Pushes the command to the handler queue, then entrypoint()

    @param handler: Active ConnectionHandler instance
    @param cmd: Command to send
    @return Raw response string from the server
    """
    handler.push_to_server(cmd)
    while cmd.response is None:
        handler.entrypoint()
    handler.consume_command()
    return cmd.response