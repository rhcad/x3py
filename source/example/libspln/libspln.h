#ifndef X3_EXAMPLE_SIMPLE_IMPL_H
#define X3_EXAMPLE_SIMPLE_IMPL_H

#include <module/classmacro.h>
#include <plsimple/isimple3.h>

class CSimple3 : public ISimple3
{
    X3BEGIN_CLASS_DECLARE(CSimple3, clsidSimple3)
        X3DEFINE_INTERFACE_ENTRY(ISimple3)
    X3END_CLASS_DECLARE()
protected:
    CSimple3() {}

private:
    virtual x3::AnyObject createSimple();
};

#endif