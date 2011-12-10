#ifndef X3_EXAMPLE_SIMPLE_IMPL_H
#define X3_EXAMPLE_SIMPLE_IMPL_H

#include <module/classmacro.h>
#include <plsimple/isimple.h>

class CSimpleA : public ISimple
{
    X3BEGIN_CLASS_DECLARE(CSimpleA, clsidSimple)
        X3DEFINE_INTERFACE_ENTRY(ISimple)
    X3END_CLASS_DECLARE()
protected:
    CSimpleA();
    virtual ~CSimpleA();

private:
    virtual int add(int a, int b) const;
    virtual int subtract(int a, int b) const;
};

#endif