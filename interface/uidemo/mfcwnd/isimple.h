#ifndef X3_EXAMPLE_ISIMPLE_H
#define X3_EXAMPLE_ISIMPLE_H

#include <objptr.h>

const char* const clsidSimple = "feefc399-29f2-4354-8eeb-048d4cf56567";

class ISimpleWnd : public x3::IObject
{
    X3DEFINE_IID(ISimpleWnd);
    virtual bool createWnd(size_t hparent, int id) = 0;
    virtual size_t getHandle() const = 0;
    virtual void showMessage() = 0;
};

#endif