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
    Test of the Ref class defined in cimple/Ref.h
*/
#include <cassert>
#include <cimple/config.h>
#include <cimple/String.h>
#include <cimple/Instance.h>
#include <cimple/Ref.h>
#include <cassert>

#include "X.h"
#include "Y.h"

#define verbose_test
using namespace cimple;

// Functions to simplify the tests

void _cprint(const char* x)
{
#ifdef verbose_test
    printf("%s\n", x);
#endif
}
void _cprint(const String& x)
{
#ifdef verbose_test
    printf("%s\n", x.c_str());
#endif
}

// create an instance and destroy it
void test01()
{
    X* x = X::create(true);
    destroy(x);
}

//create an instance and Ref it.  Ref eventually destroys the instance
void test02()
{
    // creating the ref means that the instance is destroyed when
    // the ref goes out of scope
    X* x = X::create(true);
    Ref<Instance> y(x);
}

void test03()
{
    // creating the ref means that the instance is destroyed when
    // the ref goes out of scope
    X* x = X::create(true);
    Ref<Instance> y(x);

    Instance* z = y.steal();
    /// Once we steal the instance we need to destroy it.
    destroy(z);
}

// test pointer retrieval
void test04()
{
    X* x = X::create(true);
    Ref<Instance> y(x);
    Instance* w = y.ptr();
    assert(identical(x,w));
}

// unref with reset
void test05()
{
    X* x = X::create(true);
    Ref<Instance> y(x);
    y.reset();
}
// reset and recover instance
void test06()
{
    X* x = X::create(true);
    Ref<Instance> y(x);
    Instance* w;
    y.reset(w);
}
// test operator bool
void test07()
{
    X* x = X::create(true);
    Ref<Instance> y(x);

    assert( ( y ) );

    printf("test07 Operator bool test.( y ) returns %s\n", (( y )? "true" : "false"));

    // steal returns the pointer and zeros it in the Ref
    Instance* z = y.steal();

    assert( !y );

    destroy(z);

    printf("test07 Operator bool test. ( y ) returns %s\n", (( y )? "true" : "false"));
}

// test count function
void test08()
{
    X* x = X::create(true);
    Ref<Instance> y(x);
    printf("test08 count = %zd\n", y.count());
}

// Direct insertion of created instance into instance ref.
void test09()
{
    Ref<Instance> x(X::create(true));
    Instance* y = x.ptr();
    assert(x.count() == 1);
    printf("test09 count = %zd\n", x.count());
}

// rest assignment and corresponding count increments.
void test10()
{
    Ref<Instance> x(X::create(true));
    printf("test10 count = %zd\n", x.count());
    assert(x.count() == 1);

    Ref<Instance> y = x;
    printf("test10 count = %zd\n", x.count());
    assert(x.count() == 2);
}

// confirm Ref pointer is zero after reset
void test11()
{
    X* x = X::create(true);
    Ref<Instance> y(x);
    y.reset();
    Instance* z;
    assert( (z = y.ptr()) == NULL);
}


int main(int argc, char *argv[])
{
    // execute the test in the main thread
    test01();
    test02();
    test03();
    test04();
    test05();
    //test06();   // This one generates general sig error
    test07();
    test08();
    test09();
    test10();
    test11();

    printf("\n+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}



