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

#ifndef _cimple_Dispatcher_h
#define _cimple_Dispatcher_h

#include <cimple/Instance.h>
#include <cimple/Provider.h>
#include "Status.h"
#include "State.h"
#include <cimple/Error.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

class Cache;
class Envelope;

/** The dispatcher is the main API to the CIMPLE CIM engine. It maintains a the 
    collection of providers and dispatches CIM operations to them.
*/
class CIMPLEDISP_LINKAGE Dispatcher
{
public:

    const Meta_Class* get_meta_class(
	const char* class_name);

    Status get_meta_method(
	const char* class_name,
	const char* method_name,
	const Meta_Method*& meta_method);

    Status get_instance(
	const Instance* model, 
	Instance*& inst);

    Status enum_instances(
	const Instance* model, 
	Enum_Instances_Proc proc,
	void* client_data);

    Status create_instance(
	const Instance* instance);

    Status delete_instance(
	const Instance* instance);

    Status modify_instance(
	const Instance* instance);

    Status enum_associator_names(
	const Instance* instance,
	const char* assoc_class,
	const char* result_class,
	const char* role,
	const char* result_role,
	Enum_Associator_Names_Proc proc,
	void* client_data);

    Status enum_references(
	const Instance* instance,
	const Instance* model,
	const char* result_class,
	const char* role,
	Enum_References_Proc proc,
	void* client_data);

    Status enable_indications(
	const char* class_name, 
	Indication_Proc indication_proc, 
	void* client_data);

    Status disable_indications(
	const char* class_name);

    Status invoke_method(
	Instance* instance, 
	Instance* method);

    Status make_instance(
	const char* class_name, 
	Instance*& instance);

    Status make_method(
	const char* class_name, 
	const char* method_name, 
	Instance*& instance);

    /** Creates Dispatcher instance.
	@param path directory holding provider libraries.
	@return new dispatcher instance.
    */
    static Dispatcher* create(const char* path);

    void dump() const;

    size_t num_modules() const;

    size_t num_providers() const;

#ifdef CIMPLE_USE_SYNCHRONOUS_DISPATCHER_METHODS

    /** Synchronous version enum_instances(). The asynchronous version of
	this function is faster since it requires no thread synchronization.
    */
    Status enum_instance(
	const Instance* model, 
	Instance*& instance_out,
	State& state);

    /** Synchronous version of enum_associator_names(). The asynchronous 
	version of this function is faster since it requires no thread 
	synchronization.
    */
    Status enum_associator_name(
	const Instance* instance,
	const char* assoc_class,
	const char* result_class,
	const char* role,
	const char* result_role,
	Instance*& assoc_name_out,
	State& state); 

    /** Synchronous version of enum_references(). The asynchronous version of 
	this function is faster since it requires no thread synchronization.
    */
    Status enum_reference(
	const Instance* instance,
	const char* result_class,
	const char* role,
	bool keys_only,
	Instance*& reference_out,
	State& state);

#endif /* CIMPLE_USE_SYNCHRONOUS_DISPATCHER_METHODS */

private:

    Dispatcher() { }

    ~Dispatcher() { }

    Envelope* _find_provider(const Instance* inst);

    Envelope* _find_provider(const char* class_name);

    Cache* _cache;

    friend struct __Dummy;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Dispatcher_h */
