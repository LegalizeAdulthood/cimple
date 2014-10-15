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

#include <cstdarg>
#include <cstdio>
#include "Exception.h"

CIMPLE_NAMESPACE_BEGIN

struct Detail
{
    const char* name;
    Exception::Code code;
    const char* message;
};

static const Detail _details[] =
{
    {
        "FAILED",
        Exception::FAILED,
        "A general error occurred that is not covered by a more specific error "
        "code"
    },
    {
        "ACCESS_DENIED",
        Exception::ACCESS_DENIED,
        "Access to a CIM resource is not available to the client"
    },
    {
        "INVALID_NAMESPACE",
        Exception::INVALID_NAMESPACE,
        "The target namespace does not exist"
    },
    {
        "INVALID_PARAMETER",
        Exception::INVALID_PARAMETER,
        "One or more parameter values passed to the method are not valid"
    },
    {
        "INVALID_CLASS",
        Exception::INVALID_CLASS,
        "The specified class does not exist"
    },
    {
        "NOT_FOUND",
        Exception::NOT_FOUND,
        "The requested object cannot be found"
    },
    {
        "NOT_SUPPORTED",
        Exception::NOT_SUPPORTED,
        "The requested operation is not supported"
    },
    {
        "CLASS_HAS_CHILDREN",
        Exception::CLASS_HAS_CHILDREN,
        "The operation cannot be invoked on this class because it has "
        "subclasses"
    },
    {
        "CLASS_HAS_INSTANCES",
        Exception::CLASS_HAS_INSTANCES,
        "The operation cannot be invoked on this class because one or more "
        "instances of this class exist"
    },
    {
        "INVALID_SUPERCLASS", 
        Exception::INVALID_SUPERCLASS, 
        "The operation cannot be invoked because the specified superclass "
        "does not exist"
    },
    {
        "ALREADY_EXISTS",
        Exception::ALREADY_EXISTS,
        "The operation cannot be invoked because an object already exists"
    },
    {
        "NO_SUCH_PROPERTY",
        Exception::NO_SUCH_PROPERTY,
        "The specified property does not exist"
    },
    {
        "TYPE_MISMATCH", 
        Exception::TYPE_MISMATCH, 
        "The value supplied is not compatible with the type"
    },
    {
        "QUERY_LANGUAGE_NOT_SUPPORTED",
        Exception::QUERY_LANGUAGE_NOT_SUPPORTED,
        "The query language is not recognized or supported"
    },
    {
        "INVALID_QUERY",
        Exception::INVALID_QUERY,
        "The query is not valid for the specified query language"
    },
    {
        "METHOD_NOT_AVAILABLE",
        Exception::METHOD_NOT_AVAILABLE,
        "The extrinsic method cannot be invoked"
    },
    {
        "METHOD_NOT_FOUND",
        Exception::METHOD_NOT_FOUND,
        "The specified extrinsic method does not exist"
    },
    {
        "NAMESPACE_NOT_EMPTY",
        Exception::NAMESPACE_NOT_EMPTY,
        "The specified Namespace is not empty"
    },
    {
        "BAD_CAST",
        Exception::BAD_CAST,
        "attempted to cast between incompatible types"
    },
    {
        "NULL_ACCESS",
        Exception::NULL_ACCESS,
        "accessed null pointer"
    },
    {
        "BAD_URL",
        Exception::BAD_URL,
        "malformed universal resource locator"
    },
    {
        "ALREADY_CONNECTED",
        Exception::ALREADY_CONNECTED,
        "attempted to connect while already connected"
    },
    {
        "NOT_CONNECTED",
        Exception::NOT_CONNECTED,
        "attempted an operation requiring a connection when no connection "
        "has been established"
    },
    {
        "CONNECT_FAILED",
        Exception::CONNECT_FAILED,
        "failed to establish a connection"
    },
    {
        "BAD_XML",
        Exception::BAD_XML,
        "error while parsing XML"
    },
    {
        "BAD_ENUMERATOR",
        Exception::BAD_ENUMERATOR,
        "attempted to use an uninitialized or exhausted enumerator"
    },
    {
        "BAD_CONVERSION",
        Exception::BAD_CONVERSION,
        "conversion failure"
    }
};

static size_t _num_details = sizeof(_details) / sizeof(_details[0]);

static const Detail& _find_detail(Exception::Code code)
{
    for (size_t i = 0; i < _num_details; i++)
    {
        if (_details[i].code == code)
            return _details[i];
    }

    return _details[0];
}

Exception::Exception(Code code) : _code(code)
{
    const Detail& detail = _find_detail(code);
    _message = detail.name;
    _message.append(": ");
    _message.append(detail.message);
}

Exception::Exception(Code code, const char* format, ...) : _code(code)
{
    char buffer[4096];
    va_list ap;
    va_start(ap, format);
    size_t n = vsprintf(buffer, format, ap);
    assert(n < sizeof(buffer));
    va_end(ap);

    const Detail& detail = _find_detail(code);
    _message = detail.name;
    _message.append(": ");
    _message.append(detail.message);
    _message.append(": \"");
    _message.append(buffer);
    _message.append("\"");
}

Exception::Exception(const Exception& x) : _message(x._message)
{
}

Exception& Exception::operator=(const Exception& x)
{
    _code = x._code;
    _message = x._message;
    return *this;
}

Exception::~Exception()
{
}

const String& Exception::message() const
{
    return _message;
}

bool Exception::valid_cim_code(uint32 code)
{
    switch (code)
    {
        case Exception::FAILED:
        case Exception::ACCESS_DENIED:
        case Exception::INVALID_NAMESPACE:
        case Exception::INVALID_PARAMETER:
        case Exception::INVALID_CLASS:
        case Exception::NOT_FOUND:
        case Exception::NOT_SUPPORTED:
        case Exception::CLASS_HAS_CHILDREN:
        case Exception::CLASS_HAS_INSTANCES:
        case Exception::INVALID_SUPERCLASS:
        case Exception::ALREADY_EXISTS:
        case Exception::NO_SUCH_PROPERTY:
        case Exception::TYPE_MISMATCH:
        case Exception::QUERY_LANGUAGE_NOT_SUPPORTED:
        case Exception::INVALID_QUERY:
        case Exception::METHOD_NOT_AVAILABLE:
        case Exception::METHOD_NOT_FOUND:
        case Exception::NAMESPACE_NOT_EMPTY:
            return true;
        default:
            return false;
    }

    // Unreachable!
    return false;
}

CIMPLE_NAMESPACE_END

