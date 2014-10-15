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

#include <brevity/brevity.h>
#include "All_Class_Hnd.h"
#include "All_Part_Hnd.h"

using namespace cimple;

void test1(Client& c)
{
    // Create instance:

    All_Part_Hnd part;
    part.Key_value(1701);

    Datetime now = Datetime::now();

    All_Class_Hnd h1;
    h1.Key_value(1721);
    h1.booleanScalar_value(true);
    h1.uint8Scalar_value(8);
    h1.sint8Scalar_value(-8);
    h1.uint16Scalar_value(16);
    h1.sint16Scalar_value(-16);
    h1.uint32Scalar_value(32);
    h1.sint32Scalar_value(-32);
    h1.uint64Scalar_value(64);
    h1.sint64Scalar_value(-64);
    h1.real32Scalar_value(32.0);
    h1.real64Scalar_value(64.0);
    h1.stringScalar_value("Hello World");
    h1.datetimeScalar_value(now);
    h1.instanceScalar_value(part);
    h1.objectScalar_value(part);
    h1.booleanArray_value(Array<boolean>::make(true, false, true));
    h1.uint8Array_value(Array<uint8>::make(8, 8, 8));
    h1.sint8Array_value(Array<sint8>::make(-8, -8, -8));
    h1.uint16Array_value(Array<uint16>::make(16, 16, 16));
    h1.sint16Array_value(Array<sint16>::make(-16, -16, -16));
    h1.uint32Array_value(Array<uint32>::make(32, 32, 32));
    h1.sint32Array_value(Array<sint32>::make(-32, -32, -32));
    h1.uint64Array_value(Array<uint64>::make(64, 64, 64));
    h1.sint64Array_value(Array<sint64>::make(-64, -64, -64));
    h1.real32Array_value(Array<real32>::make(32.0, 32.0, 32.0));
    h1.real64Array_value(Array<real64>::make(64.0, 64.0, 64.0));
    h1.char16Array_value(Array<char16>::make('A', 'B', 'C'));
    h1.datetimeArray_value(Array<Datetime>::make(now, now, now));
    h1.stringArray_value(Array<String>::make("Red", "Green", "Blue"));

    c.create_instance("root/cimv2", h1);

    // Get instance back and compare:

    All_Class_Ref ref;
    ref.Key_value(1721);
    All_Class_Hnd h2(c.get_instance("root/cimv2", ref));

    h1.print();
    h2.print();

    assert(h1 == h2);
}

void test2(Client& c)
{
    const String ns = "root/cimv2";
    All_Class_Ref ref;
    ref.Key_value(1721);

    {
        Arg<boolean> result = ref.booleanReturn(c, ns);
        assert(!result.null());
    }

}

int main()
{
    Client client;

    try
    {
        client.connect("http://localhost:5989/cimxml");
        test1(client);
        test2(client);
    }
    catch (Exception& e)
    {
        printf("Exception: %s\n", e.message().c_str());
    }

    return 0;
}
