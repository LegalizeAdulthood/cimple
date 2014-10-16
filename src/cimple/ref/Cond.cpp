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

#include <errno.h>
#include "Cond.h"
#include "Time.h"

CIMPLE_NAMESPACE_BEGIN

int Cond::wait(Mutex& mutex, uint64 timeout_usec)
{
    struct timespec ts;
    uint64 deadline_usec = Time::now() + timeout_usec;
    uint64 deadline_sec = deadline_usec / 1000000;
    ts.tv_sec = deadline_sec;
    ts.tv_nsec = (deadline_usec % 1000000) * 1000;

    for (;;)
    {
        switch (pthread_cond_timedwait(&_cond, &mutex._mut, &ts))
        {
            case EINTR:
                continue;

            case ETIMEDOUT:
                return -1;

            case 0:
                return 0;

            default:
                CIMPLE_ASSERT(0);
        }
    }

    // Unreachable:
    return 0;
}

CIMPLE_NAMESPACE_END
