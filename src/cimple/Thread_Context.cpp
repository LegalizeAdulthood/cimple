/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, 20007, 2008, 2009
**               Michael Brasher, Karl Schopmeyer
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

#ifdef CIMPLE_VXWORKS
# include "TSD.h"
#endif

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Thread-specific-data routines (VXWORKS)
//
//==============================================================================

#if defined(CIMPLE_VXWORKS)

static TSD _tsd;

static Thread_Context* _get_top()
{
    return (Thread_Context*)_tsd.get();
}

static void _set_top(Thread_Context* data)
{
    return _tsd.set(data);
}

#endif /* defined(CIMPLE_VXWORKS) */

//==============================================================================
//
// Thread-specific-data routines (non-VXWORKS)
//
//==============================================================================

#if !defined(CIMPLE_VXWORKS)

// Export to avoid multiple copies via shared libraries.
#ifdef CIMPLE_STATIC
CIMPLE_EXPORT 
#endif
pthread_key_t _thread_context_key;

// Export to avoid multiple copies via shared libraries.
#ifdef CIMPLE_STATIC
CIMPLE_EXPORT 
#endif
pthread_once_t _thread_context_key_once = PTHREAD_ONCE_INIT;

static void _make_key()
{
    pthread_key_create(&_thread_context_key, NULL);
}

static Thread_Context* _get_top()
{
    pthread_once(&_thread_context_key_once, _make_key);
    return (Thread_Context*)pthread_getspecific(_thread_context_key);
}

static void _set_top(Thread_Context* data)
{
    pthread_once(&_thread_context_key_once, _make_key);
    pthread_setspecific(_thread_context_key, data);
}

#endif /* !defined(CIMPLE_VXWORKS) */

//==============================================================================
//
// Thread_Context
//
//==============================================================================

Thread_Context::Thread_Context() : _next(0)
{
}

Thread_Context::~Thread_Context()
{
}

void Thread_Context::push(Thread_Context* context)
{
    Thread_Context* top = _get_top();

    if (top)
    {
        context->_next = top;
    }
    else
    {
        context->_next = 0;
    }

    _set_top(context);
}

void Thread_Context::pop()
{
    Thread_Context* top = _get_top();

    if (top)
    {
        _set_top(top->_next);
        top->_next = 0;
    }
}

Thread_Context* Thread_Context::top()
{
    return (Thread_Context*)_get_top();
}

CIMPLE_NAMESPACE_END
