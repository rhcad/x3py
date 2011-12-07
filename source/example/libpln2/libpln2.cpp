#include <module/plugininc.h>
#include "libpln2.h"

CSimpleB::CSimpleB()
{
}

CSimpleB::~CSimpleB()
{
}

int CSimpleB::add(const std::vector<int>& nums) const
{
    int ret = 10;

    for (std::vector<int>::const_iterator it = nums.begin();
        it != nums.end(); ++it)
    {
        ret += *it;
    }

    return ret;
}
