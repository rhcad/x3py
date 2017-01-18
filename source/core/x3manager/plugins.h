// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_PLUGINS_IMPL_H
#define X3_CORE_PLUGINS_IMPL_H

#include <module/classmacro.h>
#include <manager/iplugins.h>
#include <observer/observerobject.h>
#include <utilfunc/lockrw.h>
#include <utilfunc/vecfunc.h>

#include <unordered_map>	
using std::unordered_multimap;

BEGIN_NAMESPACE_X3

typedef bool (*EventDispatcher)(PROC handler, void* data);
typedef bool (*ObjectEventDispatcher)(ObserverObject*, ON_EVENT, void* data);
typedef bool (*Creator)(const char*, long, IObject**);

class IRegister : public IObject
{
	X3DEFINE_IID(IRegister);
	virtual bool registerPlugin(Creator creator, HMODULE hmod, const char** clsids) = 0;
	virtual void unregisterPlugin(Creator creator) = 0;	
	virtual bool createFromOthers(const char* clsid, long iid, IObject** p) = 0;
	virtual HMODULE findModuleByFileName(const char* filename) = 0;


	virtual bool registerObserver(const char* type, PROC handler, Creator creator) = 0;
	virtual bool registerObserver(const char* type, ObserverObject* obj, 
		ON_EVENT handler, Creator creator) = 0;
	virtual void unregisterObserver(ObserverObject* obj) = 0;
	virtual int fireEvent(const char* type, EventDispatcher dispatcher, void* data) = 0;
	virtual int fireEvent(const char* type, ObjectEventDispatcher dispatcher, void* data) = 0;
};

class CPlugins : public IPlugins
	, public IRegister
{
	X3BEGIN_CLASS_DECLARE0(CPlugins)
		X3DEFINE_INTERFACE_ENTRY(IPlugins)
		X3DEFINE_INTERFACE_ENTRY(IRegister)
	X3END_CLASS_DECLARE()
protected:
	CPlugins();
	virtual ~CPlugins();

private:
	virtual bool registerPlugin(Creator creator, HMODULE hmod, const char** clsids);
	virtual void unregisterPlugin(Creator creator);
	virtual bool createFromOthers(const char* clsid, long iid, IObject** p);
	virtual HMODULE findModuleByFileName(const char* filename);

	virtual bool registerObserver(const char* type, PROC handler, Creator creator);
	virtual bool registerObserver(const char* type, ObserverObject* obj, 
		ON_EVENT handler, Creator creator);
	virtual void unregisterObserver(ObserverObject* obj);
	virtual int fireEvent(const char* type, EventDispatcher dispatcher, void* data);
	virtual int fireEvent(const char* type, ObjectEventDispatcher dispatcher, void* data);

	virtual int getPluginCount() const;
	virtual void getPluginFiles(std::vector<std::string>& files) const;
	virtual Creator findPluginByClassID(const char* clsid) const;

private:
	typedef std::pair<Creator, HMODULE> Plugin;
	LockRW_<std::vector<Plugin> >               _plugins;
	LockRW_<std::unordered_map<std::string, Creator> >    _clsmap;
	LockRW_<std::unordered_map<long, std::string> >    _iidmap;

	struct ObserverItem {
		Creator         creator;
		PROC            handler;
		ObserverObject* obj;
		ON_EVENT        objhandler;

		ObserverItem() : creator(NULL), handler(NULL), obj(NULL), objhandler(NULL) {}
	};
	typedef unordered_multimap<std::string, ObserverItem> ObserverMap;
	typedef std::pair<std::string, ObserverItem> ObserverPair;
	typedef ObserverMap::iterator               MAP_IT;

	LockRW_<ObserverMap>                        _observers;
};

END_NAMESPACE_X3
#endif
