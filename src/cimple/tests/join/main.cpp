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
#include <cimple/Thread.h>
#include <cimple/Time.h>

using namespace cimple;

static void* _proc(void* arg)
{
    char* str = (char*)arg;
    // printf("[%s]\n", str);
    Time::sleep(1000 * 1000);

    Thread::exit(arg);

    return arg;
}

int main(int argc, char** argv)
{
    const size_t N = 64;
    Thread threads[N];

    for (size_t i = 0; i < N; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        Thread::create_joinable(threads[i], _proc, strdup(buffer));
    }

    for (size_t i = 0; i < N; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));

        void* value = 0;
        int r = Thread::join(threads[i], value);
        // printf("join[%s][%s]\n", (char*)value, buffer);
        assert(r == 0);
        assert(strcmp(buffer, (char*)value) == 0);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/join/main.cpp,v 1.4 2007/03/07 20:17:33 mbrasher-public Exp $");
