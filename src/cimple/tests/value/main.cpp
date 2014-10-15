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

#include <cimple/cimple.h>
#include <cimple/Value.h>
#include <cassert>
#include "MyClass.h"

using namespace cimple;

int main(int argc, char** argv)
{
    ///printf("Test+++ %s\n",argv[0]);
    {
        Value v;
        v.set_value(uint32(10));
        v.print();
    }

    {
        Value v;
        v.set_value("one");
        String s;
        v.get_value(s);
        assert(s == "one");
        v.print();
    }

    {
        Value v;
        Array_uint32 a;
        a.append(1);
        a.append(2);
        a.append(3);
        v.set_value(a);
        v.print();
    }

    {
        Value v;
        Array_String a;
        a.append("one");
        a.append("two");
        a.append("three");
        v.set_value(a);
        v.print();

        Value v2 = v;
        Value v3 = v2;
        v = v2;
    }

    {
        Value v;
        Array_Instance a;
        MyClass* inst = MyClass::create(true);
        inst->key.set("Hello World");
        a.append(clone(inst));
        a.append(clone(inst));
        unref(inst);
        v.set_value(a);
        v.print();

        Array_Instance b;
        v.get_value(b);

        for (size_t i = 0; i < b.size(); i++)
            print(b[i]);

        Value v2(v);
        Value v3;
        v3 = v;
        v = v2;
    }

    return 0;
}
