#ifndef X3_CORE_OBSERVEROBJECT_H
#define X3_CORE_OBSERVEROBJECT_H

namespace x3 {

class ObserverObject
{
public:
    virtual ~ObserverObject() {}
};

typedef void (ObserverObject::*ON_EVENT)();

} // x3
#endif