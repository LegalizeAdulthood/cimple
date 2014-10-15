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
#include "Magic.h"
#include <pthread.h>

CIMPLE_NAMESPACE_BEGIN

struct MutexRep
{
    Magic<0x482A8C83> magic;
    pthread_mutex_t mutex;
};

Mutex::Mutex(bool recursive)
{
    new(_rep) MutexRep();

    if (recursive)
    {
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&((MutexRep*)_rep)->mutex, &attr);
	pthread_mutexattr_destroy(&attr);
    }
    else
	pthread_mutex_init(&((MutexRep*)_rep)->mutex, NULL);
}

Mutex::~Mutex()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);
    pthread_mutex_destroy(&((MutexRep*)_rep)->mutex);
    ((MutexRep*)_rep)->~MutexRep();
}

void Mutex::lock()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);
    pthread_mutex_lock(&((MutexRep*)_rep)->mutex);
}

void Mutex::unlock()
{
    CIMPLE_ASSERT(((MutexRep*)_rep)->magic);
    pthread_mutex_unlock(&((MutexRep*)_rep)->mutex);
}

CIMPLE_NAMESPACE_END
