// 1: use multiple plugins, 2: use one plugin
// 3: raw loading mode, 4: use static library plugin
//
#ifndef LOADMODE
#define LOADMODE  3
#endif

int test();

//---------------------------------------------------------------
#if   LOADMODE==1   // use multiple plugins: plugins/*.pln
//---------------------------------------------------------------

#include <portability/x3port.h>
#define PLUGIN_PATH  "plugins"
#include <nonplugin/useplugins.h>

static const char* plugins[] = { 
    "x3manager.pln", "plsimple.pln", "observerex.pln", 
    NULL };
static x3::AutoLoadPlugins autoload(plugins);

int main()
{
    return test();
}

//---------------------------------------------------------------
#elif LOADMODE==2   // use only one plugin: plugins/plsimple.pln
//---------------------------------------------------------------

#include <portability/x3port.h>
#define PLUGIN_PATH  "plugins/"
#define PLUGIN_NAME  "plsimple"
#include <nonplugin/useplugin.h>

int main()
{
    return test();
}

//---------------------------------------------------------------
#elif LOADMODE==3   // raw loading mode
//---------------------------------------------------------------

#include <portability/portimpl.h>

HMODULE modules[10] = { NULL };

int main()
{
    const char* plugins[] = { 
        "plugins/x3manager.pln", 
        "plugins/plsimple.pln", 
        "plugins/observerex.pln" };
    int count = sizeof(plugins) / sizeof(plugins[0]);

    for (int i = 0; i < count; i++)
    {
        modules[i] = x3LoadLibrary(plugins[i]);
    }

    int ret = test();

    while (--count >= 0)
    {
        x3FreeLibrary(modules[count]);
    }

    return ret;
}

namespace x3 {
class IObject;
bool createObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = (F)GetProcAddress(modules[0], "x3CreateObject");
    return f && f(clsid, iid, p);
}
} // x3

//---------------------------------------------------------------
#elif LOADMODE==4   // use static library plugin
//---------------------------------------------------------------

#include <portability/portimpl.h>
#include <module/pluginimpl.h>
#define XUSE_LIB_PLUGIN
#include <module/modulemacro.h>
XDEFINE_EMPTY_MODULE()

#ifdef _MSC_VER
#pragma comment(lib, "libpln1.lib")
#endif

extern const x3::ClassEntry* const classes_libpln1;

const x3::ClassEntry* const x3::ClassEntry::classes[] = {
        s_classes, classes_libpln1, NULL
    };

int main()
{
    return test();
}

//---------------------------------------------------------------
#endif

#include <example/isimple.h>

int test()
{
    x3::Object<ISimple> p(clsidSimple);

    if (!p)
        return 1;   // plugin not loaded

    if (p->add(1, 2) != 3)
        return 2;   // diffrent implement

    return 9;       // test ok
}
