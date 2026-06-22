##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Human AI
##

import curses
from curses import window
from curses.textpad import Textbox, rectangle
from threading import Thread
from typing import Callable, Any

from src.command import Command
from src.constants.constants import COMMAND_FACTORY
from src.connection_handler import ConnectionHandler


def call_function_in_thread(callback: Callable, *args) -> Thread:
    if args is not None:
        thread = Thread(target=callback, args=args, daemon=True)
    else:
        thread = Thread(target=callback, daemon=True)
    return thread


def get_longuest_key(dictionary: dict) -> str:
    if not dictionary:
        return None
    return max(dictionary.keys(), key=len)


class HumanAI:
    status: bool = True
    INPUT_RECTANGLE_TOP_Y = 10
    INPUT_RECTANGLE_LEFT_X = 70
    INPUT_RECTANGLE_BOTTOM_Y = INPUT_RECTANGLE_TOP_Y + 11
    INPUT_RECTANGLE_RIGHT_X = INPUT_RECTANGLE_LEFT_X + 40

    WIN_HEIGHT = (INPUT_RECTANGLE_BOTTOM_Y - INPUT_RECTANGLE_TOP_Y) - 1
    WIN_WIDTH = (INPUT_RECTANGLE_RIGHT_X - INPUT_RECTANGLE_LEFT_X) - 1
    WIN_BEGIN_Y = INPUT_RECTANGLE_TOP_Y + 1
    WIN_BEGIN_X = INPUT_RECTANGLE_LEFT_X + 1

    EVENT_RECTANGLE_TOP_Y = INPUT_RECTANGLE_TOP_Y
    EVENT_RECTANGLE_LEFT_X = INPUT_RECTANGLE_RIGHT_X + 5
    EVENT_RECTANGLE_BOTTOM_Y = EVENT_RECTANGLE_TOP_Y + 20
    EVENT_RECTANGLE_RIGHT_X = EVENT_RECTANGLE_LEFT_X + 30
    EVENT_BOX_WIDTH = EVENT_RECTANGLE_RIGHT_X - EVENT_RECTANGLE_LEFT_X

    CMD_BOX_TOP_Y = INPUT_RECTANGLE_TOP_Y
    CMD_BOX_LEFT_X = INPUT_RECTANGLE_LEFT_X - 35
    CMD_BOX_BOTTOM_Y = CMD_BOX_TOP_Y + 11
    CMD_BOX_RIGHT_X = CMD_BOX_LEFT_X + 30
    CMD_BOX_WIDTH = CMD_BOX_RIGHT_X - CMD_BOX_LEFT_X
    SEPARATOR = int(CMD_BOX_LEFT_X + (CMD_BOX_WIDTH / 2)) + 4

    INVENTORY_BOX_TOP_Y = INPUT_RECTANGLE_BOTTOM_Y + 3
    INVENTORY_BOX_LEFT_X = INPUT_RECTANGLE_LEFT_X - 35
    INVENTORY_BOX_BOTTOM_Y = INPUT_RECTANGLE_BOTTOM_Y + 9
    INVENTORY_BOX_RIGHT_X = INPUT_RECTANGLE_RIGHT_X
    INVENTORY_BOX_WIDTH = INVENTORY_BOX_RIGHT_X - INVENTORY_BOX_LEFT_X
    CELL_WIDTH = 27

    def __init__(self, handler: ConnectionHandler) -> None:
        self.handler = handler
        self.inventory = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
        }
        self.SPECIAL_RESPONSE: dict[str, Callable[["HumanAI", Any], None]] = {
            "Look": self.display_look,
            "Inventory": self.display_inventory,
        }

        self.stdscr: window = curses.initscr()
        curses.noecho()
        curses.cbreak()
        self.stdscr.keypad(True)
        self.stdscr.clear()
        if curses.has_colors():
            curses.start_color()
            curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
            curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
            curses.init_pair(3, curses.COLOR_CYAN, curses.COLOR_BLACK)
        self.stdscr.refresh()

    def get_user_input(self, textbox: Textbox) -> str:
        textbox.edit()
        message: str = textbox.gather()
        return message

    def send_user_command(self, raw_commands: str) -> None:
        commands: list[str] = raw_commands.split("\r\n")

        for command in commands:
            tokens: list[str] = command.split()
            if tokens and tokens[0] in COMMAND_FACTORY:
                arg = tokens[1] if len(tokens) > 1 else None
                self.handler.push_to_server(Command(tokens[0], arg))

    def display_look(self, vision: list[list[str]]):
        pass

    def display_line(self, resource: str, y: int, x: int) -> None:
        text = (
            f"[{resource.capitalize():<{len(get_longuest_key(self.inventory))}} "
            f"{self.inventory[resource]:>3}]"
        )
        self.stdscr.addstr(y, x, text)

    def display_inventory(self, inventory: dict[str, int]):
        self.stdscr.addstr(
            self.INVENTORY_BOX_TOP_Y - 1,
            self.INVENTORY_BOX_LEFT_X + int(self.INVENTORY_BOX_WIDTH / 2) - 5,
            "[Inventory]",
        )
        rectangle(
            self.stdscr,
            self.INVENTORY_BOX_TOP_Y,
            self.INVENTORY_BOX_LEFT_X,
            self.INVENTORY_BOX_BOTTOM_Y,
            self.INVENTORY_BOX_RIGHT_X,
        )
        if inventory is None:
            return
        self.inventory = inventory
        x1 = self.INVENTORY_BOX_LEFT_X + 3
        x2 = x1 + self.CELL_WIDTH
        x3 = x2 + self.CELL_WIDTH
        self.display_line("food", self.INVENTORY_BOX_TOP_Y + 1, x2)
        self.display_line("linemate", self.INVENTORY_BOX_TOP_Y + 3, x1)
        self.display_line("deraumere", self.INVENTORY_BOX_TOP_Y + 3, x2)
        self.display_line("sibur", self.INVENTORY_BOX_TOP_Y + 3, x3)
        self.display_line("mendiane", self.INVENTORY_BOX_TOP_Y + 5, x1)
        self.display_line("phiras", self.INVENTORY_BOX_TOP_Y + 5, x2)
        self.display_line("thystame", self.INVENTORY_BOX_TOP_Y + 5, x3)
        self.stdscr.refresh()

    def display_events(self):
        self.stdscr.addstr(
            self.EVENT_RECTANGLE_TOP_Y - 1,
            (self.EVENT_RECTANGLE_LEFT_X + int(self.EVENT_BOX_WIDTH / 2) - 4),
            "[Events]",
        )
        rectangle(
            self.stdscr,
            self.EVENT_RECTANGLE_TOP_Y,
            self.EVENT_RECTANGLE_LEFT_X,
            self.EVENT_RECTANGLE_BOTTOM_Y,
            self.EVENT_RECTANGLE_RIGHT_X,
        )
        offset: int = 1
        for event in self.handler.events:
            self.stdscr.addstr(
                self.EVENT_RECTANGLE_TOP_Y + (offset),
                self.EVENT_RECTANGLE_LEFT_X + 2,
                f"{str(event):<{18}}",
                curses.color_pair(3),
            )
            offset += 1
        self.stdscr.refresh()

    def get_color(self, response: Any):
        if response is None:
            return 1
        else:
            return 2

    def display_commands(self) -> None:
        self.stdscr.addstr(
            self.CMD_BOX_TOP_Y - 1, self.CMD_BOX_LEFT_X + 10, "[Commands]"
        )
        rectangle(
            self.stdscr,
            self.CMD_BOX_TOP_Y,
            self.CMD_BOX_LEFT_X,
            self.CMD_BOX_BOTTOM_Y,
            self.CMD_BOX_RIGHT_X,
        )
        offset: int = 1
        color: int = 1
        for cmd in self.handler.commands:
            if cmd.command in self.SPECIAL_RESPONSE:
                self.SPECIAL_RESPONSE[cmd.command](cmd.response)
            elif cmd.command in COMMAND_FACTORY:
                color = self.get_color(cmd.response)
                self.stdscr.addstr(
                    self.CMD_BOX_TOP_Y + offset,
                    self.CMD_BOX_LEFT_X + 2,
                    f"{str(cmd)}",
                    curses.color_pair(color),
                )
                self.stdscr.addstr(
                    self.CMD_BOX_TOP_Y + offset,
                    self.SEPARATOR,
                    "|",
                    curses.color_pair(color),
                )
                self.stdscr.addstr(
                    self.CMD_BOX_TOP_Y + offset,
                    self.SEPARATOR + 3,
                    str(cmd.response),
                    curses.color_pair(color),
                )
                offset += 1
        self.stdscr.refresh()

    def display_text_box(self):
        self.stdscr.addstr(
            self.INPUT_RECTANGLE_TOP_Y - 1,
            self.INPUT_RECTANGLE_LEFT_X + 3,
            "Enter command: (hit Ctrl-G to send)",
        )
        rectangle(
            self.stdscr,
            self.INPUT_RECTANGLE_TOP_Y,
            self.INPUT_RECTANGLE_LEFT_X,
            self.INPUT_RECTANGLE_BOTTOM_Y,
            self.INPUT_RECTANGLE_RIGHT_X,
        )
        self.stdscr.refresh()

    def display_box(self):
        self.display_text_box()
        self.display_events()
        self.display_commands()
        self.display_inventory(self.inventory)

    def run(self) -> None:
        call_function_in_thread(self.handler.listen_server).start()
        self.stdscr.refresh()
        textwin: window = curses.newwin(
            self.WIN_HEIGHT, self.WIN_WIDTH, self.WIN_BEGIN_Y, self.WIN_BEGIN_X
        )
        textbox: Textbox = Textbox(textwin)
        self.display_box()
        self.stdscr.refresh()
        textwin.refresh()

        while self.status:
            self.send_user_command(self.get_user_input(textbox))
            textwin.clear()
            textwin.refresh()
            self.stdscr.clear()
            self.stdscr.refresh()
            self.display_box()
