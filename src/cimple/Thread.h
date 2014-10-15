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

#ifndef _cimple_Thread_h
#define _cimple_Thread_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN

typedef void* (*Thread_Proc)(void* arg);

class CIMPLE_CIMPLE_LINKAGE Thread
{
public:

    Thread();

    Thread(const Thread& x);

    ~Thread();

    Thread& operator=(const Thread& x);

    static int create_joinable(Thread& thread, Thread_Proc proc, void* arg);

    static int create_detached(Thread& thread, Thread_Proc proc, void* arg);

    static void exit(void* return_value);

    static int join(Thread& thread, void*& value_ptr);

    static bool equal(const Thread& thread1, const Thread& thread2);

    static Thread self();

private:

    char _rep[16];
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Thread_h */
