// x3py framework: https://github.com/rhcad/x3py
#if !defined(X3_NONPLUGIN_USE_PLUGIN_H) && !defined(X3_NONPLUGIN_USE_PLUGINS_H)
#define X3_NONPLUGIN_USE_PLUGIN_H

#include <utilfunc/loadmodule.h>

// PLUGIN_PATH:         the plugin's relative folder.
// PLUGIN_NAME:         the plugin name, no extension and path.
// SELF_MODULE_NAME:    file name of the caller.

#ifdef PLUGIN_NAME

#ifndef SELF_MODULE_NAME
    #ifdef SWIGPYTHON
        #define SELF_PRE "_"
    #else
        #define SELF_PRE ""
    #endif
    #if defined(SWIGPYTHON) && defined(_WIN32)
        #define SELF_EXT ".pyd"
    #elif defined(_WIN32)
        #define SELF_EXT ".dll"
    #else
        #define SELF_EXT ".so"
    #endif
    #ifdef SELF_MODULE
        #define SELF_MODULE_NAME  SELF_PRE SELF_MODULE SELF_EXT
    #else
        #define SELF_MODULE_NAME  SELF_PRE PLUGIN_NAME SELF_EXT
    #endif
#endif // SELF_MODULE_NAME

#ifndef PLUGIN_PATH
#ifdef SWIGPYTHON
#define CURMOD_IN_CWDSUBDIR
#define PLUGIN_PATH "../../plugins/"
#elif defined(SWIGINLINE)
#define PLUGIN_PATH "../plugins/"
#else
#define PLUGIN_PATH ""
#endif
#endif // PLUGIN_PATH

#ifdef X3_CORE_PORTABILITY_H
#include "../portability/portimpl.h"
#endif

namespace x3 {

static LoadModuleHelper loader(PLUGIN_PATH PLUGIN_NAME ".pln", 
                               GetModuleHandleA(SELF_MODULE_NAME));

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

} // x3
#endif // PLUGIN_NAME
#endif
