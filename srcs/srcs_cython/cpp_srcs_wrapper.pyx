#srcs_cython: language_level=3
# distutils: language = c++

import numpy as np
cimport numpy as np

from libcpp.list cimport list
from libcpp.vector cimport vector
from libcpp.memory cimport shared_ptr


"""
c++ interface in cython

In srcs_cython dir:
    python3 setup.py build_ext --inplace
"""

cdef extern from "../srcs_cpp/includes/Node.hpp":
    cdef cppclass Node:
        int                 size
        int                 length
        int                 f
        int                 g
        vector[int]         grid
        shared_ptr[Node]    p_ptr

        Node(int, vector[int])

cdef extern from "../srcs_cpp/includes/NPuzzleHandler.hpp":
    cdef cppclass NPuzzleHandler:
        Node                p
        Node                s
        list[Node]          path

        NPuzzleHandler(Node *p_, Node *s_)
        void                solve()
        int                 get_length()
        vector[int]         get_path_grid(int)


cdef class PyNode:
    cdef Node *n_ptr

    def __cinit__(self, size, grid):
        self.n_ptr = new Node(size, np.array(grid))

    @property
    def size(self):
        return self.n_ptr.size

    @property
    def grid(self):
        return self.n_ptr.grid

cdef class PyNPuzzleHandler:
    cdef NPuzzleHandler *nph_ptr

    def __cinit__(self, PyNode p_, PyNode s_):
        self.nph_ptr = new NPuzzleHandler(p_.n_ptr, s_.n_ptr)

    @property
    def path(self):
        path_size = self.nph_ptr.path.size()
        puzzle_size = self.nph_ptr.get_length()
        cdef np.ndarray x_path = np.zeros(
            [path_size, puzzle_size]
        )
        for i in range(path_size):
            x_path[i] = self.nph_ptr.get_path_grid(i)
        return x_path

    def solve(self):
        self.nph_ptr.solve()

def create_node(size: int, grid: np.array):
    return PyNode(size, grid)

def create_npuzzlehandler(p_: PyNode, s_: PyNode):
    return PyNPuzzleHandler(p_, s_)
