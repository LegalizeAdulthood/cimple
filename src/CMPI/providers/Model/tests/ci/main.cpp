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

const String NAMESPACE = "root/cimv2";

int main(int argc, char** argv)
{
    try
    {
	CIMClient client;
	client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

	CIMObjectPath object_path;
	object_path.setClassName("Model");
	object_path.setNameSpace(NAMESPACE);

	CIMKeyBinding b_k1("k1", "", CIMKeyBinding::STRING);
	CIMKeyBinding b_k2("k2", "5555", CIMKeyBinding::NUMERIC);
	CIMKeyBinding b_k3("k3", "false", CIMKeyBinding::BOOLEAN);
	Array<CIMKeyBinding> bindings;
	bindings.append(b_k1);
	bindings.append(b_k2);
	bindings.append(b_k3);
	object_path.setKeyBindings(bindings);

	CIMInstance instance("Model");
	instance.setPath(object_path);
	instance.addProperty(CIMProperty("k1", String("hello world")));
	instance.addProperty(CIMProperty("k2", Uint32(5555)));
	instance.addProperty(CIMProperty("k3", Boolean(false)));
	instance.addProperty(CIMProperty("prop1", String("prop1")));
	instance.addProperty(CIMProperty("prop2", String("prop2")));
	instance.addProperty(CIMProperty("prop3", String("prop3")));
	instance.addProperty(CIMProperty("prop4", String("prop4")));
	instance.addProperty(CIMProperty("prop5", String("prop5")));

	CIMObjectPath return_object_path = client.createInstance(
	    NAMESPACE, instance);
    }
    catch(Exception& e)
    {
	PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
	exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
