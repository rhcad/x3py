#include <module/plugininc.h>
#include "pltempl.h"

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
