// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_CLASSMACRO_H
#define X3_CORE_CLASSMACRO_H

// X3BEGIN_CLASS_DECLARE(Cls, clsid)
// X3BEGIN_CLASS_DECLARE0(Cls)
//     X3DEFINE_INTERFACE_ENTRY(_Interface)
//     X3USE_INTERFACE_ENTRY(_BaseClass)
// X3END_CLASS_DECLARE()

namespace x3 {
LOCALAPI HMODULE getModuleHandle();
LOCALAPI HMODULE getManagerModule();
}

#define X3BEGIN_CLASS_DECLARE0(Cls) \
public: \
    static bool _queryObject(const Cls* self, long iid, x3::IObject** p)  \
    {

#define X3BEGIN_CLASS_DECLARE(Cls, clsid)  \
public: \
    static const char* _getClassID() { return clsid; }   \
    static const char* _getClassName() { return #Cls; }   \
    static bool _queryObject(const Cls* self, long iid, x3::IObject** p)  \
    {

#define X3DEFINE_INTERFACE_ENTRY(_Interface)    \
        if (iid == _Interface::getIID())        \
        {   \
            if (self) {     \
                *p = (x3::IObject*)(_Interface*)(self); \
                (*p)->retainObject(); \
            }   \
            return true;    \
        }

#define X3USE_INTERFACE_ENTRY(_BaseClass)   \
        if (_BaseClass::_queryObject(self, iid, p))   \
        {   \
            return true;    \
        }

#define X3END_CLASS_DECLARE() \
        return false; \
    }   \
protected:  // Ensure the following constructor is protected.

#endif