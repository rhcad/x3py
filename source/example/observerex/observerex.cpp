#include <module/plugininc.h>
#include "observerex.h"
#include <observerex/myevents.h>

void OnEventAdd10(int& result)
{
    result += 10;
}

void OnEventAdd100(int& result)
{
    result += 100;
}

bool OnBreakDemo1(int& result)
{
    result += 10;
    return result <= 10;
}

bool OnBreakDemo2(int& result)
{
    result += 20;
    return result <= 20;
}

void registerHandlers()
{
    X3_REGISTER_OBSERVER(EventAdd, OnEventAdd10);
    X3_REGISTER_OBSERVER(EventAdd, OnEventAdd100);
    X3_REGISTER_OBSERVER(EventAdd, &CObserverTest::OnEventAdd);
    X3_REGISTER_OBSERVER(EventBreakDemo, OnBreakDemo1);
    X3_REGISTER_OBSERVER(EventBreakDemo, OnBreakDemo2);
}

CObserverTest::CObserverTest()
{
    X3_REGISTER_OBSERVER_OBJECT(EventGather, &CObserverTest::OnGather);
    X3_REGISTER_OBSERVER_OBJECT(EventObjBreakDemo, &CObserverTest::OnBreakDemo);
    X3_REGISTER_OBSERVER_OBJECT(EventVirtualDemo, &CObserverTest::OnVirtualDemo);
}

CObserverTest::~CObserverTest()
{
    x3::unregisterObserver(this);
}

void CObserverTest::OnEventAdd(int& result)
{
    result += 200;
}

void CObserverTest::OnGather(std::vector<void*>& objs)
{
    objs.push_back(this);
}

bool CObserverTest::OnBreakDemo()
{
    return false;
}

void CObserverTest::OnVirtualDemo(std::string& text, const std::string& intest)
{
    text = "a" + intest;
}

void CObserverTestEx::OnVirtualDemo(std::string& text, const std::string& intest)
{
    text = "b" + intest;
}

bool test()
{
    registerHandlers();

    int addvalue = 0;
    if (FireEventAdd(addvalue).fireEvent().param != 310)  // 10 + 100 + 200
        return false;

    CObserverTest objs[3];
    std::vector<void*> objsv;
    if (FireEventGather(objsv).fireEvent().param.size() != 3)
        return false;

    CObserverTest objextra;
    std::vector<void*> objsv2;
    if (FireEventGather(objsv2).fireEvent().param.size() != 4)    // 3+1
        return false;

    int demovalue = 1;
    if (FireEventBreakDemo(demovalue).fireEvent().param != 11)  // call OnBreakDemo1 once.
        return false;

    int demovalue2 = 0;
    if (FireEventBreakDemo(demovalue2).fireEvent().param != 30)  // call OnBreakDemo2 too.
        return false;

    if (FireEventObjBreakDemo().fireEvent().nhandled != 1)  // only once.
        return false;

    std::string text;
    if (FireEventVirtualDemo(text, "-").fireEvent().param1 != "a-")
        return false;

    CObserverTestEx testVirtual;
    std::string text2;
    if (FireEventVirtualDemo(text2, "-").fireEvent().param1 != "b-")
        return false;

    return true;
}
