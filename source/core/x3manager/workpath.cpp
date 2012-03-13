// x3py framework: https://github.com/rhcad/x3py
#include <module/plugininc.h>
#include "workpath.h"
#include <utilfunc/convstr.h>

BEGIN_NAMESPACE_X3

static inline void GetBasePath(char* path)
{
    GetModuleFileNameA(getModuleHandle(), path, MAX_PATH);
    PathRemoveFileSpecA(path);
    if (_stricmp("plugins", PathFindFileNameA(path)) == 0)
        PathRemoveFileSpecA(path);
}

std::wstring CWorkPath::getWorkPath()
{
    if (m_path.empty())
    {
        if (isVistaDisk())
        {
            m_path = getLocalAppDataPath(L"x3");
        }
        else
        {
            char path[MAX_PATH] = { 0 };
            GetBasePath(path);
            PathAddBackslashA(path);
            m_path = a2w(path);
        }
    }
    return m_path;
}

void CWorkPath::setWorkPath(const std::wstring& path)
{
    m_path = path;
    if (path.size() > 2
        && *path.rbegin() != L'/' && *path.rbegin() != L'\\')
    {
        m_path += L'\\';
    }
}

std::wstring CWorkPath::getConfigPath(const wchar_t* subfolder)
{
    char path[MAX_PATH] = { 0 };

    GetBasePath(path);
    PathAppendA(path, "config");
    if (subfolder && *subfolder)
        PathAppendA(path, w2a(subfolder).c_str());
    PathAddBackslashA(path);

    return a2w(path);
}

std::wstring CWorkPath::getLocalAppDataPath(const wchar_t* company)
{
    char path[MAX_PATH] = { 0 };

    if (getLocalAppDataPath_(path))
    {
        char appname[MAX_PATH];
        GetModuleFileNameA(NULL, appname, MAX_PATH);

        if (company)
            PathAppendA(path, w2a(company).c_str());
        PathAppendA(path, PathFindFileNameA(appname));
        PathRenameExtensionA(path, "");
        PathAddBackslashA(path);
    }
    else
    {
        GetBasePath(path);
        PathAddBackslashA(path);
    }

    return a2w(path);
}

std::wstring CWorkPath::getTranslationsPath(const wchar_t* subfolder)
{
    char code[4] = "chs";
    char path[MAX_PATH] = { 0 };

#ifdef _WIN32
    typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
    PFNGETUSERDEFAULTUILANGUAGE pfnGetLang;

    pfnGetLang = (PFNGETUSERDEFAULTUILANGUAGE)::GetProcAddress(
        ::GetModuleHandleA("kernel32.dll"), "GetUserDefaultUILanguage");
    if (pfnGetLang != NULL)
    {
        LANGID langid = pfnGetLang();
        ::GetLocaleInfoA(langid, LOCALE_SABBREVLANGNAME, code, 4);
    }
#endif

    GetBasePath(path);
    PathAppendA(path, "translations");
    PathAppendA(path, code);
    PathAddBackslashA(path);
    if (subfolder && *subfolder)
        PathAppendA(path, w2a(subfolder).c_str());

    return a2w(path);
}

bool CWorkPath::isVistaDisk()
{
    bool ret = false;
#ifdef WINOLEAPI_
    OSVERSIONINFO osvi = { sizeof(OSVERSIONINFO) };
    char winpath[MAX_PATH], exepath[MAX_PATH];

    if (GetVersionEx(&osvi) && osvi.dwMajorVersion >= 6)
    {
        GetSystemDirectoryA(winpath, MAX_PATH);
        GetModuleFileNameA(getModuleHandle(), exepath, MAX_PATH);
        ret = (_strnicmp(winpath, exepath, 2) == 0);
    }
#endif
    return ret;
}

bool CWorkPath::getLocalAppDataPath_(char* path)
{
    bool ret = false;
#ifdef WINOLEAPI_
    // FOLDERID_LocalAppDataGUID {F1B32785-6FBA-4FCF-9D55-7B8E7F157091}
    const GUID uuidLocalAppData = {0xF1B32785,0x6FBA,0x4FCF,
        {0x9D,0x55,0x7B,0x8E,0x7F,0x15,0x70,0x91}};

    typedef HRESULT (STDAPICALLTYPE *PFNGET)(REFGUID, DWORD, HANDLE, PWSTR*);
    HMODULE hdll = LoadLibraryA("SHELL32.DLL");

    if (hdll != NULL)
    {
        PWSTR shpath = NULL;
        PFNGET pfn = (PFNGET)GetProcAddress(hdll, "SHGetKnownFolderPath");

        if (pfn != NULL)
        {
            pfn(uuidLocalAppData, 0, NULL, &shpath);
        }
        if (shpath != NULL)
        {
            strcpy_s(path, MAX_PATH, w2a(shpath).c_str());
            ret = (*path != 0);
            CoTaskMemFree(shpath);
        }
        FreeLibrary(hdll);
    }
#endif
    return ret;
}

END_NAMESPACE_X3