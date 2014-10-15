/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** Copyright (c) 2007 Novell, Inc.
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

#include <openwbem/OW_config.h>
#include <openwbem/OW_CIMException.hpp>
#include <openwbem/OW_CIMClass.hpp>
#include <openwbem/OW_CIMValue.hpp>
#include <openwbem/OW_CIMNameSpace.hpp>
#include <cimple/Registration.h>
#include <cimple/Error.h>
#include "OpenWBEM_Adapter.h"
#include "Converter.h"

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

CIMPLE_NAMESPACE_BEGIN

using namespace OpenWBEM; 

///////////////////////////////////////////////////////////////////////////////
#define _throw(code) \
{ \
    OW_THROWCIMMSG(code, Error::get());  \
}

///////////////////////////////////////////////////////////////////////////////
static void _check(int cimple_error)
{
    CIMException::ErrNoType code;

    switch (cimple_error)
    {
        case 0:
            return;

        case GET_INSTANCE_NOT_FOUND:
        case MODIFY_INSTANCE_NOT_FOUND:
        case DELETE_INSTANCE_NOT_FOUND:
            code = CIMException::NOT_FOUND; 
            break;

        case GET_INSTANCE_UNSUPPORTED:
        case CREATE_INSTANCE_UNSUPPORTED:
        case MODIFY_INSTANCE_UNSUPPORTED:
        case DELETE_INSTANCE_UNSUPPORTED:
        case ENUM_ASSOCIATOR_NAMES_UNSUPPORTED:
        case ENUM_REFERENCES_UNSUPPORTED:
        case INVOKE_METHOD_UNSUPPORTED:
            code = CIMException::NOT_SUPPORTED;
            break;

        case CREATE_INSTANCE_DUPLICATE:
            code = CIMException::ALREADY_EXISTS; 
            break;

        default:
            code = CIMException::FAILED; 
    }

    _throw(code);
}

///////////////////////////////////////////////////////////////////////////////
OpenWBEM_Adapter::OpenWBEM_Adapter(Provider_Handle* provider) :
    _provider(provider), 
    _handle(0),
    _cimom_handle(0)
{
    TRACE;
    CIMPLE_ASSERT(_provider != 0);
    _provider->get_meta_class(_mc);
}

