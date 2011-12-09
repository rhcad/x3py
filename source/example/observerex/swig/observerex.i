%module(directors="1") observerex
%include "../../../swig/observer.i"

%{
#include <example/myobsv_swig.h>
%}

%feature("director") ObserverDemo;
%include <example/myobsv_swig.h>
