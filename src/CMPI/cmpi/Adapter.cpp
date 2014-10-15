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

#include "Adapter.h"
#include <string.h>
#include <time.h>
#include <cimple/Strings.h>
#include <cimple/RMutex.h>
#include <cimple/Auto_RMutex.h>
#include <cimple/TLS.h>
#include "Converter.h"

#if 0
# define TRACE printf("===== %s(%d): %s()\n", __FILE__, __LINE__, __FUNCTION__)
#else
# define TRACE
#endif

using namespace cimple;

static const char _INDICATIONS_NAMESPACE[] = "root/cimv2";

//------------------------------------------------------------------------------
//
// _context_tls
//
//     This is the thread-local storage for the CMPIContext object.
//
//------------------------------------------------------------------------------

static TLS _context_tls;

//------------------------------------------------------------------------------
//
// _timer()
//
//------------------------------------------------------------------------------

//Removed thread support!
uint64 Adapter::_timer(void* arg)
{
    TRACE;

    // This function is called when the Scheduler's timer proc expires. It
    // invokes the provider's timer() method().

    Adapter* adapter = (Adapter*)arg;
    Auto_RMutex auto_lock(adapter->_lock);

    uint64 timeout = 0;
    Timer_Status status = adapter->timer(timeout);

    switch (status)
    {
        case TIMER_CANCEL:
            return 0;

        case TIMER_RESCHEDULE:
	    // Convert to microseconds.
            return timeout * 1000;
    }

    // Unreachable!
    return 0;
}

//------------------------------------------------------------------------------
//
// _timer_thread_proc()
//
//------------------------------------------------------------------------------

void* Adapter::_timer_thread_proc(void* arg)
{
    TRACE;

    Adapter* adapter = (Adapter*)arg;

    printf("Adapter::_timer_thread_proc()\n");

    CBAttachThread(adapter->broker, adapter->_timer_context);
    _context_tls.set((void*)adapter->_timer_context);

    // ATTN: there is currently no logic to stop this thread.

    while (!adapter->_stop_timer_thread)
        adapter->_sched->dispatch();

    CBDetachThread(adapter->broker, adapter->_timer_context);

    return 0;
}

//------------------------------------------------------------------------------
//
// Adapter::_sched
//
//------------------------------------------------------------------------------

Scheduler* Adapter::_sched = 0;
RMutex Adapter::_sched_lock;

//------------------------------------------------------------------------------
//
// Adapter::Adapter()
//
//------------------------------------------------------------------------------

Adapter::Adapter(
    const CMPIBroker* broker_, 
    const CMPIContext* context,
    const char* provider_name, 
    Provider_Proc proc) :
    Provider_Handle(proc),
    _indications_enabled(false)
{
    TRACE;

    instance_ft.ftVersion = 100;
    instance_ft.miVersion = 100;
    instance_ft.miName = str_printf("instance%s", provider_name);
    instance_ft.cleanup = Adapter::cleanup;
    instance_ft.enumInstanceNames = Adapter::enumInstanceNames;
    instance_ft.enumInstances = Adapter::enumInstances;
    instance_ft.getInstance = Adapter::getInstance;
    instance_ft.createInstance = Adapter::createInstance;
    instance_ft.modifyInstance = Adapter::modifyInstance;
    instance_ft.deleteInstance = Adapter::deleteInstance;
    instance_ft.execQuery = Adapter::execQuery;

    method_ft.ftVersion = 100;
    method_ft.miVersion = 100;
    method_ft.miName = str_printf("method%s", provider_name);
    method_ft.cleanup = Adapter::methodCleanup;
    method_ft.invokeMethod = Adapter::invokeMethod;

    indication_ft.ftVersion = 100;
    indication_ft.miVersion = 100;
    indication_ft.miName = str_printf("indication%s", provider_name);
    indication_ft.cleanup = Adapter::indicationCleanup;
    indication_ft.authorizeFilter = Adapter::authorizeFilter;
    indication_ft.mustPoll = Adapter::mustPoll;
    indication_ft.activateFilter = Adapter::activateFilter;
    indication_ft.deActivateFilter = Adapter::deactivateFilter;
    indication_ft.enableIndications = Adapter::enableIndications;
    indication_ft.disableIndications = Adapter::disableIndications;

    association_ft.ftVersion = 100;
    association_ft.miVersion = 100;
    association_ft.miName = str_printf("association%s", provider_name);
    association_ft.cleanup = Adapter::associationCleanup;
    association_ft.associators = Adapter::associators;
    association_ft.associatorNames = Adapter::associatorNames;
    association_ft.references = Adapter::references;
    association_ft.referenceNames = Adapter::referenceNames;

    broker = broker_;

    load_count = 1;

    // Invoke provider load() method:

    load();

    // Create a scheduler on first invocation.

    if (_sched == 0)
    {
	_sched_lock.lock();

	if (_sched == 0)
	{
	    _sched = new Scheduler;

	    pthread_attr_init(&_timer_thread_attr);
	    pthread_attr_setdetachstate(
		&_timer_thread_attr, PTHREAD_CREATE_DETACHED);
	    pthread_create(&_timer_thread, &_timer_thread_attr, 
		_timer_thread_proc, this);

	    _timer_context = CBPrepareAttachThread(broker, context);
	}

	_sched_lock.unlock();
    }

    // Schedule timer to call the provider's timer() method:

    _timer_id = _sched->add_timer(1, _timer, this);

    // Save meta-class:

    get_meta_class(_mc);
}

