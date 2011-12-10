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

void CObserverTest::OnVirtualDemo(std::string& text)
{
    text = "a";
}

void CObserverTestEx::OnVirtualDemo(std::string& text)
{
    text = "b";
}

#include <observerex/myobserver.h>
#include <observerex/myobserverobj.h>

bool test()
{
    registerHandlers();

    if (FireEventAdd(0).fireEvent().param != 310)  // 10 + 100 + 200
        return false;

    CObserverTest objs[3];
    if (FireGatherEvent().fireEvent().param.size() != 3)
        return false;

    CObserverTest objextra;
    if (FireGatherEvent().fireEvent().param.size() != 4)    // 3+1
        return false;

    if (FireEventBreak(1).fireEvent().param != 11)  // call OnBreakDemo1 once.
        return false;
    if (FireEventBreak(0).fireEvent().param != 30)  // call OnBreakDemo2 too.
        return false;

    if (FireObjBreakEvent().fireEvent().nhandled != 1)  // only once.
        return false;

    if (FireVirtualDemoEvent().fireEvent().param != "a")
        return false;
    CObserverTestEx testVirtual;
    if (FireVirtualDemoEvent().fireEvent().param != "b")
        return false;

    return true;
}
