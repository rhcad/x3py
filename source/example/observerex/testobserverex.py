import example.observerex as ex

class PyObserver(ex.ObserverDemo):
	def __init__(self):
		ex.ObserverDemo.__init__(self)
	def demo(self):
	    print(" PyObserver.demo() called.")

print("Adding and calling a normal C++ observer")

observer = ex.ObserverDemo()
print(" Result of fireEvent(): %d" % ex.ObserverDemo.fireEvent())

print("Adding and calling a Python observer")

observer2 = PyObserver()
print(" Result of fireEvent(): %d" % ex.ObserverDemo.fireEvent())

print("Delete a observer")
observer = observer2
print(" Result of fireEvent(): %d" % ex.ObserverDemo.fireEvent())

print("python exit")
