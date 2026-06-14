##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## client
##

import socket


class Client:
    name: str
    port: int
    host: str
    socket_client: socket.socket

    def __init__(self, name: str, port: str, host: str) -> None:
        self.name = name
        self.port = port
        self.host = host

    def connect(self) -> None:
        self.socket_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_client.connect((self.host, self.port))

    def send(self, message: str) -> None:
        self.socket_client.send(bytes(message + "\n", "utf-8"))

    def recv(self) -> str:
        data = b""
        while not data.endswith(b"\n"):
            data += self.socket_client.recv(1)
        return data.decode().strip()

    def disconnect(self) -> None:
        self.socket_client.close()
