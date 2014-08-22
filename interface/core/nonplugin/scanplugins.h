// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_NONPLUGIN_SCANPLUGINS_H
#define X3_NONPLUGIN_SCANPLUGINS_H

#include <utilfunc/scanfiles.h>
#include <utilfunc/loadmodule.h>

#if defined(X3_CORE_PORTABILITY_H) && !defined(X3_EXCLUDE_CREATEOBJECT)
#include <portability/portimpl.h>
#endif

#ifndef PLUGINS_MAXCOUNT
#define PLUGINS_MAXCOUNT 40
#endif

namespace x3 {

static HMODULE  s_modules[PLUGINS_MAXCOUNT] = { NULL };
static int      s_nmods = 0;

static bool loadfilter(const char* filename, const char* ext)
{
    if (_stricmp(ext, ".pln") == 0
        && GetModuleHandleA(PathFindFileNameA(filename)) == NULL)
    {
        s_modules[s_nmods] = x3LoadLibrary(filename);
        if (s_modules[s_nmods])
            s_nmods++;
    }
    return s_nmods < PLUGINS_MAXCOUNT;
}

int loadScanPlugins(const char* folder = "plugins")
{
    char path[MAX_PATH];

    GetModuleFileNameA(NULL, path, MAX_PATH);
    PathRemoveFileSpecA(path);
    PathAppendA(path, folder);

    // Load x3manager before others, so others can find it in x3InitPlugin().
    if (!GetModuleHandleA("x3manager.pln"))
    {
        PathAppendA(path, "x3manager.pln");
        loadfilter(path, ".pln");
        PathRemoveFileSpecA(path);
    }

    typedef int (*LOADF)(const char*);
    LOADF fload = (LOADF)GetProcAddress(GetModuleHandleA("x3manager.pln"), "x3LoadPlugins");
    int extcount = fload ? fload(folder) : 0;
    
    if (!fload) // load plugins regardless the x3manager plugin.
        x3::scanfiles(loadfilter, path, true);

    return s_nmods + extcount;
}

void unloadScanPlugins()
{
    typedef int (*UF)();
    UF uf = (UF)GetProcAddress(GetModuleHandleA("x3manager.pln"), "x3UnloadPlugins");
    if (uf) uf();

    while (s_nmods > 0)
    {
        x3FreeLibrary(s_modules[--s_nmods]);
    }
}

#if !defined(X3_EXCLUDE_CREATEOBJECT) && !defined(CREATEOBJECTIMPL)
#define CREATEOBJECTIMPL

class IObject;
LOCALAPI bool createObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = (F)GetProcAddress(s_modules[0], "x3CreateObject");
    return f && f(clsid, iid, p);
}
HMODULE getManagerModule() { return s_modules[0]; }
#endif // CREATEOBJECTIMPL

} // x3
#endif