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
    Display functions for Pegasus C++ CIMInstance object.  These functions
    were defined primarily for the Pegasus provider adapter and provide
    display of instances formatted roughly as instance mof.
    Since they are primarily used in the adapter they do not display
    CIMClasses (i.e. the case where an embedded object might be a class).
    These are intended as diagnostic tools and the format of the display
    may change at any time.
    NOTE: These functions are also used in the CIMPLE test clients to
    display instances (i.e. cimple::print(x); where x is CIMInstance x).
    We do not need corresponding functions for CIMObject path because there
    is a toString(...) function in Pegasus.
    TODO: Consider replacing this with Pegasus functions to a) reduce
    size of CIMPLE, become more standard with Pegasus and use Pegasus
    libraries.  The two possibilities are the mof output and the
    Print.h mechanism when that is cleaned up for future Pegasus.
 
    Includes:
      print - print to cout
      formatToString - Create String with formatted instance. This is
          core function used by print and log.
      log - output to log file
*/

#ifndef _pegadapter_print_h
#define _pegadapter_print_h

#include <cimple/cimple.h>
#include "pegasus.h"
#include <cimple/log.h>

CIMPLE_NAMESPACE_BEGIN

/**
    Print a CIM Instance to standard output formatted roughly as mof is 
    This is primarily a diagnostic tool. The format of the output may change
    This function is defined primarily to support diagnostics on the Pegasus
    adapter and clients. * formatted. 
    @param ci CIMInstance (Pegasus C++ object format) of instance
 */
void print(const Pegasus::CIMConstInstance& ci);

/**
    Generate a String containing a CIM Instance formatted roughly as mof. 
    Puts the formatted value of the instance in the CIMPLE String parameter str.
    This is normally internal to be used by the Pegasus adapter.
    The indent is an integer representing the level of indent for this instance.
    While this is primarily a support function for print to cout and log
    of instances it was included as a function available to the adapter in
    case the string itself might be useful formatted. 
    @param ci CIMInstance (Pegasus C++ object format) of instance
    @param indent_level - Used internally, ignore on external call
 */
void formatToString(String& str,
           const Pegasus::CIMConstInstance& ci,
                    size_t indent_level = 0);
/**
 * Output a formatted display of a Pegasus CIMInstance to the CIMPLE log 
 * file. This function is intended to be used by the CIMPLE pegasus adapter 
 * and should be used through a macro call so that it can be completely 
 * disabled when not required. 
 * 
 * @param ci Instance to be displayed
 * @param lvl  Log level
 * @param file Code Source Line (ex. __FILE__)
 * @param line Code source line (ex. __LINE__)
 */
void logPegasusInstance(const Pegasus::CIMConstInstance& ci,
                        const Log_Level lvl,const char* file, int line);


CIMPLE_NAMESPACE_END

#endif /* _pegadapter_print_h */
