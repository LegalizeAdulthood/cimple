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

#include "Mutex.h"
#include <pthread.h>

CIMPLE_NAMESPACE_BEGIN

Mutex::Mutex(bool recursive)
{
    assert(sizeof(_rep) >= sizeof(pthread_mutex_t));

    if (recursive)
    {
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init((pthread_mutex_t*)_rep, &attr);
	pthread_mutexattr_destroy(&attr);
    }
    else
	pthread_mutex_init((pthread_mutex_t*)_rep, NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy((pthread_mutex_t*)_rep);
}

void Mutex::lock()
{
    pthread_mutex_lock((pthread_mutex_t*)_rep);
}

void Mutex::unlock()
{
    pthread_mutex_unlock((pthread_mutex_t*)_rep);
}

CIMPLE_NAMESPACE_END
