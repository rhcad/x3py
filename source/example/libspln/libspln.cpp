#include <module/plugininc.h>
#include "libspln.h"
#include <plsimple/isimple.h>

x3::AnyObject CSimple3::createSimple()
{
    return x3::Object<ISimple>(clsidSimple);
}
