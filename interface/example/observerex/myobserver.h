#ifndef X3_EXAMPLE_MYOBSERVER_H
#define X3_EXAMPLE_MYOBSERVER_H

#include "myevents.h"
#include <observer/fireevent.h>

typedef x3::FireEvent1<EventAdd, int>       FireEventAdd;
typedef x3::FireEvent2<EventAddExtra, int>  FireEventAddExtra;

typedef x3::FireEvent1<EventBreakDemo, int, x3::FireEvent1Break>  FireEventBreak;

#endif