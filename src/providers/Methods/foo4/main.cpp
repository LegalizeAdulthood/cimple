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

/*
    test of the foo4 method which contains string array in and out.
*/
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connectLocal();

        // Define instance name:

        CIMObjectPath instanceName("Methods.key=7777");

        // Define input arguments:

        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        // Invoke the method:

        const String NAMESPACE = "root/cimv2";
        const String methodName = "foo4";

        Array<String> arrayIn;
        arrayIn.append("abc");
        arrayIn.append("def");
        arrayIn.append("ghijklm");


        in.append(CIMParamValue("arr1", arrayIn));

        CIMValue value = client.invokeMethod(
            NAMESPACE,
            instanceName,
            methodName,
            in,
            out);

        {
            assert(value.getType() == CIMTYPE_UINT32);
            Uint32 t;
            value.get(t);
            assert(t == 999);
        }

        // Check output argument:

        assert(out.size() == 1);
        {
            assert(out[0].getParameterName() == "arr2");
            CIMValue value = out[0].getValue();
            Array<String> arrayOut;
            value.get(arrayOut);
            assert(arrayOut == arrayIn);
        }
        
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
