#ifndef X3_EXAMPLE_ISIMPLE_H
#define X3_EXAMPLE_ISIMPLE_H

#include <objptr.h>

const char* const clsidSimple = "78d30c77-e0f0-48a3-a489-dd4327759c27";

class ISimple : public x3::IObject
{
    X3DEFINE_IID(ISimple);
    virtual bool createWnd(size_t hparent, int id) = 0;
    virtual size_t getHandle() const = 0;
    virtual void showMessage() = 0;
};

#endif