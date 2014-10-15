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

/** 
*  This file defines APIs for creating calls to log information
*  from CIMPLE providers.  The goal is to provide a standard
*  means to include log call definitions within the user code
*  and variable means to control execution and compilation of
*  that code.
*  The log mechanism includes multiple levels of logging (fatal,
*  Error, Warning, Information, debug) that can be defined with
*  each log to allow generation of log entries based on log
*  level settings for CIMPLE. Each call includes its log level
*  definition.
* 
*  Generally, the user should use only the macros defined in
*  this file to create log calls; they provide the most control
*  including:  Automatic fast-path bypass, automatic inclusion
*  of file and line information, etc.  The macros use the same
*  general format as C++ printf calls with a format string and
*  list of variables.
*  
*  The macros defined are:
*  \li \c CIMPLE_FATAL
*  \li \c CIMPLE_ERR
*  \li \c CIMPLE_WARN
*  \li \c CIMPLE_INFO
*  \li \c CIMPLE_DBG
*  
*  Setting the log level either through the cimple configuration
*  file or the cimple_configure class to a specific level causes
*  that level and all higher levels of log to be output.
*  
*  The macros can be disabled completely by setting the configure flag
*  --disable_log_macros.
*  
*   \code Example:
       CIMPLE_FATAL(("Invalid input Option %s", optionName.c_str())); 
*   \endcode
*  
*   Any c++ printf definitions can be used within the formatting
*   string.
*   NOTE: Be sure to put double parens around the parameters of
*   the calls. This is required by the macros.
*  
*/
#ifndef _cimple_log_h
#define _cimple_log_h

#include <cstdio>
#include <cstdarg>
#include "config.h"
#include "String.h"

CIMPLE_NAMESPACE_BEGIN

// Flag to control if log calls are executed.  When set false
// logging is bypassed as part of each macro call. This is external
// because used by log macros.
CIMPLE_CIMPLE_LINKAGE
extern boolean _log_enabled_state;

// Enumeration to define the possible log levels
enum Log_Level
{
    LL_FATAL,
    LL_ERR,
    LL_WARN,
    LL_INFO,
    LL_DBG,
};

/* INTERNAL ONLY
 * Create a log entry with the defined parameters formatting the
 * the output from input parameters. This call creates a single 
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
 *     log(LL_DBG, __FILE__, __LINE__,
 *         "my name is %s; my age is %d", "John", 12);
 */
CIMPLE_PRINTF_ATTR(4, 5)
CIMPLE_CIMPLE_LINKAGE
void log(
    Log_Level level, 
    const char* file, 
    size_t line, 
    const char* fmt, ...);

/** 
 * Create a log entry with the parameters defined by a va_list
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
 * \code 
 * Example: 
 *     vlog(LL_DBG, __FILE__, __LINE__, "variable x = %u", x);
 * \endcode
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
    Structure defined as part of each macro generation for log calls. This
    structure defines the level, file, line and invoke method for the call.
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

/*************************************************************************** 
** 
** Macros for generating log entries.  The following macros should be used
** to generate log entries. Each macro defines a specific log level and
** provides for variable arguments for defining the log text.
** The form of the ARGS is the same as the printf arguments
**        format string followed by variable list
** WARNING: For all of these macros the ARGS MUST BE enclosed in double
**        quotes
** Example:
**     CIMPLE_FATAL(("Invalid input Option %s", optionName.c_str())); 
**
****************************************************************************/ 

#ifdef DISABLE_LOG_MACROS_OPT

#    define CIMPLE_FATAL(ARGS) do {} while(0)
#    define CIMPLE_ERR(ARGS) do {} while(0)
#    define CIMPLE_WARN(ARGS) do {} while(0)
#    define CIMPLE_INFO(ARGS) do {} while(0)
#    define CIMPLE_DBG(ARGS) do {} while(0)

#else
/**
    Macro to simplify definition of fatal log entry. The ARGS
    consists of the fmt and argument components equivalent to
    the log method. The macro supplies the LL_FATAL, __FILE__
    and __LINE__ parameters WARNING: Invocations of this macro
    MUST USE double quotes for the ARGS.
    \code Example:
       CIMPLE_FATAL(("Invalid input Option %s", 
           optionName.c_str()));
    \endcode
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
    \code
    Example:
        CIMPLE_ERR(("no such method: %s", methodName.c_str()));
    \endcode  
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
    \code
    Example:
        CIMPLE_WARN(("no such method: %s", methodName.c_str()));
    \endcode  
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
    \code
    Example:
       CIMPLE_INFO(("ignored null CMPI string"));
    \endcode  
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
    \code
    Example:
       CIMPLE_DBG(("Enter Function"));
    \endcode  
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

#endif  // DISABLE_LOG_MACROS_OPT

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// The following functions are considered internal to CIMPLE. Please use the
// CimpleConfig Class in place of the following.  These functions may be
// removed or made internal to the cimple.dll code in the future.

// All of the functions defined below are all subject to change and
// should be considered deprecated. DO NOT USE THEM. Use the corresponding
// functions in CimpleConfig instead. All of this is to be moved to
// a logInternal module in a future version to insure that it is used only
// by components of the src/cimple directory

CIMPLE_CIMPLE_LINKAGE
bool log_enable(bool x);

CIMPLE_CIMPLE_LINKAGE
bool get_log_enable_state();

CIMPLE_CIMPLE_LINKAGE
bool log_set_level(String& level);

CIMPLE_CIMPLE_LINKAGE
bool log_set_level(Log_Level level);

CIMPLE_CIMPLE_LINKAGE
Log_Level log_get_level();

CIMPLE_CIMPLE_LINKAGE
const char * log_get_level_string();

/** 
 * DEPRECATEDSet the variable that contains the environment variable that 
 * controls location of the directory definition for CIMPLE. 
 * There is no check executed for the validity or existence of 
 * the variable.  That occurs on the first use of the 
 * environment variable. 
 * 
 * @param env_var The environment variable that will be used to 
 *                locate the directory.  The system default is
 *                CIMPLE_HOME. Note that this variable can also
 *                be set during configuration with the
 *                --cimple_home_envvar parameter.  Calling this
 *                function overrides that setting
 * 
 * @return 0
 */
//DEPRECATED
CIMPLE_CIMPLE_LINKAGE
int set_cimple_home_envvar(const char *);

CIMPLE_CIMPLE_LINKAGE
const char* get_cimple_home_envvar();

CIMPLE_CIMPLE_LINKAGE
void log_reinitialize();

CIMPLE_CIMPLE_LINKAGE
uint32 log_get_maxFileSize();

CIMPLE_CIMPLE_LINKAGE
bool log_set_maxlogFileSize(uint32 new_size);

CIMPLE_CIMPLE_LINKAGE
uint32 log_get_maxLogBackupFiles();

CIMPLE_CIMPLE_LINKAGE
bool log_set_maxlogBackupFiles(uint32 new_size);

CIMPLE_CIMPLE_LINKAGE
bool log_remove_all_logfiles();

CIMPLE_CIMPLE_LINKAGE
bool read_config_file();

CIMPLE_NAMESPACE_END

#endif /* _cimple_log_h */
