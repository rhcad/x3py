#ifndef X3_CORE_FIRE_EVENT_H
#define X3_CORE_FIRE_EVENT_H

#include <observer/eventobserver.h>

namespace x3 {

template <class EventType> class FireEventBase
{
public:
    bool    handled;

protected:
    FireEventBase() : handled(false) {}

    typedef bool (*EventDispatcher)(PROC handler, void* data);

    template <typename Dispatcher>
    void _fireEvent(Dispatcher dispatcher) {
        handled = fireEvent(EventType::getType(), 
            (PROC)static_cast<EventDispatcher>(dispatcher), this, false);
    }
};

// -------------- FireEvent0 --------------

struct FireEvent0NotBreak {
    template <typename Handler>
    static bool call(Handler handler) { handler(); return true; }
};

struct FireEvent0Break {
    template <typename Handler>
    static bool call(Handler handler) { return !!handler(); }
};

template <class EventType, class Break = FireEvent0NotBreak >
class FireEvent0 : public FireEventBase<EventType>
{
public:
    typedef FireEvent0<EventType, Break> This;
    FireEvent0() {}
    This& fireEvent() { _fireEvent(dispatcher); return *this; }

private:
    static bool dispatcher(PROC handler, void*) {
        return Break::call((typename EventType::Handler)handler);
    }
};

// -------------- FireEvent1 --------------

struct FireEvent1NotBreak {
    template <typename Handler, typename ParamT>
    static bool call(Handler handler, ParamT& param) {
        handler(param); return true;
    }
};

struct FireEvent1Break {
    template <typename Handler, typename ParamT>
    static bool call(Handler handler, ParamT& param) {
        return !!handler(param);
    }
};

template <class EventType, typename ParamT, class Break = FireEvent1NotBreak >
class FireEvent1 : public FireEventBase<EventType>
{
public:
    typedef FireEvent1<EventType, ParamT, Break> This;
    ParamT  param;

    FireEvent1() {}
    FireEvent1(const ParamT& p) : param(p) {}
    This& fireEvent() { _fireEvent(dispatcher); return *this; }

private:
    FireEvent1(const This&);
    This& operator=(const This&);

    static bool dispatcher(PROC handler, void* data) {
        return Break::call((typename EventType::Handler)handler, ((This*)data)->param);
    }
};

// -------------- FireEvent2 --------------

struct FireEvent2NotBreak {
    template <typename Handler, typename Param1, typename Param2>
    static bool call(Handler handler, Param1& param1, Param2& param2) {
        handler(param1, param2); return true;
    }
};

struct FireEvent2Break {
    template <typename Handler, typename Param1, typename Param2>
    static bool call(Handler handler, Param1& param1, Param2& param2) {
        return !!handler(param1, param2);
    }
};

template <class EventType, typename Param1, 
          typename Param2 = Param1, class Break = FireEvent2NotBreak >
class FireEvent2 : public FireEventBase<EventType>
{
public:
    typedef FireEvent2<EventType, Param1, Param2, Break> This;
    Param1  param1;
    Param2  param2;

    FireEvent2() {}
    FireEvent2(const Param1& p1, const Param2& p2) : param1(p1), param2(p2) {}
    This& fireEvent() { _fireEvent(dispatcher); return *this; }

private:
    FireEvent2(const This&);
    This& operator=(const This&);

    static bool dispatcher(PROC handler, void* data) {
        This* p = (This*)data;
        return Break::call((typename EventType::Handler)handler, p->param1, p->param2);
    }
};

} // x3
#endif