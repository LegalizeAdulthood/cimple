#include <cassert>
#include <getopt.h>
#include <cimple/Time.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Listener/CIMListener.h>
#include <Pegasus/Consumer/CIMIndicationConsumer.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

bool help_opt = false;
String name_space_opt = "root/cimv2";
String source_name_space_opt = "root/cimv2";
int seconds_opt = 1000000;
String name_opt = "56C0D70B233E46668EC64BD2671D07A2";
String query_opt = "select * from CIM_Indication";

const String DESTINATION = "http://localhost:9999";

class Str
{
public:

    Str(const String& s) : _cstr(s.getCString()) { }
    Str(const CIMName& n) : _cstr(n.getString().getCString()) { }
    Str(const CIMNamespaceName& n) : _cstr(n.getString().getCString()) { }
    Str(const Exception& e) : _cstr(e.getMessage().getCString()) { }
    Str(const CIMDateTime& x) : _cstr(x.toString().getCString()) { }
    ~Str() { }
    const char* operator*() const { return (const char*)_cstr; }
    operator const char*() const { return (const char*)_cstr; }
private:
    CString _cstr;
};

void print_instance(const CIMConstInstance& ci, bool indent = false);

void print_scalar(const String& name, const CIMValue& v)
{
    if (v.isNull())
    {
        printf("NULL");
        return;
    }

    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
        {
            Boolean x;
            v.get(x);
            if (x)
                printf("true");
            else
                printf("false");
            break;
        }

        case CIMTYPE_UINT8:
        {
            Uint8 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT8:
        {
            Sint8 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT16:
        {
            Uint16 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT16:
        {
            Sint16 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT32:
        {
            Uint32 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT32:
        {
            Sint32 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT64:
        {
            Uint64 x;
            v.get(x);
            printf(CIMPLE_LLU, x);
            break;
        }

        case CIMTYPE_SINT64:
        {
            Sint64 x;
            v.get(x);
            printf(CIMPLE_LLD, x);
            break;
        }

        case CIMTYPE_REAL32:
        {
            Real32 x;
            v.get(x);
            printf("%f", x);
            break;
        }

        case CIMTYPE_REAL64:
        {
            Real64 x;
            v.get(x);
            printf("%lf", x);
            break;
        }

        case CIMTYPE_CHAR16:
        {
            Char16 x;
            v.get(x);
            printf("%d", Uint32(x));
            break;
        }

        case CIMTYPE_STRING:
        {
            String x;
            v.get(x);
            printf("%s", *Str(x));
            break;
        }

        case CIMTYPE_DATETIME:
        {
            CIMDateTime x;
            v.get(x);
            printf("%s", *Str(x.toString()));
            break;
        }

        case CIMTYPE_REFERENCE:
        {
            CIMObjectPath x;
            v.get(x);
            printf("%s", *Str(x.toString()));
            break;
        }

        case CIMTYPE_OBJECT:
        {
            CIMObject x;
            v.get(x);

            if (x.isInstance())
            {
                print_instance(CIMInstance(x), true);
            }
            else
            {
                printf("<CLASS>");
            }
            break;
        }

        default:
            break;
    }
}

template<class T>
void print_array_aux(const String& name, const CIMValue& v, T* tag)
{
    Array<T> x;
    v.get(x);

    printf("{");

    for (Uint32 i = 0; i < x.size(); i++)
    {
        print_scalar(name, CIMValue(x[i]));

        if (i + 1 != x.size())
            printf(", ");
    }

    printf("}");
}

void print_array(const String& name, const CIMValue& v)
{
    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
            print_array_aux(name, v, (Boolean*)0);
            break;

        case CIMTYPE_UINT8:
            print_array_aux(name, v, (Uint8*)0);
            break;

        case CIMTYPE_SINT8:
            print_array_aux(name, v, (Sint8*)0);
            break;

        case CIMTYPE_UINT16:
            print_array_aux(name, v, (Uint16*)0);
            break;

        case CIMTYPE_SINT16:
            print_array_aux(name, v, (Sint16*)0);
            break;

        case CIMTYPE_UINT32:
            print_array_aux(name, v, (Uint32*)0);
            break;

        case CIMTYPE_SINT32:
            print_array_aux(name, v, (Sint32*)0);
            break;

        case CIMTYPE_UINT64:
            print_array_aux(name, v, (Uint64*)0);
            break;

        case CIMTYPE_SINT64:
            print_array_aux(name, v, (Sint64*)0);
            break;

        case CIMTYPE_REAL32:
            print_array_aux(name, v, (Real32*)0);
            break;

        case CIMTYPE_REAL64:
            print_array_aux(name, v, (Real64*)0);
            break;

        case CIMTYPE_CHAR16:
            print_array_aux(name, v, (Char16*)0);
            break;

        case CIMTYPE_STRING:
            print_array_aux(name, v, (String*)0);
            break;

        case CIMTYPE_DATETIME:
            print_array_aux(name, v, (CIMDateTime*)0);
            break;

        case CIMTYPE_REFERENCE:
            print_array_aux(name, v, (CIMObjectPath*)0);
            break;

        default:
            break;
    }
}

void print_value(const String& name, const CIMValue& v)
{
    printf("%s=", *Str(name));

    if (v.isArray())
        print_array(name, v);
    else
        print_scalar(name, v);

    printf("\n");
}

void print_instance(const CIMConstInstance& ci, bool indent)
{
    char in[5];

    if (indent)
        strcpy(in, "    ");
    else
        strcpy(in, "");

    printf("%sinstance of %s\n", in, *Str(ci.getClassName()));
    printf("%s{\n", in);

    for (Uint32 i = 0; i < ci.getPropertyCount(); i++)
    {
        CIMConstProperty cp = ci.getProperty(i);

        printf("%s    ", in);
        print_value(*Str(cp.getName()), cp.getValue());
    }

    printf("%s}\n", in);
}

//==============================================================================
//
// IndicationConsumer
//
//==============================================================================

class IndicationConsumer : public CIMIndicationConsumer
{
public:

    virtual void consumeIndication(
        const OperationContext& context,
        const String& url,
        const CIMInstance& indication)
    {
        print_instance(indication);
        cout << endl;
    }

};

//==============================================================================
//
// create_filter()
//
//==============================================================================

static CIMObjectPath create_filter(
    CIMClient& client, 
    const String& query,
    const String& name)
{
    // CIM_IndicationFilter.
    //   CreationClassName="CIM_IndicationFilter",
    //   Name=id
    //   SystemCreationClassName="CIM_ComputerSystem",
    //   SystemName="redbird.site"

    CIMInstance inst("CIM_IndicationFilter");
    inst.addProperty(CIMProperty("Name", name));
    inst.addProperty(CIMProperty("Query", query));
    inst.addProperty(CIMProperty("QueryLanguage", String("WQL")));
    inst.addProperty(CIMProperty("SourceNamespace", source_name_space_opt));

    return client.createInstance(name_space_opt, inst);
}

static CIMObjectPath create_handler(CIMClient& client, const String& name)
{
    // CIM_IndicationHandlerCIMXML.
    //   CreationClassName="CIM_IndicationHandlerCIMXML",
    //   Name=id
    //   SystemCreationClassName="CIM_ComputerSystem",
    //   SystemName="redbird.site"

    CIMInstance inst("CIM_IndicationHandlerCIMXML");
    inst.addProperty(CIMProperty("Name", name));
    inst.addProperty(CIMProperty("Destination", DESTINATION));

    return client.createInstance(name_space_opt, inst);
}

static CIMObjectPath create_subscription(
    CIMClient& client,
    const CIMObjectPath& filter,
    const CIMObjectPath& handler)
{
    CIMInstance inst("CIM_IndicationSubscription");

    inst.addProperty(
        CIMProperty("Filter", filter, 0, "CIM_IndicationFilter"));

    inst.addProperty(
        CIMProperty("Handler", handler, 0, "CIM_IndicationHandlerCIMXML"));

    inst.addProperty(CIMProperty("OnFatalErrorPolicy", Uint16(4)));

    return client.createInstance(name_space_opt, inst);
}

static bool find_object_path(
    CIMClient& client,
    const CIMName& className,
    const String& name,
    CIMObjectPath& path)
{
    try
    {
        Array <CIMObjectPath> paths;
        paths = client.enumerateInstanceNames(name_space_opt, className);

        for (Uint32 i = 0; i < paths.size(); i++)
        {
            Array<CIMKeyBinding> keyBindings = paths[i].getKeyBindings();

            for (Uint32 j = 0; j < keyBindings.size(); j++)
            {
                if (keyBindings[j].getName().equal("Name"))
                {
                    if (keyBindings[j].getValue() == name)
                    {
                        path = paths[i];
                        return true;
                    }
                }
            }
        }
    }
    catch (...)
    {
    }

    return false;
}

static void cleanup(CIMClient& client, const String& name)
{
    // Find filter.

    CIMObjectPath filter;

    if (!find_object_path(client, "CIM_IndicationFilter", name, filter))
        return;

    // Find handler.

    CIMObjectPath handler;

    if (!find_object_path(client, "CIM_IndicationHandlerCIMXML", name, handler))
        return;

    // Subscription:

    CIMObjectPath subscription("CIM_IndicationSubscription");
    {
        Array<CIMKeyBinding> bindings;
        bindings.append(CIMKeyBinding("Filter", filter));
        bindings.append(CIMKeyBinding("Handler", handler));
        subscription.setKeyBindings(bindings);
    }

    // Delete objects.

    try
    {
        client.deleteInstance(name_space_opt, subscription);
    }
    catch (...)
    {
        // Ignore.
    }

    try
    {
        client.deleteInstance(name_space_opt, filter);
    }
    catch (...)
    {
        // Ignore.
    }

    try
    {
        client.deleteInstance(name_space_opt, handler);
    }
    catch (...)
    {
        // Ignore.
    }
}

const char USAGE[] = "\
\n\
Usage: %s [OPTIONS] QUERY\n\
\n\
Examples:\n\
    $ cimlisten\n\
    $ cimlisten \"select * from MyIndicationClass\"\n\
\n\
OPTIONS:\n\
    -V              Print CIMPLE version.\n\
    -h              Print this help message.\n\
    -n NAMESPACE    subscription namespace.\n\
    -S NAMESPACE    source namespace (CIM_IndicationFilter.SourceNamespace).\n\
    -N NAME         Name of filter and handler (Name property).\n\
    -Q QUERY        query (default: \"select * from CIM_Indication\").\n\
    -s SECONDS      Seconds to listen for (default: 1000000).\n\
\n";

int main(int argc, char ** argv)
{
    const char* arg0 = argv[0];

    // Options:

    int opt;

    while ((opt = getopt(argc, argv, "n:hVs:N:Q:S:")) != -1)
    {
        switch (opt)
        {
            case 'n':
                name_space_opt = optarg;
                break;

            case 'S':
                source_name_space_opt = optarg;
                break;

            case 'h':
                help_opt = true;
                break;

            case 'V':
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
                break;

            case 's':
            {
                seconds_opt = atoi(optarg);

                if (seconds_opt == 0)
                {
                    fprintf(stderr, "%s: bad seconds option argument: %s\n", 
                        arg0, argv[1]);
                    exit(1);
                }

                break;
            }

            case 'Q':
            {
                query_opt = optarg;
                break;
            }

            case 'N':
            {
                name_opt = optarg;
                break;
            }

            default:
                cerr << "unknown option: -" << char(opt) << endl;
                break;
        }
    }

    argc -= optind;
    argv += optind;

    // check arguments.

    if (argc != 0 || help_opt)
    {
        fprintf(stderr, (const char*)USAGE, arg0);
        exit(1);
    }

    // Connect.

    CIMClient client;
    client.setTimeout(1000 * 1000 * 1000);

    try
    {
        // Connect to CIM server:

        client.connectLocal();

        // Create listener (and consumer).

        CIMListener listener(9999);
        IndicationConsumer* consumer = new IndicationConsumer();
        listener.addConsumer(consumer);
        listener.start();

        // Delete old objects.

        cleanup(client, name_opt);

        // Create filter.

        CIMObjectPath filter = create_filter(client, query_opt, name_opt);

        // Create handler.

        CIMObjectPath handler = create_handler(client, name_opt);

        // Create subscription.

        CIMObjectPath cop;

        try 
        {
            cop = create_subscription(client, filter, handler);
        }
        catch (Exception& e)
        {
            cerr << "Failed to create subscription: " << e.getMessage();
            cerr << endl;
        }

        // Sleep forever:

        for (int i = 0; i < seconds_opt; i++)
        {
            cout << "Loop..." << endl;
            cimple::Time::sleep(cimple::Time::SEC);
        }

        // Delete objects.

        cleanup(client, name_opt);

        // Stop the listener:

        listener.stop();
        listener.removeConsumer(consumer);
        delete consumer;
    }
    catch(Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }

    return 0;
}