//------------------------------------------------------------------------------
//
// Adapter::~Adapter()
//
//------------------------------------------------------------------------------

Adapter::~Adapter()
{
    TRACE;

    free((char*)instance_ft.miName);
    free((char*)method_ft.miName);
    free((char*)indication_ft.miName);

    // Remove timer:

    _sched->remove_timer(_timer_id);

    // Invoke provider unload() method:

    unload();
}

//------------------------------------------------------------------------------
//
// Adapter::cleanup()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::cleanup(
    CMPIInstanceMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    return _cleanup((Adapter*)mi->hdl, context, terminating);
}

//------------------------------------------------------------------------------
//
// Adapter::enumInstanceNames()
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
	Instance* cimple_inst,
	Enum_Instances_Status status,
	void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!cimple_inst)
	    return false;

	Destroyer<Instance> cimple_inst_d(cimple_inst);

	// Ignore if an error was already encountered.

	if (data->rc != CMPI_RC_OK)
	    return false;

	// Convert to a CMPI object path and deliver:

	CMPIObjectPath* cmpi_op = 0;

	data->rc = make_cmpi_object_path(
	    data->broker,
	    cimple_inst,
	    data->name_space,
	    cmpi_op);

	if (data->rc != CMPI_RC_OK)
	    return false;

	CMReturnObjectPath(data->result, cmpi_op);
	return true;
    }
}

