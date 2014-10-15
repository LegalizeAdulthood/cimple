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

#include <cimple/flags.h>
#include <dirent.h>
#include <dlfcn.h>
#include "Dispatcher.h"
#include <cimple/Mutex.h>
#include <cimple/Auto_Mutex.h>
#include <cimple/Time.h>
#include "Cache.h"
#include <cimple/Error.h>

// ATTN: implement destroy factory method.

CIMPLE_NAMESPACE_BEGIN

//------------------------------------------------------------------------------
//
// Dispatcher::create()
//
//------------------------------------------------------------------------------

Dispatcher* Dispatcher::create(const char* path)
{
    // Create cache (caller should call Error::get() to inquire about
    // error if zero returned).

    Cache* cache = Cache::create(path);

    if (!cache)
        return 0;

    // Create dispatcher:

    Dispatcher* dispatcher = new Dispatcher;
    dispatcher->_cache = cache;

    return dispatcher;
}

//------------------------------------------------------------------------------
//
// Dispatcher::get_instance()
//
//------------------------------------------------------------------------------

Status Dispatcher::get_instance(const Instance* model, Instance*& inst)
{
    inst = 0;

    Envelope* env = _find_provider(model);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    Get_Instance_Status provider_status = env->get_instance(model, inst);

    switch (provider_status)
    {
        case GET_INSTANCE_OK:
            return STATUS_OK;

        case GET_INSTANCE_NOT_FOUND:
            return STATUS_NOT_FOUND;

        case GET_INSTANCE_UNSUPPORTED:
            return STATUS_UNSUPPORTED;
    }

    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::enum_instances()
//
//------------------------------------------------------------------------------

Status Dispatcher::enum_instances(
    const Instance* model, 
    Enum_Instances_Proc proc,
    void* client_data)
{
    // Find provider:

    Envelope* env = _find_provider(model);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    // Invoked provider:

    Enum_Instances_Status provider_status = 
        env->enum_instances(model, proc, client_data);

    switch (provider_status)
    {
        case ENUM_INSTANCES_OK:
            return STATUS_OK;

        case ENUM_INSTANCES_FAILED:
            return STATUS_FAILED;
    }

    // Unreachable!
    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::create_instance()
//
//------------------------------------------------------------------------------

Status Dispatcher::create_instance(const Instance* inst)
{
    Envelope* env = _find_provider(inst);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    Create_Instance_Status provider_status = env->create_instance(inst);

    switch (provider_status)
    {
        case CREATE_INSTANCE_OK:
            return STATUS_OK;

        case CREATE_INSTANCE_DUPLICATE:
            return STATUS_ALREADY_EXISTS;

        case CREATE_INSTANCE_UNSUPPORTED:
            return STATUS_UNSUPPORTED;
    }

    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::delete_instance()
//
//------------------------------------------------------------------------------

Status Dispatcher::delete_instance(const Instance* inst)
{
    Envelope* env = _find_provider(inst);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    Delete_Instance_Status provider_status = env->delete_instance(inst);

    switch (provider_status)
    {
        case DELETE_INSTANCE_OK:
            return STATUS_OK;

        case DELETE_INSTANCE_NOT_FOUND:
            return STATUS_NOT_FOUND;

        case DELETE_INSTANCE_UNSUPPORTED:
            return STATUS_UNSUPPORTED;
    }

    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::modify_instance()
//
//------------------------------------------------------------------------------

Status Dispatcher::modify_instance(const Instance* inst)
{
    Envelope* env = _find_provider(inst);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    Modify_Instance_Status provider_status = env->modify_instance(inst);

    switch (provider_status)
    {
        case MODIFY_INSTANCE_OK:
            return STATUS_OK;

        case MODIFY_INSTANCE_NOT_FOUND:
            return STATUS_NOT_FOUND;

        case MODIFY_INSTANCE_UNSUPPORTED:
            return STATUS_UNSUPPORTED;
    }

    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::enum_associator_names()
//
//------------------------------------------------------------------------------

Status Dispatcher::enum_associator_names(
    const Instance* instance,
    const char* assoc_class,
    const char* result_class,
    const char* role,
    const char* result_role,
    Enum_Associator_Names_Proc proc,
    void* client_data)
{
    // Find provider:

    if (assoc_class == 0)
        return STATUS_FAILED;

    Envelope* env = _find_provider(assoc_class);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    // Delegate to envelope:

    Enum_Associator_Names_Status status = env->enum_associator_names(
        instance, result_class, role, result_role, proc, client_data);

    switch (status)
    {
        case ENUM_ASSOCIATOR_NAMES_OK:
            return STATUS_OK;

        case ENUM_ASSOCIATOR_NAMES_FAILED:
            return STATUS_FAILED;

        case ENUM_ASSOCIATOR_NAMES_UNSUPPORTED:
            return STATUS_FAILED;
    }

    // Unreachable!
    return STATUS_FAILED;
}

//------------------------------------------------------------------------------
//
// Dispatcher::enum_references()
//
//------------------------------------------------------------------------------

Status Dispatcher::enum_references(
    const Instance* instance,
    const Instance* model,
    const char* result_class,
    const char* role,
    Enum_References_Proc proc,
    void* client_data)
{
    // Find provider:

    Envelope* env = _find_provider(result_class);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    // Delegate to envelope:

    Enum_References_Status status = env->enum_references(
        instance, model, role, proc, client_data);

    switch (status)
    {
        case ENUM_REFERENCES_OK:
            return STATUS_OK;

        case ENUM_REFERENCES_FAILED:
            return STATUS_FAILED;

        case ENUM_REFERENCES_UNSUPPORTED:
            return STATUS_FAILED;
    }

    // Unreachable!
    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::enable_indications()
//
//------------------------------------------------------------------------------

Status Dispatcher::enable_indications(
    const char* class_name, 
    Indication_Proc indication_proc,
    void* client_data)
{
    // Find the indication provider for this class:

    Envelope* env = _find_provider(class_name);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    // Enable indications on this provider:

    Enable_Indications_Status provider_status = 
        env->enable_indications(indication_proc, client_data);

    switch (provider_status)
    {
        case ENABLE_INDICATIONS_OK:
            return STATUS_OK;

        case ENABLE_INDICATIONS_FAILED:
            return STATUS_FAILED;
    }

    // Unreachable:
    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::disable_indications()
//
//------------------------------------------------------------------------------

Status Dispatcher::disable_indications(const char* class_name)
{
    // Find the indication provider for this class:

    Envelope* env = _find_provider(class_name);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    // Disable indications on this provider:

    Disable_Indications_Status provider_status = env->disable_indications();

    switch (provider_status)
    {
        case DISABLE_INDICATIONS_OK:
            return STATUS_OK;

        case DISABLE_INDICATIONS_FAILED:
            return STATUS_FAILED;
    }

    // Unreachable:
    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::invoke_method()
//
//------------------------------------------------------------------------------

Status Dispatcher::invoke_method(Instance* inst, Instance* method)
{
    Envelope* env = _find_provider(inst);

    if (!env)
        return STATUS_UNKNOWN_CLASS;

    Auto_Mutex a(env->mutex());

    Invoke_Method_Status provider_status = env->invoke_method(inst, method);

    switch (provider_status)
    {
        case INVOKE_METHOD_OK:
            return STATUS_OK;

        case INVOKE_METHOD_FAILED:
            return STATUS_FAILED;

        case INVOKE_METHOD_UNSUPPORTED:
            return STATUS_UNSUPPORTED;
    }

    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::_find_provider()
//
//------------------------------------------------------------------------------

Envelope* Dispatcher::_find_provider(const Instance* inst)
{
    return _cache->get_provider_by_class(inst->meta_class->name);
}

Envelope* Dispatcher::_find_provider(const char* class_name)
{
    return _cache->get_provider_by_class(class_name);
}

//------------------------------------------------------------------------------
//
// Dispatcher::get_meta_class()
//
//------------------------------------------------------------------------------

const Meta_Class* Dispatcher::get_meta_class(const char* class_name)
{
    return _cache->get_meta_class(class_name);
}

//------------------------------------------------------------------------------
//
// Dispatcher::get_meta_repository()
//
//------------------------------------------------------------------------------

const Meta_Repository* Dispatcher::get_meta_repository()
{
    return _cache->get_meta_repository();
}

//------------------------------------------------------------------------------
//
// Dispatcher::get_meta_method()
//
//------------------------------------------------------------------------------

Status Dispatcher::get_meta_method(
    const char* class_name,
    const char* method_name,
    const Meta_Method*& meta_method)
{
    // Lookup the class.

    const Meta_Class* meta_class = _cache->get_meta_class(class_name);

    if (!meta_class)
        return STATUS_UNKNOWN_CLASS;

    // Lookup the method.

    meta_method = find_method(meta_class, method_name);

    if (!meta_method)
        return STATUS_UNKNOWN_METHOD;

    // Success!
    return STATUS_OK;
}

//------------------------------------------------------------------------------
//
// Dispatcher::make_instance()
//
//------------------------------------------------------------------------------

Status Dispatcher::make_instance(const char* class_name, Instance*& instance)
{
    instance = 0;

    // Get the meta class.

    const Meta_Class* meta_class = get_meta_class(class_name);

    if (!meta_class)
        return STATUS_UNKNOWN_CLASS;

    // Create instance.

    if ((instance = cimple::create(meta_class)))
        return STATUS_OK;

    return STATUS_FAILED;
}

//------------------------------------------------------------------------------
//
// Dispatcher::make_method()
//
//------------------------------------------------------------------------------

Status Dispatcher::make_method(
    const char* class_name, const char* method_name, Instance*& instance)
{
    // Get the meta method.

    const Meta_Method* meta_method;

    Status status = get_meta_method(class_name, method_name, meta_method);

    if (status != STATUS_OK)
        return status;

    // Create instance.

    if ((instance = cimple::create(meta_method)))
        return STATUS_OK;

    return STATUS_FAILED;
}

//------------------------------------------------------------------------------
//
// Dispatcher::num_modules()
//
//------------------------------------------------------------------------------

size_t Dispatcher::num_modules() const
{
    return _cache->num_modules();
}

//------------------------------------------------------------------------------
//
// Dispatcher::num_providers()
//
//------------------------------------------------------------------------------

size_t Dispatcher::num_providers() const
{
    return _cache->num_providers();
}

CIMPLE_NAMESPACE_END
