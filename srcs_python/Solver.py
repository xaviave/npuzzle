import heapq
import logging
import datetime

from Node import Node
from Parser import Parser
from Heuristic import Heuristic

from cython.CPP_wrapper import PyNode, PyNpuzzleHandler


class Solver(Parser):
    COST: int = 1
    goal: list = []
    moves: list = []
    hash_dict: dict = {}

    def _add_parser_args(self, parser):
        super()._add_parser_args(parser)
        parser.add_argument(
            "-lc",
            "--linear_conflict",
            action="store_true",
            help=f"Active linear conflict with heuristic (only with manhanttan distance)",
            dest="linear_conflict",
        )
        parser.add_argument(
            "-cpp",
            "--cpp_code",
            action="store_const",
            const=self._cpp_solver,
            help="Launch cpp code_solver, for high speed",
            default=self._solver,
            dest="solver_func",
        )
        parser.add_argument(
            "-sf",
            "--solution_file",
            type=str,
            help=f"File where Solution is save",
            default="solution_file.txt",
            dest="solution_file",
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

    def _save_in_file(self, path: list):
        with open(self.args.solution_file, "w") as fd:
            fd.write("\n".join([x.__str__() for x in path]))

    def _get_path(self, start: datetime.datetime, end: Node):
        logging.info("Solution founded")
        n: Node = end
        path: list = [end]
        while n.parent is not None:
            path.append(self.hash_dict[n.parent])
            n = path[-1]
        path = path[::-1]
        print(
            f"""
number of node explored: {len(self.hash_dict)}
{len(path)} movements done to find the solution
resolution time: {datetime.datetime.now() - start}
"""
        )
        self._save_in_file(path)
        return path

    def _solver(self):
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

        c_append = closeset.append
        while len(openset):
            p = heapq.heappop(openset)
            if p.grid == self.goal:
                return self._get_path(start, p)
            self.hash_dict[hash(p)] = p
            c_append(p.grid)
            z = p.grid.index(0)
            states: list = p.get_successor(z)
            for s in states:
                if s is None or s.grid in closeset:
                    continue
                s.update(self.COST + p.g, self.goal, hash(p))
                if s not in openset:
                    heapq.heappush(openset, s)
                else:
                    n = openset.index(s)
                    if s.g < openset[n].g:
                        openset[n].g = s.g
                        openset[n].f = s.f
                        openset[n].parent = s.parent

    def _cpp_solver(self):
        logging.warning("Launching C++ module")
        p_node = PyNode(self.base.size, self.base.grid)
        s_node = PyNode(self.base.size, self.goal)
        nph = PyNpuzzleHandler(p_node, s_node)
        nph.solve()


    def __init__(self):
        super().__init__()
        self.goal = self._generate_solution(self.kwargs["size"])
        self.kwargs["cost"] = 0
        self.kwargs["parent"] = None
        self.kwargs["goal"] = self.goal
        self.kwargs["linear_conflict"] = self.args.linear_conflict
        self.kwargs["heuristic_function"] = self.args.heuristic_function
        self.base = Node(self.kwargs)
        self.hash_dict: dict = {hash(self.base): self.base}

    def __call__(self):
        self.args.solver_func()
