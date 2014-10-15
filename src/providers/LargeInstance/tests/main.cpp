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
#include <util/util.h>
#include "usage.h"
//#include <Pegasus/Common/XmlWriter.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

const String NAMESPACE = "root/cimv2";
const String CLASSNAME = "CMPL_LargeInstance";

Uint32 sizeOfInstanceOpt = 1200;
Uint32 instanceCountOpt = 100;
Uint32 enumerationTypeOpt = 1;
Uint32 repeatOpt = 1;
bool verboseOpt = false;

void setConfigParameters(CIMClient& client,
                    Uint32 countToReturn,
                    Uint32 sizeOfInstance,
                    Uint16 instanceDeliveryType)
{
    CIMObjectPath instanceName(CLASSNAME);

    // Define input arguments:

    Array<CIMParamValue> inParams;
    Array<CIMParamValue> outParams;

    // Invoke the method:

    const String methodName = "setconfig";

    inParams.append(CIMParamValue("size", sizeOfInstance));
    inParams.append(CIMParamValue("count", countToReturn));
    inParams.append(CIMParamValue("type", instanceDeliveryType));

    CIMValue value = client.invokeMethod(
        NAMESPACE,
        instanceName,
        methodName,
        inParams,
        outParams);
}

void getConfigParameters(CIMClient& client,
                    Uint32 countToReturn,
                    Uint32 sizeOfInstance,
                    Uint16 instanceDeliveryType)
{
    CIMObjectPath instanceName(CLASSNAME);

    // Define input arguments:

    Array<CIMParamValue> inParams;
    Array<CIMParamValue> outParams;

    // Invoke the method:

    const String methodName = "getconfig";

    CIMValue value = client.invokeMethod(
        NAMESPACE,
        instanceName,
        methodName,
        inParams,
        outParams);

    assert(outParams.size() == 3);

    for (size_t i = 0; i < outParams.size(); i++)
    {
        const CIMParamValue& pv = outParams[i];
        const CIMValue v = pv.getValue();

        if (pv.getParameterName() == "size")
        {
            Uint32 localSizeOfInstance;
            assert(v.getType() == CIMTYPE_UINT32);
            pv.getValue().get(localSizeOfInstance);
            assert(sizeOfInstance == localSizeOfInstance);
        }
        else if (pv.getParameterName() == "count")
        {
            Uint32 localCountToReturn;
            assert(v.getType() == CIMTYPE_UINT32);
            pv.getValue().get(localCountToReturn);
            assert(localCountToReturn == countToReturn);
        }
        else if (pv.getParameterName() == "type")
        {
            Uint16 localInstanceDeliveryType;
            assert(v.getType() == CIMTYPE_UINT16);
            pv.getValue().get(localInstanceDeliveryType);
            assert(localInstanceDeliveryType == instanceDeliveryType);
        }
        else
        {
            assert(false);
        }
    }
}

bool instanceSizeTest(const CIMInstance& instance, Uint32 minSize)
{
    return true;
}


int main(int argc, char** argv)
{
    const char* arg0 = argv[0];
    // Check options:

    int opt;

    while ((opt = getopt(argc, argv, "s:c:r:t:hvV")) != -1)
    {
        switch (opt)
        {
            case 's':
            {
                if (!optarg)
                {
                    err("missing argument on -s option");
                    exit(1);
                }
                sizeOfInstanceOpt = atoi(optarg);

                if (sizeOfInstanceOpt == 0)
                {
                    fprintf(stderr,
                        "%s: bad instance size option argument: %s\n", 
                        arg0, argv[1]);
                    exit(1);
                }
                break;
            }

            case 'c':
            {
                if (!optarg)
                {
                    err("missing argument on -c option");
                    exit(1);
                }
                instanceCountOpt = atoi(optarg);

                if (instanceCountOpt == 0)
                {
                    fprintf(stderr, 
                        "%s: bad operation type option argument: %s\n", 
                        arg0, argv[1]);
                    exit(1);
                }
                break;

            }
            case 'r':
            {
                if (!optarg)
                {
                    err("missing argument on -r option");
                    exit(1);
                }
                repeatOpt = atoi(optarg);

                if (repeatOpt == 0)
                {
                    fprintf(stderr, 
                        "%s: bad repeat option argument: %s\n", 
                        arg0, argv[1]);
                    exit(1);
                }

                break;
            }
            case 't':
            {
                if (!optarg)
                {
                    err("missing argument on -t option");
                    exit(1);
                }
               enumerationTypeOpt = atoi(optarg);

                if (enumerationTypeOpt == 0)
                {
                    fprintf(stderr,
                        "%s: bad enumeration type option argument: %s\n", 
                        arg0, argv[1]);
                    exit(1);
                }
                if (enumerationTypeOpt > 3)
                {
                    fprintf(stderr, 
                        "%s: invalid operation type option argument:"
                        "Value not in range %s\n", 
                        arg0, argv[1]);
                    exit(1);
                }
                break;
            } 

            case 'h':
            {
                fprintf(stderr, (char*)USAGE, arg0);
                printf("Options are countToDeliver %u "
                   "returned InstanceSize %u type %u repeats %u\n",
                   instanceCountOpt,sizeOfInstanceOpt, 
                   enumerationTypeOpt, repeatOpt);
                exit(0);
            }

            case 'v':
            {
                verboseOpt = true;
                break;
            }

            case 'V':
            {
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
            }

            default:
                err("unknown option: %c", opt);
                break;
        }
    }

    // Check usage.

    argc -= optind;
    argv += optind;

    try
    {
        if (verboseOpt)
        {
            printf("Options are countToDeliver %u "
                   "returned InstanceSize %u type %u repeats %u\n",
                   instanceCountOpt,sizeOfInstanceOpt, 
                   enumerationTypeOpt, repeatOpt);
        }
        CIMClient client;
        client.connectLocal();

        setConfigParameters(client, instanceCountOpt,sizeOfInstanceOpt, 
                            enumerationTypeOpt);

        getConfigParameters(client, instanceCountOpt, sizeOfInstanceOpt, 
                            enumerationTypeOpt);

        for (Uint32 i = 0 ; i < repeatOpt ; i++)
        {
            Array<CIMInstance> instances = client.enumerateInstances(
                NAMESPACE, CLASSNAME);
            assert(instances.size() == instanceCountOpt);
            assert(instanceSizeTest(instances[0], sizeOfInstanceOpt));
            if (verboseOpt)
            {
                printf(".");
            }
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
