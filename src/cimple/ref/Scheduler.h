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

#ifndef _cimple_Scheduler_h
#define _cimple_Scheduler_h

#include "config.h"
#include "List.h"
#include "Threads.h"
#include "RMutex.h"

CIMPLE_NAMESPACE_BEGIN

/** This function is called when the timer expires. It passes the arg
    parameter that was initially passed to add_timer(). If this function
    returns zero, the timer is canceled and the function will not be called
    again. If it returns a non-zero value, say n, the function will be called
    again in n microseconds.
*/
typedef uint64 (*Timer_Proc)(void* arg);

/** This class provides a thread safe interface for scheduling timers.
*/
class CIMPLE_LIBCIMPLE_LINKAGE Scheduler
{
public:

    Scheduler();

    ~Scheduler();

    /** Add a timer and return the timer id.
    */
    size_t add_timer(uint64 timeout, Timer_Proc proc, void* arg);

    /** Remove the timer (with the return value of initial add_timer() call.
    */
    bool remove_timer(size_t timer_id);

    /** Dispatch all expired timers.
    */
    void dispatch();

    /** Create a thread to drive the dispatch() method.
    */
    int start_thread();

    /** Stop the thread driving the dispatch() method.
    */
    int stop_thread();

private:

    RMutex _lock;

    List _list;

    // Timer thread:
    Thread _thread;

    // Indications whether timer thread is running.
    bool _thread_running;

    // Thread routine:
    static void* _thread_proc(void* arg);
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Scheduler_h */
