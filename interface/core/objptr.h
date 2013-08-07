// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_OBJPTR_H
#define X3_CORE_OBJPTR_H

#include "iobject.h"

BEGIN_NAMESPACE_X3

#ifndef SWIG
LOCALAPI bool createObject(const char* clsid, long iid, IObject** p);
struct NullPointerError {};
#ifndef X3THROW_NULLPOINTERERROR
#define X3THROW_NULLPOINTERERROR(name) throw x3::NullPointerError()
#endif
#endif // SWIG

template <class I> class Object
{
public:
    // if clsid is "" then the actual class id will be used just in the current plugin.
    Object(const char* clsid) : _p(0)
    {
        createObject(clsid, I::getIID(), address());
    }

    Object(const IObject* src) : _p(0)
    {
        operator=(src);
    }

#if !defined(_MSC_VER) || _MSC_VER > 1200
    Object(const Object<I>& src) : _p(0)
    {
        operator=(src.p());
    }
#endif // not vc6

    bool valid() const
    {
        return this && _p;
    }

    I* p() const
    {
        return this ? _p : 0;
    }

    I* operator->() const
    {
        if (!_p) {
            X3THROW_NULLPOINTERERROR(I::getInterfaceName());
        }
        return _p;
    }

#ifndef SWIG    // SWIG always call operator->() so must create when constructing.
    Object() : _p(0)
    {
    }

    template <class I2>
    Object(const Object<I2>& src) : _p(0)
    {
        operator=(src.p());
    }

    ~Object()
    {
        release();
    }

    void release()
    {
        if (this && _p)
        {
            _p->releaseObject();
            _p = 0;
        }
    }

    Object<I>& create(const char* clsid = "")
    {
        createObject(clsid, I::getIID(), address());
        return *this;
    }

#if !defined(_MSC_VER) || _MSC_VER > 1200
    Object<I>& operator=(const Object<I>& src)
    {
        if (src)
            src.p()->retainObject();
        if (_p)
            _p->releaseObject();
        _p = src.p();

        return *this;
    }
#endif // not vc6

    template <class I2>
    Object<I>& operator=(const Object<I2>& src)
    {
        if (I::getIID() == I2::getIID()
            || I::getIID() == IObject::getIID())
        {
            if (src)
                src.p()->retainObject();
            if (_p)
                _p->releaseObject();
            _p = src.p();

            return *this;
        }
        
        return operator=(src.p());
    }

    Object<I>& operator=(const IObject* src)
    {
        if (_p != src)
        {
            release();
            if (I::getIID() == IObject::getIID() && src)
            {
                src->retainObject();
                _p = static_cast<I*>(const_cast<IObject*>(src));
            }
            else if (src)
            {
                src->queryObject(I::getIID(), address());
            }
        }
        return *this; 
    }

    operator bool() const
    {
        return this && _p;
    }

    bool operator!() const
    {
        return !(this && _p);
    }

    bool operator==(const Object<I>& src) const
    {
        return _p == src._p;
    }

    bool operator!=(const Object<I>& src) const
    {
        return _p != src._p;
    }

    IObject** address()
    {
        release();
        return reinterpret_cast<IObject**>(&_p);
    }
#endif // SWIG

private:
    I*  _p;
};

typedef Object<IObject> AnyObject;

END_NAMESPACE_X3
#endif