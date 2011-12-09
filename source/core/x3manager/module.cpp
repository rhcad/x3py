#include <module/plugininc.h>
#include <module/modulemacro.h>
#define X3_EXCLUDE_CREATEOBJECT
#include <module/pluginimpl.h>

#include "plugins.h"

BEGIN_NAMESPACE_X3

class CManager : public CPlugins
{
    X3BEGIN_CLASS_DECLARE(CManager, clsidManager)
        X3USE_INTERFACE_ENTRY(CPlugins)
    X3END_CLASS_DECLARE()
protected:
    CManager() {}
};

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(CManager)
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    return true;
}

OUTAPI void x3UninitializePlugin()
{
}

OUTAPI bool x3RegisterPlugin(Creator creator, HMODULE hmod, const char** clsids)
{
    Object<IRegister> reg(clsidManager);
    return reg && reg->registerPlugin(creator, hmod, clsids);
}

OUTAPI void x3UnregisterPlugin(Creator creator)
{
    Object<IRegister> reg(clsidManager);
    if (reg && creator)
        reg->unregisterPlugin(creator);
}

OUTAPI bool x3CreateObject(const char* clsid, long iid, IObject** p)
{
    if (x3InternalCreate(clsid, iid, p))
        return true;
    Object<IRegister> reg(clsidManager);
    return reg && reg->createFromOthers(clsid, iid, p);
}

OUTAPI bool x3RegisterObserver(const char* type, PROC handler, Creator creator)
{
    Object<IRegister> reg(clsidManager);
    return reg && reg->registerObserver(type, handler, creator);
}

OUTAPI bool x3RegisterObserverObject(const char* type, ObserverObject* obj, 
                                     ON_EVENT handler, Creator creator)
{
    Object<IRegister> reg(clsidManager);
    return reg && reg->registerObserver(type, obj, handler, creator);
}

OUTAPI void x3UnregisterObserverObject(ObserverObject* obj)
{
    Object<IRegister> reg(clsidManager);
    if (reg && obj)
        reg->unregisterObserver(obj);
}

OUTAPI int x3FireEvent(const char* type, EventDispatcher dispatcher, void* data)
{
    Object<IRegister> reg(clsidManager);
    return reg ? reg->fireEvent(type, dispatcher, data) : 0;
}

OUTAPI int x3FireObjectEvent(const char* type, ObjectEventDispatcher dispatcher, void* data)
{
    Object<IRegister> reg(clsidManager);
    return reg ? reg->fireEvent(type, dispatcher, data) : 0;
}

#ifndef _WIN32
OUTAPI HMODULE unixFindModule(const char* filename)
{
    Object<IRegister> reg(clsidManager);
    return reg ? reg->findModuleByFileName(filename) : NULL;
}
#endif // UNIX

END_NAMESPACE_X3