%module examples
%{
#include <portability/x3port.h>
#define SELF_MODULE  "examples"
#include <nonplugin/useplugins.h>

static const char* plugins[] = {
    "x3manager.pln", "plsimple.pln", "observerex.pln", "mfcwnd.pln", NULL };
static x3::AutoLoadPlugins autoload(plugins, PLUGIN_PATH);
%}
%include "../../core/x3manager/swig/x3manager.i"
%include "../../example/plsimple/plsimple.i"
%include "../../example/observerex/observerex.i"
