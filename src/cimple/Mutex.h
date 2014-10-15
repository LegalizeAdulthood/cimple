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

#ifndef _cimple_Mutex_h
#define _cimple_Mutex_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN
/**
 * Class defining Mutex with lock and unlock similar to Posix
 * Mutex. There is an option for recursive mutex capability.
 */
class CIMPLE_CIMPLE_LINKAGE Mutex
{
public:

    /** 
     * Mutex constructor. The input parameter determines whether
     * themutex will be recursive
     * @param recursive bool Optional parameter that determines if 
     * the mutex will be recursive.  If true the mutex will be
     * recursive. The default is false (non-recursive).
     */
    Mutex(bool recursive = true);

    /**
     * Mutex destructor
     */
    ~Mutex();

    /**
     * Lock the mutex. If the mutex is recursive this may be applied
     * repeatedly and the mutex does not become unlocked until an 
     * unlock() call has been executed for each lock() call. 
     */
    void lock();

    /**
     * Unlock the mutex.  If the mutex is recursive the mutex does 
     * not unlock until the number of unlock() calls matches the 
     * number of lock() calls. 
     */
    void unlock();

private:

    union
    {
        double alignemnt;
        char _rep[128];
    };
    friend class Cond;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Mutex_h */
