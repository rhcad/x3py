#ifndef X3_EXAMPLE_OBSERVEREX_H
#define X3_EXAMPLE_OBSERVEREX_H

#include <observer/observerobject.h>
#include <vector>
#include <string>

class CObserverTest : x3::ObserverObject
{
public:
    CObserverTest();
    virtual ~CObserverTest();

    static void registerHandlers();

private:
    static void OnEventAdd(int& result);
    static void OnEventAdd2(int& result);

    void OnGather(std::vector<void*>& objs);
    bool OnBreakDemo();
    virtual void OnVirtualDemo(std::string& text, const std::string& intest);
};

class CObserverTestEx : public CObserverTest
{
public:
    CObserverTestEx() {}

private:
    virtual void OnVirtualDemo(std::string& text, const std::string& intest);
};

#endif