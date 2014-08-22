// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_FIRE_EVENT_H
#define X3_CORE_FIRE_EVENT_H

#include <observer/eventobserver.h>

#define X3DEFINE_EVENT_0(TypeName, Namespace)   \
    X3DEFINE_EVENT(TypeName, void, (), Namespace);  \
    typedef x3::FireEvent0<TypeName> Fire ## TypeName

#define X3DEFINE_EVENT_0Break(TypeName, Namespace)   \
    X3DEFINE_EVENT(TypeName, bool, (), Namespace);  \
    typedef x3::FireEvent0<TypeName, x3::FireEvent0Break> Fire ## TypeName

#define X3DEFINE_EVENT_1(TypeName, ParamT, Namespace)   \
    X3DEFINE_EVENT(TypeName, void, (ParamT), Namespace);  \
    typedef x3::FireEvent1<TypeName, ParamT> Fire ## TypeName

#define X3DEFINE_EVENT_1Break(TypeName, ParamT, Namespace)   \
    X3DEFINE_EVENT(TypeName, bool, (ParamT), Namespace);  \
    typedef x3::FireEvent1<TypeName, ParamT, \
        x3::FireEvent1Break> Fire ## TypeName

#define X3DEFINE_EVENT_2(TypeName, Param1, Param2, Namespace)   \
    X3DEFINE_EVENT(TypeName, void, (Param1, Param2), Namespace);  \
    typedef x3::FireEvent2<TypeName, Param1, Param2> Fire ## TypeName

#define X3DEFINE_EVENT_2Break(TypeName, Param1, Param2, Namespace)   \
    X3DEFINE_EVENT(TypeName, bool, (Param1, Param2), Namespace);  \
    typedef x3::FireEvent2<TypeName, Param1, Param2, \
        x3::FireEvent2Break> Fire ## TypeName

// ----------------------------------------

namespace x3 {

template <class EventType> class FireEventBase
{
public:
    int     nhandled;

    bool handled() const { return nhandled > 0; }

protected:
    FireEventBase() : nhandled(0) {}

    typedef bool (*EventDispatcher)(PROC handler, void* data);

    template <typename Dispatcher>
    void _fireEvent(Dispatcher dispatcher) {
        nhandled = fireEvent(EventType::getType(), 
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
    typedef FireEventBase<EventType> Base;
    typedef FireEvent0<EventType, Break> This;
    FireEvent0() {}
    This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
    static bool dispatcher(PROC handler, void*) {
        return Break::call((typename EventType::Handler)handler);
    }
};

// -------------- FireEvent1 --------------

struct FireEvent1NotBreak {
    template <typename Handler, typename ParamT>
    static bool call(Handler handler, ParamT* param) {
        handler(*param); return true;
    }
};

struct FireEvent1Break {
    template <typename Handler, typename ParamT>
    static bool call(Handler handler, ParamT* param) {
        return !!handler(*param);
    }
};

template <class EventType, typename ParamT, class Break = FireEvent1NotBreak >
class FireEvent1 : public FireEventBase<EventType>
{
public:
    typedef FireEventBase<EventType> Base;
    typedef FireEvent1<EventType, ParamT, Break> This;
    ParamT  param;

    FireEvent1(ParamT p) : param(p) {}
    This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
    FireEvent1(const This&);
    This& operator=(const This&);
    FireEvent1();

    static bool dispatcher(PROC handler, void* data) {
        return Break::call((typename EventType::Handler)handler, &((This*)data)->param);
    }
};

// -------------- FireEvent2 --------------

struct FireEvent2NotBreak {
    template <typename Handler, typename Param1, typename Param2>
    static bool call(Handler handler, Param1* param1, Param2* param2) {
        handler(*param1, *param2); return true;
    }
};

struct FireEvent2Break {
    template <typename Handler, typename Param1, typename Param2>
    static bool call(Handler handler, Param1* param1, Param2* param2) {
        return !!handler(*param1, *param2);
    }
};

template <class EventType, typename Param1, 
          typename Param2 = Param1, class Break = FireEvent2NotBreak >
class FireEvent2 : public FireEventBase<EventType>
{
public:
    typedef FireEventBase<EventType> Base;
    typedef FireEvent2<EventType, Param1, Param2, Break> This;
    Param1  param1;
    Param2  param2;

    FireEvent2(Param1 p1, Param2 p2) : param1(p1), param2(p2) {}
    This& fireEvent() { Base::_fireEvent(dispatcher); return *this; }

private:
    FireEvent2(const This&);
    This& operator=(const This&);
    FireEvent2();

    static bool dispatcher(PROC handler, void* data) {
        This* p = (This*)data;
        return Break::call((typename EventType::Handler)handler, &p->param1, &p->param2);
    }
};

} // x3
#endif