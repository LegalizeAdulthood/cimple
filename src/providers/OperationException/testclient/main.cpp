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

/*==============================================================================
    This test program tests the possible cimple provider defined error codes
    against the codes actually returned from the provider.

    It first tells the provider what  cimple return code to use for the next
    operation with the setException method and then executes that
    operation expecting a certain pegasus error code. 

    It tests both the case where the "optional" provider functions such as
    get_instance actually return codes and the case where they use the
    unsupported response.
=============================================================================*/

#include <pegasus/utils/pegasus.h>
#include <pegasus/utils/print.h>
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>
#include <cimple/Provider.h>

#define NAMESPACE "root/cimv2"

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

Boolean verbose = false;

/*
    Send the defined provider retun code to the provider.
    The code is the cimple exception code as defined in the cimple
    header file provider.h
*/
Boolean setReturnCode(CIMClient& client, Uint32 code,
                      Boolean getInstanceDefault,
                      Boolean associatorsDefault,
                      CIMObjectPath& cop)
{
    Array<CIMParamValue> in;
    Array<CIMParamValue> out;

    in.append(CIMParamValue("Exception", code));
    in.append(CIMParamValue("getInstanceDefault", getInstanceDefault));
    in.append(CIMParamValue("associatorsDefault", associatorsDefault));
    CIMValue value = client.invokeMethod(NAMESPACE,cop,"setException", in, out);

    Uint32 rv;
    value.get(rv);

    // There is no expectation of an error response from the provider
    if (value.isNull() || rv != 0)
    {
        printf("%s(%d): error\n", __FILE__, __LINE__);
        return false;
    }
     if (out.size() != 0)
    {
        printf("%s(%d): error\n", __FILE__, __LINE__);
        return false;
    }
    return true;
}

// enum to define the operations called in test_op
enum opEnum
{
    GETINST = 1,
    ENUMINST = 2,
    MODINST = 3,
    CRINST = 4,
    DELINST = 5,
    ASSOCNAMES = 6,
    ASSOCS = 7,
    REFNAMES = 8,
    REFS = 9
};

/*
    test a single operation using the operation defined by op.
    First we send the desired CIMPLEStatusCode with setException
    and then execute the operation and test the status returned agains
    PegExceptionCode.
    All operations should fail and generate an exception.
*/

String _toString(Boolean x)
{
    return (x? "true" : "false");
}

/*
    Test one operation.   Provide this function with the CIMPLE and
    Pegasus exceptions codes.  It sets the provider to provide
    the defined response and then calls it with the operation defined
    by opEnum.  The return error is compared to the expected
    Pegasus Exception code.

    If the return does not match, we assert.
*/
void test_op(CIMClient& client,
    opEnum op,
    Uint32 PegExceptionCode,
    Uint32 CimpleStatusCode,
    Boolean getInstanceDefault,
    Boolean associatorsDefault)
{
    if (verbose)
    {
        printf("Operation = %u "
               "Pegasus Except code = %u msg = %s. Cimple Status code = %u "
               " getInstanceDefault = %s. associatorsDefault = %s\n",
           op,
           PegExceptionCode,
           cimStatusCodeToString((CIMStatusCode)PegExceptionCode),
           CimpleStatusCode,
           (const char *)_toString(getInstanceDefault).getCString(),
           (const char *)_toString(associatorsDefault).getCString()
        );
    }


    // create a dummy instance and objectPath for tests

    CIMInstance ci("CIMPLE_Exception");
    ci.addProperty(CIMProperty("Key", Uint32(9999)));
    CIMObjectPath cop("CIMPLE_Exception.Key=9999");
    ci.setPath(cop);

    // Tell provider what code to return
    assert(setReturnCode(client, CimpleStatusCode,
                         getInstanceDefault, associatorsDefault, cop));

    // Execute the defined operation to generate exception
    // These calls should always result in exceptions
    try
    {
        switch (op)
        {
            case GETINST:
            {
                CIMInstance inst;
                inst = client.getInstance(NAMESPACE,cop);
                break;
            }
            case ENUMINST:
            {
                Array<CIMInstance> x = client.enumerateInstances(NAMESPACE,
                                            cop.getClassName());
                break;
            }
            case MODINST:
            {
                client.modifyInstance(NAMESPACE,ci);
                break;
            }
            case CRINST:
            {
                CIMObjectPath p = client.createInstance(NAMESPACE,ci);
                break;
            }
            case DELINST:
            {
                client.deleteInstance(NAMESPACE,cop);
                break;
            }
            case ASSOCNAMES:
            {
                Array<CIMObjectPath> paths = client.associatorNames(NAMESPACE,
                                                              cop);
                break;
            }
            case ASSOCS:
            {
                Array<CIMObject> objects = client.associators(NAMESPACE,
                                                              cop);
                break;
            }
            case REFNAMES:
            {
                Array<CIMObjectPath> paths = client.referenceNames(NAMESPACE,
                                                              cop);
                break;
            }
            case REFS:
            {
                Array<CIMObject> objects = client.references(NAMESPACE,
                                                              cop);
                break;
            }
        }

        // all functions should take exception so we error if we get here
        assert(false);
    }

    catch(CIMException& e)
    {
        if (verbose)
        {
            PEGASUS_STD(cerr) << "Passed " 
                << e.getMessage()
                << " for Code " << e.getCode()
                << " CIMPLE status " << CimpleStatusCode
                << PEGASUS_STD(endl);
        }
        assert(e.getCode() == (int)PegExceptionCode);
    }

    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        assert(false);
    }
}

