#include <module/plugininc.h>
#include <module/pluginimpl.h>
#include <module/modulemacro.h>
#include <observer/observerimpl.h>

#include "observerex.h"

XBEGIN_DEFINE_MODULE()
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    if (!test())
        return false;
    return true;
}

OUTAPI void x3UninitializePlugin()
{
}
