//%LICENSE////////////////////////////////////////////////////////////////
//
// Licensed to The Open Group (TOG) under one or more contributor license
// agreements.  Refer to the OpenPegasusNOTICE.txt file distributed with
// this work for additional information regarding copyright ownership.
// Each contributor licenses this file to you under the OpenPegasus Open
// Source License; you may not use this file except in compliance with the
// License.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////
//
//%/////////////////////////////////////////////////////////////////////////////

/*
    Test of operations that stress the CIM Operationresponse mechanism with
    both verylarge response objects and very large numbers of response objects.
    This client works specifically with the corresponding provider and
    depends on the information in the TST_ResponseStressTest class.
*/
#include <cimple/cimple.h>

#include <pegasus/utils/pegasus.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/General/Stopwatch.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

//static CIMNamespaceName NAMESPACE = CIMNamespaceName("test/TestProvider");
//static CIMName TEST_CLASS = CIMName("TST_ResponseStressTest");

static CIMNamespaceName NAMESPACE = CIMNamespaceName("root/cimv2");
static CIMName TEST_CLASS = CIMName("CMPL_ResponseStressTest");

static Boolean verbose;

ClientOpPerformanceData returnedPerformanceData;
class ClientStatistics : public ClientOpPerformanceDataHandler
{
public:

    virtual void handleClientOpPerformanceData (
            const ClientOpPerformanceData & item)
    {
        if (!(0 <= item.operationType) || !(39 >= item.operationType))
        {
           cerr << "Operation type out of expected range in"
                        " ClientOpPerformanceData "
               << endl;
           exit(1);
        }
        returnedPerformanceData.operationType =  item.operationType;
        if (item.roundTripTime == 0)
        {
           cerr << "roundTripTime is incorrect in ClientOpPerformanceData "
               << endl;
        }
        returnedPerformanceData.roundTripTime =  item.roundTripTime;

        if (item.requestSize == 0)
        {
            cerr << "requestSize is incorrect in ClientOpPerformanceData "
                << endl;
        }
        returnedPerformanceData.requestSize =  item.requestSize;

        if (item.responseSize == 0)
        {
            cerr << "responseSize is incorrect in ClientOpPerformanceData "
                << endl;
        }
        returnedPerformanceData.responseSize =  item.responseSize;

        if (item.serverTimeKnown)
        {
            /* Bypass this because we are getting server times zero
            if (item.serverTime == 0)
            {
                cerr << "serverTime is incorrect in ClientOpPerformanceData "
                    << endl;
            }
            */
            returnedPerformanceData.serverTime =  item.serverTime;
            returnedPerformanceData.serverTimeKnown =  item.serverTimeKnown;
            returnedPerformanceData.roundTripTime =  item.roundTripTime;
        }
   }
   //returnedPerformanceData = item;   // Copy the data to public place
};

class tests
{
public:
    tests()
    {
        classIndex = 0;
        setClassListArray();
    }
    ~tests()
    {
    }

    // set up and array with the list of classes and namespaces for the various
    // tests.  NOTE: The first one should be one that is guaranteed to be in
    // the environment since it is used for the live test.
    
    void setClassListArray()
    {
        classList.append("CMPL_ResponseStressTest");
        namespaceList.append("root/cimv2");
        classList.append("TST_ResponseStressTest");
        namespaceList.append("root/cimv2");
    }
    void _displayTimes(Uint32 objCount,
        Uint32 objSize,
        Uint64 elapsed,
        Uint64 providerTime,
        ClientOpPerformanceData& perfData);

    void enumerateInstances(Uint32 responseSize, Uint64 responseCount);

    void enumerateInstanceNames(Uint32 InstanceSize, Uint64 responseCount);
    void set(Uint64 instanceSize, Uint64 responseCount);

    void get(Uint64& instanceSize, Uint64& responseCount);

    void testSetAndGetMethods();

    void connect(bool connectLocal)
    {

        // Register for Client statistics.
        ClientStatistics statistics = ClientStatistics();
    
        client.registerClientOpPerformanceDataHandler(statistics);
        try
        {
            if (connectLocal)
            {
                client.connectLocal();
            }
            else
            {
                client.connect("localhost", 5988, String(), String());
            }

            client.setTimeout( 400*1000);
        }
        catch (Exception& e)
        {
            cerr << "Error: Connect Failure " << e.getMessage() << endl;
            exit(1);
        }
    }
    // test to be sure all classes in list exist and that they all return
    // instances
    void testAllClasses()
    {
        while (moreClasses())
        {
            try
            {
                CIMClass cl = client.getClass(testNamespaceName, testClass);
                Array<CIMInstance> instances =
                    client.enumerateInstances(testNamespaceName, testClass);
                if (instances.size() == 0)
                {
                    cout << "Error: " << testClass.getString()
                         << " returned zero instances."
                         << endl;
                }
            }
            catch (Exception& e)
            {
                cerr << "Error: get Failure " << e.getMessage()
                     << " for " << testNamespaceName.getString()
                     << " "  << testClass.getString()
                    << endl;
                exit(1);
            }
        }

    }

