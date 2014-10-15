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

const String NAMESPACE = "root/cimv2";

Uint32 SetReturnCount(CIMClient& client, Uint32 returnCount,
    Uint32& prevReturnCount)
{
    try
    {
        Array<CIMParamValue> inParams;
        Array<CIMParamValue> outParams;
        const String methodName = "returnCount";

        inParams.append(CIMParamValue(methodName, returnCount));

        CIMValue returnValue = client.invokeMethod(
            NAMESPACE,
            CIMObjectPath("Arrays"),
            methodName,
            inParams,
            outParams);

        assert(outParams.size() == 1);

        for (Uint32 i = 0; i < outParams.size(); i++)
        {
            CIMParamValue pv = outParams[i];

            if (CIMName(pv.getParameterName()) == CIMName("prevReturnCount"))
            {
                CIMValue v = pv.getValue();
                v.get(prevReturnCount);
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

void printInstance(const CIMInstance& instance)
{

}

//testArray(CIMType type, const CIMValue& v)
//{
//
//}

void testProperty(const CIMInstance& instance,
    const CIMName& name,
    Uint32 returnCount)
 {
    Uint32 pos = instance.findProperty(name);
    assert(pos != PEG_NOT_FOUND);
    CIMConstProperty p = instance.getProperty(pos);
    CIMValue v = p.getValue();
    assert(v.isArray());
    cout << "array size (getArraySize() method) = " <<  v.getArraySize()
    <<  endl;

    CIMType type = v.getType();

    // ISSUE : Why are we returning nonzero getArraySize.  This should
    // be zero for anything that is not fixed size
    // Need to call specific function for each type to test the array
    // values, etc.

}
int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

        Array<CIMInstance> instances = client.enumerateInstances(NAMESPACE,
            "Arrays");

        assert(instances.size() == 1);

        printInstance(instances[0]);

        CIMInstance instance = instances[0];

        // get countReturned property value
        Uint32 returnCount;
        if (Uint32 pos = instance.findProperty("returnCount") != PEG_NOT_FOUND)
        {
            CIMConstProperty p = instance.getProperty(pos);
            CIMValue v = p.getValue();
            // assert value type == Uint32
            v.get(returnCount);
            cout << "returnCount property = " << returnCount << endl;
        }
        else
            assert(false);

        testProperty(instance, CIMName("arr"), returnCount);
    }

    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