CMPIStatus Adapter::enumInstanceNames(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;
    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Destroyer<Instance> cimple_ref_d(cimple_ref);

    // Nullify non-key properties (this is a reference).

    nullify_non_keys(cimple_ref);

    // Invoke provider:

    const char* ns = name_space(cmpi_op);

    enum_instance_names::Data data = 
	{ adapter->broker, result, ns, CMPI_RC_OK };

    Enum_Instances_Status status = 
	adapter->enum_instances(cimple_ref, enum_instance_names::_proc, &data); 

    switch (status)
    {
	case ENUM_INSTANCES_OK:
	    CMReturnDone(result);
	    CMReturn(CMPI_RC_OK);

	case ENUM_INSTANCES_FAILED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Unreachable!
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::enumInstances()
//
//------------------------------------------------------------------------------

namespace enum_instances
{
    struct Data
    {
	const CMPIBroker* broker;
	const CMPIResult* result;
	const CMPIObjectPath* cmpi_op;
	const char* const* properties;
	CMPIrc rc;
    };

    static bool _proc(
	Instance* cimple_inst,
	Enum_Instances_Status status,
	void* client_data)
    {
	Data* data = (Data*)client_data;
	Destroyer<Instance> destroyer(cimple_inst);

	if (!cimple_inst)
	    return false;

	// Ignore if an error was already encountered.

	if (data->rc != CMPI_RC_OK)
	    return false;

	// Filter out unwanted properties.

	filter_properties(cimple_inst, data->properties);

	// Convert to a CMPI instance and deliver:

	CMPIInstance* cmpi_inst = 0;

	data->rc = make_cmpi_instance(
	    data->broker, 
	    cimple_inst, 
	    name_space(data->cmpi_op), 
	    data->cmpi_op, 
	    cmpi_inst); 

	if (data->rc != CMPI_RC_OK)
	    return false;

	CMReturnInstance(data->result, cmpi_inst);
	return true;
    }
}

CMPIStatus Adapter::enumInstances(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char** properties)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;
    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Filter properties:

    if (properties)
	filter_properties(cimple_ref, properties);

    // Invoke provider:

    enum_instances::Data data = 
	{ adapter->broker, result, cmpi_op, properties, CMPI_RC_OK };

    Enum_Instances_Status status = 
	adapter->enum_instances(cimple_ref, enum_instances::_proc, &data); 

    switch (status)
    {
	case ENUM_INSTANCES_OK:
	    break;

	case ENUM_INSTANCES_FAILED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::getInstance()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::getInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char** properties)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;

    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Filter properties:

    if (properties)
	filter_properties(cimple_ref, properties);

    // Invoke provider:

    Instance* cimple_inst = 0;

    Get_Instance_Status status = 
	adapter->get_instance(cimple_ref, cimple_inst);

    switch (status)
    {
	case GET_INSTANCE_OK:
	    break;

	case GET_INSTANCE_NOT_FOUND:
	    CMReturn(CMPI_RC_ERR_NOT_FOUND);

	case GET_INSTANCE_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Create CMPI instance:

    CMPIInstance* cmpi_inst;

    rc = make_cmpi_instance(
	adapter->broker, cimple_inst, name_space(cmpi_op), cmpi_op, cmpi_inst); 

    if (rc == CMPI_RC_OK)
    {
	CMReturnInstance(result, cmpi_inst);
	CMReturnDone(result);
	CMReturn(CMPI_RC_OK);
    }

    CMReturn(rc);
}

//------------------------------------------------------------------------------
//
// Adapter::createInstance()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::createInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const CMPIInstance* cmpi_inst)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Create CIMPLE instance:

    const Meta_Class* mc = adapter->_mc;

    Instance* cimple_inst = 0;
    CMPIrc rc = make_cimple_instance(mc, cmpi_inst, cimple_inst);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Destroyer<Instance> cmpi_inst_d(cimple_inst);

    // Invoke the provider:

    Create_Instance_Status status =
	adapter->create_instance(cimple_inst);

    switch (status)
    {
	case CREATE_INSTANCE_OK:
	    CMReturnObjectPath(result, cmpi_op);
	    CMReturnDone(result);
	    CMReturn(CMPI_RC_OK);

	case CREATE_INSTANCE_DUPLICATE:
	    CMReturn(CMPI_RC_ERR_ALREADY_EXISTS);

	case CREATE_INSTANCE_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::modifyInstance()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::modifyInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const CMPIInstance* cmpi_inst,
    const char** properties)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Create CIMPLE instance:

    const Meta_Class* mc = adapter->_mc;

    Instance* cimple_inst = 0;
    CMPIrc rc = make_cimple_instance(mc, cmpi_inst, cimple_inst);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Destroyer<Instance> cmpi_inst_d(cimple_inst);

    // Invoke the provider:

    Modify_Instance_Status status =
	adapter->modify_instance(cimple_inst);

    switch (status)
    {
	case MODIFY_INSTANCE_OK:
	    CMReturnObjectPath(result, cmpi_op);
	    CMReturnDone(result);
	    CMReturn(CMPI_RC_OK);

	case MODIFY_INSTANCE_NOT_FOUND:
	    CMReturn(CMPI_RC_ERR_NOT_FOUND);

	case MODIFY_INSTANCE_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::deleteInstance()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::deleteInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;
    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Invoke provider:

    Delete_Instance_Status status = 
	adapter->delete_instance(cimple_ref);

    switch (status)
    {
	case DELETE_INSTANCE_OK:
	    break;

	case DELETE_INSTANCE_NOT_FOUND:
	    CMReturn(CMPI_RC_ERR_NOT_FOUND);

	case DELETE_INSTANCE_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::execQuery()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::execQuery(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const char* lang, 
    const char* query)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

//------------------------------------------------------------------------------
//
// Adapter::methodCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::methodCleanup(
    CMPIMethodMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    return _cleanup((Adapter*)mi->hdl, context, terminating);
}

//------------------------------------------------------------------------------
//
// Adapter::invokeMethod()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::invokeMethod(
    CMPIMethodMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* method, 
    const CMPIArgs* in,
    CMPIArgs* out)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Find CIMPLE method object:

    const Meta_Class* mc = adapter->_mc;
    const Meta_Method* mm = find_method(mc, method);

    if (!mm)
	CMReturn(CMPI_RC_ERR_METHOD_NOT_FOUND);

    // Validate the object path:

    const char* cn = class_name(cmpi_op);

    if (!cn || strcasecmp(cn, mm->name) == 0)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    if (CMGetKeyCount(cmpi_op, NULL) > 0 && (mm->flags & CIMPLE_FLAG_STATIC))
	CMReturn(CMPI_RC_ERR_FAILED);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Destroyer<Instance> cimple_ref_d(cimple_ref);

    // Create the method:

    Instance* cimple_meth = 0;
    rc = make_method(mm, in, cimple_meth);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Destroyer<Instance> cimple_meth_d(cimple_meth);

    // Invoke the provider:

    Invoke_Method_Status status = adapter->invoke_method(
	cimple_ref, cimple_meth);

    switch (status)
    {
	case INVOKE_METHOD_OK:
	    break;

	case INVOKE_METHOD_FAILED:
	    CMReturn(CMPI_RC_ERR_FAILED);

	case INVOKE_METHOD_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    // Convert to CMPI out arguments:

    CMPIValue return_value;
    CMPIType return_type;
    const char* ns = name_space(cmpi_op);

    rc = make_method_out(
	adapter->broker, ns, cimple_meth, out, return_value, return_type);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Append CMPI out args:

    CMReturnData(result, &return_value, return_type);
    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::indicationCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::indicationCleanup(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    return _cleanup((Adapter*)mi->hdl, context, terminating);
}

//------------------------------------------------------------------------------
//
// Adapter::authorizeFilter()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::authorizeFilter(
     CMPIIndicationMI* mi, 
     const CMPIContext* context,
     const CMPISelectExp* select_expr, 
     const char* name_space, 
     const CMPIObjectPath* cmpi_object_path,
     const char* user_name)
{
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::mustPoll()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::mustPoll(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    const CMPISelectExp* filter, 
    const char* indication_type,
    const CMPIObjectPath* class_path)
{
    // ATTN: What is thie for?
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::activateFilter()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::activateFilter(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    const CMPISelectExp* select_expr, 
    const char* indication_type,
    const CMPIObjectPath* class_path, 
    CMPIBoolean first)
{
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::deactivateFilter()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::deactivateFilter(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    const CMPISelectExp* select_expr, 
    const  char* name_space,
    const CMPIObjectPath* class_path, 
    CMPIBoolean last)
{
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::enableIndications()
//
//------------------------------------------------------------------------------

static bool _indication_proc(Instance* cimple_inst, void* client_data)
{
    TRACE;

    // This function is called by the CIMPLE Indication_Handler<> in order to 
    // deliver a single indication.

    Adapter* adapter = (Adapter*)client_data;

    // If this is the final call, just return.

    if (cimple_inst == 0)
	return false;

    // Convert CIMPLE instance to CMPI instance:

    CMPIInstance* cmpi_inst = 0;

    CMPIrc rc = make_cmpi_instance(adapter->broker, 
	cimple_inst, _INDICATIONS_NAMESPACE, 0, cmpi_inst); 

    // Deliver the indication (we cannot do anything about failures).

    if (rc == CMPI_RC_OK)
    {
	// Grab the CMPI context from thread-specific-data.

	const CMPIContext* context = (const CMPIContext*)_context_tls.get();

	// Deliver the indication:

	CBDeliverIndication(
	    adapter->broker, context, _INDICATIONS_NAMESPACE, cmpi_inst);
    }

    // Keep them coming!
    return true;
}

void Adapter::enableIndications(
    CMPIIndicationMI* mi, 
    const CMPIContext* context)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Ignore request if indications already enabled.

    if (adapter->_indications_enabled)
	return;

    adapter->_indications_enabled = true;

    // Invoke the provider:

    Enable_Indications_Status status = adapter->enable_indications(
	_indication_proc, adapter);

    switch (status)
    {
	case ENABLE_INDICATIONS_OK:
	    break;

	case ENABLE_INDICATIONS_FAILED:
	    break;
    }
}

//------------------------------------------------------------------------------
//
// Adapter::disableIndications()
//
//------------------------------------------------------------------------------

void Adapter::disableIndications(
    CMPIIndicationMI* mi, 
    const CMPIContext* context)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Ignore if indications are not enabled.

    if (!adapter->_indications_enabled)
	return;

    // Invoke the provider:

    Disable_Indications_Status status = adapter->disable_indications();

    switch (status)
    {
	case DISABLE_INDICATIONS_OK:
	    break;

	case DISABLE_INDICATIONS_FAILED:
	    break;
    }

    adapter->_indications_enabled = false;
}

//------------------------------------------------------------------------------
//
// Adapter::associationCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::associationCleanup(
    CMPIAssociationMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    return _cleanup((Adapter*)mi->hdl, context, terminating);
}

//------------------------------------------------------------------------------
//
// Adapter::associators()
//
//------------------------------------------------------------------------------

namespace associators
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

    static void _proc(const Instance* cimple_inst, void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!cimple_inst)
	    return;

	// Ignore if an error was already encountered.

	if (data->rc != CMPI_RC_OK)
	    return;

	// Convert to a CMPI object path and deliver:

	CMPIObjectPath* cmpi_op = 0;

	data->rc = make_cmpi_object_path(
	    data->broker,
	    cimple_inst,
	    data->name_space,
	    cmpi_op);

	// Now use the CMPI broker to get the full instance.

	CMPIInstance* cmpi_inst = CBGetInstance(
	    data->broker, data->context, cmpi_op, data->properties, NULL);

	if (!cmpi_inst)
	{
	    data->rc = CMPI_RC_ERR_FAILED;
	    return;
	}

	// Deliver instance to requestor:

	CMReturnInstance(data->result, cmpi_inst);
    }
}

CMPIStatus Adapter::associators( 
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* assoc_class, 
    const char* result_class,
    const char* role, 
    const char* result_role, 
    const char** properties)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    CIMPLE_ASSERT(strcasecmp(assoc_class, adapter->_mc->name) == 0);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Invoke the provider:

    associators::Data data = { adapter->broker, 
	context, result, name_space(cmpi_op), properties, CMPI_RC_OK };

    Enum_Associator_Names_Status status = adapter->enum_associator_names(
	cimple_ref,
        result_class,
        role,
        result_role,
        associators::_proc,
	&data);

    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::associatorNames()
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

    static void _proc(const Instance* cimple_inst, void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!cimple_inst)
	    return;

	// Ignore if an error was already encountered.

	if (data->rc != CMPI_RC_OK)
	    return;

	// Convert to a CMPI object path and deliver:

	CMPIObjectPath* cmpi_op = 0;

	data->rc = make_cmpi_object_path(
	    data->broker,
	    cimple_inst,
	    data->name_space,
	    cmpi_op);

	if (data->rc == CMPI_RC_OK)
	    CMReturnObjectPath(data->result, cmpi_op);
    }
}

