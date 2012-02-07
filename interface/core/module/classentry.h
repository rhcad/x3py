// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_CLASSENTRY_H
#define X3_CORE_CLASSENTRY_H

#include "iobject.h"

BEGIN_NAMESPACE_X3

typedef IObject* (*ObjectCreator)(long iid);
typedef bool (*HASIID)(long iid);
enum { MIN_SINGLETON_TYPE = 10 };

class ClassEntry
{
public:
    int             type;
    const char*     className;
    const char*     clsid;
    ObjectCreator   creator;
    HASIID          hasiid;

    ClassEntry(int _type, const char* _className,
        const char* _clsid, ObjectCreator _creator, HASIID _hasiid)
        : type(_type), className(_className), clsid(_clsid)
        , creator(_creator), hasiid(_hasiid)
    {
    }

    ClassEntry() : type(0), className(""), clsid(""), creator(NULL), hasiid(NULL)
    {
    }

    // see XEND_DEFINE_MODULE, XEND_DEFINE_MODULE_LIB
    static const ClassEntry* const  classes[];
};

END_NAMESPACE_X3
#endif