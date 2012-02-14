%module pltempl
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "pltempl"
#endif
%}
%include <swig/plugin.i>

%{
#include <pltempl/isimple.h>
%}

%include <pltempl/isimple.h>
%template(Simple) x3::Object<ISimple>;
