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
    Test of the condition variable mechanism that creates a consumer and
    producer thread as detachable threads. 
*/
#include <cassert>
#include <cimple/config.h>
#include <cimple/Thread.h>
#include <cimple/Cond.h>
#include <cimple/Time.h>
#include <cimple/Mutex.h>

using namespace cimple;

//#include <pthread.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
//#include <unistd.h>
//#include <string.h>

void* producer_signal (void* arg);
void* producer_broadcast (void* arg);

void* consumer (void* arg);

int condition = 0;
int consumers_completed = 0;

Mutex mutex(false);
Cond cond;

int main(int argc, char *argv[])
{
    int r;
    void* value = 0;

    // Test of condition variable.
    Thread thread2;
    r = Thread::create_joinable(thread2, consumer, NULL);
    assert(r == 0);

    Thread thread1;
    r = Thread::create_joinable(thread1, producer_signal, NULL);
    assert(r == 0);

    r = Thread::join(thread1, value);
    assert(r == 0);

    r = Thread::join(thread2, value);
    assert(r == 0);

    // Repeat the test but with single consumers and
    // using the producer that broadcasts.
    // 
    condition = 0;
    Thread thread4;
    r = Thread::create_joinable(thread4, consumer, NULL);
    assert(r == 0);

    Thread thread3;
    r = Thread::create_joinable(thread3, producer_broadcast, NULL);
    assert(r == 0);

    r = Thread::join(thread3, value);
    assert(r == 0);

    r = Thread::join(thread4, value);
    assert(r == 0);

    //
    // Test broadcast with multiple consumers outstanding
    // Start two consumers and broadcast the condition to both of them.
    // 
    consumers_completed = 0;
    r = Thread::create_joinable(thread2, consumer, NULL);
    assert(r == 0);

    r = Thread::create_joinable(thread3, consumer, NULL);
    assert(r == 0);

    r = Thread::create_joinable(thread1, producer_broadcast, NULL);
    assert(r == 0);

    // Join all of the started threads

    r = Thread::join(thread1, value);
    assert(r == 0);

    r = Thread::join(thread2, value);
    assert(r == 0);

    r = Thread::join(thread3, value);
    assert(r == 0);

    assert(consumers_completed == 2);

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}

// Producer waits a second and then increments a variable and
// signals the consumer that the varaible has been incremented.
void* producer_signal (void* arg)
{
    printf ("Signaling Producer: making item.\n");
    Time::sleep (1 * Time::SEC);

    mutex.lock();
    condition++;
    cond.signal();
    mutex.unlock();

    return NULL;
}

// Producer waits a second and then increments a variable and
// signals the consumer that the varaible has been incremented.
void* producer_broadcast (void* arg)
{
    printf ("Broadcasting Producer: making item.\n");
    Time::sleep (2 * Time::SEC);

    mutex.lock();

    condition++;
    cond.broadcast();

    mutex.unlock();

    return NULL;
}

void* consumer (void* arg)
{
    printf ("Consumer: waiting...\n");

    mutex.lock();

    //while (!condition)
    cond.wait(mutex);

    assert(condition != 0);
    consumers_completed++;
    mutex.unlock();
    printf ("Consumer: got it!\n");

    return NULL;
}
