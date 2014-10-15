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

#include "MOF_Buffer.h"

inline MOF_uint32 _next_pow_2(MOF_uint32 x)
{
    MOF_uint32 r = 1;

    while (r < x)
        r <<= 1;

    return r;
}

inline MOF_uint32 _round_capacity(MOF_uint32 capacity)
{
    return capacity < 16 ? 16 : _next_pow_2(capacity);
}

void MOF_Buffer::reserve(size_t capacity)
{
    if (capacity > _capacity)
    {
        capacity = _round_capacity(capacity);
        _data = (char*)realloc(_data, capacity);
        _capacity = capacity;
    }
}

void MOF_Buffer::append(const char* data, size_t size)
{
    reserve(_size + size);
    memcpy(_data + _size, data, size);
    _size += size;
}

char* MOF_Buffer::steal_data() 
{
    char* data = _data;
    _data = 0;
    _size = 0;
    _capacity = 0;
    return data;
}

/*NOCHKSRC*/
