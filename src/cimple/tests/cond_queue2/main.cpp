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

#include <cassert>
#include <cimple/config.h>
#include <cimple/Threads.h>
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

static void* _reader(void* arg)
{
    Cond_Queue* queue = (Cond_Queue*)arg;

    for (size_t i = 0; i < NUM_WRITES; i++)
    {
	void* entry = queue->dequeue();
	assert(size_t(entry) == i);
	// printf("reader: %zu\n", (size_t)entry);
    }

    return 0;
}

int main(int argc, char** argv)
{
    Cond_Queue queue(1);

    Thread thread;
    Threads::create_joinable(thread, _reader, &queue);

    _writer(&queue);

    printf("+++++ passed all tests\n");

    return 0;
}
