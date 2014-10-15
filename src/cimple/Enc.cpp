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

/*
    Seralization value packing and unpacking functions.
    These functions pack into a Buffer in binary form and
    correspondingly unpack from a Buffer.
    Functions are provided for all CIM Data types.
    The functions include the capability for Endian swap when required
    by the system.
*/

#include "Enc.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// swap functions.
//
//==============================================================================

uint64 swap_uint64(uint64 x)
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

sint64 swap_sint64(sint64 x)
{
#ifdef _GNU_SOURCE

    return (uint64)
     (((uint64)(x) & 0xff00000000000000ull) >> 56) | 
     (((uint64)(x) & 0x00ff000000000000ull) >> 40) | 
     (((uint64)(x) & 0x0000ff0000000000ull) >> 24) |
     (((uint64)(x) & 0x000000ff00000000ull) >>  8) |
     (((uint64)(x) & 0x00000000ff000000ull) <<  8) |
     (((uint64)(x) & 0x0000000000ff0000ull) << 24) |
     (((uint64)(x) & 0x000000000000ff00ull) << 40) |
     (((uint64)(x) & 0x00000000000000ffull) << 56);

#else /* _GNU_SOURCE */

    union
    {
        uint64 x;
        uint8 data[8];
    }
    u;

    u.x = (uint64)x;
    swap(u.data[0], u.data[7]);
    swap(u.data[1], u.data[6]);
    swap(u.data[2], u.data[5]);
    swap(u.data[3], u.data[4]);

    return (uint64)u.x;

#endif /* _GNU_SOURCE */
}

//==============================================================================
//
// pack:
//
//==============================================================================

void pack_uint64(Buffer& out, const uint64& x)
{
    uint64* ptr = (uint64*)align_buffer(out, sizeof(uint64));

#ifdef CIMPLE_CONVERSE_ENDIAN
    *ptr = swap_uint64(x);
#else
    *ptr = x;
#endif
}

void pack_sint64(Buffer& out, const sint64& x)
{
    sint64* ptr = (sint64*)align_buffer(out, sizeof(sint64));

#ifdef CIMPLE_CONVERSE_ENDIAN
    *ptr = swap_sint64(x);
#else
    *ptr = x;
#endif
}

void pack_real32(Buffer& out, const real32& x)
{
    uint32 tmp;
    memcpy(&tmp, &x, sizeof(x));
    pack_uint32(out, tmp);
}

void pack_real64(Buffer& out, const real64& x)
{
    uint64 tmp;
    memcpy(&tmp, &x, sizeof(x));
    pack_uint64(out, tmp);
}

void pack_string(Buffer& out, const String& x)
{
    pack_uint32(out, x.size());
    out.append(x.c_str(), x.size() + 1);
}

void pack_c_str(Buffer& out, const char* str)
{
    size_t size = strlen(str);
    pack_uint32(out, size);
    out.append(str, size + 1);
}

void pack_datetime(Buffer& out, const Datetime& x)
{
    pack_uint64(out, x.usec());
    pack_uint32(out, x.offset());
    pack_boolean(out, x.is_timestamp());
}

//==============================================================================
//
// unpack
//
//==============================================================================

