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
#include "boolean.h"

CIMPLE_NAMESPACE_BEGIN

int str_to_boolean(const char* s, boolean& x)
{
    if (tolower(s[0]) == 't' &&
        tolower(s[1]) == 'r' &&
        tolower(s[2]) == 'u' &&
        tolower(s[3]) == 'e' &&
        tolower(s[4]) == '\0')
    {
        x = true;
        return 0;
    }

    if (tolower(s[0]) == 'f' &&
        tolower(s[1]) == 'a' &&
        tolower(s[2]) == 'l' &&
        tolower(s[3]) == 's' &&
        tolower(s[4]) == 'e' &&
        tolower(s[5]) == '\0')
    {
        x = false;
        return 0;
    }

    return -1;
}

CIMPLE_NAMESPACE_END
