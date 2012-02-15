#ifndef X3_EXAMPLE_SIMPLE_IMPL_H
#define X3_EXAMPLE_SIMPLE_IMPL_H

#include <module/classmacro.h>
#include <pltempl/isimple.h>

class CSimple : public ISimple
{
    X3BEGIN_CLASS_DECLARE(CSimple, clsidSimple)
        X3DEFINE_INTERFACE_ENTRY(ISimple)
    X3END_CLASS_DECLARE()
protected:
    CSimple();
    virtual ~CSimple();

private:
    virtual int add(int a, int b) const;
    virtual int subtract(int a, int b) const;
};

#endif