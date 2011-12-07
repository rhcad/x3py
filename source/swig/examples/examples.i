%module examples
%{
#include <portability/portimpl.h>
#define PLUGIN_PATH  "../plugins"
#define SELF_MODULE  "examples"
#include <nonplugin/useplugins.h>

static const char* plugins[] = {
    "x3manager.pln", "plsimple.pln", "observerex.pln", NULL };
static x3::AutoLoadPlugins autoload(plugins);
%}
%include "../../core/x3manager/swig/x3manager.i"
%include "../../example/plsimple/swig/plsimple.i"
%include "../../example/observerex/swig/observerex.i"
