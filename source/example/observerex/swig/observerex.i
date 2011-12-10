%module(directors="1") observerex
%include "../../../public/swig/observer.i"

%{
#include <observerex/observerswig.h>
%}

%feature("director") ObserverDemo;
%include <observerex/observerswig.h>
