#ifndef X3_NONPLUGIN_SCANPLUGINS_H
#define X3_NONPLUGIN_SCANPLUGINS_H

#include <portability/x3port.h>
#include <utilfunc/scanfiles.h>
#include <objptr.h>

#ifndef X3_EXCLUDE_CREATEOBJECT
#include <portability/portimpl.h>
#endif

#ifndef PLUGINS_MAXCOUNT
#define PLUGINS_MAXCOUNT 20
#endif

BEGIN_NAMESPACE_X3

static HMODULE  s_modules[PLUGINS_MAXCOUNT] = { NULL };
static int      s_nplugin = 0;

static bool loadfilter(const char* filename, const char* ext)
{
    if (_stricmp(ext, ".pln") == 0)
    {
        s_modules[s_nplugin] = x3LoadLibrary(filename);
        if (s_modules[s_nplugin])
            s_nplugin++;
    }
    return s_nplugin < PLUGINS_MAXCOUNT;
}

int loadPlugins(const char* folder = "plugins")
{
    char path[MAX_PATH];

    GetModuleFileNameA(NULL, path, MAX_PATH);
    PathRemoveFileSpecA(path);
    PathAppendA(path, folder);

    x3::scanfiles(loadfilter, path, true);
    return s_nplugin;
}

void unloadPlugins()
{
    while (s_nplugin > 0)
    {
        x3FreeLibrary(s_modules[--s_nplugin]);
    }
}

HMODULE getManagerModule()
{
    return s_modules[0];
}

#ifndef X3_EXCLUDE_CREATEOBJECT
bool createObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = (F)GetProcAddress(s_modules[0], "x3CreateObject");
    return f && f(clsid, iid, p);
}
#endif

END_NAMESPACE_X3
#endif