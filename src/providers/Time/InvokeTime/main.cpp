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

#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

Uint32 SetTime(CIMClient& client, const CIMDateTime& Time)
{
    try
    {
        Array<CIMParamValue> inParams;
        Array<CIMParamValue> outParams;
        const String NAMESPACE = "root/cimv2";
        const String methodName = "SetTime";

        inParams.append(CIMParamValue("Time", Time));

        CIMValue returnValue = client.invokeMethod(
            NAMESPACE,
            CIMObjectPath("CMPL_Time"),
            methodName,
            inParams,
            outParams);

        assert(outParams.size() == 0);
        Uint32 tmp;
        returnValue.get(tmp);
        return tmp;
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    return 0;
}

Uint32 GetTime(CIMClient& client, CIMDateTime& Time)
{
    try
    {
        Array<CIMParamValue> inParams;
        Array<CIMParamValue> outParams;
        const String NAMESPACE = "root/cimv2";
        const String methodName = "GetTime";

        CIMValue returnValue = client.invokeMethod(
            NAMESPACE,
            CIMObjectPath("CMPL_Time"),
            methodName,
            inParams,
            outParams);

        assert(outParams.size() == 1);

        for (Uint32 i = 0; i < outParams.size(); i++)
        {
            CIMParamValue pv = outParams[i];

            if (CIMName(pv.getParameterName()) == CIMName("Time"))
            {
                CIMValue v = pv.getValue();
                v.get(Time);
            }
        }

        Uint32 tmp;
        returnValue.get(tmp);
        return tmp;
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    return 0;
}

int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

        CIMDateTime inTime("20070101120000.123456-360");

        Uint32 result = SetTime(client, inTime);

        CIMDateTime outTime;
        result = GetTime(client, outTime);

        assert(inTime == outTime);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