CMPIStatus Adapter::associatorNames(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* assoc_class, 
    const char* result_class,
    const char* role, 
    const char* result_role)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    CIMPLE_ASSERT(strcasecmp(assoc_class, adapter->_mc->name) == 0);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Invoke the provider:

    associator_names::Data data = 
	{ adapter->broker, context, result, name_space(cmpi_op), CMPI_RC_OK };

    Enum_Associator_Names_Status status = adapter->enum_associator_names(
	cimple_ref,
        result_class,
        role,
        result_role,
        associator_names::_proc,
	&data);

    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::references()
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

    static void _proc(Instance* cimple_inst, void* client_data)
    {
	Data* data = (Data*)client_data;

	// Ignore the final call.

	if (!cimple_inst)
	    return;

	Destroyer<Instance> cimple_inst_d(cimple_inst);

	// Ignore errors on prior call.

	if (data->rc != CMPI_RC_OK)
	    return;

	// Filter the properties.

	filter_properties(cimple_inst, data->properties);

	// Convert to CMPI instance.

	CMPIInstance* cmpi_inst = 0;

	data->rc = make_cmpi_instance(
	    data->broker, cimple_inst, data->name_space, 0, cmpi_inst);

	if (data->rc != CMPI_RC_OK)
	    return;

	// Deliver the instance.

	CMReturnInstance(data->result, cmpi_inst);
    }
}

