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

#include "Predicate.h"
#include "Auto_Mutex.h"

CIMPLE_NAMESPACE_BEGIN

Predicate::Predicate(int n) : _n(n)
{
}

Predicate::~Predicate()
{
}

void Predicate::reset(int n)
{
    Auto_Mutex auto_mutex(_mutex);
    _n = n;
    _cond.signal();
}

void Predicate::signal()
{
    Auto_Mutex auto_mutex(_mutex);
    _n--;
    _cond.signal();
}

void Predicate::wait()
{
    Auto_Mutex auto_mutex(_mutex);

    while (_n > 0)
        _cond.wait(_mutex);
}

CIMPLE_NAMESPACE_END
