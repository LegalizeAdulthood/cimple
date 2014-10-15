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

//
// Mutex return codes used by CIMPLE
//

#define CIMPLE_EBUSY 16

/**
 * Class defining Mutex with lock and unlock similar to Posix
 * Mutex. There is a a parameter option for recursive mutex 
 * capability. 
 */ 
class CIMPLE_CIMPLE_LINKAGE Mutex
{
public:
    /** 
     * Mutex constructor. Create a new mutex in the unlocked state. 
     * The input parameter determines whether the mutex will be 
     * recursive. 
     * @param recursive bool Optional parameter that determines if 
     * the mutex will be recursive.  If true the mutex will be
     * recursive. The default is true (recursive). If false a 
     * non-recursive mutex is created. 
     */
    Mutex(bool recursive = true);

    /**
     * Mutex destructor
     */
    ~Mutex();

    /**
     * Lock the mutex. If the mutex is locked wait for it to be 
     * unlocked. If the mutex is recursive this may be applied 
     * repeatedly by the thread owner and the mutex does not become 
     * unlocked until an unlock() call has been executed for each 
     * lock() call. 
     * Any error to a lock will cause an assert error in the code. 
     */
    void lock();

    /**
     * Try to lock the mutex without wait, this function returns an 
     * error code if the thread is locked. If the mutex is recursive
     * this may be applied repeatedly and the mutex does not become 
     * unlocked until an unlock() call has been executed for each 
     * lock() call. 
     *  
     * @return If the mutex is already locked , the try_lock() 
     *         returns non-zero. Note that any error except busy
     *         causes an assert so that a non=zero return means
     *         that the mutex is locked.
     */ 
    int try_lock();

    /**
     * Unlock the mutex.  If the mutex is recursive the mutex does 
     * not unlock until the number of unlock() calls matches the 
     * number of lock() calls. Note that the unlock() not check for 
     * errors so that unlock() to a Mutex that is not locked will 
     * not be detected. 
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
