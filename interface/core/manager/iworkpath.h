/*! \file iworkpath.h
 *  \brief Define interface of getting the application's writable path: IAppWorkPath
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2012.3.4
 */
#ifndef X3_CORE_IWORKPATH_H
#define X3_CORE_IWORKPATH_H

#include "x3manager.h"
#include <string>

BEGIN_NAMESPACE_X3

/*! \ingroup _GROUP_APPUI_
 *  \interface IAppWorkPath
 *  \brief interface of getting the application's writable path.
 *  \see   x3::clsidManager, x3::getAppWorkPath()
 */
class IAppWorkPath : public IObject
{
public:
    X3DEFINE_IID(IAppWorkPath);

    //! Get the application's writable absolute path.
    /*! The default path is same as getLocalAppDataPath("x3") if setWorkPath() is not called.
        \see getLocalAppDataPath, setWorkPath
    */
    virtual std::wstring getWorkPath() = 0;

    //! Set the application's writable absolute path. (call before loading plugins)
    /*! \see getLocalAppDataPath, getWorkPath
    */
    virtual void setWorkPath(const std::wstring& path) = 0;

    //! Returns path as calling SHGetKnownFolderPath(FOLDERID_LocalAppData, ...)
    /*! The path form is "X:\Users\auser\AppData\Local\company\"
        or the executable file's folder if failed to call SHGetKnownFolderPath().
        \param company append company name to path if not empty.
        \return the absolute path.
    */
    virtual std::wstring getLocalAppDataPath(const wchar_t* company) = 0;

    //! Returns the language translation path of the current user.
    /*! eg: exepath/translations/chs/subfolder (not end with slash char).
        \param subfolder sub folder name in the translation path.
        \return the language translation path which not end with slash char.
    */
    virtual std::wstring getTranslationsPath(const wchar_t* subfolder) = 0;

    virtual std::wstring getConfigPath(const wchar_t* subfolder) = 0;
};

//! \copydoc IAppWorkPath::getWorkPath
//! \ingroup _GROUP_APPUI_
inline std::wstring getAppWorkPath()
{
    return Object<IAppWorkPath>(clsidManager)->getWorkPath();
}

//! \copydoc IAppWorkPath::getConfigPath
//! \ingroup _GROUP_APPUI_
inline std::wstring getConfigPath(const wchar_t* subfolder = L"")
{
    return Object<IAppWorkPath>(clsidManager)->getConfigPath(subfolder);
}

//! \copydoc IAppWorkPath::getTranslationsPath
//! \ingroup _GROUP_APPUI_
inline std::wstring getTranslationsPath(const wchar_t* subfolder)
{
    return Object<IAppWorkPath>(clsidManager)->getTranslationsPath(subfolder);
}

END_NAMESPACE_X3
#endif