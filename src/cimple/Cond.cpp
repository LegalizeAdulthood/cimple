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
#include <pthread.h>
#include "Cond.h"
#include "Time.h"

CIMPLE_NAMESPACE_BEGIN

Cond::Cond()
{
    assert(sizeof(_rep) >= sizeof(pthread_cond_t));
    pthread_cond_init((pthread_cond_t*)_rep, 0);
}

Cond::~Cond()
{
    pthread_cond_destroy((pthread_cond_t*)_rep);
}

void Cond::signal()
{
    pthread_cond_signal((pthread_cond_t*)_rep);
}

void Cond::wait(Mutex& lock)
{
    pthread_cond_wait((pthread_cond_t*)_rep, (pthread_mutex_t*)lock._rep);
}

void Cond::broadcast()
{
    pthread_cond_broadcast((pthread_cond_t*)_rep);
}

CIMPLE_NAMESPACE_END

