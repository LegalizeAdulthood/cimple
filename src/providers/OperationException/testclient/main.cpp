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
                assert(false);
                break;
            }
            case ASSOCS:
            {
                assert(false);
                break;
            }
            case REFNAMES:
            {
                assert(false);
                break;
            }
            case REFS:
            {
                assert(false);
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
        test_op(client,GETINST, Pegasus::CIM_ERR_NOT_FOUND, 60, false, false);
        // Not valid code if provider is trying support get_instance. This is
        // the code provider uses to use the default and enumerate_instances.
        //test_GETINST(client, Pegasus::CIM_ERR_NOT_SUPPORTED, 61);
        test_op(client,GETINST, Pegasus::CIM_ERR_INVALID_PARAMETER, 62, false, false);
        test_op(client,GETINST, Pegasus::CIM_ERR_ACCESS_DENIED, 63, false, false);
        test_op(client,GETINST, Pegasus::CIM_ERR_FAILED, 64, false, false);

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
        //test_op(client,REFS, Pegasus::CIM_ERR_NOT_FOUND, 60, false, false);
        /*CHKSRC*/
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
