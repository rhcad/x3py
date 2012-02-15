// x3py framework: https://github.com/rhcad/x3py
#if !defined(X3_NONPLUGIN_USE_PLUGIN_H) && !defined(X3_NONPLUGIN_USE_PLUGINS_H)
#define X3_NONPLUGIN_USE_PLUGIN_H

#include <utilfunc/loadmodule.h>
#include "swigext.h"

// PLUGIN_PATH:         the internal plugin (*.pln) 's relative folder.
// PLUGIN_NAME:         the internal plugin name, no extension and path.
// SELF_MODULE_NAME:    file name of the caller module which will load the internal plugin.
// SELF_MODULE:         defined when the caller name hasn't PLUGIN_NAME.

#ifdef PLUGIN_NAME

#ifndef SELF_MODULE_NAME
#ifndef SELF_MODULE
#define SELF_MODULE_NAME  SELF_PRE PLUGIN_NAME SELF_EXT
#else
#define SELF_MODULE_NAME  SELF_PRE SELF_MODULE SELF_EXT
#endif
#endif // SELF_MODULE_NAME

#if defined(X3_CORE_PORTABILITY_H) && !defined(X3_EXCLUDE_CREATEOBJECT)
#include "../portability/portimpl.h"
#endif

namespace x3 {

static LoadModuleHelper loader(PLUGIN_PATH PLUGIN_NAME ".pln", 
                               GetModuleHandleA(SELF_MODULE_NAME));

#if !defined(X3_EXCLUDE_CREATEOBJECT) && !defined(CREATEOBJECTIMPL)
#define CREATEOBJECTIMPL

HMODULE getManagerModule()
{
    return loader.getModule();
}

class IObject;
bool createObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = (F)loader.getFunc("x3CreateObject");
    return f && f(clsid, iid, p);
}
#endif // CREATEOBJECTIMPL

} // x3
#endif // PLUGIN_NAME
#endif
