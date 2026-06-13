import re
import sys
import ast
from src.client import Client
from typing import Optional, Any
from src.command import Command, Event
from collections import deque
from collections.abc import Callable


def get_key_from_dict(dictionary: dict, string: str) -> Optional[str]:
    for key in dictionary.keys():
        if string.startswith(key):
            return key
    return None


class ConnectionHandler:
    client: Client
    commands: deque[Command]
    events: deque[Event]
    slots: int
    max_command: int
    status: bool = True
    dimension: tuple = ()

    def __init__(self, team: str, port: int, host: str, max_command=10):
        self.max_command = max_command
        self.client = Client(team, port, host)
        self.commands = deque(maxlen=max_command)
        self.events = deque()

        self.COMMON_EVENTS: dict[str, Callable[["ConnectionHandler", str], Optional[Event]]] = {
            "dead": self.handle_dead,
            "message": self.handle_message,
            "eject": self.handle_eject,
            "Current level": self.handle_level,
        }

        self.SPECIAL_RESPONSE: dict[str, Callable[["ConnectionHandler", str], Any]] = {
            "Look": self.handle_look_response,
            "Inventory": self.handle_inventory_response,
            "Connect_nbr": lambda self, request : int(request), 
        }

    def handle_dead(self, request: str) -> Optional[Event]:
        self.status = False
        return Event("dead")

    def handle_eject(self, request: str) -> Optional[Event]:
        try:
            return Event("eject", int(request.split(":")[1]))
        except Exception as e:
            print(
                f"Exception: {e}, A direction must be specified in the eject event.",
                file=sys.stderr,
            )
            return None

    def handle_message(self, request: str) -> Optional[Event]:
        try:
            tokens: list[str] = re.split(r"[ ,]+", request)
            _ = tokens.pop(0)
            direction: int = int(tokens.pop(0))
            return Event("message", direction, tokens[0].split(";"))
        except Exception as e:
            print(
                f"Exception: {e}, A direction must be specified in the message event.",
                file=sys.stderr,
            )
            return None

    def handle_level(self, request: str) -> Optional[Event]:
        try:
            return Event("Current level", int(request.split(":")[1]))
        except Exception as e:
            print(
                f"Exception: {e}, A level must be specified in the current level event.",
                file=sys.stderr,
            )
            return None
    
    def handle_look_response(self, request: str) -> list[str]:
            return request.split(",")
    
    def handle_inventory_response(self, request: str) -> dict[str, int]:
        request.replace("[", "{").replace("]", "}").replace(" ", ": ")
        return ast.literal_eval(request)
    
    def handle_response(self, request: str) -> Any:
        if (self.commands[0] in self.SPECIAL_RESPONSE):
            return self.SPECIAL_RESPONSE[self.commands[0]](request)
        else:
            return request

    def start_session(self):
        if self.client.recv() != "WELCOME":
            raise ConnectionError(
                "The server did not initiate the connection with the client using WELCOME."
            )
        self.client.send(self.client.name)
        try:
            raw_slot: str = self.client.recv()
            self.slots = int(raw_slot)
        except ValueError:
            raise ValueError(f"Number of available slot must be a number {raw_slot}.")
        if self.slots < 1:
            raise ConnectionError(
                f"No slot available for the team: {self.client.name}."
            )
        self.dimension = tuple(self.client.recv().split())
        print(f"Slot: {self.slots}, Map: {self.dimension}")

    def entrypoint(self):
        request: str = self.client.recv()
        key: str = get_key_from_dict(self.COMMON_EVENTS, request)

        if key:
            self.events.append(self.COMMON_EVENTS[key](request))
        elif self.commands:
            self.commands[0].response = self.handle_response(request)

    def consume_command(self) -> Optional[Command]:
        try:
            return self.commands.popleft()
        except IndexError as e:
            print(f"{e}")
            return None

    def consume_event(self) -> Optional[Event]:
        try:
            return self.events.popleft()
        except IndexError as e:
            print(f"{e}")
            return None

    def push_to_server(self, new_command: Command) -> None:
        if len(self.commands) <= self.max_command:
            self.commands.append(new_command)
            self.client.send(str(self.commands[-1]))