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
#include <cimple/version.h>
#include <cimple/Mutex.h>
#include <cimple/Auto_Mutex.h>
#include "Converter.h"
#include "CMPI_Thread_Context.h"

#if 0
# define TRACE printf("===== %s(%d): %s()\n", __FILE__, __LINE__, __FUNCTION__)
#else
# define TRACE
#endif

CIMPLE_NAMESPACE_BEGIN

static const char _INDICATIONS_NAMESPACE[] = "root/cimv2";

//------------------------------------------------------------------------------
//
// _timer()
//
//------------------------------------------------------------------------------

#ifdef ENABLE_TIMER_PROC

uint64 CMPI_Adapter::_timer(void* arg)
{
    TRACE;

    // This function is called when the Scheduler's timer proc expires. It
    // invokes the provider's timer() method().

    CMPI_Adapter* adapter = (CMPI_Adapter*)arg;
    Auto_Mutex auto_lock(adapter->_lock);

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

#endif /* ENABLE_TIMER_PROC */

//------------------------------------------------------------------------------
//
// _timer_thread_proc()
//
//------------------------------------------------------------------------------

#ifdef ENABLE_TIMER_PROC

void* CMPI_Adapter::_timer_thread_proc(void* arg)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)arg;

    // ATTN: there is currently no logic to stop this thread.

    while (!adapter->_stop_timer_thread)
        adapter->_sched->dispatch();

    return 0;
}

#endif /* ENABLE_TIMER_PROC */

//------------------------------------------------------------------------------
//
// CMPI_Adapter::_sched
//
//------------------------------------------------------------------------------

#ifdef ENABLE_TIMER_PROC

Scheduler* CMPI_Adapter::_sched = 0;
Mutex CMPI_Adapter::_sched_lock;

#endif /* ENABLE_TIMER_PROC */

//------------------------------------------------------------------------------
//
// CMPI_Adapter::CMPI_Adapter()
//
//------------------------------------------------------------------------------

