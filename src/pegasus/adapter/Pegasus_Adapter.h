#ifndef _cimple_Pegasus_Adapter_h
#define _cimple_Pegasus_Adapter_h

#include <cimple/cimple.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/AtomicInt.h>
#include <Pegasus/Provider/CIMMethodProvider.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>
#include <Pegasus/Provider/CIMAssociationProvider.h>
#include <Pegasus/Provider/CIMIndicationProvider.h>
#include <cimple/Provider_Handle.h>

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_HIDE Pegasus_Adapter : 
    public Pegasus::CIMMethodProvider, 
    public Pegasus::CIMInstanceProvider,
    public Pegasus::CIMAssociationProvider,
    public Pegasus::CIMIndicationProvider
{
public:

    Pegasus_Adapter(Provider_Handle* handle);

    virtual ~Pegasus_Adapter();

    virtual void initialize(Pegasus::CIMOMHandle& cimom);

    virtual void terminate(void);

    virtual void getInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::Boolean includeQualifiers,
	const Pegasus::Boolean includeClassOrigin,
	const Pegasus::CIMPropertyList& propertyList,
	Pegasus::InstanceResponseHandler& handler);

    virtual void enumerateInstances(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::Boolean includeQualifiers,
	const Pegasus::Boolean includeClassOrigin,
	const Pegasus::CIMPropertyList& propertyList,
	Pegasus::InstanceResponseHandler& handler);

    virtual void enumerateInstanceNames(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	Pegasus::ObjectPathResponseHandler& handler);

    virtual void modifyInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::CIMInstance& instance,
	const Pegasus::Boolean includeQualifiers,
	const Pegasus::CIMPropertyList& propertyList,
	Pegasus::ResponseHandler& handler);

    virtual void createInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::CIMInstance& instance,
	Pegasus::ObjectPathResponseHandler& handler);

    virtual void deleteInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	Pegasus::ResponseHandler& handler);

    virtual void invokeMethod(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::CIMName& methodName,
        const Pegasus::Array<Pegasus::CIMParamValue>& inParameters,
        Pegasus::MethodResultResponseHandler& handler);

    virtual void associators(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& associationClass,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        const Pegasus::String& resultRole,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
        Pegasus::ObjectResponseHandler& handler);

    virtual void associatorNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& associationClass,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        const Pegasus::String& resultRole,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual void references(
        const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& resultClass,
	const Pegasus::String& role,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
	Pegasus::ObjectResponseHandler& handler);

    virtual void referenceNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual void enableIndications(
	Pegasus::IndicationResponseHandler & handler);

    virtual void disableIndications();

    virtual void createSubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames,
        const Pegasus::CIMPropertyList & propertyList,
        const Pegasus::Uint16 repeatNotificationPolicy);

    virtual void modifySubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames,
        const Pegasus::CIMPropertyList & propertyList,
        const Pegasus::Uint16 repeatNotificationPolicy);

    virtual void deleteSubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames);

    const Meta_Class* find_meta_class(
	const Pegasus::CIMObjectPath& objectPath) const;

private:

    Pegasus::CIMOMHandle* _handle;
    Provider_Handle* _provider;
    Pegasus::IndicationResponseHandler* _handler;
    Pegasus::AtomicInt _handler_refs;
    const Meta_Class* _mc;
    struct Extended_Meta_Class* _emc;
    Pegasus::CIMOMHandle* _cimom_handle;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Pegasus_Adapter_h */
