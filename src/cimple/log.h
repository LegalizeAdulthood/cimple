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

#ifndef _cimple_log_h
#define _cimple_log_h

#include <cstdio>
#include <cstdarg>
#include "config.h"

CIMPLE_NAMESPACE_BEGIN

enum Log_Level
{
    LL_FATAL,
    LL_ERR,
    LL_WARN,
    LL_INFO,
    LL_DBG,
};

CIMPLE_CIMPLE_LINKAGE
CIMPLE_PRINTF_ATTR(4, 5)
void log(
    Log_Level level, 
    const char* file, 
    size_t line, 
    const char* fmt, ...);

CIMPLE_CIMPLE_LINKAGE
void vlog(
    Log_Level level, 
    const char* file, 
    size_t line, 
    const char* fmt,
    va_list ap);

struct Log_Call_Frame
{
    Log_Level level;
    const char* file;
    size_t line;
    
    Log_Call_Frame(Log_Level level_, const char* file_, size_t line_) : 
        level(level_), file(file_), line(line_) { }
    
    CIMPLE_PRINTF_ATTR(2, 3)
    inline void invoke(const char* format, ...) 
    {
        va_list ap;
        va_start(ap, format);
        vlog(level, file, line, format, ap);
        va_end(ap);
    }
};


#define CIMPLE_FATAL(ARGS) \
    do \
    { \
        Log_Call_Frame frame(LL_FATAL, __FILE__, __LINE__); \
        frame.invoke ARGS; \
    } \
    while (0)

#define CIMPLE_ERR(ARGS) \
    do \
    { \
        Log_Call_Frame frame(LL_ERR, __FILE__, __LINE__); \
        frame.invoke ARGS; \
    } \
    while (0)

#define CIMPLE_WARN(ARGS) \
    do \
    { \
        Log_Call_Frame frame(LL_WARN, __FILE__, __LINE__); \
        frame.invoke ARGS; \
    } \
    while (0)

#define CIMPLE_INFO(ARGS) \
    do \
    { \
        Log_Call_Frame frame(LL_INFO, __FILE__, __LINE__); \
        frame.invoke ARGS; \
    } \
    while (0)

#define CIMPLE_DBG(ARGS) \
    do \
    { \
        Log_Call_Frame frame(LL_DBG, __FILE__, __LINE__); \
        frame.invoke ARGS; \
    } \
    while (0)

CIMPLE_NAMESPACE_END

#endif /* _cimple_log_h */
