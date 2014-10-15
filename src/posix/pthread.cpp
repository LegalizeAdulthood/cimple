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

#include "pthread.h"
#include "unistd.h"
#include <cassert>
#include <cstdio>
#include <windows.h>
#include <errno.h>

#define for if (0) ; else for

POSIX_NAMESPACE_BEGIN

//==============================================================================
//
// pthread_mutexattr_t
//
//==============================================================================

struct pthread_mutexattr_rep_t
{
    int kind;
};

int pthread_mutexattr_init(
    pthread_mutexattr_t* attr)
{
    assert(sizeof(pthread_mutexattr_t) >= sizeof(pthread_mutexattr_rep_t));
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
    // Set kind into attribute (PTHREAD_MUTEX_FAST_NP or 
    // PTHREAD_MUTEX_RECURSIVE_NP.

    if (attr)
    {
        pthread_mutexattr_rep_t* rep = (pthread_mutexattr_rep_t*)attr;
        rep->kind = kind;
        return 0;
    }

    return -1;
}

//==============================================================================
//
// pthread_mutex_t
//
//==============================================================================

struct pthread_mutex_rep_t
{
    HANDLE handle;
    size_t count;
    // PTHREAD_MUTEX_FAST_NP or PTHREAD_MUTEX_RECURSIVE_NP
    bool recursive;
};

pthread_mutex_t::pthread_mutex_t()
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)this;
    rep->handle = NULL;
    rep->count = 0;
}

pthread_mutex_t::pthread_mutex_t(pthread_mutex_initializer_t)
{
    pthread_mutex_init(this, NULL);
}

pthread_mutex_t::~pthread_mutex_t()
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)this;

    if (rep->handle != NULL)
        pthread_mutex_destroy(this);
}

int pthread_mutex_init(
    pthread_mutex_t* mutex,
    const pthread_mutexattr_t* attr)
{
    assert(sizeof(pthread_mutex_t) >= sizeof(pthread_mutex_rep_t));

    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;
    rep->count = 0;

    if (attr)
    {
        pthread_mutexattr_rep_t* attrrep = (pthread_mutexattr_rep_t*)attr;

        if (attrrep->kind & PTHREAD_MUTEX_RECURSIVE_NP)
            rep->recursive = true;
        else
            rep->recursive = false;
    }
    else
    {
        rep->recursive = false;
    }

    if ((rep->handle = CreateMutex(NULL, FALSE, NULL)) == NULL)
        return -1;

    return 0;
}

int pthread_mutex_destroy(
    pthread_mutex_t* mutex)
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    if (!CloseHandle(rep->handle))
    {
        rep->handle = NULL;
        rep->count = 0;
        return -1;
    }

    rep->handle = NULL;
    rep->count = 0;
    return 0;
}

int pthread_mutex_lock(
    pthread_mutex_t* mutex)
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    if (WaitForSingleObject(rep->handle, INFINITE) == WAIT_FAILED)
        return -1;

    if (!rep->recursive && rep->count == 1)
    {
        // Avoid double lock on non-recursive mutex.
        ReleaseMutex(rep->handle);
        return -1;
    }

    rep->count++;

    return 0;
}


int pthread_mutex_trylock(
    pthread_mutex_t* mutex)
{
    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    DWORD rc = 0;
    rc = WaitForSingleObject(rep->handle, (DWORD)0);

    //printf("waitforSingleObject rtn = %ld\n", rc);
    if (rc == WAIT_TIMEOUT)
    {
        //printf("waitforSingleObject WAIT_TIMEOUT rtn = %ld\n", rc);
        return(EBUSY);
    }
    else if (rc == WAIT_FAILED)
    {
        //printf("waitforSingleObject WAIT_FAILED = %ld\n", rc);
        return(-1);
    }

    //printf("waitforSingleObject Supposidly no error = %ld\n", rc);
    if (!rep->recursive && rep->count == 1)
    {
        //printf("pthread return recurse limit hit. EBUSY= %d \n", EBUSY);
        // Avoid double lock on non-recursive mutex.
        assert(ReleaseMutex(rep->handle));
        //printf("pthread returning EBUSY\n");
        return(EBUSY);
    }

    rep->count++;
    return 0;
}

