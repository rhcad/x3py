/*! \file pathstr.h
 *  \brief Included by portimpl.h to implement path functions.
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.5.23
 */
#ifndef X3_PORTABILITY_PATHSTR_IMPL_H
#define X3_PORTABILITY_PATHSTR_IMPL_H

static inline bool IsPathSlash(char c)
{
    return '\\' == c || '/' == c;
}

char* PathFindFileNameA(const char* path)
{
    const char* p1 = path ? strrchr(path, '\\') : NULL;
    const char* p2 = path ? strrchr(path, '/') : NULL;

    p1 = !p1 || (p2 && p2 > p1) ? p2 : p1;

    return const_cast<char*>(p1 ? p1 + 1 : path);
}

char* PathFindExtensionA(const char* path)
{
    char* p = PathFindFileNameA(path);
    char* ext = p ? strrchr(p, '.') : p;
    return ext ? ext : p;
}

bool PathIsRelativeA(const char* path)
{
    return path && strrchr(path, ':') == NULL && path[0] != '\\' && path[0] != '/';
}

void PathStripPathA(char* path)
{
    PathRemoveBackslashA(path);
    char* filename = PathFindFileNameA(path);

    if (filename && filename > path)
    {
        while (*filename)
        {
            *path++ = *filename++;
        }
        *path = *filename;
    }
}

void PathRemoveFileSpecA(char* path)
{
    PathRemoveBackslashA(path);
    char* filename = PathFindFileNameA(path);

    if (filename && filename > path)
    {
        *(filename - 1) = 0;
    }
}

void PathRemoveExtensionA(char* path)
{
    char* dot = path ? strrchr(path, '.') : NULL;

    if (dot)
    {
        *dot = 0;
    }
}

void PathRemoveBackslashA(char* path)
{
    size_t len = path ? strlen(path) : 0;

    if (len > 0 && IsPathSlash(path[len - 1]))
    {
        path[len - 1] = 0;
    }
}

void PathAppendA(char* path, const char* more)
{
    ASSERT(path && more);

    if (path[0] && '.' == more[0] && '.' == more[1])
    {
        PathRemoveFileSpecA(path);
        PathAppendA(path, more[2] ? more + 3 : more + 2);
        return;
    }

    size_t len = strlen(path);

    if (len > 0 && !IsPathSlash(path[len - 1]) && *more)
    {
        strcat(path, "/");
    }
    strcat(path, IsPathSlash(*more) ? more + 1 : more);
}

char* PathAddBackslashA(char* path)
{
    size_t len = path ? strlen(path) : 0;

    if (len > 0 && !IsPathSlash(path[len - 1]))
    {
        strcat(path, "/");
    }

    return path;
}

void PathRenameExtensionA(char* path, const char* more)
{
    ASSERT(path && more);
    char* dot = strrchr(path, '.');

    if (!dot)
    {
        dot = path + strlen(path);
    }
    strcpy(dot, more);
}

#endif