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
#include "CMPI_Adapter.h"
#include "CMPI_Containers.h"
#include <cimple/log.h>

CIMPLE_NAMESPACE_BEGIN
#define FL __FILE__, __LINE__
extern int cmpi_to_cimple_value(
    const Meta_Repository* mr,
    const CMPIBroker* cb,
    const char* ns,
    const CMPIData& data,
    Value& v);

//==============================================================================
//
// Local definitions:
//
//==============================================================================

static CMPIEnumeration* cimple_CBEnumInstances(
    const CMPIBroker* mb, 
    const CMPIContext* ctx,
    const CMPIObjectPath* op, 
    const char** properties, 
    CMPIStatus* rc)
{
    return (mb->bft->enumerateInstances(mb, ctx, op, properties, rc));
}

inline static CMPIStatus cimple_CBSetInstance(
    const CMPIBroker* mb, 
    const CMPIContext* ctx,
    const CMPIObjectPath* op, 
    const CMPIInstance* inst)
{
    return (mb->bft->modifyInstance(mb, ctx, op, inst, NULL));
}

static CMPIrc _make_cmpi_method(
    const CMPIBroker* cb,
    const char* ns,
    const Instance* meth,
    CMPIArgs* in)
{
    CMPIArgs_Container cont(
        meth->meta_class->meta_repository, cb, ns, in);

    if (cont.convert(meth, CIMPLE_FLAG_IN) != 0)
        return CMPI_RC_ERR_FAILED;

    return CMPI_RC_OK;
}

static CMPIrc _make_cimple_method(
    const CMPIBroker* cb,
    const Meta_Repository* mr,
    const Meta_Method* mm,
    const CMPIObjectPath* cop,
    const CMPIArgs* out,
    Instance*& inst)
{
    CMPIArgs_Container cont(mr, cb, name_space(cop), (CMPIArgs*)out);

    out = 0;

    if (cont.convert((Meta_Class*)mm, CIMPLE_FLAG_OUT, inst) != 0 || !inst)
        return CMPI_RC_ERR_FAILED;

    if (cop)
        __set_name_space_recursive(inst, name_space(cop), false);

/*
ATTN: handle "return_value"!
*/

    return CMPI_RC_OK;
}

//==============================================================================
//
// _top()
//
//==============================================================================

static CMPI_Thread_Context* _top()
{
    CMPI_Thread_Context* context = (CMPI_Thread_Context*)Thread_Context::top();

    CIMPLE_ASSERT(context != 0);
    return context;
}

//==============================================================================
//
// CMPI_Thread_Context:
//
//==============================================================================

CMPI_Thread_Context::~CMPI_Thread_Context()
{
    log(LL_DBG, __FILE__, __LINE__, "enter: %s()",
        "CMPI_Thread_Context::~CMPI_Thread_Context");
}

Thread_Context* CMPI_Thread_Context::thread_create_hook(void* arg)
{
    CMPI_Thread_Context* context = _top();

    CIMPLE_ASSERT(context != 0);
    CIMPLE_ASSERT(context->cmpi_broker() != 0);
    CIMPLE_ASSERT(context->cmpi_context() != 0);

    CMPIContext* cmpi_context = CBPrepareAttachThread(
        context->cmpi_broker(), context->cmpi_context());

    CIMPLE_ASSERT(cmpi_context != 0);

    return new CMPI_Thread_Context(
        context->cmpi_broker(), cmpi_context, context->cmpi_adapter());
}

void CMPI_Thread_Context::thread_start_hook()
{
    CMPI_Thread_Context* context = _top();

    CIMPLE_ASSERT(context != 0);
    CIMPLE_ASSERT(context->cmpi_broker() != 0);
    CIMPLE_ASSERT(context->cmpi_context() != 0);

    CBAttachThread(context->cmpi_broker(), context->cmpi_context());
}

