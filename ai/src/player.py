from collections.abc import Callable
from src.client import Client
from src.command import Command
from src.algorithm import algorithm


class ObservationState:
    inventory: list[str] = []
    dimension: tuple = ()
    vision: list[str] = []
    level: int = 1
    slots: int = 0
    status: bool = True
    handlers: dict[str, Callable[[None], None]]

    def __init__(self):
        self.handlers = {
            "Look": self.handle_look,
            "Inventory": self.handle_inventory,
            "Connect_nbr": self.handle_slots_nbr,
        }

    def handle_response(self, response: str):
        handler = self.handlers.get(response)

        if handler:
            handler(response)

    def handle_look(self, response: str):
        self.vision = response.split(",")

    def handle_inventory(self, response: str):
        self.inventory = response.split(",")

    def handle_dead(self, response: str):
        self.status = False

    def handle_slots_nbr(self, response: str):
        self.slots = int(response)

    def handle_incantation(self, response: str):
        if len(response > 3):
            self.level = response.split(sep=":")[1]


class Player:
    client: Client
    state: ObservationState
    commands: list[Command] = []

    def __init__(self):
        self.state = ObservationState()

    def start_session(self):
        if self.client.recv() != "WELCOME":
            raise ConnectionError(
                "The server did not initiate the connection with the client using WELCOME."
            )
        self.client.send(self.client.name)
        self.state.slots = int(self.client.recv())
        if self.state.slots < 1:
            raise ConnectionError(
                f"No slot available for the team: {self.client.name}."
            )
        self.state.dimension = tuple(self.client.recv().split())

    def move(self):
        """Call AI"""
        self.commands.append(algorithm(self.vision, self.inventory))

    def turn_right(self):
        """Call AI"""
        self.commands.append(Command("Right", self.turn_right))

    def turn_left(self):
        """Call AI"""
        self.commands.append(Command("Left", self.turn_left))

    def look(self):
        """Call AI"""
        self.commands.append(Command("Look", self.look, "food"))

    def get_inventory(self):
        """Call AI"""
        self.commands.append(Command("Inventory", self.get_inventory, "food"))

    def broadcast(self):
        """Call IA"""
        self.commands.append(Command("Broadcast", self.broadcast, "Start Incantation"))

    def get_connected_client_nbr(self):
        """Call IA"""
        self.commands.append(Command("Connect_nbr", self.get_connected_client_nbr))

    def fork(self):
        """Call AI"""
        self.commands.append(Command("Fork", self.fork))

    def eject(self):
        """Call AI"""
        self.commands.append(Command("Eject", self.eject))

    def take_obj(self):
        """Call AI"""
        self.commands.append(Command("Take", self.take_obj))

    def set_obj(self):
        """Call AI"""
        self.commands.append(Command("Set", self.set_obj))

    def start_incantation(self):
        """Call AI"""
        self.commands.append(Command("Incantation", self.start_incantation))

    def run(self, team: str, port: str, host: str):
        self.client = Client(team, port, host)
        self.client.connect()
        self.start_session()

        while self.state.status:
            for command in self.commands:
                self.client.send(str(command))