CMPIStatus Adapter::references(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* result_class, 
    const char* role ,
    const char** properties)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    CIMPLE_ASSERT(strcasecmp(result_class, adapter->_mc->name) == 0);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Invoke the provider:

    references::Data data = { adapter->broker, 
	context, result, name_space(cmpi_op), properties, CMPI_RC_OK };

    Enum_References_Status status = adapter->enum_references(
        cimple_ref, role, false, references::_proc, &data);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
	    CMReturn(CMPI_RC_OK);

        case ENUM_REFERENCES_FAILED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Unreachable!
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::referenceNames()
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

    static void _proc(Instance* cimple_inst, void* client_data)
    {
	Data* data = (Data*)client_data;

	// Ignore the final call.

	if (!cimple_inst)
	    return;

	Destroyer<Instance> cimple_inst_d(cimple_inst);

	// Ignore errors on prior call.

	if (data->rc != CMPI_RC_OK)
	    return;

	// Filter out non-key properties:

	nullify_non_keys(cimple_inst);

	// Convert to CMPI object path:

	CMPIObjectPath* cmpi_op = 0;

	data->rc = make_cmpi_object_path(
	    data->broker, cimple_inst, data->name_space, cmpi_op);

	if (data->rc != CMPI_RC_OK)
	    return;

	// Deliver the instance.

	CMReturnObjectPath(data->result, cmpi_op);
    }
}