int pthread_mutex_unlock(
    pthread_mutex_t* mutex)
{
    if (!mutex)
        return -1;

    pthread_mutex_rep_t* rep = (pthread_mutex_rep_t*)mutex;

    if (rep->count == 0)
    {
        return -1;
    }

    rep->count--;

    if (!ReleaseMutex(rep->handle))
        return -1;

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
        {
            (*init_routine)();
            rep->initialized = 1;
        }

        pthread_mutex_unlock(&rep->mutex);
    }

    return 0;
}

//==============================================================================
//
// pthread_key_t
//
//==============================================================================

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
// pthread_attr_t
//
//==============================================================================

struct pthread_attr_rep_t
{
    int detachstate;
};

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
// pthread_t
//
//==============================================================================

struct pthread_rep_t
{
    void* (*start_routine)(void*);
    void* arg;
    HANDLE event;
    HANDLE handle;
    pthread_rep_t* next;

    int joined;
    void* value_ptr;
    pthread_mutex_t join_mutex;
    HANDLE join_event;
    pthread_rep_t* join_next;
};

static pthread_rep_t* _join_list = 0;
static pthread_mutex_t _join_list_mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_once_t _self_once = PTHREAD_ONCE_INIT;
static pthread_key_t _self_key;

static void _create_self_key()
{
    pthread_key_create(&_self_key, NULL);
}

static DWORD WINAPI _proc(LPVOID arg) 
{
    pthread_rep_t* rep = (pthread_rep_t*)arg;

    // Set thread rep into thread-specific storage.

    if (pthread_setspecific(_self_key, rep) != 0)
    {
        assert(0);
        CloseHandle(rep->event);

        if (rep->join_event != NULL)
        {
            CloseHandle(rep->join_event);

            pthread_mutex_destroy(&rep->join_mutex);
        }

        delete rep;
        return 0;
    }

    // Run thread procedure passed to Threads::create().

    void* return_value = (*rep->start_routine)(rep->arg);

    pthread_exit(return_value);

    // Unreachable!
    assert(0);

    return (DWORD)0;
}

static void _destroy_thread_rep(pthread_rep_t* rep)
{
    if (rep)
    {
        if (rep->event != NULL)
            CloseHandle(rep->event);

        if (rep->join_event != NULL)
            CloseHandle(rep->join_event);

        pthread_mutex_destroy(&rep->join_mutex);

        delete rep;
    }
}

int pthread_create(
    pthread_t* thread, 
    const pthread_attr_t* attr,
    void* (*start_routine)(void*), 
    void* arg)
{
    pthread_attr_rep_t* attr_rep = (pthread_attr_rep_t*)attr;

    //
    // Initialize _self_key.
    //

    if (pthread_once(&_self_once, _create_self_key) != 0)
        return -1;

    //
    // Create rep object.
    //

    pthread_rep_t* rep = new pthread_rep_t;
    memset(rep, 0, sizeof(*rep));
    rep->start_routine = start_routine;
    rep->arg = arg;

    // Create an event to be used by the condition variable implementation.

    if ((rep->event = CreateEvent(0, TRUE, FALSE, 0)) == NULL)
    {
        _destroy_thread_rep(rep);
        return -1;
    }

    // For joinable events, create a join event.

    if (attr_rep == 0 || attr_rep->detachstate == PTHREAD_CREATE_JOINABLE)
    {
        if ((rep->join_event = CreateEvent(0, TRUE, FALSE, 0)) == NULL)
        {
            _destroy_thread_rep(rep);
            return -1;
        }

        pthread_mutex_init(&rep->join_mutex, NULL);
    }

    // Create thread:

    if ((rep->handle = CreateThread(NULL, 0, _proc, rep, 0, NULL)) == NULL)
    {
        _destroy_thread_rep(rep);
        return -1;
    }

    // Stick this rep into the join list (if joinable).

    if (attr_rep == 0 || attr_rep->detachstate == PTHREAD_CREATE_JOINABLE)
    {
        pthread_mutex_lock(&_join_list_mutex);
        rep->join_next = _join_list;
        _join_list = rep;
        pthread_mutex_unlock(&_join_list_mutex);
    }

    *thread = (long)rep;

    return 0;
}

