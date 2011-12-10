#ifndef X3_EXAMPLE_ISIMPLE3_H
#define X3_EXAMPLE_ISIMPLE3_H

#include <objptr.h>

const char* const clsidSimple3 = "94071767-ba6b-4769-9eb4-2ebf469218f3";

class ISimple3 : public x3::IObject
{
    X3DEFINE_IID(ISimple3);

    virtual x3::AnyObject createSimple() = 0;
};

#endif