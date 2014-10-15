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

#ifndef _cimple_Id_Pool_h
#define _cimple_Id_Pool_h

#include "config.h"
#include "Array.h"
#include "Mutex.h"

CIMPLE_NAMESPACE_BEGIN

/** This class maintains a pool of integer identifiers. It
*   defines two operations: get() and put(). The get() method
*   obtains an integer identifier from the pool. The put()
*   method returns an integer identifier to the pool. All
*   outstanding identifiers are guaranteed to be unique.
*   Instances of this object can be safely shared among threads.
*   Note that get() never returns zero, so zero can be used to
*   represent the "null" id. Both get() and put() are O(1)
*   operations.
*  
*   The pool is of unlimited size and will use all uint32
*   integers except zero.
*/
class CIMPLE_CIMPLE_LINKAGE Id_Pool
{
public:

    /**
     * Constructor creates an Id Pool
     */
    Id_Pool();

    /**
     * Destructor
     */
    ~Id_Pool();

    /**
     * get an Id from the pool 
     * @return uint32 Id that is guaranteed to be unique among the 
     *         gotten Ids from this pool.  Zero is never returned
     */
    uint32 get();

    /**
     * return ad id to the pool.
     */
    void put(uint32 id);

private:

    Array<uint32> _pool;
    uint32 _next;
    Mutex _mutex;
}; 

CIMPLE_NAMESPACE_END

#endif /* _cimple_Id_Pool_h */
