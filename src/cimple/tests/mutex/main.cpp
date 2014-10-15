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

#include <cassert>
#include <cimple/Mutex.h>
#include <pthread.h>
#include <cimple/Time.h>
#include <cimple/Thread.h>
#include <cimple/Array.h>

using namespace cimple;

#define TRACE CIMPLE_TRACE;

// Replacement for assert that prints out error and continues
#define TASSERT(X) if(!(X)) printf \
                       ("Test failed %u. continuing\n", __LINE__)

// Test timer class to allow testing for time delays in the
// other tests. Starts a timer and provides for accessing the
// timer and testing the current interval against a range.

class test_timer
{
public:

    /** 
     * Create a new test timer and set the time to NOW
     * 
     */
    test_timer(){_starttime = Time::now();}

    ~test_timer(){}

    /** 
     * restart an existing timer and set time to now
     * 
     */
    void restart(){ _starttime = Time::now();}

    /** return milliseconds since test_timer created or restarted
    */
    uint32 get_interval_ms()
    {
        return((uint32)((Time::now() - _starttime)/1000));
    }

    // test range of expired time in milliseconds
    bool test_range_ms(uint32 nominal, uint32 range)
    {
        uint32 t = get_interval_ms();
        if ((t >= nominal-range) && t <= nominal+range )
            return true;

        printf("test_timer failed. rtnd %u ms. min %u ms max %u ms\n",
               t, nominal-range, nominal+range);
        return false;
    }
    // test range of expired time in seconds
    bool test_range_sec(uint32 nominal, uint32 range)
    {
        uint32 t = get_interval_ms();
        uint32 min = (nominal-range) * 1000;
        uint32 max = (nominal+range) * 1000;
        if (t >= min && t <= max )
            return true;

        printf("test_timer failed. rtnd %u sec. min %u sec max %u sec\n",
               t/1000, min, max);
        return false;
    }

private:
    uint64 _starttime;
};

/** 
 * Gather and present statistics in as a histogram.  The
 * constructor defines the dimensions for the statistics to be
 * gathered.  The inc function increments a specific value slot
 * in the histogram.  The print function returns the gathered
 * data.
 * Data out of the range of the defined histogram
 * Shows how many of the values presented appear in each slot
 * defined by the resolution, max and min parameters.
 * NOTE: This does not present the data in the form of a
 * graphical histogram.  It is, in reality a means to gather
 * statistical data by counting the number of times particular
 * values occur.
 */
class histogram
{
public:
    /**
     * Constructor.  Creates a histogram object with a defined 
     * number of slots and a range for each slot. 
     * @param resolution for each slot 
     * @param max maximum value that will be counted in the 
     *            histogram
     * @param min minimum value that will be counted in the 
     *            histogram
     */
    histogram(uint32 resolution, uint32 max, uint32 min)
    {
        _max = max;
        _min = min;
        _resolution = resolution;
        _slots = (max - min + 2)/_resolution;
        _total = 0;
        countTooLarge = 0;
        countTooSmall = 0;

        dataArray.reserve(_slots);

        for (uint32 i = 0 ; i < _slots ; i++)
            dataArray.append(0);
    }

    ~histogram(){};

    /** 
     * Increment the count for the defined value.
     * 
     * @param value
     */
    void inc(sint64 value)
    {
        //_mutex.lock();
        _total++;
        if (value > _max)
            countTooLarge++;

        else if (value < _min)
            countTooSmall++;

        else
        {
            uint64 v = (value - _min)/_resolution;
            dataArray[v]++;
        }
        //_mutex.unlock();
    }

    uint32 getMax()
    {
        uint32 rtn = 0;
        for (uint32 i = 0 ; i < dataArray.size(); i++)
        {
            if ((dataArray[i] != 0) && (i > rtn))
                rtn = i;
        }
        return ((rtn * _resolution) + _min);
    }

    uint32 getMin()
    {
        uint32 rtn = CIMPLE_UINT32_MAX;
        for (uint32 i = 0 ; i < dataArray.size(); i++)
        {
            if ((dataArray[i] != 0) && (i < rtn))
                rtn = i;
        }
        return ((rtn * _resolution) + _min);
    }

    void print(boolean all = true)
    {
        printf("     Value      Count Percentage\n");
        if (countTooSmall != 0)
        {
            printf("min ERROR %lu %lu%% \n",(long unsigned int)countTooSmall,
                    (long unsigned int)((countTooSmall*100)/_total));
        }
        for (uint32 i = 0 ; i < dataArray.size() ; i++)
        {
            if (all || (dataArray[i] != 0))
            {
                printf("%10lu %10lu %lu%%\n",
                    (long unsigned int)((i * _resolution) + _min),
                    (long unsigned int)dataArray[i],
                    (long unsigned int)((dataArray[i] * 100) / _total));
            }
        }
        if (countTooLarge != 0)
        {
            printf("max ERROR %lu %lu%%\n",(long unsigned int)countTooLarge,
                   (long unsigned int)((countTooLarge*100)/_total));
        }
    }

private:
    uint32 _slots;
    uint32 _resolution;
    uint32 _max;
    uint32 _min;
    Array<uint64> dataArray;
    sint64 countTooLarge;
    sint64 countTooSmall;
    uint64 _total;
    //Mutex _mutex(false);
};

