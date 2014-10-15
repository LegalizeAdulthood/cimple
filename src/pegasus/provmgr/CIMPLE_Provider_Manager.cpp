/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#include <Pegasus/ProviderManager2/OperationResponseHandler.h>
#include <cimple/config.h>
# include <libgen.h>

#include <cstdarg>
#include <cimple/Strings.h>
#include <Pegasus/Common/MofWriter.h>

#include "Converter.h"
#include "CStr.h"
#include "CIMPLE_Provider_Manager.h"


// ATTN: the indication namespace is hard coded for now. 
#define INDICATION_NAMESPACE "root/cimv2"

using namespace std;
using namespace cimple;

PEGASUS_NAMESPACE_BEGIN

//------------------------------------------------------------------------------
//
// _print_instance()
//
//------------------------------------------------------------------------------

#if 0
static void _print_instance(const CIMInstance& inst)
{
    Buffer buf;
    MofWriter::appendInstanceElement(buf, inst);
    buf.append('\0');

    printf("<<<<<<<<<< _print_instance():\n");

    printf("%.*s\n", int(buf.size()), buf.getData());

    printf(">>>>>>>>>>\n");
}
#endif

//------------------------------------------------------------------------------
//
// FTRACE()
//
//------------------------------------------------------------------------------

#if 0
# define FTRACE printf("FTRACE: %s(%d)\n", __FILE__,__LINE__)
#else
# define FTRACE /* empty */
#endif

//------------------------------------------------------------------------------
//
// _set_status()
//
//------------------------------------------------------------------------------

