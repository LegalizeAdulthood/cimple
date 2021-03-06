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

#include <cstdarg>
#include <cstdio>
#include <cimple/TLS.h>
#include <cimple/Strings.h>
#include "Error.h"

CIMPLE_NAMESPACE_BEGIN

static TLS _message;

void Error::set(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    char* message = str_vprintf(format, ap);
    va_end(ap);

    // Replace the existing message. This is thread safe since we are using
    // thread-specific-data (no other thread can be accessing this slot since
    // since the thread executing this function owns it).

    void* old_message = _message.get();

    if (old_message)
        free(old_message);

    _message.set(message);
}

const char* Error::get()
{
    const char* message = (const char*)_message.get();

    return message ? message : "<unitialized error message>";
}

void Error::set_prefix(
    const char* function,
    const char* file,
    size_t line)
{
    char* old_message = (char*)_message.get();
    _message.set(0);
    Error::set("%s(): %s(%d): %s", function, file, int(line), old_message);
    free(old_message);
}

void Error::clear()
{
    void* old_message = _message.get();

    if (old_message)
        free(old_message);

    _message.set(0);
}

CIMPLE_NAMESPACE_END