///////////////////////////////////////////////////////////////////////////////
OpenWBEM_Adapter::~OpenWBEM_Adapter()
{
    TRACE;
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::initialize(
    const OpenWBEM::ProviderEnvironmentIFCRef& env)
{
    TRACE;
    (void)env; 

    _provider->load();
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::shuttingDown(
    const OpenWBEM::ProviderEnvironmentIFCRef& env)
{
    TRACE;
    (void)env; 

    _provider->unload();
}

///////////////////////////////////////////////////////////////////////////////
struct Handle_Enumerate_Instance_Names_Data
{
    OpenWBEM::CIMObjectPathResultHandlerIFC* handler; 
    OpenWBEM::String name_space; 
    bool error; 
    Handle_Enumerate_Instance_Names_Data() : error(false) {}
};

///////////////////////////////////////////////////////////////////////////////
// TODO why is instance param const for associatorNames, but non const for
// enumInstanceNames? 
template <class STATUS, typename INST>
static bool _enum_instance_names_proc(
    INST instance, 
    STATUS status, 
    void* client_data)
{
    TRACE; 
    Handle_Enumerate_Instance_Names_Data* data = 
        (Handle_Enumerate_Instance_Names_Data*) client_data; 

    // Ignore the final call. 
    if (!instance || data->error)
    {
        return false; 
    }

    Ref<Instance> instance_d(instance); 

    OpenWBEM::CIMObjectPath cop; 
    if (Converter::to_openwbem_object_path(
        data->name_space, instance, cop) != 0)
    {
        TRACE; 
        data->error = true; 
        return false; 
    }
    data->handler->handle(cop); 

    return true; 
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::enumInstanceNames(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    const OpenWBEM::String& ns,
    const OpenWBEM::String& className,
    OpenWBEM::CIMObjectPathResultHandlerIFC& result,
    const OpenWBEM::CIMClass& cimClass )
{
    TRACE; 

    // Find model meta class: 
    CIMObjectPath cop(className, ns); 
    const Meta_Class* mc = find_model_meta_class(cop); 

    // Create the model (nullify non-key properties)
    const Instance* model = create(mc);
    Ref<Instance> model_d(model); 
    nullify_non_keys(model); 

    // Invoke the provider
    Handle_Enumerate_Instance_Names_Data data; 
    data.handler = &result; 
    data.name_space = ns; 
    data.error = false; 

    Enum_Instances_Status status = _provider->enum_instances(model, 
                _enum_instance_names_proc<Enum_Instances_Status, Instance*>, 
                &data); 
    if (data.error)
    {
        _throw(CIMException::FAILED); 
    }
    _check(status); 
}

///////////////////////////////////////////////////////////////////////////////
struct Enum_Instances_Data
{
    OpenWBEM::CIMInstanceResultHandlerIFC* handler; 
    OpenWBEM::String name_space; 
    bool error; 
    Enum_Instances_Data() : error(false) {}
};

///////////////////////////////////////////////////////////////////////////////
template <class STATUS>
static bool _enum_instances_proc(Instance* instance, 
    STATUS status, 
    void* client_data)
{
    Enum_Instances_Data* data = (Enum_Instances_Data*)client_data; 
    // Ignore the final call. 
    if (!instance || data->error)
    {
        return false; 
    }

    Ref<Instance> instance_d(instance); 
    OpenWBEM::CIMInstance oi; 

    if (Converter::to_openwbem_instance(data->name_space, instance, oi) != 0)
    {
        TRACE; 
        // ATTN: what do we do here? 
        data->error = true; 
        return false; 
    }

    data->handler->handle(oi); 

    // Keep them coming!
    return true; 
}
///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::enumInstances(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    const OpenWBEM::String& ns,
    const OpenWBEM::String& className,
    OpenWBEM::CIMInstanceResultHandlerIFC& result,
    OpenWBEM::WBEMFlags::ELocalOnlyFlag localOnly,
    OpenWBEM::WBEMFlags::EDeepFlag deep,
    OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
    OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
    const OpenWBEM::StringArray* propertyList,
    const OpenWBEM::CIMClass& requestedClass,
    const OpenWBEM::CIMClass& cimClass )
{
    TRACE; 
    // Find model meta class: 
    CIMObjectPath cop(className, ns); 
    const Meta_Class* mc = find_model_meta_class(cop); 

    // Create the model. 
    Instance* model = create(mc); 
    Ref<Instance> model_d(model); 
    nullify_properties(model); 

    if (Converter::de_nullify_properties(propertyList, model) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    // Invoke the provider
    Enum_Instances_Data data; 
    data.handler = &result; 
    data.name_space = ns; 

    Enum_Instances_Status status = _provider->enum_instances(model, 
                _enum_instances_proc<Enum_Instances_Status>, &data); 
    _check(status); 
}

///////////////////////////////////////////////////////////////////////////////
OpenWBEM::CIMInstance OpenWBEM_Adapter::getInstance(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    const OpenWBEM::String& ns,
    const OpenWBEM::CIMObjectPath& instanceName,
    OpenWBEM::WBEMFlags::ELocalOnlyFlag localOnly,
    OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
    OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
    const OpenWBEM::StringArray* propertyList,
    const OpenWBEM::CIMClass& cimClass )
{
    TRACE; 
    // find the model class: 
    const Meta_Class* mc = find_model_meta_class(instanceName); 
    // Create key. 
    Instance* model = 0; 

    if (Converter::to_cimple_key(instanceName, mc, model) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    Ref<Instance> model_d(model); 

    // mark properties mentioned in property list as non-null. 
    if (Converter::de_nullify_properties(propertyList, model) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    // Invoke provider
    Instance* inst = 0; 
    Get_Instance_Status status = _provider->get_instance(model, inst); 
    Ref<Instance> inst_d(inst); 
    _check(status); 

    // Convert CIMPLE instance to OpenWBEM instance. 
    OpenWBEM::CIMInstance oi = cimClass.newInstance(); 

    if (Converter::to_openwbem_instance(ns, inst, oi) != 0)
    {
        _throw(CIMException::FAILED); 
    }
    TRACE; 
    return oi; 
}

///////////////////////////////////////////////////////////////////////////////
OpenWBEM::CIMObjectPath OpenWBEM_Adapter::createInstance(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    const OpenWBEM::String& ns,
    const OpenWBEM::CIMInstance& cimInstance )
{
    TRACE; 
    // find model meta class: 
    CIMObjectPath cop(cimInstance.getClassName(), ns); 
    cop.setKeys(cimInstance); 
    const Meta_Class* mc = find_model_meta_class(cop); 

    // convert the OpenWBEM instance to a CIMPLE instance. 
    Instance* ci = 0; 
    if (Converter::to_cimple_instance(cimInstance, mc, ci) != 0)
    {
        _throw(CIMException::FAILED); 
    }
    Ref<Instance> ci_d(ci); 

    // be sure that all fields are non-null; 

    if (!keys_non_null(ci))
    {
        _throw(CIMException::FAILED); 
    }

    // Invoke provider
    Create_Instance_Status status = _provider->create_instance(ci); 
    _check(status); 

    // build and return the instance name. 

    if (Converter::to_openwbem_object_path(ns, ci, cop) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    return cop; 
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::modifyInstance(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    const OpenWBEM::String& ns,
    const OpenWBEM::CIMInstance& modifiedInstance,
    const OpenWBEM::CIMInstance& previousInstance,
    OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
    const OpenWBEM::StringArray* propertyList,
    const OpenWBEM::CIMClass& theClass)
{
    TRACE; 
    // find the model meta class: 
    CIMObjectPath cop(modifiedInstance.getClassName(), ns); 
    cop.setKeys(modifiedInstance); 
    const Meta_Class* mc = find_model_meta_class(cop); 

    // convert the OpenWBEM instance to a CIMPLE instance. 
    Instance* ci = 0; 
    if (Converter::to_cimple_instance(modifiedInstance, mc, ci)!= 0)
    {
        _throw(CIMException::FAILED); 
    }

    Ref<Instance> ci_d(ci); 

    // marks propertied mentioned in property list as non-null. 
    if (Converter::de_nullify_properties(propertyList, ci) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    // Invoke the provider
    Modify_Instance_Status status = _provider->modify_instance(ci); 
    _check(status); 
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::deleteInstance(
                    const OpenWBEM::ProviderEnvironmentIFCRef& env,
                    const OpenWBEM::String& ns,
                    const OpenWBEM::CIMObjectPath& cop)
{
    TRACE; 
    // find model meta class: 
    const Meta_Class* mc = find_model_meta_class(cop); 

    // create CIMPLE instance (initialize key properties). 
    Instance* ci = 0; 
    if (Converter::to_cimple_key(cop, mc, ci)!= 0)
    {
        _throw(CIMException::FAILED); 
    }
    Ref<Instance> ci_d(ci); 

    //Invoke the provider
    Delete_Instance_Status status = _provider->delete_instance(ci); 
    _check(status); 
}

///////////////////////////////////////////////////////////////////////////////
OpenWBEM::CIMValue OpenWBEM_Adapter::invokeMethod(
                    const OpenWBEM::ProviderEnvironmentIFCRef& env,
                    const OpenWBEM::String& ns,
                    const OpenWBEM::CIMObjectPath& path,
                    const OpenWBEM::String& methodName,
                    const OpenWBEM::CIMParamValueArray& in,
                    OpenWBEM::CIMParamValueArray& out )
{
    TRACE; 
    // find model meta class
    const Meta_Class* mc = find_model_meta_class(path); 
    // convert instance name to CIMPLE instance
    Instance* ref = 0; 
    if (Converter::to_cimple_key(path, mc, ref)!= 0)
    {
        _throw(CIMException::FAILED); 
    }
    Ref<Instance> ref_d(ref); 
    // convert to a CIMPLE method:

    Instance* meth = 0; 
    if (Converter::to_cimple_method(methodName, in, mc, meth) != 0)
    {
        _throw(CIMException::FAILED); 
    }
    Ref<Instance> meth_d(meth); 
    // invoke the method
    Invoke_Method_Status status = _provider->invoke_method(ref, meth); 
    _check(status); 

    // convert CIMPLE method to OpenWBEM types
    OpenWBEM::CIMValue return_value(CIMNULL); 
    if (Converter::to_openwbem_method(path, meth, out, return_value) != 0)
    {
        _throw(CIMException::FAILED); 
    }
    if (!return_value)
    {
        // TODO: really?  null return values aren't allowed? 
        _throw(CIMException::FAILED); 
    }
    return return_value; 
}

///////////////////////////////////////////////////////////////////////////////
struct Handle_Associators_Request_Data
{
    OpenWBEM::CIMOMHandleIFCRef handle; 
    const OpenWBEM::CIMObjectPath& objectPath; 
    OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers; 
    OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin; 
    const OpenWBEM::StringArray* propertyList; 
    OpenWBEM::CIMInstanceResultHandlerIFC& handler; 
    bool error; 
    Handle_Associators_Request_Data(
        OpenWBEM::CIMOMHandleIFCRef handle_, 
        const OpenWBEM::CIMObjectPath& objectPath_, 
        OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers_, 
        OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin_, 
        const OpenWBEM::StringArray* propertyList_, 
        OpenWBEM::CIMInstanceResultHandlerIFC& handler_)
        : handle(handle_)
        , objectPath(objectPath_)
        , includeQualifiers(includeQualifiers_)
        , includeClassOrigin(includeClassOrigin_)
        , propertyList(propertyList_) 
        , handler(handler_)
        , error(false)
        {}
};

static bool _enum_associators_proc(const Instance* associator_name, 
                                   Enum_Associator_Names_Status status, 
                                   void* client_data)
{
    Handle_Associators_Request_Data* data = 
        (Handle_Associators_Request_Data*)client_data; 

    // ignore the final call or if already in an error state. 
    if (!associator_name || data->error)
    {
        return false; 
    }
    // convert associator to object path. 
    OpenWBEM::CIMObjectPath objectPath; 
    OpenWBEM::String ns = data->objectPath.getFullNameSpace().getNameSpace(); 
    if (Converter::to_openwbem_object_path(ns, 
                        associator_name, objectPath) != 0)
    {
        data->error = true; 
        return false; 
    }

    // get instance from provider:
    OpenWBEM::CIMInstance instance; 
    try
    {
        instance = data->handle->getInstance(ns, 
                                             objectPath, 
                                             WBEMFlags::E_NOT_LOCAL_ONLY, 
                                             data->includeQualifiers, 
                                             data->includeClassOrigin, 
                                             data->propertyList); 
        instance.setNameSpace(ns); 
        data->handler.handle(instance); 
    }
    catch(...)
    {
        TRACE; 
        // ignore!
    }
    // keep them coming!
    return true; 
}
///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::associators(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    OpenWBEM::CIMInstanceResultHandlerIFC& result,
    const OpenWBEM::String& ns,
    const OpenWBEM::CIMObjectPath& objectName,
    const OpenWBEM::String& assocClass,
    const OpenWBEM::String& resultClass,
    const OpenWBEM::String& role,
    const OpenWBEM::String& resultRole,
    OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
    OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
    const OpenWBEM::StringArray* propertyList)
{
    TRACE; 
    // get association meta class
    const Meta_Class* assoc_mc = _mc; 

    // get source meta class
    const Meta_Class* source_mc = find_meta_class(objectName); 
    // convert object name to CIMPLE key
    Instance* ck = 0; 
    if (Converter::to_cimple_key(objectName, source_mc, ck) != 0)
    {
        _throw(CIMException::FAILED); 
    }
    Ref<Instance> ck_d(ck); 
    // Invoke the provider
    Handle_Associators_Request_Data data(env->getCIMOMHandle(), 
                                         objectName, 
                                         includeQualifiers, 
                                         includeClassOrigin, 
                                         propertyList, 
                                         result); 
    Enum_Associator_Names_Status status = _provider->enum_associator_names(
                ck, 
                resultClass.c_str(), 
                role.c_str(), 
                resultRole.c_str(), 
                _enum_associators_proc, 
                &data); 
    if (data.error)
    {
        _throw(CIMException::FAILED); 
    }
    _check(status); 
}


///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::associatorNames(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    OpenWBEM::CIMObjectPathResultHandlerIFC& result,
    const OpenWBEM::String& ns,
    const OpenWBEM::CIMObjectPath& objectName,
    const OpenWBEM::String& assocClass,
    const OpenWBEM::String& resultClass,
    const OpenWBEM::String& role,
    const OpenWBEM::String& resultRole )
{
    TRACE; 
    // get association meta class. 
    const Meta_Class* assoc_mc = _mc; 
    // get source meta class. 
    const Meta_Class* source_mc = find_meta_class(objectName); 

    if (!source_mc)
    {
        _throw(CIMException::INVALID_CLASS); 
    }

    Instance* ck = 0; 

    if (Converter::to_cimple_key(objectName, source_mc, ck) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    Ref<Instance> ck_d(ck); 

    // invoke provider
    Handle_Enumerate_Instance_Names_Data data; 
    data.handler = &result; 
    data.name_space = ns; 
    Enum_Associator_Names_Status status = _provider->enum_associator_names(ck, 
        resultClass.c_str(), 
        role.c_str(), 
        resultRole.c_str(),
        _enum_instance_names_proc<Enum_Associator_Names_Status,const Instance*>,
        &data);
    if (data.error)
    {
        _throw(CIMException::FAILED); 
    }
    _check(status); 
}
///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::references(
    const OpenWBEM::ProviderEnvironmentIFCRef& env,
    OpenWBEM::CIMInstanceResultHandlerIFC& result,
    const OpenWBEM::String& ns,
    const OpenWBEM::CIMObjectPath& objectName,
    const OpenWBEM::String& resultClass,
    const OpenWBEM::String& role,
    OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
    OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
    const OpenWBEM::StringArray* propertyList)
{
    TRACE; 
    // Get association meta class
    const Meta_Class* assoc_mc = _mc;
    // get source meta class
    const Meta_Class* source_mc = find_meta_class(objectName);
    if (!source_mc)
    {
        _throw(CIMException::INVALID_CLASS); 
    }

    // convert source object name to CIMPLE key
    Instance* ck = 0; 
    if (Converter::to_cimple_key(objectName, source_mc, ck)!= 0 || !ck)
    {
        _throw(CIMException::INVALID_CLASS); 
    }

    Ref<Instance> ck_d(ck); 
    // create model
    Instance* model = create(assoc_mc); 
    Ref<Instance> model_d(model); 
    nullify_properties(model); 

    if (Converter::de_nullify_properties(propertyList, model) != 0)
    {
        _throw(CIMException::FAILED); 
    }

    // invoke provider
    Enum_Instances_Data data; 
    data.handler = &result; 
    data.name_space = ns; 
    Enum_References_Status status = _provider->enum_references(
        ck, model, role.c_str(), 
        _enum_instances_proc<Enum_References_Status>, &data);
    if (data.error)
    {
        _throw(CIMException::FAILED); 
    }
    _check(status); 
}
///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::referenceNames(
                    const OpenWBEM::ProviderEnvironmentIFCRef& env,
                    OpenWBEM::CIMObjectPathResultHandlerIFC& result,
                    const OpenWBEM::String& ns,
                    const OpenWBEM::CIMObjectPath& objectName,
                    const OpenWBEM::String& resultClass,
                    const OpenWBEM::String& role )
{
    TRACE; 
    // Get association meta class; 
    const Meta_Class* assoc_mc = _mc; 
    // get source meta class
    const Meta_Class* source_mc = find_meta_class(objectName); 
    if (!source_mc)
    {
        _throw(CIMException::INVALID_CLASS); 
    }
    // convert object name to cimple key
    Instance* ck = 0; 
    if (Converter::to_cimple_key(objectName, source_mc, ck) != 0 || !ck)
    {
        _throw(CIMException::FAILED); 
    }

    Ref<Instance> ck_d(ck); 
    // create the model
    Instance* model = create(assoc_mc); 
    Ref<Instance> model_d(model); 
    nullify_non_keys(model); 
    // invoke provider
    Handle_Enumerate_Instance_Names_Data data; 
    data.name_space = ns; 
    data.handler = &result; 
    Enum_References_Status status = _provider->enum_references(
            ck, model, role.c_str(), 
            _enum_instance_names_proc<Enum_References_Status>, &data); 

    if (data.error)
    {
        _throw(CIMException::FAILED); 
    }
    _check(status); 

}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::activateFilter(
            const OpenWBEM::ProviderEnvironmentIFCRef& env,
            const OpenWBEM::WQLSelectStatement& filter, 
            const OpenWBEM::String& eventType, 
            const OpenWBEM::String& nameSpace,
            const OpenWBEM::StringArray& classes, 
            bool firstActivation
            )
{
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::authorizeFilter(
            const OpenWBEM::ProviderEnvironmentIFCRef& env,
            const OpenWBEM::WQLSelectStatement& filter, 
            const OpenWBEM::String& eventType, 
            const OpenWBEM::String& nameSpace,
            const OpenWBEM::StringArray& classes, 
            const OpenWBEM::String& owner
            )
{
}

///////////////////////////////////////////////////////////////////////////////
void OpenWBEM_Adapter::deActivateFilter(
            const OpenWBEM::ProviderEnvironmentIFCRef& env,
            const OpenWBEM::WQLSelectStatement& filter, 
            const OpenWBEM::String& eventType, 
            const OpenWBEM::String& nameSpace,
            const OpenWBEM::StringArray& classes, 
            bool lastActivation
            )
{
}
///////////////////////////////////////////////////////////////////////////////
int OpenWBEM_Adapter::mustPoll(
            const OpenWBEM::ProviderEnvironmentIFCRef& env,
            const OpenWBEM::WQLSelectStatement& filter, 
            const OpenWBEM::String& eventType, 
            const OpenWBEM::String& nameSpace,
            const OpenWBEM::StringArray& classes
            )
{
    return -1; 
}
///////////////////////////////////////////////////////////////////////////////
const Meta_Class* OpenWBEM_Adapter::find_meta_class(
    const OpenWBEM::CIMObjectPath& objectPath) const
{
    // Invoke provider to get the meta-repository.

    const Meta_Repository* repository = 0;
    _provider->get_repository(repository);

    if (!repository)
        return 0;

    // Find the class.

    return cimple::find_meta_class(repository, 
        objectPath.getClassName().c_str());
}

///////////////////////////////////////////////////////////////////////////////
const Meta_Class* OpenWBEM_Adapter::find_model_meta_class(
    const OpenWBEM::CIMObjectPath& objectPath) const
{
    const Meta_Class* mc = find_meta_class(objectPath);

    if (!mc)
        _throw(CIMException::NOT_FOUND); 

    if (!is_subclass(_mc, mc))
        _throw(CIMException::INVALID_CLASS);

    return mc;
}


CIMPLE_NAMESPACE_END

extern "C" CIMPLE_EXPORT int cimple_openwbem_adapter(
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

    const char* providerName = (char*)arg1;
    cimple::Registration* head = (cimple::Registration*)arg2;

    // Create the adapter object:

    for (cimple::Registration* r = head; r; r = r->next)
    {
        if (strcasecmp(r->provider_name, providerName) == 0)
        {
            cimple::OpenWBEM_Adapter* adapter =
                new cimple::OpenWBEM_Adapter(new cimple::Provider_Handle(r));
            *((OpenWBEM::CppProviderBaseIFC**)arg3) = adapter;
            return 0;
        }
    }

    // Not found!
    return -1;
}


