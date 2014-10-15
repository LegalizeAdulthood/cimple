#ifndef _cimple_Benchmark4Provider_h
#define _cimple_Benchmark4Provider_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>

class Benchmark4Provider : public Pegasus::CIMInstanceProvider
{
public:

    Benchmark4Provider();

    virtual ~Benchmark4Provider();

    virtual void initialize(Pegasus::CIMOMHandle& cimom);

    virtual void terminate();

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

private:
    Pegasus::Array<Pegasus::CIMInstance> _instances;
};

#endif /* _cimple_Benchmark4Provider_h */
