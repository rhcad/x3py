#ifndef X3_EXAMPLE_SIMPLE_IMPL_H
#define X3_EXAMPLE_SIMPLE_IMPL_H

#include <module/classmacro.h>
#include <plsimple/isimple.h>
#include <plsimple/isimple2.h>
#include <plsimple/isimple3.h>

class CSimple
    : public ISimple
    , public ISimple2
    , public ISimple3
{
    X3BEGIN_CLASS_DECLARE(CSimple, clsidSimple)
        X3DEFINE_INTERFACE_ENTRY(ISimple)
        X3DEFINE_INTERFACE_ENTRY(ISimple2)
        X3DEFINE_INTERFACE_ENTRY(ISimple3)
    X3END_CLASS_DECLARE()
protected:
    CSimple();
    virtual ~CSimple();

private:
    virtual int add(int a, int b) const;
    virtual int subtract(int a, int b) const;

    virtual int add(const std::vector<int>& nums) const;

    virtual x3::AnyObject createSimple();
};

#endif