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

#include "Thread_Pool.h"

CIMPLE_NAMESPACE_BEGIN

void* Thread_Pool::_thread_proc(void* arg)
{
    Thread_Pool* pool = (Thread_Pool*)arg;

    for (;;)
    {
	// Wait for someone to call Thread_Pool::create()

	Cond_Queue_Entry entry;
	pool->_queue.dequeue(entry);

	// Extract the arguments:

	Thread_Proc proc = Thread_Proc(entry.args[0]);
	void* arg = (void*)(entry.args[1]);
	Cond_Queue* queue = (Cond_Queue*)(entry.args[2]);

	// Invoke the thread routine.

	void* return_value = proc(arg);

	// Enqueue the return value for thread waiting on Thread_Proc::join().

	if (queue)
	{
	    Cond_Queue_Entry return_entry;
	    return_entry.args[0] = (unsigned long)return_value;
	    queue->enqueue(return_entry);
	}
    }
}

Thread_Pool* Thread_Pool::create_pool(size_t num_threads)
{
    // Create the pool:

    Thread_Pool* pool = new Thread_Pool(num_threads);

    // Create the threads:

    for (size_t i = 0; i < num_threads; i++)
    {
	Thread thread;
	int r = Thread::create(thread, _thread_proc, pool, true);
	assert(r == 0);
    }

    return pool;
}

Cond_Queue* Thread_Pool::create_joinable(Thread_Proc proc, void* arg)
{
    // Create queue:

    Cond_Queue* queue = new Cond_Queue(1);

    // Enqueue the arguments for the next thread to handle:

    Cond_Queue_Entry entry;
    entry.args[0] = (unsigned long)proc;
    entry.args[1] = (unsigned long)arg;
    entry.args[2] = (unsigned long)queue;
    _queue.enqueue(entry);

    return queue;
}

void Thread_Pool::create_detached(Thread_Proc proc, void* arg)
{
    // Enqueue the arguments for the next thread to handle:

    Cond_Queue_Entry entry;
    entry.args[0] = (unsigned long)proc;
    entry.args[1] = (unsigned long)arg;
    entry.args[2] = (unsigned long)0;
    _queue.enqueue(entry);
}

void* Thread_Pool::join(Cond_Queue* queue)
{
    Cond_Queue_Entry entry;
    queue->dequeue(entry);
    return (void*)(entry.args[0]);
}

Thread_Pool::Thread_Pool(size_t num_threads) : _queue(num_threads) 
{
    _num_threads = num_threads;
}

CIMPLE_NAMESPACE_END
