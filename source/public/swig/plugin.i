/* plugin.i: included by swig projects.
   Define PLUGIN_NAME before include this file to auto load internal plugin.
*/
#ifndef X3_PLUGIN_SWIGI
#define X3_PLUGIN_SWIGI

%{
#include <portability/x3port.h>
#include <nonplugin/useplugin.h>

#define X3THROW_NULLPOINTERERROR(name) \
    printf("NullPointerError occurs, interface name: %s\n", name); \
    throw x3::NullPointerError()
#include <objptr.h>
%}

%include <iobject.h>
%include <objptr.h>

%template(AnyObject) x3::Object<x3::IObject>;

#endif
