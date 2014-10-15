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

#include "Time.h"
#include "Scheduler.h"
#include "Id_Pool.h"
#include "Auto_Mutex.h"

CIMPLE_NAMESPACE_BEGIN

static Id_Pool _id_pool;

struct Timer : public List_Elem
{
    size_t id;
    uint64 deadline;
    Timer_Proc proc;
    void* arg;
};

static void _insert_timer(List& list, Timer* timer)
{
    // Keep list sorted in ascending order of deadline.
    if (!list.empty())
    {
        // insert in time sequence
        for (List_Elem* p = list.head; p; p = p->next)
        {
            if (timer->deadline < ((Timer*)p)->deadline)
            {
                list.insert_before(p, timer);
                return;
            }
        }
    }

    list.append(timer);
}

Scheduler::Scheduler() :
    _dispatcher_thread_running(false),
    _auto_dispatch(false)
{
}

Scheduler::Scheduler(bool autoDispatcherStart) :
    _dispatcher_thread_running(false),
    _auto_dispatch(autoDispatcherStart)
{
}

Scheduler::~Scheduler()
{
    for (List_Elem* p = _list.head; p; )
    {
        List_Elem* next = p->next;
        delete p;
        p = next;
    }
}

size_t Scheduler::add_timer(uint64 timeout,
                            Timer_Proc proc,
                            void* arg)
{
    Auto_Mutex auto_lock(_lock);

    // Create new timer:

    Timer* timer = new Timer;
    timer->id = _id_pool.get();
    timer->deadline = Time::now() + timeout;
    timer->proc = proc;
    timer->arg = arg;

    // Insert timer into list:

    _insert_timer(_list, timer);

    if (_auto_dispatch && !_dispatcher_thread_running)
        start_dispatcher();

    return timer->id;
}

bool Scheduler::remove_timer(size_t timer_id)
{
    Auto_Mutex auto_lock(_lock);

    for (List_Elem* p = _list.head; p; p = p->next)
    {
        Timer* timer = (Timer*)p;
    
        if (timer->id == timer_id)
        {
            // Found!
            _list.remove(p);
            _id_pool.put(timer->id);
            delete timer;
            if (_auto_dispatch && _list.empty())
                stop_dispatcher();

            return true;
        }
    }

    // Not found!
    return false;
}

void Scheduler::dispatch()
{
    // We will spend no more than this duration in this dispatch() function.
    // Currently 100 milliseconds
    const uint64 MAX_TIME_INSIDE_DISPATCH_USEC = 1000 * 1000;

    _lock.lock();

    // if list empty exit without any other processing. If we are using
    // continuous threads, execute timer before exiting.
    if (_list.empty())
    {
        _lock.unlock();
        if (_auto_dispatch)
            stop_dispatcher();
        else
            Time::sleep(MAX_TIME_INSIDE_DISPATCH_USEC);
        return;
    }

    // Sleep until the closest deadline

    uint64 now = Time::now();
    uint64 closest_deadline = ((Timer*)_list.head)->deadline;

    if (now < closest_deadline)
    {
        uint64 diff = closest_deadline - now;
    
        if (diff > MAX_TIME_INSIDE_DISPATCH_USEC)
        {
            _lock.unlock();
            Time::sleep(MAX_TIME_INSIDE_DISPATCH_USEC);
            return;
        }
    
        _lock.unlock();
        Time::sleep(diff);
        _lock.lock();
    
        now = closest_deadline;
    }

    // Dispatch expired timers (there will be at least one).

    for (;;)
    {
        Timer* timer = (Timer*)_list.head;

        // if current timer not expired, terminate loop

        if (!timer || now < timer->deadline)
            break;
    
        _list.remove(timer);

        // Call the function to be executed for this timer.

        _lock.unlock();
        uint64 new_timeout = timer->proc(timer->arg);
        _lock.lock();

        // if the function returns zero, delete this timer
        // else reinsert the timer with the returned timeout.
        // 
        if (new_timeout == 0)
            delete timer;
        else
        {
            if (!_auto_dispatch)
            {
                timer->deadline = Time::now() + new_timeout;
                _insert_timer(_list, timer);
            }
            else   // if autothreading
            {
                if (_dispatcher_thread_running)
                {
                    timer->deadline = Time::now() + new_timeout;
                    _insert_timer(_list, timer);
                }
                else
                    delete timer;
            }
        }
    }

    if (_auto_dispatch && _list.empty())
        stop_dispatcher();

    _lock.unlock();
}

// Run the dispatcher while the running flag is true

void* Scheduler::_thread_proc(void* arg)
{
    Scheduler* sched = (Scheduler*)arg;
    while (sched->_dispatcher_thread_running)
        sched->dispatch();

    return 0;
}

// Start the dispatcher by creating a joinable thread.
int Scheduler::start_dispatcher()
{
    Auto_Mutex auto_lock(_lock);

    if (_dispatcher_thread_running)
        return -1;

    _dispatcher_thread_running = true;

    return Thread::create_joinable(_thread, _thread_proc, this);

    return 0;
}

int Scheduler::stop_dispatcher()
{
    Auto_Mutex auto_lock(_lock);

    if (!_dispatcher_thread_running)
        return -1;

    // Setting this to false will cause _thread_proc() to fall out of its
    // loop and terminate.

    _dispatcher_thread_running = false;

    return 0;
}

int Scheduler::clean()
{
    if (_dispatcher_thread_running)
        return -1;

    // Clean out all elements in the list
    for (List_Elem* p = _list.head; p; )
    {
        List_Elem* next = p->next;
        delete p;
        p = next;
    }

    // set the list to clear
    _list.clear();

    return 0;
}

Thread& Scheduler::thread_id()
{
    return _thread;
}

CIMPLE_NAMESPACE_END
