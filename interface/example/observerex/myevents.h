#ifndef X3_EXAMPLE_MYOBSERVER_TYPES_H
#define X3_EXAMPLE_MYOBSERVER_TYPES_H

#include <observer/fireevent.h>

// void func(int& result)
X3DEFINE_EVENT_1(EventAdd, int&, "mypkg.x3");

// void func(int& result, int extra)
X3DEFINE_EVENT_2(EventAddExtra, int&, int, "mypkg.x3");

// bool func(int& result)
X3DEFINE_EVENT_1Break(EventBreakDemo, int&, "mypkg.x3");

#include <observer/fireobjevent.h>
#include <vector>
#include <string>

// void YourClass::func(std::vector<void*>& objs)
X3DEFINE_OBJEVENT_1(EventGather, std::vector<void*>&, "mypkg.x3");

// bool YourClass::func()
X3DEFINE_OBJEVENT_0Break(EventObjBreakDemo, "mypkg.x3");

// void YourClass::func(std::string& text, const std::string& intest)
X3DEFINE_OBJEVENT_2(EventVirtualDemo, std::string&, const std::string&, "mypkg.x3");

// void YourClass::func()
X3DEFINE_OBJEVENT_0(EventSwigVoid, "mypkg.x3");

#endif
