// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_WORKPATH_IMPL_H
#define X3_CORE_WORKPATH_IMPL_H

#include <module/classmacro.h>
#include <manager/iworkpath.h>

BEGIN_NAMESPACE_X3

class CWorkPath : public IAppWorkPath
{
    X3BEGIN_CLASS_DECLARE0(CWorkPath)
        X3DEFINE_INTERFACE_ENTRY(IAppWorkPath)
    X3END_CLASS_DECLARE()
protected:
    CWorkPath() {}

private:
    virtual std::wstring getWorkPath();
    virtual void setWorkPath(const std::wstring&);
    virtual std::wstring getLocalAppDataPath(const wchar_t*);
    virtual std::wstring getTranslationsPath(const wchar_t*);
    virtual std::wstring getConfigPath(const wchar_t*);

private:
    bool isVistaDisk();
    bool getLocalAppDataPath_(char*);

    std::wstring    m_path;
};

END_NAMESPACE_X3
#endif