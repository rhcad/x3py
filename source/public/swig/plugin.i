/* plugin.i: included by swig projects.
   Define PLUGIN_NAME before include this file to auto load internal plugin.
*/
#ifndef X3_PLUGIN_SWIGI
#define X3_PLUGIN_SWIGI

%{
#include <portability/x3port.h>

#ifdef  PLUGIN_SWIG             // pluginimpl.h has been included
#undef  PLUGIN_NAME
#define PLUGIN_NAME "x3manager"
#define X3_EXCLUDE_CREATEOBJECT
#endif
#include <nonplugin/useplugin.h>    // load PLUGIN_NAME.pln when not use useplugins.h

#define X3THROW_NULLPOINTERERROR(name) \
    printf("NullPointerError occurs, interface name: %s\n", name); \
    throw x3::NullPointerError()
#include <objptr.h>
%}

%include <iobject.h>
%include <objptr.h>

%template(AnyObject) x3::Object<x3::IObject>;

#endif
