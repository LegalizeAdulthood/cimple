//%2005////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2000, 2001, 2002 BMC Software; Hewlett-Packard Development
// Company, L.P.; IBM Corp.; The Open Group; Tivoli Systems.
// Copyright (c) 2003 BMC Software; Hewlett-Packard Development Company, L.P.;
// IBM Corp.; EMC Corporation, The Open Group.
// Copyright (c) 2004 BMC Software; Hewlett-Packard Development Company, L.P.;
// IBM Corp.; EMC Corporation; VERITAS Software Corporation; The Open Group.
// Copyright (c) 2005 Hewlett-Packard Development Company, L.P.; IBM Corp.;
// EMC Corporation; VERITAS Software Corporation; The Open Group.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// THE ABOVE COPYRIGHT NOTICE AND THIS PERMISSION NOTICE SHALL BE INCLUDED IN
// ALL COPIES OR SUBSTANTIAL PORTIONS OF THE SOFTWARE. THE SOFTWARE IS PROVIDED
// "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//==============================================================================
//
// Author: Mike Brasher (mbrasher@bmc.com)
//
//%/////////////////////////////////////////////////////////////////////////////

#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Common/XmlWriter.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

int main(int argc, char** argv)
{
    try
    {
	CIMClient client;
	client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

	// Define instance name:

	CIMObjectPath instanceName("Methods.key=7777");

	// Define input arguments:

	Array<CIMParamValue> inParams;
	Array<CIMParamValue> outParams;

	// Invoke the method:

	const String NAMESPACE = "root/cimv2";
	const String methodName = "foo";

	inParams.append(CIMParamValue("arg1", Uint32(99)));
	inParams.append(CIMParamValue("arg2", String("ninety-nine")));
	inParams.append(CIMParamValue("arg3", Boolean(true)));

        CIMValue value = client.invokeMethod(
            NAMESPACE,
            instanceName,
            methodName,
            inParams,
            outParams);

	{
	    String t;
	    assert(value.getType() == CIMTYPE_STRING);
	    value.get(t);
	    assert(t == "thanks for calling");
	}

	assert(outParams.size() == 3);

	for (size_t i = 0; i < outParams.size(); i++)
	{
	    const CIMParamValue& pv = outParams[i];
	    const CIMValue v = pv.getValue();

	    if (pv.getParameterName() == "arg4")
	    {
		Uint32 t = 0;
		assert(v.getType() == CIMTYPE_UINT32);
		pv.getValue().get(t);
		assert(t == 999);
	    }
	    else if (pv.getParameterName() == "arg5")
	    {
		String t;
		assert(v.getType() == CIMTYPE_STRING);
		pv.getValue().get(t);
		assert(t == "nine hundred ninety-nine");
	    }
	    else if (pv.getParameterName() == "arg6")
	    {
		Boolean t = true;
		assert(v.getType() == CIMTYPE_BOOLEAN);
		// pv.getValue().get(t);
		//assert(t == false);
	    }
	    else
	    {
		assert(0);
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