CMPI_Adapter::CMPI_Adapter(
    const CMPIBroker* broker_, 
    const CMPIContext* context,
    const char* provider_name, 
    const Registration* registration,
    CMPI_Adapter*& adapter_back_pointer) :
    Provider_Handle(registration),
    _indications_enabled(false),
    _adapter_back_pointer(adapter_back_pointer)
{
    TRACE;

    CMPI_Thread_Context_Pusher pusher(broker_, context);

#ifdef ENABLE_TIMER_PROC
    _stop_timer_thread = false;
#endif /* ENABLE_TIMER_PROC */

    instance_ft.ftVersion = 100;
    instance_ft.miVersion = 100;
    instance_ft.miName = str_printf("instance%s", provider_name);
    instance_ft.cleanup = CMPI_Adapter::cleanup;
    instance_ft.enumInstanceNames = CMPI_Adapter::enumInstanceNames;
    instance_ft.enumInstances = CMPI_Adapter::enumInstances;
    instance_ft.getInstance = CMPI_Adapter::getInstance;
    instance_ft.createInstance = CMPI_Adapter::createInstance;
    instance_ft.modifyInstance = CMPI_Adapter::modifyInstance;
    instance_ft.deleteInstance = CMPI_Adapter::deleteInstance;
    instance_ft.execQuery = CMPI_Adapter::execQuery;

    method_ft.ftVersion = 100;
    method_ft.miVersion = 100;
    method_ft.miName = str_printf("method%s", provider_name);
    method_ft.cleanup = CMPI_Adapter::methodCleanup;
    method_ft.invokeMethod = CMPI_Adapter::invokeMethod;

    indication_ft.ftVersion = 100;
    indication_ft.miVersion = 100;
    indication_ft.miName = str_printf("indication%s", provider_name);
    indication_ft.cleanup = CMPI_Adapter::indicationCleanup;
    indication_ft.authorizeFilter = CMPI_Adapter::authorizeFilter;
    indication_ft.mustPoll = CMPI_Adapter::mustPoll;
    indication_ft.activateFilter = CMPI_Adapter::activateFilter;
    indication_ft.deActivateFilter = CMPI_Adapter::deactivateFilter;
    indication_ft.enableIndications = CMPI_Adapter::enableIndications;
    indication_ft.disableIndications = CMPI_Adapter::disableIndications;

    association_ft.ftVersion = 100;
    association_ft.miVersion = 100;
    association_ft.miName = str_printf("association%s", provider_name);
    association_ft.cleanup = CMPI_Adapter::associationCleanup;
    association_ft.associators = CMPI_Adapter::associators;
    association_ft.associatorNames = CMPI_Adapter::associatorNames;
    association_ft.references = CMPI_Adapter::references;
    association_ft.referenceNames = CMPI_Adapter::referenceNames;

    broker = broker_;

    load_count = 1;

    // Invoke provider load() method:

    load();

#ifdef ENABLE_TIMER_PROC

    // Create a scheduler on first invocation.

    if (_sched == 0)
    {
	_sched_lock.lock();

	if (_sched == 0)
	{
	    _sched = new Scheduler;
	    Thread::create(_timer_thread, _timer_thread_proc, this);
	}

	_sched_lock.unlock();
    }

    // Schedule timer to call the provider's timer() method:

    _timer_id = _sched->add_timer(1, _timer, this);

#endif /* ENABLE_TIMER_PROC */

    // Save meta-class:

    get_meta_class(_mc);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::~CMPI_Adapter()
//
//------------------------------------------------------------------------------

CMPI_Adapter::~CMPI_Adapter()
{
    TRACE;

/*
ATTN: cannot get a context here:
    CMPI_Thread_Context_Pusher pusher(broker_, cmpi_context);
*/


    unload();

    // Release these!

    free((char*)instance_ft.miName);
    free((char*)method_ft.miName);
    free((char*)indication_ft.miName);

    // Remove timer:

#ifdef ENABLE_TIMER_PROC
    _sched->remove_timer(_timer_id);
#endif

    // Null this out so that next time cimple_cmpi_adapter() is called, it
    // will find a null adapter.
    _adapter_back_pointer = 0;

#if 0
    Thread_Context::pop();
#endif
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::cleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::cleanup(
    CMPIInstanceMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    return _cleanup((CMPI_Adapter*)mi->hdl, context, terminating);
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
	Instance* cimple_inst,
	Enum_Instances_Status status,
	void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!cimple_inst)
	    return false;

	Ref<Instance> cimple_inst_d(cimple_inst);

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

CMPIStatus CMPI_Adapter::enumInstanceNames(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;
    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Ref<Instance> cimple_ref_d(cimple_ref);

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
// CMPI_Adapter::enumInstances()
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
	Ref<Instance> destroyer(cimple_inst);

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

CMPIStatus CMPI_Adapter::enumInstances(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char** properties)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;
    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

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
// CMPI_Adapter::getInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::getInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char** properties)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:


    const Meta_Class* mc = adapter->_mc;

    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

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
// CMPI_Adapter::createInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::createInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const CMPIInstance* cmpi_inst)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Create CIMPLE instance:

    const Meta_Class* mc = adapter->_mc;

    Instance* cimple_inst = 0;
    CMPIrc rc = make_cimple_instance(mc, cmpi_inst, cimple_inst);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Ref<Instance> cmpi_inst_d(cimple_inst);

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
// CMPI_Adapter::modifyInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::modifyInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const CMPIInstance* cmpi_inst,
    const char** properties)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Create CIMPLE instance:

    const Meta_Class* mc = adapter->_mc;

    Instance* cimple_inst = 0;
    CMPIrc rc = make_cimple_instance(mc, cmpi_inst, cimple_inst);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Ref<Instance> cmpi_inst_d(cimple_inst);

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
// CMPI_Adapter::deleteInstance()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::deleteInstance(
    CMPIInstanceMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Convert to CIMPLE reference:

    const Meta_Class* mc = adapter->_mc;
    Instance* cimple_ref = 0;
    
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);

    Ref<Instance> cimple_ref_d(cimple_ref);

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
    return _cleanup((CMPI_Adapter*)mi->hdl, context, terminating);
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
    const CMPIObjectPath* cmpi_op, 
    const char* method, 
    const CMPIArgs* in,
    CMPIArgs* out)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

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

    Ref<Instance> cimple_ref_d(cimple_ref);

    // Create the method:

    Instance* cimple_meth = 0;
    rc = make_method(mm, in, find_meta_class_callback, adapter, cimple_meth);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    Ref<Instance> cimple_meth_d(cimple_meth);

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
// CMPI_Adapter::indicationCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::indicationCleanup(
    CMPIIndicationMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    return _cleanup((CMPI_Adapter*)mi->hdl, context, terminating);
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
    // ATTN: What is thie for?
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
    const  char* name_space,
    const CMPIObjectPath* class_path, 
    CMPIBoolean last)
{
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::enableIndications()
//
//------------------------------------------------------------------------------

static bool _indication_proc(Instance* cimple_inst, void* client_data)
{
    TRACE;

    // This function is called by the CIMPLE Indication_Handler<> in order to 
    // deliver a single indication.

    CMPI_Adapter* adapter = (CMPI_Adapter*)client_data;

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
	// ATTN: get thread context for this thread somehow!

	// Deliver the indication:

	CMPI_Thread_Context* thread_context = 
	    (CMPI_Thread_Context*)Thread_Context::top();
	assert(thread_context != 0);

	CBDeliverIndication(
	    thread_context->cmpi_broker(),
	    thread_context->cmpi_context(),
	    _INDICATIONS_NAMESPACE, 
	    cmpi_inst);
    }

    // Keep them coming!
    return true;
}

