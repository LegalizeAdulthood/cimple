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
#include <cimple/cimple.h>

using namespace cimple;

void test(const char* name, Type expected_type)
{
    Type type;

    int status = type_name_to_type(name, type);
    assert(status == 0);
    assert(type == expected_type);
}

int main(int argc, char** argv)
{
    printf("Test+++ %s\n",argv[0]);
    test("boolean", BOOLEAN);
    test("uint8", UINT8);
    test("sint8", SINT8);
    test("uint16", UINT16);
    test("sint16", SINT16);
    test("uint32", UINT32);
    test("sint32", SINT32);
    test("uint64", UINT64);
    test("sint64", SINT64);
    test("real32", REAL32);
    test("real64", REAL64);
    test("char16", CHAR16);
    test("string", STRING);
    test("datetime", DATETIME);
    test("BOOLEAN", BOOLEAN);
    test("UINT8", UINT8);
    test("SINT8", SINT8);
    test("UINT16", UINT16);
    test("SINT16", SINT16);
    test("UINT32", UINT32);
    test("SINT32", SINT32);
    test("UINT64", UINT64);
    test("SINT64", SINT64);
    test("REAL32", REAL32);
    test("REAL64", REAL64);
    test("CHAR16", CHAR16);
    test("STRING", STRING);
    test("DATETIME", DATETIME);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
