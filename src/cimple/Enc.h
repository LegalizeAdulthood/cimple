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

#ifndef _cimple_Enc_h
#define _cimple_Enc_h

#include "config.h"
#include "Type.h"
#include "Buffer.h"
#include "Array.h"

// #define CIMPLE_ENABLE_TAGGING

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// align()
//
//==============================================================================

inline size_t align(size_t x, size_t n)
{
    ptrdiff_t m = n - 1;
    return (x + m) & ~m;
}

//==============================================================================
//
// align_buffer()
//
//==============================================================================

inline void* align_buffer(Buffer& out, size_t elem_size)
{
    size_t pos = align(out.size(), elem_size);
    out.resize(pos + elem_size);
    return out.data() + pos;
}

//==============================================================================
//
// Internal encoding functions
//
//==============================================================================

inline void swap(uint8& x, uint8& y)
{
    uint8 t = x;
    x = y;
    y = t;
}

inline uint16 swap_uint16(uint16 x)
{
    return (uint16)(
	(((uint16)(x) & 0x00ffu) << 8) |
	(((uint16)(x) & 0xff00u) >> 8));
}

inline uint32 swap_uint32(uint32 x)
{
    return (uint32)(
	(((uint32)(x) & 0x000000fful) << 24) |
	(((uint32)(x) & 0x0000ff00ul) <<  8) |
	(((uint32)(x) & 0x00ff0000ul) >>  8) |
	(((uint32)(x) & 0xff000000ul) >> 24));
}

CIMPLE_LIBCIMPLE_LINKAGE
uint64 swap_uint64(uint64 x);

//==============================================================================
//
// Internal encoding functions
//
//==============================================================================

typedef void (*Pack_Elem)(
    Buffer& out, 
    const void* x);

CIMPLE_LIBCIMPLE_LINKAGE
void __pack_array(
    Buffer& out, 
    const Array_Base& x,
    Pack_Elem pack_elem);

typedef void (*Unpack_Elem)(
    const Buffer& out, 
    size_t& pos, 
    void* x);

CIMPLE_LIBCIMPLE_LINKAGE
void __unpack_array(
    const Buffer& in,
    size_t& pos,
    Array_Base& x,
    Unpack_Elem unpack_elem);

//==============================================================================
//
// pack_<type>
//
//==============================================================================
  
inline void pack_boolean(Buffer& out, const boolean& x)
{
    out.append(x ? 1 : 0);
}

inline void pack_uint8(Buffer& out, const uint8& x)
{
    out.append(char(x));
}

inline void pack_uint16(Buffer& out, const uint16& x)
{
    uint16* ptr = (uint16*)align_buffer(out, sizeof(uint16));

#ifdef CIMPLE_CONVERSE_ENDIAN
    *ptr = swap_uint16(x);
#else
    *ptr = x;
#endif
}

CIMPLE_LIBCIMPLE_LINKAGE
void pack_char16(Buffer& out, const char16& x);

inline void pack_char16(Buffer& out, const char16& x)
{
    pack_uint16(out, x.code);
}

inline void pack_uint32(Buffer& out, const uint32& x)
{
    uint32* ptr = (uint32*)align_buffer(out, sizeof(uint32));

#ifdef CIMPLE_CONVERSE_ENDIAN
    *ptr = swap_uint32(x);
#else
    *ptr = x;
#endif
}

CIMPLE_LIBCIMPLE_LINKAGE
void pack_uint64(Buffer& out, const uint64& x);

inline void pack_size_t(Buffer& out, const size_t& x)
{
    pack_uint64(out, uint64(x));
}

CIMPLE_LIBCIMPLE_LINKAGE
void pack_real32(Buffer& out, const real32& x);

CIMPLE_LIBCIMPLE_LINKAGE
void pack_real64(Buffer& out, const real64& x);

CIMPLE_LIBCIMPLE_LINKAGE
void pack_string(Buffer& out, const String& x);

CIMPLE_LIBCIMPLE_LINKAGE
void pack_c_str(Buffer& out, const char* str);