//---test01---------------------------------------------------------------------
// 
// simple mutex tests in a single thread.
void test01()
{
    printf("test01 Start\n");
    // create a non-recursive mutex
    Mutex m(false);

    // Lock and unlock the mutex
    m.lock();
    m.unlock();

    // test try_lokc and if successful, unlock
    assert(m.try_lock() == 0);
    m.unlock();

    // test the try_lock against an already locked mutex.
    m.lock();

    int rtncode = m.try_lock();
    //printf("test_mutex. try_lock rtn code = %u\n", rtncode);

    assert(rtncode == CIMPLE_EBUSY);

    m.unlock();

    //
    // recursive Mutex test. The default is recursive
    //

    Mutex n;
    n.lock();
    n.unlock();

    n.try_lock();
    n.unlock();

    n.lock();
    rtncode = n.try_lock();
    assert(rtncode == 0);
    n.unlock();

    {
        Mutex nonRecursiveMutex(false);
        test_timer x;
        for (int i = 0 ; i < 10 ; i++)
        {
            nonRecursiveMutex.lock();
            Time::sleep(100 * Time::MSEC);
            nonRecursiveMutex.unlock();
        }
        TASSERT(x.test_range_ms(1000, 300));
    }

    {
        Mutex RecursiveMutex(true);
        test_timer x;
        for (int i = 0 ; i < 10 ; i++)
        {
            RecursiveMutex.lock();
            Time::sleep(100 * Time::MSEC);
            RecursiveMutex.unlock();
        }
        TASSERT(x.test_range_ms(1000, 100));
    }
    printf("Test01 Passed\n");
}


// Test recursive locks.
void test01a()
{
    printf("Test01a Start\n");

    uint32 lock_depth = 200;
    test_timer t;
    Mutex m;

    for (uint32 i = 0 ; i < lock_depth ; i++ )
    {
        m.lock();
    }
    for (uint32 i = 0 ; i < lock_depth ; i++ )
    {
        m.unlock();
    }

    m.unlock();

    for (uint32 i = 0 ; i < lock_depth ; i++ )
    {
        m.try_lock();
    }
    for (uint32 i = 0 ; i < lock_depth ; i++ )
    {
        m.unlock();
    }

    m.unlock();

    printf("Test01a Passed in %u ms\n", t.get_interval_ms() );
}

//------------------------------------------------------------------------------
// test02 - nonrecursive mutex in a thread.  The process should take as long
// as the total of all the sleeps since the mutex should block the thread
// to serial operation.
static Mutex _procMutex(false);

// thread proc used by test02. Locks and waits defined time. Then
// unlocks and exits thread.
// This should cause all calls to be executed in series.
static void* _proc(void* arg)
{
    _procMutex.lock();
    char* str = (char*)arg;
    //printf("_proc [%s]\n", str);
    Time::sleep(100 * Time::MSEC);

    _procMutex.unlock();

    Thread::exit(arg);

    return arg;
}


void test02()
{
    printf("Test02 Start\n");
    test_timer test2;
    const size_t N = 160;
    Thread threads[N];

    // create N joinable threads that call _proc
    for (size_t i = 0; i < N; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        int r = Thread::create_joinable(threads[i], _proc, strdup(buffer));
        assert(r == 0);
    }

    // Join all of the created threads.
    for (size_t i = 0; i < N; i++)
    {
        // Create corresponding counter for join.
        char buffer[64];
        sprintf(buffer, "%d", int(i));

        // execute the join
        void* value = 0;
        int r = Thread::join(threads[i], value);
        //printf("join[%s][%s]\n", (char*)value, buffer);
        assert(r == 0);

        // test that we have returned the proper arg value
        assert(strcmp(buffer, (char*)value) == 0);
        free(value);
    }
    // originally second parameter was 100 for 64 bit linux.
    // Windows required expansion to 3000.
    TASSERT(test2.test_range_ms(N * 100, 3000));

    printf("Test02 Passed in %u ms\n", test2.get_interval_ms() );
}


//----Test03--------------------------------------------------------------------
// 

// thread proc that simply waits and returns.

static void* _nonblock_proc(void* arg)
{
    char* str = (char*)arg;
    //printf("_nonblock_proc [%s]\n", str);
    Time::sleep(100 * Time::MSEC);
    Thread::exit(arg);

    return arg;
}


