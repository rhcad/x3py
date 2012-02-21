// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_NONPLUGIN_SWIG_EXT_H
#define X3_NONPLUGIN_SWIG_EXT_H

#if defined(SWIGPYTHON) || defined(SWIGCSHARP) || \
    defined(USE_PYTHON) || defined(USE_CSHARP)
    #define SELF_PRE "_"
#else
    #define SELF_PRE ""
#endif

#if defined(_WIN32) && (defined(SWIGPYTHON) || defined(USE_PYTHON))
    #define SELF_EXT ".pyd"
#elif !defined(SWIGINLINE)      // not in swig wrapper file.
    #define SELF_EXT ".pln"
#elif defined(_WIN32)
    #define SELF_EXT ".dll"
#else
    #define SELF_EXT ".so"
#endif

// the internal plugin (*.pln) 's relative folder base on the current module.
//
#ifndef PLUGIN_PATH
#ifdef  SWIGPYTHON                      // in python wrapper file.
#define CURMOD_IN_CWDSUBDIR             // see x3LoadLibrary() in uniximpl.h
#define PLUGIN_PATH "../../plugins/"    // python module has a package
#elif   defined(SWIGINLINE)             // in swig wrapper file.
#define PLUGIN_PATH "../plugins/"
#else
#define PLUGIN_PATH ""
#endif
#endif // PLUGIN_PATH

#endif
