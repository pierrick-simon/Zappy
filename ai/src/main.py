##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## main
##

import sys
import argparse

from src.constants.ai_list import AI_LIST
from src.connection_handler import ConnectionHandler


def handle_args():
    args = argparse.ArgumentParser(description="Zappy AI Client", add_help=False)
    args.add_argument(
        "-p", dest="port", type=int, help="-p port number", default="4242"
    )
    args.add_argument(
        "-n", dest="name", type=str, help="-n name of the team", default="127.0.0.1"
    )
    args.add_argument(
        "-a",
        dest="algo",
        type=str,
        help="-n name of the ai/algorithm to use",
        default="survivor",
    )
    args.add_argument(
        "-h",
        dest="machine",
        type=str,
        help="-h machine name of the machine; localhost by default",
        default="localhost",
    )
    args.add_argument("--help", action="help", help="show this help message and exit")
    return args.parse_args()


def main():
    args = handle_args()
    if args.name == "GRAPHIC":
        print("Team cannot be GRAPHIC.", file=sys.stderr)
        return 84
    try:
        handler = ConnectionHandler(args.name, args.port, args.machine)
        handler.client.connect()
        handler.start_session()
        ai = AI_LIST[args.algo.lower()]
        ai(handler).run()
        handler.client.disconnect()
    except BaseException as e:
        print(e, file=sys.stderr)
        return 84


if __name__ == "__main__":
    sys.exit(main())
