// Included by X3Portability.h to declare functions on linux or macosx.

#ifndef X3UNIX_PORTABILITY_H
#define X3UNIX_PORTABILITY_H

#include <string.h>
#include <stdlib.h>

#define OUTAPI      extern "C" __attribute__((visibility("default")))
#define LOCALAPI    __attribute__((visibility("hidden")))

#ifndef MAX_PATH
#define MAX_PATH    512
#endif

typedef void* HMODULE;
typedef void* HANDLE;
typedef void* HWND;
typedef void* PROC;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef DWORD ULONG;

long InterlockedIncrement(long* p);
long InterlockedDecrement(long* p);
long InterlockedExchange(long* p, long v);

bool x3FreeLibrary(HMODULE hdll);
HMODULE x3LoadLibrary(const char* filename);
HMODULE GetModuleHandleA(const char* filename);
PROC GetProcAddress(HMODULE hdll, const char* name);
void GetModuleFileNameA(HMODULE hdll, char* filename, int size);
DWORD GetLastError();

int WideCharToMultiByte(int codepage, DWORD flags,
                        const wchar_t* wstr, int wchars,
                        char* astr, int achars,
                        const char* defaultChar, void*);
int MultiByteToWideChar(int codepage, DWORD flags,
                        const char* astr, int achars,
                        wchar_t* wstr, int wchars);

int _stricmp(const char* s1, const char* s2);
int _strnicmp(const char* s1, const char* s2, int count);

#endif