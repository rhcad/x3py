# This example illustrates how C++ interfaces can be used from Python.

from example.plsimple import *

a = Simple("")
if a.valid():
    print("add(1, 2) = %d" % a.add(1, 2))
else:
    print("Fail to create the wrapper object.")

b = Simple2(a.p())
if b.valid():
    print("Simple2(Simple.p()): ok")
    print("add([1, 2, 3, 4]) = %d" % b.add([1, 2, 3, 4]))
    print("add((2, 3, 4)) = %d" % b.add((2, 3, 4)))

a = AnyObject(b.p())
if a.valid(): print("AnyObject(obj.p()): ok")

c = Simple3(a.p())
if c.valid():
    print("Simple3(AnyObject.p()): ok")
    obj = c.createSimple()
    d = Simple(obj.p())
    print("Simple(AnyObject createSimple()): ok")
    print("subtract(2, 1) = %d" % d.subtract(2, 1))
