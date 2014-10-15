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

#include "config.h"
#include <cstdarg>
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

char* str_printf(const char* format, ...)
{
    int n;
    int size = 128;
    char *p;
    va_list ap;

    if ((p = (char*)malloc(size)) == NULL)
        return 0;

    for (;;)
    {
        va_start(ap, format);
        n = vsnprintf(p, size, format, ap);
        va_end(ap);

        if (n > -1 && n < size)
            return p;

        if (n > -1)
            size = n + 1;
        else
            size *= 2;

        if ((p = (char*)realloc(p, size)) == NULL)
            return 0;
    }

    return 0;
}

char* str_vprintf(const char* format, va_list ap)
{
    int n;
    int size = 128;
    char *p;

    if ((p = (char*)malloc(size)) == NULL)
        return 0;

    for (;;)
    {
        n = vsnprintf(p, size, format, ap);

        if (n > -1 && n < size)
            return p;

        if (n > -1)
            size = n + 1;
        else
            size *= 2;

        if ((p = (char*)realloc(p, size)) == NULL)
            return 0;
    }

    return 0;
}

int ifprintf(FILE* os, size_t level, const char* format, ...)
{
    fprintf(os, "%*s", int(level * 4), "");

    va_list ap;
    va_start(ap, format);
    int r = vfprintf(os, format, ap);
    va_end(ap);

    return r;
}

int iprintf(size_t level, const char* format, ...)
{
    printf("%*s", int(level * 4), "");

    va_list ap;
    va_start(ap, format);
    int r = vprintf(format, ap);
    va_end(ap);

    return r;
}

CIMPLE_NAMESPACE_END

