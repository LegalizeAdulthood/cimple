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
    Lowest level of the encoding and decoding functions.  The functions in
    this file encode single cimple value types and their corresponding arrays.
    This module also includes the functions for swapping and alignment.
*/

#ifndef _cimple_Enc_h
#define _cimple_Enc_h

#include "config.h"
#include "Type.h"
#include "Buffer.h"
#include "Array.h"
#include "Array_Impl.h"
#include "char16.h"

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
inline sint16 swap_sint16(sint16 x)
{
    return (sint16)(
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

inline sint32 swap_sint32(sint32 x)
{
    return (sint32)(
    (((uint32)(x) & 0x000000fful) << 24) |
    (((uint32)(x) & 0x0000ff00ul) <<  8) |
    (((uint32)(x) & 0x00ff0000ul) >>  8) |
    (((uint32)(x) & 0xff000000ul) >> 24));}

CIMPLE_CIMPLE_LINKAGE
uint64 swap_uint64(uint64 x);

CIMPLE_CIMPLE_LINKAGE
sint64 swap_sint64(sint64 x);
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

inline void pack_sint8(Buffer& out, const sint8& x)
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

inline void pack_sint16(Buffer& out, const sint16& x)
{
    sint16* ptr = (sint16*)align_buffer(out, sizeof(sint16));

#ifdef CIMPLE_CONVERSE_ENDIAN
    *ptr = swap_sint16(x);
#else
    *ptr = x;
#endif
}

CIMPLE_CIMPLE_LINKAGE
void pack_char16(Buffer& out, const char16& x);

inline void pack_char16(Buffer& out, const char16& x)
{
    pack_uint16(out, x.code());
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

inline void pack_sint32(Buffer& out, const sint32& x)
{
    sint32* ptr = (sint32*)align_buffer(out, sizeof(sint32));

#ifdef CIMPLE_CONVERSE_ENDIAN
    *ptr = swap_sint32(x);
#else
    *ptr = x;
#endif
}

CIMPLE_CIMPLE_LINKAGE
void pack_uint64(Buffer& out, const uint64& x);

CIMPLE_CIMPLE_LINKAGE
void pack_sint64(Buffer& out, const sint64& x);

inline void pack_size_t(Buffer& out, const size_t& x)
{
    pack_uint64(out, uint64(x));
}

CIMPLE_CIMPLE_LINKAGE
void pack_real32(Buffer& out, const real32& x);

CIMPLE_CIMPLE_LINKAGE
void pack_real64(Buffer& out, const real64& x);

CIMPLE_CIMPLE_LINKAGE
void pack_string(Buffer& out, const String& x);

CIMPLE_CIMPLE_LINKAGE
void pack_c_str(Buffer& out, const char* str);

CIMPLE_CIMPLE_LINKAGE
void pack_datetime(Buffer& out, const Datetime& x);

CIMPLE_CIMPLE_LINKAGE
void pack_boolean_array(Buffer& out, const Array<boolean>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_uint8_array(Buffer& out, const Array<uint8>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_sint8_array(Buffer& out, const Array<sint8>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_uint16_array(Buffer& out, const Array<uint16>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_sint16_array(Buffer& out, const Array<sint16>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_char16_array(Buffer& out, const Array<char16>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_uint32_array(Buffer& out, const Array<uint32>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_sint32_array(Buffer& out, const Array<sint32>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_uint64_array(Buffer& out, const Array<uint64>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_sint64_array(Buffer& out, const Array<sint64>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_real32_array(Buffer& out, const Array<real32>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_real64_array(Buffer& out, const Array<real64>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_string_array(Buffer& out, const Array<String>& x);

CIMPLE_CIMPLE_LINKAGE
void pack_datetime_array(Buffer& out, const Array<Datetime>& x);

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

inline void unpack_sint8(const Buffer& in, size_t& pos, sint8& x)
{
    x = in[pos++];
}

CIMPLE_CIMPLE_LINKAGE
void unpack_uint16(const Buffer& in, size_t& pos, uint16& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint16(const Buffer& in, size_t& pos, sint16& x);

inline void unpack_char16(const Buffer& in, size_t& pos, char16& x)
{
    uint16 y;
    unpack_uint16(in, pos, y);
    x = (char16&)y;
}

CIMPLE_CIMPLE_LINKAGE
void unpack_uint32(const Buffer& in, size_t& pos, uint32& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint32(const Buffer& in, size_t& pos, sint32& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_uint64(const Buffer& in, size_t& pos, uint64& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint64(const Buffer& in, size_t& pos, sint64& x);

inline void unpack_size_t(const Buffer& in, size_t& pos, size_t& x)
{
    uint64 tmp;
    unpack_uint64(in, pos, tmp);
    x = size_t(tmp);
}

CIMPLE_CIMPLE_LINKAGE
void unpack_real32(const Buffer& in, size_t& pos, real32& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_real64(const Buffer& in, size_t& pos, real64& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_string(const Buffer& in, size_t& pos, String& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_c_str(
    const Buffer& in, 
    size_t& pos, 
    const char*& str, 
    size_t& size);

CIMPLE_CIMPLE_LINKAGE
void unpack_datetime(const Buffer& in, size_t& pos, Datetime& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_boolean_array(const Buffer& in, size_t& pos, Array<boolean>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_uint8_array(const Buffer& in, size_t& pos, Array<uint8>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint8_array(const Buffer& in, size_t& pos, Array<sint8>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_uint16_array(const Buffer& in, size_t& pos, Array<uint16>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint16_array(const Buffer& in, size_t& pos, Array<sint16>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_char16_array(const Buffer& in, size_t& pos, Array<char16>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_uint32_array(const Buffer& in, size_t& pos, Array<uint32>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint32_array(const Buffer& in, size_t& pos, Array<sint32>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_uint64_array(const Buffer& in, size_t& pos, Array<uint64>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_sint64_array(const Buffer& in, size_t& pos, Array<sint64>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_real32_array(const Buffer& in, size_t& pos, Array<real32>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_real64_array(const Buffer& in, size_t& pos, Array<real64>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_string_array(const Buffer& in, size_t& pos, Array<String>& x);

CIMPLE_CIMPLE_LINKAGE
void unpack_datetime_array(const Buffer& in, size_t& pos, Array<Datetime>& x);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Enc_h */
