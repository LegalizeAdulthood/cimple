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
//#include <Pegasus/Common/XmlWriter.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

#define NAMESPACE "root/interop"

// original simple modify test based on the fixed definition in the
// provider
void test01(CIMClient& client)
{
    try
    {
        // Define instance name:

        CIMInstance inst("CIMPLE_Widget");
        inst.addProperty(CIMProperty("Key", Uint32(1234)));
        inst.addProperty(CIMProperty("Color", String("Red")));

        client.modifyInstance("root/cimv2", inst);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }
}

// More complete test of create, modify, delete.
void test02(CIMClient& client)
{
    try
    {
        // Create an instance       
        CIMInstance inst("CIMPLE_Widget");       
        inst.addProperty(CIMProperty("Key", Uint32(5678)));
        inst.addProperty(CIMProperty("Color", String("Cyan")));
        inst.addProperty(CIMProperty("Flag", Boolean(true)));
        
        CIMObjectPath cop = client.createInstance(NAMESPACE, inst);
        assert(cop.toString() == "CIMPLE_Widget.Key=1234");

        // Get instance and check for identical property status.

        CIMInstance inst2 = client.getInstance(NAMESPACE, cop);
        Uint32 pos;
        assert(pos = inst2.findProperty("Key") != PEG_NOT_FOUND);

        CIMProperty pkey = inst2.getProperty(pos);
        Uint32 key;
        CIMValue v = pkey.getValue();
        v.get(key);
        assert(key == 1234);
        
        assert(pos = inst2.findProperty("Color") != PEG_NOT_FOUND);
        CIMProperty pcolor = inst2.getProperty(pos);
        String color;
        v = pcolor.getValue();
        v.get(color);
        assert(color == "Cyan");       

        assert(pos = inst2.findProperty("Flag") != PEG_NOT_FOUND);        
        CIMProperty pflag = inst2.getProperty(pos);
        Boolean flag;
        v = pflag.getValue();
        v.get(flag);
        assert(flag == true);        
        
        // Modify the created instance:

        CIMInstance instModify("CIMPLE_Widget");
        instModify.addProperty(CIMProperty("Key", Uint32(5678)));
        instModify.addProperty(CIMProperty("Color", String("Red")));
        instModify.addProperty(CIMProperty("Flag", Boolean(false)));

        client.modifyInstance(NAMESPACE, instModify);

        
        client.deleteInstance(NAMESPACE,cop);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }
}

int main(int argc, char** argv)
{
    CIMClient client;
    client.connect("localhost", 5988, String(), String());
    test01(client);
    //test02(client);
    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
