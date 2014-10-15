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

#include "HTTP.h"
#include <cctype>

CIMPLE_NAMESPACE_BEGIN

static const uint8 _is_uri[256] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,1,1,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

static const char* _uri_str[256] =
{
    "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07",
    "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F",
    "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17",
    "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F",
    "%20", "%21", "%22", "%23", "%24", "%25", "%26", "%27",
    "%28", "%29", "%2A", "%2B", "%2C", "%2D", "%2E", "%2F",
    "%30", "%31", "%32", "%33", "%34", "%35", "%36", "%37",
    "%38", "%39", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F",
    "%40", "%41", "%42", "%43", "%44", "%45", "%46", "%47",
    "%48", "%49", "%4A", "%4B", "%4C", "%4D", "%4E", "%4F",
    "%50", "%51", "%52", "%53", "%54", "%55", "%56", "%57",
    "%58", "%59", "%5A", "%5B", "%5C", "%5D", "%5E", "%5F",
    "%60", "%61", "%62", "%63", "%64", "%65", "%66", "%67",
    "%68", "%69", "%6A", "%6B", "%6C", "%6D", "%6E", "%6F",
    "%70", "%71", "%72", "%73", "%74", "%75", "%76", "%77",
    "%78", "%79", "%7A", "%7B", "%7C", "%7D", "%7E", "%7F",
    "%80", "%81", "%82", "%83", "%84", "%85", "%86", "%87",
    "%88", "%89", "%8A", "%8B", "%8C", "%8D", "%8E", "%8F",
    "%90", "%91", "%92", "%93", "%94", "%95", "%96", "%97",
    "%98", "%99", "%9A", "%9B", "%9C", "%9D", "%9E", "%9F",
    "%A0", "%A1", "%A2", "%A3", "%A4", "%A5", "%A6", "%A7",
    "%A8", "%A9", "%AA", "%AB", "%AC", "%AD", "%AE", "%AF",
    "%B0", "%B1", "%B2", "%B3", "%B4", "%B5", "%B6", "%B7",
    "%B8", "%B9", "%BA", "%BB", "%BC", "%BD", "%BE", "%BF",
    "%C0", "%C1", "%C2", "%C3", "%C4", "%C5", "%C6", "%C7",
    "%C8", "%C9", "%CA", "%CB", "%CC", "%CD", "%CE", "%CF",
    "%D0", "%D1", "%D2", "%D3", "%D4", "%D5", "%D6", "%D7",
    "%D8", "%D9", "%DA", "%DB", "%DC", "%DD", "%DE", "%DF",
    "%E0", "%E1", "%E2", "%E3", "%E4", "%E5", "%E6", "%E7",
    "%E8", "%E9", "%EA", "%EB", "%EC", "%ED", "%EE", "%EF",
    "%F0", "%F1", "%F2", "%F3", "%F4", "%F5", "%F6", "%F7",
    "%F8", "%F9", "%FA", "%FB", "%FC", "%FD", "%FE", "%FF",
};

size_t HTTP::format_request_header(
    Buffer& out,
    const char* host,
    uint16 port,
    const char* cim_operation,
    const char* cim_method,
    const char* cim_object)
{
    // Example:
    //
    //     POST /cimom HTTP/1.1<CRLF>
    //     HOST: localhost:8888<CRLF>
    //     Content-Type: application/xml; charset="utf-8"<CRLF>
    //     Content-Length: 0000000000<CRLF>
    //     CIMOperation: MethodCall<CRLF>
    //     CIMMethod: EnumerateInstances<CRLF>
    //     CIMObject: root%2Fcimv2<CRLF>
    //     <CRLF>
    //

    // POST header:
    out.append(STRLIT("POST /cimom HTTP/1.1\r\n"));

    // HOST header:
    {
        out.append(STRLIT("HOST: "));
        encode_uri(out, host);
        out.append(':');

        char buf[22];
        size_t size;
        const char* s = uint16_to_str(buf, port, size);
        out.append(s, size);

        out.append(STRLIT("\r\n"));
    }

    // Content-Type:
    out.append(STRLIT("Content-Type: application/xml; charset=\"utf-8\"\r\n"));

    // Content-Length (to be filled in later).
    out.append(STRLIT("Content-Length: 0000000000\r\n"));
    size_t offset = out.size() - 12;

    // CIMOperation:
    {
        out.append(STRLIT("CIMOperation: "));
        out.appends(cim_operation);
        out.append(STRLIT("\r\n"));
    }

    // CIMMethod:
    {
        out.append(STRLIT("CIMMethod: "));
        out.appends(cim_method);
        out.append(STRLIT("\r\n"));
    }

    // CIMObject:
    {
        out.append(STRLIT("CIMObject: "));
        encode_uri(out, cim_object);
        out.append(STRLIT("\r\n"));
    }

    // Blank line:
    out.append(STRLIT("\r\n"));

    return offset;
}