static void _set_status(
    OperationResponseHandler& handler, 
    const char* format,
    ...)
{
    va_list ap;

    va_start(ap, format);
    char* str = str_vprintf(format, ap);
    va_end(ap);

    handler.setStatus(CIM_ERR_FAILED, str);
    free(str);
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::CIMPLE_Provider_Manager()
//
//------------------------------------------------------------------------------

CIMPLE_Provider_Manager::CIMPLE_Provider_Manager() : _disp(0)
{
    FTRACE;

    // Set true by _handleSubscriptionInitCompleteRequest().
    _subscriptionInitComplete = false;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::~CIMPLE_Provider_Manager()
//
//------------------------------------------------------------------------------

CIMPLE_Provider_Manager::~CIMPLE_Provider_Manager()
{
    FTRACE;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::processMessage()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::processMessage(Message* message)
{
    FTRACE;

    // Create dispatcher if null.

    if (!_disp)
	_create_disp(message);

    // Dispatch the message to a handler method.

    Message* response = 0;

    try
    {
	switch (message->getType())
	{
	    case CIM_INITIALIZE_PROVIDER_REQUEST_MESSAGE:
		response = _handleInitializeProviderRequest(message);
		break;

	    case CIM_GET_INSTANCE_REQUEST_MESSAGE:
		response = _handleGetInstanceRequest(message);
		break;

	    case CIM_ENUMERATE_INSTANCES_REQUEST_MESSAGE:
		response = _handleEnumerateInstancesRequest(message);
		break;

	    case CIM_ENUMERATE_INSTANCE_NAMES_REQUEST_MESSAGE:
		response = _handleEnumerateInstanceNamesRequest(message);
		break;

	    case CIM_CREATE_INSTANCE_REQUEST_MESSAGE:
		response = _handleCreateInstanceRequest(message);
		break;

	    case CIM_MODIFY_INSTANCE_REQUEST_MESSAGE:
		response = _handleModifyInstanceRequest(message);
		break;

	    case CIM_DELETE_INSTANCE_REQUEST_MESSAGE:
		response = _handleDeleteInstanceRequest(message);
		break;

	    case CIM_EXEC_QUERY_REQUEST_MESSAGE:
		break;

	    case CIM_ASSOCIATORS_REQUEST_MESSAGE:
		response = _handleAssociatorsRequest(message);
		break;

	    case CIM_ASSOCIATOR_NAMES_REQUEST_MESSAGE:
		response = _handleAssociatorNamesRequest(message);
		break;

	    case CIM_REFERENCES_REQUEST_MESSAGE:
		response = _handleReferencesRequest(message);
		break;

	    case CIM_REFERENCE_NAMES_REQUEST_MESSAGE:
		response = _handleReferenceNamesRequest(message);
		break;

	    case CIM_INVOKE_METHOD_REQUEST_MESSAGE:
		response = _handleInvokeMethodRequest(message);
		break;

	    case CIM_CREATE_SUBSCRIPTION_REQUEST_MESSAGE:
		response = _handleCreateSubscriptionRequest(message);
		break;

	    case CIM_MODIFY_SUBSCRIPTION_REQUEST_MESSAGE:
		response = _handleModifySubscriptionRequest(message);
		break;

	    case CIM_DELETE_SUBSCRIPTION_REQUEST_MESSAGE:
		response = _handleDeleteSubscriptionRequest(message);
		break;

	    case CIM_SUBSCRIPTION_INIT_COMPLETE_REQUEST_MESSAGE:
		response = _handleSubscriptionInitCompleteRequest(message);
		break;

	    // ATTN: implement these:

	    case CIM_GET_PROPERTY_REQUEST_MESSAGE:
	    case CIM_SET_PROPERTY_REQUEST_MESSAGE:
	    case CIM_STOP_ALL_PROVIDERS_REQUEST_MESSAGE:
	    case CIM_EXPORT_INDICATION_REQUEST_MESSAGE:
	    case CIM_DISABLE_MODULE_REQUEST_MESSAGE:
	    case CIM_ENABLE_MODULE_REQUEST_MESSAGE:
	    default:
		return 0;
	}
    }
    catch (...)
    {
	// Unexpected!
	CIMPLE_ASSERT(0);
    }

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleInitializeProviderRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleInitializeProviderRequest(
    Message* message)
{
    FTRACE;

    CIMInitializeProviderRequestMessage* request = 
	dynamic_cast<CIMInitializeProviderRequestMessage*>(message);

    CIMInitializeProviderResponseMessage* response =
	(CIMInitializeProviderResponseMessage*)request->buildResponse();

    OperationResponseHandler handler(request, response);

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleGetInstanceRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleGetInstanceRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMGetInstanceRequestMessage* request =
        dynamic_cast<CIMGetInstanceRequestMessage*>(message);

    CIMGetInstanceResponseMessage* response =
	(CIMGetInstanceResponseMessage*)request->buildResponse();

    // Create handler.

    GetInstanceResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Create CIMPLE instance (initialize key properties).

    Instance* model = 0;

    if (Converter::to_cimple_key(
	request->instanceName.getKeyBindings(), mc, model) != 0)
    {
	_set_status(handler, "malformed object name: %s", Error::get());
	return response;
    }

    Destroyer<Instance> model_d(model);

    // Mark properties mentioned in property list as non-null.

    if (Converter::de_nullify_properties(request->propertyList, model) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    // Invoke provider:

    Instance* inst = 0;
    Status stat = _disp->get_instance(model, inst);
    Destroyer<Instance> inst_d(inst);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    // Convert CIMPLE instance to Pegasus instance.

    CIMInstance pi;

    if (Converter::to_pegasus_instance(
	System::getHostName(), request->nameSpace, inst, pi) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    // Deliver the instance to client.

    handler.processing();
    handler.deliver(pi);
    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleEnumerateInstancesRequest()
//
//------------------------------------------------------------------------------

struct Enum_Instance_Data
{
    EnumerateInstancesResponseHandler* handler;
    CIMNamespaceName name_space;
};

static bool _enum_instances_proc(
    Instance* instance, Enum_Instances_Status status, void* client_data)
{
    FTRACE;

    // Ignore the final call.

    if (!instance)
	return false;

    Destroyer<Instance> instance_d(instance);

    Enum_Instance_Data* data = (Enum_Instance_Data*)client_data;

    CIMInstance pi;

    if (Converter::to_pegasus_instance(
	System::getHostName(), data->name_space, instance, pi) != 0)
    {
	_set_status(*data->handler, "%s", Error::get());
	return false;
    }


    CIMObjectPath path = pi.getPath();
    pi.setPath(path);

    data->handler->deliver(pi);

    // Keep them coming!
    return true;
}

Message* CIMPLE_Provider_Manager::_handleEnumerateInstancesRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMEnumerateInstancesRequestMessage* request =
        dynamic_cast<CIMEnumerateInstancesRequestMessage*>(message);

    CIMEnumerateInstancesResponseMessage* response =
	(CIMEnumerateInstancesResponseMessage*)request->buildResponse();

    // Create handler.

    EnumerateInstancesResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Create the model.

    Instance* model = create(mc);
    Destroyer<Instance> model_d(model);
    nullify_properties(model);

    // Validate properties that appear in the property list.

    if (Converter::de_nullify_properties(request->propertyList, model) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    // Invoke the provider:

    handler.processing();
    State state;
    Enum_Instance_Data data;
    data.handler = &handler;
    data.name_space = request->nameSpace;
    Status stat = _disp->enum_instances(model, _enum_instances_proc, &data);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleEnumerateInstanceNamesRequest()
//
//------------------------------------------------------------------------------

struct Handle_Enumerate_Instance_Names_Data
{
    EnumerateInstanceNamesResponseHandler* handler;
    CIMNamespaceName name_space;
    bool error;
};

static bool _enum_instance_names_proc(
    Instance* instance, Enum_Instances_Status status, void* client_data)
{
    FTRACE;

    Handle_Enumerate_Instance_Names_Data* data = 
	(Handle_Enumerate_Instance_Names_Data*)client_data;

    EnumerateInstanceNamesResponseHandler& handler = *data->handler;

    // Ignore the final call.

    if (!instance || data->error)
	return false;

    Destroyer<Instance> instance_d(instance);

    // Convert to pegasus object path:

    Pegasus::CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	System::getHostName(), data->name_space, instance, op) != 0)
    {
	_set_status(handler, "%s", Error::get());
	data->error = true;
	return false;
    }

    // Deliver to client:

    handler.deliver(op);

    // Keep them coming!
    return true;
}

Message* CIMPLE_Provider_Manager::_handleEnumerateInstanceNamesRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMEnumerateInstanceNamesRequestMessage* request =
        dynamic_cast<CIMEnumerateInstanceNamesRequestMessage*>(message);

    CIMEnumerateInstanceNamesResponseMessage* response =
	(CIMEnumerateInstanceNamesResponseMessage*)request->buildResponse();

    // Create handler.

    EnumerateInstanceNamesResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Create the model (nullify non-key properties).

    Instance* model = create(mc);
    Destroyer<Instance> model_d(model);
    nullify_non_keys(model);

    // Invoke the provider.

    handler.processing();

    Handle_Enumerate_Instance_Names_Data data;
    data.handler = &handler;
    data.name_space = request->nameSpace;
    data.error = false;

    Status stat = _disp->enum_instances(
	model, _enum_instance_names_proc, &data);

    if (data.error)
	return response;

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleCreateInstanceRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleCreateInstanceRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMCreateInstanceRequestMessage* request =
        dynamic_cast<CIMCreateInstanceRequestMessage*>(message);

    CIMCreateInstanceResponseMessage* response =
	(CIMCreateInstanceResponseMessage*)request->buildResponse();

    // Create handler.

    CreateInstanceResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Convert the Pegasus instance to a CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(
	request->newInstance, mc, ci) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ci_d(ci);

    // Be sure that all the key fields are non-null:

    if (!keys_non_null(ci))
    {
	_set_status(handler, "some key fields are null");
	return response;
    }

    // Invoke provider.

    Status stat = _disp->create_instance(ci);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    // Build and deliver the instance name.

    CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	System::getHostName(), request->nameSpace, ci, op) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    handler.processing();
    handler.deliver(op);
    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleModifyInstanceRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleModifyInstanceRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMModifyInstanceRequestMessage* request =
        dynamic_cast<CIMModifyInstanceRequestMessage*>(message);

    CIMModifyInstanceResponseMessage* response =
	(CIMModifyInstanceResponseMessage*)request->buildResponse();

    // Create handler.

    ModifyInstanceResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Convert the Pegasus instance to a CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(request->modifiedInstance, mc, ci) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ci_d(ci);

    // Marks properties mentioned in property list as non-null.

    if (Converter::de_nullify_properties(request->propertyList, ci) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    // Invoke provider:

    Status stat = _disp->modify_instance(ci);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    // Done:

    handler.processing();
    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleDeleteInstanceRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleDeleteInstanceRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMDeleteInstanceRequestMessage* request =
        dynamic_cast<CIMDeleteInstanceRequestMessage*>(message);

    CIMDeleteInstanceResponseMessage* response =
	(CIMDeleteInstanceResponseMessage*)request->buildResponse();

    // Create handler.

    DeleteInstanceResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Create CIMPLE instance (initialize key properties).

    Instance* ci = 0;

    if (Converter::to_cimple_key(
	request->instanceName.getKeyBindings(), mc, ci) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ci_d(ci);

    // Invoke provider.

    Status stat = _disp->delete_instance(ci);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    // Done:

    handler.processing();
    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleAssociatorsRequest()
//
//------------------------------------------------------------------------------

struct Handle_Associators_Request_Data
{
    CIMAssociatorsRequestMessage* request;
    AssociatorsResponseHandler* handler;
    Dispatcher* disp;
    bool error;
};

static bool _enum_associator_proc(
    const Instance* assoc_name,
    Enum_Associator_Names_Status status,
    void* client_data)
{
    FTRACE;

    Handle_Associators_Request_Data* data = 
	(Handle_Associators_Request_Data*)client_data;

    AssociatorsResponseHandler& handler = *data->handler;

    // Ignore last call or if already in an error state:

    if (!assoc_name || data->error)
	return false;

    // Create a model for the get_instance() call below.

    Instance* model = clone(assoc_name);
    Destroyer<Instance> model_d(model);

    if (!model)
    {
	_set_status(handler, "key_to_instance() failed");
	data->error = true;
	return false;
    }

    // Validate selected properties.

    if (Converter::de_nullify_properties(
	data->request->propertyList, model) != 0)
    {
	_set_status(handler, "%s", Error::get());
	data->error = true;
	return false;
    }

    // Now get the instance from the provdier.

    Instance* inst = 0;

    Status stat = data->disp->get_instance(model, inst);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	data->error = true;
	return false;
    }

    Destroyer<Instance> inst_d(inst);

    // Convert to Pegasus instance and deliver.

    CIMInstance pi;

    if (Converter::to_pegasus_instance(
	System::getHostName(), data->request->nameSpace, inst, pi) != 0)
    {
	_set_status(handler, "%s", Error::get());
	data->error = true;
	return false;
    }

    handler.deliver(pi);

    // Keep them coming!
    return true;
}

Message* CIMPLE_Provider_Manager::_handleAssociatorsRequest(
    Message* message)
{
    FTRACE;

    CIMAssociatorsRequestMessage* request =
        dynamic_cast<CIMAssociatorsRequestMessage*>(message);

    CStr assoc_class(request->assocClass);
    CStr result_class(request->resultClass);
    CStr role(request->role);
    CStr result_role(request->resultRole);

    // Create and initialize response.

    CIMAssociatorsResponseMessage* response =
	(CIMAssociatorsResponseMessage*)request->buildResponse();

    // Create handler.

    AssociatorsResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    const Meta_Class* rmc = mc;

    // Convert object name to CIMPLE key.

    CIMObjectPath& op = request->objectName;

    Instance* ck = 0;

    if (Converter::to_cimple_key(op.getKeyBindings(), rmc, ck) != 0 || !ck)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ck_d(ck);

    // Invoke the provider.

    handler.processing();

    Handle_Associators_Request_Data data;
    data.request = request;
    data.handler = &handler;
    data.disp = _disp;
    data.error = false;

    Status stat = _disp->enum_associator_names(ck, assoc_class, result_class, 
	role, result_role, _enum_associator_proc, &data);

    if (data.error)
	return response;

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleAssociatorNamesRequest()
//
//------------------------------------------------------------------------------

struct Handle_Associator_Names_Request_Data
{
    CIMAssociatorNamesRequestMessage* request;
    AssociatorNamesResponseHandler* handler;
    Dispatcher* disp;
    bool error;
};

static bool _enum_associator_names_proc(
    const Instance* assoc_name,
    Enum_Associator_Names_Status status,
    void* client_data)
{
    FTRACE;

    Handle_Associator_Names_Request_Data* data = 
	(Handle_Associator_Names_Request_Data*)client_data;

    AssociatorNamesResponseHandler& handler = *data->handler;

    // Ignore last call or if already in an error state:

    if (!assoc_name || data->error)
	return false;

    // Convert assoc_name to an Pegasus object path:

    CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	System::getHostName(), data->request->nameSpace, assoc_name, op) != 0)
    {
	_set_status(handler, "%s", Error::get());
	data->error = true;
	return false;
    }

    // Deliver the object path:

    handler.deliver(op);

    // Keep them coming!
    return true;
}

Message* CIMPLE_Provider_Manager::_handleAssociatorNamesRequest(
    Message* message)
{
    FTRACE;

    // Get request and response objects:

    CIMAssociatorNamesRequestMessage* request =
        dynamic_cast<CIMAssociatorNamesRequestMessage*>(message);

    CIMAssociatorNamesResponseMessage* response =
	(CIMAssociatorNamesResponseMessage*)request->buildResponse();

    // Extract some of the request fields:

    CStr assoc_class(request->assocClass);
    CStr result_class(request->resultClass);
    CStr role(request->role);
    CStr result_role(request->resultRole);

    // Create handler.

    AssociatorNamesResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    const Meta_Class* rmc = mc;

    // Convert object name to CIMPLE key.

    CIMObjectPath& op = request->objectName;

    Instance* ck = 0;

    if (Converter::to_cimple_key(op.getKeyBindings(), rmc, ck) != 0 || !ck)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ck_d(ck);

    // Invoke provider.

    Handle_Associator_Names_Request_Data data;
    data.request = request;
    data.handler = &handler;
    data.disp = _disp;
    data.error = false;

    Status stat = _disp->enum_associator_names(ck, assoc_class, result_class, 
	role, result_role, _enum_associator_names_proc, &data);

    if (data.error)
	return response;

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleReferencesRequest()
//
//------------------------------------------------------------------------------

struct Handle_References_Request_Data
{
    CIMReferencesRequestMessage* request;
    ReferencesResponseHandler* handler;
    Dispatcher* disp;
    bool error;
};

static bool _enumerate_references_proc(
    Instance* reference,
    Enum_References_Status status,
    void* client_data)
{
    FTRACE;

    Handle_References_Request_Data* data = 
	(Handle_References_Request_Data*)client_data;
    ReferencesResponseHandler& handler = *data->handler;

    // Ignore last call and return if already got an error.

    if (!reference || data->error)
	return false;

    Destroyer<Instance> reference_d(reference);

    // Convert to pegasus instance:

    CIMInstance pi;

    if (Converter::to_pegasus_instance(
	System::getHostName(), data->request->nameSpace, reference, pi) != 0)
    {
	_set_status(handler, "%s", Error::get());
	data->error = true;
	return false;
    }

    handler.deliver(pi);

    // Keep them coming!
    return true;
}

Message* CIMPLE_Provider_Manager::_handleReferencesRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMReferencesRequestMessage* request =
        dynamic_cast<CIMReferencesRequestMessage*>(message);

    CIMReferencesResponseMessage* response =
	(CIMReferencesResponseMessage*)request->buildResponse();

    // Extract some request fields:

    CStr result_class(request->resultClass);
    CStr role(request->role);

    // Create handler.

    ReferencesResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    const Meta_Class* rmc = mc;

    // Convert object name to CIMPLE key.

    CIMObjectPath& op = request->objectName;

    Instance* ck = 0;

    if (Converter::to_cimple_key(op.getKeyBindings(), rmc, ck) != 0 || !ck)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ck_d(ck);

    // Create the model.
    // ATTN: filter model!

    const Meta_Class* result_meta_class = _disp->get_meta_class(result_class);
    Instance* model = cimple::create(result_meta_class);

    // Invoke provider.

    handler.processing();

    Handle_References_Request_Data data;
    data.request = request;
    data.handler = &handler;
    data.disp = _disp;
    data.error = false;

    State state;
    Status stat = _disp->enum_references(
	ck, model, result_class, role, _enumerate_references_proc, &data);

    destroy(model);

    if (data.error)
	return response;

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleReferenceNamesRequest()
//
//------------------------------------------------------------------------------

struct Handle_Reference_Names_Request_Data
{
    CIMReferenceNamesRequestMessage* request;
    ReferenceNamesResponseHandler* handler;
    Dispatcher* disp;
    bool error;
};

static bool _enumerate_reference_names_proc(
    Instance* reference,
    Enum_References_Status status,
    void* client_data)
{
    FTRACE;

    Handle_Reference_Names_Request_Data* data = 
	(Handle_Reference_Names_Request_Data*)client_data;
    ReferenceNamesResponseHandler& handler = *data->handler;

    // Ignore last call and return if already got an error.

    if (!reference || data->error)
	return false;

    Destroyer<Instance> reference_d(reference);

    // Convert to pegasus instance:

    CIMObjectPath op;

    if (Converter::to_pegasus_object_path(
	System::getHostName(), data->request->nameSpace, reference, op) != 0)
    {
	_set_status(handler, "%s", Error::get());
	data->error = true;
	return false;
    }

    handler.deliver(op);

    // Keep them coming.
    return true;
}

Message* CIMPLE_Provider_Manager::_handleReferenceNamesRequest(
    Message* message)
{
    FTRACE;

    // Get request and response:

    CIMReferenceNamesRequestMessage* request =
        dynamic_cast<CIMReferenceNamesRequestMessage*>(message);

    CIMReferenceNamesResponseMessage* response =
	(CIMReferenceNamesResponseMessage*)request->buildResponse();

    // Extract some request fields:

    CStr result_class(request->resultClass);
    CStr role(request->role);

    // Create handler.

    ReferenceNamesResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    const Meta_Class* rmc = mc;

    // Convert object name to CIMPLE key.

    CIMObjectPath& op = request->objectName;

    Instance* ck = 0;

    if (Converter::to_cimple_key(op.getKeyBindings(), rmc, ck) != 0 || !ck)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    Destroyer<Instance> ck_d(ck);

    // Create the model.

    const Meta_Class* result_meta_class = _disp->get_meta_class(result_class);
    Instance* model = cimple::create(result_meta_class);
    nullify_non_keys(model);

    // Invoke provider.

    handler.processing();

    Handle_Reference_Names_Request_Data data;
    data.request = request;
    data.handler = &handler;
    data.disp = _disp;
    data.error = false;

    State state;
    Status stat = _disp->enum_references(ck, model, result_class, role,
	_enumerate_reference_names_proc, &data);

    destroy(model);

    if (data.error)
	return response;

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleInvokeMethodRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleInvokeMethodRequest(
    Message* message)
{
    FTRACE;

    // Create response:

    CIMInvokeMethodRequestMessage* request =
        dynamic_cast<CIMInvokeMethodRequestMessage*>(message);

    CIMInvokeMethodResponseMessage* response =
        (CIMInvokeMethodResponseMessage*)(request->buildResponse());

    // Create handler.

    InvokeMethodResponseHandler handler(request, response);

    // Get meta class.

    CStr class_name(request->className);
    const Meta_Class* mc = _disp->get_meta_class(class_name);

    if (!mc)
    {
	_set_status(handler, "unknown class: %s", class_name.c_str());
	return response;
    }

    // Convert instance name to CIMPLE reference.

    Instance* ref = 0;

    if (Converter::to_cimple_key(
	request->instanceName.getKeyBindings(), mc, ref) != 0)
    {
	_set_status(handler, "malformed object name: %s", Error::get());
	return response;
    }

    Destroyer<Instance> ref_d(ref);

    // Convert to a CIMPLE method:

    CStr meth_name(request->methodName);
    Instance* meth;

    if (Converter::to_cimple_method(
	meth_name, request->inParameters, mc, meth) != 0)
    {
	_set_status(handler, "error: %s", Error::get());
	return response;
    }

    // Invoke the method:

    Status stat = _disp->invoke_method(ref, meth);

    if (stat != STATUS_OK)
    {
	_set_status(handler, "%s", Status_to_string(stat));
	return response;
    }

    // Convert CIMPLE method to Pegasus types:

    Array<CIMParamValue> out_params;
    CIMValue return_value;

    if (Converter::to_pegasus_method(System::getHostName(), 
	request->nameSpace, meth, out_params, return_value) != 0)
    {
	_set_status(handler, "%s", Error::get());
	return response;
    }

    // Deliver the responses:

    handler.processing();

    if (return_value.isNull())
    {
	_set_status(handler, 
	    "method \"%s\" returned null value\n", meth_name.c_str());
	return response;
    }

    handler.deliver(return_value); 

    for (size_t i = 0; i < out_params.size(); i++)
	handler.deliverParamValue(out_params[i]);

    handler.complete();

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleCreateSubscriptionRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleCreateSubscriptionRequest(
    Message* message)
{
    FTRACE;

    // This function is called for each subscription that is made. During
    // server startup, this function is called zero or more times and
    // finally _handleSubscriptionInitCompleteRequest() is called.

    // Create response:

    CIMCreateSubscriptionRequestMessage* request =
        dynamic_cast<CIMCreateSubscriptionRequestMessage*>(message);

    CIMCreateSubscriptionResponseMessage* response =
        (CIMCreateSubscriptionResponseMessage*)(request->buildResponse());

    // Create handler.

    OperationResponseHandler handler(request, response);

    // Create a new subscription for each class name in the request. Add the
    // subscription to the subscriptions table. But if the subscription exists 
    // already, just increment its reference count.

    {
	ProviderIdContainer pidc = request->operationContext.get(
	    ProviderIdContainer::NAME);

	CIMInstance provider = pidc.getProvider();

	for (size_t i = 0, n = request->classNames.size(); i < n; i++)
	{
	    const CIMName& class_name = request->classNames[i];

	    Subscription* sub = _subscription_list.find(class_name);

	    if (sub)
	    {
		// We have seen a subscription on this class already and
		// the provider has already been enabled.
		sub->subscription_count++;
	    }
	    else
	    {
		// This is the first subscription on this class. We must
		// enabled the provider (it the CIM server is not in the
		// process of starting up).

		sub = new Subscription(provider, class_name);
		_subscription_list.append(sub);

		if (_subscriptionInitComplete)
		{
		    if (_enable_indications(sub) != 0)
		    {
			_set_status(handler, "failed to enable indications");
			return response;
		    }
		}
	    }
	}
    }

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleModifySubscriptionRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleModifySubscriptionRequest(
    Message* message)
{
    FTRACE;

    CIMModifySubscriptionRequestMessage* request =
        dynamic_cast<CIMModifySubscriptionRequestMessage*>(message);

    CIMModifySubscriptionResponseMessage* response =
        (CIMModifySubscriptionResponseMessage*)(request->buildResponse());

    OperationResponseHandler handler(request, response);

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleDeleteSubscriptionRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleDeleteSubscriptionRequest(
    Message* message)
{
    FTRACE;

    // Set request and response:

    CIMDeleteSubscriptionRequestMessage* request =
        dynamic_cast<CIMDeleteSubscriptionRequestMessage*>(message);

    CIMDeleteSubscriptionResponseMessage* response =
        (CIMDeleteSubscriptionResponseMessage*)(request->buildResponse());

    // Create handler:

    OperationResponseHandler handler(request, response);

    // Disable indication providers that provide these classes.

    for (size_t i = 0, n = request->classNames.size(); i < n; i++)
    {
	const CIMName& class_name = request->classNames[i];

	Subscription* sub;

	if (_subscription_list.dec_and_remove_if_zero(class_name, sub) == 0)
	{
	    CStr class_name(sub->class_name);
	    Status status = _disp->disable_indications(class_name);
	    delete sub;

	    if (status != STATUS_OK)
	    {
		fprintf(stderr, "failed to disable provider for: %s\n",
		    (const char*)class_name);
	    }
	}
    }

    return response;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_handleSubscriptionInitCompleteRequest()
//
//------------------------------------------------------------------------------

Message* CIMPLE_Provider_Manager::_handleSubscriptionInitCompleteRequest(
    Message* message)
{
    FTRACE;

    // When the server starts, it calls _handleCreateSubscriptionRequest() 
    // for each subscription it finds in the repository. Afterwards it calls
    // _handleCreateSubscriptionRequest() to announce the completion of
    // this process.

    // Set this flag to true so that _handleCreateSubscriptionRequest() will
    // know it is safe to enable indications.

    _subscriptionInitComplete = true;

    // Create response:

    CIMSubscriptionInitCompleteRequestMessage* request =
        dynamic_cast<CIMSubscriptionInitCompleteRequestMessage*>(message);

    CIMSubscriptionInitCompleteResponseMessage* response =
        (CIMSubscriptionInitCompleteResponseMessage*)(request->buildResponse());

    // Create handler.

    OperationResponseHandler handler(request, response);

    // Enable each indication providers for which there is a subscription:

    for (List_Elem* p = _subscription_list.head(); p; p = p->next)
	_enable_indications((Subscription*)p);

    return response;
}

//------------------------------------------------------------------------------
//
// _indication_proc() -- delivers indications
//
//------------------------------------------------------------------------------

struct Indication_Proc_Data
{
    IndicationResponseHandler* handler;
    CIMNamespaceName name_space;
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

    CIMInstance pegasus_indication;

    if (Converter::to_pegasus_instance(System::getHostName(), 
	data->name_space, indication, pegasus_indication) != 0)
    {
	return false;
    }

    // Build an object path for this indication.

    try
    {
	CIMObjectPath objectPath;
	objectPath.setHost(System::getHostName());
	objectPath.setNameSpace(INDICATION_NAMESPACE);
	objectPath.setClassName(indication->meta_class->name);
	pegasus_indication.setPath(objectPath);
	data->handler->deliver(pegasus_indication);
    }
    catch (Exception& e)
    {
	cerr << __FILE__ << "(" << __LINE__ << "): ";
	cerr << e.getMessage() << endl;
    }
    catch (...)
    {
	fprintf(stderr, "ERROR: %s(%d): unexpected\n", __FILE__, __LINE__);
    }

    // Keep them coming!
    return true;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_enable_indications()
//
//------------------------------------------------------------------------------

int CIMPLE_Provider_Manager::_enable_indications(
    Subscription* sub)
{
    FTRACE;

    assert(_indicationCallback != 0);

    // Create the Pegasus indication response handler:

    IndicationResponseHandler* handler = new EnableIndicationsResponseHandler(
	0, 0, sub->provider, _indicationCallback);

    // Use the dispatcher to enable indications on the given provider.

    CStr class_name(sub->class_name);

    // ATTN: this is never deleted!
    Indication_Proc_Data* data = new Indication_Proc_Data;
    data->handler = handler;
    data->name_space = String(INDICATION_NAMESPACE);

    Status status = _disp->enable_indications(
	class_name, _indication_proc, data);

    if (status != STATUS_OK)
	return -1;

    // Succsess!
    return 0;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::_create_disp()
//
//------------------------------------------------------------------------------

void CIMPLE_Provider_Manager::_create_disp(Message* message)
{
    if (_disp)
	return;

    CIMRequestMessage* request = dynamic_cast<CIMRequestMessage*>(message);

    if (!request)
	return;

    try
    {
	const ProviderIdContainer& pic = 
	    request->operationContext.get(ProviderIdContainer::NAME);

	CIMInstance module = pic.getModule();
	String path;
	module.getProperty(
	    module.findProperty("Location")).getValue().get(path);
	path = ProviderManager::_resolvePhysicalName(path);

	CStr tmp(path);

	char* dn = strdup(tmp.c_str());

	_disp = Dispatcher::create(dirname(dn), "cmpl");

	free(dn);
    }
    catch (...)
    {
	fprintf(stderr, "%s(%d): ignored\n", __FILE__, __LINE__);
    }
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::hasActiveProviders()
//
//------------------------------------------------------------------------------

Boolean CIMPLE_Provider_Manager::hasActiveProviders()
{
    return true;
}

//------------------------------------------------------------------------------
//
// CIMPLE_Provider_Manager::unloadIdleProviders()
//
//------------------------------------------------------------------------------

void CIMPLE_Provider_Manager::unloadIdleProviders()
{
}

//------------------------------------------------------------------------------
//
// PegasusCreateProviderManager()
//
//------------------------------------------------------------------------------

extern "C" PEGASUS_EXPORT ProviderManager* PegasusCreateProviderManager(
    const String& providerManagerName)
{
    FTRACE;

    if (String::equalNoCase(providerManagerName, "CIMPLE"))
        return new CIMPLE_Provider_Manager();

    return 0;
}

PEGASUS_NAMESPACE_END

//------------------------------------------------------------------------------
//
// __libcimpleprovmgr()
//
//------------------------------------------------------------------------------

CIMPLE_EXPORT void __libcimpleprovmgr()
{
    // Entry point used by loadpm utility to see if this provider manager
    // can be loaded.
}
