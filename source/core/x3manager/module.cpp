#include <module/plugininc.h>
#include <module/modulemacro.h>
#define X3_EXCLUDE_CREATEOBJECT
#include <module/pluginimpl.h>

#include "plugins.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(x3::CPlugins)
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    return true;
}

OUTAPI void x3UninitializePlugin()
{
}

OUTAPI bool x3RegisterPlugin(x3::Creator creator, HMODULE hmod, const char** clsids)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return reg && reg->registerPlugin(creator, hmod, clsids);
}

OUTAPI void x3UnregisterPlugin(x3::Creator creator)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    if (reg && creator)
        reg->unregisterPlugin(creator);
}

OUTAPI bool x3CreateObject(const char* clsid, long iid, x3::IObject** p)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return x3InternalCreate(clsid, iid, p)
        || reg && reg->createFromOthers(clsid, iid, p);
}

OUTAPI bool x3RegisterObserver(const char* type, PROC handler, x3::Creator creator)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return reg && reg->registerObserver(type, handler, creator);
}

OUTAPI bool x3RegisterObserverObject(const char* type, x3::ObserverObject* obj, 
                                     x3::ON_EVENT handler, x3::Creator creator)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return reg && reg->registerObserver(type, obj, handler, creator);
}

OUTAPI void x3UnregisterObserverObject(x3::ObserverObject* obj)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    if (reg && obj)
        reg->unregisterObserver(obj);
}

OUTAPI bool x3FireEvent(const char* type, x3::EventDispatcher dispatcher, void* data)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return reg && reg->fireEvent(type, dispatcher, data);
}

OUTAPI bool x3FireObjectEvent(const char* type, x3::ObjectEventDispatcher dispatcher, void* data)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return reg && reg->fireEvent(type, dispatcher, data);
}

#ifndef _WIN32
OUTAPI HMODULE unixFindModule(const char* filename)
{
    x3::Object<x3::IRegister> reg(x3::clsidManager);
    return reg ? reg->findModuleByFileName(filename) : NULL;
}
#endif // UNIX
