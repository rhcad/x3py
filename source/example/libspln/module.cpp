#include <module/plugininc.h>
#include <module/pluginimpl.h>
#define XUSE_LIB_PLUGIN
#include <module/modulemacro.h>

#include "libspln.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY(CSimple3)
XEND_DEFINE_MODULE_DLL()

#ifdef _MSC_VER
#pragma comment(lib, "libpln1.lib")
#pragma comment(lib, "libpln2.lib")
#endif

extern const x3::ClassEntry* const classes_libpln1;
extern const x3::ClassEntry* const classes_libpln2;

const x3::ClassEntry* const x3::ClassEntry::classes[] = {
        s_classes, classes_libpln1, classes_libpln2, NULL
    };

OUTAPI bool x3InitializePlugin()
{
    return true;
}

OUTAPI void x3UninitializePlugin()
{
}
