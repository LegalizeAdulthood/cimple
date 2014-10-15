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

#include <cimple/Array.h>
#include <cassert>
#include <pthread.h>
#include "cimom.h"
#include "Thread_Context.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Instance_Enumerator
//
//==============================================================================

Instance_Enumerator::Instance_Enumerator() : _rep(0)
{
}

Instance_Enumerator::~Instance_Enumerator()
{
    Thread_Context* context = Thread_Context::top();

    if (!context)
        return;

    context->instance_enumerator_destroy(_rep);
}

Instance_Enumerator::operator bool() const
{
    Thread_Context* context = Thread_Context::top();

    if (!context)
        return false;

    return context->instance_enumerator_more(_rep);
}

void Instance_Enumerator::operator++(int)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        context->instance_enumerator_next(_rep);
}

Ref<Instance> Instance_Enumerator::operator()() const
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        return context->instance_enumerator_get(_rep);

    return Ref<Instance>();
}

//==============================================================================
//
// CIMOM
//
//==============================================================================

int cimom::enum_instances(
    const char* name_space, 
    const Instance* model,
    Instance_Enumerator& enumerator)
{
    Thread_Context* context = Thread_Context::top();

    if (!context)
        return -1;

    if (enumerator._rep)
    {
        context->instance_enumerator_destroy(enumerator._rep);
        enumerator._rep = 0;
    }

    enumerator._rep = context->instance_enumerator_create(name_space, model);

    return enumerator._rep ? 0 : -1;
}

int cimom::enum_instances(
    const char* name_space, 
    const Instance* model,
    Array<Instance>& instances)
{
    printf("NOT IMPLEMENTED.\n");
    // absolute assert. Should NEVER be called
    assert(false);
    return 0;
}

Ref<Instance> cimom::get_instance(
    const char* name_space, 
    const Instance* model)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        return context->get_instance(name_space, model);

    return Ref<Instance>();
}

int cimom::create_instance(
    const char* name_space, 
    const Instance* instance)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        return context->create_instance(name_space, instance);

    return -1;
}

int cimom::delete_instance(
    const char* name_space, 
    const Instance* instance)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        return context->delete_instance(name_space, instance);

    return -1;
}

int cimom::modify_instance(
    const char* name_space, 
    const Instance* instance)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        return context->modify_instance(name_space, instance);

    return -1;
}

int cimom::invoke_method(
    const char* name_space, 
    const Instance* instance,
    Instance* meth)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        return context->invoke_method(name_space, instance, meth);

    return -1;
}

void cimom::allow_unload(bool flag)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        context->allow_unload(flag);
}

/* call from the cimom to the thread_context to get
   user information for the operation thread
   (Experimental)
*/
bool cimom::get_username(String& user_name)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
    {
        if(context->get_username(user_name))
        {
            // set string
            return true;
        }
    }
    return false;
}

CIMPLE_NAMESPACE_END

