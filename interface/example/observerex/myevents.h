#ifndef X3_EXAMPLE_MYOBSERVER_TYPES_H
#define X3_EXAMPLE_MYOBSERVER_TYPES_H

#include <observer/eventobserver.h>
#include <vector>
#include <string>

// void func(int& result)
X3DEFINE_EVENT(EventAdd, void, (int& result), "mypkg.x3");

// void func(int& result, int extra)
X3DEFINE_EVENT(EventAddExtra, void, (int&, int), "mypkg.x3");

// bool func(int& result)
X3DEFINE_EVENT(EventBreakDemo, bool, (int&), "mypkg.x3");

// void YourClass::func(std::vector<void*>& objs)
X3DEFINE_OBJEVENT(EventGather, void, (std::vector<void*>&), "mypkg.x3");

// bool YourClass::func()
X3DEFINE_OBJEVENT(EventObjBreakDemo, bool, (void), "mypkg.x3");

// void YourClass::func(std::string& text)
X3DEFINE_OBJEVENT(EventVirtualDemo, void, (std::string&), "mypkg.x3");

// void YourClass::func()
X3DEFINE_OBJEVENT(EventSwigVoid, void, (), "mypkg.x3");

#endif
