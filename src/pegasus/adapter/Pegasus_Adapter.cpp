#include <Pegasus/Common/System.h>
#include <cimple/version.h>
#include <cimple/Registration.h>
#include <cimple/Error.h>
#include "Pegasus_Adapter.h"
#include "Converter.h"
#include "CStr.h"
#include "Pegasus_Thread_Context.h"

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

#define INDICATION_NAMESPACE "root/cimv2"

CIMPLE_NAMESPACE_BEGIN

static void _throw(Pegasus::CIMStatusCode code)
{
    // printf("Error: [%s]\n", Error::get());
    throw Pegasus::CIMException(code, Error::get());
}

static void _check(int cimple_error)
{
    Pegasus::CIMStatusCode code;

    switch (cimple_error)
    {
	case 0:
	    return;

	case GET_INSTANCE_NOT_FOUND:
	case MODIFY_INSTANCE_NOT_FOUND:
	case DELETE_INSTANCE_NOT_FOUND:
	    code = Pegasus::CIM_ERR_NOT_FOUND;
	    break;

	case GET_INSTANCE_UNSUPPORTED:
	case CREATE_INSTANCE_UNSUPPORTED:
	case MODIFY_INSTANCE_UNSUPPORTED:
	case DELETE_INSTANCE_UNSUPPORTED:
	case ENUM_ASSOCIATOR_NAMES_UNSUPPORTED:
	case ENUM_REFERENCES_UNSUPPORTED:
	case INVOKE_METHOD_UNSUPPORTED:
	    code = Pegasus::CIM_ERR_NOT_SUPPORTED;
	    break;

	case CREATE_INSTANCE_DUPLICATE:
	    code = Pegasus::CIM_ERR_ALREADY_EXISTS;
	    break;

	default:
	    code = Pegasus::CIM_ERR_FAILED;
    }

    _throw(code);
}

Pegasus_Adapter::Pegasus_Adapter(Provider_Handle* provider) :
    _provider(provider), 
    _handler(0),
    _cimom_handle(0)
{
    TRACE;
    CIMPLE_ASSERT(_provider != 0);
    _provider->get_meta_class(_mc);
}

Pegasus_Adapter::~Pegasus_Adapter()
{
    TRACE;
}

void Pegasus_Adapter::initialize(Pegasus::CIMOMHandle& handle)
{
    TRACE;

    _cimom_handle = &handle;

    Pegasus::OperationContext context;
    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    _handle = &handle;
    _provider->load();
}

void Pegasus_Adapter::terminate(void)
{
    TRACE;

    Pegasus::OperationContext context;
    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    _provider->unload();
}

