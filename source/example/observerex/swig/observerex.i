%module(directors="1") observerex
%{
#ifndef SELF_MODULE
#define SELF_MODULE "observerex"
#endif
%}
%include "../../../public/swig/observer.i"

%{
#include <observerex/observerswig.h>
%}

%feature("director") ObserverDemo;
%include <observerex/observerswig.h>
