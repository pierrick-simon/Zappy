##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## command dataclass
##

from dataclasses import dataclass
from typing import Optional, Any
from src.connexion_handler import ConnectionHandler
from ai.src.algorithms import Constants as constants

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


def forward(handler: ConnectionHandler) -> bool:
    """! Moves the player one tile forward

    @param handler: ConnectionHandler instance
    @return True on success, False on 'ko'
    """
    return send_and_recv(handler, Command("Forward")) == "ok"


def right(handler: ConnectionHandler) -> bool:
    """! Turns the player 90° right

    @param handler: ConnectionHandler instance
    @return True on success
    """
    return send_and_recv(handler, Command("Right")) == "ok"


def left(handler: ConnectionHandler) -> bool:
    """! Turns the player 90° left

    @param handler: ConnectionHandler instance
    @return True on success
    """
    return send_and_recv(handler, Command("Left")) == "ok"


def look(handler: ConnectionHandler) -> list[list[str]]:
    """! Looks forward the AI and returns visible tile contents

    [player food, , linemate] -> [["player", "food"], [], ["linemate"]]

    @param handler: ConnectionHandler instance
    @return List of tiles, each tile is a list of string
    """
    response = send_and_recv(handler, Command("Look"))
    return [
        [token for token in tile.strip().split() if token]
        for tile in response.strip().strip("[]").split(",")
    ]


def inventory(handler: ConnectionHandler) -> dict[str, int]:
    """! Returns the player's current inventory.

    [food 10, linemate 2, ...] -> {"food": 10, "linemate": 2, ...}

    @param handler: ConnectionHandler instance
    @return Dict mapping each resource name and its quantity
    """
    response = send_and_recv(handler, Command("Inventory"))
    result = {r: 0 for r in constants.RESOURCES}
    for item in response.strip().strip("[]").split(","):
        parts = item.strip().split()
        if len(parts) == 2 and parts[0] in result:
            try:
                result[parts[0]] = int(parts[1])
            except ValueError:
                pass
    return result


def take(handler: ConnectionHandler, resource: str) -> bool:
    """! Picks up a resource from the current tile

    @param handler: ConnectionHandler instance
    @param resource: Resource name
    @return True if picked up, False if 'ko'
    """
    return send_and_recv(handler, Command("Take", resource)) == "ok"


def set_down(handler: ConnectionHandler, resource: str) -> bool:
    """! Drops a resource in the current tile

    @param handler: ConnectionHandler instance
    @param resource: Resource name
    @return True if dropped, False if 'ko'
    """
    return send_and_recv(handler, Command("Set", resource)) == "ok"


def broadcast(handler: ConnectionHandler, text: str) -> bool:
    """! Broadcasts a message to all players on the map

    @param handler: ConnectionHandler instance
    @param text: Message string to broadcast
    @return True on success
    """
    return send_and_recv(handler, Command("Broadcast", text)) == "ok"


def connect_nbr(handler: ConnectionHandler) -> int:
    """! Returns the number of unused slots available for the team

    @param handler: ConnectionHandler instance
    @return Number of free slots
    """
    try:
        return int(send_and_recv(handler, Command("Connect_nbr")))
    except ValueError:
        return 0


def fork(handler: ConnectionHandler) -> bool:
    """! Lays an egg, adding one slot to the team

    @param handler: ConnectionHandler instance
    @return True on success
    """
    return send_and_recv(handler, Command("Fork")) == "ok"


def eject(handler: ConnectionHandler) -> bool:
    """! Pushes all players off the current tile

    @param handler: ConnectionHandler instance
    @return True if at least one entity was ejected, False on 'ko'
    """
    return send_and_recv(handler, Command("Eject")) == "ok"


def incantation(handler: ConnectionHandler) -> Optional[int]:
    """! Starts an elevation ritual and waits for its end

    @param handler: ConnectionHandler instance
    @return New level as int on success, None on 'ko'
    """
    cmd = Command("Incantation")
    handler.push_to_server(cmd)

    while cmd.response is None:
        handler.entrypoint()
    handler.consume_command()

    if "Elevation underway" not in (cmd.response or ""):
        return None

    response = handler.client.recv()
    try:
        return int(response.split(":")[1])
    except (ValueError, IndexError):
        return None
