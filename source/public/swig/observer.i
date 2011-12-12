/* observer.i: included by swig projects which use eventobserver.h .*/
#ifndef X3_OBSERVER_PLUGIN_SWIGI
#define X3_OBSERVER_PLUGIN_SWIGI

%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "x3manager"
#endif
%}
%include "plugin.i"

%{
#include <observer/observerimpl.h>
%}

%include <observer/observerobject.h>

#endif
