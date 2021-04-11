import os
import ctypes
import logging

from libcpp.vector cimport vector
from libcpp.memory cimport shared_ptr


# c++ interface to cython
cdef extern from "Node.hpp":
    cdef cppclass Node:
        int                 size
        int                 length
        int                 f
        int                 g
        vector[int]         grid
        shared_ptr[Node]    p_ptr

        Node(int, int*)

cdef extern from "NPuzzleHandler.hpp":
    cdef cppclass NPuzzleHandler:
        Node                p
        Node                s
        int                 len_path
        Node                *path

        NPuzzleHandler(Node, Node)
        void                solve(void)

cdef class PyNode:
    cdef Node *n_ptr

    def __cinit__(self, int size, int *grid):
        self.n_ptr = new Node(size, grid)

    def __dealloc__(self):
        del self.n_ptr

cdef class PyNPuzzleHandler:
    cdef NPuzzleHandler *nph_ptr

    def __cinit__(self, size, grid):
        self.nph_ptr = new NPuzzleHandler(size, grid)

    def __dealloc__(self):
        del self.nph_ptr

    def solve(self):
        self.nph_ptr.solve()

    def get_path_node(self, i):
        return self.nph_ptr.path[i]


"""
https://dmtn-013.lsst.io/
https://gist.github.com/benjaminirving/436262a58f9da5a68532
https://cython.readthedocs.io/en/latest/src/userguide/wrapping_CPlusPlus.html

need to refactor CWrapper to:
    - init a node and communicate with it
    - init Npuzzlehandler and communicate with
    - get a list a C++ obj 

"""


class CWrapper:
    lib: ctypes.CDLL = None
    lib_name: str = os.path.join("so_cpp", "lib_npuzzle.so")
    compile_cmd: str = "make lib"

    @staticmethod
    def _list_to_c_int(l: list):
        """
        Transform a int list to a c_int array used by the C++ lib

        type(arr) = CWrapper.c_int_Array_9
        """
        arr = (ctypes.c_int * len(l))()
        arr[:] = l[:]
        return arr

    def _compile_lib(self, cmd: str = compile_cmd):
        logging.warning(f"Compiling C++ sources with '{cmd}'")
        error_code: int = os.system(cmd)
        if error_code or not os.path.exists(self.lib_name):
            logging.error(f"Compilation failed or file '{self.lib_name}' not found")
            exit(-1)

    def __init__(self, lib_name: str = lib_name):
        # load the library
        self._compile_lib()
        self.lib: ctypes.CDLL = ctypes.cdll.LoadLibrary(lib_name)
        self.lib.launch_solver.restype = ctypes.POINTER(Foo)

    def launch_solver(self, size: int, c_puzzle: list, c_solution: list):
        logging.info("Launching C++ Solver")
        cpp_ret = self.lib.launch_solver(
            size, self._list_to_c_int(c_puzzle), self._list_to_c_int(c_solution)
        )
        arr = ctypes.cast(cpp_ret.contents.grid, ctypes.POINTER(ctypes.c_int))
        print(cpp_ret.contents.m_states, cpp_ret.contents.t_states)
        for a in range(9):
            print(arr[a])
        print("cpp return " , len(cpp_ret.contents.grid), type(cpp_ret))
