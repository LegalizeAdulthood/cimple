/*
**==============================================================================
**
** Copyright (c) 2010 Michael Brasher, Karl Schopmeyer
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
    Debugging utilities to be used with the CMPI Provider.  These are only
    compiled when the CMPI_ADAPTER_DEBUG compiler flag is set.  See the
    Makefile.
        Display tools for cmpi that are compiled only in compile debug mode
        Includes:
            CMPIInstance and CMPIObjectPath
                - output to std output
                - output to file
                - format to string
                - output to CIMPLE log
*/
#ifndef _CMPI_Utils_h
#define _CMPI_Utils_h

#include <cimple/config.h>
#include <cimple/cimple.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmpi.h"

CIMPLE_NAMESPACE_BEGIN

/*
    Print the CMPIObjectPath or CMPIInstance to the  defined output file. 
*/

CMPIStatus printCMPIObjectPath(FILE* os,
                               const CMPIObjectPath* self,
                               size_t indent = 0);

CMPIStatus printCMPIInstance(FILE* os,
                             const CMPIInstance* self,
                             size_t indent = 0);

/*
    Print the CMPIObjectPath or CMPIInstance to std output 
*/

CMPIStatus printCMPIObjectPath(const CMPIObjectPath* self,
                               size_t indent = 0);

CMPIStatus printCMPIInstance(const CMPIInstance* self,
                             size_t indent = 0);

// Print the CIMPIObjectPath or CMPIInstance to a CIMPLE String

CMPIStatus printCMPIObjectPath(String& str,
                               const CMPIObjectPath* self,
                               size_t indent = 0);

CMPIStatus printCMPIInstance(String& str,
                             const CMPIInstance* self,
                             size_t indent = 0);

// Log a formatted CMPIObjectPath. This logs only in
// debug mode. These two methods differ in that they require the file and line
// information for the log.

CMPIStatus logCMPIObjectPath(const char* file, int line,
                             const CMPIObjectPath* self,
                             size_t indent = 0);

// Log a formatted CMPIInstanc to the log file with file/line info. This
// logs only in debug log mode. Note that this
CMPIStatus logCMPIInstance(const char* file, int line,
                           const CMPIInstance* self,
                           size_t indent = 0);

CIMPLE_NAMESPACE_END

#endif /* _CMPI_Utils_h */