//temp support for the CIMPLE internal error codes.
//Copied here in lieu of include simple because of issue with C++ namespaces
// for the moment.  Copied from cimple/Provider.h
// 
enum Get_Instance_Status
{
    GET_INSTANCE_OK = 0,
    GET_INSTANCE_NOT_FOUND = 60,
    GET_INSTANCE_UNSUPPORTED = 61,
    GET_INSTANCE_INVALID_PARAMETER = 62,
    GET_INSTANCE_ACCESS_DENIED = 63,
    GET_INSTANCE_FAILED = 64,
};

enum Enum_Instances_Status
{
    ENUM_INSTANCES_OK = 0,
    ENUM_INSTANCES_FAILED = 70,
    ENUM_INSTANCES_ACCESS_DENIED = 71,
};

enum Create_Instance_Status
{
    CREATE_INSTANCE_OK = 0,
    CREATE_INSTANCE_DUPLICATE = 80,
    CREATE_INSTANCE_UNSUPPORTED = 81,
    CREATE_INSTANCE_INVALID_PARAMETER = 82,
    CREATE_INSTANCE_ACCESS_DENIED = 83,
    CREATE_INSTANCE_FAILED = 84,
};

enum Delete_Instance_Status
{
    DELETE_INSTANCE_OK = 0,
    DELETE_INSTANCE_NOT_FOUND = 90,
    DELETE_INSTANCE_UNSUPPORTED = 91,
    DELETE_INSTANCE_ACCESS_DENIED = 92,
    DELETE_INSTANCE_FAILED = 93,
};

enum Modify_Instance_Status
{
    MODIFY_INSTANCE_OK = 0,
    MODIFY_INSTANCE_NOT_FOUND = 100,
    MODIFY_INSTANCE_UNSUPPORTED = 101,
    MODIFY_INSTANCE_INVALID_PARAMETER = 102,
    MODIFY_INSTANCE_ACCESS_DENIED = 103,
    MODIFY_INSTANCE_FAILED = 104,
};

enum Enum_Associator_Names_Status
{
    ENUM_ASSOCIATOR_NAMES_OK = 0,
    ENUM_ASSOCIATOR_NAMES_FAILED = 110,
    ENUM_ASSOCIATOR_NAMES_UNSUPPORTED = 111,
    ENUM_ASSOCIATOR_NAMES_ACCESS_DENIED = 112,
};

