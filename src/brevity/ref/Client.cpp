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
#include "Instance_Enum_Rep.h"
#include "Instance_Name_Enum_Rep.h"
#include "Sockets.h"
#include "HTTP.h"
#include "CIMXML.h"
#include "CIMXML_Parser.h"

// ATTN: validate incoming namespace (valid identifiers).

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local functions
//
//==============================================================================

static inline size_t _min(size_t x, size_t y)
{
    return x < y ? x : y;
}

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

static void _parse_cimxml(CIMXML_Parser& parser, Sock sock, HTTP_Message& rsp)
{
    // Parse partial content from response message:

    if (rsp.partial_content_length())
    {
        if (parser.parse(
            rsp.partial_content(), rsp.partial_content_length()) != 0)
        {
            throw Exception(Exception::BAD_XML, "%s",
                parser.error_msg().c_str());
        }
    }

    // Parse remaining content from socket.

    size_t r = rsp.content_length - rsp.partial_content_length();

    while (r)
    {
        char buf[BREVITY_BLOCK_SIZE];
        ssize_t n = Sockets::recv(sock, buf, _min(r, BREVITY_BLOCK_SIZE));

        if (n == -1)
            throw Exception(Exception::FAILED, "socket read failure");

        if (parser.parse(buf, n) != 0)
        {
            throw Exception(Exception::FAILED, "XML parse failure: %s",
                parser.error_msg().c_str());
        }

        if (n == 0)
            break;

        r -= n;
    }
}

//==============================================================================
//
// Client_Rep
//
//==============================================================================

class Client_Rep : public Ops_Rep
{
public:

    Sock sock;
    String default_name_space;
    String host;
    uint16 port;
    uint64 next_message_id;
    Mutex mutex;

    Client_Rep() : 
        Ops_Rep(), sock(Sockets::BAD_SOCKET), port(0), next_message_id(1000)
    {
    }

    ~Client_Rep()
    {
    }

    virtual void invoke(
        const String& name_space,
        const Instance_Ref& instance_name,
        Instance* meth)
    {
    }
};

//==============================================================================
//
// Client
//
//==============================================================================

Client::Client()
{
    open_log("brevity");
    CIMPLE_INFO(("started client"));

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

    if (rep->sock != Sockets::BAD_SOCKET)
        disconnect();

    rep->mutex.unlock();
}

Client& Client::operator=(const Client& x)
{
    Ops::operator=(x);
    return *this;
}

void Client::connect(
    const String& url, 
    const String& username, 
    const String& password)
{
    Client_Rep* rep = (Client_Rep*)_rep;
    Auto_Mutex am(rep->mutex);

    if (rep->sock != Sockets::BAD_SOCKET)
        throw Exception(Exception::ALREADY_CONNECTED);

    if (url.size() == 0)
        throw Exception(Exception::BAD_URL, "URL is empty");

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

    // Create address:

    sockaddr_in addr;

    if (Sockets::init_addr(addr, host.c_str(), port) != 0)
    {
        throw Exception(Exception::FAILED, 
            "failed to create address for host %s", host.c_str());
    }

    // Create socket:

    rep->sock = Sockets::socket();

    if (rep->sock == Sockets::BAD_SOCKET)
    {
        throw Exception(Exception::FAILED, "failed to create socket");
    }

    // Connect:

    if (Sockets::connect(rep->sock, addr) != 0)
    {
        Sockets::close(rep->sock);
        rep->sock = Sockets::BAD_SOCKET;
        throw Exception(Exception::CONNECT_FAILED, 
            "host=%s port=%u", host.c_str(), port);
    }

    rep->host = host;
    rep->port = port;
}

void Client::disconnect()
{
    Client_Rep* rep = (Client_Rep*)_rep;
    Auto_Mutex am(rep->mutex);

    if (rep->sock == Sockets::BAD_SOCKET)
        return;

    Sockets::close(rep->sock);
    rep->sock = Sockets::BAD_SOCKET;
    rep->host.clear();
    rep->port = 0;
}

bool Client::connected() const
{
    Client_Rep* rep = (Client_Rep*)_rep;
    return rep->sock != Sockets::BAD_SOCKET;
}

Instance_Ref Client::create_instance(const String& ns, const Instance_Hnd& ni)
{
    return Instance_Ref();
}

Instance_Hnd Client::get_instance(const String& ns, const Instance_Ref& in)
{
    return Instance_Hnd();
}

