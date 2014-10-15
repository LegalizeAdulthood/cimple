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

#ifndef _cimple_Thread_Pool_h
#define _cimple_Thread_Pool_h

#include "config.h"
#include "Thread.h"
#include "Cond_Queue.h"
#include "List.h"

CIMPLE_NAMESPACE_BEGIN

/** This class implements a simple pool of threads with essentially the 
    same operations as the Thread class. The main advantage is that the 
    it prevents more than a certain number of threads from being created.
    Unfortunately, benchmarks reveal that pre-creating and caching treads 
    is no faster than creating a new one every time (on Linux X86).
*/
class Thread_Pool
{
public:

    // ATTN: implement destroy:

    /** Create a thread pool with num_threads threads.
    */
    static Thread_Pool* create_pool(size_t num_threads);

    /** Elects a thread to execute the given thread routine. If none are
        available, it blocks until one is. Returns a Cond_Queue object that
	must be passed to join(), otherwise, the Cond_Queue object is leaked
	and the thread may hang forever.
    */
    Cond_Queue* create_joinable(Thread_Proc proc, void* arg);

    /** Elects a thread to execute the given thread routine. If none are
	available, it blocks until one is.
    */
    void create_detached(Thread_Proc proc, void* arg);

    /** Obtain the thread return value from a thread that was created with
        create(). Returns the thread's return value.
    */
    void* join(Cond_Queue* queue);

private:

    Thread_Pool(size_t num_threads);

    Thread_Pool& operator=(const Thread_Pool& x);

    static void* _thread_proc(void* arg);

    size_t _num_threads;
    Cond_Queue _queue;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Thread_Pool_h */
