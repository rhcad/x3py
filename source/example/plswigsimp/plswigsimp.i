%module plswigsimp
%{
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "plswigsimp"
#define PLUGIN_SWIG
#endif
%}
%include "../../public/swig/plugin.i"

%{
#include <plswigsimp/isimple.h>
#include <plswigsimp/isimple2.h>
#include <plswigsimp/isimple3.h>
%}

%include <plswigsimp/isimple.h>
%template(Simple) x3::Object<ISimple>;

%include std_vector.i
%template(Ints) std::vector<int>;

%include <plswigsimp/isimple2.h>
%template(Simple2) x3::Object<ISimple2>;

%include <plswigsimp/isimple3.h>
%template(Simple3) x3::Object<ISimple3>;
