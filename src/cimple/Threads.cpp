/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include "Threads.h"

CIMPLE_NAMESPACE_BEGIN

Thread::~Thread()
{
    if (_has_attr)
        pthread_attr_destroy(&_attr);
}

int Threads::create_detached(Thread& thread, Thread_Proc proc, void* arg)
{
    thread._has_attr = true;
    pthread_attr_init(&thread._attr);
    pthread_attr_setdetachstate(&thread._attr, PTHREAD_CREATE_DETACHED);
    return pthread_create(&thread._rep, &thread._attr, proc, arg);
}

CIMPLE_NAMESPACE_END
