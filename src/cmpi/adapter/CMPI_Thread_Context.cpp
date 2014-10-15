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

#include <cimple/cimple.h>
#include "CMPI_Thread_Context.h"
#include "Converter.h"
#include <cimple/Thread.h>

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// _top()
//
//==============================================================================

static CMPI_Thread_Context* _top()
{
    CMPI_Thread_Context* context = (CMPI_Thread_Context*)Thread_Context::top();
    assert(context != 0);
    return context;
}

//==============================================================================
//
// CMPI_Thread_Context:
//
//==============================================================================

CMPI_Thread_Context::~CMPI_Thread_Context()
{
}

Thread_Context* CMPI_Thread_Context::thread_create_hook(void* arg)
{
    CMPI_Thread_Context* context = _top();
    assert(context != 0);

    CMPIContext* cmpi_context = CBPrepareAttachThread(
	context->cmpi_broker(), context->cmpi_context());

    return new CMPI_Thread_Context(context->cmpi_broker(), cmpi_context);
}

void CMPI_Thread_Context::thread_start_hook()
{
    CMPI_Thread_Context* context = _top();
    CBAttachThread(context->cmpi_broker(), context->cmpi_context());
}

void CMPI_Thread_Context::thread_exit_hook()
{
    CMPI_Thread_Context* context = _top();
    CBDetachThread(context->cmpi_broker(), context->cmpi_context());
}

struct Instance_Enumerator_Rep
{
    CMPIEnumeration* cmpi_enumeration;
    const Meta_Class* meta_class;
    Ref<Instance> instance;
};

static Ref<Instance> _next_instance(
    CMPIEnumeration* cmpi_enumeration,
    const Meta_Class* meta_class)
{
    CMPIStatus status;

    if (CMHasNext(cmpi_enumeration, &status))
    {
	CMPIData data = CMGetNext(cmpi_enumeration, &status);

	if (status.rc != CMPI_RC_OK)
	    return Ref<Instance>();

	if (data.type != CMPI_instance)
	    return Ref<Instance>();

	CMPIInstance* cmpi_instance = data.value.inst;

	Instance* instance = 0;

	CMPIrc rc = make_cimple_instance(
	    meta_class,
	    data.value.inst,
	    instance);

	if (rc != CMPI_RC_OK)
	    return Ref<Instance>();

	return Ref<Instance>(instance);
    }

    return Ref<Instance>();
}

Instance_Enumerator_Rep* CMPI_Thread_Context::instance_enumerator_create(
    const char* name_space,
    const Instance* model)
{
    Error::clear();

    if (!name_space)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::instance_enumerator_create(): "
            "null name_space parameter");
	return 0;
    }

    if (!model)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::instance_enumerator_create(): "
            "null model parameter");
	return 0;
    }

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create an object path.

    CMPIObjectPath* object_path = NULL;

    CMPIrc rc = make_cmpi_object_path(
	context->cmpi_broker(),
	model,
	name_space,
	object_path);

    if (rc != CMPI_RC_OK)
    {
        // Propgate error.
	return 0;
    }

    // Create the enumeration object.

    CMPIStatus status;

    CMPIEnumeration* enumeration = CBEnumInstances(
	context->cmpi_broker(), 
	context->cmpi_context(),
	object_path,
	NULL, // properties
	&status);

    if (status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
	return 0;
    }

    Instance_Enumerator_Rep* rep = new Instance_Enumerator_Rep;
    rep->cmpi_enumeration = enumeration;
    rep->meta_class = model->meta_class;
    rep->instance = _next_instance(rep->cmpi_enumeration, rep->meta_class);

    return rep;
}

void CMPI_Thread_Context::instance_enumerator_destroy(
    Instance_Enumerator_Rep* rep)
{
    // CMPI cleans up its own objects.
    delete rep;
}

bool CMPI_Thread_Context::instance_enumerator_more(
    Instance_Enumerator_Rep* rep)
{
    if (!rep)
	return false;

    return rep->instance.ptr() != 0;
}

void CMPI_Thread_Context::instance_enumerator_next(
    Instance_Enumerator_Rep* rep)
{
    if (!rep)
	return;

    rep->instance = _next_instance(rep->cmpi_enumeration, rep->meta_class);
}

Ref<Instance> CMPI_Thread_Context::instance_enumerator_get(
    Instance_Enumerator_Rep* rep)
{
    if (!rep)
	return Ref<Instance>();

    return rep->instance;
}

