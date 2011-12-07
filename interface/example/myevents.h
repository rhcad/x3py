#ifndef X3_EXAMPLE_MYOBSERVER_TYPES_H
#define X3_EXAMPLE_MYOBSERVER_TYPES_H

#include <observer/eventobserver.h>

#define MYEVENT_NAMESPACE "example.myapp"

typedef void (*_EventAdd)(int& result);
X3DEFINE_EVENT_TYPE(EventAdd, MYEVENT_NAMESPACE);

typedef void (*_EventAddExtra)(int& result, int extra);
X3DEFINE_EVENT_TYPE(EventAddExtra, MYEVENT_NAMESPACE);

typedef bool (*_EventBreakDemo)(int& result);
X3DEFINE_EVENT_TYPE(EventBreakDemo, MYEVENT_NAMESPACE);

typedef void (x3::ObserverObject::*_EventGather)(std::vector<void*>& objs);
X3DEFINE_EVENT_TYPE(EventGather, MYEVENT_NAMESPACE);

typedef bool (x3::ObserverObject::*_EventObjBreakDemo)(void);
X3DEFINE_EVENT_TYPE(EventObjBreakDemo, MYEVENT_NAMESPACE);

#endif