#ifndef X3_NONPLUGIN_USE_PLUGINS_H
#define X3_NONPLUGIN_USE_PLUGINS_H

#include <objptr.h>
#include <utilfunc/loadmodule.h>

#ifdef X3_CORE_PORTABILITY_H
#include "../portability/portimpl.h"
#endif

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
#define PLUGIN_PATH ""
#endif

BEGIN_NAMESPACE_X3

static LoadModuleHelper* s_plugins[10] = { NULL };
static int s_nplugin = 0;

bool createObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = !s_plugins[0] ? NULL : (F)s_plugins[0]->getFunc("x3CreateObject");
    return f && f(clsid, iid, p);
}

void loadPlugins(const char* const* plugins)
{
    HMODULE basemod = GetModuleHandleA(SELF_MODULE_NAME);
    for (int i = 0; s_nplugin < 10 - 1 && plugins[i]; ++i, ++s_nplugin)
    {
        s_plugins[s_nplugin] = new LoadModuleHelper();
        s_plugins[s_nplugin]->load(plugins[i], basemod, PLUGIN_PATH);
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
    AutoLoadPlugins(const char* const* plugins) { loadPlugins(plugins); }
    ~AutoLoadPlugins() { unloadPlugins(); }
};

END_NAMESPACE_X3
#endif