void CMPI_Adapter::enableIndications(
    CMPIIndicationMI* mi, 
    const CMPIContext* context)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

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
// CMPI_Adapter::disableIndications()
//
//------------------------------------------------------------------------------

void CMPI_Adapter::disableIndications(
    CMPIIndicationMI* mi, 
    const CMPIContext* context)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

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
// CMPI_Adapter::associationCleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::associationCleanup(
    CMPIAssociationMI* mi, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    return _cleanup((CMPI_Adapter*)mi->hdl, context, terminating);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::associators()
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

    static bool _proc(
	const Instance* cimple_inst, 
	Enum_Associator_Names_Status status, 
	void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!cimple_inst)
	    return false;

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

	// Now use the CMPI broker to get the full instance.

	CMPIInstance* cmpi_inst = CBGetInstance(
	    data->broker, data->context, cmpi_op, data->properties, NULL);

	if (!cmpi_inst)
	{
	    data->rc = CMPI_RC_ERR_FAILED;
	    return false;
	}

	// Deliver instance to requestor:

	CMReturnInstance(data->result, cmpi_inst);

	return true;
    }
}

CMPIStatus CMPI_Adapter::associators( 
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* assoc_class_, 
    const char* result_class_,
    const char* role_, 
    const char* result_role_, 
    const char** properties)
{
    TRACE;

    const char* assoc_class = assoc_class_ ? assoc_class_ : "";
    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";
    const char* result_role = result_role_ ? result_role_ : "";

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    CIMPLE_ASSERT(strcasecmp(assoc_class, adapter->_mc->name) == 0);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

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
	const Instance* cimple_inst, 
	Enum_Associator_Names_Status status,
	void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!cimple_inst)
	    return false;

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

	if (data->rc == CMPI_RC_OK)
	    CMReturnObjectPath(data->result, cmpi_op);

	return true;
    }
}

