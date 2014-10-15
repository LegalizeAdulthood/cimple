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

#include "CMPI_Adapter.h"
#include <string.h>
#include <time.h>
#include <cimple/Strings.h>
#include <cimple/config.h>
#include <cimple/Mutex.h>
#include <cimple/Auto_Mutex.h>
#include "Converter.h"
#include "CMPI_Thread_Context.h"

#define STATIC_DATA_MAGIC 0x5DE2B131

#define FL __FILE__, __LINE__

// Export cimple_cmpi_adapter() only for shared library.
#ifdef CIMPLE_STATIC
# define CIMPLE_ADAPTER_LINKAGE CIMPLE_HIDE
#else
# define CIMPLE_ADAPTER_LINKAGE CIMPLE_EXPORT
#endif

CIMPLE_NAMESPACE_BEGIN

static const char* _rc_to_str(CMPIrc rc)
{
    switch (rc)
    {
        case CMPI_RC_OK:
            return "CMPI_RC_OK";
        case CMPI_RC_ERR_FAILED:
            return "CMPI_RC_ERR_FAILED";
        case CMPI_RC_ERR_ACCESS_DENIED:
            return "CMPI_RC_ERR_ACCESS_DENIED";
        case CMPI_RC_ERR_INVALID_NAMESPACE:
            return "CMPI_RC_ERR_INVALID_NAMESPACE";
        case CMPI_RC_ERR_INVALID_PARAMETER:
            return "CMPI_RC_ERR_INVALID_PARAMETER";
        case CMPI_RC_ERR_INVALID_CLASS:
            return "CMPI_RC_ERR_INVALID_CLASS";
        case CMPI_RC_ERR_NOT_FOUND:
            return "CMPI_RC_ERR_NOT_FOUND";
        case CMPI_RC_ERR_NOT_SUPPORTED:
            return "CMPI_RC_ERR_NOT_SUPPORTED";
        case CMPI_RC_ERR_CLASS_HAS_CHILDREN:
            return "CMPI_RC_ERR_CLASS_HAS_CHILDREN";
        case CMPI_RC_ERR_CLASS_HAS_INSTANCES:
            return "CMPI_RC_ERR_CLASS_HAS_INSTANCES";
        case CMPI_RC_ERR_INVALID_SUPERCLASS:
            return "CMPI_RC_ERR_INVALID_SUPERCLASS";
        case CMPI_RC_ERR_ALREADY_EXISTS:
            return "CMPI_RC_ERR_ALREADY_EXISTS";
        case CMPI_RC_ERR_NO_SUCH_PROPERTY:
            return "CMPI_RC_ERR_NO_SUCH_PROPERTY";
        case CMPI_RC_ERR_TYPE_MISMATCH:
            return "CMPI_RC_ERR_TYPE_MISMATCH";
        case CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED:
            return "CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED";
        case CMPI_RC_ERR_INVALID_QUERY:
            return "CMPI_RC_ERR_INVALID_QUERY";
        case CMPI_RC_ERR_METHOD_NOT_AVAILABLE:
            return "CMPI_RC_ERR_METHOD_NOT_AVAILABLE";
        case CMPI_RC_ERR_METHOD_NOT_FOUND:
            return "CMPI_RC_ERR_METHOD_NOT_FOUND";
        case CMPI_RC_DO_NOT_UNLOAD:
            return "CMPI_RC_DO_NOT_UNLOAD";
        case CMPI_RC_NEVER_UNLOAD:
            return "CMPI_RC_NEVER_UNLOAD";
        case CMPI_RC_ERR_INVALID_HANDLE:
            return "CMPI_RC_ERR_INVALID_HANDLE";
        case CMPI_RC_ERR_INVALID_DATA_TYPE:
            return "CMPI_RC_ERR_INVALID_DATA_TYPE";
        case CMPI_RC_ERROR_SYSTEM:
            return "CMPI_RC_ERROR_SYSTEM";
        case CMPI_RC_ERROR:
            return "CMPI_RC_ERROR";
        default:
            return "CMPI_RC_ERR_FAILED";
    }

    return NULL;
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::CMPI_Adapter()
//
//------------------------------------------------------------------------------

CMPI_Adapter::CMPI_Adapter(
    const CMPIBroker* broker_, 
    const CMPIContext* context,
    const char* prov_name, 
    const Registration* registration,
    CMPI_Static_Data* static_data)
    :
    Provider_Handle(registration),
    sd(static_data),
    allow_unload(true),
    indications_enabled(false)
{
    ent(FL, "CMPI_Adapter");

    CMPI_Thread_Context_Pusher pusher(broker_, context, this);

    // Set magic number.

    sd->magic = STATIC_DATA_MAGIC;

    // Save adapter pointer into static data.

    sd->adapter = this;

    // Instance FT:

    sd->instance_ft.ftVersion = 100;
    sd->instance_ft.miVersion = 100;

    strlcpy(sd->inst_mi_name, "instance", sizeof(sd->inst_mi_name));
    strlcat(sd->inst_mi_name, prov_name, sizeof(sd->inst_mi_name));
    sd->instance_ft.miName = sd->inst_mi_name;

    sd->instance_ft.cleanup = CMPI_Adapter::instanceCleanup;
    sd->instance_ft.enumerateInstanceNames = CMPI_Adapter::enumInstanceNames;
    sd->instance_ft.enumerateInstances = CMPI_Adapter::enumInstances;
    sd->instance_ft.getInstance = CMPI_Adapter::getInstance;
    sd->instance_ft.createInstance = CMPI_Adapter::createInstance;
    sd->instance_ft.modifyInstance = CMPI_Adapter::modifyInstance;
    sd->instance_ft.deleteInstance = CMPI_Adapter::deleteInstance;
    sd->instance_ft.execQuery = CMPI_Adapter::execQuery;

    // Method FT:

    sd->method_ft.ftVersion = 100;
    sd->method_ft.miVersion = 100;

    strlcpy(sd->meth_mi_name, "method", sizeof(sd->meth_mi_name));
    strlcat(sd->meth_mi_name, prov_name, sizeof(sd->meth_mi_name));
    sd->instance_ft.miName = sd->meth_mi_name;

    sd->method_ft.cleanup = CMPI_Adapter::methodCleanup;
    sd->method_ft.invokeMethod = CMPI_Adapter::invokeMethod;

    // Indication FT:

    sd->indication_ft.ftVersion = 100;
    sd->indication_ft.miVersion = 100;

    strlcpy(sd->indic_mi_name, "indication", sizeof(sd->indic_mi_name));
    strlcat(sd->indic_mi_name, prov_name, sizeof(sd->indic_mi_name));
    sd->instance_ft.miName = sd->indic_mi_name;

    sd->indication_ft.cleanup = CMPI_Adapter::indicationCleanup;
    sd->indication_ft.authorizeFilter = CMPI_Adapter::authorizeFilter;
    sd->indication_ft.mustPoll = CMPI_Adapter::mustPoll;
    sd->indication_ft.activateFilter = CMPI_Adapter::activateFilter;
    sd->indication_ft.deActivateFilter = CMPI_Adapter::deactivateFilter;

    /*
     * If the following two lines fail to compile, try reconfiguring with the
     * --cmpi-void-return-bug option. That is:
     *
     *     ./configure --cmpi-void-return-bug
     *
     * If you already configured with that option and still have the compiler
     * error, then try configuring WITHOUT it.
     *
     */
    sd->indication_ft.enableIndications = CMPI_Adapter::enableIndications;
    sd->indication_ft.disableIndications = CMPI_Adapter::disableIndications;

    // Assocication FT:

    sd->association_ft.ftVersion = 100;
    const CMPISint32* miVersionPtr = &sd->association_ft.miVersion;
    *((CMPISint32*)miVersionPtr) = 100;

    strlcpy(sd->assoc_mi_name, "association", sizeof(sd->assoc_mi_name));
    strlcat(sd->assoc_mi_name, prov_name, sizeof(sd->assoc_mi_name));
    sd->instance_ft.miName = sd->assoc_mi_name;

    sd->association_ft.cleanup = CMPI_Adapter::associationCleanup;
    sd->association_ft.associators = CMPI_Adapter::associators;
    sd->association_ft.associatorNames = CMPI_Adapter::associatorNames;
    sd->association_ft.references = CMPI_Adapter::references;
    sd->association_ft.referenceNames = CMPI_Adapter::referenceNames;

    // Save broker.

    broker = broker_;

    // This provider has been loaded one time so far.

    load_count = 1;

    // Invoke provider load() method.

    load();

    // Save meta-class:

    get_meta_class(mc);

    ret(FL, "CMPI_Adapter");
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::~CMPI_Adapter()
//
//------------------------------------------------------------------------------

CMPI_Adapter::~CMPI_Adapter()
{
    ent(FL, "~CMPI_Adapter");

    CIMPLE_ASSERT(sd->adapter == this);
    CIMPLE_ASSERT(sd->magic == STATIC_DATA_MAGIC);

    sd->magic = 0xDDDDDDDD;
    sd->adapter = 0;

    ret(FL, "~CMPI_Adapter");
}

//------------------------------------------------------------------------------
//
// _adapter()
//
//------------------------------------------------------------------------------

template<class MI>
static CMPI_Adapter* _adapter(MI* mi)
{
    CIMPLE_ASSERT(mi != 0);
    CMPI_Static_Data* sd = (CMPI_Static_Data*)mi->hdl;
    CIMPLE_ASSERT(sd != 0);
    CIMPLE_ASSERT(sd->magic == STATIC_DATA_MAGIC);
    CIMPLE_ASSERT(sd->adapter);
    CIMPLE_ASSERT(sd->adapter->magic);

    return sd->adapter;
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::instanceCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::instanceCleanup(
    CMPIInstanceMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    CMPI_Adapter* adapter = _adapter(mi);

    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    return cleanup(adapter, context, terminating);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::enumInstanceNames()
//
//------------------------------------------------------------------------------

namespace enum_instance_names
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIResult* result;
        const char* name_space;
        CMPIrc rc;
    };

    static bool _proc(
        Instance* inst,
        Enum_Instances_Status status,
        void* client_data)
    {
        Data* data = (Data*)client_data;

        if (!inst)
            return false;

        Ref<Instance> cimple_inst_d(inst);

        // Ignore if an error was already encountered.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Convert to a CMPI object path and deliver:

        CMPIObjectPath* cop = 0;

        data->rc = make_cmpi_object_path(
            data->broker,
            inst,
            data->name_space,
            cop);

        if (data->rc != CMPI_RC_OK)
            return false;

        CMReturnObjectPath(data->result, cop);
        return true;
    }
}

CMPIStatus CMPI_Adapter::enumInstanceNames(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "enumInstanceNames");

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "enumInstanceNames", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "enumInstanceNames", rc);
        CMReturn(rc);
    }

    Ref<Instance> cimple_ref_d(cimple_ref);

    // Nullify non-key properties (this is a reference).

    nullify_non_keys(cimple_ref);

    // Invoke provider:

    const char* ns = name_space(cop);

    enum_instance_names::Data data = 
        { adapter->broker, result, ns, CMPI_RC_OK };

    Enum_Instances_Status status = 
        adapter->enum_instances(cimple_ref, enum_instance_names::_proc, &data); 

    switch (status)
    {
        case ENUM_INSTANCES_OK:
        {
            CMReturnDone(result);
            adapter->ret(FL, "enumInstanceNames", CMPI_RC_OK);
            CMReturn(CMPI_RC_OK);
        }

        case ENUM_INSTANCES_FAILED:
        {
            adapter->ret(FL, "enumInstanceNames", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);
        }
    }


    // Unreachable!
    adapter->ret(FL, "enumInstanceNames", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::enumInstances()
//
//------------------------------------------------------------------------------

namespace enum_instances
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIResult* result;
        const CMPIObjectPath* cop;
        const char* const* properties;
        CMPIrc rc;
    };

    static bool _proc(
        Instance* inst,
        Enum_Instances_Status status,
        void* client_data)
    {
        Data* data = (Data*)client_data;
        Ref<Instance> destroyer(inst);

        if (!inst)
            return false;

        // Ignore if an error was already encountered.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Filter out unwanted properties.

        filter_properties(inst, data->properties);

        // Convert to a CMPI instance and deliver:

        CMPIInstance* ci = 0;

        data->rc = make_cmpi_instance(
            data->broker, 
            inst, 
            name_space(data->cop), 
            data->cop, 
            ci); 

        if (data->rc != CMPI_RC_OK)
            return false;

        CMReturnInstance(data->result, ci);
        return true;
    }
}

