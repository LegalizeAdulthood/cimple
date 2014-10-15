#include <cimple/config.h>
#include <pegasus/utils/pegasus.h>
#include <cimple/Registration.h>
#include <cimple/Error.h>
#include <cimple/Provider_Handle.h>
#include <cimple/Buffer.h>
#include "Pegasus_Adapter.h"
#include "Converter.h"
#include <pegasus/utils/Str.h>
#include "Pegasus_Thread_Context.h"

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

#define INDICATION_NAMESPACE "root/cimv2"

// Export cimple_pegasus_adapter() only for shared library.
#ifdef CIMPLE_STATIC
# define CIMPLE_ADAPTER_LINKAGE CIMPLE_HIDE
#else
# define CIMPLE_ADAPTER_LINKAGE CIMPLE_EXPORT
#endif

CIMPLE_NAMESPACE_BEGIN

static P_String _get_host_name()
{
/*
MEB: get host name here.
*/
    return P_String();
}

static void _throw(P_CIMStatusCode code)
{
    // printf("Error: [%s]\n", Error::get());
    throw P_CIMException(code, Error::get());
}

static void _throw(P_CIMStatusCode code, const P_String& msg)
{
    throw P_CIMException(code, msg);
}

static void _check(int cimple_error)
{
    P_CIMStatusCode code;

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

static int _de_nullify_properties(const P_CIMPropertyList& pl, Instance* ci)
{
    // If the property list is null, define all the properties (the requestor
    // wants them all).

    if (pl.isNull())
    {
        cimple::de_nullify_properties(ci);
        return 0;
    }

    // Nullify all properties.

    nullify_non_keys(ci);

    // Denullify requested properties:

    const Meta_Class* mc = ci->meta_class;

    for (size_t i = 0; i < pl.size(); i++)
    {
        Str name(pl[P_Uint32(i)]);

        const Meta_Property* mp = (Meta_Property*)find_feature(mc, *name);

        if (!mp)
        {
            // CIMPLE does not have this property but Pegasus does.
            continue;
        }

        if (mp->flags & CIMPLE_FLAG_KEY)
            continue;

        if (mp->flags & CIMPLE_FLAG_PROPERTY)
            null_of(mp, (char*)ci + mp->offset) = 0;
    }

    return 0;
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
    delete _provider;
    TRACE;
}

void Pegasus_Adapter::initialize(P_CIMOMHandle& handle)
{
    TRACE;

    _cimom_handle = &handle;

    P_OperationContext context;
    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    _handle = &handle;
    _provider->load();
}

void Pegasus_Adapter::terminate(void)
{
    TRACE;

    P_OperationContext context;
    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    _provider->unload();
}

void Pegasus_Adapter::getInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_Boolean includeQualifiers,
    const P_Boolean includeClassOrigin,
    const P_CIMPropertyList& propertyList,
    P_InstanceResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create key.

    Instance* model = 0;

    if (Converter::to_cimple_key(objectPath, mc, model) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> model_d(model);

    // Mark properties mentioned in property list as non-null.

    if (_de_nullify_properties(propertyList, model) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    // Invoke provider:

    Instance* inst = 0;
    Get_Instance_Status status = _provider->get_instance(model, inst);
    Ref<Instance> inst_d(inst);

    _check(status);

    // Convert CIMPLE instance to Pegasus instance.

    P_CIMInstance pi;

    if (Converter::to_pegasus_instance(_get_host_name(),
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
    P_InstanceResponseHandler* handler;
    P_CIMNamespaceName name_space;
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
    P_CIMInstance pi;

    if (Converter::to_pegasus_instance(_get_host_name(),
        data->name_space, instance, pi) != 0)
    {
        // ATTN: what do we do here?
        return false;
    }

    data->handler->deliver(pi);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::enumerateInstances(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_Boolean includeQualifiers,
    const P_Boolean includeClassOrigin,
    const P_CIMPropertyList& propertyList,
    P_InstanceResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create the model.

    Instance* model = create(mc);
    Ref<Instance> model_d(model);
    nullify_properties(model);

    // Validate properties that appear in the property list.

    if (_de_nullify_properties(propertyList, model) != 0)
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
    P_ObjectPathResponseHandler* handler;
    P_CIMNamespaceName name_space;
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

    P_ObjectPathResponseHandler* handler = data->handler;

    // Ignore the final call.

    if (!instance || data->error)
        return false;

#if 0
    Ref<Instance> instance_d(instance);
#endif

    // Convert to pegasus object path:

    P_CIMObjectPath op;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
           data->name_space, instance, op) != 0)
    {
        destroy(instance);
        data->error = true;
        return false;
    }

    destroy(instance);

    // Deliver to client:

    handler->deliver(op);

    // Keep them coming!
    return true;
}

void Pegasus_Adapter::enumerateInstanceNames(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    P_ObjectPathResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create the model (nullify non-key properties).

    Instance* model = create(mc);
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
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMInstance& instance,
    P_ObjectPathResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Convert the Pegasus instance to a CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(instance, mc, ci) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ci_d(ci);

    // Invoke provider.

    Create_Instance_Status status = _provider->create_instance(ci);

    _check(status);

    // Build and deliver the instance name.

    P_CIMObjectPath op;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
        objectPath.getNameSpace(), ci, op) != 0)
    {
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    handler.processing();
    handler.deliver(op);
    handler.complete();
}

void Pegasus_Adapter::modifyInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMInstance& instance,
    const P_Boolean includeQualifiers,
    const P_CIMPropertyList& propertyList,
    P_ResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Convert Pegasus instance to CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(instance, mc, ci) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ci_d(ci);

    // Create model.

    Instance* model = clone(ci);
    Ref<Instance> model_d(model);

    // Marks properties mentioned in property list as non-null.

    if (_de_nullify_properties(propertyList, model) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    // Invoke provider:

    Modify_Instance_Status status = _provider->modify_instance(model, ci);

    _check(status);

    // Done:

    handler.processing();
    handler.complete();
}

void Pegasus_Adapter::deleteInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    P_ResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create CIMPLE instance (initialize key properties).

    Instance* ci = 0;

    if (Converter::to_cimple_key(objectPath, mc, ci) != 0)
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
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMName& methodName,
    const Pegasus::Array<P_CIMParamValue>& inParameters,
    P_MethodResultResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Convert instance name to CIMPLE reference.

    Instance* ref = 0;

    if (Converter::to_cimple_key(objectPath, mc, ref) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> ref_d(ref);

    // Convert to a CIMPLE method:

    Str meth_name(methodName);
    Instance* meth = 0;

    if (Converter::to_cimple_method(inParameters, *meth_name, mc, meth) != 0)
        _throw(Pegasus::CIM_ERR_FAILED);

    Ref<Instance> meth_d(meth);

    // Invoke the method:

    Invoke_Method_Status status = _provider->invoke_method(ref, meth);

    if (status == INVOKE_METHOD_UNSUPPORTED)
    {
        Buffer buffer;
        buffer.format("unsupported method: %s.%s()", mc->name, *meth_name);
        _throw(Pegasus::CIM_ERR_NOT_SUPPORTED, P_String(buffer.data()));
    }

    _check(status);

    // Convert CIMPLE method to Pegasus types:

    Pegasus::Array<P_CIMParamValue> out_params;
    P_CIMValue return_value;

    if (Converter::to_pegasus_method(_get_host_name(), 
        objectPath.getNameSpace(), meth, out_params, return_value) != 0)
    {
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    // Deliver the responses:

    if (return_value.isNull())
    {
        P_String m = "extrinsic method returned a null value: ";
        m.append(mc->name);
        m.append(".");
        m.append(methodName.getString());
        m.append("()");
        _throw(Pegasus::CIM_ERR_FAILED, m);
    }

    handler.processing();
    handler.deliver(return_value); 

    for (size_t i = 0; i < out_params.size(); i++)
        handler.deliverParamValue(out_params[P_Uint32(i)]);

    handler.complete();
}

struct Handle_Associators_Request_Data_1
{
    P_CIMOMHandle* handle;
    const P_OperationContext& context;
    const P_CIMObjectPath& objectPath;
    P_Boolean includeQualifiers;
    P_Boolean includeClassOrigin;
    const P_CIMPropertyList& propertyList;
    P_ObjectResponseHandler& handler;
    bool error;

    Handle_Associators_Request_Data_1(
        P_CIMOMHandle* handle_,
        const P_OperationContext& context_,
        const P_CIMObjectPath& objectPath_,
        P_Boolean includeQualifiers_,
        P_Boolean includeClassOrigin_,
        const P_CIMPropertyList& propertyList_,
        P_ObjectResponseHandler& handler_)
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

static bool _enum_associator_proc_1(
    const Instance* associator,
    Enum_Associators_Status status,
    void* client_data)
{
    Handle_Associators_Request_Data_1* data = 
        (Handle_Associators_Request_Data_1*)client_data;

    // Ignore the final call or if already in an error state:

    if (!associator || data->error)
        return false;

    // Convert associator to pegasus instance.

    P_CIMInstance ci;

    if (Converter::to_pegasus_instance(_get_host_name(), 
        data->objectPath.getNameSpace(), associator, ci) != 0)
    {
        data->error = true;
        return false;
    }

    data->handler.deliver(ci);

    // Keep them coming!
    return true;
}

struct Handle_Associators_Request_Data_2
{
    P_CIMOMHandle* handle;
    const P_OperationContext& context;
    const P_CIMObjectPath& objectPath;
    P_Boolean includeQualifiers;
    P_Boolean includeClassOrigin;
    const P_CIMPropertyList& propertyList;
    P_ObjectResponseHandler& handler;
    bool error;

    Handle_Associators_Request_Data_2(
        P_CIMOMHandle* handle_,
        const P_OperationContext& context_,
        const P_CIMObjectPath& objectPath_,
        P_Boolean includeQualifiers_,
        P_Boolean includeClassOrigin_,
        const P_CIMPropertyList& propertyList_,
        P_ObjectResponseHandler& handler_)
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

static bool _enum_associator_proc_2(
    const Instance* associator_name,
    Enum_Associator_Names_Status status,
    void* client_data)
{
    Handle_Associators_Request_Data_2* data = 
        (Handle_Associators_Request_Data_2*)client_data;

    // Ignore the final call or if already in an error state:

    if (!associator_name || data->error)
        return false;

    // Convert associator to object path:

    P_CIMObjectPath objectPath;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
        data->objectPath.getNameSpace(), associator_name, objectPath) != 0)
    {
        data->error = true;
        return false;
    }

    // Get instance from the provider:

    P_CIMInstance instance;

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

        // ATTN: added this since instance lacks an object path. Find out why!
        instance.setPath(objectPath);

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
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMName& associationClass,
    const P_CIMName& resultClass,
    const P_String& role,
    const P_String& resultRole,
    const P_Boolean includeQualifiers,
    const P_Boolean includeClassOrigin,
    const P_CIMPropertyList& propertyList,
    P_ObjectResponseHandler& handler)
{
    TRACE;

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    // Convert object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(objectPath, source_mc, ck) != 0 || !ck)
    {
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ck_d(ck);

    // Start processing:

    handler.processing();

    // First try enum_associators().
    {
        Handle_Associators_Request_Data_1 data(
            _handle,
            context,
            objectPath,
            includeQualifiers,
            includeClassOrigin,
            propertyList,
            handler);

        Enum_Associators_Status status = _provider->enum_associators(
            ck, 
            *Str(resultClass), 
            *Str(role), 
            *Str(resultRole), 
            _enum_associator_proc_1, 
            &data);

        if (status != ENUM_ASSOCIATORS_UNSUPPORTED)
        {
            if (data.error)
                _throw(Pegasus::CIM_ERR_FAILED);

            _check(status);
            handler.complete();
            return;
        }
    }

    // Second try enum_associator_names().
    {
        Handle_Associators_Request_Data_2 data(
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
                *Str(resultClass), 
                *Str(role), 
                *Str(resultRole), 
                _enum_associator_proc_2, 
                &data);

        if (data.error)
            _throw(Pegasus::CIM_ERR_FAILED);

        _check(status);

        handler.complete();
        return;
    }
}

struct Handle_Associator_Names_Request_Data
{
    P_ObjectPathResponseHandler* handler;
    P_CIMObjectPath objectPath;
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

    P_CIMObjectPath op;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
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
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMName& associationClass,
    const P_CIMName& resultClass,
    const P_String& role,
    const P_String& resultRole,
    P_ObjectPathResponseHandler& handler)
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

    if (Converter::to_cimple_key(objectPath, source_mc, ck) != 0 || !ck)
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
            *Str(resultClass), 
            *Str(role), 
            *Str(resultRole), 
            _enum_associator_names_proc, 
            &data);

    if (data.error)
        _throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

struct Handle_References_Request_Data
{
    P_ObjectResponseHandler& handler;
    const P_CIMObjectPath& objectPath;
    bool error;

    Handle_References_Request_Data(
        P_ObjectResponseHandler& handler_,
        const P_CIMObjectPath& objectPath_)
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

    P_CIMInstance pi;

    if (Converter::to_pegasus_instance(_get_host_name(), 
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
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMName& resultClass,
    const P_String& role,
    const P_Boolean includeQualifiers,
    const P_Boolean includeClassOrigin,
    const P_CIMPropertyList& propertyList,
    P_ObjectResponseHandler& handler)
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

    if (Converter::to_cimple_key(objectPath, source_mc, ck) != 0 || !ck)
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
        *Str(role), 
        _enumerate_references_proc, 
        &data);

    if (data.error)
        _throw(Pegasus::CIM_ERR_FAILED);

    _check(status);

    handler.complete();
}

struct Handle_Reference_Names_Request_Data
{
    P_ObjectPathResponseHandler& handler;
    const P_CIMObjectPath& objectPath;
    bool error;

    Handle_Reference_Names_Request_Data(
        P_ObjectPathResponseHandler& handler_,
        const P_CIMObjectPath& objectPath_)
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

    P_CIMObjectPath op;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
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
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMName& resultClass,
    const P_String& role,
    P_ObjectPathResponseHandler& handler)
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

    if (Converter::to_cimple_key(objectPath, source_mc, ck) != 0 || !ck)
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
        *Str(role), 
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
    P_IndicationResponseHandler* handler;
    P_CIMNamespaceName name_space;
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

    P_CIMInstance pegasus_indication;

    if (Converter::to_pegasus_instance(_get_host_name(), 
        data->name_space, indication, pegasus_indication) != 0)
        return false;

    // Build an object path for this indication.

    try
    {
        P_CIMObjectPath objectPath;
        objectPath.setHost(_get_host_name());
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
    P_IndicationResponseHandler& handler)
{
    if (_handler_refs.get() == 0)
    {
        // Save the handler.

        _handler = &handler;
        _handler->processing();

        // Invoke the provider.

        Indication_Proc_Data* data = new Indication_Proc_Data;
        data->handler = _handler;
        data->name_space = P_String(INDICATION_NAMESPACE);
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
    const P_OperationContext& context,
    const P_CIMObjectPath& subscriptionName,
    const Pegasus::Array<P_CIMObjectPath>& classNames,
    const P_CIMPropertyList& propertyList,
    const P_Uint16 repeatNotificationPolicy)
{
    try
    {
        // ATTN: save namespace and use it to determine which namespace
        // to deliver events on.

        P_SubscriptionFilterQueryContainer c =
            context.get(P_SubscriptionFilterQueryContainer::NAME);

        // c.getSourceNameSpace()
    }
    catch (...)
    {
        // Ignore.
    }

    // Nothing to do!
}

void Pegasus_Adapter::modifySubscription(
    const P_OperationContext& context,
    const P_CIMObjectPath& subscriptionName,
    const Pegasus::Array<P_CIMObjectPath>& classNames,
    const P_CIMPropertyList& propertyList,
    const P_Uint16 repeatNotificationPolicy)
{
    // Nothing to do!
}

void Pegasus_Adapter::deleteSubscription(
    const P_OperationContext& context,
    const P_CIMObjectPath& subscriptionName,
    const Pegasus::Array<P_CIMObjectPath>& classNames)
{
    // Nothing to do!
}

const Meta_Class* Pegasus_Adapter::find_meta_class(
    const P_CIMObjectPath& objectPath) const
{
    Str class_name(objectPath.getClassName());

    // Invoke provider to get the meta-repository.

    const Meta_Repository* repository = 0;
    _provider->get_repository(repository);

    if (!repository)
        return 0;

    // Find the class.

    return cimple::find_meta_class(repository, class_name);
}

const Meta_Class* Pegasus_Adapter::find_model_meta_class(
    const P_CIMObjectPath& objectPath) const
{
    const Meta_Class* mc = find_meta_class(objectPath);

    if (!mc)
        _throw(Pegasus::CIM_ERR_NOT_FOUND);

    if (!is_subclass(_mc, mc))
        _throw(Pegasus::CIM_ERR_INVALID_CLASS);

    return mc;
}

CIMPLE_NAMESPACE_END

extern "C" CIMPLE_ADAPTER_LINKAGE int cimple_pegasus_adapter(
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

    const P_String& providerName = *((P_String*)arg1);
    cimple::Registration* head = (cimple::Registration*)arg2;

    // Create the adapter object:

    for (cimple::Registration* r = head; r; r = r->next)
    {
        if (strcasecmp(r->provider_name, providerName.getCString()) == 0)
        {
            cimple::Provider_Handle* provider = 
                new cimple::Provider_Handle(r);

            cimple::Pegasus_Adapter* adapter =
                new cimple::Pegasus_Adapter(provider);

            *((P_CIMProvider**)arg3) = adapter;
            return 0;
        }
    }

    // Not found!
    return -1;
}
