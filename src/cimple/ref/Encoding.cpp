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

#include "Encoding.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// swap_bytes
//
//==============================================================================

uint64 swap_bytes<uint64>::func(uint64 x)
{
#ifdef _GNU_SOURCE

    return
         (((x) & 0xff00000000000000ull) >> 56) | 
         (((x) & 0x00ff000000000000ull) >> 40) | 
         (((x) & 0x0000ff0000000000ull) >> 24) |
         (((x) & 0x000000ff00000000ull) >>  8) |
         (((x) & 0x00000000ff000000ull) <<  8) |
         (((x) & 0x0000000000ff0000ull) << 24) |
         (((x) & 0x000000000000ff00ull) << 40) |
         (((x) & 0x00000000000000ffull) << 56);

#else /* _GNU_SOURCE */

    union
    {
        uint64 x;
        uint8 data[8];
    }
    u;

    u.x = x;
    swap(u.data[0], u.data[7]);
    swap(u.data[1], u.data[6]);
    swap(u.data[2], u.data[5]);
    swap(u.data[3], u.data[4]);

    return u.x;

#endif /* _GNU_SOURCE */
}

//==============================================================================
//
// align_buffer()
//
//==============================================================================

size_t align_buffer(Buffer& out, size_t elem_size)
{
    size_t pos = align(out.size(), elem_size);
    out.resize(pos + elem_size);
    return pos;
}

size_t align_buffer(Buffer& out, size_t elem_size, size_t array_size)
{
    size_t pos = align(out.size(), elem_size);
    out.resize(pos + elem_size * array_size);
    return pos;
}

//==============================================================================
//
// pack:
//
//==============================================================================

static void _pack_array(
    Buffer& out, 
    const void* data_, 
    size_t size,
    size_t elem_size, 
    void (*pack_elem)(Buffer& out, const void* elem))
{
    const char* data = (const char*)data_;

    while (size--)
    {
        pack_elem(out, data);
        data += elem_size;
    }
}

template<class T>
struct pack_elem
{
    static void func(Buffer& out, const void* elem)
    {
        pack<T>(out, *((T*)elem));
    }
};

pack<boolean>::pack(Buffer& out, const boolean* data, size_t size)
{
    _pack_array(out, data, size, 1, pack_elem<boolean>::func);
}

pack<uint16>::pack(Buffer& out, const uint16* data, size_t size)
{
    _pack_array(out, data, size, sizeof(uint16), pack_elem<uint16>::func);
}

pack<uint32>::pack(Buffer& out, const uint32* data, size_t size)
{
    _pack_array(out, data, size, sizeof(uint32), pack_elem<uint32>::func);
}

pack<uint64>::pack(Buffer& out, const uint64* data, size_t size)
{
    _pack_array(out, data, size, sizeof(uint64), pack_elem<uint64>::func);
}

pack<String>::pack(Buffer& out, const String* data, size_t size)
{
    _pack_array(out, data, size, sizeof(String), pack_elem<String>::func);
}

pack<Datetime>::pack(Buffer& out, const Datetime* data, size_t size)
{
    _pack_array(out, data, size, sizeof(Datetime), pack_elem<Datetime>::func);
}

//==============================================================================
//
// unpack:
//
//==============================================================================

unpack<uint16>::unpack(const Buffer& in, size_t& pos, uint16& x)
{
    pos = align(pos, sizeof(uint16));
    x = *((const uint16*)(in.data() + pos));

#ifdef CIMPLE_LITTLE_ENDIAN
    x = swap_bytes<uint16>::func(x);
#endif

    pos += sizeof(uint16);
}

unpack<uint32>::unpack(const Buffer& in, size_t& pos, uint32& x)
{
    pos = align(pos, sizeof(uint32));
    x = *((const uint32*)(in.data() + pos));

#ifdef CIMPLE_LITTLE_ENDIAN
    x = swap_bytes<uint32>::func(x);
#endif

    pos += sizeof(uint32);
}

unpack<uint64>::unpack(const Buffer& in, size_t& pos, uint64& x)
{
    pos = align(pos, sizeof(uint64));
    x = *((const uint64*)(in.data() + pos));

#ifdef CIMPLE_LITTLE_ENDIAN
    x = swap_bytes<uint64>::func(x);
#endif

    pos += sizeof(uint64);
}

unpack<String>::unpack(const Buffer& in, size_t& pos, String& x)
{
    uint32 size;
    unpack<uint32>(in, pos, size);

    x.assign(in.data() + pos, size);
    pos += size;
}

unpack<Datetime>::unpack(const Buffer& in, size_t& pos, Datetime& x)
{
    uint64 datetime_usec;
    unpack<uint64>(in, pos, datetime_usec);

    uint32 datetime_pos;
    unpack<uint32>(in, pos, datetime_pos);

    x.set(datetime_usec, datetime_pos);
}

#if 0

