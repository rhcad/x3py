#ifndef X3_EXAMPLE_ISIMPLE_H
#define X3_EXAMPLE_ISIMPLE_H

#include <objptr.h>

const char* const clsidSimple = "94071767-ba6b-4769-9eb4-2ebf469289f3";

class ISimpleWnd : public x3::IObject
{
    X3DEFINE_IID(ISimpleWnd);
    virtual bool createWnd(size_t hparent, int id) = 0;
    virtual size_t getHandle() const = 0;
    virtual void showMessage() = 0;
};

#endif