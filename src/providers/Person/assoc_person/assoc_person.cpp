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
        object_path.setClassName("Person");
        object_path.setNameSpace(NAMESPACE);
        CIMKeyBinding binding("ssn", "1", CIMKeyBinding::NUMERIC);
        Array<CIMKeyBinding> bindings;
        bindings.append(binding);
        object_path.setKeyBindings(bindings);

        cout << object_path.toString() << endl;

        client.associators(NAMESPACE, object_path, "ParentChild", "Person");
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Person/assoc_person/assoc_person.cpp,v 1.4 2007/03/07 20:19:40 mbrasher-public Exp $");
