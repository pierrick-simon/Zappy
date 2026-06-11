##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## main
##

import argparse
import time
import random

DX = [0, 1, 0, -1]
DY = [-1, 0, 1, 0]
DIR_NAME = ["N", "E", "S", "O"]

RESOURCES = ["food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

class SimMap:
    WIDTH = 12
    HEIGHT = 12

    FOOD_POSITIONS = [
        (2, 1), (7, 1), (10, 1),
        (1, 4), (5, 4), (9, 4),
        (3, 6), (8, 6), (11, 6),
        (0, 9), (4, 9), (7, 9), (11, 9),
        (2, 11), (6, 11), (10, 11),
    ]

    def __init__(self):
        self.grid = [
            [{r: 0 for r in RESOURCES} for _ in range(self.WIDTH)]
            for _ in range(self.HEIGHT)
        ]
        for x, y in self.FOOD_POSITIONS:
            self.grid[y][x]["food"] = 3

        stones = ["linemate", "deraumere", "sibur"]
        for _ in range(10):
            x = random.randint(0, self.WIDTH - 1)
            y = random.randint(0, self.HEIGHT - 1)
            s = random.choice(stones)
            self.grid[y][x][s] += 1

    def tile(self, x: int, y: int) -> dict:
        return self.grid[y % self.HEIGHT][x % self.WIDTH]

    def take(self, x: int, y: int, resource: str) -> bool:
        t = self.tile(x, y)
        if t.get(resource, 0) > 0:
            t[resource] -= 1
            return True
        return False

    def display(self, px: int, py: int) -> str:
        lines = []
        header = "  " + "".join(f"{x:3}" for x in range(self.WIDTH))
        lines.append(header)
        for y in range(self.HEIGHT):
            row = f"{y:2} "
            for x in range(self.WIDTH):
                if x == px % self.WIDTH and y == py % self.HEIGHT:
                    row += "  @"
                elif self.tile(x, y)["food"] > 0:
                    row += "  f"
                elif any(self.tile(x, y)[r] > 0 for r in RESOURCES if r != "food"):
                    row += "  #"
                else:
                    row += "  ."
            lines.append(row)
        lines.append("@ = AI  f = food  # = stone  . = empty")
        return "\n".join(lines)


class SimConnection:
    def __init__(self, team: str, delay: float):
        self._map = SimMap()
        self._team = team
        self._x = SimMap.WIDTH // 2
        self._y = SimMap.HEIGHT // 2
        self._dir = 0
        self._inv = {r: 0 for r in RESOURCES}
        self._inv["food"] = 10
        self._delay = delay
        self._step = 0
        self._pending_cmd = None

    def send(self, cmd: str):
        self._pending_cmd = cmd

    def recv(self) -> str:
        cmd = self._pending_cmd or ""
        self._pending_cmd = None

        self._step += 1

        if self._step % 15 == 0:
            self._inv["food"] = max(0, self._inv["food"] - 1)
            if self._inv["food"] == 0:
                self.close()
                raise "dead"
        response = self._dispatch(cmd)
        self._print_action(cmd, response)
        time.sleep(self._delay)
        return response

    def _dispatch(self, cmd: str) -> str:
        w = cmd.split()
        if not w:
            return "ko"
        name = w[0]

        if name == "Forward":
            self._x = (self._x + DX[self._dir]) % SimMap.WIDTH
            self._y = (self._y + DY[self._dir]) % SimMap.HEIGHT
            return "ok"

        if name == "Right":
            self._dir = (self._dir + 1) % 4
            return "ok"

        if name == "Left":
            self._dir = (self._dir - 1) % 4
            return "ok"

        if name == "Look":
            return self._build_look()

        if name == "Inventory":
            parts = ", ".join(f"{r} {self._inv[r]}" for r in RESOURCES)
            return f"[{parts}]"

        if name == "Take" and len(w) == 2:
            res = w[1]
            if self._map.take(self._x, self._y, res):
                self._inv[res] = self._inv.get(res, 0) + 1
                return "ok"
            return "ko"

        if name == "Set" and len(w) == 2:
            res = w[1]
            if self._inv.get(res, 0) > 0:
                self._inv[res] -= 1
                self._map.tile(self._x, self._y)[res] += 1
                return "ok"
            return "ko"
        return "ko"

    def _build_look(self) -> str:
        lat_dx = [1, 0, -1, 0]
        lat_dy = [0, 1, 0, -1]

        fwd_dx = DX[self._dir]
        fwd_dy = DY[self._dir]
        ldx = lat_dx[self._dir]
        ldy = lat_dy[self._dir]

        def tile_str(x, y):
            t = self._map.tile(x, y)
            items = []
            if x % SimMap.WIDTH == self._x % SimMap.WIDTH and \
                    y % SimMap.HEIGHT == self._y % SimMap.HEIGHT:
                items.append("player")
            items += [r for r in RESOURCES if t.get(r, 0) > 0]
            return " ".join(items)
        t0 = tile_str(self._x, self._y)

        fx = self._x + fwd_dx
        fy = self._y + fwd_dy
        t1 = tile_str(fx - ldx, fy - ldy)
        t2 = tile_str(fx, fy)
        t3 = tile_str(fx + ldx, fy + ldy)

        return f"[{t0}, {t1}, {t2}, {t3}]"

    def _print_action(self, cmd: str, response: str):
        food = self._inv["food"]
        pos = f"({self._x},{self._y})"
        dire = DIR_NAME[self._dir]
        print(f"[{self._step}] {pos} {dire} {food}"
              f"-> {cmd} <- {response}")

    def close(self):
        print("\nSimulation ended")
        print(self._map.display(self._x, self._y))

class SurvivalAI:
    def __init__(self, conn):
        self.conn = conn
        self.food = 10
        self._turn = 0

    def _cmd(self, command: str) -> str:
        self.conn.send(command)
        return self.conn.recv()

    def _refresh_food(self):
        raw = self._cmd("Inventory")
        self.food = _parse_food(raw)

    def run(self):
        self._refresh_food()
        while True:
            self._tick()

    def _tick(self):
        tiles = _parse_look(self._cmd("Look"))

        food_tile = next((i for i, t in enumerate(tiles) if "food" in t), None)

        if food_tile is not None:
            for move in _moves_to_tile(food_tile):
                self._cmd(move)
            result = self._cmd("Take food")
            if result == "ok":
                self.food += 1
            self._turn = 0
        else:
            self._explore()
            self._turn += 1

        if self._turn % 8 == 0:
            self._refresh_food()

    def _explore(self):
        self._cmd("Forward")
        if self._turn > 0 and self._turn % 5 == 0:
            self._cmd("Right")

def _parse_look(response: str) -> list[list[str]]:
    raw = response.strip().strip("[]")
    return [
        [item for item in tile.strip().split() if item]
        for tile in raw.split(",")]

def _parse_food(response: str) -> int:
    for part in response.strip("[] \n").split(","):
        part = part.strip()
        if part.startswith("food"):
            try:
                return int(part.split()[1])
            except (IndexError, ValueError):
                pass
    return 0


def _moves_to_tile(tile_idx: int) -> list[str]:
    if tile_idx == 0:
        return []
    row = 0
    while (row + 1) ** 2 <= tile_idx:
        row += 1
    col = tile_idx - row * row
    offset = col - row
    moves = ["Forward"] * row
    if offset > 0:
        moves += ["Right", "Forward"] * offset
    elif offset < 0:
        moves += ["Left", "Forward"] * abs(offset)
    return moves

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="zappy_ai",
        description="Zappy AI surviver",
        add_help=False
    )
    parser.add_argument("-p", type=int, required=True,
                        metavar="port", help="port du serveur")
    parser.add_argument("-n", required=True,
                        metavar="name", help="nom de l'équipe")
    parser.add_argument("-h", dest="host", default="localhost",
                        metavar="machine", help="adresse du serveur")
    parser.add_argument("--help", action="help")
    return parser


def main():
    parser = build_parser()
    args = parser.parse_args()
    random.seed(random.randint(1, 100))
    conn = SimConnection(team=args.n, delay=0)
    ai = SurvivalAI(conn)
    result = ai.run()
    print(result)
    conn.close()


if __name__ == "__main__":
    main()
