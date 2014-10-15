/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include <cimple/cimple.h>
#include <cassert>
#include <cstdio>

using namespace cimple;

int main(int argc, char** argv)
{
    Property<uint32> a;
    a.value = 99;
    a.null = false;

    Property<cimple::boolean> b;
    b.value  = true;
    b.null = false;

    Property<cimple::String> c;
    c.value = String("hello");
    c.null = false;

    Property<Array_String> d;

    Property<Array_boolean> e;

    e.value.append(true);
    e.value.append(false);

    d.value.append(String("Red"));
    d.value.append(String("Green"));
    d.value.append(String("Blue"));

    a.value = 100;
    c.value = String("hello");

#if 0
    printf("%d\n", a());
    printf("%d\n", b());
    printf("%s\n", c.value.c_str());

    for (size_t i = 0; i < d.value.size(); i++)
	printf("%s\n", d()[i].c_str());


    printf("e: %d %d\n", e()[0], e()[1]);

    printf("f: %d %d %d\n", f()[0], f()[1], f()[2]);
    printf("g: %d %d %d\n", g()[0], g()[1], g()[2]);
#endif

#if 0
    printf("f: %d %d %d\n", f()[0], f()[1], f()[2]);
    printf("g: %d %d %d\n", g()[0], g()[1], g()[2]);
#endif

    // printf("f: %d %d %d\n", f()[0], f()[1], f()[2]);

    // printf("+++++ passed all tests\n");

    const Array_String& v = d.value;
    assert(v.size() == 3);
    assert(v[0] == "Red");
    assert(v[1] == "Green");
    assert(v[2] == "Blue");
    d.value.clear();
    d.null = true;
    assert(d.value.size() == 0);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
