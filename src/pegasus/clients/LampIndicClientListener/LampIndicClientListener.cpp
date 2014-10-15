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
const String QUERY = "SELECT * FROM LampIndic";
const String DESTINATION = "http://localhost:9999/LampIndicListener";
const String NAMESPACE = "root/cimv2";
const String SOURCE_NAMESPACE = "root/cimv2";

class LampIndicConsumer : public CIMIndicationConsumer
{
public:

    virtual void consumeIndication(
        const OperationContext& context,
        const String& url,
        const CIMInstance& indicationInstance);
};

bool _success = false;

static void _dump(const String& s)
{
    CString cstr(s.getCString());
    
    for (const char* p = (const char*)cstr; *p; p++)
    {
        char c = *p;

        // Attention. Without the cast, windows expands this to an integer
        // and falsly passes the test.
        if (isprint((unsigned char)c))
            printf("%c", c);
        else
            printf("[%2X]", (unsigned char)c);
    }

    printf("\n");
}

void LampIndicConsumer::consumeIndication(
    const OperationContext& context,
    const String& url,
    const CIMInstance& indication)
{
    {
        CIMConstProperty prop = indication.getProperty(
            indication.findProperty("IndicationIdentifier"));

        String ident;
        prop.getValue().get(ident);

        static size_t _count = 0;

        //cout << ident << endl;
        assert(ident == "HELLO" || ident == "GOODBYE");

        if (++_count == 5)
            _success = true;

        printf("Consume indication... %u finished %s \n", _count,
                (_success? "true" : "false"));
    }

    {
        CIMConstProperty prop = indication.getProperty(
            indication.findProperty("message"));

        String message;
        prop.getValue().get(message);

        _dump(message);

        //cout << message << endl;
    }
}

static CIMObjectPath _createFilter(CIMClient& client)
{
    // CIM_IndicationFilter.
    //   CreationClassName="CIM_IndicationFilter",
    //   Name="LampIndicFilter",
    //   SystemCreationClassName="CIM_ComputerSystem",
    //   SystemName="redbird.site"

    CIMInstance inst(FILTER_CLASS);
    inst.addProperty(CIMProperty("Name", String("LampIndicFilter")));
    inst.addProperty(CIMProperty("Query", QUERY));
    inst.addProperty(CIMProperty("QueryLanguage", String("WQL")));
    inst.addProperty(CIMProperty("SourceNamespace", String(SOURCE_NAMESPACE)));

    return client.createInstance(NAMESPACE, inst);
}

static CIMObjectPath _createHandler(CIMClient& client)
{
    // CIM_IndicationHandlerCIMXML.
    //   CreationClassName="CIM_IndicationHandlerCIMXML",
    //   Name="LampIndicHandler",
    //   SystemCreationClassName="CIM_ComputerSystem",
    //   SystemName="redbird.site"

    CIMInstance inst(HANDLER_CLASS);
    inst.addProperty(CIMProperty("Name", String("LampIndicHandler")));
    inst.addProperty(CIMProperty("Destination", DESTINATION));

    return client.createInstance(NAMESPACE, inst);
}

static CIMObjectPath _createSubscription(
    CIMClient& client,
    const CIMObjectPath& filter,
    const CIMObjectPath& handler)
{
    CIMInstance inst("CIM_IndicationSubscription");
    inst.addProperty(CIMProperty("Filter", filter, 0, FILTER_CLASS));
    inst.addProperty(CIMProperty("Handler", handler, 0, HANDLER_CLASS));
    inst.addProperty(CIMProperty("OnFatalErrorPolicy", Uint16(4)));

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
        client, "CIM_IndicationFilter", "LampIndicFilter", objectPath))
        return objectPath;

    return _createFilter(client);
}

static CIMObjectPath _getHandlerName(CIMClient& client)
{
    CIMObjectPath objectPath;

    if (_findFilterOrHandlerPath(
        client, "CIM_IndicationHandler", "LampIndicHandler", objectPath))
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
        LampIndicConsumer* consumer = new LampIndicConsumer();
        listener.addConsumer(consumer);
        listener.start();

        // Connect to CIM server:

        client.connectLocal();

        // Create or get existing filter

        CIMObjectPath filter = _getFilterName(client);

        // Create handler or get existing handler.

        CIMObjectPath handler = _getHandlerName(client);

        // Delete old subscription if any.

        try
        {
            Array<CIMKeyBinding> bindings;
            bindings.append(CIMKeyBinding("Filter", filter));
            bindings.append(CIMKeyBinding("Handler", handler));
            CIMObjectPath cop("CIM_IndicationSubscription");
            cop.setKeyBindings(bindings);
            client.deleteInstance(NAMESPACE, cop);
        }
        catch (Exception&)
        {
            // Ignore:
        }

        // Create new subscription.

        CIMObjectPath subscriptionObjectPath;

        try 
        {
            subscriptionObjectPath = 
                _createSubscription(client, filter, handler);
        }
        catch (Exception& e)
        {
            cerr << "Subscription already exists: " << e.getMessage() << endl;
        }

        // Send the method to generate indications:

        for (int i = 0; i < 5; i++)
            _invokeMethod(client, "LampIndic");

        // Sleep 5 seconds waiting for indications
        cimple::Time::sleep(5 * 1000000);
        assert(_success == true);
        cout << "Received all indications. Clean up" << endl;

        try
        {
            cout << "Delete subscription" << endl;
            client.deleteInstance(NAMESPACE, subscriptionObjectPath);
        }
        catch (Exception& e)
        {
            cerr << "Error: failed to delete subscription: " << e.getMessage();
            cerr << endl;
        }
        catch (...)
        {
            cerr << "Error: Failed in delete subscription" << endl;
        }

        listener.stop();
        listener.removeConsumer(consumer);
        delete consumer;

    }
    catch(Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }

    printf("+++++ passed all tests\n");
    return 0;
}
