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

#include "linkage.h"
#include "sys/time.h"

#include <cassert>
#include <windows.h>

POSIX_NAMESPACE_BEGIN

static UINT64 _get_epoch_in_usec()
{
    // Get time as nanoseconds.
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER uli = { ft.dwLowDateTime, ft.dwHighDateTime };

    // Convert to POSIX time (Epoch: January 1, 1970, 00:00:00).
    uli.QuadPart -= 0X19DB1DED53E8000;

    return uli.QuadPart / UINT64(10);
}

int gettimeofday(struct timeval* tv, struct timezone* tz)
{
    memset(tv, 0, sizeof(struct timeval));
    memset(tz, 0, sizeof(struct timezone));

    UINT64 usec = _get_epoch_in_usec();

    tv->tv_sec = (long)(usec / 1000000);
    tv->tv_usec = (long)(usec % 1000000);

    // FIX: how do we get the UTC offset?

    return 0;
}

POSIX_NAMESPACE_END
