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
}

void __pack_array(
    Buffer& out, 
    const Array_Base& x,
    Pack_Elem pack_elem)
{
    // ATTN: make this faster by not aligning each element (only the first
    // element should be aligned.

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
    pos = align(pos, sizeof(uint16));
    uint16* ptr = (uint16*)(in.data() + pos);

#ifdef CIMPLE_CONVERSE_ENDIAN
    x = swap_uint16(*ptr);
#else
    x = *ptr;
#endif

    pos += sizeof(uint16);
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
