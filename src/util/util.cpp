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

#include "util.h"
#include <sys/types.h>
#include <cimple/config.h>
#include <cstdarg>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>

#ifdef CIMPLE_WINDOWS
# include <windows.h>
#endif

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
    fprintf(stderr, "%s[%s]: ", _arg0, CIMPLE_VERSION_STRING);
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

string base_name(const string& path)
{
    const char* p = strrchr(path.c_str(), '/');

    if (p)
        return string(p + 1);
    else
        return path;
}

bool exists(const string& path)
{
    return access(path.c_str(), F_OK) == 0;
}

bool is_dir(const char* path)
{
#ifdef CIMPLE_WINDOWS

    char cwd[1024];
    DWORD r = GetCurrentDirectory(sizeof(cwd), cwd);

    if (r == 0 || r > sizeof(cwd))
        return false;

    BOOL flag = SetCurrentDirectory(path);

    if (flag)
        SetCurrentDirectory(cwd);

    return flag;

#else

    struct stat st;

    if (stat(path, &st) != 0)
        return false;

    return S_ISDIR(st.st_mode);

#endif
}

bool is_absolute(const char* p)
{
#ifdef CIMPLE_WINDOWS
    return p[0] == '/' || (isalpha(p[0]) && p[1] == ':' && p[2] == '/');
#else
    return p[0] == '/';
#endif
}


string shlib_name(const string& name)
{
#ifdef CIMPLE_WINDOWS
    return name + string(".dll");
#else
    return string("lib") + name + string(".so");
#endif
}

string shlib_dir(const string& root)
{
#ifdef CIMPLE_WINDOWS
    return root + string("/bin/");
#else
    return root + string("/lib/");
#endif
}

string full_shlib_name(const string& root, const string& name)
{
    return shlib_dir(root) + shlib_name(name);
}

string shlib_basename(const string& path)
{
    string base = base_name(path);

    size_t dot = base.find('.');

    if (dot != (size_t)-1)
        base.erase(dot);

#ifdef CIMPLE_UNIX

    if (base.substr(0, 3) == "lib")
        base.erase(0, 3);

#endif

    return base;
}

