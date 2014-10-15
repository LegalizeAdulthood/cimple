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

#ifndef _cimple_Provider2_h
#define _cimple_Provider2_h

#include "config.h"
#include "Provider.h"

CIMPLE_NAMESPACE_BEGIN

template<class HANDLE>
class Provider2
{
public:

    typedef Provider2<HANDLE> This;
    typedef typename HANDLE::Class Class;
    typedef typename HANDLE::REFERENCE REFERENCE;

    Provider2()
    {
    }

    virtual ~Provider2()
    {
    }

    virtual Load_Status load()
    {
        return LOAD_OK;
    }

    virtual Unload_Status unload()
    {
        return UNLOAD_OK;
    }

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
                *((Meta_Class**)arg0) = (Meta_Class*)&Class::static_meta_class;
                return GET_META_CLASS_OK;
            }

            case OPERATION_CREATE_PROVIDER:
            {
                *((This**)arg0) = new This;
                return CREATE_PROVIDER_OK;
            }

            case OPERATION_DESTROY_PROVIDER:
            {
                delete (This*)arg0;
                return DESTROY_PROVIDER_OK;
            }

            case OPERATION_LOAD:
            {
                This* provider = (This*)arg0;
                return provider->load();
            }

            case OPERATION_UNLOAD:
            {
                This* provider = (This*)arg0;
                return provider->unload();
            }

            case OPERATION_GET_REPOSITORY:
            {
                const Meta_Repository*& meta_repository = 
                    *((const Meta_Repository**)arg0);

                const Meta_Class* mc = (Meta_Class*)&Class::static_meta_class;

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

template<class HANDLE>
class Instance_Provider2 : public Provider2<HANDLE>
{
public:

    typedef Instance_Provider2<HANDLE> This;
    typedef typename HANDLE::Class Class;
    typedef typename HANDLE::REFERENCE REFERENCE;

    Instance_Provider2()
    {
    }

    virtual ~Instance_Provider2()
    {
    }

    virtual Get_Instance_Status get_instance(
        const REFERENCE& reference,
        const HANDLE& instance)
    {
        return GET_INSTANCE_UNSUPPORTED;
    }

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
                return Provider2<HANDLE>::proc(registration,
                    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }

            case OPERATION_GET_INSTANCE:
            {
                This* provider = (This*)arg0;
                const Class* inst = (const Class*)arg1;
                ref(inst);
                REFERENCE reference((Class*)inst);
                HANDLE instance;
                Get_Instance_Status status = 
                    provider->get_instance(reference, instance);

                ref(*((Class**)arg2) = (Class*)instance.instance());
                return status;
            }

#if 0
            case OPERATION_ENUM_INSTANCES:
            {
                This* provider = (This*)arg0;

                Enum_Instances_Handler<Class> handler(
                    (Enum_Instances_Proc)arg2, (void*)arg3);
                        
                Enum_Instances_Status status = provider->enum_instances(
                    (const Class*)arg1, &handler);

                handler._proc(0, status, handler._client_data);

                return status;
            }

            case OPERATION_CREATE_INSTANCE:
            {
                This* provider = (This*)arg0;
                return provider->create_instance((Class*)arg1);
            }

            case OPERATION_DELETE_INSTANCE:
            {
                This* provider = (This*)arg0;
                return provider->delete_instance((const Class*)arg1);
            }

            case OPERATION_MODIFY_INSTANCE:
            {
                This* provider = (This*)arg0;
                return provider->modify_instance(
                    (const Class*)arg1,
                    (const Class*)arg2);
            }

#endif
            default:
            {
                // Not handled!
                return -1;
            }
        }
    }
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Provider2_h */
