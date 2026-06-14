##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## BackpackModule
##

"""@package docstring
Documentation for the AutoGather module

The AutoGather module generates a sequence of movement and take commands
to collect aimed resources from a Look observation, with a time limit

It does'nt call commands directly it builds a plan that the AI
can execute step by step

example:

- Basic usage:

mod = AutoGatherModule()
plan = mod.auto_gather(
    obs=["food", "linemate", "", "", "food"],
    aimed_materials={"food": 2, "linemate": 1},
    max_time=200
)
mod.plan()


- Integrate with BackpackModule:

plan = mod.auto_gather(obs, targets, max_time)
for action in plan:
    backpack.tick(action)
    # send actions to server
"""

from src.constants.resources import *


class AutoGatherModule:
    def __init__(self) -> None:
        self.plan = []
        self.time_used = 0
        self.remaining = {}

    def auto_gather(self, obs: list, aimed_materials: dict, max_time: int):
        self.remaining = {r: q for r, q in aimed_materials.items() if q > 0}
        paths = self._build_path(obs)

        self.plan, self.time_used = self._build_plan(paths, max_time)

        return self.plan

    def _build_path(self, obs: list) -> list:
        """! Builds the list of (tile_idx, resource) path from obs

        @param obs: list of tile strings from a Look command
        @return list of tuples of wanted resources
        """
        paths = []
        for tile_idx, tile_str in enumerate(obs):
            for resource in self._parse_tile(tile_str):
                if resource in self.remaining:
                    paths.append((tile_idx, resource))

        return paths

    def _find_best_path(self, paths: list, cur_x: int, cur_y: int, cur_orient: int):
        """! Finds the smallest path to reach from the current position

        @param paths: list of (tile_idx, resource) tuples
        @param cur_x: current x position
        @param cur_y: current z position
        @param cur_orient: current orientation
        @return (path, length, moves, new_state) or (None, None, None, None)
        """
        best = None
        best_length = None
        best_moves = None
        best_state = None

        for path in paths:
            tile_idx, resource = path
            if resource not in self.remaining:
                continue

            tx, ty = self._tile_to_coords(tile_idx)
            moves, new_x, new_y, new_orient = self._moves_between(
                cur_x, cur_y, cur_orient, tx, ty
            )

            length = (
                    sum(COMMAND_TIME[m] for m in moves)
                    + COMMAND_TIME["Take"]
            )

            if best_length is None or length < best_length:
                best_length = length
                best = path
                best_moves = moves
                best_state = (new_x, new_y, new_orient)

        return best, best_length, best_moves, best_state

    def _apply_path(self, plan: list, best: tuple, best_moves: list) -> None:
        """! Appends the moves/take command for the chosen path to the plan
        and updates the remaining resources count

        @param plan: plan list being built
        @param best: (tile_idx, resource) tuple of the chosen path
        @param best_moves: movement commands to reach the path
        """
        tile_idx, resource = best
        plan.extend(best_moves)
        plan.append(f"Take {resource}")

        self.remaining[resource] -= 1
        if self.remaining[resource] == 0:
            del self.remaining[resource]

    def _build_plan(self, paths: list, max_time: int):
        """! Builds a movement/take plan from a list of paths

        @param paths: list of (tile_idx, resource) tuples
        @param max_time: time limit for the whole plan
        @return (plan, time_used)
        """
        time_left = max_time
        plan = []

        cur_x, cur_y = 0, 0
        cur_orient = 0

        while paths and self.remaining:
            best, best_length, best_moves, best_state = self._find_best_path(
                paths, cur_x, cur_y, cur_orient
            )

            if best is None:
                break

            if best_length > time_left:
                paths.remove(best)
                continue

            self._apply_path(plan, best, best_moves)
            time_left -= best_length
            cur_x, cur_y, cur_orient = best_state

            paths.remove(best)

        return plan, max_time - time_left

    def is_complete(self) -> bool:
        """! True if the plan have all the resources needed inside it

        @return bool
        """
        return not self.remaining

    @staticmethod
    def _tile_to_coords(tile_idx: int):
        """! Converts a tile index into (x, y) coordinates
        relative to the player's starting tile and orientation

        @param tile_idx: Index of the target tile in the Look command
        @return (x, y) tuple
        """
        if tile_idx == 0:
            return (0, 0)

        row = 0
        while (row + 1) ** 2 <= tile_idx:
            row += 1

        col = tile_idx - row * row
        offset = col - row

        return (offset, row)

    @staticmethod
    def _moves_between(
        cur_x: int, cur_y: int, cur_orient: int, target_x: int, target_y: int
    ):
        """! Computes the move commands needed to go from
        (cur_x, cur_y) oriented to cur_orient to (target_x, target_y).

        @return (moves, new_x, new_y, new_orient)
        """
        dx = target_x - cur_x
        dy = target_y - cur_y

        moves = []
        orient = cur_orient

        if dy != 0:
            desired_orient = 0 if dy > 0 else 2
            moves += AutoGatherModule._turn_to(orient, desired_orient)
            orient = desired_orient
            moves += ["Forward"] * abs(dy)

        if dx != 0:
            desired_orient = 1 if dx > 0 else 3
            moves += AutoGatherModule._turn_to(orient, desired_orient)
            orient = desired_orient
            moves += ["Forward"] * abs(dx)

        return moves, target_x, target_y, orient

    @staticmethod
    def _turn_to(cur_orient: int, target_orient: int):
        """! Returns the list of Left/Right commands needed to turn
        from cur_orient to target_orient

        @return list of "Left"/"Right" commands
        """
        diff = (target_orient - cur_orient) % 4

        if diff == 0:
            return []
        elif diff == 1:
            return ["Right"]
        elif diff == 2:
            return ["Right", "Right"]
        else:
            return ["Left"]

    @staticmethod
    def _parse_tile(tile) -> list:
        """! Extracts resource names from a tile

        @param tile: list of tokens from a parsed Look response
        @return List of resource names found on the tile
        """
        return [t for t in tile if t in RESOURCES]
