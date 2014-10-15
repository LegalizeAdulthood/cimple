/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#include "dirent.h"
#include <cstdio>
#include <windows.h>
#include <io.h>

POSIX_NAMESPACE_BEGIN

struct DIR
{
#if _MSC_VER < 1300
    long handle;
#else
    intptr_t handle;
#endif
    struct _finddata_t data;
    dirent ent;
    bool first;
};

DIR* opendir(const char* path)
{
    DIR* dir = new DIR;

    char* pattern = (char*)malloc(strlen(path) + 3);
    strcpy(pattern, path);
    strcat(pattern, "/*");

    if ((dir->handle = _findfirst(pattern, &dir->data)) == -1)
    {
        delete dir;
        free(pattern);
        return NULL;
    }

    free(pattern);
    dir->first = true;
    return dir;
}

dirent* readdir(DIR* dir)
{
    if (dir->first)
    {
        dir->first = false;
        dir->ent.d_name = dir->data.name;
        return &dir->ent;
    }

    if (_findnext(dir->handle, &dir->data) != 0)
        return NULL;

    return &dir->ent;
}

int closedir(DIR* dir)
{
    if (dir && dir->handle != -1)
    {
        _findclose(dir->handle);
        delete dir;
        return 0;
    }

    return -1;
}

POSIX_NAMESPACE_END
