//! \file syserrstr.h
//! \brief Define a function to obtains error message strings: GetSystemErrorString.

#ifndef UTILFUNC_SYSERRSTR_H_
#define UTILFUNC_SYSERRSTR_H_

#include <string>

namespace x3 {

//! Obtains error message strings for a error code.
/*!
    \ingroup _GROUP_UTILFUNC
    \param errorcode the error code returned by GetLastError or HRESULT value.
    \return error message strings.
*/
inline std::wstring GetSystemErrorString(unsigned long errorcode)
{
    std::wstring retstr;
    wchar_t buf[21] = { 0 };

    if (errorcode != 0)
    {
#ifdef FormatMessage
        wchar_t* p = NULL;

        ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, errorcode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (wchar_t*)&p, 0, NULL);

        if (p != NULL)
        {
            retstr = p;
            ::LocalFree((HLOCAL)p);
        }
#endif

        // define _NEED_STDIO before include PluginInc.h for vc6 or gcc.
        swprintf_s(buf, _countof(buf), L"[0x%x]", errorcode);
        retstr = buf + retstr;
    }

    return retstr;
}

} // x3
#endif // UTILFUNC_SYSERRSTR_H_
