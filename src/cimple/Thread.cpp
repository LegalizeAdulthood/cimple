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

#include <cassert>
#include "Thread.h"
#include "Thread_Context.h"
#include <pthread.h>

CIMPLE_NAMESPACE_BEGIN

// Structure defining argument to _thread_proc
struct Arg
{
    Thread_Proc proc;
    void* arg;
    Thread_Context* context;
};

static void* _thread_proc(void* arg_)
{
    Thread_Proc proc = ((Arg*)arg_)->proc;
    Thread_Context* context = ((Arg*)arg_)->context;
    void* arg = ((Arg*)arg_)->arg;
    delete (Arg*)arg_;

    // Push context if any.

    if (context)
        Thread_Context::push(context);

    // Invoke start hook.

    if (context)
        context->thread_start_hook();

    // Invoke thread routine.

    void* return_value = proc(arg);

    // Invoke exit hook.

    if (context)
        context->thread_exit_hook();

    // Pop context.

    assert(context == Thread_Context::top());

    if (context)
    {
        Thread_Context::pop();
        delete context;
    }

    return return_value;
}

Thread::Thread()
{
    assert(sizeof(pthread_t) <= sizeof(_rep));
    memset(_rep, 0, sizeof(_rep));
}

Thread::Thread(const Thread& x)
{
    *((pthread_t*)_rep) = *((pthread_t*)x._rep);
}

Thread::~Thread()
{
}

Thread& Thread::operator=(const Thread& x)
{
    if (&x != this)
        *((pthread_t*)_rep) = *((pthread_t*)x._rep);

    return *this;
}

// local function to create a thread. 
int _create(
    Thread& thread, Thread_Proc user_proc, void* arg_, bool detached)
{
    // Create arg object.

    Arg* arg = new Arg;
    memset(arg, 0, sizeof(Arg));
    arg->proc = user_proc;
    arg->arg = arg_;

    // Call create hook.

    Thread_Context* context = Thread_Context::top();

    if (context)
        arg->context = context->thread_create_hook(arg_);
    else
        arg->context = 0;

    // Create the thread.

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    if (detached)
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    else
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int status = pthread_create(
        (pthread_t*)&thread, &attr, _thread_proc, arg);

    pthread_attr_destroy(&attr);

    // Clean up if thread create failed.

    if (status != 0)
    {
        delete context;
        delete arg;
    }

    return status;
}

int Thread::create_joinable(
    Thread& thread, Thread_Proc user_proc, void* arg)
{
    return _create(thread, user_proc, arg, false);
}

int Thread::create_detached(
    Thread& thread, Thread_Proc user_proc, void* arg)
{
    return _create(thread, user_proc, arg, true);
}

void Thread::exit(void* return_value)
{
    Thread_Context* context = Thread_Context::top();

    if (context)
        context->thread_exit_hook();

    pthread_exit(return_value);
}

int Thread::join(Thread& thread, void*& value_ptr)
{
    value_ptr = 0;
    return pthread_join(*((pthread_t*)thread._rep), &value_ptr);
}

Thread Thread::self()
{
    Thread thread;
    *((pthread_t*)thread._rep) = pthread_self();

    return thread;
}

bool Thread::equal(const Thread& t1, const Thread& t2)
{
    return pthread_equal(*((pthread_t*)t1._rep), *((pthread_t*)t2._rep));
}

CIMPLE_NAMESPACE_END

