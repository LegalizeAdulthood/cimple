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

#include "Id_Pool.h"

CIMPLE_NAMESPACE_BEGIN

Id_Pool::Id_Pool() : _next(1)
{
}

Id_Pool::~Id_Pool()
{
}

uint32 Id_Pool::get()
{
    _mutex.lock();

    uint32 id;

    if (_pool.size())
    {
        size_t pos = _pool.size() - 1;
        id = _pool[pos];
        _pool.remove(pos);
    }
    else
        id = _next++;

    _mutex.unlock();

    return id;
}

void Id_Pool::put(uint32 id)
{
    _mutex.lock();
    _pool.append(id);
    _mutex.unlock();
}

CIMPLE_NAMESPACE_END
