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

#include "Enc.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// align
//
//==============================================================================

static inline size_t _align(size_t x, size_t n)
{
    ptrdiff_t m = n - 1;
    return (x + m) & ~m;
}

//==============================================================================
//
// swap functions.
//
//==============================================================================

static inline uint16 _swap_uint16(uint16 x)
{
    return (uint16)(
	(((uint16)(x) & 0x00ffu) << 8) |
	(((uint16)(x) & 0xff00u) >> 8));
}

static inline uint32 _swap_uint32(uint32 x)
{
    return (uint32)(
	(((uint32)(x) & 0x000000fful) << 24) |
	(((uint32)(x) & 0x0000ff00ul) <<  8) |
	(((uint32)(x) & 0x00ff0000ul) >>  8) |
	(((uint32)(x) & 0xff000000ul) >> 24));
}

static inline void _swap(uint8& x, uint8& y)
{
    uint8 t = x;
    x = y;
    y = t;
}

static uint64 _swap_uint64(uint64 x)
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
    _swap(u.data[0], u.data[7]);
    _swap(u.data[1], u.data[6]);
    _swap(u.data[2], u.data[5]);
    _swap(u.data[3], u.data[4]);

    return u.x;

#endif /* _GNU_SOURCE */
}

//==============================================================================
//
// align_buffer()
//
//==============================================================================

static void* _align_buffer(Buffer& out, size_t elem_size)
{
    size_t pos = _align(out.size(), elem_size);
    out.resize(pos + elem_size);
    return out.data() + pos;
}

//==============================================================================
//
// pack:
//
//==============================================================================

void pack_uint16(Buffer& out, const uint16& x)
{
    uint16* ptr = (uint16*)_align_buffer(out, sizeof(uint16));

#ifdef CIMPLE_LITTLE_ENDIAN
    *ptr = _swap_uint16(x);
#else
    *ptr = x;
#endif
}

void pack_uint32(Buffer& out, const uint32& x)
{
    uint32* ptr = (uint32*)_align_buffer(out, sizeof(uint32));

#ifdef CIMPLE_LITTLE_ENDIAN
    *ptr = _swap_uint32(x);
#else
    *ptr = x;
#endif
}

void pack_uint64(Buffer& out, const uint64& x)
{
    uint64* ptr = (uint64*)_align_buffer(out, sizeof(uint64));

#ifdef CIMPLE_LITTLE_ENDIAN
    *ptr = _swap_uint64(x);
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
    out.append(x.c_str(), x.size());
}

// ATTN: consider null-terminated string encodings.

void pack_c_str(Buffer& out, const char* str)
{
    size_t size = strlen(str);
    pack_uint32(out, size);
    out.append(str, size);
}

void pack_datetime(Buffer& out, const Datetime& x)
{
    pack_uint64(out, x.usec());
    pack_uint32(out, x.offset());
}

void __pack_array(
    Buffer& out, 
    const Array_Base& x,
    Pack_Elem pack_elem)
{
    pack_uint32(out, x.size());

    for (size_t i = 0; i < x.size(); i++)
	pack_elem(out, x.get_raw(i));
}

//==============================================================================
//
// unpack
//
//==============================================================================

void unpack_uint16(const Buffer& in, size_t& pos, uint16& x)
{
    pos = _align(pos, sizeof(uint16));
    uint16* ptr = (uint16*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
    x = _swap_uint16(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint16);
}

void unpack_uint32(const Buffer& in, size_t& pos, uint32& x)
{
    pos = _align(pos, sizeof(uint32));
    uint32* ptr = (uint32*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
    x = _swap_uint32(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint32);
}

void unpack_uint64(const Buffer& in, size_t& pos, uint64& x)
{
    pos = _align(pos, sizeof(uint64));
    uint64* ptr = (uint64*)(in.data() + pos);

#ifdef CIMPLE_LITTLE_ENDIAN
    x = _swap_uint64(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint64);
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
    pos += size;
}

void unpack_c_str(const Buffer& in, size_t& pos, char*& str)
{
    uint32 size;
    unpack_uint32(in, pos, size);

    str = new char[size+1];
    memcpy(str, in.data() + pos, size);

    pos += size;
}

void unpack_datetime(const Buffer& in, size_t& pos, Datetime& x)
{
    uint64 usec;
    unpack_uint64(in, pos, usec);

    uint32 offset;
    unpack_uint32(in, pos, offset);

    x.set(usec, offset);
}

void __unpack_array(
    const Buffer& in,
    size_t& pos,
    Array_Base& x,
    Unpack_Elem unpack_elem)
{
    // Unpack array size.

    uint32 size = 0;
    unpack_uint32(in, pos, size);

    // Unpack the elements.

    while (size--)
    {
	// Note: this trick only works for the raw data types.
	union
	{
	    uint64 align1;
	    real64 align2;
	    char data[sizeof(Datetime)];
	}
	u;
	unpack_elem(in, pos, u.data);
	x.append_raw(u.data, 1);
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

CIMPLE_NAMESPACE_END
