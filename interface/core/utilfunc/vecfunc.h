//! \file vecfunc.h
//! \brief Define functions of STL container and include frequently-used STL files.

#ifndef __STL_VECTOR_FUNCTIONS_H
#define __STL_VECTOR_FUNCTIONS_H

#ifdef _MSC_VER                 // hide warnings
#pragma warning(disable:4710)   // inline function not expanded
#pragma warning(disable:4786)   // identifier was truncated
#pragma warning (push, 3)
#pragma warning(disable:4018)   // signed/unsigned mismatch
#pragma warning(disable:4702)   // unreachable code
#endif
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <sstream>
#ifdef _MSC_VER                 // hide warnings
#pragma warning (pop)
#endif

namespace x3 {

#ifdef __AFX_H__
//! Converts safely from CString variable to std::wstring, avoid null address problem.
inline std::wstring towstr(const CString& str)
{
    return str.IsEmpty() ? L"" : (LPCTSTR)str;
}
#endif

//! Removes an element that match a condition expression in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map). eg: " vector<Ix_xxx*> arr; "
    \param _P The condition expression for matching elements. eg: " std::bind2nd(std::equal_to<Ix_xxx*>(), pObj) "
    \return the element is removed or not.
    \see erase_value, find_if
*/
template<class _Ta, class _Pr> inline
bool erase_if(_Ta& arr, _Pr _P)
{
    typename _Ta::iterator it = std::find_if(arr.begin(), arr.end(), _P);
    bool b = (it != arr.end());

    if (b)
    {
        arr.erase(it);
    }

    return b;
};

//! Removes an element that match a element value in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map). eg: " vector<Ix_xxx*> arr; "
    \param p The element value for matching. It's type is same as the element type of 'arr'. eg: " Ix_xxx* pObj"
    \return the element is removed or not.
    \see erase_if, find_value
*/
template<class _Ta, class _Tp> inline
bool erase_value(_Ta& arr, _Tp& p)
{
    return erase_if(arr, std::bind2nd(std::equal_to<_Tp>(), p));
}

//! Finds the position index of an element that match a condition expression in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL vector variable. eg: " vector<Ix_xxx*> arr; "
    \param _P The condition expression for matching elements. eg: " std::bind2nd(std::equal_to<Ix_xxx*>(), pObj) "
    \return the position index of an element, or -1 if not found.
    \see find_value, has_value
*/
template<class _Ta, class _Pr> inline
long find_if(const _Ta& arr, _Pr _P)
{
    typename _Ta::const_iterator it = std::find_if(arr.begin(), arr.end(), _P);
    return (it != arr.end()) ? (long)(it - arr.begin()) : -1;
}

//! Finds the position index of an element that match a element value in a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map). eg: " vector<Ix_xxx*> arr; "
    \param p The element value for matching. It's type is same as the element type of 'arr'. eg: " Ix_xxx* pObj"
    \return the position index of an element, or -1 if not found.
    \see has_value, find_if
*/
template<class _Ta, class _Tp> inline
long find_value(const _Ta& arr, const _Tp& p)
{
    return find_if(arr, std::bind2nd(std::equal_to<_Tp>(), p));
}

//! Checks whether a container has an element that match a element value or not.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map). eg: " vector<Ix_xxx*> arr; "
    \param p The element value for matching. It's type is same as the element type of 'arr'. eg: " Ix_xxx* pObj"
    \return true if the container has the element.
    \see find_value, find_if
*/
template<class _Ta, class _Tp> inline
bool has_value(const _Ta& arr, const _Tp& p)
{
    typename _Ta::const_iterator it = std::find_if(arr.begin(), arr.end(),
        std::bind2nd(std::equal_to<_Tp>(), p));
    return it != arr.end();
}

//! Returns element count of a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL container variable (vector, list, map).
    \return element count.
*/
template<class _Ta> inline
long GetSize(const _Ta& arr)
{
    return static_cast<long>(arr.size());
}

//! Checks a position index is in range or out of range of a container.
/*!
    \ingroup _GROUP_UTILFUNC
    \param arr STL vector variable. eg: " vector<Ix_xxx*> arr; "
    \param index The position index of the element.
    \return true if the position index is in range of the container.
*/
template<class _Ta> inline
bool IsValidIndexOf(const _Ta& arr, long index)
{
    return index >= 0 && index < static_cast<long>(arr.size());
}

} // x3
#endif // __STL_VECTOR_FUNCTIONS_H
