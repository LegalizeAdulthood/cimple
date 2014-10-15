/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include "util.h"
#include <sys/types.h>
#include <cstdarg>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>

using namespace std;

static const char* _arg0 = "unknown";

string toupper(const char* str)
{
    string r;
    r.reserve(strlen((char*)str));

    while (*str)
	r += char(::toupper(*str++));

    return r;
}

bool is_c_ident(const char* str)
{
    if (!isalpha(*str) && *str != '_')
        return false;

    for (str++; *str; str++)
    {
        if (!isalnum(*str) && *str != '_')
            return false;
    }

    return true;
}

void set_arg0(const char* arg0)
{
    _arg0 = arg0;
}

void err(const char* format, ...)
{
    fputc('\n', stderr);
    va_list ap;
    fprintf(stderr, "%s: ", _arg0);
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputc('\n', stderr);
    fputc('\n', stderr);
    exit(1);
}

void warn(const char* format, ...)
{
    fputc('\n', stderr);
    va_list ap;
    fprintf(stderr, "%s: ", _arg0);
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputc('\n', stderr);
    fputc('\n', stderr);
}

string basename_of(const char* path)
{
    const char* p = strrchr(path, '/');

    if (p)
        return p + 1;
    else
        return path;
}

bool exists(const char* path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

bool is_dir(const char* path)
{
    struct stat st;

    if (stat(path, &st) != 0)
        return false;

    return S_ISDIR(st.st_mode);
}
