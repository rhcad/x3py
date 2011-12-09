/* observer.i: included by swig projects which use eventobserver.h .*/
#ifndef X3_OBSERVER_PLUGIN_SWIGI
#define X3_OBSERVER_PLUGIN_SWIGI

%include "plugin.i"

%{
#include <module/modulemacro.h>
#include <module/pluginimpl.h>
#include <observer/observerimpl.h>
XDEFINE_EMPTY_MODULE()

#include <example/myobserver.h>
#include <example/myobserverobj.h>
%}

%include <observer/observerobject.h>

#endif