unpack<boolean>::unpack(
    const Buffer& in, size_t& pos, boolean* data, size_t size)
{
    const uint8* ptr = (const uint8*)(in.data() + pos);

    for (size_t i = 0; i < size; i++)
        data[i] = ptr[i] ? true : false;

    pos += size;
}

unpack<uint8>::unpack(
    const Buffer& in, size_t& pos, uint8* data, size_t size)
{
    memcpy(data, in.data() + pos, size);
    pos += size;
}

unpack<uint16>::unpack(
    const Buffer& in, size_t& pos, uint16* data, size_t size)
{
    pos = align(pos, sizeof(uint16));
    const uint16* ptr = (const uint16*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
    for (size_t i = 0; i < size; i++)
        data[i] = swap_bytes<uint64>::func(ptr[i]);

    pos += size * sizeof(uint16);
#else
    size_t n = size * sizeof(uint16);
    memcpy(data, ptr, n);
    pos += n;
#endif
}

unpack<uint32>::unpack(
    const Buffer& in, size_t& pos, uint32* data, size_t size)
{
    pos = align(pos, sizeof(uint32));
    const uint32* ptr = (const uint32*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
    for (size_t i = 0; i < size; i++)
        data[i] = swap_bytes<uint64>::func(ptr[i]);

    pos += size * sizeof(uint32);
#else
    size_t n = size * sizeof(uint32);
    memcpy(data, ptr, n);
    pos += n;
#endif
}

unpack<uint64>::unpack(
    const Buffer& in, size_t& pos, uint64* data, size_t size)
{
    pos = align(pos, sizeof(uint64));
    const uint64* ptr = (const uint64*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
    for (size_t i = 0; i < size; i++)
        data[i] = swap_bytes<uint64>::func(ptr[i]);

    pos += size * sizeof(uint64);
#else
    size_t n = size * sizeof(uint64);
    memcpy(data, ptr, n);
    pos += n;
#endif
}

unpack<String>::unpack(
    const Buffer& in, size_t& pos, String* data, size_t size)
{
    while (size--)
        unpack<String>(in, pos, *data++);
}

unpack<Datetime>::unpack(
    const Buffer& in, size_t& pos, Datetime* data, size_t size)
{
    while (size--)
        unpack<Datetime>(in, pos, *data++);
}

#endif

template<class T>
struct unpack_elem
{
    static void func(const Buffer& in, size_t& pos, void* elem)
    {
        unpack<T>(in, pos, *((T*)elem));
    }
};

struct Array_Friend
{
    static void unpack_raw_array(
        const Buffer& in, 
        size_t& pos, 
        void (*unpack_elem)(const Buffer& in, size_t& pos, void* elem),
        Array_Base& x)
    {
        // Clear the array.

        x._remove(0, x.size());

        // Unpack the size.

        uint32 size;
        unpack<uint32>(in, pos, size);

        // Unpack the elements.

        while (size--)
        {
            union
            {
                double align1;
                uint64 align2;
                char data[32];
            }
            u;
            unpack_elem(in, pos, u.data);
            x._append(u.data, 1);
        }
    }
};

unpack<boolean>::unpack(const Buffer& in, size_t& pos, Array<boolean>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<boolean>::func, x);
}

unpack<uint8>::unpack(const Buffer& in, size_t& pos, Array<uint8>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<uint8>::func, x);
}

template<class T>
struct _unpack_helper
{
    _unpack_helper(const Buffer& in, size_t& pos, Array<T>& x)
    {
        x.clear();

        // Unpack array size.

        uint32 size;
        unpack<uint32>(in, pos, size);

        // Unpack data.

        pos = align(pos, sizeof(T));
        const T* data = (const T*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
        for (size_t i = 0; i < size; i++)
            x.append(swap_bytes<T>::func(data[i]));
#else
        x.assign(data, size);
#endif
        pos += size * sizeof(T);
    }
};

unpack<uint16>::unpack(const Buffer& in, size_t& pos, Array<uint16>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<uint16>::func, x);
}

unpack<uint32>::unpack(const Buffer& in, size_t& pos, Array<uint32>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<uint32>::func, x);
}

unpack<uint64>::unpack(const Buffer& in, size_t& pos, Array<uint64>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<uint64>::func, x);
}

unpack<real32>::unpack(const Buffer& in, size_t& pos, Array<real32>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<real32>::func, x);
}

unpack<real64>::unpack(const Buffer& in, size_t& pos, Array<real64>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<real64>::func, x);
}

unpack<String>::unpack(const Buffer& in, size_t& pos, Array<String>& x)
{
    x.clear();

    uint32 size;
    unpack<uint32>(in, pos, size);

    while (size--)
    {
        String tmp;
        unpack<String>(in, pos, tmp);
        x.append(tmp);
    }
}

unpack<Datetime>::unpack(
    const Buffer& in, size_t& pos, Array<Datetime>& x)
{
    Array_Friend::unpack_raw_array(in, pos, unpack_elem<Datetime>::func, x);
}

CIMPLE_NAMESPACE_END
