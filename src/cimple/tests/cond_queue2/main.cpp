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
    Test of condition queue mechanism where a writer operating on the main
    thread writes to a queue that is read by a reader  operating on
    a joinable thread
*/

#include <cassert>
#include <cimple/config.h>
#include <cimple/Thread.h>
#include <cimple/Cond_Queue.h>
#include <cimple/Time.h>

using namespace cimple;

const size_t NUM_WRITES = 100000;

static void* _writer(void* arg)
{
    Cond_Queue* queue = (Cond_Queue*)arg;

    for (size_t i = 0; i < NUM_WRITES; i++)
    {
        // printf("writer: %zu\n", i);
        queue->enqueue((void*)i);
    }

    return 0;
}
static size_t number_read = 0;

static void* _reader(void* arg)
{
    // get the condition queue from the arg parameter.
    Cond_Queue* queue = (Cond_Queue*)arg;

    for (size_t i = 0; i < NUM_WRITES; i++)
    {
        void* entry = queue->dequeue();
        assert(size_t(entry) == i);
        number_read++;
        // printf("reader: %zu\n", (size_t)entry);
    }

    return 0;
}

int main(int argc, char** argv)
{
    // define a condition queue
    Cond_Queue queue(1);

    // Create the _reader thread with the condition queue as the
    // arg parameter
    
    Thread thread;
    Thread::create_joinable(thread, _reader, &queue);

    // call the writer to enqueue things.

    _writer(&queue);

    // Wait for the thread to join before terminating.
    void * value;
    Thread::join(thread, value);

    assert(number_read == NUM_WRITES);

    printf("+++++ passed all tests\n");

    return 0;
}

