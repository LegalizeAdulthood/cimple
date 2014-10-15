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

//#define USE_PEGASUS_CLIENT

#include "Client.h"
#include <cimple/Ops.h>

#include <Pegasus/Client/CIMClient.h>
#include <pegasus/utils/Containers.h>
#include <pegasus/utils/Converter.h>
#include <pegasus/utils/Str.h>
#include "Instance_Enum_Rep.h"
#include "Instance_Name_Enum_Rep.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local functions
//
//==============================================================================

static void _parse_url(
    const String& url,
    String& scheme,
    String& host,
    uint16& port,
    String& protocol)
{
    // Examples:
    //     http://localhost:5989/cimxml
    //     http://saturn:5989/wsman

    // Get scheme (e.g., "http://").

    const char* start = url.c_str();
    const char* p = strchr(start, ':');

    if (!p)
    {
        throw Exception(
            Exception::BAD_URL, "missing ':' character: %s", url.c_str());
    }

    scheme.assign(start, p - start);

    if (p[1] != '/' || p[2] != '/')
    {
        throw Exception(
            Exception::BAD_URL, "missing \"//\" sequence: %s", url.c_str());
    }

    p += 3;

    // Get host (terminated by ':' or '/').

    start = p;

    while (*p && *p != ':' && *p != '/')
        p++;

    if (*p == 0)
    {
        throw Exception(
            Exception::BAD_URL, "unterminated host: %s", url.c_str());
    }

    if (p == start)
    {
        throw Exception(
            Exception::BAD_URL, "missing host: %s", url.c_str());
    }

    host.assign(start, p - start);

    // Get port:

    port = 0;

    if (*p == ':')
    {
        p++;
        char* end;
        unsigned long x = strtoul(p, &end, 10);

        if (*end != '/')
        {
            throw Exception(
                Exception::BAD_URL, "expected '/' after port: %s", url.c_str());
        }

        if (end == p)
        {
            throw Exception(
                Exception::BAD_URL, "missing port: %s", url.c_str());
        }

        if (x > 65535)
        {
            throw Exception(
                Exception::BAD_URL, "port number too big: %ld", x);
        }

        port = uint16(x);

        if ((unsigned long)port != (unsigned long)x)
        {
            throw Exception(
                Exception::BAD_URL, "port number too big: %s", url.c_str());
        }

        p = end + 1;
    }
    else
        p++;

    // Get protocol type:

    protocol = p;
}

//==============================================================================
//
// Client_Rep
//
//==============================================================================

class Client_Rep : public Ops_Rep
{
public:

    Pegasus::CIMClient client;
    bool connected;
    Pegasus::String default_name_space;
    Mutex mutex;

    Client_Rep() : Ops_Rep(), connected(false)
    {
    }

    ~Client_Rep()
    {
    }

    virtual void invoke(
        const String& name_space,
        const Instance_Ref& instance_name,
        Instance* meth);
};

