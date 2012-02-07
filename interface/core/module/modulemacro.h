// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_MODULEMACRO_H
#define X3_CORE_MODULEMACRO_H

// XBEGIN_DEFINE_MODULE()
//     XDEFINE_CLASSMAP_ENTRY(cls)
//     XDEFINE_CLASSMAP_ENTRY_Singleton(cls)
// XEND_DEFINE_MODULE()
// XEND_DEFINE_MODULE_DLL()
// XEND_DEFINE_MODULE_MFCEXTDLL()
// XEND_DEFINE_MODULE_MFCDLL()
// XEND_DEFINE_MODULE_LIB(moduleName)
// XDEFINE_EMPTY_MODULE()

#include "classentry.h"
#include "normalobject.h"
#include "singletonobj.h"

#define XBEGIN_DEFINE_MODULE()  \
    static const x3::ClassEntry s_classes[] = {

#define XDEFINE_CLASSMAP_ENTRY(cls)      \
        x3::ClassEntry(1, "NormalObject<" #cls ">", cls::_getClassID(),  \
            (x3::ObjectCreator)(&x3::NormalObject<cls>::create), \
            (x3::HASIID)(&x3::NormalObject<cls>::hasInterface)),

#define XDEFINE_CLASSMAP_ENTRY_Singleton(cls)    \
        x3::ClassEntry(x3::MIN_SINGLETON_TYPE,   \
            "SingletonObject<" #cls ">", cls::_getClassID(),  \
            (x3::ObjectCreator)(&x3::SingletonObject<cls>::create), \
            (x3::HASIID)(&x3::SingletonObject<cls>::hasInterface)),

#if !defined(_LIB) && !defined(XUSE_LIB_PLUGIN)
#define XEND_DEFINE_MODULE() \
        x3::ClassEntry() \
    };  \
    const x3::ClassEntry* const x3::ClassEntry::classes[] = {   \
        s_classes, NULL    \
    };
#else
#define XEND_DEFINE_MODULE()            x3::ClassEntry() };
#endif

#ifdef _LIB
#define XEND_DEFINE_MODULE_LIB(moduleName)  \
    x3::ClassEntry() };     \
    extern const x3::ClassEntry* const classes_##moduleName = s_classes;
#define XEND_DEFINE_MODULE_DLL()
#define XEND_DEFINE_MODULE_MFCEXTDLL()
#define XEND_DEFINE_MODULE_MFCDLL()
#else
#define XEND_DEFINE_MODULE_LIB(moduleName)  x3::ClassEntry() };

#ifdef _MSC_VER
#pragma warning(disable:4710)   // inline function not expanded
#endif

OUTAPI bool x3InitPlugin(HMODULE hmod, HMODULE);
OUTAPI void x3FreePlugin();

// XEND_DEFINE_MODULE_MFCEXTDLL: for MFC Extension DLL

#define XEND_DEFINE_MODULE_MFCEXTDLL() \
        XEND_DEFINE_MODULE()    \
static AFX_EXTENSION_MODULE MFCExtDLL = { NULL, NULL }; \
extern "C" int APIENTRY \
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)    \
{   \
    if (dwReason == DLL_PROCESS_ATTACH) \
    {   \
        if (!AfxInitExtensionModule(MFCExtDLL, hInstance))  \
            return 0;   \
        new CDynLinkLibrary(MFCExtDLL); \
        return ::x3InitPlugin(MFCExtDLL.hmod, NULL) ? 1 : 0;  \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        ::x3FreePlugin();        \
        AfxTermExtensionModule(MFCExtDLL);  \
    }   \
    return 1;   \
}

// XEND_DEFINE_MODULE_MFCDLL: for regular DLL with MFC or MFC application.

#define XEND_DEFINE_MODULE_MFCDLL() \
        XEND_DEFINE_MODULE()        \
class CPluginApp : public CWinApp   \
{   \
public: \
    CPluginApp()    \
    {   \
    }   \
    virtual BOOL InitInstance() \
    {   \
        CWinApp::InitInstance();    \
        return ::x3InitPlugin(m_hInstance, NULL); \
    }   \
    virtual int ExitInstance()  \
    {   \
        ::x3FreePlugin();    \
        return CWinApp::ExitInstance(); \
    }   \
};

// XEND_DEFINE_MODULE_DLL: for MFC Extension DLL
#if defined(_AFXEXT) && defined(_AFXDLL) && defined(APIENTRY)
#define XEND_DEFINE_MODULE_DLL()    \
        XEND_DEFINE_MODULE_MFCEXTDLL()

// XEND_DEFINE_MODULE_DLL: for regular DLL with MFC or console application with MFC
#elif defined(_AFXDLL) && defined(__AFXWIN_H__)
#define XEND_DEFINE_MODULE_DLL()    \
        XEND_DEFINE_MODULE_MFCDLL() \
        CPluginApp theApp;

// XEND_DEFINE_MODULE_DLL: for Win32 DLL
#elif defined(_USRDLL) && defined(APIENTRY)
#define XEND_DEFINE_MODULE_DLL()    \
        XEND_DEFINE_MODULE()        \
extern "C" BOOL APIENTRY DllMain(HANDLE hmod, DWORD dwReason, LPVOID)   \
{   \
    if (dwReason == DLL_PROCESS_ATTACH) \
    {   \
        return ::x3InitPlugin((HMODULE)hmod, NULL);   \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        ::x3FreePlugin();    \
    }   \
    return TRUE;    \
}

#else
#define XEND_DEFINE_MODULE_DLL()    XEND_DEFINE_MODULE()
#endif // XEND_DEFINE_MODULE_DLL


#define XDEFINE_EMPTY_MODULE()      \
    XBEGIN_DEFINE_MODULE()          \
    XEND_DEFINE_MODULE_DLL()        \
    OUTAPI bool x3InitializePlugin() { return true; }   \
    OUTAPI void x3UninitializePlugin() {}

#endif // _LIB
#endif