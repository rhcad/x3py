// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_SINGLETONOBJECT_H
#define X3_CORE_SINGLETONOBJECT_H

#include "moduleitem.h"
#include "iobject.h"

#if !defined(_MSC_VER) || _MSC_VER >= 1700
#include <mutex>
#endif

BEGIN_NAMESPACE_X3

template <class Cls>
class SingletonObject
    : public Cls
    , public ModuleItem
{
protected:
    SingletonObject() : _refcount(1)
    {
    }

    virtual ~SingletonObject()
    {
        if (Instance() == this)
        {
            Instance() = NULL;
        }
    }

protected:
    virtual long retainObject() const
    {
        return InterlockedIncrement(&_refcount);
    }

    virtual long releaseObject() const
    {
        return InterlockedDecrement(&_refcount);
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
        if (!Instance())
        {
#if !defined(_MSC_VER) || _MSC_VER >= 1700
            static std::mutex s_mutex;
            std::lock_guard<std::mutex> lock(s_mutex);
            if (!Instance())
            {
                SingletonObject<Cls>* p = new SingletonObject<Cls>();
                Instance() = p;
                p->addModuleItem();
            }
#else
            static long s_count = 0;
            SingletonObject<Cls>* p = new SingletonObject<Cls>();
            
            if (1 == InterlockedIncrement(&s_count))
            {
                Instance() = p;
                p->addModuleItem();
            }
            else
            {
                delete p;   // created by another thread
            }
            InterlockedDecrement(&s_count);
#endif
        }

        IObject* ret = NULL;
        Instance()->queryObject(iid, &ret);

        return ret;
    }

    static bool hasInterface(long iid)
    {
        return Cls::_queryObject(NULL, iid, NULL);
    }

private:
    SingletonObject(const SingletonObject&);
    void operator=(const SingletonObject&);

    mutable long    _refcount;

    static SingletonObject<Cls>*& Instance()
    {
        static SingletonObject<Cls>* obj = NULL;
        return obj;
    }
};

END_NAMESPACE_X3
#endif