void Pegasus_Adapter::getInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::InstanceResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Create key.

    Instance* model = 0;

    if (Converter::to_cimple_key(objectPath.getKeyBindings(), _mc, model) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> model_d(model);

    // Mark properties mentioned in property list as non-null.

    if (Converter::de_nullify_properties(propertyList, model) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    // Invoke provider:

    Instance* inst = 0;
    Get_Instance_Status status = _provider->get_instance(model, inst);
    Ref<Instance> inst_d(inst);

    _check(status);

    // Convert CIMPLE instance to Pegasus instance.

    Pegasus::CIMInstance pi;

    if (Converter::to_pegasus_instance(Pegasus::System::getHostName(), 
	objectPath.getNameSpace(), inst, pi) != 0)
    {
	_throw(Pegasus::CIM_ERR_FAILED);
    }

    // Deliver the instance to client.

    handler.processing();
    handler.deliver(pi);
    handler.complete();
}

struct Enum_Instance_Data
{
    Pegasus::InstanceResponseHandler* handler;
    Pegasus::CIMNamespaceName name_space;
};

static bool _enum_instances_proc(
    Instance* instance, 
    Enum_Instances_Status status, 
    void* client_data)
{
    // Ignore the final call.

    if (!instance)
	return false;

    Ref<Instance> instance_d(instance);
    Enum_Instance_Data* data = (Enum_Instance_Data*)client_data;
    Pegasus::CIMInstance pi;

    if (Converter::to_pegasus_instance(
	Pegasus::System::getHostName(), data->name_space, instance, pi) != 0)
    {
	// ATTN: what do we do here?
	return false;
    }

    data->handler->deliver(pi);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::enumerateInstances(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::InstanceResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Create the model.

    Instance* model = create(_mc);
    Ref<Instance> model_d(model);
    nullify_properties(model);

    // Validate properties that appear in the property list.

    if (Converter::de_nullify_properties(propertyList, model) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    // Invoke the provider:

    handler.processing();
    Enum_Instance_Data data;
    data.handler = &handler;
    data.name_space = objectPath.getNameSpace();

    Enum_Instances_Status status = _provider->enum_instances(
	model, _enum_instances_proc, &data);

    _check(status);

    handler.complete();
}

struct Handle_Enumerate_Instance_Names_Data
{
    Pegasus::ObjectPathResponseHandler* handler;
    Pegasus::CIMNamespaceName name_space;
    bool error;
};

static bool _enum_instance_names_proc(
    Instance* instance, 
    Enum_Instances_Status status, 
    void* client_data)
{
    TRACE;

    Handle_Enumerate_Instance_Names_Data* data = 
	(Handle_Enumerate_Instance_Names_Data*)client_data;

    Pegasus::ObjectPathResponseHandler* handler = data->handler;

    // Ignore the final call.

    if (!instance || data->error)
	return false;

    Ref<Instance> instance_d(instance);

    // Convert to pegasus object path:

    Pegasus::CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	Pegasus::System::getHostName(), data->name_space, instance, op) != 0)
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
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    Pegasus::ObjectPathResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Create the model (nullify non-key properties).

    Instance* model = create(_mc);
    Ref<Instance> model_d(model);
    nullify_non_keys(model);

    // Invoke the provider.

    handler.processing();

    Handle_Enumerate_Instance_Names_Data data;
    data.handler = &handler;
    data.name_space = objectPath.getNameSpace();
    data.error = false;

    Enum_Instances_Status status = _provider->enum_instances(
	model, _enum_instance_names_proc, &data);

    if (data.error)
	_throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

void Pegasus_Adapter::createInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMInstance& instance,
    Pegasus::ObjectPathResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Convert the Pegasus instance to a CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(instance, _mc, ci) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ci_d(ci);

    // Be sure that all the key fields are non-null:

    if (!keys_non_null(ci))
	_throw(Pegasus::CIM_ERR_FAILED);

    // Invoke provider.

    Create_Instance_Status status = _provider->create_instance(ci);

    _check(status);

    // Build and deliver the instance name.

    Pegasus::CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	Pegasus::System::getHostName(), objectPath.getNameSpace(), ci, op) != 0)
    {
	_throw(Pegasus::CIM_ERR_FAILED);
    }

    handler.processing();
    handler.deliver(op);
    handler.complete();
}

void Pegasus_Adapter::modifyInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMInstance& instance,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::ResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Convert the Pegasus instance to a CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(instance, _mc, ci) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ci_d(ci);

    // Marks properties mentioned in property list as non-null.

    if (Converter::de_nullify_properties(propertyList, ci) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    // Invoke provider:

    Modify_Instance_Status status = _provider->modify_instance(ci);

    _check(status);

    // Done:

    handler.processing();
    handler.complete();
}

void Pegasus_Adapter::deleteInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    Pegasus::ResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Create CIMPLE instance (initialize key properties).

    Instance* ci = 0;

    if (Converter::to_cimple_key(objectPath.getKeyBindings(), _mc, ci) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ci_d(ci);

    // Invoke provider.

    Delete_Instance_Status status = _provider->delete_instance(ci);

    _check(status);

    // Done:

    handler.processing();
    handler.complete();
}

