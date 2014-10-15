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
#include "String.h"

CIMPLE_NAMESPACE_BEGIN

// formatting function that returns a CIMPLE string. 
String string_printf(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    char* rtn;
    rtn = str_vprintf(format, ap);
    va_end(ap);
    String rtn_string(rtn);
    free(rtn);
    return(rtn_string);
}

// formatter that appends formatted output to existing string
void string_append_printf(String& str, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    char* rtn;
    rtn = str_vprintf(format, ap);
    va_end(ap);
    str.append(rtn);
    //String rtn_string(rtn);
    free(rtn);
}
// formatting function that returns char pointer.  This function
// allocates memory for the return char*. The user is responsible for
// freeing that memory.
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
    // unreachable
    return 0;
}

//  function to return a formatted char*  from a va_list.
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
    // unreachable
    return 0;
}

String string_vprintf(const char* format, va_list ap)
{
    char *rtn = str_vprintf(format, ap);
    String return_String(rtn);
    free(rtn);
    return(return_String);
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

void istring_printf(String& str, size_t level, const char* format, ...)
{
    string_append_printf(str, "%*s", int(level * 4), "");
    //printf("%*s", int(level * 4), "");

    va_list ap;
    va_start(ap, format);
    String data = string_vprintf(format, ap);
    va_end(ap);

    str.append(data);

    return;
}

CIMPLE_NAMESPACE_END