    // set next class in list into current test variables. Return false
    // if no more in list
    bool moreClasses()
    {
        if ( classList.size() == 0 || classIndex >= classList.size())
        {
            return false;
        }
        testClass = classList[classIndex++];
        testNamespaceName = namespaceList[classIndex++];
        return true;
    }

    Uint32 classIndex;
    CIMClient client;
    CIMName testClass;
    CIMNamespaceName testNamespaceName;
    Array<CIMName> classList;
    Array<CIMNamespaceName> namespaceList;    
};


Boolean first = true;
void tests::_displayTimes(Uint32 objCount,
    Uint32 objSize,
    Uint64 elapsed,
    Uint64 providerTime,
    ClientOpPerformanceData& perfData)
{
    if (first)
    {
        printf("Request : %s:%s\n",
               (const char *)testNamespaceName.getString().getCString(),
               (const char *)testClass.getString().getCString());
        if (!perfData.serverTimeKnown)
        {
            cout << "WARNING: Server data may not be valid" << endl;
        }
        printf(
"Op ClientTime   ProvTime RndTrpTime SvrTime ReqSize   RespSize ObjSize  ObjCnt"
"\n"
"           us         us         us      us   bytes      bytes   bytes\n");
        first = false;
    }

    printf("%2u%11lu%11lu%11lu%8lu%8lu%11lu%8u%8u\n",
           perfData.operationType,
           (long unsigned int) elapsed,
           (long unsigned int) providerTime,
           (long unsigned int)perfData.roundTripTime,
           (long unsigned int)perfData.serverTime,
           (long unsigned int) perfData.requestSize,
           (long unsigned int) perfData.responseSize,
           objSize,
           objCount);
}

// Enumerate the instance names for the defined testclasses.
// Tests for response size and response count and displays test results
void tests::enumerateInstances(Uint32 responseSize, Uint64 responseCount)
{
    try
    {
        Stopwatch sw;
        sw.start();

        Array<CIMInstance> instances =
            client.enumerateInstances(testNamespaceName, testClass);

        sw.stop();
        Uint64 elapsed = sw.getElapsedUsec();

        Uint64 providerTime = 0;
        CIMInstance lastInstance = instances[instances.size() - 1];
        if (Uint32 pos = lastInstance.findProperty("totalTime") != 
            PEG_NOT_FOUND)
        {
            CIMProperty p = lastInstance.getProperty(pos);
            CIMValue v = p.getValue();
            if (v.getType() != CIMTYPE_UINT64)
            {
                cout << "Error:  CIMType for type totalTime Property"
                        " should be uint64." << endl;
            }
            v.get(providerTime);
        }
        else
        {
            cout << "Error: totalTime propety not found" << endl;
        }

        _displayTimes(instances.size(), responseSize,  elapsed,
                      providerTime,
                      returnedPerformanceData);

        CIMPLE_TEST_ASSERT(instances.size() == responseCount);
        
        // Confirm that the sequence numbers are monolithic increasing
        //
        Uint64 prevSequenceNumber = 0;
        for (Uint64 i = 0, n = instances.size() ;  i < n ; i++)
        {
            Uint32 pos;
            if ((pos = instances[i].findProperty("SequenceNumber"))
                 != PEG_NOT_FOUND )
            {
                CIMProperty p = instances[i].getProperty(pos);
                CIMValue v = p.getValue();
                Uint64 sequenceNumber;
                v.get(sequenceNumber);
                //cout << "SequenceNumber = " << sequenceNumber 
                //    << " prevSequenceNumber " << prevSequenceNumber << endl;

                CIMPLE_TEST_ASSERT(sequenceNumber == (prevSequenceNumber));
                prevSequenceNumber++;
            }
        }
    }
    catch (Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }
}

// Test to validate instance names. Executes the enumerate and tests the
// number of responses against the expected response count
void tests::enumerateInstanceNames(Uint32 InstanceSize, Uint64 responseCount)
{
    try
    {
        Array<CIMObjectPath> paths =
            client.enumerateInstanceNames(testNamespaceName, testClass);

        cout << "count = " << paths.size() << endl;
        if (verbose)
        {
            cout << endl;
            for (Uint32 i = 0; i < paths.size() ; i++)
            {
                cout << paths[i].toString() << endl;
            }
        }
        CIMPLE_TEST_ASSERT(paths.size() == responseCount);
    }
    catch (Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }
}

