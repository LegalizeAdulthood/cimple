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

#ifndef _cimple_Atomic_WIN32_IX86_MSVC_h
#define _cimple_Atomic_WIN32_IX86_MSVC_h


#include "config.h"

// The following definitions are necessary to avoid the inclusion of 
// windows.h, which causes symbol conflicts with CIMPLE.

extern "C" long __stdcall _InterlockedIncrement(long*);
extern "C" long __stdcall _InterlockedDecrement(long*);
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)

CIMPLE_NAMESPACE_BEGIN

struct Atomic
{
    long n;
};

inline void Atomic_create(Atomic* atomic, int x)
{
    atomic->n = long(x);
}

inline void Atomic_destroy(Atomic* atomic)
{
}

inline int Atomic_get(const Atomic* atomic)
{
    return int(atomic->n);
}

inline void Atomic_set(Atomic* atomic, int x)
{
    atomic->n = long(x);
}

static inline void Atomic_inc(Atomic* atomic)
{
    _InterlockedIncrement(&atomic->n);
}

static inline int Atomic_dec_and_test(Atomic* atomic)
{
    return _InterlockedDecrement(&atomic->n) == 0;
}

static inline void Atomic_dec(Atomic* atomic)
{
    _InterlockedDecrement(&atomic->n);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Atomic_WIN32_IX86_MSVC_h */
