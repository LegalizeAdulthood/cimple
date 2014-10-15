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

#ifndef _brevity_HTTP_h
#define _brevity_HTTP_h

#include <cimple/cimple.h>
#include "linkage.h"
#include "defines.h"
#include "Sockets.h"

CIMPLE_NAMESPACE_BEGIN

enum HTTP_Status
{
    HTTP_STATUS_NONE = 0,
    HTTP_STATUS_OK = 200,
    HTTP_STATUS_BAD_REQUEST = 400,
    HTTP_STATUS_UNAUTHORIZED = 401,
    HTTP_STATUS_FORBIDDEN = 403,
    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
    HTTP_STATUS_NOT_IMPLEMENTED = 501,
    HTTP_STATUS_SERVICE_UNAVAILABLE = 503,
};

struct HTTP_Message
{
    HTTP_Status status;
    const char* content_type;
    uint32 content_length;
    const char* cim_operation;
    const char* cim_error;
    const char* pg_error_detail;

    // Includes header and zero or more content bytes.
    Buffer buffer;

    // Size of header portion of buffer.
    size_t header_size;

    HTTP_Message()
    {
        clear();
    }

    const char* partial_content() const
    {
        return buffer.data() + header_size;
    }

    size_t partial_content_length() const
    {
        return buffer.size() - header_size;
    }

    void clear()
    {
        status = HTTP_STATUS_NONE;
        content_type = 0;
        content_length = 0;
        cim_operation = 0;
        cim_error = 0;
        pg_error_detail = 0;
        header_size = 0;
        buffer.clear();
    }

    void print() const
    {
        printf("HTTP_Message:\n");
        printf("  status={%u}\n", status);
        printf("  content_type={%s}\n", content_type);
        printf("  content_length={%u}\n", content_length);
        printf("  cim_operation={%s}\n", cim_operation);
        printf("  cim_error={%s}\n", cim_error);
        printf("  pg_error_detail={%s}\n", pg_error_detail);

        printf("===== BEGIN PARTIAL CONTENT =====\n");
        printf("%s\n", partial_content());
        printf("===== END PARTIAL CONTENT =====\n");
    }
};

class CIMPLE_BREVITY_LINKAGE HTTP
{
public:

    // Format HTTP request header and return the offset of the 10 digit zero
    // content length (which should be overwrittent with the actual content
    // length when available).
    static size_t format_request_header(
        Buffer& out,
        const char* host,
        uint16 port,
        const char* cim_operation,
        const char* cim_method,
        const char* cim_object);

    // Encode string as URI characters.
    static void encode_uri(Buffer& out, const char* str);

    // Overwrite the "0000000000" with the actual content length.
    static void set_content_length(
        Buffer& out, size_t offset, size_t content_length)
    {
        char buffer[22];
        size_t size;
        const char* str = uint32_to_str(buffer, content_length, size);
        offset += 10 - size;
        memcpy((char*)out.data() + offset, str, size);
    }

    static int send(Sock sock, const Buffer& request, HTTP_Message& response);
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_HTTP_h */
