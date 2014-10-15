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

#ifndef _cimple_Error_h
#define _cimple_Error_h

#include <cimple/config.h>
#include <cimple/String.h>

#ifdef CIMPLE_DEBUG
# define CIMPLE_ERROR(ARGS) \
    do \
    { \
        Error::set ARGS; \
        Error::set_prefix(CIMPLE_FUNCTION, __FILE__, __LINE__); \
    } \
    while (0)
#else
# define CIMPLE_ERROR(ARGS) Error::set ARGS;
#endif

CIMPLE_NAMESPACE_BEGIN

// This class implements a simple scheme for setting and getting the error 
// message for the current thread. It uses thread-specific-data (TSD) so that 
// each thread may have its own error message.
class CIMPLE_CIMPLE_LINKAGE Error
{
public:

    // Set the message. This clears any previous message
    // in the TSD
    static CIMPLE_PRINTF_ATTR(1, 2)
    void set(const char* format, ...);

    // Prepend debugging information to error message:
    static void set_prefix(
        const char* function, 
        const char* file, 
        size_t line);

    // get the error message. Returns "" if no message
    static const char* get();

    // clear the message and prefix information
    static void clear();
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Error_h */
