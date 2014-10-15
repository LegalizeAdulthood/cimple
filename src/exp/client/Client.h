/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#ifndef _clients_pegasus_Client_h
#define _clients_pegasus_Client_h

#include <cassert>
#include <cimple/cimple.h>
#include <pegasus/provmgr/Converter.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>

CIMPLE_NAMESPACE_BEGIN

class Client
{
public:

    Client();

    ~Client();

    int connect(
        const char* host,
        unsigned short port);

    void raise_error(const char* message);

    void put_error(const char* prefix);

    template<class CLASS>
    int create_instance(const String& name_space, const CLASS* instance);

    template<class CLASS>
    int get_instance(const String& name_space, CLASS* ci);

private:

    Pegasus::CIMClient _rep;
    bool _error;
    String _error_message;
};

template<class CLASS>
int Client::create_instance(const String& name_space, const CLASS* ci)
{
    assert(ci != 0);
    assert(ci->magic == CIMPLE_INSTANCE_MAGIC);

    //
    // Convert CIMPLE instance to Pegasus instance.
    //

    Pegasus::CIMInstance pi;

    if (Pegasus::Converter::to_pegasus_instance(
        ci, pi, name_space.c_str()) != 0)
    {
        raise_error("conversion to Pegasus instance failed");
        return 0;
    }

    try
    {
        _rep.createInstance(name_space.c_str(), pi);
    }
    catch(Pegasus::Exception& e)
    {
        raise_error(e.getMessage().getCString());
        return -1;
    }

    return 0;
}

template<class CLASS>
int Client::get_instance(const String& name_space, CLASS* ci)
{
    assert(ci != 0);
    assert(ci->magic == CIMPLE_INSTANCE_MAGIC);

    //
    // Convert CIMPLE instance to object path.
    //

    Pegasus::CIMObjectPath op;

    if (Pegasus::Converter::to_pegasus_object_path(
        ci, op, name_space.c_str()) != 0)
    {
        raise_error("conversion to Pegasus object path failed");
        return 0;
    }

    //
    // Get the instance from the server.
    //

    try
    {
        Pegasus::CIMInstance pi = _rep.getInstance(name_space.c_str(), op);

        Instance* tmp = 0;

        if (Pegasus::Converter::to_cimple_instance(
            pi, &CLASS::static_meta_class, tmp) != 0)
        {
            raise_error("failed to convert to a cimple instance");
            return -1;
        }

        copy(ci, tmp);
    }
    catch(Pegasus::Exception& e)
    {
        raise_error(e.getMessage().getCString());
        return -1;
    }


    return 0;
}

CIMPLE_NAMESPACE_END

#endif /* _clients_pegasus_Client_h */
