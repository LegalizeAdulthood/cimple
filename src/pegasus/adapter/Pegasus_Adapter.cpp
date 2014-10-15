/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
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

#include <cimple/config.h>
#include <pegasus/utils/pegasus.h>
#include <cimple/Registration.h>
#include <cimple/Error.h>
#include <cimple/Provider_Handle.h>
#include <cimple/Buffer.h>
#include "Pegasus_Adapter.h"
#include <pegasus/utils/Converter.h>
#include <pegasus/utils/Str.h>
#include "Pegasus_Thread_Context.h"
#include <cimple/log.h>
#include <cimple/Adapter_Tracer.h>
#include <pegasus/utils/print.h>

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
    ATTN: get host name here.
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
    PENTRY("_check");
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

        case GET_INSTANCE_INVALID_PARAMETER:
        case CREATE_INSTANCE_INVALID_PARAMETER:
        case MODIFY_INSTANCE_INVALID_PARAMETER:
               code = Pegasus::CIM_ERR_INVALID_PARAMETER;
               break;
    
        case GET_INSTANCE_ACCESS_DENIED:
        case ENUM_INSTANCES_ACCESS_DENIED:
        case CREATE_INSTANCE_ACCESS_DENIED:
        case DELETE_INSTANCE_ACCESS_DENIED:
        case MODIFY_INSTANCE_ACCESS_DENIED:
        case ENUM_ASSOCIATOR_NAMES_ACCESS_DENIED:
        case ENUM_REFERENCES_ACCESS_DENIED:
        case INVOKE_METHOD_ACCESS_DENIED:
        case ENUM_ASSOCIATORS_ACCESS_DENIED:
            code = Pegasus::CIM_ERR_ACCESS_DENIED;
            break;

		// define FAILED enums to separate user defined FAILED calls
        // from the default if the return code is not in the status enums.
        case GET_INSTANCE_FAILED:
        case ENUM_INSTANCES_FAILED:
        case CREATE_INSTANCE_FAILED:
        case DELETE_INSTANCE_FAILED:
        case MODIFY_INSTANCE_FAILED:
        case ENUM_REFERENCES_FAILED:
        case INVOKE_METHOD_FAILED:
        case ENUM_ASSOCIATORS_FAILED:
        case ENUM_ASSOCIATOR_NAMES_FAILED:
            code = Pegasus::CIM_ERR_FAILED;
            break;
            
        // Invalid error code defaults to CIM_ERR_FAILED but with
        // log entry.
        default:
            CIMPLE_ERR(("Invalid Error return code = %u\n", cimple_error));
            code = Pegasus::CIM_ERR_FAILED;
    }
    PEXITUINT32(code);
    _throw(code);
}

