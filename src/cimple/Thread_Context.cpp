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

#include <pthread.h>
#include "Array.h"
#include "Thread_Context.h"

CIMPLE_NAMESPACE_BEGIN

Thread_Context::~Thread_Context()
{
}

struct Stack
{
    enum { MAX_SIZE = 16 };
    Thread_Context* data[MAX_SIZE];
    size_t size;
};

static pthread_key_t _key;
static pthread_once_t _key_once = PTHREAD_ONCE_INIT;

static void _make_key()
{
    pthread_key_create(&_key, NULL);
}

static Stack* _stack()
{
    pthread_once(&_key_once, _make_key);

    Stack* stack = (Stack*)pthread_getspecific(_key);

    if (stack == 0)
    {
	stack = new Stack;
	stack->size = 0;
	pthread_setspecific(_key, stack);
    }

    return stack;
}

void Thread_Context::push(Thread_Context* context)
{
    assert(context != 0);
    Stack* stack = _stack();
    assert(stack->size < Stack::MAX_SIZE);
    stack->data[stack->size++] = context;
}

void Thread_Context::pop()
{
    Stack* stack = _stack();
    assert(stack->size > 0);
    stack->size--;

    if (stack->size == 0)
    {
	pthread_setspecific(_key, NULL);
	delete stack;
    }
}

Thread_Context* Thread_Context::top()
{
    Stack* stack = _stack();

    if (stack->size != 0)
	return stack->data[stack->size-1];

    return 0;
}

CIMPLE_NAMESPACE_END
