#ifndef X3_CORE_PORTABILITY_H
#define X3_CORE_PORTABILITY_H

#if defined(_WIN64) && !defined(_WIN32)
#define _WIN32
#endif

#ifdef _WIN32
#include "x3win.h"
#else
#include "x3unix.h"
#endif

#if !defined(_MSC_VER) || _MSC_VER < 1400
#include "func_s.h"
#endif

HMODULE x3LoadLibrary(const char* filename);
bool x3FreeLibrary(HMODULE hdll);

#ifndef _INC_SHLWAPI
char* PathFindFileNameA(const char* path);
char* PathFindExtensionA(const char* path);
bool PathIsRelativeA(const char* path);
void PathStripPathA(char* path);
void PathRemoveFileSpecA(char* path);
void PathRemoveExtensionA(char* path);
void PathRemoveBackslashA(char* path);
void PathAppendA(char* path, const char* more);
char* PathAddBackslashA(char* path);
void PathRenameExtensionA(char* path, const char* more);
#endif

#endif