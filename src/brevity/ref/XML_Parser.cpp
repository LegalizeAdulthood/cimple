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

#include <expat.h>
#include <cstdarg>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "XML_Parser.h"
#include <cimple/Buffer.h>

CIMPLE_NAMESPACE_BEGIN

struct XML_Parser_Rep
{
    ::XML_Parser parser;
    XML_Parser* self;
    bool error;
    String error_msg;
};

static void XMLCALL _start_element_handler(
    void* data,
    const char* el,
    const char** attrs)
{
    XML_Parser_Rep* rep = (XML_Parser_Rep*)data;
    rep->self->handle_start_element(el, attrs);
}

static void XMLCALL _end_element_handler(void* data, const char* el)
{
    XML_Parser_Rep* rep = (XML_Parser_Rep*)data;
    rep->self->handle_end_element(el);
}

static void XMLCALL _character_data_handler(
    void* data, const XML_Char* s, int len)
{
    XML_Parser_Rep* rep = (XML_Parser_Rep*)data;
    rep->self->handle_character_data(s, len);
}

XML_Parser::XML_Parser()
{
    _rep = new XML_Parser_Rep;
    _rep->self = this;
    _rep->error = false;
    _rep->parser = XML_ParserCreate("UTF-8");

    XML_SetUserData(_rep->parser, _rep);

    XML_SetStartElementHandler(_rep->parser, _start_element_handler);
    XML_SetEndElementHandler(_rep->parser, _end_element_handler);
    XML_SetCharacterDataHandler(_rep->parser, _character_data_handler);
}

XML_Parser::~XML_Parser()
{
    XML_ParserFree(_rep->parser);
    delete _rep;
}

char* XML_Parser::allocate(size_t n)
{
    return (char*)XML_GetBuffer(_rep->parser, n);
}

int XML_Parser::parse(size_t n)
{
    XML_Status status = XML_ParseBuffer(_rep->parser, n, n == 0);

    if (!status)
    {
        if (status == XML_STATUS_ERROR)
        {
            raise("parse failed");
            return -1;
        }

        if (status == XML_STATUS_SUSPENDED)
        {
            raise("parse failed");
            return -1;
        }
    }

    return _rep->error ? -1 : 0;
}

int XML_Parser::parse(const char* buffer, size_t n)
{
    XML_Status status = XML_Parse(_rep->parser, buffer, n, n == 0);

    if (!status)
    {
        if (status == XML_STATUS_ERROR)
        {
            raise("parse() failed");
            return -1;
        }

        if (status == XML_STATUS_SUSPENDED)
        {
            raise("parse() failed");
            return -1;
        }
    }

    return _rep->error ? -1 : 0;
}

int XML_Parser::parse_fd(int fd)
{
    // Read file:

    for (;;)
    {
        const size_t BUFFER_SIZE = 16;
        char* buffer = allocate(BUFFER_SIZE);

        if (!buffer)
        {
            raise("allocate() failed");
            return -1;
        }

        int n = read(fd, buffer, BUFFER_SIZE);

        if (n < 0)
        {
            raise("read() failed");
            return -1;
        }

        if (parse(n) != 0)
            return -1;

        if (n == 0)
            return 0;
    }

    // Unreachable:
    return 0;
}

int XML_Parser::parse_file(const char* path)
{
    // Open file:

    int fd =  open(path, O_RDONLY);

    if (fd < 0)
    {
        raise("open() failed");
        return -1;
    }

    // Parse file descriptor:

    return parse_fd(fd);
}

void XML_Parser::clear_error()
{
    _rep->error = false;
    _rep->error_msg.clear();
}

void XML_Parser::raise(const char* format, ...)
{
    if (_rep->error)
        return;

    _rep->error = true;

    XML_Error code = XML_GetErrorCode(_rep->parser);
    int line = XML_GetCurrentLineNumber(_rep->parser);
    Buffer buffer;

    if (code)
        buffer.format("line %d: %s: ", line, XML_ErrorString(code));
    else
        buffer.format("line %d: error: ", line);

    va_list ap;
    va_start(ap, format);
    buffer.vformat(format, ap);
    va_end(ap);

    _rep->error_msg = buffer.data();

    XML_StopParser(_rep->parser, XML_FALSE);
}

bool XML_Parser::error() const
{
    return _rep->error;
}

const String& XML_Parser::error_msg() const
{
    return _rep->error_msg;
}

CIMPLE_NAMESPACE_END
