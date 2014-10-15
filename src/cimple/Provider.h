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

#ifndef _cimple_Provider_h
#define _cimple_Provider_h

#include "config.h"
#include "Property.h"
#include "Instance.h"
#include "Meta_Class.h"
#include "Meta_Property.h"

CIMPLE_NAMESPACE_BEGIN

enum Get_Meta_Class_Status
{
    GET_META_CLASS_OK = 0,
};

enum Create_Provider_Status
{
    CREATE_PROVIDER_OK = 0,
};

enum Destroy_Provider_Status
{
    DESTROY_PROVIDER_OK = 0,
};

enum Load_Status
{
    LOAD_OK = 0,
    LOAD_FAILED = 30,
};

enum Unload_Status
{
    UNLOAD_OK = 0,
    UNLOAD_FAILED = 40,
};

// Deprecated!
enum Timer_Status
{
    TIMER_RESCHEDULE = 0,
    TIMER_CANCEL = 50,
};

enum Get_Instance_Status
{
    GET_INSTANCE_OK = 0,
    GET_INSTANCE_NOT_FOUND = 60,
    GET_INSTANCE_UNSUPPORTED = 61,
};

enum Enum_Instances_Status
{
    ENUM_INSTANCES_OK = 0,
    ENUM_INSTANCES_FAILED = 70,
};

enum Create_Instance_Status
{
    CREATE_INSTANCE_OK = 0,
    CREATE_INSTANCE_DUPLICATE = 80,
    CREATE_INSTANCE_UNSUPPORTED = 81,
};

enum Delete_Instance_Status
{
    DELETE_INSTANCE_OK = 0,
    DELETE_INSTANCE_NOT_FOUND = 90,
    DELETE_INSTANCE_UNSUPPORTED = 91,
};

enum Modify_Instance_Status
{
    MODIFY_INSTANCE_OK = 0,
    MODIFY_INSTANCE_NOT_FOUND = 100,
    MODIFY_INSTANCE_UNSUPPORTED = 101,
};

enum Enum_Associator_Names_Status
{
    ENUM_ASSOCIATOR_NAMES_OK = 0,
    ENUM_ASSOCIATOR_NAMES_FAILED = 110,
    ENUM_ASSOCIATOR_NAMES_UNSUPPORTED = 111,
};

enum Enum_References_Status
{
    ENUM_REFERENCES_OK = 0,
    ENUM_REFERENCES_FAILED = 120,
    ENUM_REFERENCES_UNSUPPORTED = 121,
};

enum Invoke_Method_Status
{
    INVOKE_METHOD_OK = 0,
    INVOKE_METHOD_FAILED = 130,
    INVOKE_METHOD_UNSUPPORTED = 131,
};

enum Enable_Indications_Status
{
    ENABLE_INDICATIONS_OK = 0,
    ENABLE_INDICATIONS_FAILED = 140,
};

enum Disable_Indications_Status
{
    DISABLE_INDICATIONS_OK = 0,
    DISABLE_INDICATIONS_FAILED = 150,
};

enum Get_Repository_Status
{
    GET_REPOSITORY_OK = 0,
};

enum Provider_Operation
{
    OPERATION_GET_META_CLASS,
    OPERATION_CREATE_PROVIDER,
    OPERATION_DESTROY_PROVIDER,
    OPERATION_LOAD,
    OPERATION_UNLOAD,
    OPERATION_GET_INSTANCE,
    OPERATION_ENUM_INSTANCES,
    OPERATION_CREATE_INSTANCE,
    OPERATION_DELETE_INSTANCE,
    OPERATION_MODIFY_INSTANCE,
    OPERATION_INVOKE_METHOD,
    OPERATION_ENABLE_INDICATIONS,
    OPERATION_DISABLE_INDICATIONS,
    OPERATION_GET_REPOSITORY,
    OPERATION_ENUM_ASSOCIATOR_NAMES,
    OPERATION_ENUM_REFERENCES,
};

//==============================================================================
//
// Indication_Handler<>
//
//==============================================================================

struct Instance;

// This function is called repeatedly by an indication provider to deliver 
// indications. It is called one final time with instance equal to zero,
// allowing a chance to perform clean up.
typedef bool (*Indication_Proc)(Instance* instance, void* client_data);

/** This class is used by providers to deliver indications.
*/
template<class CLASS>
class Indication_Handler
{
public:

    Indication_Handler(Indication_Proc proc, void* client_data) :
        _proc(proc), _client_data(client_data) 
    { 
    }

    ~Indication_Handler()
    {
        _proc(0, _client_data);
    }

    /**
    */
    bool handle(CLASS* indication)
    {
        return _proc(indication, _client_data);
    }

private:

    Indication_Proc _proc;
    void* _client_data;
};

//==============================================================================
//
// Enum_Instances_Handler<>
//
//==============================================================================

// ATTN: there is no way to tell the caller to quit calling!

// If instance is null, then status is set:
typedef bool (*Enum_Instances_Proc)(
    Instance* instance, 
    Enum_Instances_Status status,
    void* client_data);