void Pegasus_Adapter::invokeMethod(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMName& methodName,
    const Pegasus::Array<Pegasus::CIMParamValue>& inParameters,
    Pegasus::MethodResultResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Convert instance name to CIMPLE reference.

    Instance* ref = 0;

    if (Converter::to_cimple_key(objectPath.getKeyBindings(), _mc, ref) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ref_d(ref);

    // Convert to a CIMPLE method:

    CStr meth_name(methodName);
    Instance* meth;

    if (Converter::to_cimple_method(meth_name, inParameters, _mc, meth) != 0)
	_throw(Pegasus::CIM_ERR_FAILED);

    // Invoke the method:

    Invoke_Method_Status status = _provider->invoke_method(ref, meth);

    _check(status);

    // Convert CIMPLE method to Pegasus types:

    Pegasus::Array<Pegasus::CIMParamValue> out_params;
    Pegasus::CIMValue return_value;

    if (Converter::to_pegasus_method(Pegasus::System::getHostName(), 
	objectPath.getNameSpace(), meth, out_params, return_value) != 0)
    {
	_throw(Pegasus::CIM_ERR_FAILED);
    }

    // Deliver the responses:

    if (return_value.isNull())
	_throw(Pegasus::CIM_ERR_FAILED);

    handler.processing();
    handler.deliver(return_value); 

    for (size_t i = 0; i < out_params.size(); i++)
	handler.deliverParamValue(out_params[Pegasus::Uint32(i)]);

    handler.complete();
}

struct Handle_Associators_Request_Data
{
    Pegasus::CIMOMHandle* handle;
    const Pegasus::OperationContext& context;
    const Pegasus::CIMObjectPath& objectPath;
    Pegasus::Boolean includeQualifiers;
    Pegasus::Boolean includeClassOrigin;
    const Pegasus::CIMPropertyList& propertyList;
    Pegasus::ObjectResponseHandler& handler;
    bool error;

    Handle_Associators_Request_Data(
	Pegasus::CIMOMHandle* handle_,
	const Pegasus::OperationContext& context_,
	const Pegasus::CIMObjectPath& objectPath_,
	Pegasus::Boolean includeQualifiers_,
	Pegasus::Boolean includeClassOrigin_,
	const Pegasus::CIMPropertyList& propertyList_,
	Pegasus::ObjectResponseHandler& handler_)
	: 
	handle(handle_),
	context(context_),
	objectPath(objectPath_),
	includeQualifiers(includeQualifiers_),
	includeClassOrigin(includeClassOrigin_),
	propertyList(propertyList_),
	handler(handler_),
	error(false)
    {
    }
};

static bool _enum_associator_proc(
    const Instance* associator_name,
    Enum_Associator_Names_Status status,
    void* client_data)
{
    Handle_Associators_Request_Data* data = 
	(Handle_Associators_Request_Data*)client_data;

    // Ignore the final call or if already in an error state:

    if (!associator_name || data->error)
	return false;

    // Convert associator to object path:

    Pegasus::CIMObjectPath objectPath;

    if (Converter::to_pegasus_object_path(Pegasus::System::getHostName(), 
	data->objectPath.getNameSpace(), associator_name, objectPath) != 0)
    {
	data->error = true;
	return false;
    }

    // Get instance from the provider:

    Pegasus::CIMInstance instance;

    try
    {
	instance = data->handle->getInstance(
	    data->context,
	    data->objectPath.getNameSpace(),
	    objectPath,
	    false,
	    data->includeQualifiers,
	    data->includeClassOrigin,
	    data->propertyList);

	data->handler.deliver(instance);
    }
    catch (...)
    {
	// Ignore!
    }

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::associators(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMName& associationClass,
    const Pegasus::CIMName& resultClass,
    const Pegasus::String& role,
    const Pegasus::String& resultRole,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::ObjectResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    // Convert object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(
	objectPath.getKeyBindings(), source_mc, ck) != 0 || !ck)
    {
	_throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ck_d(ck);

    // Invoke the provider.

    handler.processing();

    Handle_Associators_Request_Data data(
	_handle,
	context,
	objectPath,
	includeQualifiers,
	includeClassOrigin,
	propertyList,
	handler);

    Enum_Associator_Names_Status status = 
	_provider->enum_associator_names(
	    ck, 
	    (const char*)CStr(resultClass), 
	    (const char*)CStr(role), 
	    (const char*)CStr(resultRole), 
	    _enum_associator_proc, 
	    &data);

    if (data.error)
	_throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

struct Handle_Associator_Names_Request_Data
{
    Pegasus::ObjectPathResponseHandler* handler;
    Pegasus::CIMObjectPath objectPath;
    bool error;
};

static bool _enum_associator_names_proc(
    const Instance* assoc_name,
    Enum_Associator_Names_Status status,
    void* client_data)
{
    TRACE;

    Handle_Associator_Names_Request_Data* data = 
	(Handle_Associator_Names_Request_Data*)client_data;

    // Ignore last call or if already in an error state:

    if (!assoc_name || data->error)
	return false;

    // Convert assoc_name to an Pegasus object path:

    Pegasus::CIMObjectPath op;

    if (Converter::to_pegasus_object_path(Pegasus::System::getHostName(), 
	data->objectPath.getNameSpace(), assoc_name, op) != 0)
    {
	data->error = true;
	return false;
    }

    // Deliver the object path:

    data->handler->deliver(op);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::associatorNames(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMName& associationClass,
    const Pegasus::CIMName& resultClass,
    const Pegasus::String& role,
    const Pegasus::String& resultRole,
    Pegasus::ObjectPathResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
	_throw(Pegasus::CIM_ERR_INVALID_CLASS);

    Instance* ck = 0;

    if (Converter::to_cimple_key(
	objectPath.getKeyBindings(), source_mc, ck) != 0 || !ck)
    {
	_throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ck_d(ck);

    // Invoke provider.

    Handle_Associator_Names_Request_Data data;
    data.handler = &handler;
    data.objectPath = objectPath;
    data.error = false;

    Enum_Associator_Names_Status status = 
	_provider->enum_associator_names(
	    ck, 
	    (const char*)CStr(resultClass), 
	    (const char*)CStr(role), 
	    (const char*)CStr(resultRole), 
	    _enum_associator_names_proc, 
	    &data);

    if (data.error)
	_throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

struct Handle_References_Request_Data
{
    Pegasus::ObjectResponseHandler& handler;
    const Pegasus::CIMObjectPath& objectPath;
    bool error;

    Handle_References_Request_Data(
	Pegasus::ObjectResponseHandler& handler_,
	const Pegasus::CIMObjectPath& objectPath_)
	:
	handler(handler_),
	objectPath(objectPath_),
	error(false)
    {
    }
};

static bool _enumerate_references_proc(
    Instance* reference,
    Enum_References_Status status,
    void* client_data)
{
    TRACE;

    Handle_References_Request_Data* data = 
	(Handle_References_Request_Data*)client_data;

    // Ignore last call and return if already got an error.

    if (!reference || data->error)
	return false;

    Ref<Instance> reference_d(reference);

    // Convert to pegasus instance:

    Pegasus::CIMInstance pi;

    if (Converter::to_pegasus_instance(Pegasus::System::getHostName(), 
	data->objectPath.getNameSpace(), reference, pi) != 0)
    {
	data->error = true;
	return false;
    }

    data->handler.deliver(pi);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::references(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMName& resultClass,
    const Pegasus::String& role,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::ObjectResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
	_throw(Pegasus::CIM_ERR_INVALID_CLASS);

    // Convert source object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(
	objectPath.getKeyBindings(), source_mc, ck) != 0 || !ck)
    {
	_throw(Pegasus::CIM_ERR_INVALID_CLASS);
    }

    Ref<Instance> ck_d(ck);

    // Create model:

    Instance* model = create(assoc_mc);
    nullify_non_keys(model);
    Ref<Instance> model_d(model);

    // Invoke provider.

    handler.processing();

    Handle_References_Request_Data data(handler, objectPath);

    Enum_References_Status status = _provider->enum_references(
	ck, 
	model, 
	(const char*)CStr(role), 
	_enumerate_references_proc, 
	&data);

    if (data.error)
	_throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

struct Handle_Reference_Names_Request_Data
{
    Pegasus::ObjectPathResponseHandler& handler;
    const Pegasus::CIMObjectPath& objectPath;
    bool error;

    Handle_Reference_Names_Request_Data(
	Pegasus::ObjectPathResponseHandler& handler_,
	const Pegasus::CIMObjectPath& objectPath_)
	:
	handler(handler_),
	objectPath(objectPath_),
	error(false)
    {
    }
};

static bool _enumerate_reference_names_proc(
    Instance* reference,
    Enum_References_Status status,
    void* client_data)
{
    TRACE;

    Handle_Reference_Names_Request_Data* data = 
	(Handle_Reference_Names_Request_Data*)client_data;

    // Ignore last call and return if already got an error.

    if (!reference || data->error)
	return false;

    Ref<Instance> reference_d(reference);

    // Convert to pegasus instance:

    Pegasus::CIMObjectPath op;

    if (Converter::to_pegasus_object_path(Pegasus::System::getHostName(), 
	data->objectPath.getNameSpace(), reference, op) != 0)
    {
	data->error = true;
	return false;
    }

    data->handler.deliver(op);

    // Keep them coming.
    return true;
}

void Pegasus_Adapter::referenceNames(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMName& resultClass,
    const Pegasus::String& role,
    Pegasus::ObjectPathResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
	_throw(Pegasus::CIM_ERR_INVALID_CLASS);

    // Convert object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(
	objectPath.getKeyBindings(), source_mc, ck) != 0 || !ck)
    {
	_throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ck_d(ck);

    // Create the model.

    Instance* model = create(assoc_mc);
    nullify_non_keys(model);

    // Invoke provider.

    handler.processing();

    Handle_Reference_Names_Request_Data data(handler, objectPath);

    Enum_References_Status status = _provider->enum_references(
	ck, 
	model, 
	(const char*)CStr(role), 
	_enumerate_reference_names_proc, 
	&data);

    destroy(model);

    if (data.error)
	_throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

struct Indication_Proc_Data
{
    Pegasus::IndicationResponseHandler* handler;
    Pegasus::CIMNamespaceName name_space;
};

static bool _indication_proc(Instance* indication, void* client_data)
{
    Indication_Proc_Data* data = (Indication_Proc_Data*)client_data;

    // Delete client data on last call.

    if (indication == 0)
    {
	delete data;
	return false;
    }

    // Convert CIMPLE indication to Pegasus indication.

    Pegasus::CIMInstance pegasus_indication;

    if (Converter::to_pegasus_instance(Pegasus::System::getHostName(), 
	data->name_space, indication, pegasus_indication) != 0)
	return false;

    // Build an object path for this indication.

    try
    {
	Pegasus::CIMObjectPath objectPath;
	objectPath.setHost(Pegasus::System::getHostName());
	objectPath.setNameSpace(INDICATION_NAMESPACE);
	objectPath.setClassName(indication->meta_class->name);
	pegasus_indication.setPath(objectPath);
	data->handler->deliver(pegasus_indication);
    }
    catch (...)
    {
	// Ignore!
    }

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::enableIndications(
    Pegasus::IndicationResponseHandler& handler)
{
    if (_handler_refs.get() == 0)
    {
	// Save the handler.

	_handler = &handler;
	_handler->processing();

	// Invoke the provider.

	Indication_Proc_Data* data = new Indication_Proc_Data;
	data->handler = _handler;
	data->name_space = INDICATION_NAMESPACE;
	_provider->enable_indications(_indication_proc, data);
    }

    _handler_refs.inc();
}

void Pegasus_Adapter::disableIndications()
{
    _handler_refs.dec();

    if (_handler_refs.get() == 0)
    {
	// Flush out handler.

	_handler->complete();

	// Invoke the provider.

	_provider->disable_indications();
    }
}

void Pegasus_Adapter::createSubscription(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& subscriptionName,
    const Pegasus::Array<Pegasus::CIMObjectPath>& classNames,
    const Pegasus::CIMPropertyList& propertyList,
    const Pegasus::Uint16 repeatNotificationPolicy)
{
    // Nothing to do!
}

void Pegasus_Adapter::modifySubscription(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& subscriptionName,
    const Pegasus::Array<Pegasus::CIMObjectPath>& classNames,
    const Pegasus::CIMPropertyList& propertyList,
    const Pegasus::Uint16 repeatNotificationPolicy)
{
    // Nothing to do!
}

void Pegasus_Adapter::deleteSubscription(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& subscriptionName,
    const Pegasus::Array<Pegasus::CIMObjectPath>& classNames)
{
    // Nothing to do!
}

const Meta_Class* Pegasus_Adapter::find_meta_class(
    const Pegasus::CIMObjectPath& objectPath) const
{
    CStr tmp(objectPath.getClassName());
    const char* class_name = (const char*)tmp;

    // Invoke provider to get the meta-repository.

    const Meta_Repository* repository = 0;
    _provider->get_repository(repository);

    if (!repository)
	return 0;

    // Find the class.

    return cimple::find_meta_class(repository, class_name);
}

CIMPLE_NAMESPACE_END

extern "C" CIMPLE_EXPORT int cimple_pegasus_adapter(
    void* arg0, /* provider-interface */
    void* arg1, /* provider-name */
    void* arg2, /* registration */
    void* arg3, /* adapter */
    void* arg4, /* unused */
    void* arg5, /* unused */ 
    void* arg6, /* unused */
    void* arg7) /* unused */
{
    TRACE;

    // Extract arguments:

    const Pegasus::String& providerName = *((Pegasus::String*)arg1);
    cimple::Registration* head = (cimple::Registration*)arg2;

    // Create the adapter object:

    for (cimple::Registration* r = head; r; r = r->next)
    {
	if (strcasecmp(r->provider_name, providerName.getCString()) == 0)
	{
	    cimple::Pegasus_Adapter* adapter =
		new cimple::Pegasus_Adapter(new cimple::Provider_Handle(r));
	    *((Pegasus::CIMProvider**)arg3) = adapter;
	    return 0;
	}
    }

    // Not found!
    return -1;
}

CIMPLE_INJECT_VERSION_TAG;
