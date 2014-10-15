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

#ifdef __USE_GNU
#  include <execinfo.h>
#endif

int __CIMPLE_VERSION_SYMBOL(CIMPLE_MAJOR, CIMPLE_MINOR, CIMPLE_REVISION);

CIMPLE_NAMESPACE_BEGIN

void __cimple_assert(
    const char* file, 
    size_t line, 
    const char* function,
    const char* cond)
{
    // Print general assertion failure message:

    fprintf(stderr, "%s(%d): %s(): assert: %s\n\n", 
        file, int(line), function, cond);

#if defined(USE_BACKTRACE) && defined(__USE_GNU)

    // Print backtrace:

    void *array[1024];
    size_t size;
    char **strings;

    size = backtrace (array, 1024);
    strings = backtrace_symbols (array, size);

    for (size_t i = 0; i < size; i++)
        fprintf(stderr, "%s\n", strings[i]);

    free (strings);
    fflush(stderr);

#endif /* __USE_GNU */

    // Abort!
    abort();
}

void __cimple_trace(
    const char* file, 
    size_t line,
    const char* function)
{
    // char buffer[Threads::ID_SIZE];
    // Threads::id(buffer);
    fprintf(stderr, "TRACE: %s(%d): %s\n", file, int(line), function);
}

CIMPLE_NAMESPACE_END

