#ifndef _cimple_Pegasus_Adapter_h
#define _cimple_Pegasus_Adapter_h

#include <cimple/cimple.h>
#include <cimple/Atomic_Counter.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Provider/CIMMethodProvider.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>
#include <Pegasus/Provider/CIMAssociationProvider.h>
#include <Pegasus/Provider/CIMIndicationProvider.h>
#include <cimple/Provider_Handle.h>
#include "typedefs.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_HIDE Pegasus_Adapter : 
    public P_CIMMethodProvider, 
    public P_CIMInstanceProvider,
    public P_CIMAssociationProvider,
    public P_CIMIndicationProvider
{
public:

    Pegasus_Adapter(Provider_Handle* handle);

    virtual ~Pegasus_Adapter();

    virtual void initialize(P_CIMOMHandle& cimom);

    virtual void terminate(void);

    virtual void getInstance(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        const P_Boolean includeQualifiers,
        const P_Boolean includeClassOrigin,
        const P_CIMPropertyList& propertyList,
        P_InstanceResponseHandler& handler);

    virtual void enumerateInstances(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        const P_Boolean includeQualifiers,
        const P_Boolean includeClassOrigin,
        const P_CIMPropertyList& propertyList,
        P_InstanceResponseHandler& handler);

    virtual void enumerateInstanceNames(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        P_ObjectPathResponseHandler& handler);

    virtual void modifyInstance(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        const P_CIMInstance& instance,
        const P_Boolean includeQualifiers,
        const P_CIMPropertyList& propertyList,
        P_ResponseHandler& handler);

    virtual void createInstance(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        const P_CIMInstance& instance,
        P_ObjectPathResponseHandler& handler);

    virtual void deleteInstance(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        P_ResponseHandler& handler);

    virtual void invokeMethod(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectPath,
        const P_CIMName& methodName,
        const Pegasus::Array<P_CIMParamValue>& inParameters,
        P_MethodResultResponseHandler& handler);

    virtual void associators(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectName,
        const P_CIMName& associationClass,
        const P_CIMName& resultClass,
        const P_String& role,
        const P_String& resultRole,
        const P_Boolean includeQualifiers,
        const P_Boolean includeClassOrigin,
        const P_CIMPropertyList& propertyList,
        P_ObjectResponseHandler& handler);

    virtual void associatorNames(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectName,
        const P_CIMName& associationClass,
        const P_CIMName& resultClass,
        const P_String& role,
        const P_String& resultRole,
        P_ObjectPathResponseHandler& handler);

    virtual void references(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectName,
        const P_CIMName& resultClass,
        const P_String& role,
        const P_Boolean includeQualifiers,
        const P_Boolean includeClassOrigin,
        const P_CIMPropertyList& propertyList,
        P_ObjectResponseHandler& handler);

    virtual void referenceNames(
        const P_OperationContext& context,
        const P_CIMObjectPath& objectName,
        const P_CIMName& resultClass,
        const P_String& role,
        P_ObjectPathResponseHandler& handler);

    virtual void enableIndications(
        P_IndicationResponseHandler & handler);

    virtual void disableIndications();

    virtual void createSubscription(
        const P_OperationContext & context,
        const P_CIMObjectPath & subscriptionName,
        const Pegasus::Array<P_CIMObjectPath> & classNames,
        const P_CIMPropertyList & propertyList,
        const P_Uint16 repeatNotificationPolicy);

    virtual void modifySubscription(
        const P_OperationContext & context,
        const P_CIMObjectPath & subscriptionName,
        const Pegasus::Array<P_CIMObjectPath> & classNames,
        const P_CIMPropertyList & propertyList,
        const P_Uint16 repeatNotificationPolicy);

    virtual void deleteSubscription(
        const P_OperationContext & context,
        const P_CIMObjectPath & subscriptionName,
        const Pegasus::Array<P_CIMObjectPath> & classNames);

    const Meta_Class* find_meta_class(
        const P_CIMObjectPath& objectPath) const;

    const Meta_Class* find_model_meta_class(
        const P_CIMObjectPath& objectPath) const;

private:

    P_CIMOMHandle* _handle;
    Provider_Handle* _provider;
    P_IndicationResponseHandler* _handler;
    Atomic_Counter _handler_refs;
    const Meta_Class* _mc;
    P_CIMOMHandle* _cimom_handle;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Pegasus_Adapter_h */
