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

#ifndef _cimple_Atomic_DARWIN_PPC_GNU_h
#define _cimple_Atomic_DARWIN_PPC_GNU_h

#include "config.h"

#define CIMPLE_ATOMIC_INITIALIZER { 0 }

CIMPLE_NAMESPACE_BEGIN

//------------------------------------------------------------------------------
// WARNING: this implementation does not work on multi-processor PPC 
// architectures or on the IBM-405 processor.
//------------------------------------------------------------------------------

CIMPLE_NAMESPACE_BEGIN

struct Atomic
{ 
    volatile int n; 
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
    atomic->n = x;
}

static __inline__ void Atomic_inc(Atomic* atomic)
{
    int t;

    __asm__ __volatile__(
        "1: lwarx %0,0,%2\n"
        "addic %0,%0,1\n"
        "stwcx. %0,0,%2\n"
        "bne- 1b"
        : "=&r" (t), "=m" (atomic->n)
        : "r" (&atomic->n), "m" (atomic->n)
        : "cc");
}

static __inline__ int Atomic_dec_and_test(Atomic* atomic)
{
    int n;

    __asm__ __volatile__(
        "1: lwarx %0,0,%1\n"
        "addic %0,%0,-1\n"
        "stwcx. %0,0,%1\n"
        "bne- 1b"
        : "=&r" (n)
        : "r" (&atomic->n)
        : "cc", "memory");

    return n == 0;
}

static __inline__ void Atomic_dec(Atomic* atomic)
{
    int n;

    __asm__ __volatile__(
        "1: lwarx %0,0,%2\n"
        "addic %0,%0,-1\n"
        "stwcx. %0,0,%2\n"
        "bne- 1b"
        : "=&r" (n), "=m" (atomic->n)
        : "r" (&atomic->n), "m" (atomic->n)
        : "cc");
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Atomic_DARWIN_PPC_GNU_h */