static int _de_nullify_properties(const P_CIMPropertyList& pl, Instance* ci)
{
    PENTRY("_de_nullify_properties");
    // If the property list is null, define all the properties (the requestor
    // wants them all).

    if (pl.isNull())
    {
        cimple::de_nullify_properties(ci);
        PEXIT();
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

    PEXIT();
    return 0;
}

static bool _contains(const P_CIMPropertyList& pl, const P_CIMName& name)
{
    P_Uint32 n = pl.size();

    for (Pegasus::Uint32 i = 0; i < n; i++)
    {
        if (!pl[i].isNull() && pl[i] == name)
            return true;
    }

    // Not found!
    return false;
}

// Discard properties not in the propertyList
static void _discard_properties(P_CIMInstance& pi, const P_CIMPropertyList& pl)
{
    PENTRY("_discard_properties");
    if (pl.isNull())
    {
        PEXIT();
        return;
    }

    for (P_Uint32 i = 0; i < pi.getPropertyCount(); )
    {
        // If propertyList does not contain this name, remove property
        if (_contains(pl, pi.getProperty(i).getName()))
        {
            i++;
        }
        else
        {
            pi.removeProperty(i);
        }
    }
    PEXIT();
}

Pegasus_Adapter::Pegasus_Adapter(Provider_Handle* provider) :
    _provider(provider), 
    _handler(0),
    _cimom_handle(0)
{
    PENTRY("Pegasus_Adapter");
    CIMPLE_ASSERT(_provider != 0);
    _provider->get_meta_class(_mc);
    PEXIT();
}

Pegasus_Adapter::~Pegasus_Adapter()
{
    PENTRY("~Pegasus_Adapter");
    delete _provider;
    PEXIT();
}

void Pegasus_Adapter::initialize(P_CIMOMHandle& handle)
{
    PENTRY("initialize");
    Auto_Mutex am(mutex);

    _cimom_handle = &handle;

    P_OperationContext context;
    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    _handle = &handle;
    _provider->load();

    PEXIT();
}

void Pegasus_Adapter::terminate(void)
{
    PENTRY("Pegasus_Adapter::terminate");
    Auto_Mutex am(mutex);

    P_OperationContext context;
    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    _provider->unload();
    PEXIT();
}

void Pegasus_Adapter::getInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_Boolean includeQualifiers,
    const P_Boolean includeClassOrigin,
    const P_CIMPropertyList& propertyList,
    P_InstanceResponseHandler& handler)
{

    PENTRY("Pegasus_Adapter::getInstance");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create key.

    Instance* model = 0;

    if (Converter::to_cimple_key(*ns, objectPath, mc, model) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> model_d(model);

    // Mark properties mentioned in property list as non-null.

    if (_de_nullify_properties(propertyList, model) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

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
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    // Discard properties not in property list.
    _discard_properties(pi, propertyList);

    // Deliver the instance to client.

    handler.processing();
    handler.deliver(pi);
    handler.complete();
    PEXIT();
}


//------------------------------------------------------------------------------
//
// Pegasus_Adapter::enumInstances()
//
//------------------------------------------------------------------------------
struct Enum_Instance_Data
{
    P_InstanceResponseHandler* handler;
    P_CIMNamespaceName name_space;
    P_CIMPropertyList propertyList;
};

static bool _enum_instances_proc(
    Instance* instance, 
    Enum_Instances_Status status, 
    void* client_data)
{
    PENTRY("_enum_instances_proc");
    // Ignore the final call.

    if (!instance)
    {
        PEXITBOOL(false);
        return false;
    }

    Ref<Instance> instance_d(instance);
    Enum_Instance_Data* data = (Enum_Instance_Data*)client_data;
    P_CIMInstance pi;

    if (Converter::to_pegasus_instance(_get_host_name(),
        data->name_space, instance, pi) != 0)
    {
        // ATTN: what do we do here?
        PEXITBOOL(true);
        return false;
    }

    // Discard properties:
    _discard_properties(pi, data->propertyList);


    /// KS_TODO delete this logPegasusInstance(pi, LL_DBG, __FILE__, __LINE__);

    data->handler->deliver(pi);

    // Keep them coming!

    PEXITBOOL(true);
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
    PENTRY("enumerateInstances");
    Auto_Mutex am(mutex);

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create the model.

    Instance* model = create(mc);
    Str ns(objectPath.getNameSpace());
    model->__name_space = ns;
    Ref<Instance> model_d(model);
    nullify_properties(model);

    // Validate properties that appear in the property list.

    if (_de_nullify_properties(propertyList, model) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    // Invoke the provider:

    handler.processing();
    Enum_Instance_Data data;
    data.handler = &handler;
    data.name_space = objectPath.getNameSpace();
    data.propertyList = propertyList;

    Enum_Instances_Status status = _provider->enum_instances(
        model, _enum_instances_proc, &data);

    _check(status);
    handler.complete();
    PEXIT();
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
    PENTRY("_enum_instance_names_proc");

    Handle_Enumerate_Instance_Names_Data* data = 
        (Handle_Enumerate_Instance_Names_Data*)client_data;

    P_ObjectPathResponseHandler* handler = data->handler;

    // Ignore the final call.

    if (!instance || data->error)
    {
        PEXITBOOL(false);
        return false;
    }

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
        PEXITBOOL(false);
        return false;
    }

    destroy(instance);

    // Deliver to client:

    handler->deliver(op);

    // Keep them coming!

    PEXITBOOL(true);
    return true;
}

void Pegasus_Adapter::enumerateInstanceNames(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    P_ObjectPathResponseHandler& handler)
{
    PENTRY("Pegasus_Adapter::enumerateInstanceNames");
    Auto_Mutex am(mutex);

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Create the model (nullify non-key properties).

    Instance* model = create(mc);
    Str ns(objectPath.getNameSpace());
    model->__name_space = ns;
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
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    _check(status);

    handler.complete();
    PEXIT();
}

void Pegasus_Adapter::createInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMInstance& instance,
    P_ObjectPathResponseHandler& handler)
{
    PENTRY("Pegasus_Adapter::createInstance");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Convert the Pegasus instance to a CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(*ns, instance, mc, ci) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ci_d(ci);

    // Invoke provider.

    Create_Instance_Status status = _provider->create_instance(ci);

    _check(status);

    // Build and deliver the instance name.

    P_CIMObjectPath op;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
        objectPath.getNameSpace(), ci, op) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    handler.processing();
    handler.deliver(op);
    handler.complete();
    PEXIT();
}

