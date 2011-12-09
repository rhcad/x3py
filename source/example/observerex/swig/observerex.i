%module(directors="1") observerex
%include "../../../swig/observer.i"

%{
#include "observerex.h"
%}

%feature("director") ObserverDemo;
%include "observerex.h"
