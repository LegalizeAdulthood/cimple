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

#include "dlfcn.h"
#include <windows.h>
#include <cstdio>

POSIX_NAMESPACE_BEGIN

static bool _dlerror_flag = false;
static char* _dlerror_message = NULL;

static void _set_dlerror()
{
    _dlerror_flag = true;

    // Free old error message:

    if (_dlerror_message)
    {
        LocalFree(_dlerror_message);
        _dlerror_message = NULL;
    }

    // Set new error message:

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&_dlerror_message,
        0,
        NULL);
}

void* dlopen(const char* path, int flags)
{
    HMODULE module = LoadLibrary(path);

    if (module == NULL)
    {
        _set_dlerror();
        return 0;
    }

    return module;
}

void* dlsym(void* handle, const char* symbol)
{
    FARPROC proc = GetProcAddress((HMODULE)handle, symbol);

    if (proc == NULL)
    {
        _set_dlerror();
        return 0;
    }

    return proc;
}

int dlclose(void* handle)
{
    FreeLibrary((HMODULE)handle);
    return 0;
}

char* dlerror()
{
    if (!_dlerror_flag)
        return NULL;

    _dlerror_flag = false;
    return _dlerror_message;
}

POSIX_NAMESPACE_END
