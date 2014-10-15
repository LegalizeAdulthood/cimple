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
    Test the functionality of the Scheduler Class. Runs a number of tests
    that create schedules and execute them.  

    We test to be sure that the timing is correct (completes in the correct
    time) and that the calls return the proper information.

    We do not test if the schedule times are exactly correct.
*/
#include <cassert>
#include <cimple/config.h>
#include <cimple/Time.h>
#include <cimple/Scheduler.h>
#include <cimple/Thread.h>
#include <cimple/Atomic_Counter.h>

using namespace cimple;

const uint64 SECOND = Time::SEC;

// Simple scheduler. Used to manually dispatch and with start_dispatch
Scheduler sched;

// Scheduler that controls its own threading automatically
Scheduler sched_auto(true);

// Flag to stop dispatcher in test of manual dispatcher usage.
bool stopDispatcher;

// test to see if OneShotTimer  function was run.
bool ran_OriginalTimer;

Atomic_Counter test03_counter(3);

// local function to aid printf of boolean variables.
const char* _show(bool x) { return( x ? "true" : "false" );}

// Very simple local timer class to allow us to test for time delays in the
// scheduler tests. Starts a timer and provides for accessing the
// timer and testing the current interval against a range.

class test_timer
{
public:
    test_timer(){_starttime = Time::now();}

    ~test_timer(){}

    void restart(){ _starttime = Time::now();}

    // return milliseconds since start
    uint32 get_interval_ms()
    {
        return((uint32)((Time::now() - _starttime)/1000));
    }

    // test range of expired time in milliseconds
    bool test_range_ms(uint32 min, uint32 max)
    {
        uint32 t = get_interval_ms();
        if ((t >= min) && t <= max )
            return true;

        printf("test_timer failed. rtnd %u ms. min %u ms max %u ms\n",
               t, min, max);
        return false;
    }
    // 
    bool test_range_sec(uint32 min, uint32 max)
    {
        uint32 t = get_interval_ms();
        if ((t >= min * 1000) && t <= max * 1000 )
            return true;

        printf("test_timer failed. rtnd %u sec. min %u sec max %u sec\n",
               t/1000, min, max);
        return false;
    }

private:
    uint64 _starttime;
};

/*******************************************************************************
**
**   timer functions for scheduler test. These functions are called by
**   the scheduler
**
*******************************************************************************/

// Scheduled function for Repeating Timer.  This function
// arg is char * representation of integer.  The function
// returns the integer definition of this value.
static uint64 _RepeatingTimer(void* arg)
{
    const char* str = (const char*)arg;

    int rtn = atoi(str);
    ran_OriginalTimer = true;
    assert(rtn >= 0);
    uint64 x = (uint64) rtn;
    //printf("_RepeatingTimer Funct %s sec\n", str);

    return (x * SECOND);
}

// Scheduled function that restarts a new timer with the time 
// in arg
static uint64 _RestartingTimer(void* arg)
{
    const char* str = (const char*)arg;

    int rtn = atoi(str);
    ran_OriginalTimer = true;
    assert(rtn >= 0);
    uint64 x = (uint64) rtn;
    //printf("_RestartingTimer Function %s sec\n", str);

    sched.add_timer((x * SECOND), _RestartingTimer, arg);
    return 0;
}

// Scheduled function for One Shot Timer.  This function
// restarts the timer for certain inputs and adds another
// time for another input value.
// We want to delete this one completely in favor of the
// single function timers.
static uint64 _OriginalTimer(void* arg)
{
    const char* str = (const char*)arg;
    ran_OriginalTimer = true;
    printf("_OriginalTimer %s\n", str);

    if (str[0] == '1')
        return 1 * SECOND;

    if (str[0] == '2')
        return 2 * SECOND;

    if (str[0] == '3')
        return 3 * SECOND;

    // clear out old timer and add new one
    if (str[0] == '4')
    {
        sched.add_timer(4 * SECOND, _OriginalTimer, (void*)"4");
        return 0;
    }

    return 0;
}

// thread proc to increment global counter and return. returns
// 0 so timer not restarted.
static uint64 _SimpleOneShotTimer(void* arg)
{
    const char* str = (const char*)arg;

    //printf("SimpleOneShotTimer %s\n", str);

    test03_counter.dec();

    return 0;
}

