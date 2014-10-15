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

#include "pthread.h"
#include <cassert>
#include <cstdio>
#include <windows.h>

POSIX_NAMESPACE_BEGIN

//==============================================================================
//
// pthread_mutex_t
//
//==============================================================================

struct pthread_mutex_rep_t
{
    HANDLE handle;
    size_t count;
};

pthread_mutex_t::pthread_mutex_t(pthread_mutex_initializer_t)
{
    pthread_mutex_init(this, NULL);
}

int pthread_mutex_init(
    pthread_mutex_t* mutex,
    const pthread_mutexattr_t* attr)
{
    assert(sizeof(pthread_mutex_t) >= sizeof(pthread_mutex_rep_t));

    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;
    rep->count = 0;

    if ((rep->handle = CreateMutex(NULL, FALSE, NULL)) == NULL)
	return -1;

    return 0;
}

int pthread_mutex_destroy(
    pthread_mutex_t* mutex)
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    if (!CloseHandle(rep->handle))
	return -1;

    return 0;
}

int pthread_mutex_lock(
    pthread_mutex_t* mutex)
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    if (WaitForSingleObject(rep->handle, INFINITE) == WAIT_FAILED)
	return -1;

    rep->count++;

    return 0;
}

int pthread_mutex_unlock(
    pthread_mutex_t* mutex)
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    assert(rep->count > 0);
    rep->count--;

    if (!ReleaseMutex(rep->handle))
	return -1;

    return 0;
}


int pthread_mutexattr_init(
    pthread_mutexattr_t* attr)
{
    memset(attr, 0, sizeof(pthread_mutexattr_t));
    return 0;
}

int pthread_mutexattr_destroy(
    pthread_mutexattr_t* attr)
{
    return 0;
}

int pthread_mutexattr_settype(
    pthread_mutexattr_t* attr,
    int kind)
{
    // There is nothing to do here. All mutexes are recursive in Windows
    // so it does not matter whether the kind is PTHREAD_MUTEX_FAST_NP
    // or PTHREAD_MUTEX_RECURSIVE_NP.
    return 0;
}

//==============================================================================
//
// pthread_once_t
//
//==============================================================================

struct pthread_once_rep_t 
{
    int initialized;
    pthread_mutex_t mutex;
};

pthread_once_t::pthread_once_t(pthread_once_init_t)
{
    assert(sizeof(pthread_once_t) >= sizeof(pthread_once_rep_t));
    pthread_once_rep_t* rep = (pthread_once_rep_t*)this;

    rep->initialized = 0;
    pthread_mutex_init(&rep->mutex, NULL);
}

int pthread_once(
    pthread_once_t* once_control, 
    void (*init_routine)(void))
{
    assert(sizeof(pthread_once_t) >= sizeof(pthread_once_rep_t));
    pthread_once_rep_t* rep = (pthread_once_rep_t*)once_control;

    if (rep->initialized == 0)
    {
	pthread_mutex_lock(&rep->mutex);

	if (rep->initialized == 0)
	    (*init_routine)();

	pthread_mutex_unlock(&rep->mutex);
    }

    return 0;
}

//==============================================================================
//
// pthread_key_t
//
//==============================================================================

// ATTN: Implement pthread_once() behavior

struct pthread_key_rep_t
{
    DWORD index;
};

int pthread_key_create(
    pthread_key_t* key, 
    void (*destructor)(void*))
{
    assert(sizeof(pthread_key_t) >= sizeof(pthread_key_rep_t));
    assert(destructor == NULL);

    pthread_key_rep_t* rep = (pthread_key_rep_t*)key;

    // No support for destructor.

    if (destructor)
	return -1;

    // Create TLS key.

    if ((rep->index = TlsAlloc()) == TLS_OUT_OF_INDEXES)
	return -1;

    return 0;
}

int pthread_key_delete(
    pthread_key_t key)
{
    pthread_key_rep_t* rep = (pthread_key_rep_t*)&key;

    if (!TlsFree(rep->index))
	return -1;

    return 0;
}

int pthread_setspecific(
    pthread_key_t key, 
    const void* value)
{
    pthread_key_rep_t* rep = (pthread_key_rep_t*)&key;

    if (!TlsSetValue(rep->index, (void*)value))
	return -1;

    return 0;
}

void* pthread_getspecific(
    pthread_key_t key)
{
    pthread_key_rep_t* rep = (pthread_key_rep_t*)&key;

    return TlsGetValue(rep->index);
}

//==============================================================================
//
// pthread_t
//
//==============================================================================

// For the main thread, start_routine and arg are NULL.
struct pthread_rep_t
{
    void* (*start_routine)(void*);
    void* arg;
    HANDLE event;
    HANDLE handle;
    pthread_rep_t* next;
};

struct pthread_attr_rep_t
{
    int detachstate;
};

static pthread_once_t _pthread_self_once = PTHREAD_ONCE_INIT;
static pthread_key_t _pthread_self_key;

static void _create_pthread_self_key()
{
    pthread_key_create(&_pthread_self_key, NULL);
}

static DWORD WINAPI _proc(LPVOID arg) 
{
    pthread_rep_t* rep = (pthread_rep_t*)arg;

    // Set rep into thread local storage.

    if (pthread_setspecific(_pthread_self_key, rep) != 0)
    {
	assert(0);
	CloseHandle(rep->event);
	delete rep;
	return 0;
    }

    // Run thread procedure passed to Threads::create().

    void* return_value = (*rep->start_routine)(rep->arg);

    // ATTN: clean up!

    delete rep;

    return (DWORD)return_value;
}

