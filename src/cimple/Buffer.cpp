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

#include "Buffer.h"
#include <ctype.h>
#include <cstdarg>

#define MIN_CAPACITY 4096

CIMPLE_NAMESPACE_BEGIN

// Return the next power of 2 for the input x or if x is less that
// the defined minimum capacity, return minimum capacity.
static size_t _round_up_pow_2(size_t x)
{
    if (x < MIN_CAPACITY)
        return MIN_CAPACITY;

    x--;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
#if __WORDSIZE == 64
    x |= (x >> 32);
#endif
    x++;

    return x;
}

Buffer::Buffer() : _data(0), _size(0), _cap(0) 
{ 
}

Buffer::Buffer(const Buffer& x)
{
    _size = x._size;
    _cap = x._size;
    _data = (char*)malloc(_cap + 1);
    memcpy(_data, x._data, _size);
}

Buffer::~Buffer() 
{ 
    free(_data); 
}

Buffer& Buffer::operator=(const Buffer& x)
{
    if (&x != this)
    {
        free(_data);
        _size = x._size;
        _cap = x._size;
        _data = (char*)malloc(_cap + 1);
        memcpy(_data, x._data, _size);
    }

    return *this;
}

// If requested capacity > current capacity realloc space for the
// buffer.  realloc covers issues of freeing old allocated memory and
// moving existing data in the buffer. Allocates an extra byte to allow
// for addition of \0 to be inserted by the data() method.
// 
void Buffer::reserve(size_t capacity)
{
    if (capacity > _cap)
    {
        if (capacity < MIN_CAPACITY)
            capacity = MIN_CAPACITY;

        _data = (char*)realloc(_data, capacity + 1);
        _cap = capacity;
    }
}

void Buffer::remove(size_t i, size_t size)
{
    CIMPLE_ASSERT(i + size <= _size);

    size_t rem = _size - (i + size);

    if (rem)
        memmove(_data + i, _data + i + size, rem);

    _size -= size;
}

// set capacity to MIN_CAPACITY if zero else double the current
// capacity.
void Buffer::_append_aux()
{
    reserve(_cap ? _cap * 2 : MIN_CAPACITY);
}

// Sets capacity to next power of 2 of the input capacity parameter.
// Used internally to expand the buffer capacity for all append 
// functions.
void Buffer::_reserve_aux(size_t capacity)
{
    reserve(_round_up_pow_2(capacity));
}

void Buffer::insert(size_t i, const char* data, size_t size)
{
    CIMPLE_ASSERT(i <= _size);

    size_t new_size = _size + size;     
    size_t rem = _size - i;

    if (new_size > _cap)
    {
        // allocate new buffer and save in temp space.
        size_t new_cap = _round_up_pow_2(new_size);
        char* new_data = (char*)malloc(new_cap + 1);

        // Copy 1) everything below i from existing data
        //      2) the insert from data
        //      3) the remaining _data starting at i from data
        memcpy(new_data, _data, i);
        memcpy(new_data + i, data, size);
        memcpy(new_data + i + size, _data + i, rem);

        // free the previous allocation
        free(_data);

        _data = new_data;
        _size = new_size;
        _cap = new_cap;
    }
    else
    {
        if (rem)
            memmove(_data + i + size, _data + i, rem);

        memcpy(_data + i, data, size);
        _size += size;
    }
}

// Formatted input to a buffer
size_t Buffer::format(const char* format, ...)
{
    size_t size = 128;
    va_list ap;

    // loop to insure the reserve is greater than size of 
    // result generated from the format string and input parameters
    // If the vsnprintf return indicates that the capacity is too small
    // buffer capacity is increased and another conversion attempt executed.
    for (;;)
    {
        if (_size + size > _cap)
        {
            _reserve_aux(_size + size);
        }
        char* str = _data + _size;

        va_start(ap, format);
        int n = vsnprintf(str, size, format, ap);
        va_end(ap);

        if (n > -1 && n < int(size))
        {
            _size += n;
            return size_t(n);
        }

        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }

    // Unreachable:
    return 0;
}

