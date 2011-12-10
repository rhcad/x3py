#ifndef X3_EXAMPLE_ISIMPLE2_H
#define X3_EXAMPLE_ISIMPLE2_H

#include <objptr.h>
#include <vector>

class ISimple2 : public x3::IObject
{
    X3DEFINE_IID(ISimple2);
    virtual int add(const std::vector<int>& nums) const = 0;
};

#endif