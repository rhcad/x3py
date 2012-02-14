/* observer.i: included by swig projects which use eventobserver.h .*/
#ifndef X3_OBSERVER_PLUGIN_SWIGI
#define X3_OBSERVER_PLUGIN_SWIGI

%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "x3manager"
#endif
%}
%include <swig/plugin.i>

%{
#ifndef PLUGIN_SWIG
#include <observer/observerimpl.h>
#endif
%}

%include <observer/observerobject.h>

#endif
