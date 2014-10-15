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

#include "config.h"
#include "Mutex.h"

CIMPLE_NAMESPACE_BEGIN

/** The Cond class implements a conditional variable, similar to
*   the POSIX-threads conditional variable concept.  A condition
*   variable is used with appropriate functions for waiting and
*   thread continuation. It allows a thread to give up execution
*   until a defined condition is true. Note that a condition
*   variable must always be used in conjunction with a mutex to
*   avoid race conditions. Signals are not remembered, which
*   means that threads must already be waiting for a signal to
*   receive it.
*   Example:
*   \code
*   Cond cond1;
    Mutex mutex1;
    int count = Some Initial value;
    // The take_action is executed when the counter() is called enough times
    // so that count decrements to zero.
    
    action()
    { ...
        mutex1.lock();
*       // action gives up control until condition variable == 0
        while (count <> 0)
            cond1.wait(mutex1);
        
        mutex1.unlock();
        take_action();
    }
 
    counter()
    {
        ...
*       // lock the mutex decrement and test counter 
*       // the lock is used to avoid race conditions
        mutex1.lock();
        count--;
        if (count==0)
            cond1.signal();
        mutex1.unlock();
*   }
*   \endcode
*/
class CIMPLE_CIMPLE_LINKAGE Cond
{
public:
    
    /** Constructor.
    */
    Cond();

    /** Destructor.
    */
    ~Cond();

    /** Wakes up one of the threads that is blocking on the wait() method.
    */
    void signal();

    /** Blocks until a thread calls signal(). The mutex is unlocked while
    *   the thread is waiting and relocked upon wakeup.
    *   @param lock Mutex that is unlocked while the thread is
    *   waiting and relocked upon wakeup.
    */
    void wait(Mutex& lock);

private:
    Cond(const Cond&);
    Cond& operator=(const Cond&);
    union
    {
        double alignemnt;
        char _rep[128];
    };
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Cond_h */