CMPIStatus CMPI_Adapter::associatorNames(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* assoc_class_, 
    const char* result_class_,
    const char* role_, 
    const char* result_role_)
{
    TRACE;

    const char* assoc_class = assoc_class_ ? assoc_class_ : "";
    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";
    const char* result_role = result_role_ ? result_role_ : "";

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    CIMPLE_ASSERT(strcasecmp(assoc_class, adapter->_mc->name) == 0);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

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
	Instance* cimple_inst, 
	Enum_References_Status status,
	void* client_data)
    {
	Data* data = (Data*)client_data;

	// Ignore the final call.

	if (!cimple_inst)
	    return false;

	Ref<Instance> cimple_inst_d(cimple_inst);

	// Ignore errors on prior call.

	if (data->rc != CMPI_RC_OK)
	    return false;

	// Filter the properties.

	filter_properties(cimple_inst, data->properties);

	// Convert to CMPI instance.

	CMPIInstance* cmpi_inst = 0;

	data->rc = make_cmpi_instance(
	    data->broker, cimple_inst, data->name_space, 0, cmpi_inst);

	if (data->rc != CMPI_RC_OK)
	    return false;

	// Deliver the instance.

	CMReturnInstance(data->result, cmpi_inst);

	return true;
    }
}

CMPIStatus CMPI_Adapter::references(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* result_class_, 
    const char* role_,
    const char** properties)
{
    TRACE;

    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    CIMPLE_ASSERT(strcasecmp(result_class, adapter->_mc->name) == 0);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Create a model.

    const Meta_Class* model_meta_class = 0;
    adapter->get_meta_class(model_meta_class);
    Instance* cimple_model = cimple::create(model_meta_class);

    // Invoke the provider:

    references::Data data = { adapter->broker, 
	context, result, name_space(cmpi_op), properties, CMPI_RC_OK };

    Enum_References_Status status = adapter->enum_references(
        cimple_ref, cimple_model, role, references::_proc, &data);

    destroy(cimple_model);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
	    CMReturn(CMPI_RC_OK);

        case ENUM_REFERENCES_FAILED:
	    CMReturn(CMPI_RC_ERR_FAILED);

        case ENUM_REFERENCES_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Unreachable!
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
	Instance* cimple_inst, 
	Enum_References_Status status,
	void* client_data)
    {
	Data* data = (Data*)client_data;

	// Ignore the final call.

	if (!cimple_inst)
	    return false;

	Ref<Instance> cimple_inst_d(cimple_inst);

	// Ignore errors on prior call.

	if (data->rc != CMPI_RC_OK)
	    return false;

	// Filter out non-key properties:

	nullify_non_keys(cimple_inst);

	// Convert to CMPI object path:

	CMPIObjectPath* cmpi_op = 0;

	data->rc = make_cmpi_object_path(
	    data->broker, cimple_inst, data->name_space, cmpi_op);

	if (data->rc != CMPI_RC_OK)
	    return false;

	// Deliver the instance.

	CMReturnObjectPath(data->result, cmpi_op);

	return true;
    }
}

CMPIStatus CMPI_Adapter::referenceNames(
    CMPIAssociationMI* mi, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* cmpi_op, 
    const char* result_class_, 
    const char* role_)
{
    TRACE;

    CMPI_Adapter* adapter = (CMPI_Adapter*)mi->hdl;
    CMPI_Thread_Context_Pusher pusher(adapter->broker, context);
    Auto_Mutex auto_lock(adapter->_lock);

    const char* result_class = result_class_ ? result_class_ : "";
    const char* role = role_ ? role_ : "";

    // Lookup meta class for cmpi_op (not the same as the provider class).

    const Meta_Class* mc = adapter->_find_meta_class(class_name(cmpi_op));

    if (!mc)
	CMReturn(CMPI_RC_ERR_INVALID_CLASS);

    CIMPLE_ASSERT(strcasecmp(result_class, adapter->_mc->name) == 0);

    // Convert to CIMPLE reference:

    Instance* cimple_ref = 0;
    CMPIrc rc = make_cimple_reference(mc, cmpi_op, cimple_ref);
    Ref<Instance> cimple_ref_d(cimple_ref);

    if (rc != CMPI_RC_OK)
	CMReturn(rc);

    // Create a model.

    const Meta_Class* model_meta_class = 0;
    adapter->get_meta_class(model_meta_class);
    Instance* cimple_model = cimple::create(model_meta_class);
    nullify_non_keys(cimple_model);

    // Invoke the provider:

    reference_names::Data data = { 
	adapter->broker, context, result, name_space(cmpi_op), CMPI_RC_OK };

    Enum_References_Status status = adapter->enum_references(
        cimple_ref, cimple_model, role, reference_names::_proc, &data);

    destroy(cimple_model);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
	    CMReturn(CMPI_RC_OK);

        case ENUM_REFERENCES_FAILED:
        case ENUM_REFERENCES_UNSUPPORTED:
	    CMReturn(CMPI_RC_ERR_FAILED);
    }

    // Unreachable!
    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::_cleanup()
