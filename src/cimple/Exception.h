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
        // Statndard CIM status codes:
        FAILED = 1,
        ACCESS_DENIED = 2,
        INVALID_NAMESPACE = 3,
        INVALID_PARAMETER = 4,
        INVALID_CLASS = 5,
        NOT_FOUND = 6,
        NOT_SUPPORTED = 7,
        CLASS_HAS_CHILDREN = 8,
        CLASS_HAS_INSTANCES = 9,
        INVALID_SUPERCLASS = 10,
        ALREADY_EXISTS = 11,
        NO_SUCH_PROPERTY = 12,
        TYPE_MISMATCH = 13,
        QUERY_LANGUAGE_NOT_SUPPORTED = 14,
        INVALID_QUERY = 15,
        METHOD_NOT_AVAILABLE = 16,
        METHOD_NOT_FOUND = 17,
        NAMESPACE_NOT_EMPTY = 20,

        // Extended error codes:
        BAD_CAST = 1000,
        NULL_ACCESS,
        BAD_URL,
        ALREADY_CONNECTED,
        NOT_CONNECTED,
        CONNECT_FAILED,
        BAD_XML,
        BAD_ENUMERATOR,
        BAD_CONVERSION,
    };

    Exception(Code code);

    CIMPLE_PRINTF_ATTR(3, 4)
    Exception(Code code, const char* format, ...);

    Exception(const Exception& x);

    ~Exception();

    Exception& operator=(const Exception& x);

    const String& message() const;

    static bool valid_cim_code(uint32 code);

private:
    Code _code;
    String _message;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Exception_h */
