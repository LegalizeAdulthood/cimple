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

/*
 * A simple scheduler that allows thread-save scheduling for timed
 * functions. Each function is defined as a separate thread.
 * LIMITS: Today it schedules calls sequentially so that no more than
 * a single scheduled event may occur simultaneously.
*/

#ifndef _cimple_Scheduler_h
#define _cimple_Scheduler_h

#include <pthread.h>
#include "config.h"
#include "List.h"
#include "Mutex.h"
#include "Thread.h"

CIMPLE_NAMESPACE_BEGIN

/** This function is called when the timer expires. It passes the arg
    parameter that was initially passed to add_timer(). If this function
    returns zero, the timer is canceled and the function will not be called
    again. If it returns a non-zero value, say n, the function will be called
    again in n microseconds.
*/
typedef uint64 (*Timer_Proc)(void* arg);

/** This class provides a thread safe interface for scheduling
 *  timed functions. It allows adding schedule items to be
 *  defined that will cause functions to be called as these
 *  functions timeout. The called functions can define whether
 *  the timers are repetitive or terminate by the return value
 *  from the procedure.
 *  
 *  There are three modes of scheduler operation:
 *  \li \c Manual dispatcher usage.  The user executes the
 *      dispatcher in a loop to execute timed functions
 *  
 *  \li \c Manual control of a dispatcher thread.  By creating a
 *  scheduler without parameter (Scheduler x;) a scheduler is
 *  created that uses start_dispatcher to start the dispatcher
 *  thread. This thread runs until either the Scheduler is
 *  destructed or the stop_dispatcher() function is called
 *  
 *  \li \c Auto Dispatching (create with Scheduler sched(true);)
 *  creates a scheduler that starts the dispatcher thread when
 *  there is a timer added to the queue and terminates the
 *  dispatcher thread when the queue is empty.  Note that if a
 *  timer function is executed and returns a non-zero return,
 *  the dispatcher thread is not terminated during this
 *  interval.   This can be useful when the creation of
 *  scheduled function is sporadic so that the dispatcher thread
 *  is not enabled when there is nothing to dispatch.
 *  
 *  Within a single scheduler object, all timed functions run in
 *  a single thread. When a timer expires the scheduler calls
 *  the defined function and when this function terminates it
 *  attempts to evaluate the next function in the timer queue.
 *  
 *  EXAMPLE:
 *  \code
 *  Scheduler sched;
 *
 *  static uint64 _timer(void* arg)
 *  {
 *     const char* str = (const char*)arg;
 *
 *     printf("_timer(%s)\n", str);
 *     return(0);
 *  }
 *  
 *  // function to stop the scheduler
 *  static uint64 _stopScheduler(void* arg)
 *  {
 *      sched.stop_thread()
 *      return 0;
 *  }
 *  // Scheduler call function
 *  sched.add_timer(3 * SEC, _timer, (void*)"3");
 *  sched.add_timer(30 * SEC, _stop_scheduler, value);
 *  
 *  sched.start_dispatcher();
 *  Thread::join(sched.thread_id(), value); 
 *  \endcode
*/
class CIMPLE_CIMPLE_LINKAGE Scheduler
{
public:

    /** 
     * Construct a new scheduler
     * 
     */
    Scheduler();

    /** 
     * Construct a new scheduler that automatically starts and 
     * stops a scheduling thread when schedule items exist in the 
     * schedule.  If the  parameter is true, the dispatcher is 
     * run automatically when there are timers in queue. It is 
     * stopped when the queue is empty and restarted when a timer 
     * is added. 
     * @param auto_dispatch bool 
     */
    Scheduler(bool auto_dispatch);

    ~Scheduler();

    /** Add a timer and return the timer id.
    */
    size_t add_timer(uint64 timeout,
                     Timer_Proc proc,
                     void* arg);

    /** Remove the timer (with the return value of initial add_timer() call.
    */
    bool remove_timer(size_t timer_id);

    /** Dispatch all expired timers.  This function runs once to
     *  dispatch any timers that have expired. If there are no
     *  timers in the list, it returns. If there are timers, it
     *  sleeps until the first one expires and executes that timer
     *  function.
     *  The function operates on a schedule so that if it is more
     *  than 100 milliseconds to the next timer, it sleeps for 100
     *  milliseconds and returns to the caller. Thus, it does not
     *  sleep endlessly waiting for a timer to expire.
     *  It will execute all timers that have expired in  a single
     *  call.
    */
    void dispatch();

    /** Create a thread to drive the dispatch() method. This thread
     *  will run until stopped by stop_dispatcher()
    */
    int start_dispatcher();

    /** Stop the thread driving the dispatch() method.
    */
    int stop_dispatcher();

    /** 
     * If the scheduler is stopped, clean out any remaining queued
     * items.  Note that the stop_dispatcher function does not do
     * this.
     * 
     */
    int clean();

    /** Return the thread id for this scheduler.
     *  
     *  The primary use today is to be able to join the
     *  dispatcher thread
     *  
     *  @return Thread& id of the scheduler thread
     */
    Thread& thread_id();

private:

    Mutex _lock;

    List _list;

    // Timer thread:
    Thread _thread;

    // Indicates whether dispatcher thread is running.
    bool _dispatcher_thread_running;

    // Thread routine:
    static void* _thread_proc(void* arg);

    // If true, the scheduler starts threads when items are to be 
    // scheduled and stops the thread when there is nothing to 
    // schedule
    bool _auto_dispatch;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Scheduler_h */
