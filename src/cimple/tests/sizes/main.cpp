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
#include <cimple/config.h>
#include <cimple/Type.h>

using namespace cimple;

int main(int argc, char** argv)
{
    // Test size assumptions made by CIMPLE.

    assert(sizeof(long) == sizeof(void*));
    assert(sizeof(char) == 1);
    assert(sizeof(uint8) == 1);
    assert(sizeof(sint8) == 1);
    assert(sizeof(uint16) == 2);
    assert(sizeof(sint16) == 2);
    assert(sizeof(uint32) == 4);
    assert(sizeof(sint32) == 4);
    assert(sizeof(uint64) == 8);
    assert(sizeof(sint64) == 8);
    assert(sizeof(real32) == 4);
    assert(sizeof(real64) == 8);
    assert(sizeof(char16) == 2);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/sizes/main.cpp,v 1.6 2007/04/12 14:52:09 mbrasher-public Exp $");