CIMPLE_LIBCIMPLE_LINKAGE
void pack_datetime(Buffer& out, const Datetime& x);

inline void pack_boolean_array(Buffer& out, const Array<boolean>& x)
{
    __pack_array(out, x, Pack_Elem(pack_boolean));
}

inline void pack_uint8_array(Buffer& out, const Array<uint8>& x)
{
    __pack_array(out, x, Pack_Elem(pack_uint8));
}

inline void pack_uint16_array(Buffer& out, const Array<uint16>& x)
{
    __pack_array(out, x, Pack_Elem(pack_uint16));
}

inline void pack_char16_array(Buffer& out, const Array<char16>& x)
{
    __pack_array(out, x, Pack_Elem(pack_char16));
}

inline void pack_uint32_array(Buffer& out, const Array<uint32>& x)
{
    __pack_array(out, x, Pack_Elem(pack_uint32));
}

inline void pack_uint64_array(Buffer& out, const Array<uint64>& x)
{
    __pack_array(out, x, Pack_Elem(pack_uint64));
}

inline void pack_real32_array(Buffer& out, const Array<real32>& x)
{
    __pack_array(out, x, Pack_Elem(pack_real32));
}

inline void pack_real64_array(Buffer& out, const Array<real64>& x)
{
    __pack_array(out, x, Pack_Elem(pack_real64));
}

inline void pack_string_array(Buffer& out, const Array<String>& x)
{
    __pack_array(out, x, Pack_Elem(pack_string));
}

inline void pack_datetime_array(Buffer& out, const Array<Datetime>& x)
{
    __pack_array(out, x, Pack_Elem(pack_datetime));
}

//==============================================================================
//
// unpack_<type>
//
//==============================================================================

inline void unpack_boolean(const Buffer& in, size_t& pos, boolean& x)
{
    x = in[pos++];
}

inline void unpack_uint8(const Buffer& in, size_t& pos, uint8& x)
{
    x = in[pos++];
}

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_uint16(const Buffer& in, size_t& pos, uint16& x);

inline void unpack_char16(const Buffer& in, size_t& pos, char16& x)
{
    unpack_uint16(in, pos, x.code);
}

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_uint32(const Buffer& in, size_t& pos, uint32& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_uint64(const Buffer& in, size_t& pos, uint64& x);

inline void unpack_size_t(const Buffer& in, size_t& pos, size_t& x)
{
    uint64 tmp;
    unpack_uint64(in, pos, tmp);
    x = size_t(tmp);
}

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_real32(const Buffer& in, size_t& pos, real32& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_real64(const Buffer& in, size_t& pos, real64& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_string(const Buffer& in, size_t& pos, String& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_c_str(
    const Buffer& in, 
    size_t& pos, 
    const char*& str, 
    size_t& size);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_datetime(const Buffer& in, size_t& pos, Datetime& x);

inline void unpack_boolean_array(
    const Buffer& in, size_t& pos, Array<boolean>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_boolean);
}

inline void unpack_uint8_array(const Buffer& in, size_t& pos, Array<uint8>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_uint8);
}

inline void unpack_uint16_array(const Buffer& in, size_t& pos, Array<uint16>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_uint16);
}

inline void unpack_char16_array(const Buffer& in, size_t& pos, Array<char16>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_uint16);
}

inline void unpack_uint32_array(const Buffer& in, size_t& pos, Array<uint32>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_uint32);
}

inline void unpack_uint64_array(const Buffer& in, size_t& pos, Array<uint64>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_uint64);
}

inline void unpack_real32_array(const Buffer& in, size_t& pos, Array<real32>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_real32);
}

inline void unpack_real64_array(const Buffer& in, size_t& pos, Array<real64>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_real64);
}

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_string_array(const Buffer& in, size_t& pos, Array<String>& x);

inline void unpack_datetime_array(
    const Buffer& in, size_t& pos, Array<Datetime>& x)
{
    __unpack_array(in, pos, x, (Unpack_Elem)unpack_datetime);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Enc_h */
