#include <cassert>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Listener/CIMListener.h>
#include <Pegasus/Consumer/CIMIndicationConsumer.h>
#include <Pegasus/Common/System.h>
#include <Pegasus/Common/MofWriter.h>

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

const String FILTER_CLASS = "CIM_IndicationFilter";
const String HANDLER_CLASS = "CIM_IndicationHandlerCIMXML";
const String SUBSCRIPTION_CLASS = "CIM_IndicationSubscription";
// const String QUERY = "SELECT IndicationIdentifier FROM LampIndic";
const String QUERY = "SELECT * FROM LampIndic";
const String DESTINATION = "http://localhost:9999/LampIndicListener";
//const String NAMESPACE = "root/PG_InterOp";
const String NAMESPACE = "root/cimv2";

class LampIndicConsumer : public CIMIndicationConsumer
{
public:

    virtual void consumeIndication(
	const OperationContext& context,
        const String& url,
        const CIMInstance& indicationInstance);
};

bool _success = false;

void LampIndicConsumer::consumeIndication(
    const OperationContext& context,
    const String& url,
    const CIMInstance& indication)
{
    CIMConstProperty prop = indication.getProperty(
	indication.findProperty("IndicationIdentifier"));

    String indicationIdentifier;
    prop.getValue().get(indicationIdentifier);

    static size_t _count = 0;

    assert(indicationIdentifier == "HELLO");

    if (++_count == 5)
	_success = true;
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
    inst.addProperty(CIMProperty("SourceNamespace", String(NAMESPACE)));

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
	    // cerr << "Warning: " << e.getMessage() << endl;
	}

	// Send the method:

#if 1
	for (int i = 0; i < 5; i++)
	{
#if 0
	    _invokeMethod(client, "DerivedIndication");
	    System::sleep(1);
#endif
	    _invokeMethod(client, "LampIndic");
	}
#endif

	System::sleep(5);
	assert(_success == true);

	printf("+++++ passed all tests\n");

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
