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

static const char* _messages[] =
{
    "FAILED",
    "BAD_CAST",
    "BAD_NAME",
    "ALREADY_EXISTS",
    "INCOMPATIBLE_OVERRIDE",
    "BAD_SUBSCRIPT",
    "NO_SUCH_FEATURE",
    "NO_SUCH_PROPERTY",
    "NO_SUCH_REFERENCE",
    "NO_SUCH_METHOD",
    "TYPE_MISMATCH",
    "NULL_ACCESS",
    "BOUNDS",
    "BAD_URL",
    "ALREADY_CONNECTED",
    "CONNECT_FAILED",
    "CONVERSION_ERROR",
    "NOT_FOUND",
    "EXHAUSTED_ENUMERATOR",
    "UNINITIALIZED_ENUMERATOR",
    "NOT_CONNECTED",
    "UNKNOWN_CLASS",
    "UNKNOWN_METHOD",
    "UNKNOWN_PARAM",
};

static size_t _num_messages = sizeof(_messages) / sizeof(_messages[0]);

Exception::Exception(Code code) : _code(code)
{
    _message = _messages[int(_code) - 1];
}

Exception::Exception(Code code, const char* format, ...) : _code(code)
{
    char buffer[1024];
    va_list ap;
    va_start(ap, format);
    size_t n = vsprintf(buffer, format, ap);
    assert(n < sizeof(buffer));
    va_end(ap);

    _message = _messages[int(_code) - 1];
    _message.append(": ");
    _message.append(buffer);
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

CIMPLE_NAMESPACE_END

