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

#include <cimple/config.h>
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

void test1()
{
    try
    {
        CIMClient client;
        client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

        // Define instance name:

        CIMObjectPath instanceName("RefArray.key=1");

        // Define input arguments:

        Array<CIMParamValue> inParams;
        Array<CIMParamValue> outParams;

        // Invoke the method:

        const String NAMESPACE = "root/cimv2";
        Array<CIMObjectPath> arr1;

        CIMObjectPath x0("RefArrayParam.key=1");
        x0.setNameSpace("root/cimv2");

        CIMObjectPath x1("RefArrayParam.key=2");
        x1.setNameSpace("root/cimv2");

        arr1.append(x0);
        arr1.append(x1);

        inParams.append(CIMParamValue("arr1", CIMValue(arr1)));

        CIMValue returnValue = client.invokeMethod(
            NAMESPACE,
            CIMObjectPath("RefArray.key=1"),
            "SendRefArray",
            inParams,
            outParams);

        assert(outParams.size() == 1);

        Array<CIMObjectPath> arr2;
        outParams[0].getValue().get(arr2);
        assert(arr2.size() == 2);

        CIMObjectPath y0 = arr2[0];
        CIMObjectPath y1 = arr2[1];

        assert(y0.identical(x0));
        assert(y1.identical(x1));

        Uint32 tmp;
        returnValue.get(tmp);
        assert(tmp == 123);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }
}

void test2()
{
    try
    {
        CIMClient client;
        client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

        // Define instance name:

        CIMObjectPath instanceName("RefArray.key=1");

        // Define input arguments:

        Array<CIMParamValue> inParams;
        Array<CIMParamValue> outParams;

        // Invoke the method:

        const String NAMESPACE = "root/cimv2";

        CIMValue arr1_value(CIMTYPE_REFERENCE, true);
        arr1_value.setNullValue(CIMTYPE_REFERENCE, true);
        inParams.append(CIMParamValue("arr1", arr1_value));

        CIMValue returnValue = client.invokeMethod(
            NAMESPACE,
            CIMObjectPath("RefArray.key=1"),
            "SendRefArray",
            inParams,
            outParams);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }
}

int main(int argc, char** argv)
{
    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);
    test1();
    test2();

    return 0;
}

