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
 * printf variable args functions for generating char* returns 
 * or file output based on the printf pattern. 
 */
#ifndef _cimple_io_h
#define _cimple_io_h

#include <cstdarg>
#include "config.h"
#include "linkage.h"
#include "String.h"

CIMPLE_NAMESPACE_BEGIN

/**
 * Return a CIMPLE String formatted string in allocated memory 
 * based on the input format definition string and the variable 
 * number of arguments that follow the format string.
 * @param format containing the printf format definition. 
 * @param ... variable number of input parameters dependent on 
 *        the format definition input parameter
 * @return String with formatted string.
 */

CIMPLE_PRINTF_ATTR(1, 2)
CIMPLE_CIMPLE_LINKAGE 
String string_printf(const char* format, ...);

/**
 * Append a CIMPLE String formatted string to str variable 
 * based on the input format definition string and the variable 
 * number of arguments that follow the format string.
 * @param format containing the printf format definition. 
 * @param ... variable number of input parameters dependent on 
 *        the format definition input parameter
 * @return String with formatted string.
 */
CIMPLE_PRINTF_ATTR(2, 3)
CIMPLE_CIMPLE_LINKAGE 
void string_append_printf(String& str, const char* format, ...);

/**
 * Return a char* formatted string in allocated memory based on 
 * the input format definition string and the variable number of 
 * arguments that follow the format string. This function 
 * allocates the memory to include the formatted output. The 
 * user must free this memory. 
 * @param format containing the printf format definition. 
 * @param ... variable number of input parameters dependent on 
 *        the format definition input parameter
 * @return char* with formatted string.  It is the users 
 *         responsibility to free the memory allocated for the
 *         return.
 */
CIMPLE_PRINTF_ATTR(1, 2)
CIMPLE_CIMPLE_LINKAGE 
char* str_printf(const char* format, ...);

/**
 * Return a char* formatted string in allocated memory based on 
 * the input format definition format string and the variable 
 * arguments list.  This funciton can be used to define 
 * additional variable arguments print functions that will 
 * return formate char* strings 
 * @param format const char* format definition using the 
 *               standard C++ format definitions
 * @param ap va_list variable list input. 
 *  
 * EXAMPLE: 
 * // The following is a new function that the 
 * // user can define to specialize printf to a char*. It uses 
 * the the standard functions to map the variable number of 
 * input variables to a va_list 
 * 
 * char * str_vprintf_demo(const char* fmt, ...) 
    {
        size_t size;
        va_list ap;
        va_start(ap, fmt);
        char* rtn;
        rtn = str_vprintf(fmt, ap);
        va_end(ap);
        return(rtn);
    }
 *  
 */ 
CIMPLE_CIMPLE_LINKAGE 
char* str_vprintf(const char* format, va_list ap);

/**
 * Similar to str_vprintf except returns String and manages
 * local memory usage.
 */
CIMPLE_CIMPLE_LINKAGE 
String string_vprintf(const char* format, va_list ap);

/**
 * printf to std output with and indent defined by the level 
 * parameter, format defined by the format parameter and the 
 * variable list of arguments. The user must free this memory.
 * @param level size_t indent level (multiples of 4 characters)
 * @param format C printf format definition string 
 * @param ... variable number of input variables to be used by 
 *        the format definition string
 * 
 * @return CIMPLE_CIMPLE_LINKAGE int with number of characters 
 *         output.
 */
CIMPLE_CIMPLE_LINKAGE
int iprintf(size_t level, const char* format, ...);

/**
 * printf to file defined by os with indent defined by the level 
 * parameter, format definition string defined by format and 
 * following variables to be formatted for the file 
 * 
 * @param os 
 * @param level 
 * @param format 
 * 
 * @return CIMPLE_CIMPLE_LINKAGE int 
 */
CIMPLE_PRINTF_ATTR(3, 4)
CIMPLE_CIMPLE_LINKAGE
int ifprintf(FILE* os, size_t level, const char* format, ...);

/**
 * printf to String returned with indent defined by the level 
 * parameter, format definition string defined by format and 
 * following variables to be formatted for the file. This is the parallel 
 * to ifprintf but with output to a string. 
 * @param str String to which formatted data is appended
 * @param level 
 * @param format 
 */
CIMPLE_CIMPLE_LINKAGE
void istring_printf(String& str, size_t level, const char* format, ...);

CIMPLE_NAMESPACE_END

#endif /* _cimple_io_h */
