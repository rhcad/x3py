%module plsimple
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "plsimple"
#endif
%}
%include <swig/plugin.i>

%{
#include <plsimple/isimple.h>
#include <plsimple/isimple2.h>
#include <plsimple/isimple3.h>
%}

%include <plsimple/isimple.h>
%template(Simple) x3::Object<ISimple>;

%include std_vector.i
%template(Ints) std::vector<int>;

%include <plsimple/isimple2.h>
%template(Simple2) x3::Object<ISimple2>;

%include <plsimple/isimple3.h>
%template(Simple3) x3::Object<ISimple3>;
