#ifndef X3_EXAMPLE_MYOBSERVEROBJ_H
#define X3_EXAMPLE_MYOBSERVEROBJ_H

#include "myevents.h"
#include <observer/fireobjevent.h>

typedef x3::FireObjectEvent1<EventGather, std::vector<void*> >  FireGatherEvent;
typedef x3::FireObjectEvent0<EventObjBreakDemo, x3::FireObjectEvent0Break>  FireObjBreakEvent;

#endif