enum Enum_Associators_Status
{
    ENUM_ASSOCIATORS_OK = 0,
    ENUM_ASSOCIATORS_FAILED = 170,
    ENUM_ASSOCIATORS_UNSUPPORTED = 171,
    ENUM_ASSOCIATORS_ACCESS_DENIED = 172,
};

enum Enum_References_Status
{
    ENUM_REFERENCES_OK = 0,
    ENUM_REFERENCES_FAILED = 120,
    ENUM_REFERENCES_UNSUPPORTED = 121,
    ENUM_REFERENCES_ACCESS_DENIED = 122,
};

enum Invoke_Method_Status
{
    INVOKE_METHOD_OK = 0,
    INVOKE_METHOD_FAILED = 130,
    INVOKE_METHOD_UNSUPPORTED = 131,
    INVOKE_METHOD_ACCESS_DENIED = 132,
};

enum Enable_Indications_Status
{
    ENABLE_INDICATIONS_OK = 0,
    ENABLE_INDICATIONS_FAILED = 140,
};

enum Disable_Indications_Status
{
    DISABLE_INDICATIONS_OK = 0,
    DISABLE_INDICATIONS_FAILED = 150,
};

enum Get_Repository_Status
{
    GET_REPOSITORY_OK = 0,
};


int main(int argc, char** argv)
{
    verbose = (getenv ("PEGASUS_TEST_VERBOSE")) ? true : false;

    try
    {
        CIMClient client;
        client.connect("localhost", 5988, "", "");

        //// ENUMERATE, GET, CREATE, DELETE Operation tests

        // TODO: We use numeric codes today for the provider internal error
        // return codes because of conflicts with namespaces.  Fix this so we
        // can use the sympolic codes and avoid future issues.

        //
        // Test all valid provider internal codes against the expected
        // Pegasus return codes for the case where the get_client is actually
        // returning a code other than UNSUPPORTED.
        //

        /* NOCHKSRC*/
        test_op(client,GETINST, Pegasus::CIM_ERR_NOT_FOUND, GET_INSTANCE_NOT_FOUND, false, false);
        // Not valid code if provider is trying support get_instance. This is
        // the code provider uses to use the default and enumerate_instances.
        //test_GETINST(client, Pegasus::CIM_ERR_NOT_SUPPORTED, 61);
        test_op(client,GETINST, Pegasus::CIM_ERR_INVALID_PARAMETER, GET_INSTANCE_INVALID_PARAMETER, false, false);
        test_op(client,GETINST, Pegasus::CIM_ERR_ACCESS_DENIED, GET_INSTANCE_ACCESS_DENIED, false, false);
        test_op(client,GETINST, Pegasus::CIM_ERR_FAILED, GET_INSTANCE_FAILED, false, false);

        test_op(client,ENUMINST, Pegasus::CIM_ERR_FAILED, 70, false, false);
        test_op(client,ENUMINST, Pegasus::CIM_ERR_ACCESS_DENIED, 71, false, false);

        test_op(client,CRINST, Pegasus::CIM_ERR_ALREADY_EXISTS, 80, false, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_NOT_SUPPORTED, 81, false, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_INVALID_PARAMETER, 82, false, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_ACCESS_DENIED, 83, false, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_FAILED, 84, false, false);

        test_op(client,DELINST,Pegasus::CIM_ERR_NOT_FOUND, 90, false, false);
        test_op(client,DELINST,Pegasus::CIM_ERR_NOT_SUPPORTED, 91, false, false);
        test_op(client,DELINST,Pegasus::CIM_ERR_ACCESS_DENIED, 92, false, false);
        test_op(client,DELINST,Pegasus::CIM_ERR_FAILED, 93, false, false);

        // Test responses when the get_instance provider function is using
        // the default reponse (UNSUPPORTED) so that the provider uses
        // enumerate_instance to find the instance.
        // 

        test_op(client,GETINST, Pegasus::CIM_ERR_NOT_FOUND, 60, true, false);

        // This test not supported if the getInstance function
        // function is set to default (i.e. use enum_instances). First,
        //  the not_supported is the get_instance provider response that 
        // results in trying the enumerate_instances option.  Second, it is 
        // illogical for enumerate to be supported and not get_instance.
        //test_op(client, Pegasus::CIM_ERR_NOT_SUPPORTED, 61);

        // Following not supported with default since it must come from enuminst
        // and there is no invalid_Param for invalid inst.
        //test_op(client,GETINST, Pegasus::CIM_ERR_INVALID_PARAMETER, 62, true, false);
  
        // The following are an impossible conditions.  We are trying to tell
        // the provider to always generate unsupported for get_instance and
        // expecting access_denied, etc..   If the enum mechanism generates the
        // access_denied response, we get it.  That is tested.  Therefore we
        // are commenting out these test
        // test_op(client,GETINST, Pegasus::CIM_ERR_ACCESS_DENIED, 63, true, false);
        // test_op(client,GETINST, Pegasus::CIM_ERR_FAILED, 64, true, false);

        test_op(client,ENUMINST, Pegasus::CIM_ERR_FAILED, 70, true, false);
        test_op(client,ENUMINST, Pegasus::CIM_ERR_ACCESS_DENIED, 71, true, false);

        test_op(client,CRINST, Pegasus::CIM_ERR_ALREADY_EXISTS, 80, true, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_NOT_SUPPORTED, 81, true, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_INVALID_PARAMETER, 82, true, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_ACCESS_DENIED, 83, true, false);
        test_op(client,CRINST, Pegasus::CIM_ERR_FAILED, 84, true, false);

        test_op(client,DELINST, Pegasus::CIM_ERR_NOT_FOUND, 90, true, false);
        test_op(client,DELINST, Pegasus::CIM_ERR_NOT_SUPPORTED, 91, true, false);
        test_op(client,DELINST, Pegasus::CIM_ERR_ACCESS_DENIED, 92, true, false);
        test_op(client,DELINST, Pegasus::CIM_ERR_FAILED, 93, true, false);

        //    ASSOCIATOR TESTS
        // 
        // Test for default associator definition in provider and real
        // get_instance
        // 

        //TODO: Finish these tests
        //test_op(client,REFS, Pegasus::CIM_ERR_FAILED, ENUM_REFERENCES_FAILED, false, false);
        //test_op(client,REFS, Pegasus::CIM_ERR_NOT_SUPPORTED, ENUM_REFERENCES_UNSUPPORTED, false, false);
        //test_op(client,REFS, Pegasus::CIM_ERR_ACCESS_DENIED, ENUM_REFERENCES_ACCESS_DENIED, false, false);

        //test_op(client,ASSOCS, Pegasus::CIM_ERR_FAILED, ENUM_ASSOCIATORS_FAILED, false, false);
        //test_op(client,ASSOCS, Pegasus::CIM_ERR_NOT_SUPPORTED, ENUM_ASSOCIATORS_UNSUPPORTED, false, false);
        //test_op(client,ASSOCS, Pegasus::CIM_ERR_ACCESS_DENIED, ENUM_ASSOCIATORS_ACCESS_DENIED, false, false);
        /*NOCHKSRC*/

        // Tests for exceptions to association requests that do not make
        // it to the provider.  Specifically, returning if there is an
        // error in the associator or reference classnames.  Should return OK.
        // 
        /*
        CIMObjectPath cop("CIMPLE_Exception.Key=9999");
        CIMName assocClass = "CIMPLE_ExceptionLink";
        assert(setReturnCode(client, ENUM_INSTANCES_OK,
                     true, true, cop));
        Array<CIMObject> objects;

        try
        {
            objects = client.associators(NAMESPACE,
                                          cop,
                                          assocClass);
    
            objects = client.references(NAMESPACE,
                                          cop,
                                          assocClass);
        }

        catch(CIMException& e)
        {
            if (verbose)
            {
                PEGASUS_STD(cerr) << "Failed Association Class Error Test " 
                    << e.getMessage()
                    << " for Code " << e.getCode()
                    << PEGASUS_STD(endl);
            }
            assert(false);
        }
    
        catch(Exception& e)
        {
            PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
            assert(false);
        }
        */

    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
