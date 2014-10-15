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

#ifndef _cimple_Cond_Queue_h
#define _cimple_Cond_Queue_h

#include "config.h"
#include "Cond.h"

CIMPLE_NAMESPACE_BEGIN

/** This class provides a thread-safe condition queue
*   implementation so that threads may exchange data. The
*   dequeue() function blocks until an entry is available. The
*   enqueue() method blocks until there are less than max_size
*   elements.
*/
class CIMPLE_CIMPLE_LINKAGE Cond_Queue
{
public:

    /**
     * Construct a conditon queue with a maximum size defined 
     * by the variable. The enqueue method() blocks until there are
     * less than #max_size# elements in the queue. 
     *  
     * @param max_size size_t defining the number of elements in the 
     * queue before the enqueue() blocks. 
     */
    Cond_Queue(size_t max_size);

    ~Cond_Queue();

    /**
     * Enqueue an entry to the condition queue 
     *  
     * @param entry void* Any single pointer entitiy can be enqueued 
     * and will be passed to the dequeue 
     */
    void enqueue(void* entry);

    /**
     * Dequeue an entry from the condition queue. The dequeue blocks 
     * until there is an entry available in the queue. 
     *  
     * @return void* entry that was enqueued to the queue. 
     */
    void* dequeue();

private:

    Cond_Queue(const Cond_Queue&);
    Cond_Queue& operator=(const Cond_Queue&);

    enum { MAX_AUTO_ELEMENTS = 8 };

    // Used instead of heap memory when max_size <= MAX_AUTO_ELEMENTS.
    void* _auto_data[MAX_AUTO_ELEMENTS];

    void** _data;
    size_t _size;
    size_t _head;
    size_t _tail;
    size_t _max_size;

    Mutex _lock;
    Cond _not_empty;
    Cond _not_full;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Cond_Queue_h */