// When called, this function issues the stop_thread call to
// stop all outstanding timers for the scheduler defined by
// the argument
static uint64 _stopDispatcherThread(void* arg)
{
    //Scheduler* sched = (Scheduler*)arg;
    printf("test_scheduler Stop Scheduler Thread\n");
    sched.stop_dispatcher();
    stopDispatcher = true;
    return 0;
}

static uint64 _stopsched_autoDispatcherThread(void* arg)
{
    //Scheduler* sched = (Scheduler*)arg;
    printf("test_scheduler Stop Scheduler Thread\n");
    sched_auto.stop_dispatcher();
    stopDispatcher = true;
    return 0;
}
// When called, this function issues the stop_thread call to
// stop all outstanding timers.
static uint64 _stopDispatcher(void* arg)
{
    printf("test_scheduler Stop Dispatcher\n");
    stopDispatcher = true;
    return 0;
}

/*******************************************************************************
**
**   Individual tests for Scheduler
**
*******************************************************************************/

// Test scheduler with multiple repeating timers

void test01()
{
    printf("Start test01\n");
    test_timer x;
    // add several scheduled timer events

    sched.add_timer(3 * SECOND, _RepeatingTimer, (void*)"3");
    sched.add_timer(2 * SECOND, _RepeatingTimer, (void*)"2");
    sched.add_timer(1 * SECOND, _RepeatingTimer, (void*)"1");
    sched.add_timer(4 * SECOND, _RestartingTimer, (void*)"4");

    // calls the stop thread function after 30 seconds.
    sched.add_timer(30 * SECOND, _stopDispatcherThread, (void*)"30");

    // Start the dispatcher thread
    sched.start_dispatcher();

    // wait for the dispatcher thread to rejoin when
    //  _stopDispatcherThread function
    // runs.
    void * value;
    assert(Thread::join(sched.thread_id(), value) == 0);
    assert(x.test_range_sec(29, 31));

    printf("+++++ passed test01\n");
}

// test where we dispatch directly in this thread using the dispatcher
//
void test02()
{
    printf("Start test02\n");
    test_timer x;

    sched.clean();
    sched.add_timer(3 * SECOND, _RepeatingTimer, (void*)"3");
    sched.add_timer(2 * SECOND, _RepeatingTimer, (void*)"2");
    sched.add_timer(1 * SECOND, _RepeatingTimer, (void*)"1");
    sched.add_timer(4 * SECOND, _RepeatingTimer, (void*)"4");

    // calls the stop thread function after 30 seconds.
    sched.add_timer(30 * SECOND, _stopDispatcher, (void*)"30");
    stopDispatcher = false;

    // manually call the dispatcher until the _stopDispatcher method
    // runs to turn it off.
    while (!stopDispatcher)
    {
        //printf(" . ");
        sched.dispatch();
    }
    assert(x.test_range_sec(29,31));

    printf("+++++ passed test02\n");
}

// test autostart and stop of dispatcher. Executes some one-shot timers that
// do not restart and terminates.  This test whether the auto thread starter
// and stoppers work when we add timers and run out of timers to execute.
void test03()
{
    printf("Start test03\n");
    test_timer x;
    sched_auto.clean();
    sched_auto.add_timer(3 * SECOND, _SimpleOneShotTimer, (void*)"3");
    sched_auto.add_timer(1 * SECOND, _SimpleOneShotTimer, (void*)"1");

    // wait for the dispatcher thread to rejoin 

    void * value;
    assert(Thread::join(sched_auto.thread_id(), value) == 0);
    assert(x.test_range_sec(2, 5));
    //  Rerun again with new timer after sleeping.
    //  no particular reason for the sleep

    Time::sleep(2 * SECOND);

    // Schedule another timer
    sched_auto.add_timer(2 * SECOND, _SimpleOneShotTimer, (void*)"2");

    // wait for the dispatcher thread to rejoin

    assert(Thread::join(sched_auto.thread_id(), value) == 0);

    printf("+++++ passed test03\n");
}

// test to assure that stopDispatcher does stop the dispatcher 
// immediatly and that the timed functions are not run.
void test04()
{
    printf("Start test04\n");
    test_timer x;

    ran_OriginalTimer = false;

    assert(sched.clean() == 0);;

    sched.add_timer(10 * SECOND, _RepeatingTimer, (void*)"10");
    sched.add_timer(8 * SECOND, _RepeatingTimer, (void*)"8");

    sched.start_dispatcher();

    // immediatly stop the dispatcher
    sched.stop_dispatcher();

    void * value;
    assert(Thread::join(sched.thread_id(), value) == 0);

    // Nothing should have run
    assert(!ran_OriginalTimer);

    // assert that this all happend in < 1200 ms
    assert(x.test_range_ms(0,1200));

    printf("+++++ passed test04\n");
}

