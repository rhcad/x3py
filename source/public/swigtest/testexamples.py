# This example illustrates how multiple C++ plugins can be used from Python.

from examples import *

a = Simple("")
assert(not a.valid())

a = Plugins(clsidManager)
print("plugin count: %d" % a.getPluginCount())
files = Strings()
a.getPluginFiles(files)
for i,f in enumerate(files): print(" %d. %s" % (i+1,f))

a = Simple(clsidSimple)
if a.valid():
    print("Simple.add(1, 2) = %d" % a.add(1, 2))

b = Simple2(a.p())
if b.valid():
    print("Simple2(Simple.p()): ok")
    print("Simple2.add([1, 2, 3, 4]) = %d" % b.add([1, 2, 3, 4]))
    print("Simple2.add((2, 3, 4)) = %d" % b.add((2, 3, 4)))

a = AnyObject(b.p())
if a.valid(): print("AnyObject(obj.p()): ok")

c = Simple3(a.p())
if c.valid():
    print("Simple3(AnyObject.p()): ok")
    obj = c.createSimple()
    d = Simple(obj.p())
    print("Simple(AnyObject Simple3.createSimple()): ok")
    print("Simple.subtract(2, 1) = %d" % d.subtract(2, 1))
