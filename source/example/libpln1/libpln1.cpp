#include <module/plugininc.h>
#include "libpln1.h"

CSimpleA::CSimpleA()
{
}

CSimpleA::~CSimpleA()
{
}

int CSimpleA::add(int a, int b) const
{
    return 10 + a + b;
}

int CSimpleA::subtract(int a, int b) const
{
    return 10 - a - b;
}
