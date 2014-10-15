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

#ifndef _cimple_Exception_h
#define _cimple_Exception_h

#include "config.h"
#include "linkage.h"
#include "String.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_CIMPLE_LINKAGE Exception
{
public:

    enum Code
    {
        FAILED = 1,
        BAD_CAST = 2,
        BAD_NAME = 3,
        ALREADY_EXISTS = 4,
        INCOMPATIBLE_OVERRIDE = 5,
        BAD_SUBSCRIPT = 6,
        NO_SUCH_FEATURE = 7,
        NO_SUCH_PROPERTY = 8,
        NO_SUCH_REFERENCE = 9,
        NO_SUCH_METHOD = 10,
        TYPE_MISMATCH = 11,
        NULL_ACCESS = 12,
        BOUNDS = 13,
        BAD_URL = 14,
        ALREADY_CONNECTED = 15,
        CONNECT_FAILED = 16,
        CONVERSION_ERROR = 17,
        NOT_FOUND = 18,
        EXHAUSTED_ENUMERATOR = 19,
        UNINITIALIZED_ENUMERATOR = 20,
        NOT_CONNECTED = 21,
        UNKNOWN_CLASS = 22,
        UNKNOWN_METHOD = 23,
        UNKNOWN_PARAM = 24,
    };

    Exception(Code code);

    CIMPLE_PRINTF_ATTR(3, 4)
    Exception(Code code, const char* format, ...);

    Exception(const Exception& x);

    ~Exception();

    Exception& operator=(const Exception& x);

    const String& message() const;

private:
    Code _code;
    String _message;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Exception_h */
