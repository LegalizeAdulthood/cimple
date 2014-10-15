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

class CIMPLE_EXPORT Pegasus_Adapter : 
    public Pegasus::CIMMethodProvider, 
    public Pegasus::CIMInstanceProvider,
    public Pegasus::CIMAssociationProvider,
    public Pegasus::CIMIndicationProvider
{
public:

    Pegasus_Adapter(Provider_Handle* handle);

    virtual CIMPLE_HIDE ~Pegasus_Adapter();

    virtual CIMPLE_HIDE void initialize(Pegasus::CIMOMHandle& cimom);

    virtual CIMPLE_HIDE void terminate(void);

    virtual CIMPLE_HIDE void getInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::Boolean includeQualifiers,
	const Pegasus::Boolean includeClassOrigin,
	const Pegasus::CIMPropertyList& propertyList,
	Pegasus::InstanceResponseHandler& handler);

    virtual CIMPLE_HIDE void enumerateInstances(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::Boolean includeQualifiers,
	const Pegasus::Boolean includeClassOrigin,
	const Pegasus::CIMPropertyList& propertyList,
	Pegasus::InstanceResponseHandler& handler);

    virtual CIMPLE_HIDE void enumerateInstanceNames(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	Pegasus::ObjectPathResponseHandler& handler);

    virtual CIMPLE_HIDE void modifyInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::CIMInstance& instance,
	const Pegasus::Boolean includeQualifiers,
	const Pegasus::CIMPropertyList& propertyList,
	Pegasus::ResponseHandler& handler);

    virtual CIMPLE_HIDE void createInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	const Pegasus::CIMInstance& instance,
	Pegasus::ObjectPathResponseHandler& handler);

    virtual CIMPLE_HIDE void deleteInstance(
	const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectPath,
	Pegasus::ResponseHandler& handler);

    virtual CIMPLE_HIDE void invokeMethod(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::CIMName& methodName,
        const Pegasus::Array<Pegasus::CIMParamValue>& inParameters,
        Pegasus::MethodResultResponseHandler& handler);

    virtual CIMPLE_HIDE void associators(
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

    virtual CIMPLE_HIDE void associatorNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& associationClass,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        const Pegasus::String& resultRole,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual CIMPLE_HIDE void references(
        const Pegasus::OperationContext& context,
	const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& resultClass,
	const Pegasus::String& role,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
	Pegasus::ObjectResponseHandler& handler);

    virtual CIMPLE_HIDE void referenceNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual CIMPLE_HIDE void enableIndications(
	Pegasus::IndicationResponseHandler & handler);

    virtual CIMPLE_HIDE void disableIndications();

    virtual CIMPLE_HIDE void createSubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames,
        const Pegasus::CIMPropertyList & propertyList,
        const Pegasus::Uint16 repeatNotificationPolicy);

    virtual CIMPLE_HIDE void modifySubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames,
        const Pegasus::CIMPropertyList & propertyList,
        const Pegasus::Uint16 repeatNotificationPolicy);

    virtual CIMPLE_HIDE void deleteSubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames);

    CIMPLE_HIDE const Meta_Class* find_meta_class(
	const Pegasus::CIMObjectPath& objectPath) const;

private:

    Pegasus::CIMOMHandle* _handle;
    Provider_Handle* _provider;
    Pegasus::IndicationResponseHandler* _handler;
    Pegasus::AtomicInt _handler_refs;
    const Meta_Class* _mc;
    Pegasus::CIMOMHandle* _cimom_handle;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Pegasus_Adapter_h */
