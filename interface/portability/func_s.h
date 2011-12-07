//! \file func_s.h
//! \brief Realize functions compatible with VC++ 6.0 and below

#ifndef FUNCTIONS_COMPATIBLE_VC60_H
#define FUNCTIONS_COMPATIBLE_VC60_H

#if !defined(_MSC_VER) || _MSC_VER < 1400   // not VC8

#ifdef __GNUC__
#include <wchar.h>
#include <wctype.h>
#endif

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

#if defined(_STDIO_DEFINED)     // stdio.h

inline int sprintf_s(char *buffer, size_t, const char *format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    return vsprintf(buffer, format, arglist);
}

inline int swprintf_s(wchar_t *buffer, size_t size, const wchar_t *format, ...)
{
    va_list arglist;
    va_start(arglist, format);
#if !defined(_WIN32)
    return vswprintf(buffer, size, format, arglist);
#else
    size; return vswprintf(buffer, format, arglist);
#endif
}

inline int vsprintf_s(char *buffer, size_t, const char *format, va_list arglist)
    { return vsprintf(buffer, format, arglist); }

inline int vswprintf_s(wchar_t *buffer, size_t size, const wchar_t *format, va_list arglist)
#if !defined(_WIN32)
    { return vswprintf(buffer, size, format, arglist); }
#else
    { size; return vswprintf(buffer, format, arglist); }
#endif

#endif // _INC_STDIO

inline int strcpy_s(char *str, size_t size, const char *src)
    { return strncpy(str, src, size) ? 0 : -1; }
inline int wcscpy_s(wchar_t *str, size_t size, const wchar_t *src)
    { return wcsncpy(str, src, size) ? 0 : -1; }

inline int strncpy_s(char *str, size_t size, const char *src, size_t len)
    { return strncpy(str, src, min(size, len)) ? 0 : -1; }
inline int wcsncpy_s(wchar_t *str, size_t size, const wchar_t *src, size_t len)
    { return wcsncpy(str, src, min(size, len)) ? 0 : -1; }

inline int strcat_s(char *str, size_t, const char *src)
    { return strcat(str, src) ? 0 : -1; }
inline int wcscat_s(wchar_t *str, size_t, const wchar_t *src)
    { return wcscat(str, src) ? 0 : -1; }

inline wchar_t * _wcslwr_s(wchar_t *str)
    { for (wchar_t* p = str; *p; p++) towlower(*p); return str; }
inline wchar_t * _wcsupr_s(wchar_t *str)
    { for (wchar_t* p = str; *p; p++) towupper(*p); return str; }

#if defined(_WIN32)

inline int _ltoa_s(long value, char *str, size_t, int radix)
    { _ltoa(value, str, radix); return errno; }
inline int _ltow_s(long value, wchar_t *str, size_t, int radix)
    { _ltow(value, str, radix); return errno; }
inline int _itoa_s(int value, char *str, size_t, int radix)
    { _itoa(value, str, radix); return errno; }
inline int _itow_s(int value, wchar_t *str, size_t, int radix)
    { _itow(value, str, radix); return errno; }
inline int _ultow_s(unsigned long value, wchar_t *str, size_t, int radix)
    { _ultow(value, str, radix); return errno; }

#elif defined(_STDIO_DEFINED)

inline int _ltoa_s(long value, char *str, size_t size, int radix)
    { sprintf_s(str, size, 16 == radix ? "%lx" : "%ld", value); return 0; }
inline int _ltow_s(long value, wchar_t *str, size_t size, int radix)
    { swprintf_s(str, size, 16 == radix ? L"%lx" : L"%ld", value); return 0; }
inline int _itoa_s(int value, char *str, size_t size, int radix)
    { return _ltoa_s(value, str, size, radix); }
inline int _itow_s(int value, wchar_t *str, size_t size, int radix)
    { return _ltow_s(value, str, size, radix); }
inline int _ultow_s(unsigned long value, wchar_t *str, size_t size, int radix)
    { swprintf_s(str, size, 16 == radix ? L"%ulx" : L"%uld", value); return 0; }

#endif

#if (defined(_INC_STDLIB) || defined(_STDLIB_H_)) && defined(_WIN32)

inline int _splitpath_s(
    const char * path, char * drive, size_t,
    char * dir, size_t,
    char * fname, size_t,
    char * ext,  size_t)
{
    _splitpath(path, drive, dir, fname, ext);
    return errno;
}

inline int _wsplitpath_s(
    const wchar_t * path, wchar_t * drive, size_t,
    wchar_t * dir, size_t,
    wchar_t * fname, size_t,
    wchar_t * ext,  size_t)
{
    _wsplitpath(path, drive, dir, fname, ext);
    return errno;
}

inline int _makepath_s(char *path, size_t,
    const char *drive, const char *dir, const char *fname, const char *ext)
{
    _makepath(path, drive, dir, fname, ext);
    return errno;
}

inline int _wmakepath_s(wchar_t *path, size_t,
    const wchar_t *drive, const wchar_t *dir, const wchar_t *fname, const wchar_t *ext)
{
    _wmakepath(path, drive, dir, fname, ext);
    return errno;
}

#endif // _INC_STDLIB

#ifdef _INC_TIME        // time.h
inline void localtime_s(struct tm *tmOut, const time_t *timer)
{
    struct tm * p = localtime(timer);
    if (tmOut != NULL && p != NULL)
        *tmOut = *p;
}
#endif // _INC_TIME

#define _sopen_s(fileHandler, filename, oflag, pmode, rw)   \
    (*fileHandler = _open(filename, oflag, pmode), errno)

#ifdef UNICODE
#define _stprintf_s     swprintf_s
#define _vstprintf_s    vswprintf_s
#define _tcscpy_s       wcscpy_s
#define _tcsncpy_s      wcsncpy_s
#define _tcscat_s       wcscat_s
#define _tsplitpath_s   _wsplitpath_s
#define _tmakepath_s    _wmakepath_s
#define _ltot_s         _ltow_s
#define _itot_s         _itow_s
#else
#define _stprintf_s     sprintf_s
#define _vstprintf_s    vsprintf_s
#define _tcscpy_s       strcpy_s
#define _tcsncpy_s      strncpy_s
#define _tcscat_s       strcat_s
#define _tsplitpath_s   _splitpath_s
#define _tmakepath_s    _makepath_s
#define _ltot_s         _ltoa_s
#define _itot_s         _itoa_s
#endif // UNICODE

#endif // _MSC_VER

#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))
#endif

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#endif // FUNCTIONS_COMPATIBLE_VC60_H