template<class CLASS>
class Enum_Instances_Handler
{
public:

    Enum_Instances_Handler(Enum_Instances_Proc proc, void* client_data) :
        _proc(proc), _client_data(client_data)
    { 
    }

    bool handle(CLASS* instance)
    {
        return _proc(instance, ENUM_INSTANCES_OK, _client_data);
    }

    Enum_Instances_Proc _proc;
    void* _client_data;
};

//==============================================================================
//
// Enum_Associator_Names_Handler<>
//
//==============================================================================

// Called each time a qualifying associator name is found. A null value for
// associator_name indicates the final call (in which status is set). This 
// callback must NOT pass associator_name to destroy(). Also, associator_name 
// is not valid beyond the scope of this function (it is destroyed immediately
// after this callback is invoked).
typedef bool (*Enum_Associator_Names_Proc)(
    const Instance* associator_name,
    Enum_Associator_Names_Status status,
    void* client_data); 

template<class CLASS>
class Enum_Associator_Names_Handler
{
public:

    Enum_Associator_Names_Handler(
        Enum_Associator_Names_Proc proc, void* client_data) :
        _proc(proc), _client_data(client_data)
    {
    }

    bool handle(CLASS* instance)
    {
        return _proc(instance, ENUM_ASSOCIATOR_NAMES_OK, _client_data);
    }

    Enum_Associator_Names_Proc _proc;
    void* _client_data;
};

//==============================================================================
//
// Enum_References_Handler<>
//
//==============================================================================

// Called each time a qualifying reference is found. A null value for
// reference indicates the final call. This callback must pass
// reference to destroy().
typedef bool (*Enum_References_Proc)(
    Instance* reference,
    Enum_References_Status status,
    void* client_data);

template<class CLASS>
class Enum_References_Handler
{
public:

    Enum_References_Handler(Enum_References_Proc proc, void* client_data) :
        _proc(proc), _client_data(client_data)
    {
    }

    bool handle(CLASS* instance)
    {
        return _proc(instance, ENUM_REFERENCES_OK, _client_data);
    }

    Enum_References_Proc _proc;
    void* _client_data;
};

//==============================================================================
//
// Provider_Proc()
//
//==============================================================================

struct Registration;

typedef int (*Provider_Proc)(
    const Registration* registration,
    int operation, 
    void* arg0, 
    void* arg1, 
    void* arg2, 
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7);

// Operations common to all provider types (i.e., instance providers and
// association providers).
template<class PROVIDER>
class Provider_Proc_Common_T
{
public:

    typedef typename PROVIDER::Class CLASS;

    static int proc(
        const Registration* registration,
        int operation, 
        void* arg0, 
        void* arg1, 
        void* arg2, 
        void* arg3, 
        void* arg4, 
        void* arg5, 
        void* arg6, 
        void* arg7)
    {
        switch (operation)
        {
            case OPERATION_GET_META_CLASS:
            {
                *((Meta_Class**)arg0) = (Meta_Class*)&CLASS::static_meta_class;
                return GET_META_CLASS_OK;
            }

            case OPERATION_CREATE_PROVIDER:
            {
                *((PROVIDER**)arg0) = new PROVIDER;
                return CREATE_PROVIDER_OK;
            }

            case OPERATION_DESTROY_PROVIDER:
            {
                delete (PROVIDER*)arg0;
                return DESTROY_PROVIDER_OK;
            }

            case OPERATION_LOAD:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->load();
            }

            case OPERATION_UNLOAD:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->unload();
            }

            case OPERATION_GET_REPOSITORY:
            {
                const Meta_Repository*& meta_repository = 
                    *((const Meta_Repository**)arg0);

                const Meta_Class* mc = (Meta_Class*)&CLASS::static_meta_class;

                meta_repository = mc->meta_repository;

                return GET_REPOSITORY_OK;
            }

            default:
            {
                // Not handled!
                return -1;
            }
        }
    }
};

// Instance/Method provider proc.
template<class PROVIDER>
class Provider_Proc_T
{
public:

    typedef typename PROVIDER::Class CLASS;

    static int proc(
        const Registration* registration,
        int operation, 
        void* arg0, 
        void* arg1, 
        void* arg2, 
        void* arg3, 
        void* arg4, 
        void* arg5, 
        void* arg6, 
        void* arg7)
    {
        switch (operation)
        {
            case OPERATION_GET_META_CLASS:
            case OPERATION_CREATE_PROVIDER:
            case OPERATION_DESTROY_PROVIDER:
            case OPERATION_LOAD:
            case OPERATION_UNLOAD:
            case OPERATION_GET_REPOSITORY:
            {
                return Provider_Proc_Common_T<PROVIDER>::proc(registration,
                    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }

            case OPERATION_GET_INSTANCE:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->get_instance(
                    (const CLASS*)arg1, *((CLASS**)arg2));
            }

            case OPERATION_ENUM_INSTANCES:
            {
                PROVIDER* provider = (PROVIDER*)arg0;

                Enum_Instances_Handler<CLASS> handler(
                    (Enum_Instances_Proc)arg2, (void*)arg3);
                        
                Enum_Instances_Status status = provider->enum_instances(
                    (const CLASS*)arg1, &handler);

                handler._proc(0, status, handler._client_data);

                return status;
            }

            case OPERATION_CREATE_INSTANCE:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->create_instance((const CLASS*)arg1);
            }

            case OPERATION_DELETE_INSTANCE:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->delete_instance((const CLASS*)arg1);
            }

