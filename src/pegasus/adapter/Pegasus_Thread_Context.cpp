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
#include "Pegasus_Thread_Context.h"
#include <pegasus/utils/Converter.h>
#include <pegasus/utils/Str.h>
#include <cimple/Thread.h>
#include <cimple/log.h>
#include <cimple/Adapter_Tracer.h>

CIMPLE_NAMESPACE_BEGIN

Pegasus_Thread_Context::Pegasus_Thread_Context(
    P_CIMOMHandle* cimom_handle,
    P_OperationContext* operation_context,
    bool delete_operation_context)
    :
    _cimom_handle(cimom_handle),
    _operation_context(operation_context),
    _delete_operation_context(delete_operation_context)
{
}

Pegasus_Thread_Context::~Pegasus_Thread_Context()
{
    if (_delete_operation_context)
        delete _operation_context;
}

static Pegasus_Thread_Context* _top()
{
    Pegasus_Thread_Context* context = 
        (Pegasus_Thread_Context*)Thread_Context::top();
    assert(context != 0);

    return context;
}

Thread_Context* Pegasus_Thread_Context::thread_create_hook(void* arg)
{
    Pegasus_Thread_Context* context = _top();
    assert(context != 0);

    P_OperationContext* operation_context = 
        new P_OperationContext(*context->operation_context());

    return new Pegasus_Thread_Context(
        context->cimom_handle(), operation_context, true);
}

void Pegasus_Thread_Context::thread_start_hook()
{
}

void Pegasus_Thread_Context::thread_exit_hook()
{
}

struct Pegasus_Instance_Enumerator_Rep
{
    const Meta_Class* meta_class;
    Pegasus::Array<P_CIMInstance> instances;
    P_Uint32 pos;
};

Instance_Enumerator_Rep* Pegasus_Thread_Context::instance_enumerator_create(
    const char* name_space,
    const Instance* model)
{
    if (!name_space || !model)
        return 0;

    Pegasus_Thread_Context* context = _top();

    Pegasus_Instance_Enumerator_Rep* rep = 0;
    rep = new Pegasus_Instance_Enumerator_Rep;
    rep->meta_class = model->meta_class;
    rep->pos = 0;

    try
    {
        rep->instances = context->cimom_handle()->enumerateInstances(
            *context->operation_context(),
            name_space,
            model->meta_class->name,
            true,
            false,
            false,
            false,
            P_CIMPropertyList());

    }
    catch (...)
    {
        delete rep;
        return 0;
    }


    return (Instance_Enumerator_Rep*)rep;
}

void Pegasus_Thread_Context::instance_enumerator_destroy(
    Instance_Enumerator_Rep* rep)
{
    delete (Pegasus_Instance_Enumerator_Rep*)rep;
}

bool Pegasus_Thread_Context::instance_enumerator_more(
    Instance_Enumerator_Rep* rep_)
{
    Pegasus_Instance_Enumerator_Rep* rep = 
        (Pegasus_Instance_Enumerator_Rep*)rep_;

    if (!rep)
        return false;

    return (rep->pos == rep->instances.size()) ? false : true;
}

void Pegasus_Thread_Context::instance_enumerator_next(
    Instance_Enumerator_Rep* rep_)
{
    Pegasus_Instance_Enumerator_Rep* rep = 
        (Pegasus_Instance_Enumerator_Rep*)rep_;

    if (rep && rep->pos != rep->instances.size())
        rep->pos++;
}

Ref<Instance> Pegasus_Thread_Context::instance_enumerator_get(
    Instance_Enumerator_Rep* rep_)
{
    Pegasus_Instance_Enumerator_Rep* rep = 
        (Pegasus_Instance_Enumerator_Rep*)rep_;

    if (!rep || rep->pos == rep->instances.size())
        return Ref<Instance>();

    Instance* instance = 0;

    Str ns(rep->instances[rep->pos].getPath().getNameSpace());

    if (Converter::to_cimple_instance(
        *ns, rep->instances[rep->pos], rep->meta_class, instance) == 0)
    {
        return Ref<Instance>(instance);
    }

    return Ref<Instance>();
}

