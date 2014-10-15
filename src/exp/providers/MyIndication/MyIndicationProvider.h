#ifndef _MyIndicationProvider_h
#define _MyIndicationProvider_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Provider/CIMIndicationProvider.h>
#include <Pegasus/Provider/CIMMethodProvider.h>

PEGASUS_USING_PEGASUS;

class MyIndicationProvider : public CIMMethodProvider, public CIMIndicationProvider
{
public:

    MyIndicationProvider();

    virtual ~MyIndicationProvider();

    virtual void initialize(CIMOMHandle& cimomHandle);

    virtual void terminate();

    virtual void enableIndications(IndicationResponseHandler& handler);

    virtual void disableIndications();

    virtual void createSubscription(
        const OperationContext& context,
        const CIMObjectPath& subscriptionName,
        const Array <CIMObjectPath>& classNames,
        const CIMPropertyList& propertyList,
        const Uint16 repeatNotificationPolicy);

    virtual void modifySubscription(
        const OperationContext& context,
        const CIMObjectPath& subscriptionName,
        const Array <CIMObjectPath>& classNames,
        const CIMPropertyList& propertyList,
        const Uint16 repeatNotificationPolicy);

    virtual void deleteSubscription (
        const OperationContext& context,
        const CIMObjectPath& subscriptionName,
        const Array <CIMObjectPath>& classNames);

    virtual void invokeMethod(
        const OperationContext& context,
        const CIMObjectPath& objectReference,
        const CIMName& methodName,
        const Array<CIMParamValue>& inParameters,
        MethodResultResponseHandler& handler);

    CIMInstance createIndication(const CIMName& className);

    static String getNextIndicationIdentifier();

private:

    IndicationResponseHandler* _handler;
    static Uint32 _nextIndicationIdentifier;
};

#endif /* _MyIndicationProvider_h */
