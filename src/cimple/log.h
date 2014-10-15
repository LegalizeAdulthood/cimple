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
#include "String.h"

CIMPLE_NAMESPACE_BEGIN

// Flag to control if logging is used at all.  When set false
// logging is bypassed as part of each macro call.
CIMPLE_CIMPLE_LINKAGE
extern boolean _log_enabled_state;

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

/* INTERNAL ONLY
 * Create a log entry with the defined parameters formatting the
 * the output from input paramters. This call creates a single 
 * log entry with information about the file and line number 
 * from which the log entry occurred, and information from a 
 * format string and additional parameters. 
 * @param level Log_Level representing one of the 5 defined 
 * log levels. See the Log_level enum and the string literals 
 * defined in log.h 
 * @param file const char* current file normally defined with __FILE__ 
 * @Param line size_t defines the line number of the log entry. 
 *       Normally this is simply __LINE__.
 * @Param fmt char* defines the format of the output using the printf 
 * formated output definitions.
 * Any other arguments are arguments for processing of the fmt.
 *  
 * Example 
 *     log(LL_DBG, "my name is %s; my age is %d", "John", 12);
 */
void log(
    Log_Level level, 
    const char* file, 
    size_t line, 
    const char* fmt, ...);

/** 
 * Create a log entry with the defined parameters
 * 
 * @param level Log_Level representing one of the 5 defined 
 * log levels. See the Log_level enum and the string literals 
 * defined in log.h. The alternative to this function is to use 
 * the macros defined below (ex. CIMPLE_FATAL) that simplify the 
 * generation of logs 
 * @param file const char* current file normally defined with __FILE__
 * @param line size_t defines the line number of the log entry. 
 * Normally this is simply __LINE__.
 * @param fmt char* defines the format of the output using the printf 
 * formated output definitions.
 * @param ap va_list
 * /code 
 * Example: 
 *     vlog(LL_DBG, __FILE__, __LINE__, "variable x = %u", x);
 * /endcode
 */
CIMPLE_CIMPLE_LINKAGE
void vlog(
    Log_Level level, 
    const char* file, 
    size_t line, 
    const char* fmt,
    va_list ap);

/**
    Open a log file getting information for the log level from
    a configuration file defined by the name parameter. Normally
    this function is not used except by the logging functions
    themselves.
    @param name - name for the config file containing
                information about the configuration.  This
                function looks specifically for the parameter
                LOGLEVEL
*/
CIMPLE_CIMPLE_LINKAGE
void open_log(const char* name);

/*
    Structure defined as part of each macro generation for logs that
    defines the level, file, line and invoke method for the call.
    This is used by the logging macros CIMPLE_FATAL, etc. defined
    below.
*/
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

/**
    Macro to simplify definition of fatal log entry. the ARGS
    consists of the fmt and argument components equivalent to
    the log method. The macro supplies the LL_FATAL, __FILE__
    and __LINE__ parameters WARNING: Invocations of this macro
    MUST USE double quotes for the ARGS.
    /code
    Example:
       CIMPLE_FATAL(("Invalid input Option %s", optionName.c_str())); 
    /endcode
 */
#define CIMPLE_FATAL(ARGS) \
    do \
    { \
        if (_log_enabled_state) \
        { \
            Log_Call_Frame frame(LL_FATAL, __FILE__, __LINE__); \
            frame.invoke ARGS; \
        } \
    } \
    while (0)

/**
    Macro to simplify definition of ERROR severity log entries.
    The ARGS consists of the fmt and argument components
    equivalent to the log method and using definitons from
    printf.
    WARNING: Invocations of this macro MUST USE double quotes
    for the ARGS.
    /code
    Example:
        CIMPLE_ERR(("no such method: %s", methodName.c_str()));
    /endcode  
*/
#define CIMPLE_ERR(ARGS) \
    do \
    { \
        if (_log_enabled_state) \
        { \
            Log_Call_Frame frame(LL_ERR, __FILE__, __LINE__); \
            frame.invoke ARGS; \
        } \
    } \
    while (0)
/**
    Macro to simplify definition of WARN severity log entries.
    The ARGS consists of the fmt and argument components
    equivalent to the log method and using definitons from
    printf.
    WARNING: Invocations of this macro MUST USE double quotes
    for the ARGS.
    /code
    Example:
        CIMPLE_WARN(("no such method: %s", methodName.c_str()));
    /endcode  
*/
#define CIMPLE_WARN(ARGS) \
    do \
    { \
        if(_log_enabled_state) \
        { \
        Log_Call_Frame frame(LL_WARN, __FILE__, __LINE__); \
        frame.invoke ARGS; \
        } \
    } \
    while (0)
/**
    Macro to simplify definition of ERROR severity log entries.
    The ARGS consists of the fmt and argument components
    equivalent to the log method and using definitons from
    printf.
    WARNING: Invocations of this macro MUST USE double quotes
    for the ARGS.
    /code
    Example:
       CIMPLE_INFO(("ignored null CMPI string"));
    /endcode  
*/
#define CIMPLE_INFO(ARGS) \
    do \
    { \
        if(_log_enabled_state) \
        {   \
        Log_Call_Frame frame(LL_INFO, __FILE__, __LINE__); \
        frame.invoke ARGS; \
        } \
    } \
    while (0)
/**
*   Macro to simplify definition of debug (LL_DBG) severity log
*   entries. The ARGS consists of the fmt and argument
*   components equivalent to the log method and using definitons
*   from printf. WARNING: Invocations of this macro MUST USE
*   double quotes for the ARGS.
    /code
    Example:
       CIMPLE_DBG(("Enter Function"));
    /endcode  
*/
#define CIMPLE_DBG(ARGS) \
    do \
    { \
        if(_log_enabled_state) \
        {   \
        Log_Call_Frame frame(LL_DBG, __FILE__, __LINE__); \
        frame.invoke ARGS; \
        } \
    } \
    while (0)

CIMPLE_CIMPLE_LINKAGE
int log_enable(boolean x);

CIMPLE_CIMPLE_LINKAGE
int log_set_level(String& level);

CIMPLE_NAMESPACE_END

#endif /* _cimple_log_h */
