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

#include <cassert>
#include <cimple/config.h>
#include <cimple/Scheduler.h>

using namespace cimple;

const uint64 SECOND = 1000 * 1000;

Scheduler sched;

static uint64 _timer(void* arg)
{
    const char* str = (const char*)arg;

    printf("_timer(%s)\n", str);

    if (str[0] == '1')
        return 1 * SECOND;

    if (str[0] == '2')
        return 2 * SECOND;

    if (str[0] == '3')
        return 3 * SECOND;

    if (str[0] == '4')
    {
        sched.add_timer(4 * SECOND, _timer, (void*)"4");
        return 0;
    }

    return 0;
}

int main(int argc, char** argv)
{
    sched.add_timer(3 * SECOND, _timer, (void*)"3");
    sched.add_timer(2 * SECOND, _timer, (void*)"2");
    sched.add_timer(1 * SECOND, _timer, (void*)"1");
    sched.add_timer(4 * SECOND, _timer, (void*)"4");

    for (;;)
    {
        printf("inside...\n");
        sched.dispatch();
    }

    printf("+++++ passed all tests\n");

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/scheduler/main.cpp,v 1.4 2007/03/07 20:18:10 mbrasher-public Exp $");