pthread_t pthread_self()
{
    pthread_rep_t* self = (pthread_rep_t*)pthread_getspecific(_self_key);

    // This thread has a null _self_key slot, which means
    // it was not created by pthread_create(). It is probably the main
    // thread but could be a thread that was created outside this
    // thread package. In either case, we must create a self for it.

    if (!self)
    {
        self = new pthread_rep_t;
        memset(self, 0, sizeof(*self));
        self->event = CreateEvent(0, TRUE, FALSE, 0);
        self->handle = GetCurrentThread();

        assert(self->event != NULL);
        assert(self->handle != NULL);

        pthread_setspecific(_self_key, self);
    }

    return (long)self;
}

void pthread_exit(void* value_ptr)
{
    //
    // Get thread rep (if none, then just exit).
    //

    pthread_rep_t* rep = (pthread_rep_t*)pthread_getspecific(_self_key);

    if (!rep)
    {
        ExitThread(0);
        return;
    }

    //
    // Handle join operation (if thread is joinable)
    //

    if (rep->join_event != NULL)
    {
        pthread_mutex_lock(&rep->join_mutex);
        rep->joined = 1;
        rep->value_ptr = value_ptr;
        SetEvent(rep->join_event);
        pthread_mutex_unlock(&rep->join_mutex);
    }
    else
        _destroy_thread_rep(rep);

    //
    // Exit thread.
    //

    ExitThread(0);
}

int pthread_join(pthread_t thread, void** value_ptr)
{
    pthread_rep_t* rep = (pthread_rep_t*)thread;

    //
    // Clear value.
    //

    if (value_ptr)
        *value_ptr = 0;

    //
    // Remove join list.
    //

    pthread_mutex_lock(&_join_list_mutex);

    pthread_rep_t* prev = 0;
    bool found = false;

    for (pthread_rep_t* p = _join_list; p; p = p->join_next)
    {
        if (p == rep)
        {
            if (prev)
                prev->join_next = p->join_next;
            else
                _join_list = p->join_next;

            found = true;
        }

        prev = p;
    }

    pthread_mutex_unlock(&_join_list_mutex);

    if (!found)
    {
        // This thread is not joinable or has already been joined.
        return -1;
    }

    //
    // Wait for thread to finish.
    //

    pthread_mutex_lock(&rep->join_mutex);

    if (rep->joined == 0)
    {
        pthread_mutex_unlock(&rep->join_mutex);
        DWORD rc = WaitForSingleObject(rep->join_event, INFINITE);
        pthread_mutex_lock(&rep->join_mutex);

        assert(rc == WAIT_OBJECT_0);
    }

    pthread_mutex_unlock(&rep->join_mutex);

    assert(rep->joined == 1);
    *value_ptr = rep->value_ptr;
    _destroy_thread_rep(rep);

    return 0;
}

int pthread_equal(pthread_t t1, pthread_t t2)
{
    return t1 == t2;
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

    if (!cond || ! mutex)
        return -1;

    // Get current thread.

    pthread_self();
    pthread_rep_t* self = (pthread_rep_t*)pthread_getspecific(_self_key);
    assert(self != 0);
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

    size_t i;

    for (i = 0; i < lock_count; i++)
        pthread_mutex_unlock(mutex);

    // Wait to be signaled.

    DWORD rc = WaitForSingleObject(self->event, INFINITE);
    assert(rc == WAIT_OBJECT_0);

    // Relock the mutex.

    for (i = 0; i < lock_count; i++)
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

int pthread_cond_broadcast(
    pthread_cond_t* cond)
{
    pthread_cond_rep_t* rep = (pthread_cond_rep_t*)cond;

    // Remove thread waiting at front of queue.

    while (rep->front)
    {
        pthread_cond_signal(cond);
    }

    return 0;
}

POSIX_NAMESPACE_END
