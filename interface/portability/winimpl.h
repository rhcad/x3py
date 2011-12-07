// Included by portimpl.h to implement functions on Windows.

#ifndef X3WIN_PORTABILITY_IMPL_H
#define X3WIN_PORTABILITY_IMPL_H

#include "x3win.h"

bool x3FreeLibrary(HMODULE hdll)
{
#ifdef __GNUC__
    typedef void (*F)();
    F f = (F)GetProcAddress(hdll, "x3FreePlugin");
    if (f) f();
#endif
    return !!FreeLibrary(hdll);
}

HMODULE x3LoadLibrary(const char* filename)
{
    HMODULE hdll = LoadLibraryExA(filename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

#ifdef __GNUC__
    typedef bool (*F)(HMODULE, HMODULE);
    F f = (F)GetProcAddress(hdll, "x3InitPlugin");

    if (f && !f(hdll, NULL))
    {
        x3FreeLibrary(hdll);
        hdll = NULL;
    }
#endif

    return hdll;
}

#endif