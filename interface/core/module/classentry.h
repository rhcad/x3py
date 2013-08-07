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

// If don't need plugininc.h or portability/*.h on Windows:
#if !defined(OUTAPI) && defined(_WIN32)
#ifndef _WINDEF_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#define OUTAPI      extern "C" __declspec(dllexport)
#define LOCALAPI
#define x3FreeLibrary(h) FreeLibrary(h)
#define x3LoadLibrary(f) LoadLibraryExA(f, NULL, LOAD_WITH_ALTERED_SEARCH_PATH)
#endif // OUTAPI

#endif