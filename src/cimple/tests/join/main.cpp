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

/*
    Test the thread and join functions.  Creates a number of threads
    each of which calls a function to sleep and then exit.  After starting
    the threads, the main thread waits for these threads to join the
    main thread.  Tests that each thread returns the proper return argument.
*/

#include <cassert>
#include <cimple/Thread.h>
#include <cimple/Time.h>

using namespace cimple;

static void* _proc(void* arg)
{
    char* str = (char*)arg;
    // printf("[%s]\n", str);
    Time::sleep(Time::SEC);

    Thread::exit(arg);

    return arg;
}

int main(int argc, char** argv)
{
    // Single thread test.  Used to find memory leak.
    //Thread myThread;

//  {
//      const char STR[] = "abc";
//      int r = Thread::create_joinable(myThread, _proc, (void*)strdup(STR));
//      assert(r == 0);
//  }
//
//  {
//      void* value = 0;
//      int r = Thread::join(myThread, value);
//
//      assert(r == 0);
//      assert(strcmp((char*)value,"abc") == 0);
//
//      free(value);
//  }

    // create a single detached thread and wait for it to complete
    {

        Thread myThread;
        const char str[] = "abc";
        int r = Thread::create_detached(myThread, _proc, (void*)str);
        assert(r == 0);

        Time::sleep(3 * Time::SEC);
    }
    return 0;  // enable this to just do one thread for memory leak testing


    // Test to create multiple joinable strings and then wait to join them.

    const size_t N = 164;
    Thread threads[N];

    for (size_t i = 0; i < N; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        int r = Thread::create_joinable(threads[i], _proc, strdup(buffer));
        assert(r == 0);
    }

    for (size_t i = 0; i < N; i++)
    {
        // Create corresponding counter for join.
        char buffer[64];
        sprintf(buffer, "%d", int(i));

        // execute the join
        void* value = 0;
        int r = Thread::join(threads[i], value);
        // printf("join[%s][%s]\n", (char*)value, buffer);
        assert(r == 0);

        // test that we have returned the proper arg value
        assert(strcmp(buffer, (char*)value) == 0);
        free(value);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