CMPIStatus Adapter::referenceNames(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* result_class, 
    const char* role)
{
    TRACE;

    _context_tls.set((void*)context);
    Adapter* adapter = (Adapter*)mi->hdl;
    Auto_RMutex auto_lock(adapter->_lock);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    CIMPLE_ASSERT(strcasecmp(result_class, adapter->_mc->name) == 0);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Destroyer<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Invoke the provider:

    reference_names::Data data = { 
	adapter->broker, context, result, name_space(cmpi_op), CMPI_RC_OK };

    Enum_References_Status status = adapter->enum_references(
        cimple_ref, role, false, reference_names::_proc, &data);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
	    CMReturn(CMPI_RC_OK);

        case ENUM_REFERENCES_FAILED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Unreachable!
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::_cleanup()
//
//------------------------------------------------------------------------------

CMPIStatus Adapter::_cleanup(
    Adapter* adapter, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    TRACE;

    Auto_RMutex auto_lock(adapter->_lock);

    if (adapter && --adapter->load_count == 1)
	delete adapter;

    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// Adapter::_find_meta_class()
//
//------------------------------------------------------------------------------

const Meta_Class* Adapter::_find_meta_class(const char* class_name)
{
    const Meta_Class* const* meta_classes = 0;
    size_t num_meta_classes = 0;

    get_repository(meta_classes, num_meta_classes);

    return find_meta_class(meta_classes, num_meta_classes, class_name);
}