            case OPERATION_MODIFY_INSTANCE:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->modify_instance((const CLASS*)arg1);
            }

            default:
            {
                // Not handled!
                return -1;
            }
        }
    }
};

template<class PROVIDER>
class Indication_Provider_Proc_T
{
public:

    typedef typename PROVIDER::Class CLASS;
    typedef Indication_Handler<CLASS> INDICATION_HANDLER;

    static int proc(
        const Registration* registration,
        int operation, 
        void* arg0, 
        void* arg1, 
        void* arg2, 
        void* arg3, 
        void* arg4, 
        void* arg5, 
        void* arg6, 
        void* arg7)
    {
        switch (operation)
        {
            case OPERATION_GET_META_CLASS:
            case OPERATION_CREATE_PROVIDER:
            case OPERATION_DESTROY_PROVIDER:
            case OPERATION_LOAD:
            case OPERATION_UNLOAD:
            case OPERATION_GET_REPOSITORY:
            {
                return Provider_Proc_Common_T<PROVIDER>::proc(registration,
                    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }

            case OPERATION_ENABLE_INDICATIONS:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                Indication_Proc indication_proc = (Indication_Proc)arg1;
                void* client_data = arg2;

                INDICATION_HANDLER* indication_handler = new INDICATION_HANDLER(
                    indication_proc, client_data);
                return provider->enable_indications(indication_handler);
            }

            case OPERATION_DISABLE_INDICATIONS:
            {
                PROVIDER* provider = (PROVIDER*)arg0;
                return provider->disable_indications();
            }

            default:
            {
                // Not handled!
                return -1;
            }
        }
    }
};

template<class PROVIDER>
class Association_Provider_Proc_T
{
public:

    typedef typename PROVIDER::Class CLASS;

    static int proc(
        const Registration* registration,
        int operation, 
        void* arg0, 
        void* arg1, 
        void* arg2, 
        void* arg3, 
        void* arg4, 
        void* arg5, 
        void* arg6, 
        void* arg7)
    {
        switch (operation)
        {
            case OPERATION_GET_META_CLASS:
            case OPERATION_CREATE_PROVIDER:
            case OPERATION_DESTROY_PROVIDER:
            case OPERATION_LOAD:
            case OPERATION_UNLOAD:
            case OPERATION_GET_REPOSITORY:
            case OPERATION_GET_INSTANCE:
            case OPERATION_ENUM_INSTANCES:
            case OPERATION_CREATE_INSTANCE:
            case OPERATION_DELETE_INSTANCE:
            case OPERATION_MODIFY_INSTANCE:
            {
                return Provider_Proc_T<PROVIDER>::proc(registration,
                    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }

            case OPERATION_ENUM_ASSOCIATOR_NAMES:
            {
                // arg0: provider
                // arg1: instance
                // arg2: result_class
                // arg3: role
                // arg4: result_role
                // arg5: proc
                // arg6: client_data

                PROVIDER* provider = (PROVIDER*)arg0;

                Enum_Associator_Names_Handler<Instance> handler(
                    (Enum_Associator_Names_Proc)arg5, (void*)arg6);

                Enum_Associator_Names_Status status = 
                    provider->enum_associator_names(
                        (const Instance*)arg1, /* instance */
                        *((const String*)arg2), /* result_class */
                        *((const String*)arg3), /* role */
                        *((const String*)arg4), /* result_role */
                        &handler);

                // ATTN: a hack for now since otherwise the user's
                // callback would be called here and by the Provider_Handle
                // method with the same name as well.
                if (status != ENUM_ASSOCIATOR_NAMES_UNSUPPORTED)
                    handler._proc(0, status, handler._client_data);

                return status;
            }

            case OPERATION_ENUM_REFERENCES:
            {
                // arg0: provider
                // arg1: instance
                // arg2: model
                // arg3: role
                // arg4: proc
                // arg5: client_data

                PROVIDER* provider = (PROVIDER*)arg0;

                Enum_References_Handler<CLASS> handler(
                    (Enum_References_Proc)arg4, (void*)arg5);

                Enum_References_Status status = 
                    provider->enum_references(
                        (const Instance*)arg1, /* instance */
                        (const CLASS*)arg2, /* model */
                        *((const String*)arg3), /* role */
                        &handler);

                // ATTN: a hack for now since otherwise the user's
                // callback would be called here and by the Provider_Handle
                // method with the same name as well.
                if (status != ENUM_REFERENCES_UNSUPPORTED)
                    handler._proc(0, status, handler._client_data);

                return status;
            }

            default:
            {
                // Not handled!
                return -1;
            }
        }
    }
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Provider_h */
