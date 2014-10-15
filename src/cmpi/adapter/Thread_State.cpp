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

#include "Thread_State.h"
#include <cimple/cimple.h>
#include <cimple/Thread.h>
#include <pthread.h>
#include <cassert>
#include <cmpidt.h>
#include <cmpift.h>
#include <cmpimacs.h>

CIMPLE_NAMESPACE_BEGIN

static void* _cmpi_thread_create_hook(void* arg)
{
    // This function is called before the thread is created.

    Thread_State* key = Thread_State::get();
    assert(key != 0);

    Thread_State* state = new Thread_State;
    state->broker = key->broker;
    state->context = CBPrepareAttachThread(key->broker, key->context);

    return state;
}

static void* _cmpi_thread_start_hook(void* arg)
{
    // This function is called by the new thread right after it starts.

    Thread_State* state = (Thread_State*)arg;
    Thread_State::push(state->broker, state->context);
    CBAttachThread(state->broker, state->context);

    return state;
}

static void* _cmpi_thread_exit_hook(void* arg)
{
    // This function is called by the new thread after it exits.

    Thread_State* state = (Thread_State*)arg;
    CBDetachThread(state->broker, state->context);
    Thread_State::pop();
    delete state;

    return 0;
}

static pthread_key_t _key;
static pthread_once_t _key_once = PTHREAD_ONCE_INIT;

static void _make_key()
{
    pthread_key_create(&_key, NULL);

    // Install thread hooks (used in src/cimple/Thread.cpp):

    thread_create_hook = _cmpi_thread_create_hook;
    thread_start_hook = _cmpi_thread_start_hook;
    thread_exit_hook = _cmpi_thread_exit_hook;
}

static void _set_key(Thread_State* state)
{
    pthread_once(&_key_once, _make_key);
    pthread_setspecific(_key, state);
}

static Thread_State* _get_key()
{
    return (Thread_State*)pthread_getspecific(_key);
}

Thread_State* Thread_State::get()
{
    return _get_key();
}

void Thread_State::push(
    const CMPIBroker* broker, 
    const CMPIContext* context)
{
    Thread_State* key = _get_key();

    if (!key)
	key = new Thread_State;

    key->broker = broker;
    key->context = context;

    _set_key(key);
}

void Thread_State::pop()
{
    Thread_State* key = _get_key();

    _set_key(0);

    if (key)
	delete key;
}

CIMPLE_NAMESPACE_END
