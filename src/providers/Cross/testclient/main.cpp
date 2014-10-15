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
#include <cimple/Provider.h>

/******************************************************************************
*   This test clients tests the capability for cross namespace associations
*   delivered from the Cross provider.
*
******************************************************************************/

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

Boolean verbose = false;

int main(int argc, char** argv)
{
    verbose = (getenv ("PEGASUS_TEST_VERBOSE")) ? true : false;

    // Provide option of getting namespaces from command line

    CIMNamespaceName NamespaceLeft;
    if (argc == 2)
    {
        NamespaceLeft = argv[1];
    }
    else
    {
        NamespaceLeft = "root/PG_Interop";
    }

    CIMNamespaceName NamespaceRight;
    if (argc == 3)
    {
        NamespaceRight = argv[2];
    }
    else
    {
        NamespaceRight = "root/cimv2";
    }

    if (verbose)
    {
        printf("Test namespace Left = %s, namespace Right = %s\n",
            (const char *) NamespaceLeft.getString().getCString(),
            (const char *) NamespaceRight.getString().getCString());
    }

    try
    {
        CIMClient client;
        client.connect("localhost", 5988, "", "");

        // test associations for key = 1. This is an association with
        // Left in LeftNamespace and Right in RightNamespace and a single
        // instance
        {
            CIMObjectPath copLeft("Left.Key=1");
            CIMObjectPath copRight("Right.Key=1");
            CIMName rtnClassName("Cross");
            CIMName LClass("Left");
            CIMName RClass("Right");

            // Test reference returns

            Array<CIMObjectPath> rnL= client.referenceNames(NamespaceLeft,
                                                              copLeft);
            assert(rnL.size() == 1);
            assert(rnL[0].getClassName() == rtnClassName);
            assert(rnL[0].getNameSpace() == NamespaceLeft);

            Array<CIMObjectPath> rnR= client.referenceNames(NamespaceRight,
                                                              copRight);
            assert(rnR.size() == 1);
            assert(rnR[0].getClassName() == rtnClassName);
            assert(rnR[0].getNameSpace() == NamespaceRight);

            // get associator names cross namespace from left to right   
            
            Array<CIMObjectPath> anL= client.associatorNames(NamespaceLeft,
                                                              copLeft);
        
            assert(anL.size() == 1);
            assert(anL[0].getNameSpace() == NamespaceRight);
            assert(anL[0].getClassName() == RClass);
        
            // get associatorNames cross namespace from right to left.
        
            Array<CIMObjectPath> anR= client.associatorNames(NamespaceRight,
                                                              copRight);
        
            assert(anR.size() == 1);
            assert(anR[0].getNameSpace() == NamespaceLeft);
            assert(anR[0].getClassName() == LClass);
            //
            // get associators cross namespace from left to right
            // Key = 1.  This key returns a cross namespace association.
            // 
        
            Array<CIMObject> aL= client.associators(NamespaceLeft, copLeft);
        
            assert(aL.size() == 1);
            assert(aL[0].getPath().getNameSpace() == NamespaceRight);
            assert(aL[0].getPath().getClassName() == RClass);
            //
            // get associatorNames cross namespace from right to left.
            // Key = 1. This key returns cross namespace association
            // 
        
            Array<CIMObject> aR= client.associators(NamespaceRight, copRight);
        
            assert(aR.size() == 1);
            assert(aR[0].getPath().getNameSpace() == NamespaceLeft);
            assert(aR[0].getPath().getClassName() == LClass);
        }

        // 
        // Above tests with Key 2 which is non-cross namespace association
        // That is returned from Cross Association.

       {

           CIMObjectPath copLeft("Left.Key=2");
           CIMObjectPath copRight("Right.Key=2");
        
            Array<CIMObjectPath> anL= client.associatorNames(NamespaceLeft,
                                                              copLeft);
        
            assert(anL.size() == 1);
            assert(anL[0].getNameSpace() == NamespaceLeft);
        
        
            Array<CIMObjectPath> anR= client.associatorNames(NamespaceRight,
                                                              copRight);
        
            assert(anR.size() == 1);
            assert(anR[0].getNameSpace() == NamespaceRight);

        
            Array<CIMObject> aL= client.associators(NamespaceLeft, copLeft);
        
            assert(aL.size() == 1);
            assert(aL[0].getPath().getNameSpace() == NamespaceLeft);

         
            Array<CIMObject> aR= client.associators(NamespaceRight, copRight);
        
            assert(aR.size() == 1);
            assert(aR[0].getPath().getNameSpace() == NamespaceRight);
        }

        // test associations for key = 3. This is an association with
        // Left in LeftNamespace and Right in RightNamespace and a single
        // instance. Also, the association is in the subclass, not the Cross
        // class.
        {
            CIMObjectPath copLeft("Left.Key=3");
            CIMObjectPath copRight("Right.Key=3");
            CIMName rtnClassName("CrossSubClass");

            Array<CIMObjectPath> rnL= client.referenceNames(NamespaceLeft,
                                                              copLeft);
            assert(rnL.size() == 1);
            assert(rnL[0].getClassName() == rtnClassName);
            assert(rnL[0].getNameSpace() == NamespaceLeft);

            Array<CIMObjectPath> rnR= client.referenceNames(NamespaceRight,
                                                              copRight);
            assert(rnR.size() == 1);
            assert(rnR[0].getClassName() == rtnClassName);
            assert(rnR[0].getNameSpace() == NamespaceRight);

            // get associator names cross namespace from left to right   
            
            Array<CIMObjectPath> anL= client.associatorNames(NamespaceLeft,
                                                              copLeft);
        
            assert(anL.size() == 1);

            assert(anL[0].getClassName() == "Right");
            assert(anL[0].getNameSpace() == NamespaceRight);
        
            // get associatorNames cross namespace from right to left.
        
            Array<CIMObjectPath> anR= client.associatorNames(NamespaceRight,
                                                              copRight);
        
            assert(anR.size() == 1);
            assert(anR[0].getNameSpace() == NamespaceLeft);

            //
            // get associators cross namespace from left to right
            // Key = 1.  This key returns a cross namespace association.
            // 
        
            Array<CIMObject> aL= client.associators(NamespaceLeft, copLeft);
        
            assert(aL.size() == 1);
            assert(aL[0].getPath().getNameSpace() == NamespaceRight);

            //
            // get associatorNames cross namespace from right to left.
            // Key = 1. This key returns cross namespace association
            // 
        
            Array<CIMObject> aR= client.associators(NamespaceRight, copRight);
        
            assert(aR.size() == 1);
            assert(aR[0].getPath().getNameSpace() == NamespaceLeft);
        }

    }
    catch(CIMException& e)
    {
        PEGASUS_STD(cerr) << "Error: CIMException " << e.getMessage() 
            << " StatusCode = " << e.getCode()
            << PEGASUS_STD(endl);
        exit(1);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: Exception " << e.getMessage() 
            << PEGASUS_STD(endl);
        exit(1);
    }

    catch( ... )
    {
        PEGASUS_STD(cerr) << "Error: Exception"
            << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
