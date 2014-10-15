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

#ifndef _CMPI_Thread_Context_h
#define _CMPI_Thread_Context_h

#include <cimple/Thread_Context.h>
#include "cmpi.h"

CIMPLE_NAMESPACE_BEGIN

class CMPI_Adapter;

class CMPI_Thread_Context : public Thread_Context
{
public:

    CMPI_Thread_Context(
        const CMPIBroker* cmpi_broker,
        const CMPIContext* cmpi_context,
        CMPI_Adapter* cmpi_adapter);

    virtual ~CMPI_Thread_Context();

    const CMPIBroker* cmpi_broker() const
    {
        return _cmpi_broker;
    }

    const CMPIContext* cmpi_context() const
    {
        return _cmpi_context;
    }

    CMPI_Adapter* cmpi_adapter() const
    {
        return _cmpi_adapter;
    }

    virtual Thread_Context* thread_create_hook(void* arg);

    virtual void thread_start_hook();

    virtual void thread_exit_hook();

    virtual Instance_Enumerator_Rep* instance_enumerator_create(
        const char* name_space, 
        const Instance* model);

    virtual void instance_enumerator_destroy(
        Instance_Enumerator_Rep* rep);

    virtual bool instance_enumerator_more(
        Instance_Enumerator_Rep* rep);

    virtual void instance_enumerator_next(
        Instance_Enumerator_Rep* rep);

    virtual Ref<Instance> instance_enumerator_get(
        Instance_Enumerator_Rep* rep);

    virtual Ref<Instance> get_instance(
        const char* name_space, 
        const Instance* model);

    virtual int create_instance(
        const char* name_space, 
        const Instance* instance);

    virtual int delete_instance(
        const char* name_space, 
        const Instance* instance);

    virtual int modify_instance(
        const char* name_space, 
        const Instance* instance);

    virtual int invoke_method(
        const char* name_space,
        const Instance* instance,
        Instance* meth);

    virtual void allow_unload(bool flag);

    virtual bool get_username(String&);

private:

    const CMPIBroker* _cmpi_broker;
    const CMPIContext* _cmpi_context;
    CMPI_Adapter* _cmpi_adapter;
};

class CMPI_Thread_Context_Pusher
{
public:

    CMPI_Thread_Context_Pusher(
        const CMPIBroker* cmpi_broker, 
        const CMPIContext* cmpi_context,
        CMPI_Adapter* cmpi_adpater)
    {
        CIMPLE_ASSERT(cmpi_broker);
        CIMPLE_ASSERT(cmpi_context);
        CIMPLE_ASSERT(cmpi_adpater);
        _context = new CMPI_Thread_Context(
            cmpi_broker, cmpi_context, cmpi_adpater);
        Thread_Context::push(_context);
    }

    ~CMPI_Thread_Context_Pusher()
    {
        CIMPLE_ASSERT(Thread_Context::top() == _context);
        Thread_Context::pop();
        delete _context;
    }

private:

    CMPI_Thread_Context* _context;
};

CIMPLE_NAMESPACE_END

#endif /* _CMPI_Thread_Context_h */
