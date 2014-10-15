#ifndef _cimple_Pegasus_Adapter_h
#define _cimple_Pegasus_Adapter_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Provider/CIMMethodProvider.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>
#include <cimple/Provider_Handle.h>

class Pegasus_Adapter : 
    public Pegasus::CIMMethodProvider, 
    public Pegasus::CIMInstanceProvider
{
public:

    Pegasus_Adapter(cimple::Provider_Handle* handle);

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

    const cimple::Meta_Class* get_meta_class() const;

private:

    cimple::Provider_Handle* _handle;
};

inline const cimple::Meta_Class* Pegasus_Adapter::get_meta_class() const
{
    const cimple::Meta_Class* mc;
    _handle->get_meta_class(mc);
    return mc;
}

#endif /* _cimple_Pegasus_Adapter_h */