Instance_Enum Client::enum_instances(
    const String& ns,
    const Instance_Ref& cn,
    bool deep_inheritance)
{
    Client_Rep* rep = (Client_Rep*)_rep;

    if (rep->sock == Sockets::BAD_SOCKET)
        throw Exception(Exception::NOT_CONNECTED);

    const Meta_Class* mc = cn.meta_class();

    // Format header:

    Buffer req;
    req.reserve(4096);
    size_t offset = HTTP::format_request_header(req, 
        rep->host.c_str(), rep->port, "MethodCall", "EnumerateInstances",
        ns.c_str());

    size_t header_size = req.size();

    // Preamble:

    CIMXML::xml_line(req);
    CIMXML::start_CIM(req);
    CIMXML::start_MESSAGE(req, rep->next_message_id++);
    CIMXML::start_SIMPLEREQ(req);
    CIMXML::start_IMETHODCALL(req, STRLIT("EnumerateInstances"));

    // Namespace:

    CIMXML::put_LOCALNAMESPACEPATH(req, ns.c_str());

    // ClassName:

    CIMXML::start_IPARAMVALUE(req, STRLIT("ClassName"));
    CIMXML::put_CLASSNAME(req, mc->name);
    CIMXML::end_IPARAMVALUE(req);

    // DeepInheritance:

    CIMXML::start_IPARAMVALUE(req, STRLIT("DeepInheritance"));

    if (deep_inheritance)
        req.append(STRLIT("<VALUE>TRUE</VALUE>\n"));
    else
        req.append(STRLIT("<VALUE>FALSE</VALUE>\n"));

    CIMXML::end_IPARAMVALUE(req);

    // IncludeQualifiers:

    CIMXML::start_IPARAMVALUE(req, STRLIT("IncludeQualifiers"));
    req.append(STRLIT("<VALUE>FALSE</VALUE>\n"));
    CIMXML::end_IPARAMVALUE(req);

    // Postamble:

    CIMXML::end_IMETHODCALL(req);
    CIMXML::end_SIMPLEREQ(req);
    CIMXML::end_MESSAGE(req);
    CIMXML::end_CIM(req);

    // Update the Content-Length now that we know the length.

    HTTP::set_content_length(req, offset, req.size() - header_size);

#if 0
    printf("%s\n", req.data());
#endif

    // Send request:

    HTTP_Message rsp;

    if (HTTP::send(rep->sock, req, rsp) != 0)
        throw Exception(Exception::FAILED, "communication failure");

#if 0
    rsp.print();
#endif

    // If HTTP error:

    if (rsp.status != HTTP_STATUS_OK)
        throw Exception(Exception::FAILED, "bad HTTP status: %u", rsp.status);

    // Parse the response content.

    CIMXML_Parser parser(cn.instance()->meta_class->meta_repository);
    parser.meta_class(cn.instance()->meta_class);
    _parse_cimxml(parser, rep->sock, rsp);

    CIMXML_Context& ctx = parser.context();

    if (ctx.error)
    {
        if (ctx.message[0])
            throw Exception(ctx.code, "%s", ctx.message);
        else
            throw Exception(ctx.code);
    }

#if 0
    ctx.print();
#endif

    // Create enumerator:

    Instance_Enum_Rep* tmp = new Instance_Enum_Rep(ctx.instances);
    ctx.instances.clear();
    return Instance_Enum(tmp);
}

Instance_Name_Enum Client::enum_instance_names(
    const String& ns,
    const Instance_Ref& cn)
{
    return Instance_Name_Enum();
}

void Client::delete_instance(const String& ns, const Instance_Ref& in)
{
}

void Client::modify_instance(
    const String& ns,
    const Instance_Hnd& modified_instance)
{
}

void Client::modify_instance(
    const String& ns,
    const Instance_Hnd& modified_instance,
    const Array<String>& property_list)
{
}

Instance_Enum Client::associators(
    const String& ns,
    const Instance_Ref& in, 
    const String& assoc_class,
    const String& result_class,
    const String& role,
    const String& result_role)
{
    return Instance_Enum();
}

Instance_Name_Enum Client::associator_names(
    const String& ns,
    const Instance_Ref& in, 
    const String& assoc_class,
    const String& result_class,
    const String& role,
    const String& result_role)
{
    return Instance_Name_Enum();
}

Instance_Enum Client::references(
    const String& ns,
    const Instance_Ref& in, 
    const String& result_class,
    const String& role)
{
    return Instance_Enum();
}

Instance_Name_Enum Client::reference_names(
    const String& ns,
    const Instance_Ref& in, 
    const String& result_class,
    const String& role)
{
    return Instance_Name_Enum();
}

CIMPLE_NAMESPACE_END
