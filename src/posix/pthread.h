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

//==============================================================================
//
// pthread.h
//
//     This module provides a POSIX Thread implementation for Windows. It
//     implements only those features needed by CIMPLE.
//
//==============================================================================


#ifndef _cimple_posix_pthread_h
#define _cimple_posix_pthread_h

#include "linkage.h"

POSIX_NAMESPACE_BEGIN

//==============================================================================
//
// pthread_mutex_t
//
//==============================================================================

#define PTHREAD_MUTEX_FAST_NP 1
#define PTHREAD_MUTEX_RECURSIVE_NP 2

enum pthread_mutex_initializer_t { PTHREAD_MUTEX_INITIALIZER };

struct POSIX_LINKAGE pthread_mutex_t
{
    pthread_mutex_t();
    ~pthread_mutex_t();
    pthread_mutex_t(pthread_mutex_initializer_t);
    char opaque[32];
};

struct pthread_mutexattr_t
{
    char opaque[8];
};

POSIX_LINKAGE int pthread_mutex_init(
    pthread_mutex_t* mutex,
    const pthread_mutexattr_t* attr);

POSIX_LINKAGE int pthread_mutex_lock(
    pthread_mutex_t* mutex);

POSIX_LINKAGE int pthread_mutex_trylock(
    pthread_mutex_t* mutex);

POSIX_LINKAGE int pthread_mutex_unlock(
    pthread_mutex_t* mutex);

POSIX_LINKAGE int pthread_mutex_destroy(
    pthread_mutex_t* mutex);

POSIX_LINKAGE int pthread_mutexattr_init(
    pthread_mutexattr_t* attr);

POSIX_LINKAGE int pthread_mutexattr_destroy(
    pthread_mutexattr_t* attr);

POSIX_LINKAGE int pthread_mutexattr_settype(
    pthread_mutexattr_t* attr,
    int kind);

//==============================================================================
//
// pthread_once_t
//
//==============================================================================

enum pthread_once_init_t { PTHREAD_ONCE_INIT };

struct POSIX_LINKAGE pthread_once_t 
{
    char opaque[64];
    pthread_once_t(pthread_once_init_t);
};

POSIX_LINKAGE int pthread_once(
    pthread_once_t* once_control, 
    void (*init_routine)(void)); 

//==============================================================================
//
// pthread_key_t
//
//==============================================================================

struct pthread_key_t
{
    char opaque[8];
};

POSIX_LINKAGE int pthread_key_create(
    pthread_key_t* key, 
    void (*destructor)(void*));

POSIX_LINKAGE int pthread_key_delete(
    pthread_key_t key);

POSIX_LINKAGE int pthread_setspecific(
    pthread_key_t key, 
    const void* value);

POSIX_LINKAGE void* pthread_getspecific(
    pthread_key_t key);

//==============================================================================
//
// pthread_t
//
//==============================================================================

#define PTHREAD_CREATE_JOINABLE 1
#define PTHREAD_CREATE_DETACHED 2

typedef long pthread_t;

struct pthread_attr_t
{
    char opaque[8];
};

POSIX_LINKAGE int pthread_create(
    pthread_t* thread, 
    const pthread_attr_t* attr,
    void* (*start_routine)(void*), 
    void* arg);

POSIX_LINKAGE pthread_t pthread_self();

POSIX_LINKAGE int pthread_attr_init(
    pthread_attr_t* attr);

POSIX_LINKAGE int pthread_attr_destroy(
    pthread_attr_t* attr);

POSIX_LINKAGE int pthread_attr_setdetachstate(
    pthread_attr_t* attr,
    int detachstate);

POSIX_LINKAGE void pthread_exit(void*);

POSIX_LINKAGE int pthread_join(pthread_t thread, void** value_ptr);

POSIX_LINKAGE int pthread_equal(pthread_t t1, pthread_t t2);

//==============================================================================
//
// pthread_cond_t
//
//==============================================================================

enum pthread_cond_initializer_t { PTHREAD_COND_INITIALIZER };

struct pthread_cond_t
{
    char opaque[64];
};

struct pthread_condattr_t;

POSIX_LINKAGE int pthread_cond_init(
    pthread_cond_t* cond,
    const pthread_condattr_t* attr);

POSIX_LINKAGE int pthread_cond_destroy(
    pthread_cond_t* cond);

POSIX_LINKAGE int pthread_cond_wait(
    pthread_cond_t* cond,
    pthread_mutex_t* mutex);

POSIX_LINKAGE int pthread_cond_signal(
    pthread_cond_t* cond);

POSIX_LINKAGE int pthread_cond_broadcast(
    pthread_cond_t* cond);

POSIX_NAMESPACE_END

#endif /* _cimple_posix_pthread_h */
