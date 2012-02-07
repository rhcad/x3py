// x3py framework: https://github.com/rhcad/x3py
#include <module/plugininc.h>
#include "plugins.h"

BEGIN_NAMESPACE_X3

CPlugins::CPlugins()
{
}

CPlugins::~CPlugins()
{
}

int CPlugins::getPluginCount() const
{
    LockRW locker(_plugins.locker);
    return locker.canRead() ? (1 + GetSize(_plugins)) : 1;
}

void CPlugins::getPluginFiles(std::vector<std::string>& files) const
{
    char filename[MAX_PATH] = { 0 };

    files.clear();
    GetModuleFileNameA(getModuleHandle(), filename, MAX_PATH);
    files.push_back(filename);

    LockRW locker(_plugins.locker);
    if (locker.canRead())
    {
        for (std::vector<Plugin>::const_iterator it = _plugins.begin();
            it != _plugins.end(); ++it)
        {
            GetModuleFileNameA(it->second, filename, MAX_PATH);
            files.push_back(filename);
        }
    }
}

bool CPlugins::registerPlugin(Creator creator, HMODULE hmod, const char** clsids)
{
    bool needInit = true;
    LockRW locker(_plugins.locker, true);

    if (locker.canWrite() && find_value(_plugins, Plugin(creator, hmod)) < 0)
    {
        _plugins.push_back(Plugin(creator, hmod));

        LockRW lockcls(_clsmap.locker, true);
        for (; *clsids && lockcls.canWrite(); clsids++)
        {
            _clsmap[*clsids] = creator;
        }
    }

    return needInit;
}

void CPlugins::unregisterPlugin(Creator creator)
{
    LockRW locker(_plugins.locker, true);
    if (locker.canWrite())
    {
        for (std::vector<Plugin>::iterator it = _plugins.begin();
            it != _plugins.end(); ++it)
        {
            if (it->first == creator)
            {
                _plugins.erase(it);
                break;
            }
        }
    }

    LockRW lockcls(_clsmap.locker, true);
    if (lockcls.canWrite())
    {
        hash_map<std::string, Creator>::iterator it = _clsmap.begin();
        while (it != _clsmap.end())
        {
            if (it->second == creator)
            {
                _clsmap.erase(it);
                it = _clsmap.begin();
            }
            else
            {
                ++it;
            }
        }
    }

    LockRW lockobserver(_observers.locker, true);
    if (lockobserver.canRead())
    {
        for (MAP_IT it = _observers.begin(); it != _observers.end(); )
        {
            if (it->second.creator == creator)
            {
                if (lockobserver.canWrite())
                {
                    _observers.erase(it);
                    it = _observers.begin();
                }
                else
                {
                    it->second = ObserverItem();
                    ++it;
                }
            }
            else
            {
                ++it;
            }
        }
    }
}

void CPlugins::unregisterObserver(ObserverObject* obj)
{
    LockRW locker(_observers.locker, true);

    if (!locker.canRead())
    {
        return;
    }
    for (MAP_IT it = _observers.begin(); it != _observers.end(); )
    {
        if (it->second.obj == obj)
        {
            if (locker.canWrite())
            {
                _observers.erase(it);
                it = _observers.begin();
            }
            else
            {
                it->second.obj = NULL;
                ++it;
            }
        }
        else
        {
            ++it;
        }
    }
}

Creator CPlugins::findPluginByClassID(const char* clsid) const
{
    LockRW locker(_clsmap.locker);
    Creator ret = NULL;

    if (locker.canRead())
    {
        hash_map<std::string, Creator>::const_iterator it = _clsmap.find(clsid);
        ret = (it != _clsmap.end()) ? it->second : NULL;
    }

    return ret;
}

bool CPlugins::createFromOthers(const char* clsid, long iid, IObject** p)
{
    Creator creator = findPluginByClassID(clsid);
    return creator && creator(clsid, iid, p);
}

bool CPlugins::registerObserver(const char* type, PROC handler, Creator creator)
{
    LockRW locker(_observers.locker, true);
    bool ret = type && handler && creator && locker.canWrite();

    if (ret)
    {
        ObserverItem item;
        item.creator = creator;
        item.handler = handler;
        item.obj = NULL;
        item.objhandler = NULL;
        _observers.insert(ObserverPair(type, item));
    }

    return ret;
}

bool CPlugins::registerObserver(const char* type, ObserverObject* obj, 
                                ON_EVENT handler, Creator creator)
{
    LockRW locker(_observers.locker, true);
    bool ret = type && obj && handler && creator && locker.canWrite();

    if (ret)
    {
        ObserverItem item;
        item.creator = creator;
        item.handler = NULL;
        item.obj = obj;
        item.objhandler = handler;
        _observers.insert(ObserverPair(type, item));
    }

    return ret;
}

int CPlugins::fireEvent(const char* type, EventDispatcher dispatcher, void* data)
{
    LockRW locker(_observers.locker);
    std::vector<PROC> observers;

    if (locker.canRead())
    {
        std::pair<MAP_IT, MAP_IT> range (_observers.equal_range(type));

        for (MAP_IT it = range.first; it != range.second; ++it)
        {
            if (it->second.handler)
            {
                observers.push_back(it->second.handler);
            }
        }
    }
    locker.free();

    int count = 0;
    std::vector<PROC>::iterator it = observers.begin();

    for (; it != observers.end(); ++it)
    {
        count++;
        if (!dispatcher(*it, data))
            break;
    }

    return count;
}

int CPlugins::fireEvent(const char* type, ObjectEventDispatcher dispatcher, void* data)
{
    LockRW locker(_observers.locker);
    typedef std::pair<ObserverObject*, ON_EVENT> Pair;
    std::vector<Pair> observers;

    if (locker.canRead())
    {
        std::pair<MAP_IT, MAP_IT> range (_observers.equal_range(type));

        for (MAP_IT it = range.first; it != range.second; ++it)
        {
            if (it->second.obj && it->second.objhandler)
            {
                observers.push_back(Pair(it->second.obj, it->second.objhandler));
            }
        }
    }
    locker.free();

    int count = 0;
    std::vector<Pair>::iterator it = observers.begin();

    for (; it != observers.end(); ++it)
    {
        count++;
        if (!dispatcher(it->first, it->second, data))
            break;
    }

    return count;
}

HMODULE CPlugins::findModuleByFileName(const char* filename)
{
    char tmp[MAX_PATH];
    LockRW locker(_plugins.locker);

    if (!locker.canRead())
    {
        return NULL;
    }

    for (std::vector<Plugin>::const_iterator it = _plugins.begin();
        it != _plugins.end(); ++it)
    {
        typedef bool (*F)(char*, int);
        F f = (F)GetProcAddress(it->second, "_getdlname");

        if (f && f(tmp, MAX_PATH) && _stricmp(tmp, filename) == 0)
        {
            return it->second;
        }
    }

    return NULL;
}

END_NAMESPACE_X3
