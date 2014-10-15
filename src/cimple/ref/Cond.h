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

#ifndef _cimple_Cond_h
#define _cimple_Cond_h

#include <pthread.h>
#include "config.h"
#include "Mutex.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LIBCIMPLE_LINKAGE Cond
{
public:
    
    Cond();

    void signal();

    void broadcast();

    void wait(Mutex& lock);

    int wait(Mutex& lock, uint64 timeout_usec);

private:

    Cond(const Cond&);
    Cond& operator=(const Cond&);

    pthread_cond_t _cond;
};

inline Cond::Cond()
{
    pthread_cond_init(&_cond, 0);
}

inline void Cond::signal()
{
    pthread_cond_signal(&_cond);
}

inline void Cond::broadcast()
{
    pthread_cond_broadcast(&_cond);
}

inline void Cond::wait(Mutex& lock)
{
    pthread_cond_wait(&_cond, &lock._mut);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Cond_h */
