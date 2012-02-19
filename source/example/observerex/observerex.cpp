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

int registerHandlers()
{
    int count = 0;

    count += X3_REGISTER_OBSERVER(EventAdd, OnEventAdd10) ? 1 : 0;
    count += X3_REGISTER_OBSERVER(EventAdd, OnEventAdd100) ? 1 : 0;
    count += X3_REGISTER_OBSERVER(EventBreakDemo, OnBreakDemo1) ? 1 : 0;
    count += X3_REGISTER_OBSERVER(EventBreakDemo, OnBreakDemo2) ? 1 : 0;

    CObserverTest::registerHandlers();

    return count;
}

void CObserverTest::registerHandlers()
{
    X3_REGISTER_OBSERVER(EventAdd, &CObserverTest::OnEventAdd);
    X3_REGISTER_OBSERVER(EventAdd, &CObserverTest::OnEventAdd2);
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

void CObserverTest::OnEventAdd2(int& result)
{
    result += 0;
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

#include <stdio.h>

bool test()
{
    int regcount = registerHandlers();
    printf("[observerex] registerHandlers: %d\n", regcount);

    int addvalue = 0;
    if (FireEventAdd(addvalue).fireEvent().param != 310)  // 10 + 100 + 200
    {
        printf("[observerex] Test fail: FireEventAdd, %d\n", addvalue);
        return false;
    }

    CObserverTest objs[3];
    std::vector<void*> objsv;
    if (FireEventGather(objsv).fireEvent().param.size() != 3)
    {
        printf("[observerex] Test fail: FireEventGather\n");
        return false;
    }

    CObserverTest objextra;
    std::vector<void*> objsv2;
    if (FireEventGather(objsv2).fireEvent().param.size() != 4)  // 3+1
    {
        printf("[observerex] Test fail: FireEventGather2\n");
        return false;
    }

    int demovalue = 1;
    if (FireEventBreakDemo(demovalue).fireEvent().param != 11)  // call OnBreakDemo1 once.
    {
        printf("[observerex] Test fail: FireEventBreakDemo\n");
        return false;
    }

    int demovalue2 = 0;
    if (FireEventBreakDemo(demovalue2).fireEvent().param != 30) // call OnBreakDemo2 too.
    {
        printf("[observerex] Test fail: FireEventBreakDemo2\n");
        return false;
    }

    if (FireEventObjBreakDemo().fireEvent().nhandled != 1)      // only once.
    {
        printf("[observerex] Test fail: FireEventObjBreakDemo\n");
        return false;
    }

    std::string text;
    if (FireEventVirtualDemo(text, "-").fireEvent().param1 != "a-")
    {
        printf("[observerex] Test fail: FireEventVirtualDemo\n");
        return false;
    }

    CObserverTestEx testVirtual;
    std::string text2;
    if (FireEventVirtualDemo(text2, "-").fireEvent().param1 != "b-")
    {
        printf("[observerex] Test fail: FireEventVirtualDemo2\n");
        return false;
    }

    return true;
}
