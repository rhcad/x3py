%module x3manager
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "x3manager"
#endif
%}
%include "../../../swig/plugin.i"

%{
#include <core/iplugins.h>
%}

%include std_vector.i
%include std_string.i
%template(Strings) std::vector<std::string>;

%include <core/iplugins.h>
%template(Plugins) x3::Object<x3::IPlugins>;

%include <core/x3manager.h>
