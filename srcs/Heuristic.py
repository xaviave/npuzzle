import math


class Heuristic:
    @staticmethod
    def manhattan_distance(a_x: int, a_y: int, t_x: int, t_y: int):
        return abs((a_x - t_x)) + abs((a_y - t_y))

    @staticmethod
    def diagonal_distance(a_x: int, a_y: int, t_x: int, t_y: int):
        return max(abs((a_x - t_x)), abs((a_y - t_y)))

    @staticmethod
    def euclidian_distance(a_x: int, a_y: int, t_x: int, t_y: int):
        return math.sqrt(math.pow((a_x - t_x), 2) + math.pow((a_y - t_y), 2))
