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

#include "MOF_Date_Time.h"

//
// yyymmddhhmmss.mmmmmmsutc
// dddddddhhmmss.mmmmmm:utc
//

bool MOF_Date_Time::valid(const char* datetime)
{
    const char DIGITS[] = "0123456789";
    const char ZEROS[] = "0";
    char ch;

    //
    // Check the length:
    //

    if (strlen(datetime) != 24)
        return false;

    //
    // The first thirteen characters must be digits:
    //

    if (strspn(datetime, DIGITS) != 13)
        return false;

    //
    // Check for colon separator:
    //

    if (datetime[13] != '.')
        return false;

    //
    // The next six characters must be digits:
    //

    if (strspn(datetime + 14, DIGITS) != 6)
        return false;

    //
    // Check for sign or colon:
    //

    ch = datetime[20];

    if (ch != '-' && ch != '+' && ch != ':')
        return false;

    //
    // Check that the last three characters are digits (zeros for intervals).
    //

    if (ch == ':')
    {
        if (strspn(datetime + 21, ZEROS) != 3)
            return false;
    }
    else
    {
        if (strspn(datetime + 21, DIGITS) != 3)
            return false;
    }

    return true;
}

