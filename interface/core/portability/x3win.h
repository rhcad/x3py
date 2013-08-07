// Included by X3Portability.h to declare functions on Windows.

#ifndef X3WIN_PORTABILITY_H
#define X3WIN_PORTABILITY_H

#if !defined(_MSC_VER) || _MSC_VER > 1200 // not VC6

#ifndef WINVER
#define WINVER 0x0501           // WinXP or later.
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT    WINVER
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS  WINVER
#endif
#ifndef _WIN32_IE
#define _WIN32_IE 0x0600        // IE6 or later.
#endif

#endif // _MSC_VER

#ifdef _AFXDLL
#define VC_EXTRALEAN
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdisp.h>        // MFC Automation classes
#endif
#else
#define _WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>        // Windows master include file
#endif // _AFXDLL

#ifdef _MSC_VER
#include <shlwapi.h>        // Windows light-weight utility APIs
#pragma comment(lib, "shlwapi.lib")
#endif

#ifdef __GNUC__
#define OUTAPI      extern "C" __attribute__((dllexport))
#else
#define OUTAPI      extern "C" __declspec(dllexport)
#endif
#define LOCALAPI

#endif