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

#ifndef _log_h
#define _log_h

#include <cstdio>
#include <cstdlib>
#include <cstdarg>


inline void __log(const char* format, ...)
{
    const char PATH[] = "C:\\PersonProvider.log";

    FILE* os = fopen(PATH, "a");

    if (!os)
        return;

    va_list ap;
    va_start(ap, format);
    vfprintf(os, format, ap);
    va_end(ap);
    fprintf(os, "\n");
    fflush(os);

    fclose(os);
}
#if 1
#  define LOG_DATA(ARGS) __log(ARGS)
#  define LOG_TRACE __log("LOG_TRACE: %s(%d)", __FILE__, __LINE__)
#  define LOG_ENTER __log("LOG_ENTER: %s(%d) %s", __FILE__, __LINE__, CIMPLE_FUNCTION)
#  define LOG_EXIT __log("LOG_EXIT: %s(%d) %s", __FILE__, __LINE__, CIMPLE_FUNCTION)
#else
#  define LOG_DATA
#  define LOG_TRACE
#  define LOG_ENTER
#  define LOG_EXIT
#endif

#endif /* _log_h */
