#include <Pegasus/Common/System.h>
#include <cimple/Registration.h>
#include "Pegasus_Adapter.h"
#include "Converter.h"
#include "CStr.h"

#define TRACE CIMPLE_TRACE

using namespace Pegasus;

Pegasus_Adapter::Pegasus_Adapter(cimple::Provider_Handle* handle) :
    _handle(handle)
{
    TRACE;
}

Pegasus_Adapter::~Pegasus_Adapter()
{
    TRACE;
}

void Pegasus_Adapter::initialize(CIMOMHandle& cimom)
{
    TRACE;
    _handle->load();
}

void Pegasus_Adapter::terminate(void)
{
    TRACE;
    _handle->unload();
}

void Pegasus_Adapter::getInstance(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const Boolean includeQualifiers,
    const Boolean includeClassOrigin,
    const CIMPropertyList& propertyList,
    InstanceResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    // Create CIMPLE instance (initialize key properties).

    cimple::Instance* model = 0;

    if (Converter::to_cimple_key(objectPath.getKeyBindings(), mc, model) != 0)
	throw CIMException(CIM_ERR_FAILED);

    cimple::Destroyer<cimple::Instance> model_d(model);

    // Mark properties mentioned in property list as non-null.

    if (Converter::de_nullify_properties(propertyList, model) != 0)
	throw CIMException(CIM_ERR_FAILED);

    // Invoke provider:

    cimple::Instance* inst = 0;
    cimple::Get_Instance_Status status = _handle->get_instance(model, inst);
    cimple::Destroyer<cimple::Instance> inst_d(inst);

    switch (status)
    {
	case cimple::GET_INSTANCE_OK:
	    break;

	case cimple::GET_INSTANCE_NOT_FOUND:
	    throw CIMException(CIM_ERR_NOT_FOUND);
	    break;

	case cimple::GET_INSTANCE_UNSUPPORTED:
	    throw CIMException(CIM_ERR_NOT_SUPPORTED);
	    break;
    }


    // Convert CIMPLE instance to Pegasus instance.

    CIMInstance pi;

    if (Converter::to_pegasus_instance(
	System::getHostName(), objectPath.getNameSpace(), inst, pi) != 0)
    {
	throw CIMException(CIM_ERR_FAILED);
    }

    // Deliver the instance to client.

    handler.processing();
    handler.deliver(pi);
    handler.complete();
}

struct Enum_Instance_Data
{
    InstanceResponseHandler* handler;
    CIMNamespaceName name_space;
};

