%module plsimple
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "plsimple"
#endif
%}
%include "../../../swig/plugin.i"

%{
#include <example/isimple.h>
#include <example/isimple2.h>
#include <example/isimple3.h>
%}

%include <example/isimple.h>
%template(Simple) x3::Object<ISimple>;

%include std_vector.i
%template(Ints) std::vector<int>;

%include <example/isimple2.h>
%template(Simple2) x3::Object<ISimple2>;

%include <example/isimple3.h>
%template(Simple3) x3::Object<ISimple3>;
