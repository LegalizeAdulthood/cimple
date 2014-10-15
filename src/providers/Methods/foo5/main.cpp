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
    Simple fixed client test for foo 5 method.
*/
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

Sint32 findParam(const Array<CIMParamValue>& out, const String& argName)
{
    for (Uint32 i = 0; i < out.size() ; i++)
    {
        if (out[i].getParameterName() == argName)
        {
            return i;
        }
    }
    return -1;
}

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
        const String methodName = "foo5";

        Uint32 in_arg = 234567;
        Uint32 in_out_arg = 123456;
        in.append(CIMParamValue("in_arg", in_arg));
        in.append(CIMParamValue("in_out_arg", in_out_arg));

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
            assert(t == 1200);
        }

        // Check output argument:

        assert(out.size() == 2);
        {
            Uint32 pos = 0;
            assert((pos = findParam(out, "in_out_arg")) != -1);
            assert(out[pos].getParameterName() == "in_out_arg");
            CIMValue value = out[0].getValue();
            Uint32 in_out_arg_rtn;
            value.get(in_out_arg_rtn);
            assert(in_out_arg_rtn == in_out_arg);

            assert((pos = findParam(out, "out_arg")) != -1);
            assert(out[pos].getParameterName() == "out_arg");
            CIMValue value1 = out[1].getValue();
            Uint32 out_arg_rtn;
            value1.get(out_arg_rtn);
            assert(out_arg_rtn == in_arg);
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
