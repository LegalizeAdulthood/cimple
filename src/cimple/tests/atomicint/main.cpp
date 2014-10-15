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
    TODO:
        Create multi thread atomic int test.  The current test is
        simply confirmation of the APIs.
*/

#include <cassert>
#include <cimple/Atomic_Counter.h>
#include <pthread.h>
#include <cimple/Time.h>
#include <cimple/Thread.h>
#include <cimple/Array.h>

using namespace cimple;

#define TRACE CIMPLE_TRACE;

// Simple test to assure that basic
void test01()
{
    Atomic_Counter a(0);

    assert(a.get() == 0);

    a.inc();

    assert(a.get() == 1);

    a.dec();

    assert(a.get() == 0);

    a.inc();

    assert(a.dec_and_test());

    a.inc();
    a.inc();

    Atomic_Counter b = a;

    assert(b.get() == 2);

    assert(a.get() == b.get());

    assert(!a.dec_and_test());
    assert(a.dec_and_test());
}


int main(int argc, char** argv)
{


    test01();


    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

