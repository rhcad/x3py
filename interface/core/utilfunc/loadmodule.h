#ifndef UTILFUNC_LOADDLLHELPER_H_
#define UTILFUNC_LOADDLLHELPER_H_

namespace x3 {

class LoadModuleHelper
{
public:
    LoadModuleHelper(const char* filename = NULL, 
        HMODULE basemod = NULL, HMODULE* assign = NULL)
        : _hmod(NULL), _assign(assign), _loadnew(false)
    {
        if (filename)
            load(filename, basemod);
    }

    ~LoadModuleHelper()
    {
        unload();
    }

    void unload()
    {
        if (_hmod)
        {
            if (_loadnew)
                x3FreeLibrary(_hmod);
            _hmod = NULL;

            if (_assign)
                *_assign = NULL;
        }
    }

    bool load(const char* filename, HMODULE basemod = NULL, const char* folder = "")
    {
        unload();

        _hmod = GetModuleHandleA(PathFindFileNameA(filename));
        _loadnew = !_hmod;

        if (!_hmod)
        {
            char fullname[MAX_PATH] = "";

            if (PathIsRelativeA(filename))
            {
                GetModuleFileNameA(basemod, fullname, MAX_PATH);
                PathRemoveFileSpecA(fullname);
                PathAppendA(fullname, folder);
                PathAppendA(fullname, filename);
                _hmod = x3LoadLibrary(fullname);
            }
            if (!_hmod)
                _hmod = x3LoadLibrary(filename);
            if (!_hmod)
                _hmod = x3LoadLibrary(PathFindFileNameA(filename));
        }
        if (_assign)
        {
            *_assign = _hmod;
        }

        return _hmod != NULL;
    }

    HMODULE getModule() const
    {
        return _hmod;
    }

    PROC getFunc(const char* name) const
    {
        return _hmod ? GetProcAddress(_hmod, name) : NULL;
    }

private:
    HMODULE     _hmod;
    HMODULE*    _assign;
    bool        _loadnew;
};

} // x3
#endif