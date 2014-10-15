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

#include <pegasus/utils/pegasus.h>
#include <pegasus/utils/print.h>
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

void test_enum(CIMClient& client)
{
    printf("===== test_enum()\n");

    try
    {
        Array<CIMInstance> set = client.enumerateInstances(
            "root/cimv2", "CMPL_Embedded");

        for (Uint32 i = 0; i < set.size(); i++)
        {
            cimple::print(set[i]);
        }
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        assert(0);
    }
}

void test_invoke(CIMClient& client)
{
    printf("===== test_invoke()\n");

    try
    {
        // Call foo1().

        CIMInstance ci;
        {
            Array<CIMParamValue> inParams;
            Array<CIMParamValue> outParams;

            CIMValue value = client.invokeMethod(
                "root/cimv2",
                CIMObjectPath("CMPL_Embedded.Key=1"),
                "foo1",
                inParams,
                outParams);

            assert(value.getType() == CIMTYPE_INSTANCE);

            value.get(ci);
            // cimple::print(ci);
        }

        // Call foo2().
        {
            Array<CIMParamValue> inParams;
            Array<CIMParamValue> outParams;

            CIMInstance arg2("CMPL_Embedded2");
            arg2.addProperty(CIMProperty("Key", Uint32(22222)));

            inParams.append(CIMParamValue("arg1", ci));
            inParams.append(CIMParamValue("arg2", arg2));

            CIMValue value = client.invokeMethod(
                "root/cimv2",
                CIMObjectPath("CMPL_Embedded.Key=1"),
                "foo2",
                inParams,
                outParams);

            for (size_t i = 0; i < outParams.size(); i++)
            {
                const CIMParamValue& pv = outParams[i];
                const CIMValue v = pv.getValue();

                if (pv.getParameterName() == "arg3")
                {
                    CIMInstance t;
                    assert(v.getType() == CIMTYPE_INSTANCE);
                    v.get(t);
                    // cimple::print(t);
                }
            }

            // Check return value:
            {
                assert(value.getType() == CIMTYPE_STRING);
                String x;
                value.get(x);
                assert(x == "Hello");
            }
        }
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        assert(0);
    }
}

int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connectLocal();

        test_enum(client);
        test_invoke(client);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