void unpack_uint16(const Buffer& in, size_t& pos, uint16& x)
{
    pos = align(pos, sizeof(uint16));
    uint16* ptr = (uint16*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_uint16(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint16);
}

void unpack_sint16(const Buffer& in, size_t& pos, sint16& x)
{
    pos = align(pos, sizeof(sint16));
    sint16* ptr = (sint16*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_sint16(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(sint16);
}

void unpack_uint32(const Buffer& in, size_t& pos, uint32& x)
{
    pos = align(pos, sizeof(uint32));
    uint32* ptr = (uint32*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_uint32(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint32);
}

void unpack_sint32(const Buffer& in, size_t& pos, sint32& x)
{
    pos = align(pos, sizeof(sint32));
    sint32* ptr = (sint32*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_sint32(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(sint32);
}

void unpack_uint64(const Buffer& in, size_t& pos, uint64& x)
{
    pos = align(pos, sizeof(uint64));
    uint64* ptr = (uint64*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_uint64(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint64);
}

void unpack_sint64(const Buffer& in, size_t& pos, sint64& x)
{
    pos = align(pos, sizeof(sint64));
    sint64* ptr = (sint64*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_sint64(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(sint64);
}

void unpack_real32(const Buffer& in, size_t& pos, real32& x)
{
    uint32 tmp;
    unpack_uint32(in, pos, tmp);
    memcpy(&x, &tmp, sizeof(tmp));
}

void unpack_real64(const Buffer& in, size_t& pos, real64& x)
{
    uint64 tmp;
    unpack_uint64(in, pos, tmp);
    memcpy(&x, &tmp, sizeof(tmp));
}

void unpack_string(const Buffer& in, size_t& pos, String& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);
    x.assign(in.data() + pos, size);
    pos += size + 1;
}

void unpack_c_str(const Buffer& in, size_t& pos, const char*& str, size_t& size)
{
    uint32 n;
    unpack_uint32(in, pos, n);
    str = (const char*)(in.data() + pos);
    pos += n + 1;
    size = size_t(n);
}

void unpack_datetime(const Buffer& in, size_t& pos, Datetime& x)
{
    uint64 usec;
    unpack_uint64(in, pos, usec);

    uint32 offset;
    unpack_uint32(in, pos, offset);

    boolean is_timestamp;
    unpack_boolean(in, pos, is_timestamp);

    if (is_timestamp)
        x.set(usec, offset);
    else
        x.set(usec);
}

void pack_boolean_array(Buffer& out, const Array<boolean>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_boolean(out, x[i]);
}

void pack_uint8_array(Buffer& out, const Array<uint8>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_uint8(out, x[i]);
}

void pack_sint8_array(Buffer& out, const Array<sint8>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_sint8(out, x[i]);
}

void pack_uint16_array(Buffer& out, const Array<uint16>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_uint16(out, x[i]);
}

void pack_sint16_array(Buffer& out, const Array<sint16>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_sint16(out, x[i]);
}

void pack_uint32_array(Buffer& out, const Array<uint32>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_uint32(out, x[i]);
}

void pack_sint32_array(Buffer& out, const Array<sint32>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_sint32(out, x[i]);
}

void pack_uint64_array(Buffer& out, const Array<uint64>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_uint64(out, x[i]);
}

void pack_sint64_array(Buffer& out, const Array<sint64>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_sint64(out, x[i]);
}

void pack_real32_array(Buffer& out, const Array<real32>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_real32(out, x[i]);
}

void pack_real64_array(Buffer& out, const Array<real64>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_real64(out, x[i]);
}

void pack_char16_array(Buffer& out, const Array<char16>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_char16(out, x[i]);
}

void pack_string_array(Buffer& out, const Array<String>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_string(out, x[i]);
}

void pack_datetime_array(Buffer& out, const Array<Datetime>& x)
{
    pack_uint32(out, uint32(x.size()));

    for (size_t i = 0; i < x.size(); i++)
        pack_datetime(out, x[i]);
}

void unpack_boolean_array(const Buffer& in, size_t& pos, Array<boolean>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        boolean tmp;
        unpack_boolean(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_uint8_array(const Buffer& in, size_t& pos, Array<uint8>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        uint8 tmp;
        unpack_uint8(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_sint8_array(const Buffer& in, size_t& pos, Array<sint8>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        sint8 tmp;
        unpack_sint8(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_uint16_array(const Buffer& in, size_t& pos, Array<uint16>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        uint16 tmp;
        unpack_uint16(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_sint16_array(const Buffer& in, size_t& pos, Array<sint16>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        sint16 tmp;
        unpack_sint16(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_uint32_array(const Buffer& in, size_t& pos, Array<uint32>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        uint32 tmp;
        unpack_uint32(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_sint32_array(const Buffer& in, size_t& pos, Array<sint32>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        sint32 tmp;
        unpack_sint32(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_uint64_array(const Buffer& in, size_t& pos, Array<uint64>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        uint64 tmp;
        unpack_uint64(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_sint64_array(const Buffer& in, size_t& pos, Array<sint64>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        sint64 tmp;
        unpack_sint64(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_real32_array(const Buffer& in, size_t& pos, Array<real32>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        real32 tmp;
        unpack_real32(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_real64_array(const Buffer& in, size_t& pos, Array<real64>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        real64 tmp;
        unpack_real64(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_char16_array(const Buffer& in, size_t& pos, Array<char16>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        char16 tmp;
        unpack_char16(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_string_array(const Buffer& in, size_t& pos, Array<String>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        String tmp;
        unpack_string(in, pos, tmp);
        x.append(tmp);
    }
}

void unpack_datetime_array(const Buffer& in, size_t& pos, Array<Datetime>& x)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    while (size--)
    {
        Datetime tmp;
        unpack_datetime(in, pos, tmp);
        x.append(tmp);
    }
}

CIMPLE_NAMESPACE_END
