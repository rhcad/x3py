// Implement portability functions.
// This file has included by XModuleImpl.h and XComCreator.h

#ifndef X3_PORTABILITY_IMPL_H
#define X3_PORTABILITY_IMPL_H

#include "x3port.h"

#ifndef ASSERT
#define ASSERT(expr)
#define VERIFY(expr)  expr
#endif

#ifndef _INC_SHLWAPI
#include "pathstr.h"
#endif

#ifdef _WIN32
#include "winimpl.h"
#else
#include "uniximpl.h"
#endif

#endif