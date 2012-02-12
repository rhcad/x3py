// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_NONPLUGIN_USE_PLUGINS_H
#define X3_NONPLUGIN_USE_PLUGINS_H

#include <utilfunc/loadmodule.h>

// PLUGIN_PATH:         plugins's relative folder.
// SELF_MODULE_NAME:    file name of the caller.
// SELF_MODULE:         used to make SELF_MODULE_NAME.

#ifndef SELF_MODULE_NAME
    #ifndef SELF_MODULE
        #define SELF_MODULE_NAME  NULL
    #else
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
        #define SELF_MODULE_NAME  SELF_PRE SELF_MODULE SELF_EXT
    #endif
#endif // SELF_MODULE_NAME

#ifndef PLUGIN_PATH
#ifdef SWIGPYTHON
#define PLUGIN_PATH "../../plugins/"
#define CURMOD_IN_CWDSUBDIR
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

static LoadModuleHelper* s_plugins[10] = { NULL };
static int s_nplugin = 0;

HMODULE getManagerModule()
{
    return s_plugins[0] ? s_plugins[0]->getModule() : NULL;
}

#ifndef CREATEOBJECTIMPL
#define CREATEOBJECTIMPL
class IObject;
bool createObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = !s_plugins[0] ? NULL : (F)s_plugins[0]->getFunc("x3CreateObject");
    return f && f(clsid, iid, p);
}
#endif

void loadPlugins(const char* const* plugins, const char* folder = PLUGIN_PATH)
{
    HMODULE basemod = GetModuleHandleA(SELF_MODULE_NAME);
    for (int i = 0; s_nplugin < 10 - 1 && plugins[i]; ++i, ++s_nplugin)
    {
        s_plugins[s_nplugin] = new LoadModuleHelper();
        s_plugins[s_nplugin]->load(plugins[i], basemod, folder);
    }
}

void unloadPlugins()
{
    for (int i = s_nplugin - 1; i >= 0; i--)
    {
        delete s_plugins[i];
        s_plugins[i] = NULL;
    }
    s_nplugin = 0;
}

/** \code
 * static const char* PLUGINS[] = { "x3manager.pln", "myplugin.pln", NULL };
 * static x3::AutoLoadPlugins autoload(PLUGINS);
 * \endcode
 */
struct AutoLoadPlugins
{
    AutoLoadPlugins(const char* const* plugins, const char* folder = PLUGIN_PATH)
    {
        loadPlugins(plugins, folder);
    }
    ~AutoLoadPlugins()
    {
        unloadPlugins();
    }
};

} // x3
#endif
