#include <cassert>
#include <Pegasus/Common/Config.h>
#include "MyIndicationProvider.h"

PEGASUS_USING_STD;

PEGASUS_USING_PEGASUS;

Uint32 MyIndicationProvider::_nextIndicationIdentifier = 1;

#define T(X) /* */

String MyIndicationProvider::getNextIndicationIdentifier()
{
    char buffer[32];
    sprintf(buffer, "%u", _nextIndicationIdentifier++);

    return String(buffer);
}

CIMInstance MyIndicationProvider::createIndication(const CIMName& className)
{
    // Create indication object:

    CIMInstance indic(className);

    // Create object path:

    CIMObjectPath objectPath;
    objectPath.setNameSpace("root/cimv2");
    objectPath.setClassName(className);
    indic.setPath(objectPath);

    // Add CIMProperty property:
    indic.addProperty(CIMProperty("CorrelatedIndications", Array<String>()));

    // Add IndicationIdentifier property:

    indic.addProperty(
	CIMProperty("IndicationIdentifier", getNextIndicationIdentifier()));

    // Add IndicationTime property:
    indic.addProperty(
	CIMProperty("IndicationTime", CIMDateTime::getCurrentDateTime()));

    return indic;
}

MyIndicationProvider::MyIndicationProvider() : _handler(0)
{
    T( printf("=== MyIndicationProvider::MyIndicationProvider()\n"); );
}

MyIndicationProvider::~MyIndicationProvider()
{
    T( printf("=== MyIndicationProvider::~MyIndicationProvider()\n"); );
}

void MyIndicationProvider::initialize(CIMOMHandle& cimomHandle)
{
    T( printf("=== MyIndicationProvider::initialize()\n"); );
}

void MyIndicationProvider::terminate()
{
    T( printf("=== MyIndicationProvider::terminate()\n"); );
    delete this;
}

void MyIndicationProvider::enableIndications(IndicationResponseHandler& handler)
{
    T( printf("=== MyIndicationProvider::enableIndications()\n"); );

    _handler = &handler;
}

void MyIndicationProvider::disableIndications()
{
    _handler->complete();
    _handler = 0;
}

void MyIndicationProvider::createSubscription(
    const OperationContext& context,
    const CIMObjectPath& subscriptionName,
    const Array <CIMObjectPath>& classNames,
    const CIMPropertyList& propertyList,
    const Uint16 repeatNotificationPolicy)
{
    T( printf("=== MyIndicationProvider::createSubscription()\n"); );
}

void MyIndicationProvider::modifySubscription(
    const OperationContext& context,
    const CIMObjectPath& subscriptionName,
    const Array <CIMObjectPath>& classNames,
    const CIMPropertyList& propertyList,
    const Uint16 repeatNotificationPolicy)
{
    T( printf("=== MyIndicationProvider::modifySubscription()\n"); );
}

void MyIndicationProvider::deleteSubscription(
    const OperationContext& context,
    const CIMObjectPath& subscriptionName,
    const Array <CIMObjectPath>& classNames)
{
    T( printf("=== MyIndicationProvider::deleteSubscription()\n"); );
}

void MyIndicationProvider::invokeMethod(
    const OperationContext& context,
    const CIMObjectPath& objectReference,
    const CIMName& methodName,
    const Array<CIMParamValue>& inParameters,
    MethodResultResponseHandler& handler)
{
    T( printf("=== MyIndicationProvider::invokeMethod()\n"); );

    assert(objectReference.getClassName().equal("MyIndication"));

    if ((!methodName.equal("DeliverIndications")))
	throw Exception("no such method");

    // Send return value:

    handler.processing();
    handler.deliver(CIMValue(Uint32(0)));
    handler.complete();

    // Deliver the indication:

    if (_handler)
    {
	for (size_t i = 0; i < 1000000; i++)
	{
	    _handler->deliver(createIndication("MyIndication"));
	}
    }
}

extern "C" PEGASUS_EXPORT CIMProvider* PegasusCreateProvider(
    const String& providerName)
{
    T( printf("=== PegasusCreateProvider()\n"); );

    if (String::equalNoCase(providerName, "MyIndicationProvider"))
	return new MyIndicationProvider;

    return 0;
}
