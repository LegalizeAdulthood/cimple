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

#ifndef _cimple_Thread_Context_h
#define _cimple_Thread_Context_h

#include "config.h"
#include "Instance.h"
#include "Ref.h"

CIMPLE_NAMESPACE_BEGIN

struct Instance_Enumerator_Rep;

class CIMPLE_CIMPLE_LINKAGE Thread_Context
{
public:

    Thread_Context();

    virtual ~Thread_Context();

    virtual Thread_Context* thread_create_hook(void* arg) = 0;

    virtual void thread_start_hook() = 0;

    virtual void thread_exit_hook() = 0;

    virtual Instance_Enumerator_Rep* instance_enumerator_create(
        const char* name_space, 
        const Instance* model) = 0;

    virtual void instance_enumerator_destroy(
        Instance_Enumerator_Rep* rep) = 0;

    virtual bool instance_enumerator_more(
        Instance_Enumerator_Rep* rep) = 0;

    virtual void instance_enumerator_next(
        Instance_Enumerator_Rep* rep) = 0;

    virtual Ref<Instance> instance_enumerator_get(
        Instance_Enumerator_Rep* rep) = 0;

    virtual Ref<Instance> get_instance(
        const char* name_space, 
        const Instance* model) = 0;

    virtual int create_instance(
        const char* name_space, 
        const Instance* instance) = 0;

    virtual int delete_instance(
        const char* name_space, 
        const Instance* instance) = 0;

    virtual int modify_instance(
        const char* name_space, 
        const Instance* instance) = 0;

    virtual int invoke_method(
        const char* name_space, 
        const Instance* instance,
        Instance* meth) = 0;

    virtual void allow_unload(bool flag) = 0;

    virtual bool get_username(String&) = 0;

    static void push(Thread_Context* context);

    static void pop();

    static Thread_Context* top();

    // Pointer to next item on stack (one lower).
    Thread_Context* _next;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Thread_Context_h */