void HTTP::encode_uri(Buffer& out, const char* str)
{
    while (*str)
    {
        uint8 c = *str++;

        if (_is_uri[c])
            out.append(_uri_str[c], 3);
        else
            out.append(c);
    }
}

static inline size_t _find_content(char* s, size_t n)
{
    // Content starts right after <CRLF><CRLF> sequence (or after <LF><LF> 
    // on some non-conformant servers).

    char* p = s; 
    
    for (;;)
    {
        if (n >= 4)
        {
            if (p[0] == '\r' && p[1] == '\n' && p[2] == '\r' && p[3] == '\n')
            {
                p[0] = '\0';
                return (p + 4) - s;
            }

            if (p[0] == '\n' && p[1] == '\n')
            {
                p[0] = '\0';
                return (p + 2) - s;
            }
        }
        else if (n >= 2)
        {
            if (p[0] == '\n' && p[1] == '\n')
            {
                p[0] = '\0';
                return (p + 2) - s;
            }
        }
        else
            break;

        n--;
        p++;
    }

    // Not found!
    return 0;
}

static int _parse_hdr(HTTP_Message& hdr)
{
    const char* s = hdr.buffer.data();

    // Parse "HTTP/1.1 200 OK" line:

    const char* start = s;
    const char* end;

    if (find_token(start, "\r\n", start, end) == 0)
    {
        // Null terminate this token:

        const char* tok = start;
        start = end;

        if (*start)
            *((char*)start++) = '\0';

        // Find start of status number:

        char* p = (char*)strchr(tok, ' ');

        if (!p)
            return -1;

        while (isspace(*p))
            p++;

        // Seek end of status number:

        char* q = p;

        while (isdigit(*q))
            q++;

        if (p == q)
            return -1;

        // Convert status number:

        if (strncmp(p, "200", 3) == 0)
            hdr.status = HTTP_STATUS_OK;
        else if (strncmp(p, "400", 3) == 0)
            hdr.status = HTTP_STATUS_BAD_REQUEST;
        else if (strncmp(p, "401", 3) == 0)
            hdr.status = HTTP_STATUS_UNAUTHORIZED;
        else if (strncmp(p, "403", 3) == 0)
            hdr.status = HTTP_STATUS_FORBIDDEN;
        else if (strncmp(p, "500", 3) == 0)
            hdr.status = HTTP_STATUS_INTERNAL_SERVER_ERROR;
        else if (strncmp(p, "501", 3) == 0)
            hdr.status = HTTP_STATUS_NOT_IMPLEMENTED;
        else if (strncmp(p, "503", 3) == 0)
            hdr.status = HTTP_STATUS_SERVICE_UNAVAILABLE;
        else
            return -1;
    }
    else
        return -1;

    // Parse individual headers (of the form "name: value").

    while (find_token(start, "\r\n", start, end) == 0)
    {
        // Null-terminate token:

        char* tok = (char*)start;
        start = end;

        if (*start)
            *((char*)start++) = '\0';

        // Find end of name:

        char* p = tok;

        while (*p && !isspace(*p) && *p != ':')
            p++;

        while (isspace(*p))
            p++;

        if (*p != ':')
            return -1;

        *p++ = '\0';

        // Find start of value:

        while (isspace(*p))
            p++;

        if (*p == '\0')
            return -1;

        // Remove trailing space from value:

        for (char* q = (char*)end; q != p && isspace(q[-1]); )
            *--q = '\0';

        // Set header value:

        if (strcasecmp(tok, "Content-Type") == 0)
            hdr.content_type = p;
        else if (strcasecmp(tok, "Content-Length") == 0)
        {
            if (str_to_uint32(p, hdr.content_length) != 0)
                return -1;
        }
        else if (strcasecmp(tok, "CIMOperation") == 0)
            hdr.cim_operation = p;
        else if (strcasecmp(tok, "CIMError") == 0)
            hdr.cim_error = p;
        else if (strcasecmp(tok, "PGErrorDetail") == 0)
            hdr.pg_error_detail = p;
    }

    return 0;
}

int HTTP::send(Sock sock, const Buffer& req, HTTP_Message& rsp)
{
    rsp.clear();

    // Send request to server:

    if (Sockets::send_n(sock, req.data(), req.size()) != ssize_t(req.size()))
        return -1;

    // Read back response:

    char buf[BREVITY_BLOCK_SIZE];

    for (;;)
    {
        ssize_t n = Sockets::recv(sock, buf, sizeof(buf));

        if (n <= 0)
            return -1;

        rsp.buffer.append(buf, n);

        rsp.header_size = _find_content(rsp.buffer.data(), rsp.buffer.size());

        if (rsp.header_size != 0)
            return _parse_hdr(rsp);
    }

    // Unreachable!
    return 0;
}

CIMPLE_NAMESPACE_END
