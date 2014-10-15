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

#ifndef _cimple_platform_VXWORKS_internal_h
#define _cimple_platform_VXWORKS_internal_h

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sockLib.h>
#include <selectLib.h>
#include <ioLib.h>

#ifndef va_copy
# define va_copy __va_copy
#endif

inline int mkdir(const char* path, int mode)
{
    return ::mkdir(path);
}

inline int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
        return -1;

    tv->tv_sec = ts.tv_sec;
    tv->tv_usec = ts.tv_nsec / 1000;

    if (tz != NULL)
    {
        struct tm tm;
        time_t t;

        if (localtime_r(&t, &tm) == 0)
        {
            tz->tz_minuteswest = 0;
            tz->tz_dsttime = tm.tm_isdst;
        }
        else
        {
            tz->tz_minuteswest = 0;
            tz->tz_dsttime = 0;
        }
    }

    return 0;
}

#endif /* _cimple_platform_VXWORKS_internal_h */
