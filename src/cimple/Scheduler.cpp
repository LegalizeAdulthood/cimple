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

    if (list.empty())
    {
	list.append(timer);
	return;
    }

    for (List_Elem* p = list.head; p; p = p->next)
    {
	if (timer->deadline < ((Timer*)p)->deadline)
	{
	    list.insert_before(p, timer);
	    return;
	}
    }

    list.append(timer);
}

Scheduler::Scheduler() : _thread_running(false)
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

size_t Scheduler::add_timer(uint64 timeout, Timer_Proc proc, void* arg)
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
	    return true;
	}
    }

    // Not found!
    return false;
}

void Scheduler::dispatch()
{
    // We will spend no more than this duration in this dispatch() function.
    const uint64 MAX_TIME_INSIDE_DISPATCH_USEC = 1000 * 1000;

    // Stay in this function no longer than 100 milliseconds.

    _lock.lock();

    if (_list.empty())
    {
	_lock.unlock();
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

	if (!timer || now < timer->deadline)
	    break;

	_list.remove(timer);

	_lock.unlock();
	uint64 new_timeout = timer->proc(timer->arg);
	_lock.lock();

	if (new_timeout == 0)
	    delete timer;
	else
	{
	    timer->deadline = Time::now() + new_timeout;
	    _insert_timer(_list, timer);
	}
    }

    _lock.unlock();
}

void* Scheduler::_thread_proc(void* arg)
{
    Scheduler* sched = (Scheduler*)arg;

    while (sched->_thread_running)
	sched->dispatch();

    return 0;
}

int Scheduler::start_thread()
{
    Auto_Mutex auto_lock(_lock);

    if (_thread_running)
	return -1;

    _thread_running = true;

    pthread_attr_init(&_thread_attr);
    pthread_attr_setdetachstate(&_thread_attr, PTHREAD_CREATE_DETACHED);
    return pthread_create(&_thread, &_thread_attr, _thread_proc, this);

    return 0;
}

int Scheduler::stop_thread()
{
    Auto_Mutex auto_lock(_lock);

    if (!_thread_running)
	return -1;

    // Setting this to false will cause _thread_proc() to fall out of its
    // loop and terminate.

    _thread_running = false;

    // pthread_attr_destroy(&_thread_attr);

    return 0;
}

CIMPLE_NAMESPACE_END
