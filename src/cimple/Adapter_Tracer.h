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

/*
    This file defines a class AdapterTracer and a set of macros to implement
    tracing within the CIMPLE infrastructure, primarily the adapters.  The
    goal is to provide tools that can be used to instrument the various
    components of the CIMPLE infrastructure to flexibly trace information
    when required and at the same time be completely disabled (i.e. no
    code generated when not required by the user.
 
    These are maintained as a separate class and Macros from the log and any
    user tracer tools (future) so that they can be activated/controlled
    separately since their use is primarily to help with any issues in use
    of the CIMPLE infrastructure, not the provider user code.
 
    The normal mode for this code is completely disabled at
    compile time which minimizes overhead.
*/

#ifndef _cimple_Adapter_Tracer_h
#define _cimple_Adapter_Tracer_h

#include <cstdio>
#include <cstdarg>
#include "config.h"
#include "log.h"

CIMPLE_NAMESPACE_BEGIN

// Macros to define various trace points in the CIMPLE infrastructure.
// These macros define:
//     - Function Entry points
//     - Function Exit points (including ability to show return values)
//     - Macro to trace data values.

// Define the standard components required for the log interface, Log_Level,
// file, and line
#define FL LL_DBG, __FILE__, __LINE__

#ifdef ENABLE_ADAPTER_TRACE_OPT

/**
    Macro to define an entry for a function.  The only parameter is
    the name of the function
    ex. PENTRY("name_of_function");
    Used in conjunction with the PEXIT... macros below to provide trace
    to the log file for function entry and return points.
 */
/*
#define PENTRY(NAME) \
    static const char __cimple_local_proc_name[] = NAME; \
    log(FL, "Entry: %s", __cimple_local_proc_name);
*/

#define PENTRY(PROC_NAME) \
    static const char __cimple_local_proc_name[] = PROC_NAME; \
    AdapterTracer::pEntry(__cimple_local_proc_name, __FILE__, __LINE__);

/**
    Macro to define  the exit from a function which has no return value.
*/


#define PEXIT() \
    AdapterTracer::pExit(__cimple_local_proc_name, __FILE__, __LINE__);

#define PEXIT_RTN_VAL(RTN_VAL) \
    AdapterTracer::pExit(__cimple_local_proc_name, __FILE__, __LINE__, RTN_VAL);

#define PEXITBOOL(RTN_VAL) \
    AdapterTracer::pExit(__cimple_local_proc_name, __FILE__, __LINE__, RTN_VAL);

#define PEXITUINT32(RTN_VAL) \
    AdapterTracer::pExit(__cimple_local_proc_name, __FILE__, __LINE__, RTN_VAL);

#define PEXITTHROW(CODE) \
    log (FL,"Exit: %s %u", __cimple_local_proc_name, CODE);

#define PTRACEPEGASUSINSTANCE(INST) \
    logPegasusInstance(INST, LL_DBG, __FILE__, __LINE__);

// ARGS is format, ... NOTE: requires (())
#define PTRACE(ARGS) \
    do \
    { \
        if (_log_enabled_state) \
        { \
            Log_Call_Frame frame(LL_DBG, __FILE__, __LINE__); \
            frame.invoke ARGS; \
        } \
    } \
    while (0)
#else

// define all of the macros to be NULL
#define PENTRY(PROC_NAME)
#define PEXIT()
#define PEXIT_RTN_VAL(RTN_VAL)
#define PEXITBOOL(RTN_VAL)
#define PEXITUINT32(RTN_VAL)
#define PEXITTHROW(CODE)
#define PTRACE(ARGS)
#define PTRACEPEGASUSINSTANCE(INST)
#endif

// Class to implement trace functions. This class is compiled only
// when the adpater trace is enabled. This class is internal and should
// only be used through the macros above.

#ifdef ENABLE_ADAPTER_TRACE_OPT

class CIMPLE_CIMPLE_LINKAGE AdapterTracer
{
public:
    static void pEntry(const char* name, const char* file, size_t line);

    static void pExit(const char* name, const char* file, size_t line);

    static void pExit(const char* name, const char* file, size_t line,
                          bool value);

    static void pExit(const char* name, const char* file, size_t line,
                          int value);

    static void pExit(const char* name, const char* file, size_t line,
                          uint32 value);
private:
    // hide constructor & desctructor
    AdapterTracer();
    ~AdapterTracer();
};
#endif

CIMPLE_NAMESPACE_END

#endif /* _cimple_Adapter_Tracer_h */
