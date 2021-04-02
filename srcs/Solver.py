import heapq
import logging
import datetime

from Node import Node
from Parser import Parser
from Heuristic import Heuristic


class Solver(Parser):
    COST: int = 1
    goal: list = []
    moves: list = []

    def _add_parser_args(self, parser):
        super()._add_parser_args(parser)
        parser.add_argument(
            "-lc",
            "--linear_conflict",
            action="store_true",
            help=f"Active linear conflict with heuristic (only with manhanttan distance)",
            dest="linear_conflict",
        )

    def _add_exclusive_args(self, parser):
        super()._add_exclusive_args(parser)
        heuristic_group = parser.add_mutually_exclusive_group(required=False)
        heuristic_group.add_argument(
            "-md",
            "--manhattan_distance",
            action="store_const",
            const=Heuristic.manhattan_distance,
            help="Use Manhanttan distance as Heuristic function",
            dest="heuristic_function",
            default=Heuristic.manhattan_distance,
        )
        heuristic_group.add_argument(
            "-dd",
            "--diagonal_distance",
            action="store_const",
            const=Heuristic.diagonal_distance,
            help="Use Diagonal distance as Heuristic function",
            dest="heuristic_function",
            default=Heuristic.manhattan_distance,
        )
        heuristic_group.add_argument(
            "-ed",
            "--euclidian_distance",
            action="store_const",
            const=Heuristic.euclidian_distance,
            help="Use Euclidian distance as Heuristic function",
            dest="heuristic_function",
            default=Heuristic.manhattan_distance,
        )

    @staticmethod
    def _get_path(end: Node):
        logging.info("Solution founded")
        n: Node = end
        path: list = [end]
        while n.parent is not None:
            path.append(n.parent)
            n = path[-1]
        return path[::-1]

    def __init__(self):
        super().__init__()
        print(self.args, "\n", self.kwargs)
        self.goal = self._generate_solution(self.kwargs["size"])
        # self.kwargs["grid"] = [0, 8, 4, 5, 2, 3, 6, 7, 1]
        self.kwargs["goal"] = self.goal
        self.kwargs["parent"] = None
        self.kwargs["cost"] = 0
        self.kwargs["heuristic_function"] = self.args.heuristic_function
        self.kwargs["linear_conflict"] = self.args.linear_conflict
        self.base = Node(self.kwargs)
        print(self.base)

    def __call__(self):
        """
        - OPENSET data structure
            A priority queue (high-priority elements first, here "high-priority" means "low-cost")
            or another container that allows for immediate retrieval of the lowest-cost item

        - CLOSESET data structure
            A container that easily allows to check whether a node currently is in the set or not
        """

        start = datetime.datetime.now()
        closeset: list = []
        openset: list = [self.base]
        heapq.heapify(openset)
        i: int = 0
        while len(openset):
            p = heapq.heappop(openset)
            closeset.append(p.grid)
            if p.grid == self.goal:
                pp = self._get_path(p)
                print(
                    f"{i} iterations | {len(pp)} movements | resolution time: {datetime.datetime.now() - start}"
                )
                return pp
            i += 1
            z = p.grid.index(0)
            states: list = p.get_successor(z)
            for s in states:
                if s is None or s.grid in closeset:
                    continue
                s.update(self.COST + p.g, self.goal, p)
                if s not in openset:
                    heapq.heappush(openset, s)
                else:
                    n = openset.index(s)
                    if s.g < openset[n].g:
                        openset[n].g = s.g
                        openset[n].f = s.f
                        openset[n].parent = s.parent
        print(f"Not possible to reach goal")
