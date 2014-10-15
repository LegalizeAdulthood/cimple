#include <cassert>
#include <getopt.h>
#include <pegasus/utils/pegasus.h>
#include <cimple/Time.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Listener/CIMListener.h>
#include <Pegasus/Consumer/CIMIndicationConsumer.h>
#include <pegasus/utils/print.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

bool help_opt = false;
String name_space_opt = "root/cimv2";
String source_name_space_opt = "root/cimv2";
int seconds_opt = 1000000;
String name_opt = "56C0D70B233E46668EC64BD2671D07A2";
String query_opt = "select * from CIM_Indication";
unsigned short port_opt = 5988;
String host_opt;
String user_opt;
String password_opt;

String dest_opt = "http://localhost:9999";

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
        cimple::print(indication);
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
    inst.addProperty(CIMProperty("Destination", dest_opt));

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
    -n NAMESPACE    The subscription namespace, where the subscription\n\
                    instances are placed (default is \"root/cimv2\").\n\
    -S NAMESPACE    The source namespace, where the indication provider is\n\
                    registered (default is \"root/cimv2\").\n\
    -N NAME         Name of filter and handler (Name property).\n\
    -Q QUERY        query (default: \"select * from CIM_Indication\").\n\
    -s SECONDS      Seconds to listen for (default: 1000000).\n\
    -H HOST         Connect to this HOST.\n\
    -P PORT         Connect on this PORT.\n\
    -u USER         Connect as this USER.\n\
    -p PASSWORD     Connect with this PASSWORD.\n\
    -d DESTINATION  Deliver indication to this listener (default is\n\
                    http://localhost:9999\n\
\n";

int main(int argc, char ** argv)
{
    const char* arg0 = argv[0];

    // Options:

    int opt;

    while ((opt = getopt(argc, argv, "n:hVs:N:Q:S:H:P:u:p:d:")) != -1)
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

            case 'H':
            {
                host_opt = optarg;
                break;
            }

            case 'P':
            {
                port_opt = atoi(optarg);
                break;
            }

            case 'u':
            {
                user_opt = optarg;
                break;
            }

            case 'p':
            {
                password_opt = optarg;
                break;
            }

            case 'd':
            {
                dest_opt = optarg;
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

        if (host_opt.size() || port_opt != 5988)
            client.connect(host_opt, port_opt, user_opt, password_opt);
        else
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
