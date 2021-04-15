# N-Puzzle

## Project

This project is a 3x3 npuzzle solver using A* search algorithm in Python/C++.

Python solving time is from les than a second to 5 for hard puzzle, in C++ always under 1s.

The project use C++ as backend as optimisation for hard 3x3 puzzle or bigger puzzle size.
An Cython interface is used for the C++ to Python communication. 

## Compile

Due to Cython and C++, the project need to be compile.

    cd srcs/srcs_cython

This command compile Cython and C++ and create a shared library (.so) used by Python.
 
    python3 setup.py build_ext --inplace

## Launch

In project root, default command create a pseudo-random-resolvable-puzzle then resolve it by launching this command:
    
    python3 srcs/main.py

Then options are available:
- Parsing puzzle from file (*-p -f FILE*) or generate one (*-g*)
- Heuristic function choices (*-md / -dd / -ed*)
- Linear conflict (*-lc*) (double cost of move if the number order is inversed from gola position)
- C++ code optimisation (*-cp*) (use A* search with manhanttan distance and linear conflict)
