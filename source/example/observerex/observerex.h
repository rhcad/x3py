#ifndef X3_EXAMPLE_OBSERVEREX_H
#define X3_EXAMPLE_OBSERVEREX_H

#include <observer/observerobject.h>
#include <vector>

class CObserverTest : x3::ObserverObject
{
public:
    CObserverTest();
    virtual ~CObserverTest();

    static void OnEventAdd(int& result);

private:
    void OnGather(std::vector<void*>& objs);
    bool OnBreakDemo();
    virtual void OnVirtualDemo(std::string& text);
};

class CObserverTestEx : public CObserverTest
{
public:
    CObserverTestEx() {}

private:
    virtual void OnVirtualDemo(std::string& text);
};

bool test();

#endif