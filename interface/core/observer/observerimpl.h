// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_OBSERVERIMPL_H
#define X3_CORE_OBSERVERIMPL_H

#include <observer/observerobject.h>

#ifndef X3_CORE_PLUGINIMPL_H
#define x3InternalCreate createObject
#endif

namespace x3 {

bool registerObserver(const char* type, PROC handler)
{
    typedef bool (*CF)(const char*, long, IObject**);
    typedef bool (*F)(const char*, PROC, CF);
    F f = (F)GetProcAddress(getManagerModule(), "x3RegisterObserver");
    return f && f(type, handler, x3InternalCreate);
}

bool registerObserver(const char* type, x3::ObserverObject* obj, x3::ON_EVENT handler)
{
    typedef bool (*CF)(const char*, long, IObject**);
    typedef bool (*F)(const char*, x3::ObserverObject*, x3::ON_EVENT, CF);
    F f = (F)GetProcAddress(getManagerModule(), "x3RegisterObserverObject");
    return f && f(type, obj, handler, x3InternalCreate);
}

void unregisterObserver(x3::ObserverObject* obj)
{
    typedef void (*F)(x3::ObserverObject*);
    F f = (F)GetProcAddress(getManagerModule(), "x3UnregisterObserverObject");
    if (f) f(obj);
}

int fireEvent(const char* type, PROC dispatcher, void* data, bool obj)
{
    typedef int (*F)(const char*, PROC, void*);
    F f = (F)GetProcAddress(getManagerModule(), obj ? "x3FireObjectEvent" : "x3FireEvent");
    return f ? f(type, dispatcher, data) : 0;
}

} // x3
#endif