void CMPI_Thread_Context::thread_exit_hook()
{
    CMPI_Thread_Context* context = _top();

    CIMPLE_ASSERT(context != 0);
    CIMPLE_ASSERT(context->cmpi_broker() != 0);
    CIMPLE_ASSERT(context->cmpi_context() != 0);

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

        CMPIInstance* ci = data.value.inst;

        Instance* instance = 0;

        CMPIrc rc = make_cimple_instance(
            0,
            meta_class,
            CMGetObjectPath(ci, 0),
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

    if (!name_space)
        return 0;

    if (!model)
        return 0;

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

    CMPIEnumeration* enumeration = cimple_CBEnumInstances(
        context->cmpi_broker(), 
        context->cmpi_context(),
        object_path,
        NULL, // properties
        &status);

    if (status.rc != CMPI_RC_OK)
        return 0;

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
    if (!name_space)
        return Ref<Instance>();

    if (!model)
        return Ref<Instance>();

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cop = NULL;

    CMPIrc rc = make_cmpi_object_path(
        context->cmpi_broker(),
        model,
        name_space,
        cop);

    if (rc != CMPI_RC_OK)
    {
        // Propgate error!
        return Ref<Instance>();
    }

    // Get the instance.

    CMPIStatus status;

    CMPIInstance* ci = CBGetInstance(
        context->cmpi_broker(),
        context->cmpi_context(),
        cop,
        NULL,
        &status);

    if (status.rc != CMPI_RC_OK)
        return Ref<Instance>();

    // Create CIMPLE instance.

    Instance* instance = 0;

    rc = make_cimple_instance(
        0, model->meta_class, cop, ci, instance);

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

    if (!name_space)
        return -1;

    if (!instance)
        return -1;

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cop = NULL;

    CMPIrc rc = make_cmpi_object_path(
        context->cmpi_broker(),
        instance,
        name_space,
        cop);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
        return -1;
    }

    // Create CMPI instance.

    CMPIInstance* ci = NULL;

    rc = make_cmpi_instance(
        context->cmpi_broker(),
        instance,
        name_space,
        cop,
        0,
        ci);

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
        cop,
        ci,
        &status);

    if (status.rc != CMPI_RC_OK)
        return -1;

    return 0;
}

int CMPI_Thread_Context::delete_instance(
    const char* name_space,
    const Instance* instance)
{

    if (!name_space)
        return -1;

    if (!instance)
        return -1;

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cop = NULL;

    CMPIrc rc = make_cmpi_object_path(
        context->cmpi_broker(),
        instance,
        name_space,
        cop);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
        return -1;
    }

    // Delete instance.

    CMPIStatus status = CBDeleteInstance(
        context->cmpi_broker(),
        context->cmpi_context(),
        cop);

    if (status.rc != CMPI_RC_OK)
        return -1;

    return 0;
}

int CMPI_Thread_Context::modify_instance(
    const char* name_space,
    const Instance* instance)
{
    if (!name_space)
        return -1;

    if (!instance)
        return -1;

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    // Create CMPI object path.

    CMPIObjectPath* cop = NULL;

    CMPIrc rc = make_cmpi_object_path(
        context->cmpi_broker(),
        instance,
        name_space,
        cop);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
        return -1;
    }

    // Create CMPI instance.

    CMPIInstance* ci = NULL;

    rc = make_cmpi_instance(
        context->cmpi_broker(),
        instance,
        name_space,
        cop,
        0,
        ci);

    if (rc != CMPI_RC_OK)
    {
        // Propagate error!
        return -1;
    }

    // Create instance.

    CMPIStatus status = cimple_CBSetInstance(
        context->cmpi_broker(),
        context->cmpi_context(),
        cop,
        ci);

    if (status.rc != CMPI_RC_OK)
        return -1;

    return 0;
}

