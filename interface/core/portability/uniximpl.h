// Included by portimpl.h to implement functions on Linux.
// __linux__ or  __APPLE__ is defined.

#ifndef X3LINUX_PORTABILITY_IMPL_H
#define X3LINUX_PORTABILITY_IMPL_H

#include "x3unix.h"
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>             // getcwd

static HMODULE _hmod = NULL;
static HMODULE _manager = NULL;
static char _filename[MAX_PATH] = "";

OUTAPI bool _ondlopen(HMODULE hmod, const char* filename, HMODULE hmanager)
{
    _hmod = hmod;
    _manager = hmanager;
    strncpy(_filename, filename, MAX_PATH);

    typedef bool (*F)(HMODULE, HMODULE);
    F f = (F)GetProcAddress(hmod, "x3InitPlugin");

    return !f || f(hmod, _manager);
}

OUTAPI bool _getdlname(char* filename, int size)
{
    return !!strncpy(filename, _filename, size);
}

static inline void seterr(const char* err)
{
    if (err) {}
}

bool x3FreeLibrary(HMODULE hmod)
{
    typedef void (*F)();
    F f = (F)GetProcAddress(hmod, "x3FreePlugin");
    if (f) f();

    int ret = hmod ? dlclose(hmod) : 0;
    seterr(dlerror());
    return 0 == ret;
}

HMODULE x3LoadLibrary(const char* filename)
{
    char fullpath[MAX_PATH];
    HMODULE hmod = NULL;

    if (!filename) {
        return NULL;
    }
    if (PathIsRelativeA(filename))
    {
        if (!hmod && _filename[0]) // base on the current module
        {
            strcpy(fullpath, _filename);
            PathRemoveFileSpecA(fullpath);
            PathAppendA(fullpath, filename);
            hmod = dlopen(fullpath, RTLD_LAZY);
        }
        if (!hmod)                  // base on the current process
        {
            GetModuleFileNameA(NULL, fullpath, MAX_PATH);
            if (fullpath[0]) {
                PathRemoveFileSpecA(fullpath);
                PathAppendA(fullpath, filename);
                hmod = dlopen(fullpath, RTLD_LAZY);
            }
        }
        if (!hmod)                  // base on the current direction
        {
            getcwd(fullpath, MAX_PATH);
#ifdef CURMOD_IN_CWDSUBDIR
           if (_strnicmp(filename, "../", 3) == 0) filename += 3;
#endif
            PathAppendA(fullpath, filename);
            hmod = dlopen(fullpath, RTLD_LAZY);
        }
        if (hmod) {
            filename = fullpath;
        }
    }
    if (!hmod)
    {
        hmod = dlopen(filename, RTLD_LAZY);
        seterr(dlerror());
    }
    
    if (hmod)
    {
        if (0 == strcmp("x3manager.pln", PathFindFileNameA(filename)))
        {
            _manager = hmod;
        }

        typedef bool (*F)(HMODULE, const char*, HMODULE);
        F f = (F)GetProcAddress(hmod, "_ondlopen");
        if (f && !f(hmod, filename, _manager))
        {
            x3FreeLibrary(hmod);
            hmod = NULL;
        }
    }

    return hmod;
}

void* GetProcAddress(HMODULE hmod, const char* name)
{
    void* sym = NULL;

    if (hmod)
    {
        sym = dlsym(hmod, name);
        seterr(dlerror());
    }

    return sym;
}

HMODULE GetModuleHandleA(const char* filename)
{
    if (!filename)
    {
        return NULL;
    }
    if (PathIsRelativeA(filename)
        && 0 == strcmp(PathFindFileNameA(filename), PathFindFileNameA(_filename)))
    {
        return _hmod;
    }

    typedef HMODULE (*F)(const char*);
    F f = (F)GetProcAddress(_manager, "unixFindModule");

    return f ? f(filename) : NULL;
}

void GetModuleFileNameA(HMODULE hmod, char* filename, int size)
{
    *filename = 0;

    if (!hmod)
    {
        size_t bytes = readlink("/proc/self/exe", filename, size);
        if (bytes > 0)
            filename[bytes < size - 1 ? bytes : size - 1] = '\0';
    }
    else
    {
        typedef bool (*F)(char*, int);
        F f = (F)GetProcAddress(hmod, "_getdlname");
        if (f) f(filename, size);
    }
}

DWORD GetLastError()
{
    return 0;
}

int WideCharToMultiByte(int /*codepage*/, DWORD /*flags*/,
                        const wchar_t* wstr, int wchars,
                        char* astr, int achars,
                        const char*, void*)
{
    return (int)(astr ? wcstombs(astr, wstr, achars) : (wchars * sizeof(char)));
}

int MultiByteToWideChar(int /*codepage*/, DWORD /*flags*/,
                        const char* astr, int achars,
                        wchar_t* wstr, int wchars)
{
    return wstr ? (int)mbstowcs(wstr, astr, wchars) : achars;
}

int _stricmp(const char* s1, const char* s2)
{
    return strncasecmp(s1, s2, strlen(s1));
}

int _strnicmp(const char* s1, const char* s2, int count)
{
    return strncasecmp(s1, s2, count);
}

long InterlockedIncrement(long* p)
{
    return ++(*p);
}

long InterlockedDecrement(long* p)
{
    return --(*p);
}

long InterlockedExchange(long* p, long v)
{
    long old = *p;
    *p = v;
    return old;
}

#endif
