# Cython compile instructions

import os
import numpy

from Cython.Build import cythonize
from setuptools import Extension, setup


os.environ["CFLAGS"] = f"-I{numpy.get_include()}"

cpp_sources_path = "../srcs_cpp/srcs/"
cpp_includes_path = "../srcs_cpp/includes/"

cpp_sources = [
    os.path.abspath(os.path.join(cpp_sources_path, f))
    for f in os.listdir("../srcs_cpp/srcs/")
]
cpp_includes = [
    os.path.abspath(os.path.join(cpp_includes_path, f))
    for f in os.listdir("../srcs_cpp/includes/")
]

setup(
    ext_modules=cythonize(
        Extension(
            "cpp_wrapper",
            includes_path=cpp_includes,
            sources=["cpp_srcs_wrapper.pyx", *cpp_sources],
            language="c++",
            extra_compile_args=["-std=c++2a", "-O3"],
        ),
        language_level="3",
    )
)

print("********| CYTHON COMPLETE |******")
