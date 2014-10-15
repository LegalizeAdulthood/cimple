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
#include "Erp2.h"

using namespace cimple;

int main(int argc, char** argv)
{
    Erp2* inst = Erp2::create();
    assert(inst != 0);

    inst->w.value = "Hello";
    inst->x.value = 99;
    inst->y.value.append(String("one"));
    inst->y.value.append(String("two"));
    inst->y.value.append(String("three"));


    inst->z.value.append(String("aaa"));
    inst->z.value.append(String("bbb"));
    inst->z.value.append(String("ccc"));

    assert(inst->w.value == "Hello");
    assert(inst->x.value == 99);
    assert(inst->y.value[0] == "one");
    assert(inst->y.value[1] == "two");
    assert(inst->y.value[2] == "three");
    assert(inst->z.value[0] == "aaa");
    assert(inst->z.value[1] == "bbb");
    assert(inst->z.value[2] == "ccc");

    Erp2* inst2 = inst->clone();
    assert(inst2->w.value == "Hello");
    assert(inst2->x.value == 99);
    assert(inst2->y.value[0] == "one");
    assert(inst2->y.value[1] == "two");
    assert(inst2->y.value[2] == "three");
    assert(inst2->z.value[0] == "aaa");
    assert(inst2->z.value[1] == "bbb");
    assert(inst2->z.value[2] == "ccc");

    // print(inst);
    // print(inst2);
    nullify_properties(inst);
    // print(inst);

    Erp2::destroy(inst);
    Erp2::destroy(inst2);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

