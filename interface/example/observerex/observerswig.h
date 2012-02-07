// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_EXAMPLE_OBSERVEREX_SWIG_H
#define X3_EXAMPLE_OBSERVEREX_SWIG_H

#include <observerex/myevents.h>

class ObserverDemo : public x3::ObserverObject
{
public:
    ObserverDemo() {
        X3_REGISTER_OBSERVER_OBJECT(EventSwigVoid, &ObserverDemo::demo);
    }
    ~ObserverDemo() {
        x3::unregisterObserver(this);
    }
    static int fireEvent() {
        return FireEventSwigVoid().fireEvent().nhandled;
    }

protected:
    virtual void demo() {}
};

#endif