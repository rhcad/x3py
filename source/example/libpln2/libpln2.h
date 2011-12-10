#ifndef X3_EXAMPLE_SIMPLE_IMPL_H
#define X3_EXAMPLE_SIMPLE_IMPL_H

#include <module/classmacro.h>
#include <plsimple/isimple2.h>

const char* const clsidSimpleB = "73458821-16d7-4671-959d-c17b43c9e6de";

class CSimpleB : public ISimple2
{
    X3BEGIN_CLASS_DECLARE(CSimpleB, clsidSimpleB)
        X3DEFINE_INTERFACE_ENTRY(ISimple2)
    X3END_CLASS_DECLARE()
protected:
    CSimpleB();
    virtual ~CSimpleB();

private:
    virtual int add(const std::vector<int>& nums) const;
};

#endif