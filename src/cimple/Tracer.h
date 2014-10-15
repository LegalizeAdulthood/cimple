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

#ifndef _cimple_Tracer_h
#define _cimple_Tracer_h

#include <cstdio>
#include <cstdarg>
#include "config.h"

CIMPLE_NAMESPACE_BEGIN

enum Trace_Level
{
    TRC_FATAL,
    TRC_SEVERE,
    TRC_ERROR,
    TRC_WARN,
    TRC_INFO,
    TRC_DEBUG
};

class CIMPLE_CIMPLE_LINKAGE Tracer
{
public:

    Tracer(Trace_Level level, const char* prefix);

    virtual ~Tracer();

    virtual
    CIMPLE_PRINTF_ATTR(3, 4)
    void trace(Trace_Level level, const char* format, ...);

private:
    FILE* _os;
    Trace_Level _level;

    Tracer(const Tracer& x);
    Tracer& operator=(const Tracer& x);
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Tracer_h */
