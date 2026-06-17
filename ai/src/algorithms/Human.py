##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## Human AI
##

import time
import curses
from curses import wrapper, window
from curses.textpad import Textbox, rectangle

from src.algorithms.modules import auto_gather_module as ag
from src.connection_handler import ConnectionHandler
from src.algorithms.modules.backpack_module import BackpackModule


class HumanAI:
    RECTANGLE_TOP_Y = 30
    RECTANGLE_LEFT_X = 72
    RECTANGLE_BOTTOM_Y = (RECTANGLE_TOP_Y + 10)
    RECTANGLE_RIGHT_X = (RECTANGLE_LEFT_X + 40)

    WIN_HEIGHT = (RECTANGLE_BOTTOM_Y - RECTANGLE_TOP_Y) - 1
    WIN_WIDTH = (RECTANGLE_RIGHT_X - RECTANGLE_LEFT_X) - 1
    WIN_BEGIN_Y = RECTANGLE_TOP_Y + 1
    WIN_BEGIN_X = RECTANGLE_LEFT_X + 1

    def __init__(self, handler: ConnectionHandler) -> None:
        self.handler = handler
        self.backpack = BackpackModule()

        self.stdscr: window = curses.initscr()
        curses.noecho()
        curses.cbreak()
        self.stdscr.keypad(True)
        self.stdscr.clear()
        self.stdscr.refresh()

    def get_user_input(self, textbox: Textbox):
        textbox.edit()
        message: str = textbox.gather()
        print("Message:", message)
        
    def run(self) -> None:
        self.stdscr.addstr(1, 2, "Enter command: (hit Ctrl-G to send)")
        rectangle(
            self.stdscr,
            self.RECTANGLE_TOP_Y,
            self.RECTANGLE_LEFT_X,
            self.RECTANGLE_BOTTOM_Y,
            self.RECTANGLE_RIGHT_X,
        )
        textwin = curses.newwin(
            self.WIN_HEIGHT, self.WIN_WIDTH, self.WIN_BEGIN_Y, self.WIN_BEGIN_X
        )
        textbox: Textbox = Textbox(textwin)
        self.stdscr.refresh()
        textwin.refresh()

        while True:
            self.get_user_input(textbox)
            textwin.clear()
            textwin.refresh()
