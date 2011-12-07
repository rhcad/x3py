#include <module/plugininc.h>
#include "observerex.h"
#include <example/myevents.h>

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
    result += 1;
    return result <= 1;
}

bool OnBreakDemo2(int& result)
{
    result += 2;
    return result <= 2;
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

#include <example/myobserver.h>
#include <example/myobserverobj.h>

bool test()
{
    registerHandlers();

    if (FireEventAdd(0).fireEvent().param != 310)  // 10 + 100 + 200
        return false;

    CObserverTest objs[3];
    if (FireGatherEvent().fireEvent().param.size() != 3)
        return false;
    CObserverTest objextra;
    if (FireGatherEvent().fireEvent().param.size() != 4)
        return false;

    if (FireEventBreak(1).fireEvent().param != 2)
        return false;
    if (FireEventBreak(0).fireEvent().param != 3)
        return false;

    FireObjBreakEvent().fireEvent();

    return true;
}