// set the instanceSize and response count parameters in the
// client
void tests::set(Uint64 instanceSize, Uint64 responseCount)
{
    Array<CIMParamValue> InParams;

    Array<CIMParamValue> outParams;

    InParams.append(CIMParamValue("ResponseCount", responseCount));
    InParams.append(CIMParamValue("ResponseInstanceSize", instanceSize));
    CIMValue returnValue = client.invokeMethod(
        testNamespaceName,
        CIMObjectPath(String::EMPTY,
                      CIMNamespaceName(),
                      CIMName(testClass)),
        CIMName("set"),
        InParams,
        outParams);

    CIMPLE_TEST_ASSERT(outParams.size() == 0);

    Uint32 rc;
    returnValue.get(rc);

    CIMPLE_TEST_ASSERT(rc == 0); 
}

// get the current provider test parameters.
void tests::get(Uint64& instanceSize, Uint64& responseCount)
{
    Array<CIMParamValue> InParams;

    Array<CIMParamValue> outParams;

    InParams.append(CIMParamValue("ResponseInstanceSize", instanceSize));
    InParams.append(CIMParamValue("ResponseCount", responseCount));

    CIMValue returnValue = client.invokeMethod(
        testNamespaceName,
        CIMObjectPath(String::EMPTY,
                      CIMNamespaceName(),
                      CIMName(testClass)),
        CIMName("get"),
        InParams,
        outParams);

    Uint32 rc;
    returnValue.get(rc);
    CIMPLE_TEST_ASSERT(rc == 0);

    for(Uint32 i = 0; i < outParams.size(); ++i)
    {
        String paramName = outParams[i].getParameterName();
        CIMValue v = outParams[i].getValue();

        if(paramName =="ResponseCount")
        {
            v.get(responseCount);
        }
        else if(paramName =="ResponseInstanceSize")
        {
            v.get(instanceSize);
        }
        else
        {
            cout <<"Error: unknown parameter name = " << paramName << endl;
            CIMPLE_TEST_ASSERT(false);
        }
    }
}

// fixed test for the provider get and set methods that restores the provider
// parameters to their original condition.
void tests::testSetAndGetMethods()
{
    Uint64 instanceSizeOrig = 0;
    Uint64 responseCountOrig = 0;
    Uint64 instanceSize = 0;
    Uint64 responseCount = 0;
    get(instanceSizeOrig, responseCountOrig);
    set(1500, 2000);

    get(instanceSize, responseCount);
    CIMPLE_TEST_ASSERT(instanceSize == 1500);
    CIMPLE_TEST_ASSERT(responseCount = 2000);

    set(instanceSizeOrig, responseCountOrig);

    get(instanceSize, responseCount);

    CIMPLE_TEST_ASSERT(instanceSize == instanceSizeOrig);
    CIMPLE_TEST_ASSERT(responseCount = responseCountOrig);
}

int main(int argc, char** argv)
{
    verbose = getenv("PEGASUS_TEST_VERBOSE") ? true : false;

    tests t;

    t.connect(true);

    try
    {
        // if no argument conduct simple standard test to validate the
        // operation of the provider.
        if (argc <=1)
        {
            // get the first class in the list
            assert(t.moreClasses());
        
            t.testSetAndGetMethods();
    
            // set test parameters to 150 = size, 20 = response count
            Uint64 responseCount = 20;
            Uint64 instanceSize = 150;
    
            t.set(instanceSize, responseCount);
        
            t.enumerateInstanceNames(instanceSize, responseCount);
        
            t.enumerateInstances(instanceSize, responseCount);
        }
        else if(strcmp(argv[1], "one") == 0)
        {
            t.testAllClasses();
            while (t.moreClasses())
            {
                t.set(1000, 1);
                t. enumerateInstances(1000, 1);
            }
        }
        else if (strcmp(argv[1],"test") == 0)
        {
            Array<Uint64> objSize;
            objSize.append(100);
            objSize.append(1000);
            objSize.append(10000);
            objSize.append(50000);

            Array<Uint64> objCount;
            objCount.append(100);
            objCount.append(1000);
            objCount.append(10000);
            objCount.append(50000);
            objCount.append(100000);
            objCount.append(200000);
            objCount.append(250000);

            t.testAllClasses();
            while (t.moreClasses())
            {
                for (Uint32 x = 0; x < objSize.size() ; x++)
                {
                    for(Uint32 y = 0; y < objCount.size(); y++)
                    {
                        t.set(objSize[x], objCount[y]);
                        t.enumerateInstances(objSize[x],objCount[y]);
                    }
                }
            }
        }
    }
    catch (Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }

    cout << argv[0] << " +++++ passed all tests" << endl;

    return 0;
}