void Pegasus_Adapter::modifyInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMInstance& instance,
    const P_Boolean includeQualifiers,
    const P_CIMPropertyList& propertyList,
    P_ResponseHandler& handler)
{
    PENTRY("Pegasus_Adapter::modifyInstance");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    // Convert Pegasus instance to CIMPLE instance.

    Instance* ci = 0;

    if (Converter::to_cimple_instance(*ns, instance, mc, ci) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ci_d(ci);

    // Create model.

    Instance* model = clone(ci);
    Ref<Instance> model_d(model);

    // Marks properties mentioned in property list as non-null.

    if (_de_nullify_properties(propertyList, model) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    // Invoke provider:

    Modify_Instance_Status status = _provider->modify_instance(model, ci);

    _check(status);

    // Done:

    handler.processing();
    handler.complete();
    PEXIT();
}

void Pegasus_Adapter::deleteInstance(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    P_ResponseHandler& handler)
{
    PENTRY("Pegasus_Adapter::deleteInstance");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(objectPath);

    if (!mc)
    {
        PEXITTHROW(Pegasus::CIM_ERR_INVALID_CLASS);
        _throw(Pegasus::CIM_ERR_INVALID_CLASS);
    }

    // Create CIMPLE instance (initialize key properties).

    Instance* ci = 0;

    if (Converter::to_cimple_key(*ns, objectPath, mc, ci) != 0)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> ci_d(ci);

    // Invoke provider.

    Delete_Instance_Status status = _provider->delete_instance(ci);

    _check(status);

    // Done:

    handler.processing();
    handler.complete();
    PEXIT();
}

void Pegasus_Adapter::invokeMethod(
    const P_OperationContext& context,
    const P_CIMObjectPath& cop,
    const P_CIMName& methodName,
    const Pegasus::Array<P_CIMParamValue>& inParameters,
    P_MethodResultResponseHandler& handler)
{
    Auto_Mutex am(mutex);

    Str ns(cop.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Find model meta class:

    const Meta_Class* mc = find_model_meta_class(cop);

    // Convert instance name to CIMPLE reference.

    Instance* ref = 0;
    Str meth_name(methodName);

    // test if cop is valid.  Should not exist with static method.
    const Meta_Method* mm = find_method(mc, meth_name);

    if ((mm->flags & CIMPLE_FLAG_STATIC) && (cop.getKeyBindings().size() > 0))
    {
        _throw(Pegasus::CIM_ERR_FAILED,
               "Mof static qualifier and object path mismatch");
    }

    // Convert instance name to CIMPLE reference.
    if (Converter::to_cimple_key(*ns, cop, mc, ref) != 0)
    {
            _throw(Pegasus::CIM_ERR_FAILED, "Invalid object path");
    }

    Ref<Instance> ref_d(ref);

    // Convert to a CIMPLE method:

    Instance* meth = 0;

    if (Converter::to_cimple_method(
        *ns, inParameters, *meth_name, mc, CIMPLE_FLAG_IN, meth) != 0)
    {
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    Ref<Instance> meth_d(meth);

    // Invoke the method:

    Invoke_Method_Status status = _provider->invoke_method(ref, meth);

    if (status == INVOKE_METHOD_UNSUPPORTED)
    {
        Buffer buffer;
        buffer.format("unsupported method: %s.%s()", mc->name, *meth_name);
        _throw(Pegasus::CIM_ERR_NOT_SUPPORTED, P_String(buffer.data()));
    }

    // Check CIMPLE status returns and convert to Pegasus returns
    _check(status);

    // Convert CIMPLE method to Pegasus types:

    Pegasus::Array<P_CIMParamValue> out_params;
    P_CIMValue return_value;

    if (Converter::to_pegasus_method(_get_host_name(), cop.getNameSpace(), 
        meth, CIMPLE_FLAG_OUT, out_params, return_value) != 0)
    {
        _throw(Pegasus::CIM_ERR_FAILED, "CIMPLE to Pegasus conversion failed");
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
    PENTRY("_enum_associator_proc_1");
    Handle_Associators_Request_Data_1* data = 
        (Handle_Associators_Request_Data_1*)client_data;

    // Ignore the final call or if already in an error state:

    if (!associator || data->error)
    {
        PEXITBOOL(false);
        return false;
    }

    // Convert associator to pegasus instance.

    P_CIMInstance ci;

    if (Converter::to_pegasus_assoc_instance(_get_host_name(), 
        data->objectPath.getNameSpace(),associator, ci) != 0)
    {
        data->error = true;
        PEXITBOOL(false);
        return false;
    }

    // Discard properties:
    _discard_properties(ci, data->propertyList);
    //logPegasusInstance(ci, LL_DBG, __FILE__, __LINE__);
    PTRACEPEGASUSINSTANCE(ci);
    //printf("_enum_associator_proc_1-2 %s %u \n", __FILE__, __LINE__);    
    data->handler.deliver(ci);

    // Keep them coming!
    PEXITBOOL(true);
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
    PENTRY("_enum_associator_proc_2");
    Handle_Associators_Request_Data_2* data = 
        (Handle_Associators_Request_Data_2*)client_data;

    // Ignore the final call or if already in an error state:

    if (!associator_name || data->error)
    {
        PEXITBOOL(false);
        return false;
    }
    //printf("_enum_associator_proc_2 %s %u associator_name = \n", __FILE__, __LINE__);
    //print(associator_name);
    // Convert associator to object path:

    P_CIMObjectPath objectPath;

    if (Converter::to_pegasus_assoc_object_path(_get_host_name(), 
        data->objectPath.getNameSpace(), associator_name, objectPath) != 0)
    {
        data->error = true;
        PEXITBOOL(false);
        return false;
    }


    //printf("_enum_associator_proc_2 %s %u path %s\n", __FILE__, __LINE__, (const char *)objectPath.toString().getCString());
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
        //logPegasusInstance(instance, LL_DBG, __FILE__, __LINE__);
        PTRACEPEGASUSINSTANCE(instance);
        data->handler.deliver(instance);
    }
    // Error in getInstance. Issue error and ignore
    catch(const  P_CIMException& e)
    {
        CIMPLE_ERR(("CIMException: associators getInstance. path = %s"
                    ". Error = %u, Msg = %s",
            (const char*)objectPath.toString().getCString(),        
            e.getCode(),(const char*)e.getMessage().getCString() ));            
    }
    catch (const P_Exception& e)
    {
        CIMPLE_ERR(("Exception: associators getInstance. path = %s, msg = %s",
                (const char*)objectPath.toString().getCString(),
                 (const char*)e.getMessage().getCString() ));
    }
    catch (...)
    {
        // Ignore!
        CIMPLE_ERR(("Error: associators getInstance path = %s\n",
            (const char*)objectPath.toString().getCString() ));
    }

    // Keep them coming!
    PEXITBOOL(true);
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
    PENTRY("Pegasus_Adapter::associators");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
    {
        // If class in object path not found simply return, no error.
        // This is consistent with the concept in Pegasus at least that
        // the association provider may be called based on the association
        // class and may be called for objects that it does not comprehend.
        // The implication of this is that the association class provider 
        // and the provider for the target instance MUST exist in the
        // same provider module so that both are available with
        // find_meta_class
        //handler.processing();
        //handler.complete();
        PEXIT();
        return;
    }
    // Convert object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(*ns, objectPath, source_mc, ck) != 0 || !ck)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED );
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    //printf("Pegasus_Adapter::associators %s %u \n", __FILE__, __LINE__);
    //print(ck);
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

        //printf("Pegasus_Adapter::associators %s %u \n", __FILE__, __LINE__);
        Enum_Associators_Status status = _provider->enum_associators(
            ck, 
            *Str(resultClass), 
            *Str(role), 
            *Str(resultRole), 
            _enum_associator_proc_1, 
            &data);

        //printf("Pegasus_Adapter::associators %s %u status = %u \n",
        //        __FILE__, __LINE__, (unsigned int)status);
        if (status != ENUM_ASSOCIATORS_UNSUPPORTED)
        {
            if (data.error)
            {
                PEXITTHROW(Pegasus::CIM_ERR_FAILED );
                _throw(Pegasus::CIM_ERR_FAILED);
            }

            _check(status);
            handler.complete();
            PEXIT();
            return;
        }
    }

    //printf("Pegasus_Adapter::associators 2 %s %u \n", __FILE__, __LINE__);
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

        //printf("Pegasus_Adapter::associators 3 %s %u \n", __FILE__, __LINE__);
        // Call common function in Provider_Handle to process instance
        Enum_Associator_Names_Status status = 
            _provider->enum_associator_names(
                ck, 
                *Str(resultClass), 
                *Str(role), 
                *Str(resultRole), 
                _enum_associator_proc_2, 
                &data);

        if (data.error)
        {
            PEXITTHROW(Pegasus::CIM_ERR_FAILED );
            _throw(Pegasus::CIM_ERR_FAILED);
        }

        _check(status);

        //printf("Pegasus_Adapter::associators 4 %s %u \n", __FILE__, __LINE__);
        handler.complete();

        PEXIT();
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
    PENTRY("_enum_associator_names_proc");
    Handle_Associator_Names_Request_Data* data = 
        (Handle_Associator_Names_Request_Data*)client_data;

    // Ignore last call or if already in an error state:

    if (!assoc_name || data->error)
    {
        PEXITBOOL(false);
        return false;
    }

    // Convert assoc_name to an Pegasus object path:

    P_CIMObjectPath op;

    if (Converter::to_pegasus_assoc_object_path(_get_host_name(), 
        data->objectPath.getNameSpace(), assoc_name, op) != 0)
    {
        data->error = true;
        PEXITBOOL(false);
        return false;
    }

    // Deliver the object path:

    data->handler->deliver(op);

    // Keep them coming!
    PEXIT();
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
    PENTRY("Pegasus_Adapter::associatorNames");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
    {
        // See associators for explanation
        PEXIT();
        return;
    }

    Instance* ck = 0;

    if (Converter::to_cimple_key(*ns, objectPath, source_mc, ck) != 0 || !ck)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
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
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    _check(status);

    handler.complete();
    PEXIT();
}

struct Handle_References_Request_Data
{
    P_ObjectResponseHandler& handler;
    const P_CIMObjectPath objectPath;
    P_CIMPropertyList propertyList;
    bool error;

    Handle_References_Request_Data(
        P_ObjectResponseHandler& handler_,
        const P_CIMObjectPath& objectPath_,
        const P_CIMPropertyList& propertyList_)
        :
        handler(handler_),
        objectPath(objectPath_),
        propertyList(propertyList_),
        error(false)
    {
    }
};

static bool _enumerate_references_proc(
    Instance* reference,
    Enum_References_Status status,
    void* client_data)
{
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

    // Discard properties:
    _discard_properties(pi, data->propertyList);

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
    PENTRY("Pegasus_Adapter::references");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
    {
        // See associators for explanation
        PEXIT();
        return;
    }

    // Convert source object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(*ns, objectPath, source_mc, ck) != 0 || !ck)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED );
        _throw(Pegasus::CIM_ERR_INVALID_CLASS);
    }

    Ref<Instance> ck_d(ck);

    // Create model:

    Instance* model = create(assoc_mc);
    nullify_non_keys(model);
    Ref<Instance> model_d(model);

    // Invoke provider.

    handler.processing();

    Handle_References_Request_Data data(handler, objectPath, propertyList);

    Enum_References_Status status = _provider->enum_references(
        ck, 
        model, 
        *Str(role), 
        _enumerate_references_proc, 
        &data);

    // KS_TODO - Check why this does not include the
    // ENUM_REFERENCES_UNSUPPORTED that is in associators
    if (data.error)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED );
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    _check(status);

    handler.complete();
    PEXIT();
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
    PENTRY("_enumerate_reference_names_proc");
    Handle_Reference_Names_Request_Data* data = 
        (Handle_Reference_Names_Request_Data*)client_data;

    // Ignore last call and return if already got an error.

    if (!reference || data->error)
    {
        PEXITBOOL(false);
        return false;
    }

    Ref<Instance> reference_d(reference);

    // Convert to pegasus instance:

    P_CIMObjectPath op;

    if (Converter::to_pegasus_object_path(_get_host_name(), 
        data->objectPath.getNameSpace(), reference, op) != 0)
    {
        data->error = true;
        PEXITBOOL(false);
        return false;
    }

    data->handler.deliver(op);

    // Keep them coming.
    PEXITBOOL(true);
    return true;
}

void Pegasus_Adapter::referenceNames(
    const P_OperationContext& context,
    const P_CIMObjectPath& objectPath,
    const P_CIMName& resultClass,
    const P_String& role,
    P_ObjectPathResponseHandler& handler)
{
    PENTRY("Pegasus_Adapter::referenceNames");
    Auto_Mutex am(mutex);

    Str ns(objectPath.getNameSpace());

    Pegasus_Thread_Context_Pusher pusher(_cimom_handle, &context);

    // Get association meta class.

    const Meta_Class* assoc_mc = _mc;

    // Get source meta class.

    const Meta_Class* source_mc = find_meta_class(objectPath);

    if (!source_mc)
    {
        // See associators for explanation
        PEXIT();
        return;
    }

    // Convert object name to CIMPLE key.

    Instance* ck = 0;

    if (Converter::to_cimple_key(*ns, objectPath, source_mc, ck) != 0 || !ck)
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
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
    {
        PEXITTHROW(Pegasus::CIM_ERR_FAILED);
        _throw(Pegasus::CIM_ERR_FAILED);
    }

    _check(status);

    handler.complete();
    PEXIT();
}

struct Indication_Proc_Data
{
    P_IndicationResponseHandler* handler;
    Pegasus_Adapter* adapter;
};

/*
    Indication processor for the Pegasus adapter.  This processor
    handles a single indication upon each call from the provider.
    Returns true if the request was accepted and more can be delivered.
    NOTE: Today there is an issue with the false return.  It is used
    as the return when indication == 0 which was planned to provide a
    means for the adapter itself to clean up.  Therefore, the false return
    should NEVER be seen by the provider unless it makes an error and sends
    an empty indication.  In that case, the adapter destroys the client_data
    which leaves the adapter in a mess. KS 4 Aug 09
*/
static bool _indication_proc(Instance* indication, void* client_data)
{
    PENTRY("_indication_proc");
    Indication_Proc_Data* data = (Indication_Proc_Data*)client_data;
    Auto_Mutex am(data->adapter->mutex);

    // Delete client data on last call.

    if (indication == 0)
    {
        delete data;
        PEXITBOOL(false);
        return false;
    }

    // Deliver indication on every namespace

    for (size_t i = 0; i < data->adapter->source_name_spaces.size(); i++)
    {
        const String& ns = data->adapter->source_name_spaces[i];

        // Convert CIMPLE indication to Pegasus indication.

        P_CIMInstance pegasus_indication;

        if (Converter::to_pegasus_instance(_get_host_name(), 
            ns.c_str(), indication, pegasus_indication) != 0)
        {
            PEXITBOOL(false);
            return false;
        }

        // Build an object path for this indication. Do nothing
        // if there is an exception

        try
        {
            data->handler->deliver(pegasus_indication);
        }
        catch (...)
        {
            // Ignore!
        }
    }

    // Keep them coming!

    PEXITBOOL(true);
    return true;
}

void Pegasus_Adapter::enableIndications(
    P_IndicationResponseHandler& handler)
{
    PENTRY("Pegasus_Adapter::enableIndications");
    Auto_Mutex am(mutex);

    if (_handler_refs.get() == 0)
    {
        // Save the handler.

        _handler = &handler;
        _handler->processing();

        // Invoke the provider enable_indications() method with the pointer
        // to the indication processor and the indication_proc
        // data structure

        Indication_Proc_Data* data = new Indication_Proc_Data;
        data->handler = _handler;
        data->adapter = this;
        _provider->enable_indications(_indication_proc, data);
    }

    _handler_refs.inc();
    PEXIT();
}

void Pegasus_Adapter::disableIndications()
{
    PENTRY("Pegasus_Adapter::disableIndications");
    Auto_Mutex am(mutex);

    _handler_refs.dec();

    if (_handler_refs.get() == 0)
    {
        // Flush out handler.

        _handler->complete();

        // Invoke the provider disable_indications method.

        _provider->disable_indications();
    }
    PEXIT();
}

/*
    Saves the source namespace
*/
void Pegasus_Adapter::createSubscription(
    const P_OperationContext& context,
    const P_CIMObjectPath& subscriptionName,
    const Pegasus::Array<P_CIMObjectPath>& classNames,
    const P_CIMPropertyList& propertyList,
    const P_Uint16 repeatNotificationPolicy)
{
    PENTRY("Pegasus_Adapter::createSubscription");
    Auto_Mutex am(mutex);

    try
    {
        // Save the  source namespace so that we will have a complete list
        // of namespaces on which to deliver every indication.

        P_SubscriptionFilterQueryContainer c =
            context.get(P_SubscriptionFilterQueryContainer::NAME);

        Str ns(c.getSourceNameSpace());

        bool found = false;

        for (size_t i = 0; i < source_name_spaces.size(); i++)
        {
            if (strcasecmp(source_name_spaces[i].c_str(), *ns) == 0)
                found = true;
        }

        if (!found)
            source_name_spaces.append(*ns);

        // Note: we make no attempt to ever remove these namespaces when
        // the subscriptions are removed.
    }
    catch (...)
    {
        // Ignore.
    }

    // Nothing to do!
    PEXIT();
}

void Pegasus_Adapter::modifySubscription(
    const P_OperationContext& context,
    const P_CIMObjectPath& subscriptionName,
    const Pegasus::Array<P_CIMObjectPath>& classNames,
    const P_CIMPropertyList& propertyList,
    const P_Uint16 repeatNotificationPolicy)
{
    PENTRY("Pegasus_Adapter::modifySubscription");
    // Nothing to do!
    PEXIT();
}

void Pegasus_Adapter::deleteSubscription(
    const P_OperationContext& context,
    const P_CIMObjectPath& subscriptionName,
    const Pegasus::Array<P_CIMObjectPath>& classNames)
{
    PENTRY("Pegasus_Adapter::deleteSubscription");
    // Nothing to do!
    PEXIT();
}

const Meta_Class* Pegasus_Adapter::find_meta_class(
    const P_CIMObjectPath& objectPath) const
{
    PENTRY("Pegasus_Adapter::find_meta_class");
    Str class_name(objectPath.getClassName());

    // Invoke provider to get the meta-repository.

    const Meta_Repository* repository = 0;
    _provider->get_repository(repository);

    if (!repository)
    {
        PEXITUINT32(0);
        return 0;
    }

    // Find the class.

    PEXIT();
    return cimple::find_meta_class(repository, class_name);
}

const Meta_Class* Pegasus_Adapter::find_model_meta_class(
    const P_CIMObjectPath& objectPath) const
{
    PENTRY("Pegasus_Adapter::find_model_meta_class");
    const Meta_Class* mc = find_meta_class(objectPath);

    if (!mc)
    {
        PEXITTHROW(Pegasus::CIM_ERR_NOT_FOUND);
        _throw(Pegasus::CIM_ERR_NOT_FOUND);
    }

    if (!is_subclass(_mc, mc))
    {
        PEXITTHROW(Pegasus::CIM_ERR_NOT_FOUND);
        _throw(Pegasus::CIM_ERR_INVALID_CLASS);
    }

    PEXIT();
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
