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

#include "CMPI_Error.h"

CIMPLE_NAMESPACE_BEGIN

static const char* _rc_to_str(CMPIrc rc)
{
    switch (rc)
    {
        case CMPI_RC_OK:
            return "CMPI_RC_OK";
        case CMPI_RC_ERR_FAILED:
            return "CMPI_RC_ERR_FAILED";
        case CMPI_RC_ERR_ACCESS_DENIED:
            return "CMPI_RC_ERR_ACCESS_DENIED";
        case CMPI_RC_ERR_INVALID_NAMESPACE:
            return "CMPI_RC_ERR_INVALID_NAMESPACE";
        case CMPI_RC_ERR_INVALID_PARAMETER:
            return "CMPI_RC_ERR_INVALID_PARAMETER";
        case CMPI_RC_ERR_INVALID_CLASS:
            return "CMPI_RC_ERR_INVALID_CLASS";
        case CMPI_RC_ERR_NOT_FOUND:
            return "CMPI_RC_ERR_NOT_FOUND";
        case CMPI_RC_ERR_NOT_SUPPORTED:
            return "CMPI_RC_ERR_NOT_SUPPORTED";
        case CMPI_RC_ERR_CLASS_HAS_CHILDREN:
            return "CMPI_RC_ERR_CLASS_HAS_CHILDREN";
        case CMPI_RC_ERR_CLASS_HAS_INSTANCES:
            return "CMPI_RC_ERR_CLASS_HAS_INSTANCES";
        case CMPI_RC_ERR_INVALID_SUPERCLASS:
            return "CMPI_RC_ERR_INVALID_SUPERCLASS";
        case CMPI_RC_ERR_ALREADY_EXISTS:
            return "CMPI_RC_ERR_ALREADY_EXISTS";
        case CMPI_RC_ERR_NO_SUCH_PROPERTY:
            return "CMPI_RC_ERR_NO_SUCH_PROPERTY";
        case CMPI_RC_ERR_TYPE_MISMATCH:
            return "CMPI_RC_ERR_TYPE_MISMATCH";
        case CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED:
            return "CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED";
        case CMPI_RC_ERR_INVALID_QUERY:
            return "CMPI_RC_ERR_INVALID_QUERY";
        case CMPI_RC_ERR_METHOD_NOT_AVAILABLE:
            return "CMPI_RC_ERR_METHOD_NOT_AVAILABLE";
        case CMPI_RC_ERR_METHOD_NOT_FOUND:
            return "CMPI_RC_ERR_METHOD_NOT_FOUND";
        case CMPI_RC_DO_NOT_UNLOAD:
            return "CMPI_RC_DO_NOT_UNLOAD";
        case CMPI_RC_NEVER_UNLOAD:
            return "CMPI_RC_NEVER_UNLOAD";
        case CMPI_RC_ERR_INVALID_HANDLE:
            return "CMPI_RC_ERR_INVALID_HANDLE";
        case CMPI_RC_ERR_INVALID_DATA_TYPE:
            return "CMPI_RC_ERR_INVALID_DATA_TYPE";
        case CMPI_RC_ERROR_SYSTEM:
            return "CMPI_RC_ERROR_SYSTEM";
        case CMPI_RC_ERROR:
            return "CMPI_RC_ERROR";
    }

    return 0;
}

void throw_exception(const CMPIStatus& status, const char* format, ...)
{
    const char* rc_str = _rc_to_str(status.rc);
    const char* msg = status.msg ? CMGetCharsPtr(status.msg, NULL) : 0;

    char buffer[1024];
    int n = sprintf(buffer, "%s: %s: ", rc_str, msg);

    va_list ap;
    va_start(ap, format);
    vsprintf(buffer + n, format, ap);
    va_end(ap);

    throw Exception(buffer);
}

void throw_exception(CMPIrc rc, const char* format, ...)
{
    const char* rc_str = _rc_to_str(rc);

    char buffer[1024];
    int n = sprintf(buffer, "%s: ", rc_str);

    va_list ap;
    va_start(ap, format);
    vsprintf(buffer + n, format, ap);
    va_end(ap);

    throw Exception(buffer);
}

void throw_exception(const char* format, ...)
{
    char buffer[1024];

    va_list ap;
    va_start(ap, format);
    vsprintf(buffer, format, ap);
    va_end(ap);

    throw Exception(buffer);
}

CIMPLE_NAMESPACE_END
