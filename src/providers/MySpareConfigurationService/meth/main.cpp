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
#include <cassert>

PEGASUS_USING_PEGASUS;
using namespace std;

void call_func()
{
    try
    {
        // Connect.

        CIMClient client;
        client.connectLocal();

        //
        // uint32 AssignSpares(
        //       [IN(false), OUT] CIM_ConcreteJob REF Job, 
        //       [IN, OUT(false)] CIM_StoragePool REF InPool, 
        //       [Required, IN, OUT (false)] CIM_StorageExtent REF InExtents[], 
        //       [IN, OUT (false)] CIM_StorageRedundancySet REF RedundancySet);
        //

        // Build input arguments.

        Array<CIMParamValue> in;

        // InPool:

        CIMObjectPath InPool("CIM_StoragePool.InstanceID=\"1\"");
        in.append(CIMParamValue("InPool", InPool));

        // InExtents:

        CIMObjectPath StorageExtent(
            "MyStorageExtent."
            "SystemCreationClassName=\"CIM_StorageExtent\","
            "SystemName=\"mike\","
            "CreationClassName=\"CIM_StorageExtent\","
            "DeviceID=\"1\",");

        Array<CIMObjectPath> InExtents;
        InExtents.append(StorageExtent);
        InExtents.append(StorageExtent);
        InExtents.append(StorageExtent);
        in.append(CIMParamValue("InExtents", InExtents));

        // RedundancySet:
        CIMObjectPath RedundancySet(
            "CIM_StorageRedundancySet.InstanceID=\"1\"");
        in.append(CIMParamValue("RedundancySet", RedundancySet));

        // Invoke method.

        CIMObjectPath target("MySpareConfigurationService."
            "SystemCreationClassName=\"Mike\","
            "SystemName=\"Mike\","
            "CreationClassName=\"MySpareConfigurationService\"");

        Array<CIMParamValue> out;

        CIMValue value = client.invokeMethod(
            "root/cimv2",
            target,
            "AssignSpares",
            in,
            out);

        // Expect one output argument.
        assert(out.size() == 1);

        // Check return value.
        assert(value.getType() == CIMTYPE_UINT32);
        Uint32 return_value = 0;
        value.get(return_value);
        assert(return_value == 100);
    }
    catch(Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }
}

int main(int argc, char** argv)
{
    call_func();

    cout << "+++++ passed all tests" << endl;

    return 0;
}

