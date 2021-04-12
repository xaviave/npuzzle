# Cython compile instructions
import os

from distutils.core import setup
from Cython.Build import cythonize

# Use python setup.py build --inplace
# to compile

cython_files = [f for f in os.listdir(".") if os.path.isfile(f)]

setup(
  name = "npuzzlehandler",
  ext_modules = cythonize(cython_files),
)