static bool _enum_instances_proc(
    cimple::Instance* instance, 
    cimple::Enum_Instances_Status status, 
    void* client_data)
{
    // Ignore the final call.

    if (!instance)
	return false;

    cimple::Destroyer<cimple::Instance> instance_d(instance);
    Enum_Instance_Data* data = (Enum_Instance_Data*)client_data;
    CIMInstance pi;

    if (Converter::to_pegasus_instance(
	System::getHostName(), data->name_space, instance, pi) != 0)
    {
	// ATTN: what do we do here?
	return false;
    }

    CIMObjectPath path = pi.getPath();
    pi.setPath(path);

    data->handler->deliver(pi);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::enumerateInstances(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const Boolean includeQualifiers,
    const Boolean includeClassOrigin,
    const CIMPropertyList& propertyList,
    InstanceResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    if (!mc)
	throw CIMException(CIM_ERR_INVALID_CLASS);

    // Create the model.

    cimple::Instance* model = create(mc);
    cimple::Destroyer<cimple::Instance> model_d(model);
    nullify_properties(model);

    // Validate properties that appear in the property list.

    if (Converter::de_nullify_properties(propertyList, model) != 0)
	throw CIMException(CIM_ERR_FAILED);

    // Invoke the provider:

    handler.processing();
    Enum_Instance_Data data;
    data.handler = &handler;
    data.name_space = objectPath.getNameSpace();

    cimple::Enum_Instances_Status status = _handle->enum_instances(
	model, _enum_instances_proc, &data);

    switch (status)
    {
	case cimple::ENUM_INSTANCES_OK:
	    break;

	case cimple::ENUM_INSTANCES_FAILED:
	    throw CIMException(CIM_ERR_FAILED);
    }

    handler.complete();
}

//------------------------------------------------------------------------------

struct Handle_Enumerate_Instance_Names_Data
{
    ObjectPathResponseHandler* handler;
    CIMNamespaceName name_space;
    bool error;
};

static bool _enum_instance_names_proc(
    cimple::Instance* instance, 
    cimple::Enum_Instances_Status status, 
    void* client_data)
{
    TRACE;

    Handle_Enumerate_Instance_Names_Data* data = 
	(Handle_Enumerate_Instance_Names_Data*)client_data;

    ObjectPathResponseHandler* handler = data->handler;

    // Ignore the final call.

    if (!instance || data->error)
	return false;

    cimple::Destroyer<cimple::Instance> instance_d(instance);

    // Convert to pegasus object path:

    Pegasus::CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	System::getHostName(), data->name_space, instance, op) != 0)
    {
	data->error = true;
	return false;
    }

    // Deliver to client:

    handler->deliver(op);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::enumerateInstanceNames(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    ObjectPathResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    if (!mc)
	throw CIMException(CIM_ERR_INVALID_CLASS);

    // Create the model (nullify non-key properties).

    cimple::Instance* model = create(mc);
    cimple::Destroyer<cimple::Instance> model_d(model);
    nullify_non_keys(model);

    // Invoke the provider.

    handler.processing();

    Handle_Enumerate_Instance_Names_Data data;
    data.handler = &handler;
    data.name_space = objectPath.getNameSpace();
    data.error = false;

    cimple::Enum_Instances_Status status = _handle->enum_instances(
	model, _enum_instance_names_proc, &data);

    if (data.error)
	throw CIMException(CIM_ERR_FAILED);

    switch (status)
    {
	case cimple::ENUM_INSTANCES_OK:
	    break;

	case cimple::ENUM_INSTANCES_FAILED:
	    throw CIMException(CIM_ERR_FAILED);
    }

    handler.complete();
}

void Pegasus_Adapter::createInstance(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const CIMInstance& instance,
    ObjectPathResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    if (!mc)
	throw CIMException(CIM_ERR_INVALID_CLASS);

    // Convert the Pegasus instance to a CIMPLE instance.

    cimple::Instance* ci = 0;

    if (Converter::to_cimple_instance(instance, mc, ci) != 0)
	throw CIMException(CIM_ERR_FAILED);

    cimple::Destroyer<cimple::Instance> ci_d(ci);

    // Be sure that all the key fields are non-null:

    if (!keys_non_null(ci))
	throw CIMException(CIM_ERR_FAILED);

    // Invoke provider.

    cimple::Create_Instance_Status status = _handle->create_instance(ci);

    switch (status)
    {
	case cimple::CREATE_INSTANCE_OK:
	    break;

	case cimple::CREATE_INSTANCE_DUPLICATE:
	    throw CIMException(CIM_ERR_ALREADY_EXISTS);

	case cimple::CREATE_INSTANCE_UNSUPPORTED:
	    throw CIMException(CIM_ERR_NOT_SUPPORTED);
    }

    // Build and deliver the instance name.

    CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	System::getHostName(), objectPath.getNameSpace(), ci, op) != 0)
    {
	throw CIMException(CIM_ERR_FAILED);
    }

    handler.processing();
    handler.deliver(op);
    handler.complete();
}

void Pegasus_Adapter::modifyInstance(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const CIMInstance& instance,
    const Boolean includeQualifiers,
    const CIMPropertyList& propertyList,
    ResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    if (!mc)
	throw CIMException(CIM_ERR_INVALID_CLASS);

    // Convert the Pegasus instance to a CIMPLE instance.

    cimple::Instance* ci = 0;

    if (Converter::to_cimple_instance(instance, mc, ci) != 0)
	throw CIMException(CIM_ERR_FAILED);

    cimple::Destroyer<cimple::Instance> ci_d(ci);

    // Marks properties mentioned in property list as non-null.

    if (Converter::de_nullify_properties(propertyList, ci) != 0)
	throw CIMException(CIM_ERR_FAILED);

    // Invoke provider:

    cimple::Modify_Instance_Status status = _handle->modify_instance(ci);

    switch (status)
    {
        case cimple::MODIFY_INSTANCE_OK:
	    break;

	case cimple::MODIFY_INSTANCE_NOT_FOUND:
	    throw CIMException(CIM_ERR_NOT_FOUND);

	case cimple::MODIFY_INSTANCE_UNSUPPORTED:
	    throw CIMException(CIM_ERR_NOT_SUPPORTED);
    }

    // Done:

    handler.processing();
    handler.complete();
}

