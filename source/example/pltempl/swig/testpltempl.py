# This example illustrates how C++ interfaces can be used from Python.

from pltempl import *

a = Simple("")
if a.valid():
    print("add(1, 2) = %d" % a.add(1, 2))
