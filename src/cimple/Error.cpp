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

#include <pthread.h>
#include <cstdarg>
#include <cstdio>
#include <cimple/Strings.h>
#include "Error.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Message thread-specific storage:
//
//==============================================================================

// Export to avoid multiple copies via shared libraries.
#ifdef CIMPLE_STATIC
CIMPLE_EXPORT
#endif
pthread_key_t _error_key;

// Export to avoid multiple copies via shared libraries.
#ifdef CIMPLE_STATIC
CIMPLE_EXPORT
#endif
pthread_once_t _error_key_once = PTHREAD_ONCE_INIT;

static void _make_key()
{
    pthread_key_create(&_error_key, NULL);
}

static char* _message()
{
    pthread_once(&_error_key_once, _make_key);
    return (char*)pthread_getspecific(_error_key);
}

static void _message(char* msg)
{
    pthread_once(&_error_key_once, _make_key);
    pthread_setspecific(_error_key, msg);
}

//==============================================================================
//
// Error
//
//==============================================================================

void Error::set(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    char* message = str_vprintf(format, ap);
    va_end(ap);

    // Replace the existing message. This is thread safe since we are using
    // thread-specific-data (no other thread can be accessing this slot since
    // since the thread executing this function owns it).

    char* old_message = _message();

    if (old_message)
        free(old_message);

    _message(message);
}

const char* Error::get()
{
    const char* message = _message();

    return message ? message : "";
}

void Error::set_prefix(
    const char* function,
    const char* file,
    size_t line)
{
    char* old_message = _message();
    _message(0);
    Error::set("%s(): %s(%d): %s", function, file, int(line), old_message);
    free(old_message);
}

void Error::clear()
{
    void* old_message = _message();

    if (old_message)
        free(old_message);

    _message(0);
}

CIMPLE_NAMESPACE_END

