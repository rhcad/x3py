#include <module/plugininc.h>
#include "plsimple.h"

CSimple::CSimple()
{
}

CSimple::~CSimple()
{
}

int CSimple::add(int a, int b) const
{
    return a + b;
}

int CSimple::subtract(int a, int b) const
{
    return a - b;
}

int CSimple::add(const std::vector<int>& nums) const
{
    int ret = 0;

    for (std::vector<int>::const_iterator it = nums.begin();
        it != nums.end(); ++it)
    {
        ret += *it;
    }

    return ret;
}

x3::AnyObject CSimple::createSimple()
{
    return x3::Object<ISimple>(clsidSimple);
}
