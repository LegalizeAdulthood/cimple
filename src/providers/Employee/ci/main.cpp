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

#define CIMPLE_TRACE printf("%d\n", __LINE__)

/* function to test a property in an instance for a specific value. Returns true
   if the value is correct
   @param instance The instance containing the property
   @param name The name of the property
   @param result result value for comparison
   @return boolean true if the property exists and the property has the
   same value as the result parameter
   NOTE: Requires that the property value be not null
*/
template <class T>
bool testProperty(const CIMInstance& instance, const char* name, const T result)
 {
    Uint32 pos;
    
    if((pos = instance.findProperty(name)) != PEG_NOT_FOUND)
    {
        CIMConstProperty p = instance.getProperty(pos);
        CIMValue v = p.getValue();
        if (v.isNull())
        {
            return false;
        }
        T myValue;
        v.get(myValue);
        return(myValue == result); 
    }
    else
        return false;
 }

int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connectLocal();

        // Define object path:

        CIMObjectPath cop("Employee.Id=4004");
        CIMInstance ci("Employee");
        ci.setPath(cop);
        
        const String NAMESPACE = "root/cimv2";
        
        ci.addProperty(CIMProperty("Id", Uint32(4004)));
        ci.addProperty(CIMProperty("First", String("Michael")));
        ci.addProperty(CIMProperty("Last", String("Jackson")));
        ci.addProperty(CIMProperty("Gender", Uint32(1)));
        ci.addProperty(CIMProperty("Active", Boolean(true)));

        // Invoke the method:

        CIMObjectPath cop2 = client.createInstance(NAMESPACE, ci);

        assert(cop.toString() == cop2.toString());
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    // Now try to get the instance and compare returned values.
    try
    {
        CIMClient client;
        client.connectLocal();

        // Define object path:

        CIMObjectPath cop("Employee.Id=4004");
        CIMInstance ci("Employee");
        ci.setPath(cop);

        // Invoke getInstance to confirm that the property was created:

        const String NAMESPACE = "root/cimv2";

        CIMInstance rtnInstance = client.getInstance(NAMESPACE, cop);
  
        assert(rtnInstance.findProperty("Gender") != PEG_NOT_FOUND);      
        assert(rtnInstance.findProperty("Id") != PEG_NOT_FOUND);
        assert(rtnInstance.findProperty("First") != PEG_NOT_FOUND);        
        assert(rtnInstance.findProperty("Last") != PEG_NOT_FOUND);         
        assert(rtnInstance.findProperty("Active") != PEG_NOT_FOUND); 
 
        // test all property values       
        assert(testProperty(rtnInstance, "ID", Uint32(4004)));
        assert(testProperty(rtnInstance, "First", String("Michael")));
        assert(testProperty(rtnInstance, "Last", String("Jackson")));
        assert(testProperty(rtnInstance, "Active", true));
       
        // delete the instance       
        client.deleteInstance(NAMESPACE, cop);        
   
    }
    
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
