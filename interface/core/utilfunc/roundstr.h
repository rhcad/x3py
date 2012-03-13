//! \file roundstr.h
//! \brief Define the function converting and round float-pointing number to string: RoundStr

#ifndef UTILFUNC_ROUNDSTR_H_
#define UTILFUNC_ROUNDSTR_H_

#include <string>

namespace x3 {

//! Returns a numeric string, rounded to the specified precision.
/*!
    \ingroup _GROUP_UTILFUNC
    \param value float-pointing number to be rounded.
    \param decimal a positive number thar value is rounded to the number of decimal places.
    \return a numeric string whose zero digits ('0') after number point will be removed.
*/
inline std::wstring RoundStr(double value, int decimal = 4)
{
    wchar_t buf[65] = { 0 };

    wchar_t fmt[] = L"%.2lf";
    if (decimal < 1) decimal = 1;
    if (decimal > 5) decimal = 5;
    fmt[2] = (wchar_t)(L'0' + decimal);
    swprintf_s(buf, 65, fmt, value);

    wchar_t* p = wcschr(buf, L'.');
    if (p != NULL)
    {
        int i = decimal;
        for (; i > 0 && p[i] == L'0'; i--)
            p[i] = 0;
        if (p[i] == L'.')
            p[i] = 0;
    }

    return buf;
}

} // x3
#endif // UTILFUNC_ROUNDSTR_H_
