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

#ifndef _brevity_XML_Parser_h
#define _brevity_XML_Parser_h

#include <cimple/cimple.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_BREVITY_LINKAGE XML_Parser
{
public:

    XML_Parser();

    virtual ~XML_Parser();

    char* allocate(size_t n);

    int parse(size_t n);

    int parse(const char* buffer, size_t n);

    int parse_fd(int fd);

    int parse_file(const char* path);

    CIMPLE_PRINTF_ATTR(2, 3)
    void raise(const char* format, ...);

    void clear_error();

    bool error() const;

    const String& error_msg() const;

    virtual void handle_start_element(const char* el, const char** attrs) = 0;

    virtual void handle_end_element(const char* el) = 0;

    virtual void handle_character_data(const char* s, int len) = 0;

private:

    XML_Parser(const XML_Parser& x);

    XML_Parser& operator=(const XML_Parser& x);

    struct XML_Parser_Rep* _rep;
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_XML_Parser_h */
