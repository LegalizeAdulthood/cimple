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

#include <cimple/Array.h>
#include <cassert>
#include <cstdio>

using namespace cimple;

void print(Array_String& v)
{
    for (size_t i = 0; i < v.size(); i++)
        printf("%s\n", v[i].c_str());

    printf("\n");
}

int main(int argc, char** argv)
{
    {
        Array_uint32 v;

        v.resize(2);
        v[0] = 2;
        v[1] = 3;
        assert(v.size() == 2);
        assert(v[0] == 2);
        assert(v[1] == 3);

        v.append(4);
        assert(v.size() == 3);
        assert(v[0] == 2);
        assert(v[1] == 3);
        assert(v[2] == 4);

        v.insert(0, 1);
        assert(v.size() == 4);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);
        assert(v[3] == 4);

        v.insert(0, 0);
        assert(v.size() == 5);
        assert(v[0] == 0);
        assert(v[1] == 1);
        assert(v[2] == 2);
        assert(v[3] == 3);
        assert(v[4] == 4);

        v.remove(0, 1);
        assert(v.size() == 4);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);
        assert(v[3] == 4);

        v.remove(3, 1);
        assert(v.size() == 3);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);

        v.remove(1, 2);
        assert(v.size() == 1);
        assert(v[0] == 1);

        v.remove(0, 1);
        assert(v.size() == 0);

        for (size_t i = 0; i < 100; i++)
            v.append(i);

        Array_uint32 w(v);
        Array_uint32 x(v);

        assert(w.size() == 100);

        for (size_t i = 0; i < 100; i++)
            assert(v[i] == w[i]);

        assert(v.capacity() >= v.size());
        assert(w.capacity() >= w.size());

        w.remove(0, 50);

        for (size_t i = 50; i < 100; i++)
            assert(w[i] == i);

        v.clear();
        w.clear();
        assert(v.size() == 0);
        assert(w.size() == 0);
    }

    {
        Array_String z;
        z.append(String("zero"));
        z.append(String("one"));
        z.append(String("two"));
        assert(z.size() == 3);

        assert(z[0] == "zero");
        assert(z[1] == "one");
        assert(z[2] == "two");

        Array_String w = z;
        assert(w.size() == 3);
        assert(w[0] == "zero");
        assert(w[1] == "one");
        assert(w[2] == "two");

        w.append(String("three"));
        assert(w.size() == 4);
        assert(w[0] == String("zero"));
        assert(w[1] == String("one"));
        assert(w[2] == "two");
        assert(w[3] == "three");

        w.remove(0);
        assert(w.size() == 3);
        assert(w[0] == "one");
        assert(w[1] == "two");
        assert(w[2] == "three");

        w.insert(0, String("zero"));
        assert(w.size() == 4);
        assert(w[0] == "zero");
        assert(w[1] == "one");
        assert(w[2] == "two");
        assert(w[3] == "three");

        w.remove(0);
        w.remove(2);
        assert(w.size() == 2);
        assert(w[0] == "one");
        assert(w[1] == "two");

        w.remove(0, 2);
        assert(w.size() == 0);


        Array_String x;
        x = w;

        Array_String y;
        y.append("junk");
        y = w;

        Array_String xx(y);

        // print(w);
    }

    {
        Array<uint32> x;
        const uint32 data[] = { 10, 20, 30 };
        x.append(data, 3);
        assert(x[0] == 10);
        assert(x[1] == 20);
        assert(x[2] == 30);
    }

    {
        const uint32 data[] = { 10, 20, 30 };
        Array<uint32> x(data, 3);
        assert(x.size() == 3);
        assert(x[0] == 10);
        assert(x[1] == 20);
        assert(x[2] == 30);
    }

    {
        const boolean data[] = { true, false };
        Array<boolean> x(data, 2);
        assert(x.size() == 2);
        assert(x[0] == true);
        assert(x[1] == false);

        Array<boolean> y;
        y = x;
        x = y;

        Array<boolean> z;
        z.append(true);
        z = y;
    }

    assert(sizeof(Array<String>) == sizeof(__Array_Base));

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

