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

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/flags.h>
#include <cimple/cimple.h>
#include <cassert>
#include <cstdio>

using namespace cimple;

struct Class1
{
    Property<uint32> prop1;
    Property<String> prop2;
    Property<boolean> prop3;
    Property<Array_real32> prop5;
};

Meta_Property properties[] =
{
    {CIMPLE_FLAG_PROPERTY, "prop1", UINT32, 0, CIMPLE_OFF(Class1, prop1)},
    {CIMPLE_FLAG_PROPERTY, "prop2", STRING, 0, CIMPLE_OFF(Class1, prop2)},
    {CIMPLE_FLAG_PROPERTY, "prop3", BOOLEAN, 0, CIMPLE_OFF(Class1, prop3)},
    {CIMPLE_FLAG_PROPERTY, "prop5", REAL32, -1, CIMPLE_OFF(Class1, prop5)},
};

const size_t num_properties = CIMPLE_ARRAY_SIZE(properties);

int main(int argc, char** argv)
{
#if 0 
    for (size_t i = 0; i < num_properties; i++)
        printf("%s %d\n", properties[i].name, properties[i].offset);
#endif

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}
