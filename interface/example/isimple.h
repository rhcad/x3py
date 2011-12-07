#ifndef X3_EXAMPLE_ISIMPLE_H
#define X3_EXAMPLE_ISIMPLE_H

#include <objptr.h>

const char* const clsidSimple = "94071767-ba6b-4769-9eb4-2ebf469289f3";

class ISimple : public x3::IObject
{
    X3DEFINE_IID(ISimple);
    virtual int add(int a, int b) const = 0;
    virtual int subtract(int a, int b) const = 0;
};

#endif