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
#include <cassert>
#include <cstdio>
#include "SomeClass.h"

using namespace cimple;

int main(int argc, char** argv)
{
    SomeClass* inst = SomeClass::create();

    inst->prop1.value = "hello";
    inst->prop2.value = 7654321;
    inst->prop3.value = true;

    inst->prop4.value.append("one");
    inst->prop4.value.append("two");
    inst->prop4.value.append("three");

    inst->prop5.value.append(100);
    inst->prop5.value.append(200);
    inst->prop5.value.append(300);

    inst->prop6.value.append(true);
    inst->prop6.value.append(false);
    inst->prop6.value.append(true);

    inst->other1 = OtherClass::create();
    print(inst);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/print/main.cpp,v 1.3 2007/03/07 20:18:13 mbrasher-public Exp $");
