// x3py framework: https://github.com/rhcad/x3py
// Need to include <observer/observerimpl.h> in module.cpp
//
#ifndef X3_CORE_EVENTOBSERVER_H
#define X3_CORE_EVENTOBSERVER_H

#include <observer/observerobject.h>

namespace x3 {

bool registerObserver(const char* type, PROC handler);
bool registerObserver(const char* type, ObserverObject* obj, ON_EVENT handler);
void unregisterObserver(ObserverObject* obj);
int fireEvent(const char* type, PROC dispatcher, void* data, bool obj);

} // x3


#ifndef JOIN
#  define JOIN(a,b) JOIN1(a,b)
#  define JOIN1(a,b) a##b
#endif

// Declare a event type.
// Return: return type of the handler function, such as void or bool.
// Params: param types of the handler function. eg: (void), (int&), (int, char c).
// Namespace: extra string of event type.
#define X3DEFINE_EVENT(TypeName, Return, Params, Namespace)   \
    struct TypeName {   \
        static const char* getType() { return #TypeName "." Namespace; }    \
        typedef Return (*Handler)Params;   \
    }

// Declare a event type for classes derived from ObserverObject.
#define X3DEFINE_OBJEVENT(TypeName, Return, Params, Namespace)   \
    struct TypeName {   \
        static const char* getType() { return #TypeName "." Namespace; }    \
        typedef Return (x3::ObserverObject::*Handler)Params;   \
    }

// Register a handler function in x3InitializePlugin().
// handler: local function or static member function.
#define X3_REGISTER_OBSERVER(TypeName, handler)  \
    x3::registerObserver(TypeName::getType(), \
        (PROC)static_cast<TypeName::Handler>(handler))

// Register a member function and object in the constructor function.
// handler: member function of a class derived from x3::ObserverObject.
// Note: must callHandler x3::unregisterObserver(this) in the destructor function.
#define X3_REGISTER_OBSERVER_OBJECT(TypeName, handler)  \
    x3::registerObserver(TypeName::getType(), this, \
        (x3::ON_EVENT)static_cast<TypeName::Handler>(handler))

#endif