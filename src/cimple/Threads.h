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

#ifndef _cimple_Threads_h
#define _cimple_Threads_h

#include "config.h"
#include <pthread.h>
#include <errno.h>

CIMPLE_NAMESPACE_BEGIN

typedef void* (*Thread_Proc)(void* arg);

class Thread
{
public:

    Thread() : _has_attr(false) { }

    ~Thread();

private:

    Thread(pthread_t rep) : _rep(rep), _has_attr(false) { }

    pthread_t _rep;
    bool _has_attr;
    pthread_attr_t _attr;

    friend class Threads;
};

class Threads
{
public:

    enum { ID_SIZE = 32 };

    static int create_joinable(Thread& thread, Thread_Proc proc, void* arg);

    static int create_detached(Thread& thread, Thread_Proc proc, void* arg);

    static void exit(void* return_value);

    static void join(Thread& thread, void*& return_value);

    static void id(char buffer[Threads::ID_SIZE]);

    static Thread self();

    static bool equal(const Thread& thread1, const Thread& thread2);

private:

    Threads();
};

inline void Threads::exit(void* return_value)
{
    pthread_exit(return_value);
}

inline void Threads::join(Thread& thread, void*& return_value)
{
    pthread_join(thread._rep, &return_value);
}

inline void Threads::id(char buffer[Threads::ID_SIZE])
{
    sprintf(buffer, "%ld", pthread_self());
}

inline int Threads::create_joinable(Thread& thread, Thread_Proc proc, void* arg)
{
    return pthread_create(&thread._rep, 0, proc, arg);
}

inline Thread Threads::self()
{
    return Thread(pthread_self());
}

inline bool Threads::equal(const Thread& thread1, const Thread& thread2)
{
    return pthread_equal(thread1._rep, thread2._rep);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Threads_h */
