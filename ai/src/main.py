##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## main
##

import sys
import argparse
from src.connection_handler import ConnectionHandler


def handle_args():
    args = argparse.ArgumentParser(description="Zappy AI Client", add_help=False)
    args.add_argument("-p", dest="port", type=int, help="-p port number")
    args.add_argument("-n", dest="name", type=str, help="-n name of the team")
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
        entrypoint: ConnectionHandler = ConnectionHandler(
            args.name, args.port, args.machine
        )
        entrypoint.start_session()
    except BaseException as e:
        print(e)
        return 84
