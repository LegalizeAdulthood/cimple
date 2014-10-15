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

#ifndef _cimple_Predicate_h
#define _cimple_Predicate_h

#include "config.h"
#include "Cond.h"

CIMPLE_NAMESPACE_BEGIN

/** This class enables one or more threads to signal a waiting thread. The 
    waiter blocks on wait() until any other thread calls signal(), which causes
    wait to unblock and return. If the signaling thread calls signal() before
    the waiting thread calls wait(), then wait returns without waiting.
    The reset() method restores thte object to its unsignaled state so that
    the scenario can be repeated again.
*/
class CIMPLE_CIMPLE_LINKAGE Predicate
{
public:
    
    Predicate(int n = 1);

    ~Predicate();

    void reset(int n = 1);

    void signal();

    void wait();

private:

    Predicate(const Predicate&);
    Predicate& operator=(const Predicate&);

    int _n;
    Mutex _mutex;
    Cond _cond;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Predicate_h */
