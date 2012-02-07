// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_IOBJECT_H
#define X3_CORE_IOBJECT_H

#define BEGIN_NAMESPACE_X3  namespace x3 {
#define END_NAMESPACE_X3    }

BEGIN_NAMESPACE_X3

#ifndef SWIG
inline long _hashkey(const char* str)
{
    unsigned long value = 0;
    while (*str)
        value = (value<<5) + value + *str++;
    return value;
}
#endif

// IID is unique only in a implement class of a plugin.
#define X3DEFINE_IID(_Interface)     \
public: \
    virtual ~_Interface() {}         \
    static const char* getInterfaceName() { return #_Interface; }   \
    static long getIID() { static long iid = x3::_hashkey(#_Interface); return iid; } \
    typedef void dummy

class IObject
{
    X3DEFINE_IID(IObject);
#ifndef SWIG
    virtual long retainObject() const = 0;
    virtual long releaseObject() const = 0;
    virtual bool queryObject(long iid, IObject** p) const = 0;
#endif
    virtual const char* getClassID() const = 0;
    virtual const char* getClassName() const = 0;
};

END_NAMESPACE_X3
#endif