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

    def __init__(self, name: str, port: int, host: str) -> None:
        self.name = name
        self.port = port
        self.host = host
        self._buffer = b""

    def connect(self) -> None:
        self.socket_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_client.connect((self.host, self.port))

    def send(self, message: str) -> None:
        self.socket_client.send(bytes(message + "\n", "utf-8"))

    def recv(self) -> str:
        while b"\n" not in self._buffer:
            self._buffer += self.socket_client.recv(1024)
        line, _, self._buffer = self._buffer.partition(b"\n")
        return line.decode().strip()

    def disconnect(self) -> None:
        self.socket_client.close()