CMPIStatus CMPI_Adapter::enumInstances(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char** properties)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "enumInstances");

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "enumInstances", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "enumInstances", rc);
        CMReturn(rc);
    }

    // Filter properties:

    if (properties)
        filter_properties(cimple_ref, properties);

    // Invoke provider:

    enum_instances::Data data = 
        { adapter->broker, result, cop, properties, CMPI_RC_OK };

    Enum_Instances_Status status = 
        adapter->enum_instances(cimple_ref, enum_instances::_proc, &data); 

    switch (status)
    {
        case ENUM_INSTANCES_OK:
            break;

        case ENUM_INSTANCES_FAILED:
        {
            adapter->ret(FL, "enumInstances", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);
        }
    }

    CMReturnDone(result);

    adapter->ret(FL, "enumInstances", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::getInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::getInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char** properties)
{
    CMPI_Adapter* adapter = _adapter(mi);
    const CMPIBroker* broker = adapter->broker;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "getInstance");

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "getInstance", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "getInstance", rc);
        CMReturn(rc);
    }

    // Ask for all properties.

    de_nullify_properties(cimple_ref);

    // Filter properties:

    if (properties)
        filter_properties(cimple_ref, properties);

    // Invoke provider:

    Instance* inst = 0;

    Get_Instance_Status status = 
        adapter->get_instance(cimple_ref, inst);

    Ref<Instance> cimple_inst_d(inst);

    switch (status)
    {
        case GET_INSTANCE_OK:
            break;

        case GET_INSTANCE_NOT_FOUND:
            adapter->ret(FL, "getInstance", CMPI_RC_ERR_NOT_FOUND);
            CMReturn(CMPI_RC_ERR_NOT_FOUND);

        case GET_INSTANCE_UNSUPPORTED:
            adapter->ret(FL, "getInstance", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Create CMPI instance:

    CMPIInstance* ci;

    rc = make_cmpi_instance(
        adapter->broker, inst, name_space(cop), cop, ci); 

    if (rc == CMPI_RC_OK)
    {
        CMReturnInstance(result, ci);
        CMReturnDone(result);
        adapter->ret(FL, "getInstance", CMPI_RC_OK);
        CMReturn(CMPI_RC_OK);
    }

    adapter->ret(FL, "getInstance", rc);
    CMReturn(rc);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::createInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::createInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const CMPIInstance* ci)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "createInstance");

    // Create CIMPLE instance:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "createInstance", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    Instance* inst = 0;

    CMPIrc rc = make_cimple_instance(adapter->broker, mc, cop, ci, inst);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "createInstance", rc);
        CMReturn(rc);
    }

    Ref<Instance> cmpi_inst_d(inst);

    // Invoke the provider:

    Create_Instance_Status status =
        adapter->create_instance(inst);

    switch (status)
    {
        case CREATE_INSTANCE_OK:
        {
            CMPIObjectPath* cop_out;

            CMPIrc rc = make_cmpi_object_path(adapter->broker, inst, 
                name_space(cop), cop_out);

            if (rc != CMPI_RC_OK)
            {
                adapter->ret(FL, "createInstance", rc);
                CMReturn(rc);
            }

            CMReturnObjectPath(result, cop_out);
            CMReturnDone(result);
            adapter->ret(FL, "createInstance", CMPI_RC_OK);
            CMReturn(CMPI_RC_OK);
        }

        case CREATE_INSTANCE_DUPLICATE:
            adapter->ret(FL, "createInstance", CMPI_RC_ERR_ALREADY_EXISTS);
            CMReturn(CMPI_RC_ERR_ALREADY_EXISTS);

        case CREATE_INSTANCE_UNSUPPORTED:
            adapter->ret(FL, "createInstance", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    adapter->ret(FL, "createInstance", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::modifyInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::modifyInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const CMPIInstance* ci,
    const char** properties)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "modifyInstance");

    // Create CIMPLE instance:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "modifyInstance", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    Instance* inst = 0;
    CMPIrc rc = make_cimple_instance(adapter->broker, mc, cop, ci, inst);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "modifyInstance", rc);
        CMReturn(rc);
    }

    Ref<Instance> cmpi_inst_d(inst);

    // Create model.

    Instance* model = clone(inst);
    Ref<Instance> model_d(model);
    filter_properties(model, properties);

    // Invoke the provider:

    Modify_Instance_Status status = adapter->modify_instance(
        model, inst);

    switch (status)
    {
        case MODIFY_INSTANCE_OK:
            CMReturnObjectPath(result, cop);
            CMReturnDone(result);
            adapter->ret(FL, "modifyInstance", CMPI_RC_OK);
            CMReturn(CMPI_RC_OK);

        case MODIFY_INSTANCE_NOT_FOUND:
            adapter->ret(FL, "modifyInstance", CMPI_RC_ERR_NOT_FOUND);
            CMReturn(CMPI_RC_ERR_NOT_FOUND);

        case MODIFY_INSTANCE_UNSUPPORTED:
            adapter->ret(FL, "modifyInstance", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    adapter->ret(FL, "modifyInstance", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::deleteInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::deleteInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "deleteInstance");

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "deleteInstance", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);

    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "deleteInstance", rc);
        CMReturn(rc);
    }

    // Invoke provider:

    Delete_Instance_Status status = 
        adapter->delete_instance(cimple_ref);

    switch (status)
    {
        case DELETE_INSTANCE_OK:
            break;

        case DELETE_INSTANCE_NOT_FOUND:
            adapter->ret(FL, "deleteInstance", CMPI_RC_ERR_NOT_FOUND);
            CMReturn(CMPI_RC_ERR_NOT_FOUND);

        case DELETE_INSTANCE_UNSUPPORTED:
            adapter->ret(FL, "deleteInstance", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    CMReturnDone(result);
    adapter->ret(FL, "deleteInstance", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::execQuery()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::execQuery(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const char* lang, 
    const char* query)
{
    CMPI_Adapter* adapter = _adapter(mi);

    adapter->ent(FL, "execQuery");

    adapter->ret(FL, "execQuery", CMPI_RC_ERR_NOT_SUPPORTED);
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::methodCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::methodCleanup(
    CMPIMethodMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);

    return cleanup(adapter, context, terminating);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::invokeMethod()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::invokeMethod(
    CMPIMethodMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char* method, 
    const CMPIArgs* in,
    CMPIArgs* out)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "invokeMethod");

    // Find CIMPLE method object:

    const Meta_Class* mc = adapter->find_model_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "invokeMethod", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    const Meta_Method* mm = find_method(mc, method);

    if (!mm)
    {
        adapter->ret(FL, "invokeMethod", CMPI_RC_ERR_METHOD_NOT_FOUND);
        CMReturn(CMPI_RC_ERR_METHOD_NOT_FOUND);
    }

    // Validate the object path:

    const char* cn = class_name(cop);

    if (!cn || strcasecmp(cn, mm->name) == 0)
    {
        adapter->ret(FL, "invokeMethod", CMPI_RC_ERR_INVALID_CLASS);
        CMReturn(CMPI_RC_ERR_INVALID_CLASS);
    }

    if (CMGetKeyCount(cop, NULL) > 0 && (mm->flags & CIMPLE_FLAG_STATIC))
    {
        adapter->ret(FL, "invokeMethod", CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "invokeMethod", rc);
        CMReturn(rc);
    }

    Ref<Instance> cimple_ref_d(cimple_ref);

    // Create the method:

    Instance* cimple_meth = 0;
    rc = make_cimple_method(0, mc, mm, cop, in, adapter, cimple_meth);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "invokeMethod", rc);
        CMReturn(rc);
    }

    Ref<Instance> cimple_meth_d(cimple_meth);

    // Invoke the provider:

    Invoke_Method_Status status = adapter->invoke_method(
        cimple_ref, cimple_meth);

    switch (status)
    {
        case INVOKE_METHOD_OK:
            break;

        case INVOKE_METHOD_FAILED:
            adapter->ret(FL, "invokeMethod", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);

        case INVOKE_METHOD_UNSUPPORTED:
            adapter->ret(FL, "invokeMethod", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    // Convert to CMPI out arguments:

    CMPIValue return_value;
    CMPIType return_type;
    const char* ns = name_space(cop);

    rc = make_cmpi_method(
        adapter->broker, ns, cimple_meth, out, return_value, return_type);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "invokeMethod", rc);
        CMReturn(rc);
    }

    // Append CMPI out args:

    CMReturnData(result, &return_value, return_type);
    CMReturnDone(result);
    adapter->ret(FL, "invokeMethod", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::indicationCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::indicationCleanup(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);

    adapter->ent(FL, "indicationCleanup");

    return cleanup(adapter, context, terminating);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::authorizeFilter()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::authorizeFilter(
     CMPIIndicationMI* mi, 
     const CMPIContext* context,
     const CMPISelectExp* select_expr, 
     const char* name_space, 
     const CMPIObjectPath* cmpi_object_path,
     const char* user_name)
{
    CMPI_Adapter* adapter = _adapter(mi);

    adapter->ent(FL, "authorizeFilter");

    adapter->ret(FL, "authorizeFilter", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::mustPoll()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::mustPoll(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    const CMPISelectExp* filter, 
    const char* indication_type,
    const CMPIObjectPath* class_path)
{
    CMPI_Adapter* adapter = _adapter(mi);

    adapter->ent(FL, "mustPoll");

    adapter->ret(FL, "mustPoll", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::activateFilter()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::activateFilter(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    const CMPISelectExp* select_expr, 
    const char* indication_type,
    const CMPIObjectPath* class_path, 
    CMPIBoolean first)
{
    CMPI_Adapter* adapter = _adapter(mi);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "activateFilter");

    const char* ns = name_space(class_path);

    if (ns)
    {
        // Create entry or update existing entry.

        Name_Space_Entry entry(ns, 1);

        size_t pos = adapter->name_spaces.find(entry);

        if (pos == size_t(-1))
            adapter->name_spaces.append(entry);
        else
            adapter->name_spaces[pos].count++;
    }

    adapter->ret(FL, "activateFilter", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::deactivateFilter()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::deactivateFilter(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    const CMPISelectExp* select_expr, 
    const char* indication_type,
    const CMPIObjectPath* class_path, 
    CMPIBoolean last)
{
    CMPI_Adapter* adapter = _adapter(mi);
    Auto_Mutex auto_lock(adapter->lock);
    const char* ns = name_space(class_path);

    adapter->ent(FL, "deactivateFilter");

    if (ns)
    {
        // Create entry or update existing entry.

        Name_Space_Entry entry(ns, 1);

        size_t pos = adapter->name_spaces.find(entry);

        if (pos != size_t(-1))
        {
            if (adapter->name_spaces[pos].count == 1)
                adapter->name_spaces.remove(pos);
            else
                adapter->name_spaces[pos].count--;
        }
    }

    adapter->ret(FL, "deactivateFilter", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::enableIndications()
//
//------------------------------------------------------------------------------

static bool _indication_proc(Instance* inst, void* client_data)
{
    // This function is called by the CIMPLE Indication_Handler<> in order to 
    // deliver a single indication.

    CMPI_Adapter* adapter = (CMPI_Adapter*)client_data;
    Auto_Mutex auto_lock(adapter->lock);

    // If this is the final call, just return.

    if (inst == 0)
        return false;

    Ref<Instance> cimple_inst_d(inst);

    // Do once for each CIM namespace:

    for (size_t i = 0; i < adapter->name_spaces.size(); i++)
    {
        String name_space = adapter->name_spaces[i].name;

        // Convert CIMPLE instance to CMPI instance:

        CMPIInstance* ci = 0;

        CMPIrc rc = make_cmpi_instance(adapter->broker, 
            inst, name_space.c_str(), 0, ci); 

        // Deliver the indication (we cannot do anything about failures).

        if (rc == CMPI_RC_OK)
        {
            // ATTN: get thread context for this thread somehow!

            // Deliver the indication:

            CMPI_Thread_Context* thread_context = 
                (CMPI_Thread_Context*)Thread_Context::top();
            assert(thread_context != 0);

            CBDeliverIndication(
                thread_context->cmpi_broker(),
                thread_context->cmpi_context(),
                name_space.c_str(),
                ci);
        }
    }

    // Keep them coming!
    return true;
}

FIX_RETURN_TYPE CMPI_Adapter::enableIndications(
    CMPIIndicationMI* mi, 
    const CMPIContext* context)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "enableIndications");

    // Ignore request if indications already enabled.

    if (adapter->indications_enabled)
    {
        adapter->ret(FL, "enableIndications", CMPI_RC_OK);
        FIX_RETURN(CMPI_RC_OK);
    }

    adapter->indications_enabled = true;

    // Invoke the provider:

    Enable_Indications_Status status = adapter->enable_indications(
        _indication_proc, adapter);

    switch (status)
    {
        case ENABLE_INDICATIONS_OK:
            adapter->ret(FL, "enableIndications", CMPI_RC_OK);
            FIX_RETURN(CMPI_RC_OK);
            break;

        case ENABLE_INDICATIONS_FAILED:
            adapter->ret(FL, "enableIndications", CMPI_RC_ERR_FAILED);
            FIX_RETURN(CMPI_RC_ERR_FAILED);
            break;
    }

    // Unreachable!
    adapter->ret(FL, "enableIndications", CMPI_RC_OK);
    FIX_RETURN(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::disableIndications()
//
//------------------------------------------------------------------------------

FIX_RETURN_TYPE CMPI_Adapter::disableIndications(
    CMPIIndicationMI* mi, 
    const CMPIContext* context)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "disableIndications");

    // Ignore if indications are not enabled.

    if (!adapter->indications_enabled)
        FIX_RETURN(CMPI_RC_OK);

    // Invoke the provider:

    Disable_Indications_Status status = adapter->disable_indications();

    adapter->indications_enabled = false;

    switch (status)
    {
        case DISABLE_INDICATIONS_OK:
            adapter->ret(FL, "disableIndications", CMPI_RC_OK);
            FIX_RETURN(CMPI_RC_OK);
            break;

        case DISABLE_INDICATIONS_FAILED:
            adapter->ret(FL, "disableIndications", CMPI_RC_ERR_FAILED);
            FIX_RETURN(CMPI_RC_ERR_FAILED);
            break;
    }

    // Unreachable!
    adapter->ret(FL, "disableIndications", CMPI_RC_OK);
    FIX_RETURN(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::associationCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::associationCleanup(
    CMPIAssociationMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    CMPI_Adapter* adapter = _adapter(mi);

    adapter->ent(FL, "associationCleanup");

    return cleanup(adapter, context, terminating);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::associators()
//
//------------------------------------------------------------------------------

namespace associators1
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIContext* context;
        const CMPIResult* result;
        const char* name_space;
        const char** properties;
        CMPIrc rc;
    };

    static bool _proc(
        const Instance* inst, 
        Enum_Associators_Status status, 
        void* client_data)
    {
        Data* data = (Data*)client_data;

        if (!inst)
            return false;

        // Ignore if an error was already encountered.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Convert to a CMPI instance.

        CMPIInstance* ci = 0;

        data->rc = make_cmpi_instance(
            data->broker, 
            inst, 
            data->name_space,
            0,
            ci); 

        if (data->rc != CMPI_RC_OK)
        {
            data->rc = CMPI_RC_ERR_FAILED;
            return false;
        }

        // Deliver instance to requestor:

        CMReturnInstance(data->result, ci);

        return true;
    }
}

namespace associators2
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIContext* context;
        const CMPIResult* result;
        const char* name_space;
        const char** properties;
        CMPIrc rc;
    };

    static bool _proc(
        const Instance* inst, 
        Enum_Associator_Names_Status status, 
        void* client_data)
    {
        Data* data = (Data*)client_data;

        if (!inst)
            return false;

        // Ignore if an error was already encountered.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Convert to a CMPI object path and deliver:

        CMPIObjectPath* cop = 0;

        data->rc = make_cmpi_object_path(
            data->broker,
            inst,
            data->name_space,
            cop);

        // Now use the CMPI broker to get the full instance.

        CMPIInstance* ci = CBGetInstance(
            data->broker, data->context, cop, data->properties, NULL);

        if (!ci)
        {
            data->rc = CMPI_RC_ERR_FAILED;
            return false;
        }

        // Deliver instance to requestor:

        CMReturnInstance(data->result, ci);

        return true;
    }
}

CMPIStatus CMPI_Adapter::associators( 
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char* assoc_class_, 
    const char* result_class_,
    const char* role_, 
    const char* result_role_, 
    const char** properties)
{
    const char* assoc_class = assoc_class_ ? assoc_class_ : "";
    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";
    const char* result_role = result_role_ ? result_role_ : "";

    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "associators");

    CIMPLE_ASSERT(strcasecmp(assoc_class, adapter->mc->name) == 0);

    // Lookup meta class for cop (not the same as the provider class).

    const Meta_Class* mc = adapter->find_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "associators", CMPI_RC_ERR_INVALID_CLASS);
        CMReturn(CMPI_RC_ERR_INVALID_CLASS);
    }

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "associators", rc);
        CMReturn(rc);
    }

    // First try enum_associators().
    {
        associators2::Data data = { adapter->broker, 
            context, result, name_space(cop), properties, CMPI_RC_OK };

        Enum_Associators_Status status = adapter->enum_associators(
            cimple_ref,
            result_class,
            role,
            result_role,
            associators1::_proc,
            &data);

        switch (status)
        {
            case ENUM_ASSOCIATORS_OK:
                adapter->ret(FL, "associators", CMPI_RC_OK);
                CMReturn(CMPI_RC_OK);

            case ENUM_ASSOCIATORS_FAILED:
                adapter->ret(FL, "associators", CMPI_RC_ERR_FAILED);
                CMReturn(CMPI_RC_ERR_FAILED);

            case ENUM_ASSOCIATORS_UNSUPPORTED:
                // Fall through to case below.
                break;
        }
    }

    // Next try enum_associator_names().
    {
        associators2::Data data = { adapter->broker, 
            context, result, name_space(cop), properties, CMPI_RC_OK };

        Enum_Associator_Names_Status status = adapter->enum_associator_names(
            cimple_ref,
            result_class,
            role,
            result_role,
            associators2::_proc,
            &data);

        switch (status)
        {
            case ENUM_ASSOCIATOR_NAMES_OK:
                adapter->ret(FL, "associators", CMPI_RC_OK);
                CMReturn(CMPI_RC_OK);

            case ENUM_ASSOCIATOR_NAMES_FAILED:
                adapter->ret(FL, "associators", CMPI_RC_ERR_FAILED);
                CMReturn(CMPI_RC_ERR_FAILED);

            case ENUM_ASSOCIATOR_NAMES_UNSUPPORTED:
                adapter->ret(FL, "associators", CMPI_RC_ERR_NOT_SUPPORTED);
                CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
        }

        adapter->ret(FL, "associators", CMPI_RC_OK);
        CMReturn(CMPI_RC_OK);
    }
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::associatorNames()
//
//------------------------------------------------------------------------------

namespace associator_names
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIContext* context;
        const CMPIResult* result;
        const char* name_space;
        CMPIrc rc;
    };

    static bool _proc(
        const Instance* inst, 
        Enum_Associator_Names_Status status,
        void* client_data)
    {
        Data* data = (Data*)client_data;

        if (!inst)
            return false;

        // Ignore if an error was already encountered.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Convert to a CMPI object path and deliver:

        CMPIObjectPath* cop = 0;

        data->rc = make_cmpi_object_path(
            data->broker,
            inst,
            data->name_space,
            cop);

        if (data->rc == CMPI_RC_OK)
            CMReturnObjectPath(data->result, cop);

        return true;
    }
}