//
//------------------------------------------------------------------------------

CMPIStatus CMPI_Adapter::_cleanup(
    CMPI_Adapter* adapter, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    TRACE;

    if (adapter && --adapter->load_count == 0)
	delete adapter;

    CMReturn(CMPI_RC_OK);
}

//------------------------------------------------------------------------------
//
// CMPI_Adapter::_find_meta_class()
//
//------------------------------------------------------------------------------

const Meta_Class* CMPI_Adapter::_find_meta_class(const char* class_name)
{
    const Meta_Repository* meta_repository;
    get_repository(meta_repository);

    return find_meta_class(meta_repository, class_name);
}

CIMPLE_NAMESPACE_END

using namespace cimple;

extern "C" CIMPLE_EXPORT int cimple_cmpi_adapter(
    void* arg0, /* provider-interface */
    void* arg1, /* adapter */
    void* arg2, /* registration */
    void* arg3, /* broker */
    void* arg4, /* context */
    void* arg5, /* provider_name */
    void* arg6, /* mi-type */
    void* arg7) /* mi */
{
    TRACE;

    // Extract parameters:

    CMPI_Adapter*& adapter = *((CMPI_Adapter**)arg1);
    const Registration* registration = (const Registration*)arg2;
    const CMPIBroker* broker = (const CMPIBroker*)arg3;
    const CMPIContext* context = (const CMPIContext*)arg4;
    const char* provider_name = (const char*)arg5;
    long mi_type = (long)arg6;

    // Create adapter:

    if (adapter)
    {
        adapter->load_count++;
    }
    else
    {
        adapter = new CMPI_Adapter(
	    broker, context, provider_name, registration, adapter);
    }

    // Create management interface:

    switch (mi_type)
    {
	case 'I': /* instance provider */
	{
	    CMPIInstanceMI tmp = {((void*)adapter), &adapter->instance_ft};
	    memcpy(&adapter->instance_mi, &tmp, sizeof(tmp));
	    *((CMPIInstanceMI**)arg7) = &adapter->instance_mi;
	    break;
	}

	case 'M': /* method provider */
	{
	    CMPIMethodMI tmp = {((void*)adapter), &adapter->method_ft};
	    memcpy(&adapter->method_mi, &tmp, sizeof(tmp));
	    *((CMPIMethodMI**)arg7) = &adapter->method_mi;
	    break;
	}

	case 'A': /* association provider */
	{
	    CMPIAssociationMI tmp = 
		{((void*)adapter), &adapter->association_ft};
	    memcpy(&adapter->association_mi, &tmp, sizeof(tmp));
	    *((CMPIAssociationMI**)arg7) = &adapter->association_mi;
	    break;
	}

	case 'N': /* indication provider */
	{
	    CMPIIndicationMI tmp = 
		{((void*)adapter), &adapter->indication_ft};
	    memcpy(&adapter->indication_mi, &tmp, sizeof(tmp));
	    *((CMPIIndicationMI**)arg7) = &adapter->indication_mi;
	    break;
	}
    }

    // Success!
    return 0;
}

const Meta_Class* CMPI_Adapter::find_meta_class_callback(
    const char* class_name, void* client_data)
{
    return ((CMPI_Adapter*)client_data)->_find_meta_class(class_name);
}

CIMPLE_INJECT_VERSION_TAG;