void Pegasus_Adapter::deleteInstance(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    ResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    if (!mc)
	throw CIMException(CIM_ERR_INVALID_CLASS);

    // Create CIMPLE instance (initialize key properties).

    cimple::Instance* ci = 0;

    if (Converter::to_cimple_key(objectPath.getKeyBindings(), mc, ci) != 0)
	throw CIMException(CIM_ERR_FAILED);

    cimple::Destroyer<cimple::Instance> ci_d(ci);

    // Invoke provider.

    cimple::Delete_Instance_Status status = _handle->delete_instance(ci);

    switch (status)
    {
        case cimple::DELETE_INSTANCE_OK:
	    break;

	case cimple::DELETE_INSTANCE_NOT_FOUND:
	    throw CIMException(CIM_ERR_NOT_FOUND);

	case cimple::DELETE_INSTANCE_UNSUPPORTED:
	    throw CIMException(CIM_ERR_NOT_SUPPORTED);
    }

    // Done:

    handler.processing();
    handler.complete();
}

void Pegasus_Adapter::invokeMethod(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const CIMName& methodName,
    const Array<CIMParamValue>& inParameters,
    MethodResultResponseHandler& handler)
{
    TRACE;

    // Get meta class.

    const cimple::Meta_Class* mc = get_meta_class();

    if (!mc)
	throw CIMException(CIM_ERR_INVALID_CLASS);

    // Convert instance name to CIMPLE reference.

    cimple::Instance* ref = 0;

    if (Converter::to_cimple_key(objectPath.getKeyBindings(), mc, ref) != 0)
	throw CIMException(CIM_ERR_FAILED);

    cimple::Destroyer<cimple::Instance> ref_d(ref);

    // Convert to a CIMPLE method:

    CStr meth_name(methodName);
    cimple::Instance* meth;

    if (Converter::to_cimple_method(meth_name, inParameters, mc, meth) != 0)
	throw CIMException(CIM_ERR_FAILED);

    // Invoke the method:

    cimple::Invoke_Method_Status status = _handle->invoke_method(ref, meth);

    switch (status)
    {
        case cimple::INVOKE_METHOD_OK:
	    break;

	case cimple::INVOKE_METHOD_FAILED:
	    throw CIMException(CIM_ERR_FAILED);

	case cimple::INVOKE_METHOD_UNSUPPORTED:
	    throw CIMException(CIM_ERR_NOT_SUPPORTED);
    }

    // Convert CIMPLE method to Pegasus types:

    Array<CIMParamValue> out_params;
    CIMValue return_value;

    if (Converter::to_pegasus_method(System::getHostName(), 
	objectPath.getNameSpace(), meth, out_params, return_value) != 0)
    {
	throw CIMException(CIM_ERR_FAILED);
    }

    // Deliver the responses:

    if (return_value.isNull())
	throw CIMException(CIM_ERR_FAILED);

    handler.processing();
    handler.deliver(return_value); 

    for (size_t i = 0; i < out_params.size(); i++)
	handler.deliverParamValue(out_params[i]);

    handler.complete();
}

extern "C" void* __cimple_create_pegasus_adapter(void* arg1, void* arg2)
{
    TRACE;
    const Pegasus::String& providerName = *((String*)arg1);
    cimple::Registration* head = (cimple::Registration*)arg2;

    for (cimple::Registration* r = head; r; r = r->next)
    {
	if (strcasecmp(r->provider_name, providerName.getCString()) == 0)
	    return new Pegasus_Adapter(new cimple::Provider_Handle(r));
    }

    return 0;
}
