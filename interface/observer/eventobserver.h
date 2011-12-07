// Need to include <observer/observerimpl.h> in module.cpp
//
#ifndef X3_CORE_EVENTOBSERVER_H
#define X3_CORE_EVENTOBSERVER_H

#include <observer/observerobject.h>

namespace x3 {

bool registerObserver(const char* type, PROC handler);
bool registerObserver(const char* type, ObserverObject* obj, ON_EVENT handler);
void unregisterObserver(ObserverObject* obj);
bool fireEvent(const char* type, PROC dispatcher, void* data, bool obj);

} // x3


#ifndef JOIN
#  define JOIN(a,b) JOIN1(a,b)
#  define JOIN1(a,b) a##b
#endif

#define X3DEFINE_EVENT_TYPE(TypeName, Namespace)   \
    struct TypeName {   \
        static const char* getType() { return #TypeName "." Namespace; }    \
        typedef _##TypeName Handler;   \
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