Ref<Instance> Pegasus_Thread_Context::get_instance(
    const char* name_space,
    const Instance* model)
{
    Pegasus_Thread_Context* context = _top();

    // Convert to Pegasus object path.

    P_CIMObjectPath cim_object_path;

    if (Converter::to_pegasus_object_path(
        P_String(), name_space, model, cim_object_path) != 0)
    {
        return Ref<Instance>();
    }

    try
    {
        // Get the instance.

        P_CIMInstance cim_instance = 
            context->cimom_handle()->getInstance(
                *context->operation_context(),
                name_space,
                cim_object_path,
                false,
                false,
                false,
                P_CIMPropertyList());

        // Convert to CIMPLE instance.

        Instance* instance = 0;
        const char* ns = "";

        if (Converter::to_cimple_instance(
            ns, cim_instance, model->meta_class, instance) != 0)
        {
            destroy(instance);
            return Ref<Instance>();
        }

        return Ref<Instance>(instance);
    }
    catch (...)
    {
        // Error!
        return Ref<Instance>();
    }
        
    // Unreachable!
    return Ref<Instance>();
}

int Pegasus_Thread_Context::create_instance(
    const char* name_space,
    const Instance* instance)
{
    Pegasus_Thread_Context* context = _top();

    // Convert to Pegasus instance.

    P_CIMInstance cim_instance;

    if (Converter::to_pegasus_instance(
        P_String(), name_space, instance, cim_instance) != 0)
    {
        return Ref<Instance>();
    }

    try
    {
        // Create the instance.

        context->cimom_handle()->createInstance(
            *context->operation_context(),
            name_space,
            cim_instance);

        // Success!
        return 0;
    }
    catch (...)
    {
        // Error!
        return -1;
    }
        
    // Unreachable!
    return -1;
}

int Pegasus_Thread_Context::delete_instance(
    const char* name_space,
    const Instance* model)
{
    Pegasus_Thread_Context* context = _top();

    // Convert to Pegasus object path.

    P_CIMObjectPath cim_object_path;

    if (Converter::to_pegasus_object_path(
        P_String(), name_space, model, cim_object_path) != 0)
    {
        return Ref<Instance>();
    }

    try
    {
        // Delete the instance.

        context->cimom_handle()->deleteInstance(
            *context->operation_context(),
            name_space,
            cim_object_path);

        // Success!
        return 0;
    }
    catch (...)
    {
        // Error!
        return -1;
    }
        
    // Unreachable!
    return -1;
}

int Pegasus_Thread_Context::modify_instance(
    const char* name_space,
    const Instance* instance)
{
    Pegasus_Thread_Context* context = _top();

    // Convert to Pegasus instance.

    P_CIMInstance cim_instance;

    if (Converter::to_pegasus_instance(
        P_String(), name_space, instance, cim_instance) != 0)
    {
        return Ref<Instance>();
    }

    try
    {
        // Create the instance.

        context->cimom_handle()->modifyInstance(
            *context->operation_context(),
            name_space,
            cim_instance,
            false,
            P_CIMPropertyList());

        // Success!
        return 0;
    }
    catch (...)
    {
        // Error!
        return -1;
    }
        
    // Unreachable!
    return -1;
}

int Pegasus_Thread_Context::invoke_method(
    const char* name_space,
    const Instance* instance,
    Instance* meth)
{
    return -1;
}

void Pegasus_Thread_Context::allow_unload(bool flag)
{
    Pegasus_Thread_Context* context = _top();

    if (flag)
        context->cimom_handle()->allowProviderUnload();
    else
        context->cimom_handle()->disallowProviderUnload();
}

bool Pegasus_Thread_Context::get_username(String& user_name)
{
    PENTRY("Pegasus_Thread_Context::get_username");
    // Experimental code to test feasibility of providing a username to
    // the provider.
    Pegasus_Thread_Context* context = _top();

    if (context != 0)
    {
        // Get the pegasus operation context container and find out if
        // it contains the name item

        if (_operation_context->contains(P_IdentityContainer::NAME))
        {
            const P_OperationContext::Container& c =  
                _operation_context->get(P_IdentityContainer::NAME);
    
            const P_IdentityContainer* ic = 
                dynamic_cast<const P_IdentityContainer*>(&c);

            // TBD - We may be able to remove this if statement.
            if (ic)
            {
                user_name = ic->getUserName().getCString();
                PEXITBOOL(true);
                return true;
            }
            else
            {
                // log the error
                CIMPLE_ERR(
                   ("Pegasus_Thread_Context::get_username:"
                    " Identity Container Error"));
            }
        }
    }
    else
        CIMPLE_ERR(("Pegasus_Thread_Context::get_username: Null context found"));

    PEXITBOOL(false);
    return false;
}

CIMPLE_NAMESPACE_END

