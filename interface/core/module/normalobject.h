// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_NORMALOBJECT_H
#define X3_CORE_NORMALOBJECT_H

#include "iobject.h"

BEGIN_NAMESPACE_X3

template <class Cls>
class NormalObject : public Cls
{
protected:
    NormalObject() : _refcount(1)
    {
    }

    virtual ~NormalObject()
    {
    }

protected:
    virtual long retainObject() const
    {
        return InterlockedIncrement(&_refcount);
    }

    virtual long releaseObject() const
    {
        long ret = InterlockedDecrement(&_refcount);
        if (0 == ret)
        {
            delete this;
        }

        return ret;
    }

    virtual bool queryObject(long iid, IObject** p) const
    {
        return Cls::_queryObject(this, iid, p);
    }

    virtual const char* getClassID() const
    {
        return Cls::_getClassID();
    }

    virtual const char* getClassName() const
    {
        return Cls::_getClassName();
    }

public:
    static IObject* create(long iid)
    {
        IObject* ret = NULL;
        NormalObject<Cls>* p = new NormalObject<Cls>();

        p->queryObject(iid, &ret);
        p->releaseObject();

        return ret;
    }

    static bool hasInterface(long iid)
    {
        return Cls::_queryObject(NULL, iid, NULL);
    }

private:
    NormalObject(const NormalObject&);
    void operator=(const NormalObject&);

    mutable long    _refcount;
};

END_NAMESPACE_X3
#endif