Ref<Instance> CMPI_Thread_Context::get_instance(
    const char* name_space,
    const Instance* model)
{
    Error::clear();

    if (!name_space)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED,
            "CMPI_Thread_Context::get_instance(): "
            "null name_space parameter");
	return Ref<Instance>();
    }

    if (!model)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED,
            "CMPI_Thread_Context::get_instance(): "
            "null model parameter");
	return Ref<Instance>();
    }

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cmpi_object_path = NULL;

    CMPIrc rc = make_cmpi_object_path(
	context->cmpi_broker(),
	model,
	name_space,
	cmpi_object_path);

    if (rc != CMPI_RC_OK)
    {
        // Propgate error!
	return Ref<Instance>();
    }

    // Get the instance.

    CMPIStatus status;

    CMPIInstance* cmpi_instance = CBGetInstance(
	context->cmpi_broker(),
	context->cmpi_context(),
	cmpi_object_path,
	NULL,
	&status);

    if (status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
	return Ref<Instance>();
    }

    // Create CIMPLE instance.

    Instance* instance = 0;

    rc = make_cimple_instance(model->meta_class, cmpi_instance, instance);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
	return Ref<Instance>();
    }

    return Ref<Instance>(instance);
}

int CMPI_Thread_Context::create_instance(
    const char* name_space,
    const Instance* instance)
{
    Error::clear();

    if (!name_space)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::create_instance(): "
            "null name_space parameter");
	return -1;
    }

    if (!instance)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::create_instance(): "
            "null instance parameter");
	return -1;
    }

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cmpi_object_path = NULL;

    CMPIrc rc = make_cmpi_object_path(
	context->cmpi_broker(),
	instance,
	name_space,
	cmpi_object_path);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
	return -1;
    }

    // Create CMPI instance.

    CMPIInstance* cmpi_instance = NULL;

    rc = make_cmpi_instance(
	context->cmpi_broker(),
	instance,
	name_space,
	cmpi_object_path,
	cmpi_instance);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
	return -1;
    }

    // Create instance.

    CMPIStatus status;

    CMPIObjectPath* cmpi_object_path_tmp = CBCreateInstance(
	context->cmpi_broker(),
	context->cmpi_context(),
	cmpi_object_path,
	cmpi_instance,
	&status);

    if (status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
	return -1;
    }

    return 0;
}

int CMPI_Thread_Context::delete_instance(
    const char* name_space,
    const Instance* instance)
{
    Error::clear();

    if (name_space)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::delete_instance(): "
            "null name_space paramter");
        return -1;
    }

    if (!instance)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::delete_instance(): "
            "null instance paramter");
	return -1;
    }

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cmpi_object_path = NULL;

    CMPIrc rc = make_cmpi_object_path(
	context->cmpi_broker(),
	instance,
	name_space,
	cmpi_object_path);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
	return -1;
    }

    // Delete instance.

    CMPIStatus status = CBDeleteInstance(
	context->cmpi_broker(),
	context->cmpi_context(),
	cmpi_object_path);

    if (status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
	return -1;
    }

    return 0;
}

int CMPI_Thread_Context::modify_instance(
    const char* name_space,
    const Instance* instance)
{
    Error::clear();

    if (!name_space)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::modify_instance(): "
            "null name_space parameter");
	return -1;
    }

    if (!instance)
    {
        set_cmpi_error(CMPI_RC_ERR_FAILED, 
            "CMPI_Thread_Context::modify_instance(): "
            "null instance parameter");
	return -1;
    }

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cmpi_object_path = NULL;

    CMPIrc rc = make_cmpi_object_path(
	context->cmpi_broker(),
	instance,
	name_space,
	cmpi_object_path);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
	return -1;
    }

    // Create CMPI instance.

    CMPIInstance* cmpi_instance = NULL;

    rc = make_cmpi_instance(
	context->cmpi_broker(),
	instance,
	name_space,
	cmpi_object_path,
	cmpi_instance);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
	return -1;
    }

    // Create instance.

    CMPIStatus status = CBModifyInstance(
	context->cmpi_broker(),
	context->cmpi_context(),
	cmpi_object_path,
	cmpi_instance,
	NULL);

    if (status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
	return -1;
    }

    return 0;
}

CMPI_Thread_Context::CMPI_Thread_Context(
    const CMPIBroker* cmpi_broker,
    const CMPIContext* cmpi_context)
    :
    _cmpi_broker(cmpi_broker),
    _cmpi_context(cmpi_context)
{
}

CIMPLE_NAMESPACE_END
