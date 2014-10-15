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
#include <pthread.h>

CIMPLE_NAMESPACE_BEGIN

void* (*thread_create_hook)(void*);
void* (*thread_start_hook)(void*);
void* (*thread_exit_hook)(void*);

struct Arg
{
    Thread_Proc proc;
    void* arg;
    void* create_hook_return_value;
};

static void* _thread_proc(void* arg_)
{
    Arg* arg = (Arg*)arg_;

    void* start_hook_return_value;

    if (thread_start_hook)
    {
	start_hook_return_value = 
	    (*thread_start_hook)(arg->create_hook_return_value);
    }
    else
	start_hook_return_value = 0;

    void* return_value = arg->proc(arg->arg);
    delete arg;

    if (thread_exit_hook)
	(*thread_exit_hook)(start_hook_return_value);

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

int Thread::create(Thread& thread, Thread_Proc user_proc, void* user_arg)
{
    Arg* arg = new Arg;
    arg->proc = user_proc;
    arg->arg = user_arg;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (thread_create_hook)
	arg->create_hook_return_value = (*thread_create_hook)(user_arg);
    else
	arg->create_hook_return_value = 0;

    int status = pthread_create(
	((pthread_t*)thread._rep), &attr, _thread_proc, arg);

    pthread_attr_destroy(&attr);

    if (status != 0)
	delete arg;

    return status;
}

void Thread::exit(void* return_value)
{
    pthread_exit(return_value);
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
