/* plugin.i: included by swig projects.
   Define PLUGIN_NAME before include this file to auto load internal plugin.
*/
#ifndef X3_PLUGIN_SWIGI
#define X3_PLUGIN_SWIGI
%{
#include <portability/portimpl.h>
#ifndef PLUGIN_PATH
#define PLUGIN_PATH "../plugins/"
#endif
#include <nonplugin/useplugin.h>
%}

%include <iobject.h>
%include <objptr.h>

%template(AnyObject) x3::Object<x3::IObject>;

#endif
