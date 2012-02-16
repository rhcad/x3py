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
OUTAPI bool x3FreePlugin();

// Call x3DllMain in your DllMain function.
#define x3DllMain(hInstance, dwReason)  \
    (dwReason == DLL_PROCESS_ATTACH && ::x3InitPlugin((HMODULE)hInstance, NULL) \
    || dwReason == DLL_PROCESS_DETACH && (::x3FreePlugin() || true))

// XEND_DEFINE_MODULE_MFCEXTDLL: for MFC Extension DLL, same as XEND_DEFINE_MODULE_DLL.
// You need to remove your DllMain function or call x3DllMain in your DllMain function.

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
        return ::x3InitPlugin(MFCExtDLL.hModule, NULL) ? 1 : 0;  \
    }   \
    else if (dwReason == DLL_PROCESS_DETACH)    \
    {   \
        ::x3FreePlugin();        \
        AfxTermExtensionModule(MFCExtDLL);  \
    }   \
    return 1;   \
}

// XEND_DEFINE_MODULE_MFCDLL: for regular DLL with MFC or MFC application.
// You need to define a instance such as 'CPluginApp theApp;' .
// You may derive a class from CPluginApp instead of CWinApp.

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
// You need to remove your DllMain function or call x3DllMain and use XEND_DEFINE_MODULE.

#if defined(_AFXEXT) && defined(_AFXDLL) && defined(APIENTRY)
#define XEND_DEFINE_MODULE_DLL()    \
        XEND_DEFINE_MODULE_MFCEXTDLL()

// XEND_DEFINE_MODULE_DLL: for regular DLL with MFC or console application with MFC.
//
// If you already have a class derived from CWinApp, then 'theApp' redefinition
// error will occur. You can correct it as the following method:
// 1. call x3InitPlugin and x3FreePlugin in your app class and use XEND_DEFINE_MODULE.
// 2. or use XEND_DEFINE_MODULE_MFCDLL and derive from CPluginApp instead of CWinApp.
// 3. or remove your app class and keep to use XEND_DEFINE_MODULE_DLL.

#elif defined(_AFXDLL) && defined(__AFXWIN_H__)
#define XEND_DEFINE_MODULE_DLL()    \
        XEND_DEFINE_MODULE_MFCDLL() \
        CPluginApp theApp;

// XEND_DEFINE_MODULE_DLL: for Win32 DLL.
// You need to remove your DllMain function or call x3DllMain and use XEND_DEFINE_MODULE.

#elif defined(_USRDLL) && defined(APIENTRY)
#ifndef _ATL_DLL
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
#else // ATL project
// Please call x3DllMain in your DllMain and use XEND_DEFINE_MODULE instead of XEND_DEFINE_MODULE_DLL.
#define XEND_DEFINE_MODULE_DLL()    please_use_XEND_DEFINE_MODULE_and_call_x3DllMain
#endif

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