//----Test03--------------------------------------------------------------------
// 
// run a test consisting of creating a joinable thread that does a sleep
// and return N times.  A recursivemutex is set before the thread is called and
// reset after it joins. With a nonrecursive thread, the whole proces
// is run in parallel for each thread.
// Success is if the whole process finishes in very little more than the
// time for one sleep in the thread proc.
// 
void test03()
{

    printf("Test03 Start\n");
    Mutex m(true);
    Thread threads[160];

    test_timer test3;

    // Create N joinable threads using the _nonblock_proc
    for (size_t i = 0; i < 160; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        m.lock();
        int r = Thread::create_joinable(threads[i],
            _nonblock_proc, strdup(buffer));
        assert(r == 0);
    }

    for (size_t i = 0; i < 160; i++)
    {
        // recreate corresponding counter for join.
        char buffer[64];
        sprintf(buffer, "%d", int(i));

        // execute the join
        void* value = 0;
        int r = Thread::join(threads[i], value);
        m.unlock();
        //printf("join[%s][%s]\n", (char*)value, buffer);
        assert(r == 0);

        // test that we have returned the proper arg value
        assert(strcmp(buffer, (char*)value) == 0);
        free(value);
    }

    // was 100, 50 but made larger to pass vg tests.
    // Changed this from 100, 50 to 1000, 900 because failing on
    // 32 bit systems. Set very large to accomodate virtual
    // environments
    TASSERT(test3.test_range_ms(2000, 1000));
    printf("Test03 Passed in %u ms\n", test3.get_interval_ms() );
}


//----Test04--------------------------------------------------------------------

/*
This function simulates a number of threads working on a parallel
  problem. The threads use try_lock() so that
  they do not spend time blocking on a mutex and instead spend more
  of the time making progress towards the final solution. When
  trylock fails, the processing is done locally, eventually to
  be merged with the final parallel solution.

  Note that this is as much a demonstration as a test.
*/
#define WORKLOOP 100000
#define THREADS 100
#define WORKSIZE 10

Array<uint64> workArray;

// Define a nonrecursive lock
static Mutex workLock(false);

// Simulates doing some work by adding input to all entries in an array
// defined by workArray
void doWork(uint32 count)
{
        for (uint32 i = 0 ; i < workArray.size(); i++ )
        {
            workArray[i] += count;
        }
}

// define the histogram that gathers statistics on the percentage of 
// bursts that were calculated locally in the function vs a thread.
// The idea is that if try_lock is really working, some work should be 
// processed in each.
static histogram h(20, 100, 0);

// for each thread execute the work function WORKLOOP times.  If the
// work function is busy, execute it in this thread. The try_lock allows
// us to do this.
static void *threadfunc(void *parm)
{
    uint32 localProcessingCompleted = 0;
    uint32 numberOfLocalProcessingBursts = 0;
    uint32 processingCompletedThisBurst = 0;

    for (int i = 0; i < WORKLOOP; ++i)
    {
        // test lock
        int rc;
        rc = workLock.try_lock();
        if (rc != 0)
        {
            assert(rc == CIMPLE_EBUSY);
            /* Continue processing the part of the problem   */
            /* that we can without the lock. We do not want to waste */
            /* time blocking. Instead, we'll count locally.          */
            ++localProcessingCompleted;
            ++numberOfLocalProcessingBursts;
            continue;
        }

        /* Acquired the lock, so this part of the can be global*/
        /* Processing completed consist of last local processing  */
        /* plus the 1 unit of processing this time through        */
        processingCompletedThisBurst = 1 + localProcessingCompleted;
        localProcessingCompleted = 0;

        // do some work

        doWork(processingCompletedThisBurst);
       
        workLock.unlock();
    }
    /* If any local processing remains, merge it with the global*/
    /* problem so our part of the solution is accounted for     */
    if (localProcessingCompleted)
    {
        workLock.lock();

        // do some work
        doWork(localProcessingCompleted);
        
        workLock.unlock();
    }

    h.inc ((numberOfLocalProcessingBursts * 100) / WORKLOOP);
    //printf("Thread processed about %d%% of the problem locally\n",
    //     (numberOfLocalProcessingBursts * 100) / WORKLOOP);
    return NULL;
}

void test04()
{
    printf("Start Test04\n");

    test_timer test4;
    Thread threads[THREADS];
    int rc=0;

    for (int i = 0 ; i < WORKSIZE; i++ )
    {
        workArray.append(0);
    }

    // Create and start all the threads
    for (int i = 0; i < THREADS; ++i)
    {
        int rc;
        rc = Thread::create_joinable(threads[i], threadfunc, NULL);
        assert(rc == 0);
    }

    // join all of the threads we created
    for (int i=0; i < THREADS; ++i)
    {
        void* value = 0;
        int rc;
        rc = Thread::join(threads[i], value);
        assert(rc == 0);
    }

    // test to be sure we accurately counted all the
    // entries in the workArray
    for (uint32 i = 0 ; i < workArray.size(); i++ )
    {
        assert(workArray[i] += THREADS * WORKLOOP);
    }
    h.print(false);
    printf("max = %u. min = %u\n", h.getMax(), h.getMin());

    TASSERT(h.getMax() == 80);
    if (h.getMax() != 80)
    {
        printf("Issue here.  h.getMax() should == 80\n");
    }
    // TODO fix so this becomes permanent assert ks Apr 2010
    TASSERT(h.getMin() != 80);

    printf("Test04 Passed in %u ms\n", test4.get_interval_ms() );
}


int main(int argc, char** argv)
{


    test01();

    test01a();

    test02();

    test03();

    test04();

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

