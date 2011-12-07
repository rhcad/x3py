#include <module/plugininc.h>
#include <module/pluginimpl.h>
#include <module/modulemacro.h>

#include "plsimple.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY(CSimple)
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    return true;
}

OUTAPI void x3UninitializePlugin()
{
}
