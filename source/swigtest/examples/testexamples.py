# This example illustrates how multiple C++ plugins can be used from Python.

import example.examples as M

a = M.Simple("")
assert(not a.valid())

a = M.Plugins(M.clsidManager)
if a.valid():
    print("plugin count: %d" % a.getPluginCount())
    files = M.Strings()
    a.getPluginFiles(files)
    for i,f in enumerate(files): print(" %d. %s" % (i+1,f))

a = M.Simple(M.clsidSimple)
if a.valid():
    print("Simple.add(1, 2) = %d" % a.add(1, 2))

b = M.Simple2(a.p())
if b.valid():
    print("Simple2(Simple.p()): ok")
    print("Simple2.add([1, 2, 3, 4]) = %d" % b.add([1, 2, 3, 4]))
    print("Simple2.add((2, 3, 4)) = %d" % b.add((2, 3, 4)))

a = M.AnyObject(b.p())
if a.valid(): print("AnyObject(obj.p()): ok")

c = M.Simple3(a.p())
if c.valid():
    print("Simple3(AnyObject.p()): ok")
    obj = c.createSimple()
    d = M.Simple(obj.p())
    print("Simple(AnyObject Simple3.createSimple()): ok")
    print("Simple.subtract(2, 1) = %d" % d.subtract(2, 1))

print("Goodbye")
