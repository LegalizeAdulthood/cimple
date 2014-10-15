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

#include <cimple/config.h>
#include "Time.h"

#ifdef CIMPLE_VXWORKS
# include <sys/times.h>
#else
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
#endif

CIMPLE_NAMESPACE_BEGIN

const uint64 Time::USEC = 1;
const uint64 Time::MSEC = 1000;
const uint64 Time::SEC = 1000000;

uint64 Time::now()
{
#ifdef CIMPLE_WINDOWS_MSVC
    struct posix::timeval tv;
#else
    struct timeval tv;
#endif
    struct timezone ignore;
    memset(&tv, 0, sizeof(tv));
    memset(&ignore, 0, sizeof(ignore));

    gettimeofday(&tv, &ignore);
    return uint64(tv.tv_sec) * uint64(1000000) + uint64(tv.tv_usec);
}

void Time::sleep(uint64 timeout_usec)
{
#ifdef CIMPLE_WINDOWS_MSVC

    Sleep((DWORD)(timeout_usec / 1000));

#else

    timeval tv = { timeout_usec / 1000000, timeout_usec % 1000000 };
    select(0, 0, 0, 0, &tv);

#endif
}

CIMPLE_NAMESPACE_END