void Client_Rep::invoke(
    const String& ns,
    const Instance_Ref& instance_name,
    Instance* meth)
{
    const char* func = "Client_Rep::invoke()";

    Auto_Mutex am(mutex);

    // If not connected:

    if (!connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Get meta class:

    const Meta_Class* mc = instance_name.meta_class();

    // Get meta method:

    const Meta_Class* mm = meth->meta_class;

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hn;

    if (Converter::to_pegasus_object_path(
        hn, ns.c_str(), instance_name.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Convert input arguments:

    Pegasus::Array<Pegasus::CIMParamValue> in;
    {
        Pegasus::CIMValue rv;

        if (Converter::to_pegasus_method(
            hn, ns.c_str(), meth, CIMPLE_FLAG_IN, in, rv) != 0)
        {
            throw Exception(
                Exception::BAD_CONVERSION, "%s.%s()", mc->name, mm->name);
        }
    }

    // Perform the operation:

    Pegasus::Array<Pegasus::CIMParamValue> out;
    Pegasus::CIMValue rv;

    try
    {
        rv = client.invokeMethod(ns.c_str(), cop, mm->name, in, out);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    // Add return type to parameter list:

    out.append(Pegasus::CIMParamValue("return_value", rv));

    // Convert output arguments:
    // ATTN: lookup of meta-method is performed twice (once above and again
    // within Converter::to_cimple_method().

    if (Converter::to_cimple_method(ns.c_str(),
        out, mm->name, mc, CIMPLE_FLAG_OUT, meth) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Pegasus parameters to CIMPLE parameters");
    }
}

//==============================================================================
//
// Client
//
//==============================================================================

Client::Client()
{
    Client_Rep* rep = new Client_Rep;
    rep->default_name_space = "root/cimv2";
    _rep = rep;
}

Client::Client(const Client& x) : Ops(x)
{
}

Client::~Client()
{
    Client_Rep* rep = (Client_Rep*)_rep;
    rep->mutex.lock();

    if (rep->connected)
        disconnect();

    rep->mutex.unlock();
}

Client& Client::operator=(const Client& x)
{
    Ops::operator=(x);
    return *this;
}

void Client::connect()
{
    Client_Rep* rep = (Client_Rep*)_rep;
    connect(String(), String(), String());
}

void Client::connect(const String& url)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    connect(url, String(), String());
}

void Client::connect(
    const String& url, 
    const String& username, 
    const String& password)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    Auto_Mutex am(rep->mutex);

    if (rep->connected)
        throw Exception(Exception::ALREADY_CONNECTED, "already connected");

    if (url.size())
    {
        // Parse the URL:

        String scheme;
        String host;
        uint16 port;
        String protocol;
        _parse_url(url, scheme, host, port, protocol);

        // Check schema (only "http" supported).

        if (scheme != "http")
        {
            throw Exception(Exception::BAD_URL, 
                "unknown scheme: %s", scheme.c_str());
        }

        // Attempt to connect:

        try
        {
            rep->client.connect(
                host.c_str(), port, username.c_str(), password.c_str());
        }
        catch (...)
        {
            throw Exception(Exception::CONNECT_FAILED, 
                "failed to connect to \"%s\"", url.c_str());
        }
    }
    else
    {
        // Attempt to connect locally.

        try
        {
            rep->client.connectLocal();
        }
        catch (...)
        {
            throw Exception(Exception::CONNECT_FAILED, 
                "failed to connect to local CIM server");
        }
    }

    rep->connected = true;
}

void Client::disconnect()
{
    Client_Rep* rep = (Client_Rep*)_rep;
    Auto_Mutex am(rep->mutex);

    if (!rep->connected)
        return;

    try
    {
        rep->client.disconnect();
    }
    catch (...)
    {
    }

    rep->connected = false;
}

bool Client::connected() const
{
    Client_Rep* rep = (Client_Rep*)_rep;
    return rep->connected;
}

Instance_Ref Client::create_instance(const String& ns, const Instance_Hnd& ni)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::create_instance()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Hnd to CIMInstance:

    Pegasus::CIMInstance ci;
    Pegasus::String hostname;

    if (Converter::to_pegasus_instance(
        hostname, ns.c_str(), ni.instance(), ci) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Hnd to CIMInstance failed");
    }

    // Perform the operation:

    Pegasus::CIMObjectPath cop;

    try
    {
        cop = rep->client.createInstance(ns.c_str(), ci);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    // Convert CIMObjectPath to Instance_Ref.

    Instance* inst = 0;

    if (Converter::to_cimple_key(
        ns.c_str(), cop, ni.instance()->meta_class, inst) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from CIMObjectPath to Instance_Ref failed");
    }

    return Instance_Ref(inst);
}

Instance_Hnd Client::get_instance(const String& ns, const Instance_Ref& in)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::get_instance()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hostname;

    if (Converter::to_pegasus_object_path(
        hostname, ns.c_str(), in.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Perform the operation:

    Pegasus::CIMInstance ci;

    try
    {
        ci = rep->client.getInstance(ns.c_str(), cop);
    }
    catch (Pegasus::CIMException& e)
    {
        if (e.getCode() == Pegasus::CIM_ERR_NOT_FOUND)
            throw Exception(Exception::NOT_FOUND, "instance not found");

        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    // Convert CIMInstance to Instance_Hnd.

    Instance* inst = 0;

    // Get instance returns no namespace, so we set it to empty.

    const char NS[] = "";

    if (Converter::to_cimple_instance(
        NS, ci, in.instance()->meta_class, inst) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from CIMObjectPath to Instance_Ref failed");
    }

    return Instance_Hnd(inst);
}

Instance_Enum Client::enum_instances(
    const String& ns,
    const Instance_Ref& cn,
    bool deep_inheritance)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::enum_instances()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Perform the operation:

    Instance_Enum_Rep* r;

    try
    {
        Pegasus::Array<Pegasus::CIMInstance> instances =
            rep->client.enumerateInstances(
                ns.c_str(), cn.class_name(), deep_inheritance);

        r = new Instance_Enum_Rep(cn.meta_class(), instances);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    return Instance_Enum(r);
}

Instance_Name_Enum Client::enum_instance_names(
    const String& ns,
    const Instance_Ref& cn)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::enum_instance_names()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Perform the operation:

    Instance_Name_Enum_Rep* r;

    try
    {
        Pegasus::Array<Pegasus::CIMObjectPath> paths =
            rep->client.enumerateInstanceNames(ns.c_str(), cn.class_name());

        r = new Instance_Name_Enum_Rep(cn.meta_class(), paths);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    return Instance_Name_Enum(r);
}

void Client::delete_instance(const String& ns, const Instance_Ref& in)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::delete_instance()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hostname;

    if (Converter::to_pegasus_object_path(
        hostname, ns.c_str(), in.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Perform the operation:

    try
    {
        rep->client.deleteInstance(ns.c_str(), cop);
    }
    catch (Pegasus::CIMException& e)
    {
        if (e.getCode() == Pegasus::CIM_ERR_NOT_FOUND)
            throw Exception(Exception::NOT_FOUND, "instance not found");

        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }
}

void Client::modify_instance(
    const String& ns,
    const Instance_Hnd& modified_instance)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::modify_instance()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Hnd to CIMInstance:

    Pegasus::CIMInstance ci;
    Pegasus::String hostname;

    if (Converter::to_pegasus_instance(
        hostname, ns.c_str(), modified_instance.instance(), ci) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Hnd to CIMInstance failed");
    }

    // Perform the operation:

    try
    {
        rep->client.modifyInstance(ns.c_str(), ci);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }
}

void Client::modify_instance(
    const String& ns,
    const Instance_Hnd& modified_instance,
    const Array<String>& property_list)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::modify_instance()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Hnd to CIMInstance:

    Pegasus::CIMInstance ci;
    Pegasus::String hostname;

    if (Converter::to_pegasus_instance(
        hostname, ns.c_str(), modified_instance.instance(), ci) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Hnd to CIMInstance failed");
    }

    // Create Pegasus property list:

    Pegasus::Array<Pegasus::CIMName> property_names;

    for (size_t i = 0; i < property_list.size(); i++)
        property_names.append(property_list[i].c_str());

    // Perform the operation:

    try
    {
        rep->client.modifyInstance(
            ns.c_str(), ci, false, Pegasus::CIMPropertyList(property_names));
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }
}

Instance_Enum Client::associators(
    const String& ns,
    const Instance_Ref& in, 
    const String& assoc_class,
    const String& result_class,
    const String& role,
    const String& result_role)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::associators()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hostname;

    if (Converter::to_pegasus_object_path(
        hostname, ns.c_str(), in.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Perform the operation:

    Instance_Enum_Rep* r;

    try
    {
        Pegasus::CIMName ac;

        if (assoc_class.size())
            ac = Pegasus::CIMName(assoc_class.c_str());

        Pegasus::CIMName rc;

        if (result_class.size())
            rc = Pegasus::CIMName(result_class.c_str());

        Pegasus::Array<Pegasus::CIMObject> tmp = rep->client.associators(
                ns.c_str(),
                cop, 
                ac,
                rc,
                role.c_str(),
                result_role.c_str());

        Pegasus::Array<Pegasus::CIMInstance> instances;

        for (size_t i = 0; i < tmp.size(); i++)
        {
            if (!tmp[i].isInstance())
            {
                throw Exception(Exception::BAD_CONVERSION,
                    "conversion from CIMObject to CIMInstance failed");
            }

            instances.append(Pegasus::CIMInstance(tmp[i]));
        }

        r = new Instance_Enum_Rep(in.meta_class(), instances);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    return Instance_Enum(r);
}

Instance_Name_Enum Client::associator_names(
    const String& ns,
    const Instance_Ref& in, 
    const String& assoc_class,
    const String& result_class,
    const String& role,
    const String& result_role)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::associator_names()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hostname;

    if (Converter::to_pegasus_object_path(
        hostname, ns.c_str(), in.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Perform the operation:

    Instance_Name_Enum_Rep* r;

    try
    {
        Pegasus::CIMName ac;

        if (assoc_class.size())
            ac = Pegasus::CIMName(assoc_class.c_str());

        Pegasus::CIMName rc;

        if (result_class.size())
            rc = Pegasus::CIMName(result_class.c_str());

        Pegasus::Array<Pegasus::CIMObjectPath> paths= 
            rep->client.associatorNames(
                ns.c_str(),
                cop, 
                ac,
                rc,
                role.c_str(),
                result_role.c_str());

        r = new Instance_Name_Enum_Rep(in.meta_class(), paths);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    return Instance_Name_Enum(r);
}

Instance_Enum Client::references(
    const String& ns,
    const Instance_Ref& in, 
    const String& result_class,
    const String& role)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::references()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hostname;

    if (Converter::to_pegasus_object_path(
        hostname, ns.c_str(), in.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Perform the operation:

    Instance_Enum_Rep* r;

    try
    {
        Pegasus::CIMName rc;

        if (result_class.size())
            rc = Pegasus::CIMName(result_class.c_str());

        Pegasus::Array<Pegasus::CIMObject> tmp = rep->client.references(
                ns.c_str(),
                cop, 
                rc,
                role.c_str());

        Pegasus::Array<Pegasus::CIMInstance> instances;

        for (size_t i = 0; i < tmp.size(); i++)
        {
            if (!tmp[i].isInstance())
            {
                throw Exception(Exception::BAD_CONVERSION,
                    "conversion from CIMObject to CIMInstance failed");
            }

            instances.append(Pegasus::CIMInstance(tmp[i]));
        }

        r = new Instance_Enum_Rep(in.meta_class(), instances);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    return Instance_Enum(r);
}

Instance_Name_Enum Client::reference_names(
    const String& ns,
    const Instance_Ref& in, 
    const String& result_class,
    const String& role)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    const char* func = "Client::reference_names()";

    Auto_Mutex am(rep->mutex);

    // If not connected:

    if (!rep->connected)
        throw Exception(Exception::NOT_CONNECTED);

    // Convert Instance_Ref to CIMObjectPath:

    Pegasus::CIMObjectPath cop;
    Pegasus::String hostname;

    if (Converter::to_pegasus_object_path(
        hostname, ns.c_str(), in.instance(), cop) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION,
            "conversion from Instance_Ref to CIMObjectPath failed");
    }

    // Perform the operation:

    Instance_Name_Enum_Rep* r;

    try
    {
        Pegasus::CIMName rc;

        if (result_class.size())
            rc = Pegasus::CIMName(result_class.c_str());

        Pegasus::Array<Pegasus::CIMObjectPath> paths= 
            rep->client.referenceNames(ns.c_str(), cop, rc, role.c_str());

        r = new Instance_Name_Enum_Rep(in.meta_class(), paths);
    }
    catch (Pegasus::CIMException& e)
    {
        throw Exception(
            Exception::FAILED, "%s failed: %s", func, *Str(e.getMessage()));
    }
    catch (...)
    {
        throw Exception(Exception::FAILED, "%s failed", func);
    }

    return Instance_Name_Enum(r);
}

CIMPLE_NAMESPACE_END
