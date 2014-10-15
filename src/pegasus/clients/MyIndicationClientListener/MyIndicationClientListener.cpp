#include <cassert>
#include <cimple/Time.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Listener/CIMListener.h>
#include <Pegasus/Consumer/CIMIndicationConsumer.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

const String FILTER_CLASS = "CIM_IndicationFilter";
const String HANDLER_CLASS = "CIM_IndicationHandlerCIMXML";
const String SUBSCRIPTION_CLASS = "CIM_IndicationSubscription";
// const String QUERY = "SELECT IndicationIdentifier FROM MyIndication";
const String QUERY = "SELECT * FROM MyIndication";
const String DESTINATION = "http://localhost:9999/MyIndicationListener";
//const String NAMESPACE = "root/PG_InterOp";
const String NAMESPACE = "root/cimv2";

class MyIndicationConsumer : public CIMIndicationConsumer
{
public:

    virtual void consumeIndication(
        const OperationContext& context,
        const String& url,
        const CIMInstance& indicationInstance);
};

#ifdef PRINT_INSTANCE
static void _print_instance(const CIMInstance& inst)
{
    Buffer buf;
    MofWriter::appendInstanceElement(buf, inst);
    buf.append('\0');

    printf("<<<<<<<<<< _print_instance():\n");

    printf("%.*s\n", int(buf.size()), buf.getData());

    printf(">>>>>>>>>>\n");
}
#endif /* PRINT_INSTANCE */

void MyIndicationConsumer::consumeIndication(
    const OperationContext& context,
    const String& url,
    const CIMInstance& indication)
{
    printf("=== MyIndicationConsumer::consumeIndication()\n");

#if 0
    cout << "url: " << url << endl;
    cout << "classname: " << indication.getClassName().getString() << endl;
#endif

    CIMConstProperty prop = indication.getProperty(
        indication.findProperty("IndicationIdentifier"));

    String indicationIdentifier;
    prop.getValue().get(indicationIdentifier);

    cout << "IndicationIdentifier: " << indicationIdentifier << endl;

#ifdef PRINT_INSTANCE
    _print_instance(indication);
#endif

#if 0
    CString cstr = indicationIdentifier.getCString();
    const char* str = cstr;

    char* end;
    long x = strtol(str, &end, 10);

    // if ((x % 10) == 0)
    printf("%ld\n", x);
#endif
}

static CIMObjectPath _createFilter(CIMClient& client)
{
    // CIM_IndicationFilter.
    //   CreationClassName="CIM_IndicationFilter",
    //   Name="MyIndicationFilter",
    //   SystemCreationClassName="CIM_ComputerSystem",
    //   SystemName="redbird.site"

    CIMInstance inst(FILTER_CLASS);
    inst.addProperty(CIMProperty("Name", String("MyIndicationFilter")));
    inst.addProperty(CIMProperty("Query", QUERY));
    inst.addProperty(CIMProperty("QueryLanguage", String("WQL")));
    inst.addProperty(CIMProperty("SourceNamespace", String(NAMESPACE)));

    return client.createInstance(NAMESPACE, inst);
}

static CIMObjectPath _createHandler(CIMClient& client)
{
    // CIM_IndicationHandlerCIMXML.
    //   CreationClassName="CIM_IndicationHandlerCIMXML",
    //   Name="MyIndicationHandler",
    //   SystemCreationClassName="CIM_ComputerSystem",
    //   SystemName="redbird.site"

    CIMInstance inst(HANDLER_CLASS);
    inst.addProperty(CIMProperty("Name", String("MyIndicationHandler")));
    inst.addProperty(CIMProperty("Destination", DESTINATION));

    return client.createInstance(NAMESPACE, inst);
}

static CIMObjectPath _createSubscription(
    CIMClient& client,
    const CIMObjectPath& filter,
    const CIMObjectPath& handler)
{
    CIMInstance inst(SUBSCRIPTION_CLASS);
    inst.addProperty(CIMProperty("Filter", filter, 0, FILTER_CLASS));
    inst.addProperty(CIMProperty("Handler", handler, 0, HANDLER_CLASS));

    return client.createInstance(NAMESPACE, inst);
}

static bool _findFilterOrHandlerPath(
    CIMClient& client,
    const CIMName& className,
    const String& name,
    CIMObjectPath& path)
{
    Array <CIMObjectPath> paths;
    paths = client.enumerateInstanceNames(NAMESPACE, className);

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

    return false;
}

static CIMObjectPath _getFilterName(CIMClient& client)
{
    CIMObjectPath objectPath;

    if (_findFilterOrHandlerPath(
        client, "CIM_IndicationFilter", "MyIndicationFilter", objectPath))
        return objectPath;

    return _createFilter(client);
}

static CIMObjectPath _getHandlerName(CIMClient& client)
{
    CIMObjectPath objectPath;

    if (_findFilterOrHandlerPath(
        client, "CIM_IndicationHandler", "MyIndicationHandler", objectPath))
        return objectPath;

    return _createHandler(client);
}

static void _invokeMethod(CIMClient& client, const char* classname)
{
    Array <CIMParamValue> inParams;
    Array <CIMParamValue> outParams;
    Array <CIMKeyBinding> keyBindings;
    Uint32 result;

    CIMObjectPath className(String::EMPTY, CIMNamespaceName(),
        CIMName(classname), keyBindings);

    CIMValue retValue = client.invokeMethod(
        NAMESPACE,
        className,
        "DeliverIndications",
        inParams,
        outParams);

    retValue.get(result);
    // printf("result: %u\n", result);
}


int main(int argc, char ** argv)
{
    CIMClient client;

    client.setTimeout(1000 * 1000 * 1000);

    try
    {
        // Create listener (and consumer).

        CIMListener listener(9999);
        MyIndicationConsumer* consumer = new MyIndicationConsumer();
        listener.addConsumer(consumer);
        listener.start();

        // Connect to CIM server:

        client.connectLocal();

        CIMObjectPath filter = _getFilterName(client);
        // cout << "FILTER[" << filter.toString() << "]\n" << endl;

        CIMObjectPath handler = _getHandlerName(client);
        // cout << "HANDLER[" << handler.toString() << "]\n" << endl;

        try 
        {
            _createSubscription(client, filter, handler);
        }
        catch (Exception& e)
        {
            cerr << "Warning: " << e.getMessage() << endl;
        }

        // Send the method:

#if 1
        for (int i = 0; i < 5; i++)
        {
#if 0
            _invokeMethod(client, "DerivedIndication");
            System::sleep(1);
#endif
            _invokeMethod(client, "MyIndication");
            cimple::Time::sleep(1 * 1000000);
        }
#endif

        // Wait for 1000 seconds.

        printf("Sleeping...\n");

        cimple::Time::sleep(3 * 1000000);

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
