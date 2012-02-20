%module mfcwnd
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "mfcwnd"
#endif
%}
%include <swig/plugin.i>

%{
#include <mfcwnd/isimple.h>
%}

%include <mfcwnd/isimple.h>
%template(Simple) x3::Object<ISimple>;
