# This example illustrates how multiple C++ plugins can be used from Python.

from core.x3manager import *
import example.plsimple as A
import example.observerex as B

a = Plugins("")
if not a.valid(): print("The x3manager plugins is not loaded.")

print("plugin count: %d" % a.getPluginCount())

files = Strings()
a.getPluginFiles(files)
for i,f in enumerate(files): print(" %d. %s" % (i+1,f))

print("x3manager.Plugins: %s of %s" % (a.getInterfaceName(), a.getClassName()))

b = A.Simple(A.clsidSimple)
print("Simple(clsidSimple) ok." if b.valid() else "Simple(clsidSimple) fail.")
if b.valid():
    print("Simple(clsidSimple) ok.")
    print("clsidSimple: %s of %s" % (a.getInterfaceName(), a.getClassName()))

c = AnyObject(b.p())
if c.valid():
    print("AnyObject(anotherobj.p()) ok.")
    print("AnyObject: iid=%d, clsid=%s" % (c.getIID(), c.getClassID()))

print("---loadExtraPlugins---")
p = Plugins("")
print("plugins loaded: %d" % p.loadExtraPlugins("plugins"))
print("plugin count: %d" % p.getPluginCount())
p.getPluginFiles(files)
for i,f in enumerate(files): print(" %d. %s" % (i+1,f))
print("plugins unloaded: %d" % p.unloadExtraPlugins())
#print(list(files))
