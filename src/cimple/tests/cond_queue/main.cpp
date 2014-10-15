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
#include <cimple/config.h>
#include <cimple/Thread.h>
#include <cimple/Cond_Queue.h>
#include <cimple/Time.h>

using namespace cimple;

static Mutex _finished_lock;
static Cond _finished;
static bool _success = false;

const size_t NUM_WRITES = 100000;

static void* _writer(void* arg)
{
    Cond_Queue* queue = (Cond_Queue*)arg;

    for (size_t i = 0; i < NUM_WRITES; i++)
    {
        // printf("writer: %u\n", i);
        queue->enqueue((void*)i);
    }

    Time::sleep(10000 * 1000);

    return 0;
}

static void* _reader(void* arg)
{
    Cond_Queue* queue = (Cond_Queue*)arg;

    for (size_t i = 0; i < NUM_WRITES; i++)
    {
        // printf("reader: %u\n", i);
        void* entry = queue->dequeue();
        assert((size_t)entry == i);
    }

    Time::sleep(500 * 1000);
    _success = true;
    _finished.signal();

    return 0;
}

int main(int argc, char** argv)
{
    Cond_Queue queue(16);

    Thread thread2;
    Thread::create_detached(thread2, _writer, &queue);

    Thread thread1;
    Thread::create_detached(thread1, _reader, &queue);

    _finished_lock.lock();
    _finished.wait(_finished_lock);

    assert(_success == true);
    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