CMPIStatus CMPI_Adapter::associatorNames(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char* assoc_class_, 
    const char* result_class_,
    const char* role_, 
    const char* result_role_)
{
    const char* assoc_class = assoc_class_ ? assoc_class_ : "";
    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";
    const char* result_role = result_role_ ? result_role_ : "";

    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "associatorNames");

    CIMPLE_ASSERT(strcasecmp(assoc_class, adapter->mc->name) == 0);

    // Lookup meta class for cop (not the same as the provider class).

    const Meta_Class* mc = adapter->find_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "associatorNames", CMPI_RC_ERR_INVALID_CLASS);
        CMReturn(CMPI_RC_ERR_INVALID_CLASS);
    }

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "associatorNames", rc);
        CMReturn(rc);
    }

    // Invoke the provider:

    associator_names::Data data = 
        { adapter->broker, context, result, name_space(cop), CMPI_RC_OK };

    Enum_Associator_Names_Status status = adapter->enum_associator_names(
        cimple_ref,
        result_class,
        role,
        result_role,
        associator_names::_proc,
        &data);

    switch (status)
    {
        case ENUM_ASSOCIATOR_NAMES_OK:
            adapter->ret(FL, "associatorNames", CMPI_RC_OK);
            CMReturn(CMPI_RC_OK);

        case ENUM_ASSOCIATOR_NAMES_FAILED:
            adapter->ret(FL, "associatorNames", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);

        case ENUM_ASSOCIATOR_NAMES_UNSUPPORTED:
            adapter->ret(FL, "associatorNames", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    adapter->ret(FL, "associatorNames", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::references()
//
//------------------------------------------------------------------------------

namespace references
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIContext* context;
        const CMPIResult* result;
        const char* name_space;
        const char** properties;
        CMPIrc rc;
    };

    static bool _proc(
        Instance* inst, 
        Enum_References_Status status,
        void* client_data)
    {
        Data* data = (Data*)client_data;

        // Ignore the final call.

        if (!inst)
            return false;

        Ref<Instance> cimple_inst_d(inst);

        // Ignore errors on prior call.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Filter the properties.

        filter_properties(inst, data->properties);

        // Convert to CMPI instance.

        CMPIInstance* ci = 0;

        data->rc = make_cmpi_instance(
            data->broker, inst, data->name_space, 0, ci);

        if (data->rc != CMPI_RC_OK)
            return false;

        // Deliver the instance.

        CMReturnInstance(data->result, ci);

        return true;
    }
}

CMPIStatus CMPI_Adapter::references(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char* result_class_, 
    const char* role_,
    const char** properties)
{
    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";

    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "references");

    // Lookup meta class for cop (not the same as the provider class).

    const Meta_Class* mc = adapter->find_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "references", CMPI_RC_ERR_INVALID_CLASS);
        CMReturn(CMPI_RC_ERR_INVALID_CLASS);
    }

    CIMPLE_ASSERT(strcasecmp(result_class, adapter->mc->name) == 0);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "references", rc);
        CMReturn(rc);
    }

    // Create a model.

    const Meta_Class* model_meta_class = 0;
    adapter->get_meta_class(model_meta_class);

    Instance* cimple_model = cimple::create(model_meta_class);

    // Invoke the provider:

    references::Data data = { adapter->broker, 
        context, result, name_space(cop), properties, CMPI_RC_OK };

    Enum_References_Status status = adapter->enum_references(
        cimple_ref, cimple_model, role, references::_proc, &data);

    destroy(cimple_model);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
            adapter->ret(FL, "references", CMPI_RC_OK);
            CMReturn(CMPI_RC_OK);

        case ENUM_REFERENCES_FAILED:
            adapter->ret(FL, "references", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);

        case ENUM_REFERENCES_UNSUPPORTED:
            adapter->ret(FL, "references", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    // Unreachable!
    adapter->ret(FL, "references", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::referenceNames()
//
//------------------------------------------------------------------------------

namespace reference_names
{
    struct Data
    {
        const CMPIBroker* broker;
        const CMPIContext* context;
        const CMPIResult* result;
        const char* name_space;
        CMPIrc rc;
    };

    static bool _proc(
        Instance* inst, 
        Enum_References_Status status,
        void* client_data)
    {
        Data* data = (Data*)client_data;

        // Ignore the final call.

        if (!inst)
            return false;

        Ref<Instance> cimple_inst_d(inst);

        // Ignore errors on prior call.

        if (data->rc != CMPI_RC_OK)
            return false;

        // Filter out non-key properties:

        nullify_non_keys(inst);

        // Convert to CMPI object path:

        CMPIObjectPath* cop = 0;

        data->rc = make_cmpi_object_path(
            data->broker, inst, data->name_space, cop);

        if (data->rc != CMPI_RC_OK)
            return false;

        // Deliver the instance.

        CMReturnObjectPath(data->result, cop);

        return true;
    }
}

CMPIStatus CMPI_Adapter::referenceNames(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cop, 
    const char* result_class_, 
    const char* role_)
{
    CMPI_Adapter* adapter = _adapter(mi);
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context, adapter);
    Auto_Mutex auto_lock(adapter->lock);

    adapter->ent(FL, "referenceNames");

    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";

    // Lookup meta class for cop (not the same as the provider class).

    const Meta_Class* mc = adapter->find_meta_class(class_name(cop));

    if (!mc)
    {
        adapter->ret(FL, "referenceNames", CMPI_RC_ERR_INVALID_CLASS);
        CMReturn(CMPI_RC_ERR_INVALID_CLASS);
    }

    CIMPLE_ASSERT(strcasecmp(result_class, adapter->mc->name) == 0);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(0, mc, cop, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
    {
        adapter->ret(FL, "referenceNames", rc);
        CMReturn(rc);
    }

    // Create a model.

    const Meta_Class* model_meta_class = 0;
    adapter->get_meta_class(model_meta_class);

    Instance* cimple_model = cimple::create(model_meta_class);
    nullify_non_keys(cimple_model);

    // Invoke the provider:

    reference_names::Data data = { 
        adapter->broker, context, result, name_space(cop), CMPI_RC_OK };

    Enum_References_Status status = adapter->enum_references(
        cimple_ref, cimple_model, role, reference_names::_proc, &data);

    destroy(cimple_model);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
            adapter->ret(FL, "referenceNames", CMPI_RC_OK);
            CMReturn(CMPI_RC_OK);

        case ENUM_REFERENCES_FAILED:
            adapter->ret(FL, "referenceNames", CMPI_RC_ERR_FAILED);
            CMReturn(CMPI_RC_ERR_FAILED);

        case ENUM_REFERENCES_UNSUPPORTED:
            adapter->ret(FL, "referenceNames", CMPI_RC_ERR_NOT_SUPPORTED);
            CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    // Unreachable!
    adapter->ret(FL, "referenceNames", CMPI_RC_OK);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::cleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::cleanup(
    CMPI_Adapter* adapter, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    adapter->ent(FL, "cleanup");

    if (!terminating && !adapter->allow_unload)
    {
        adapter->ret(FL, "cleanup", CMPI_RC_DO_NOT_UNLOAD);
        CMReturn(CMPI_RC_DO_NOT_UNLOAD);
    }

    if (adapter->load_count == 1)
    {
        adapter->unload();
        adapter->ret(FL, "cleanup", CMPI_RC_OK);
        delete adapter;
    }
    else
    {
        adapter->load_count--;
        adapter->ret(FL, "cleanup", CMPI_RC_OK);
        CMReturn(CMPI_RC_OK);
    }

    // Unreachable!
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::find_meta_class()
//
//------------------------------------------------------------------------------

const Meta_Class* CMPI_Adapter::find_meta_class(const char* class_name)
{
    const Meta_Repository* meta_repository;
    get_repository(meta_repository);

    return cimple::find_meta_class(meta_repository, class_name);
}

CIMPLE_NAMESPACE_END

using namespace cimple;

extern "C" CIMPLE_ADAPTER_LINKAGE int cimple_cmpi_adapter(
    void* arg0, /* provider-interface */
    void* arg1, /* static-data */
    void* arg2, /* registration */
    void* arg3, /* broker */
    void* arg4, /* context */
    void* arg5, /* prov_name */
    void* arg6, /* mi-type */
    void* arg7) /* mi */
{
    // Extract parameters:

    CMPI_Static_Data* sd = ((CMPI_Static_Data*)arg1);
    const Registration* registration = (const Registration*)arg2;
    const CMPIBroker* broker = (const CMPIBroker*)arg3;
    const CMPIContext* context = (const CMPIContext*)arg4;
    const char* prov_name = (const char*)arg5;
    long mi_type = (long)arg6;

    // Be sure static data buffer is small enough.

    CIMPLE_ASSERT(sizeof(CMPI_Static_Data) <= sizeof(__CMPI_Static_Data));

    // Create adapter:

    if (sd->adapter)
    {
        sd->adapter->load_count++;
    }
    else
    {
        sd->adapter = new CMPI_Adapter(
            broker, context, prov_name, registration, sd);
    }

    sd->adapter->ent(FL, "cimple_cmpi_adapter");

    // Create management interface:

    switch (mi_type)
    {
        case 'I': /* instance provider */
        {
            CMPIInstanceMI tmp = {((void*)sd), &sd->instance_ft};
            memcpy(&sd->instance_mi, &tmp, sizeof(tmp));
            *((CMPIInstanceMI**)arg7) = &sd->instance_mi;
            break;
        }

        case 'M': /* method provider */
        {
            CMPIMethodMI tmp = {((void*)sd), &sd->method_ft};
            memcpy(&sd->method_mi, &tmp, sizeof(tmp));
            *((CMPIMethodMI**)arg7) = &sd->method_mi;
            break;
        }

        case 'A': /* association provider */
        {
            CMPIAssociationMI tmp = {((void*)sd), &sd->association_ft};
            memcpy(&sd->association_mi, &tmp, sizeof(tmp));
            *((CMPIAssociationMI**)arg7) = &sd->association_mi;
            break;
        }

        case 'N': /* indication provider */
        {
            CMPIIndicationMI tmp = {((void*)sd), &sd->indication_ft};
            memcpy(&sd->indication_mi, &tmp, sizeof(tmp));
            *((CMPIIndicationMI**)arg7) = &sd->indication_mi;
            break;
        }
    }

    // Success!
    sd->adapter->ret(FL, "cimple_cmpi_adapter");
    return 0;
}

const Meta_Class* CMPI_Adapter::find_meta_class_callback(
    const char* class_name, void* client_data)
{
    return ((CMPI_Adapter*)client_data)->find_meta_class(class_name);
}

const Meta_Class* CMPI_Adapter::find_model_meta_class(const char* class_name)
{
    const Meta_Class* mc = find_meta_class(class_name);

    if (!mc)
        return 0;

    if (!is_subclass(mc, mc))
        return 0;

    return mc;
}

void CMPI_Adapter::ent(const char* file, int line, const char* func)
{
    log(LL_DBG, file, line, "enter: %s()", func);
}

void CMPI_Adapter::ret(const char* file, int line, const char* func)
{
    log(LL_DBG, file, line, "return: %s()", func);
}

void CMPI_Adapter::ret(
    const char* file, int line, const char* func, CMPIrc rc)
{
    log(LL_DBG, file, line, "return: %s(): %s", func, _rc_to_str(rc));
}

void CMPI_Adapter::trc(
    const char* file, int line, const char* func, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vlog(LL_DBG, file, line, fmt, ap);
    va_end(ap);
}
