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

#ifndef _cimple_Atomic_VXWORKS_XSCALE_GNU_h
#define _cimple_Atomic_VXWORKS_XSCALE_GNU_h

#include "config.h"
#include <intLib.h>

#define CIMPLE_ATOMIC_INITIALIZER { 0 }

CIMPLE_NAMESPACE_BEGIN

struct Atomic
{
    volatile unsigned int n;
};

inline void Atomic_create(Atomic* atomic, int x)
{
    atomic->n = x;
}

inline void Atomic_destroy(Atomic* atomic)
{
}

inline int Atomic_get(const Atomic* atomic)
{
    return atomic->n;
}

inline void Atomic_set(Atomic* atomic, int x)
{
    int key = intLock();
    atomic->n = x;
    intUnlock(key);
}

static __inline__ void Atomic_inc(Atomic* atomic)
{
    int key = intLock();
    atomic->n++;
    intUnlock(key);
}

static __inline__ int Atomic_dec_and_test(Atomic* atomic)
{
    unsigned int n;
    int key = intLock();
    n = --atomic->n;
    intUnlock(key);

    return n == 0;
}

static __inline__ void Atomic_dec(Atomic* atomic)
{
    int key = intLock();
    atomic->n--;
    intUnlock(key);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Atomic_VXWORKS_XSCALE_GNU_h */