int pthread_create(
    pthread_t* thread, 
    const pthread_attr_t* attr,
    void* (*start_routine)(void*), 
    void* arg)
{
    // Only detached threads are supported.

    pthread_attr_rep_t* attr_rep = (pthread_attr_rep_t*)attr;

    if (!attr_rep || attr_rep->detachstate != PTHREAD_CREATE_DETACHED)
	return -1;

    // Initialize _pthread_self_key.

    if (pthread_once(&_pthread_self_once, _create_pthread_self_key) != 0)
	return -1;

    // Create rep object.

    pthread_rep_t* rep = new pthread_rep_t;

    // Save start_routine and arg.

    rep->start_routine = start_routine;
    rep->arg = arg;
    rep->next = 0;

    // Create an event to be used by the condition variable implementation.

    if ((rep->event = CreateEvent(0, TRUE, FALSE, 0)) == NULL)
    {
	delete rep;
	return -1;
    }

    // Create thread:

    if ((rep->handle = CreateThread(NULL, 0, _proc, rep, 0, NULL)) == NULL)
    {
	CloseHandle(rep->event);
	delete rep;
	return -1;
    }

    *thread = (long)rep;
    return 0;
}

pthread_t pthread_self()
{
    pthread_rep_t* rep = (pthread_rep_t*)pthread_getspecific(_pthread_self_key);

    // This thread does has a null _pthread_self_key slot, which means
    // it was not created by pthread_create(). It is probably the main
    // thread but could be a thread that was not created outside this
    // thread package. In either case, we must create a rep for it.

    if (!rep)
    {
	rep = new pthread_rep_t;
	rep->start_routine = NULL;
	rep->arg = NULL;
	rep->event = CreateEvent(0, TRUE, FALSE, 0);
	rep->handle = GetCurrentThread();
	rep->next = 0;

	assert(rep->event != NULL);
	assert(rep->handle != NULL);

	pthread_setspecific(_pthread_self_key, rep);
    }

    return (long)rep;
}

int pthread_attr_init(
    pthread_attr_t* attr)
{
    memset(attr, 0, sizeof(pthread_attr_t));
    return 0;
}

int pthread_attr_destroy(
    pthread_attr_t* attr)
{
    return 0;
}

int pthread_attr_setdetachstate(
    pthread_attr_t* attr,
    int detachstate)
{
    pthread_attr_rep_t* rep = (pthread_attr_rep_t*)attr;
    rep->detachstate = detachstate;
    return 0;
}

//==============================================================================
//
// pthread_cond_t
//
//==============================================================================

struct pthread_cond_rep_t
{
    // Queue of waiting threads.
    pthread_rep_t* front;
    pthread_mutex_t lock;
};

int pthread_cond_init(
    pthread_cond_t* cond,
    const pthread_condattr_t* attr)
{
    assert(sizeof(pthread_cond_t) > sizeof(pthread_cond_rep_t));
    assert(attr == NULL);

    pthread_cond_rep_t* rep = (pthread_cond_rep_t*)cond;
    rep->front = 0;
    pthread_mutex_init(&rep->lock, NULL);

    return 0;
}

int pthread_cond_destroy(
    pthread_cond_t* cond)
{
    pthread_cond_rep_t* rep = (pthread_cond_rep_t*)cond;
    pthread_mutex_destroy(&rep->lock);

    return 0;
}

int pthread_cond_wait(
    pthread_cond_t* cond,
    pthread_mutex_t* mutex)
{
    pthread_cond_rep_t* rep = (pthread_cond_rep_t*)cond;

    // Get current thread.

    pthread_rep_t* self = (pthread_rep_t*)pthread_self();
    assert(self->next == 0);

    // Add to rear of queue.

    pthread_mutex_lock(&rep->lock);

    pthread_rep_t* last = 0;

    for (pthread_rep_t* p = rep->front; p; p = p->next)
	last = p;

    if (last)
	last->next = self;
    else
	rep->front = self;

    pthread_mutex_unlock(&rep->lock);

    // Unlock mutex (it was locked when this function was entered).

    pthread_mutex_rep_t* mutex_rep = (pthread_mutex_rep_t*)mutex;
    size_t lock_count = mutex_rep->count;

    while (lock_count > 0)
	pthread_mutex_unlock(mutex);

    // Wait to be signaled.

    DWORD rc = WaitForSingleObject(self->event, INFINITE);
    assert(rc == WAIT_OBJECT_0);

    // Relock the mutex.

    for (size_t i = 0; i < lock_count; i++)
	pthread_mutex_lock(mutex);

    // Reset the event.

    ResetEvent(self->event);

    return 0;
}

int pthread_cond_signal(
    pthread_cond_t* cond)
{
    pthread_cond_rep_t* rep = (pthread_cond_rep_t*)cond;

    // Remove thread waiting at front of queue.

    if (rep->front)
    {
	pthread_mutex_lock(&rep->lock);

	pthread_rep_t* thread = (pthread_rep_t*)rep->front;

	if (thread)
	{
	    rep->front = thread->next;
	    thread->next = 0;
	    SetEvent(thread->event);
	}

	pthread_mutex_unlock(&rep->lock);
    }

    return 0;
}

POSIX_NAMESPACE_END