// Repeat test 4 but with autodispatch.  
void test05()
{
    printf("Start test05\n");
    test_timer x;
    sched_auto.clean();

    ran_OriginalTimer = false;
    sched_auto.add_timer(10 * SECOND, _RepeatingTimer, (void*)"10");
    sched_auto.add_timer(12 * SECOND, _RepeatingTimer, (void*)"12");

    // immediatly stop the dispatcher
    sched_auto.stop_dispatcher();

    void * value;
    assert(Thread::join(sched_auto.thread_id(), value) == 0);

    assert(!ran_OriginalTimer);

    // assert that this all happend in < 1200 ms. 
    assert(x.test_range_ms(0,1200));

    printf("+++++ passed test05\n");
}
// test autostart and stop of dispatcher thread
void test06()
{
    printf("Start test06\n");
    test_timer x;

    sched_auto.add_timer(3 * SECOND, _RepeatingTimer, (void*)"3");
    sched_auto.add_timer(2 * SECOND, _RepeatingTimer, (void*)"2");
    sched_auto.add_timer(1 * SECOND, _RepeatingTimer, (void*)"1");
    sched_auto.add_timer(4 * SECOND, _RestartingTimer, (void*)"4");

    // calls the stop thread function after 30 seconds.
    sched_auto.add_timer(8 * SECOND, _stopsched_autoDispatcherThread, (void*)"8");

    // wait for the dispatcher thread to rejoin when the _stopDispatcher
    // function runs.
    void * value;
    assert(Thread::join(sched_auto.thread_id(), value) == 0);

    assert(x.test_range_sec(7,9));

    x.restart();
    // Run a second test to assure it works the second time
    sched_auto.add_timer(3 * SECOND, _RepeatingTimer, (void*)"3");

    // calls the stop thread function after 8 seconds.
    sched_auto.add_timer(8 * SECOND, _stopsched_autoDispatcherThread,
                         (void*)"8");

    assert(Thread::join(sched_auto.thread_id(), value) == 0);
    assert(x.test_range_sec(7,9));

    printf("+++++ passed test06\n");
}

// Test autodispatch but with remove of timer calls as means to close out
// the scheduler.
void test07()
{
    printf("Start test07\n");
    test_timer x;
    sched_auto.clean();
    size_t t1 = sched_auto.add_timer(3 * SECOND, _RepeatingTimer, (void*)"3");
    size_t t2 = sched_auto.add_timer(2 * SECOND, _RepeatingTimer, (void*)"2");
    size_t t3 = sched_auto.add_timer(1 * SECOND, _RepeatingTimer, (void*)"1");
    size_t t4 = sched_auto.add_timer(4 * SECOND, _RestartingTimer, (void*)"4");

    // calls the stop thread function after 30 seconds.
    size_t t5 = sched_auto.add_timer(30 * SECOND, 
                   _stopsched_autoDispatcherThread, (void*)"Nothing");

    // wait for the dispatcher thread to rejoin when the _stopDispatcher
    // function runs.

    Time::sleep(4 * SECOND);

    sched_auto.remove_timer(t1);
    sched_auto.remove_timer(t2);
    sched_auto.remove_timer(t3);
    sched_auto.remove_timer(t4);
    sched_auto.remove_timer(t5);

    void * value;
    assert(Thread::join(sched_auto.thread_id(), value) == 0);

    assert(x.test_range_sec(3,6));

    x.restart();
    // Run a second test to assure it works the second time
    sched_auto.add_timer(3 * SECOND, _RepeatingTimer, (void*)"3");

    // calls the stop thread function after 8 seconds.
    sched_auto.add_timer(8 * SECOND, _stopsched_autoDispatcherThread,
                         (void*)"8");

    assert(Thread::join(sched_auto.thread_id(), value) == 0);
    assert(x.test_range_sec(7,9));

    printf("+++++ passed test07\n");
}

int main(int argc, char** argv)
{
    printf("Test+++ %s\n",argv[0]);
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();

    printf("+++++ passed all tests\n");

    return 0;
}

