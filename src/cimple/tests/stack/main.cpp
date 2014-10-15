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

/* test of implementation of the stack functions defined in cimple/stack.h
*/
#include <cassert>
#include <cimple/Stack.h>
#include <cimple/Instance.h>

using namespace cimple;
    // test with stack of structure

    struct test
    {
        int number;
        String testString;

    };

int main(int argc, char** argv)
{
    // Test with simple integer stack

    Stack<int> s_int;
    assert(s_int.empty());
    s_int.push(1);
    assert(s_int.size() == 1);
    assert(!s_int.empty());
    assert(s_int.top() == 1);

    s_int.push(2);
    assert(s_int.size() == 2);
    assert(!s_int.empty());
    assert(s_int.top() == 2);

    s_int.pop();
    assert(s_int.size() == 1);
    assert(!s_int.empty());
    assert(s_int.top() == 1);

    s_int.pop();
    assert(s_int.empty());



    // test with structure

    Stack<test*> stest;
    assert(s_int.empty());

    test test1;
    test1.number = 1;
    test1.testString = "blah";

    Array<test*> x;


    //test* testp1 = test1;

    //stest.push(test1*);


    


    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

