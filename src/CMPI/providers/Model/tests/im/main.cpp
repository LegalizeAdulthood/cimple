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
    const String NAMESPACE = "root/cimv2";

    try
    {
	CIMClient client;
	client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

	// Build object path:

	CIMObjectPath object_path("Model.k1=\"key\",k2=5555,k3=false");
	// CIMObjectPath object_path("Model");
	object_path.setNameSpace(NAMESPACE);

	// Invoke the method:

	Array<CIMParamValue> inParams;
	Array<CIMParamValue> outParams;
	inParams.append(CIMParamValue("w", String("hello")));
	inParams.append(CIMParamValue("x", Uint32(99)));

        CIMValue value = client.invokeMethod(
            // NAMESPACE, object_path, "stub2", inParams, outParams);
            NAMESPACE, object_path, "stub", inParams, outParams);

	{
	    String t;
	    assert(value.getType() == CIMTYPE_STRING);
	    value.get(t);
	    cout << "return=" << t << endl;
	}

	for (size_t i = 0; i < outParams.size(); i++)
	{
	    const CIMParamValue& pv = outParams[i];
	    const CIMValue v = pv.getValue();

	    if (pv.getParameterName() == "y")
	    {
		Boolean t = true;
		assert(v.getType() == CIMTYPE_BOOLEAN);
		pv.getValue().get(t);

		cout << "y=" << t << endl;
		//assert(t == false);
	    }
	    else if (pv.getParameterName() == "z")
	    {
		Real32 t = 0;
		assert(v.getType() == CIMTYPE_REAL32);
		pv.getValue().get(t);
		cout << "z=" << t << endl;
	    }
	}

#if 0
#endif
    }
    catch(Exception& e)
    {
	PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
	exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