int CMPI_Thread_Context::invoke_method(
    const char* ns,
    const Instance* instance,
    Instance* meth)
{
    // Check input parameters:

    if (!ns || !instance || !meth)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Get meta-class:

    const Meta_Class* mc = instance->meta_class;

    if (!mc)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Get meta-repository:

    const Meta_Repository* mr = mc->meta_repository;

    if (!mr)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Get thread context.

    CMPI_Thread_Context* context = _top();

    if (!context)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Get CMPI broker:

    const CMPIBroker* cb = context->cmpi_broker();

    if (!cb)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Get CMPI context:

    const CMPIContext* cc = context->cmpi_context();

    if (!cc)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Create CMPI object path:

    CMPIObjectPath* cop = 0;

    if (meth->meta_class->flags & CIMPLE_FLAG_STATIC)
    {
        cop = CMNewObjectPath(cb, ns, mc->name, 0);

        if (!cop)
        {
            CIMPLE_WARN(("failed"));
            return -1;
        }
    }
    else if (make_cmpi_object_path(cb, instance, ns, cop) != CMPI_RC_OK)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Create input args:

    CMPIArgs* in = CMNewArgs(cb, NULL);

    if (!in)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    CMPIrc rc = _make_cmpi_method(cb, ns, meth, in);

    if (rc != CMPI_RC_OK)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Invoke method:

    CMPIArgs* out = CMNewArgs(cb, NULL);

    if (!out)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    CMPIStatus status;
    CMPIStatus st = { CMPI_RC_OK, NULL };
    CMPIData cd = CBInvokeMethod(
        cb, cc, cop, meth->meta_class->name, in, out, &st);

    if (st.rc != CMPI_RC_OK)
    {
        CIMPLE_WARN(("failed[%u]", st.rc));
        return -1;
    }

    // Convert output parameters:

    rc = _make_cimple_method(
        cb,
        mr,
        (const Meta_Method*)meth->meta_class,
        cop,
        out,
        meth);

    if (rc != CMPI_RC_OK)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Convert the return value:

    Value ret;

    if (cmpi_to_cimple_value(mr, cb, ns, cd, ret) != 0)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    const Meta_Feature* mf = find_feature(
        meth->meta_class, "return_value", CIMPLE_FLAG_PROPERTY);

    if (!mf)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    if (ret.get(meth, mf) != 0)
    {
        CIMPLE_WARN(("failed"));
        return -1;
    }

    // Success!
    return 0;
}

void CMPI_Thread_Context::allow_unload(bool flag)
{
    CIMPLE_ASSERT(_cmpi_adapter != 0);
    _cmpi_adapter->allow_unload = flag;
}

CMPI_Thread_Context::CMPI_Thread_Context(
    const CMPIBroker* cmpi_broker,
    const CMPIContext* cmpi_context,
    class CMPI_Adapter* cmpi_adapter)
    :
    _cmpi_broker(cmpi_broker),
    _cmpi_context(cmpi_context),
    _cmpi_adapter(cmpi_adapter)
{
    cmpi_adapter->ent(FL, "createInstance");

    cmpi_adapter->ret(FL, "createInstance");
}

bool CMPI_Thread_Context::get_username(String& user_name)
{
    CIMPLE_ASSERT(_cmpi_adapter != 0);
    CMPI_Thread_Context* context = _top();

    // experimental code to get username. 

    if(context != 0) 
    {
        // Experimental code to get User Name from context. This just
        // gets the user name and displays it.

        const CMPIContext* cc = context->cmpi_context();

        if(cc) 
        { 
            CMPIStatus rc; 
            CMPIData userName = (cc->ft->getEntry)(cc,CMPIPrincipal,&rc); 
            if(rc.rc==CMPI_RC_OK) 
            {
                //printf("usernameType=%d##usernameValue=%s\n",userName.type,
                //       userName.value.string->ft->getCharPtr(
                //                      userName.value.string,&rc));
                user_name = userName.value.string->ft->getCharPtr(
                                        userName.value.string,&rc);
              
                return true;
            } 
            else 
            { 
                CIMPLE_ERR(("username not OK cmpirc=%d",rc.rc));
            } 
        } 
    }
    return false;
}

CIMPLE_NAMESPACE_END

