import copy
import logging
import line_profiler

from Heuristic import Heuristic


class Node(Heuristic):
    parent = None  # hash value from hash_dict
    h: int = 0
    g: int = 0
    f: int = 0
    size: int
    length: int
    grid: list = []
    moves: list = []

    def _rigth(self, z: int):
        if (z % self.size) == self.size - 1:
            return None
        # optimize deepecopy
        cc = copy.deepcopy(self)
        cc.grid[z] = cc.grid[z + 1]
        cc.grid[z + 1] = 0
        return cc

    def _up(self, z: int):
        if z < self.size:
            return None
        cc = copy.deepcopy(self)
        cc.grid[z] = cc.grid[z - cc.size]
        cc.grid[z - cc.size] = 0
        return cc

    def _left(self, z: int):
        if (z % self.size) == 0:
            return None
        cc = copy.deepcopy(self)
        cc.grid[z] = cc.grid[z - 1]
        cc.grid[z - 1] = 0
        return cc

    def _down(self, z: int):
        if z >= (self.length - self.size):
            return None
        cc = copy.deepcopy(self)
        cc.grid[z] = cc.grid[z + cc.size]
        cc.grid[z + cc.size] = 0
        return cc

    @staticmethod
    def _linear_conflict(size: int, goal: list, grid: list) -> int:
        """
        linear conflit - if 2 elements are not in the good order on the same line,
        it will need 2 moves to swap thoses elements
        x_g for element
        y_g for element neighbour
        x_s for element solution coord
        x_s for element neigbour solution coord
        """
        lc: int = 0
        r_size = range(size)
        for r in r_size:
            for c in r_size:
                # line
                if c + 1 < size:
                    x_g: int = r * size + c
                    y_g: int = r * size + c + 1
                    x_s: int = goal.index(grid[x_g])
                    y_s: int = goal.index(grid[y_g])
                    if all(
                        [
                            grid[x_g],
                            grid[y_g],
                            x_g % size < y_g % size,
                            x_s % size > y_s % size,
                            (x_g / size) == (y_g / size),
                            (x_s / size) == (y_s / size),
                        ]
                    ):
                        lc += 1

                # column
                if r + 1 < size:
                    x_g: int = r * size + c
                    y_g: int = (r + 1) * size + c
                    x_s: int = goal.index(grid[x_g])
                    y_s: int = goal.index(grid[y_g])
                    if all(
                        [
                            grid[x_g],
                            grid[y_g],
                            x_g // size < y_g // size,
                            x_s // size > y_s // size,
                            (x_g % size) == (y_g % size),
                            (x_s % size) == (y_s % size),
                        ]
                    ):
                        lc += 1
        return lc * 2

    def _get_heuristic(self, grid: list, goal: list) -> int:
        # local var
        h: int = 0
        lc: int = 0
        size: int = self.size  # optim
        for i in grid:
            if i == 0:
                continue
            t_p: int = goal.index(i)
            g_p: int = grid.index(i)
            h += self.f_heuristic(g_p // size, g_p % size, t_p // size, t_p % size)
        if self.f_linear_conflict:
            lc += self._linear_conflict(size, goal, grid)
        return h + lc

    def _init_kwargs(self, kwargs):
        logging.warning("_init_kwargs")
        self.grid: list = kwargs["grid"]
        self.size: int = kwargs["size"]
        self.length: int = self.size ** 2
        self.f_heuristic = kwargs["heuristic_function"]
        self.f_linear_conflict: bool = kwargs["linear_conflict"] & (
            self.f_heuristic == Heuristic.manhattan_distance
        )
        self.update(kwargs["cost"], kwargs["goal"], kwargs["parent"])

    def __init__(self, kwargs: dict = None):
        super().__init__()
        self.moves = [self._rigth, self._up, self._down, self._left]
        if kwargs is not None:
            self._init_kwargs(kwargs)
            print(self)

    def __str__(self):
        s = f"\n________________________\nh = {self.h} | g = {self.g} | f = {self.f}\n"
        for i, n in enumerate(self.grid):
            if i != 0 and (i % self.size) == 0:
                s += "\n"
            s += f"{n} "
        return s + "\n________________________"

    def __lt__(self, other):
        return self.f < other.f

    def update(self, cost: int, goal: list, parent):
        self.parent = parent
        self.h = self._get_heuristic(self.grid, goal)
        self.g = cost
        self.f = self.h + self.g

    def get_successor(self, z: int) -> list:
        return [self.moves[0](z), self.moves[1](z), self.moves[2](z), self.moves[3](z)]
