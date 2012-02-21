# This example illustrates how C++ interfaces can be used from Python.

from example import pltempl

a = pltempl.Simple("")
if a.valid():
    print("add(1, 2) = %d" % a.add(1, 2))
