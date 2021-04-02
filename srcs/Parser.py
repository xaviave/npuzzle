import itertools
import logging
import os
import math
import random
import re

from args.ArgParser import ArgParser
from args.FileCheckerAction import FileCheckerAction


class Parser(ArgParser):
    kwargs: dict = {}

    def _add_exclusive_args(self, parser):
        super()._add_exclusive_args(parser)
        parser_group = parser.add_mutually_exclusive_group(required=False)
        parser_group.add_argument(
            "-p",
            "--parse_puzzle",
            action="store_const",
            const=self._parse_puzzle_file,
            help="Use a puzzle from file",
            dest="parsing_function",
            default=self._generate_puzzle,
        )
        parser_group.add_argument(
            "-g",
            "--generate_puzzle",
            action="store_const",
            const=self._generate_puzzle,
            help="Use a pseudo-random generative puzzle",
            dest="parsing_function",
            default=self._generate_puzzle,
        )

    def _add_parser_args(self, parser):
        super()._add_parser_args(parser)
        parser.add_argument(
            "-f",
            "--file",
            type=str,
            action=FileCheckerAction,
            default=os.path.join("maps", "easy.txt"),
            help=f"Provide map TXT file - Using '{os.path.join('maps', 'easy.txt')}' as default file",
            dest="puzzle_file",
        )
        parser.add_argument(
            "-s",
            "--size",
            type=int,
            default=3,
            help=f"Provide map size - Using '3' as default map size",
            dest="puzzle_size",
        )

    @staticmethod
    def _generate_solution(size: int):
        nu: int = 1
        sr: int = 0
        sc: int = 0
        r: int = size - 1
        c: int = size - 1

        goal: list = list(range(size ** 2))
        while sr <= r and sc <= c:
            for i in range(sc, c + 1):
                goal[sr * size + i] = nu
                nu += 1
            sr += 1
            for i in range(sr, r + 1):
                goal[i * size + c] = nu
                nu += 1
            c -= 1
            if sr <= r:
                for i in range(c, sc - 1, -1):
                    goal[r * size + i] = nu
                    nu += 1
                r -= 1
            if sc <= c:
                for i in range(r, sr - 1, -1):
                    goal[i * size + sc] = nu
                    nu += 1
                sc += 1
        goal[goal.index(size ** 2)] = 0
        return goal

    @staticmethod
    def _is_solvable(grid: list) -> bool:
        """
        NI for number of inversion
        NT for 0 Position from bottom (y)

        Puzzle is solvable if:
            - SIZE % 2 == 1 AND NI % 2 == 0
            - SIZE % 2 == 0 AND (
                (NT % 2 == 0 AND NI % 2 == 1)
                OR (NT == 1 AND NI % 2 == 0))
        """
        size: int = int(math.sqrt(len(grid)))
        nt: int = int(size - (grid.index(0) // size))
        ni: int = sum(
            [
                1
                for i in range(len(grid))
                for j in range(i + 1, len(grid))
                if grid[j] and grid[j] < grid[i]
            ]
        )
        print(f"size = {size} | ni = {ni} | nt = {nt}")
        if ((size % 2) and (ni % 2)) or (
            (size % 2) == 0
            and (((nt % 2) and (ni % 2) == 0) or ((nt % 2) == 0 and (ni % 2)))
        ):
            return True
        return False

    def _parse_puzzle_file(self) -> dict:
        logging.info("_parse_puzzle_file")
        with open(self.args.puzzle_file, "r") as f:
            fdata = list(
                filter(None, [re.match("[0-9 ]+", r) for r in f.read().split("\n")])
            )
        grid = list(
            map(
                int,
                map(
                    int,
                    list(
                        itertools.chain(
                            *[
                                list(filter(None, x.group().split(" ")))
                                for x in fdata[1:]
                            ]
                        )
                    ),
                ),
            )
        )
        if not self._is_solvable(grid):
            raise ValueError("Puzzle not Solvable")
        return {
            "size": int(fdata[0].group()),
            "grid": grid,
        }

    @staticmethod
    def _swap_empty(size: int, p: list):
        idx: int = p.index(0)
        poss: list = []
        if idx % size > 0:
            poss.append(idx - 1)
        if idx % size < size - 1:
            poss.append(idx + 1)
        if idx / size > 0 and idx - size >= 0:
            poss.append(idx - size)
        if idx / size < size - 1:
            poss.append(idx + size)
        swi = random.choice(poss)
        p[idx] = p[swi]
        p[swi] = 0

    def _generate_puzzle(self):
        logging.info("_generate_puzzle")
        p: list = self._generate_solution(self.args.puzzle_size)
        for i in range(10000):
            self._swap_empty(self.args.puzzle_size, p)
        return {"size": self.args.puzzle_size, "grid": p}

    def __init__(self):
        super().__init__("Npuzzle Solver")
        self.kwargs: dict = self.args.parsing_function()
