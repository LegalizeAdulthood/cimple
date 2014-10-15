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

#include "Cond_Queue.h"
#include "Auto_Mutex.h"

CIMPLE_NAMESPACE_BEGIN

Cond_Queue::Cond_Queue(size_t max_size) : 
    _size(0), _head(0), _tail(0), _max_size(max_size)
{
    if (max_size <= MAX_AUTO_ELEMENTS)
    _data = _auto_data;
    else
    _data = new void*[max_size];
}

Cond_Queue::~Cond_Queue()
{
    if (_data != _auto_data)
        delete [] _data;
}

void Cond_Queue::enqueue(void* entry)
{
    Auto_Mutex auto_mutex(_lock);

    while (_size == _max_size)
        _not_full.wait(_lock);

    _data[_tail++] = entry;

    if (_tail == _max_size)
        _tail = 0;

    _size++;

    _not_empty.signal();
}

void* Cond_Queue::dequeue()
{
    Auto_Mutex auto_mutex(_lock);

    while (_size == 0)
        _not_empty.wait(_lock);

    void* entry = _data[_head++];

    if (_head == _max_size)
        _head = 0;

    _size--;

    _not_full.signal();

    return entry;
}

CIMPLE_NAMESPACE_END
