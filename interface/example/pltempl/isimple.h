#ifndef X3_EXAMPLE_ISIMPLE_H
#define X3_EXAMPLE_ISIMPLE_H

#include <objptr.h>

const char* const clsidSimple = "78d30c77-e0f0-48a3-a489-dd4327759c27";

class ISimple : public x3::IObject
{
    X3DEFINE_IID(ISimple);
    virtual int add(int a, int b) const = 0;
    virtual int subtract(int a, int b) const = 0;
};

#endif