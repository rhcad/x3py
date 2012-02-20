%module x3manager
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "x3manager"
#endif
%}
%include <swig/plugin.i>

%{
#include <manager/iplugins.h>
%}

%include std_vector.i
%include std_string.i
%template(Strings) std::vector<std::string>;

%include <manager/iplugins.h>
%template(Plugins) x3::Object<x3::IPlugins>;

%include <manager/x3manager.h>

%{
#ifndef PLUGIN_SWIG

namespace x3 {

class ObserverObject;
typedef void (ObserverObject::*ON_EVENT)();
typedef bool (*EventDispatcher)(PROC handler, void* data);
typedef bool (*ObjectEventDispatcher)(ObserverObject*, ON_EVENT, void* data);
typedef bool (*Creator)(const char*, long, IObject**);

OUTAPI bool x3RegisterPlugin(Creator creator, HMODULE hmod, const char** clsids)
{
    typedef bool (*F)(Creator, HMODULE, const char**);
    F f = (F)GetProcAddress(getManagerModule(), "x3RegisterPlugin");
    return f && f(creator, hmod, clsids);
}

OUTAPI bool x3UnregisterPlugin(Creator creator)
{
    typedef bool (*F)(Creator);
    F f = (F)GetProcAddress(getManagerModule(), "x3UnregisterPlugin");
    return f && f(creator);
}

OUTAPI bool x3CreateObject(const char* clsid, long iid, IObject** p)
{
    typedef bool (*F)(const char*, long, IObject**);
    F f = (F)GetProcAddress(getManagerModule(), "x3CreateObject");
    return f && f(clsid, iid, p);
}

OUTAPI bool x3RegisterObserver(const char* type, PROC handler, Creator creator)
{
    typedef bool (*F)(const char*, PROC, Creator);
    F f = (F)GetProcAddress(getManagerModule(), "x3RegisterObserver");
    return f && f(type, handler, creator);
}

OUTAPI bool x3RegisterObserverObject(const char* type, ObserverObject* obj, 
                                     ON_EVENT handler, Creator creator)
{
    typedef bool (*F)(const char*, ObserverObject*, ON_EVENT, Creator);
    F f = (F)GetProcAddress(getManagerModule(), "x3RegisterObserverObject");
    return f && f(type, obj, handler, creator);
}

OUTAPI void x3UnregisterObserverObject(ObserverObject* obj)
{
    typedef void (*F)(ObserverObject*);
    F f = (F)GetProcAddress(getManagerModule(), "x3UnregisterObserverObject");
    if (f) f(obj);
}

OUTAPI int x3FireEvent(const char* type, EventDispatcher dispatcher, void* data)
{
    typedef bool (*F)(const char*, EventDispatcher, void*);
    F f = (F)GetProcAddress(getManagerModule(), "x3FireEvent");
    return f ? f(type, dispatcher, data) : 0;
}

OUTAPI int x3FireObjectEvent(const char* type, ObjectEventDispatcher dispatcher, void* data)
{
    typedef bool (*F)(const char*, ObjectEventDispatcher, void*);
    F f = (F)GetProcAddress(getManagerModule(), "x3FireObjectEvent");
    return f ? f(type, dispatcher, data) : 0;
}

OUTAPI int x3LoadPlugins(const char* folder)
{
    typedef int (*F)(const char*);
    F f = (F)GetProcAddress(getManagerModule(), "x3LoadPlugins");
    return f ? f(folder) : 0;
}

OUTAPI int x3UnloadPlugins()
{
    typedef int (*F)();
    F f = (F)GetProcAddress(getManagerModule(), "x3UnloadPlugins");
    return f ? f() : 0;
}

#ifndef _WIN32
OUTAPI HMODULE unixFindModule(const char* filename)
{
    typedef HMODULE (*F)(const char*);
    F f = (F)GetProcAddress(getManagerModule(), "unixFindModule");
    return f ? f(filename) : NULL;
}
#endif // UNIX

} // x3
#endif // PLUGIN_SWIG
%}
