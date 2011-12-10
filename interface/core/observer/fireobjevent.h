#ifndef X3_CORE_FIRE_OBJECT_EVENT_H
#define X3_CORE_FIRE_OBJECT_EVENT_H

#include <observer/eventobserver.h>

namespace x3 {

template <class EventType> class FireObjEventBase
{
public:
    int     nhandled;

    bool handled() const { return nhandled > 0; }

protected:
    FireObjEventBase() : nhandled(0) {}

    typedef bool (*EventDispatcher)(ObserverObject*, ON_EVENT, void* data);

    template <typename Dispatcher>
    void _fireEvent(Dispatcher dispatcher) {
        nhandled = fireEvent(EventType::getType(), 
            (PROC)static_cast<EventDispatcher>(dispatcher), this, true);
    }

    template <typename Handler>
    static void cast(Handler& result, ON_EVENT handler) {
        union Funcs {
            ON_EVENT    pfn;
            Handler     handler;
        };
        Funcs f;
        f.pfn = handler;
        result = f.handler;
    }
};

// -------------- FireObjectEvent0 --------------

struct FireObjectEvent0NotBreak {
    template <typename Handler>
    static bool call(ObserverObject* obj, Handler handler) {
        (obj->*handler)(); return true;
    }
};

struct FireObjectEvent0Break {
    template <typename Handler>
    static bool call(ObserverObject* obj, Handler handler) {
        return !!(obj->*handler)();
    }
};

template <class EventType, class Break = FireObjectEvent0NotBreak >
class FireObjectEvent0 : public FireObjEventBase<EventType>
{
public:
    typedef FireObjectEvent0<EventType, Break> This;
    FireObjectEvent0() {}
    This& fireEvent() { _fireEvent(dispatcher); return *this; }

private:
    static bool dispatcher(ObserverObject* obj, ON_EVENT hd, void*) {
        typename EventType::Handler handler;
        cast(handler, hd);
        return Break::call(obj, handler);
    }
};

// -------------- FireObjectEvent1 --------------

struct FireObjectEvent1NotBreak {
    template <typename Handler, typename ParamT>
    static bool call(ObserverObject* obj, Handler hd, ParamT& param) {
        (obj->*hd)(param); return true;
    }
};

struct FireObjectEvent1Break {
    template <typename Handler, typename ParamT>
    static bool call(ObserverObject* obj, Handler hd, ParamT& param) {
        return !!(obj->*hd)(param);
    }
};

template <class EventType, typename ParamT, class Break = FireObjectEvent1NotBreak>
class FireObjectEvent1 : public FireObjEventBase<EventType>
{
public:
    typedef FireObjectEvent1<EventType, ParamT, Break> This;
    ParamT  param;

    FireObjectEvent1() {}
    FireObjectEvent1(const ParamT& p) : param(p) {}
    This& fireEvent() { _fireEvent(dispatcher); return *this; }

private:
    FireObjectEvent1(const This&);
    This& operator=(const This&);

    static bool dispatcher(ObserverObject* obj, ON_EVENT hd, void* data) {
        typename EventType::Handler handler;
        cast(handler, hd);
        return Break::call(obj, handler, ((This*)data)->param);
    }
};

// -------------- FireObjectEvent2 --------------

struct FireObjectEvent2NotBreak {
    template <typename Handler, typename Param1, typename Param2>
    static bool call(ObserverObject* obj, Handler hd, Param1& p1, Param2& p2) {
        (obj->*hd)(p1, p2); return true;
    }
};

struct FireObjectEvent2Break {
    template <typename Handler, typename Param1, typename Param2>
    static bool call(ObserverObject* obj, Handler hd, Param1& p1, Param2& p2) {
        return !!(obj->*hd)(p1, p2);
    }
};

template <class EventType, typename Param1, typename Param2 = Param1, 
          class Break = FireObjectEvent2NotBreak >
class FireObjectEvent2 : public FireObjEventBase<EventType>
{
public:
    typedef FireObjectEvent2<EventType, Param1, Param2, Break> This;
    Param1  param1;
    Param2  param2;

    FireObjectEvent2() {}
    FireObjectEvent2(const Param1& p1, const Param2& p2) : param1(p1), param2(p2) {}
    This& fireEvent() { _fireEvent(dispatcher); return *this; }

private:
    FireObjectEvent2(const This&);
    This& operator=(const This&);

    static bool dispatcher(ObserverObject* obj, ON_EVENT hd, void* data)
    {
        This* p = (This*)data;
        typename EventType::Handler handler;

        cast(handler, hd);
        return Break::call(obj, handler, p->param1, p->param2);
    }
};

} // x3
#endif