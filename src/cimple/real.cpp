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

#include <cctype>
#include "real.h"

CIMPLE_NAMESPACE_BEGIN

static int _parse_real(const char* s)
{
    /* [ "+" | "-" ] *decimalDigit "." 1*decimalDigit 
     * [ ( "e" | "E" ) [ "+" | "-" ] 1*decimalDigit ]
     */

    /* [ "+" | "-" ] */

    if (*s == '+' || *s == '-')
        s++;

    /* *decimalDigit */

    while (isdigit(*s))
        s++;

    /* "." */

    if (*s++ != '.')
        return -1;

    /* 1*decimalDigit */

    if (!isdigit(*s++))
        return -1;

    while (isdigit(*s))
        s++;

    if (*s == '\0')
        return 0;

    /* ( "e" | "E" ) */

    if (*s != 'e' && *s != 'E')
        return -1;

    s++;

    /* [ "+" | "-" ] */

    if (*s == '+' || *s == '-')
        s++;

    /* 1*decimalDigit */

    if (!isdigit(*s++))
        return -1;

    while (isdigit(*s))
        s++;

    if (*s == '\0')
        return 0;

    return -1;
}

int str_to_real64(const char* str, real64& x)
{
    char* end;

    if (_parse_real(str) != 0)
        return -1;

    x = strtod(str, &end);

    if (*end != '\0')
        return -1;

    return 0;
}

int str_to_real32(const char* str, real32& x)
{
    char* end;

    if (_parse_real(str) != 0)
        return -1;

    x = (float)strtod(str, &end);

    if (*end != '\0')
        return -1;

    return 0;
}

CIMPLE_NAMESPACE_END
