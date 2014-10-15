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

#include "Atomic.h"
#include "config.h"


#if defined(CIMPLE_PLATFORM_WIN32_IX86_MSVC)

#include <intrin.h>

CIMPLE_NAMESPACE_BEGIN

void Atomic_create(Atomic* atomic, int x)
{
    atomic->n = long(x);
}

void Atomic_destroy(Atomic* atomic)
{
}

int Atomic_get(const Atomic* atomic)
{
    return int(atomic->n);
}

void Atomic_set(Atomic* atomic, int x)
{
    atomic->n = long(x);
}

void Atomic_inc(Atomic* atomic)
{
    _InterlockedIncrement(&atomic->n);
}

int Atomic_dec_and_test(Atomic* atomic)
{
    return _InterlockedDecrement(&atomic->n) == 0;
}

void Atomic_dec(Atomic* atomic)
{
    _InterlockedDecrement(&atomic->n);
}

#endif /* defined(CIMPLE_PLATFORM_WIN32_IX86_MSVC) */

CIMPLE_NAMESPACE_END
