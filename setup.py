import sys
from distutils.core import setup
from Cython.Build import cythonize

mypyx_index = sys.argv.index("--mypyx")
pyxfile = sys.argv[mypyx_index + 1]
sys.argv[mypyx_index:mypyx_index + 2] = []

assert pyxfile.endswith(".pyx")

setup(
    name="Cython OpenEdu Solution",
    ext_modules=cythonize(pyxfile),
)