size_t Buffer::vformat(const char* format, va_list ap)
{
    size_t size = 128;

    // Repeat the reserve, format until we have reserved enough
    // space for the complete formatting operation.
    for (;;)
    {
        //reserve(_size + size);
        if (_size + size > _cap)
        {
            _reserve_aux(_size + size);
        }
        char* str = _data + _size;

        va_list tmp_ap;

        // No va_copy() on Windows at least the known versions
        // C99 spec requires that va_copy be a macro so the #ifdef
        // va_copy covers future compatible existence.
#ifdef CIMPLE_WINDOWS
#ifdef va_copy
        va_copy(tmp_ap, ap);
#else
        memcpy(&tmp_ap, &ap, sizeof(ap));
#endif
#else
        va_copy(tmp_ap, ap);
#endif

        int n = vsnprintf(str, size, format, tmp_ap);

        if (n > -1 && n < int(size))
        {
            _size += n;
            return size_t(n);
        }

        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }

    // Unreachable:
    return 0;
}

void Buffer::append_uint16(uint16 x)
{
    char buffer[5];
    char* p = &buffer[5];

    do
    {
        *--p = '0' + (x % 10);
    }
    while ((x /= 10) != 0);

    append(p, &buffer[5] - p);
}

void Buffer::append_uint32(uint32 x)
{
    char buffer[10];
    char* p = &buffer[10];

    do
    {
        *--p = '0' + (x % 10);
    }
    while ((x /= 10) != 0);

    append(p, &buffer[10] - p);
}

void Buffer::append_uint64(uint64 x)
{
    char buffer[20];
    char* p = &buffer[20];

    do
    {
        *--p = '0' + (x % 10);
    }
    while ((x /= 10) != 0);

    append(p, &buffer[20] - p);
}

// Display the contents of the buffer in side-side hex and ascii
// of the complete contents of the buffer.
// NOTE: This is a diagnostic only.
//
#ifdef ENABLE_BUFFER_DIAG
void Buffer::dump()
{
    char sp_buffer[100];
    long indent = 1;

    struct
    {
        char *data;
        unsigned long size;
    } buf;

    unsigned char *p_addr = (unsigned char *)_data;

    buf.data   = (char *)p_addr;
    buf.size   = _size;

    while (buf.size > 0)
    {
        long rel_pos;
        long out_len, index, index2, out_len2;
        unsigned char *p_tmp, uc_tmp;
        p_tmp    = (unsigned char *)buf.data;
        out_len  = (int)buf.size;

        if (out_len > 16)
          out_len = 16;
        
        // create a 64-character formatted output line:
        sprintf(sp_buffer, " >                            "
                     "                      "
                     "    %08lX", (unsigned long int)(p_tmp - p_addr));
        out_len2 = out_len;
        
        for(index = 1 + indent, index2 = 53 - 15 + indent, rel_pos = 0;
            out_len2;
            out_len2--, index += 2, index2++)
        {
            uc_tmp = *p_tmp++;
            
            sprintf(sp_buffer + index, "%02X ", (unsigned short)uc_tmp);
            if(!isprint(uc_tmp))  uc_tmp = '.'; // nonprintable char
            sp_buffer[index2] = uc_tmp;
            
            if (!(++rel_pos & 3))     // extra blank after 4 bytes
            {
                index++; 
                sp_buffer[index+2] = ' ';
            }
        }
        
        if (!(rel_pos & 3)) index--;
        
        sp_buffer[index  ]   = '<';
        sp_buffer[index+1]   = ' ';
        
        printf("%s\n", sp_buffer);
        
        buf.data   += out_len;
        buf.size   -= out_len;
    }
}
#endif


CIMPLE_NAMESPACE_END
