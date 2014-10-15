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

#include "Provider_Handle.h"

CIMPLE_NAMESPACE_BEGIN

namespace enum_associator_names
{
    struct Args
    {
	const Instance* instance;
	const char* result_class;
	const char* role;
	const char* result_role;
	Enum_Associator_Names_Proc proc;
	void* client_data;
    };

    // This function is called for each instance of the given association 
    // provider.
    static bool _proc(
	Instance* assoc_instance, 
	Enum_Instances_Status status, 
	void* client_data)
    {
	Args* args = (Args*)client_data;

	if (!assoc_instance)
	    return false;

	// Get the associator names of args->instance with respect to
	// assoc_instance.

	const Instance* associator_names[CIMPLE_MAX_REFERENCES_PER_CLASS];

	ssize_t r = get_associators(
	    args->instance, 
	    assoc_instance,
	    args->result_class, 
	    args->role, 
	    args->result_role, 
	    associator_names);

	// Call user's callback for each associator name found (if any).

	for (ssize_t i = 0; i < r; i++)
	    args->proc(associator_names[i], args->client_data);

	destroy(assoc_instance);

	// Keep them coming!
	return true;
    }
};

Enum_Associator_Names_Status Provider_Handle::enum_associator_names(
    const Instance* instance,
    const char* result_class,
    const char* role,
    const char* result_role,
    Enum_Associator_Names_Proc proc,
    void* client_data)
{
    // Get meta class:

    const Meta_Class* mc;
    get_meta_class(mc);

    // Disallow operation on non-association providers.

    if (!(mc->flags & CIMPLE_FLAG_ASSOCIATION))
	return ENUM_ASSOCIATOR_NAMES_FAILED;

    // Save arguments to pass to callback.

    enum_associator_names::Args args;
    args.instance = instance;
    args.result_class = result_class;
    args.role = role;
    args.result_role = result_role;
    args.proc = proc;
    args.client_data = client_data;

    // Create the model:

    Instance* model = create(mc);
    nullify_non_keys(model);

    // Enumerate the association provider.

    Enum_Instances_Status status = enum_instances(
	model, enum_associator_names::_proc , &args);

    // Call one last time to signal the end:

    proc(0, client_data);

    // Destroy the association model.

    destroy(model);

    switch (status)
    {
	case ENUM_INSTANCES_FAILED:
	    return ENUM_ASSOCIATOR_NAMES_FAILED;

	case ENUM_INSTANCES_OK:
	    return ENUM_ASSOCIATOR_NAMES_OK;
    }

    // Unreachable!
    return ENUM_ASSOCIATOR_NAMES_OK;
}

namespace enum_references
{
    struct Args
    {
	const Instance* instance;
	const char* role;
	Enum_References_Proc proc;
	void* client_data;
    };

    static bool _proc(
	Instance* reference, 
	Enum_Instances_Status status, 
	void* client_data)
    {
	// This function is called for each instance of the given association 
	// provider.

	Args* args = (Args*)client_data;

	// Ignore the final call.

	if (!reference)
	    return false;

	// If this association instance is a reference of our original instance,
	// then call the user's callback:

	if (is_reference_of(args->instance, reference, args->role))
	    args->proc(reference, args->client_data);
	else
	    destroy(reference);

	// Keep them coming!
	return true;
    }
}

Enum_References_Status Provider_Handle::enum_references(
    const Instance* instance,
    const char* role,
    bool keys_only,
    Enum_References_Proc proc,
    void* client_data)
{
    // Get meta class:

    const Meta_Class* mc;
    get_meta_class(mc);

    // Disallow this operation on non-association providers.

    if (!(mc->flags & CIMPLE_FLAG_ASSOCIATION))
	return ENUM_REFERENCES_FAILED;

    // Create the reference model to be enumerated.

    Instance* model = cimple::create(mc);

    if (keys_only)
	nullify_non_keys(model);

    // If this is the initial call of the enumeration, create the args object.

    enum_references::Args args;
    args.instance = instance;
    args.role = role;
    args.proc = proc;
    args.client_data = client_data;

    // Enumerate instances of this association provider while looking for an 
    // association instance that involves the instance parameter.

    Enum_Instances_Status status = enum_instances(
	model, enum_references::_proc, &args);

    // Call one last time to signal the end:

    proc(0, client_data);

    // Destroy the model:

    destroy(model);

    // Return status:

    switch (status)
    {
	case ENUM_INSTANCES_OK:
	    return ENUM_REFERENCES_OK;

	case ENUM_INSTANCES_FAILED:
	    return ENUM_REFERENCES_FAILED;
    }

    return ENUM_REFERENCES_OK;
}

namespace get_instance
{
    struct Data
    {
	const Instance* model;
	Instance* instance;
    };

    static bool _proc(
	Instance* instance, 
	Enum_Instances_Status status, 
	void* client_data)
    {
	Data* data = (Data*)client_data;

	if (!instance)
	    return false;

	if (key_eq(data->model, instance))
	{
	    // ATTN: filter instance by model here!
	    data->instance = instance;
	    return false;
	}
	else
	    destroy(instance);

	// Keep them coming!
	return true;
    }
}

Get_Instance_Status Provider_Handle::get_instance(
    const Instance* model,
    Instance*& instance)
{
    // Use OPERATION_GET_INSTANCE:

    Get_Instance_Status get_instance_status = (Get_Instance_Status)_proc(
	OPERATION_GET_INSTANCE, _provider, (void*)model, &instance, 0);

    if (get_instance_status != GET_INSTANCE_UNSUPPORTED)
	return get_instance_status;

    // Use OPERATION_ENUM_INSTANCES:

    get_instance::Data data;
    data.model = model;
    data.instance = 0;

    Enum_Instances_Status enum_instance_status = enum_instances(
	model, get_instance::_proc, &data);

    if (enum_instance_status == ENUM_INSTANCES_OK && data.instance)
    {
	instance = data.instance;
	return GET_INSTANCE_OK;
    }

    // Not found!
    return GET_INSTANCE_NOT_FOUND;
}

CIMPLE_NAMESPACE_END
