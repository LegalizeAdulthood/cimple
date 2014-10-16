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

#ifndef _cimple_Encoding_h
#define _cimple_Encoding_h

#include "config.h"
#include "Type.h"
#include "Buffer.h"
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// align
//
//==============================================================================

inline size_t align(size_t x, size_t n)
{
    ptrdiff_t m = n - 1;
    return (x + m) & ~m;
}

//==============================================================================
//
// align_buffer
//
//==============================================================================

size_t align_buffer(Buffer& out, size_t elem_size);

size_t align_buffer(Buffer& out, size_t elem_size, size_t array_size);

//==============================================================================
//
// swap
//
//==============================================================================

inline void swap(uint8& x, uint8& y)
{
    uint8 t = x;
    x = y;
    y = t;
}

//==============================================================================
//
// swap_bytes
//
//==============================================================================

template<class T>
struct swap_bytes
{
};

template<>
struct swap_bytes<uint16>
{
    static uint16 func(uint16 x)
    {
        return (uint16)(
            (((uint16)(x) & 0x00ffu) << 8) |
            (((uint16)(x) & 0xff00u) >> 8));
    }
};

template<>
struct swap_bytes<uint32>
{
    static uint32 func(uint32 x)
    {
        return (uint32)(
            (((uint32)(x) & 0x000000fful) << 24) |
            (((uint32)(x) & 0x0000ff00ul) <<  8) |
            (((uint32)(x) & 0x00ff0000ul) >>  8) |
            (((uint32)(x) & 0xff000000ul) >> 24));
    }
};

template<>
struct swap_bytes<uint64>
{
    static uint64 func(uint64 x);
};

//==============================================================================
//
// pack
//
//==============================================================================

template<class T>
struct pack
{
};

template<>
struct pack<boolean>
{
    pack(Buffer& out, const boolean& x);
    pack(Buffer& out, const boolean* data, size_t size);
    pack(Buffer& out, const Array<boolean>& x);
};

template<>
struct pack<uint8>
{
    pack(Buffer& out, const uint8& x);
    pack(Buffer& out, const uint8* data, size_t size);
    pack(Buffer& out, const Array<uint8>& x);
};

template<>
struct pack<uint16>
{
    pack(Buffer& out, const uint16& x);
    pack(Buffer& out, const uint16* data, size_t size);
    pack(Buffer& out, const Array<uint16>& x);
};

template<>
struct pack<uint32>
{
    pack(Buffer& out, const uint32& x);
    pack(Buffer& out, const uint32* data, size_t size);
    pack(Buffer& out, const Array<uint32>& x);
};

template<>
struct pack<uint64>
{
    pack(Buffer& out, const uint64& x);
    pack(Buffer& out, const uint64* data, size_t size);
    pack(Buffer& out, const Array<uint64>& x);
};

template<>
struct pack<real32>
{
    pack(Buffer& out, const real32& x);
    pack(Buffer& out, const real32* data, size_t size);
    pack(Buffer& out, const Array<real32>& x);
};

template<>
struct pack<real64>
{
    pack(Buffer& out, const real64& x);
    pack(Buffer& out, const real64* data, size_t size);
    pack(Buffer& out, const Array<real64>& x);
};

template<>
struct pack<String>
{
    pack(Buffer& out, const String& x);
    pack(Buffer& out, const String* data, size_t size);
    pack(Buffer& out, const Array<String>& x);
};

template<>
struct pack<Datetime>
{
    pack(Buffer& out, const Datetime& x);
    pack(Buffer& out, const Datetime* data, size_t size);
    pack(Buffer& out, const Array<Datetime>& x);
};

inline pack<boolean>::pack(Buffer& out, const boolean& x)
{
    pack<uint8>(out, x ? 1 : 0);
}

inline pack<uint8>::pack(Buffer& out, const uint8& x)
{
    out.append(char(x));
}

inline pack<uint16>::pack(Buffer& out, const uint16& x)
{
#ifdef CIMPLE_LITTLE_ENDIAN
    uint16 tmp = swap_bytes<uint16>::func(x);
#else
    uint16 tmp = x;
#endif
    size_t pos = align_buffer(out, sizeof(uint16));
    *((uint16*)(out.data() + pos)) = tmp;
}

inline pack<uint32>::pack(Buffer& out, const uint32& x)
{
#ifdef CIMPLE_LITTLE_ENDIAN
    uint32 tmp = swap_bytes<uint32>::func(x);
#else
    uint32 tmp = x;
#endif
    size_t pos = align_buffer(out, sizeof(uint32));
    *((uint32*)(out.data() + pos)) = tmp;
}

inline pack<uint64>::pack(Buffer& out, const uint64& x)
{
#ifdef CIMPLE_LITTLE_ENDIAN
    uint64 tmp = swap_bytes<uint64>::func(x);
#else
    uint64 tmp = x;
#endif
    size_t pos = align_buffer(out, sizeof(uint64));
    *((uint64*)(out.data() + pos)) = tmp;
}

inline pack<real32>::pack(Buffer& out, const real32& x)
{
    uint32 tmp;
    memcpy(&tmp, &x, sizeof(x));
    pack<uint32>(out, tmp);
}

inline pack<real64>::pack(Buffer& out, const real64& x)
{
    uint64 tmp;
    memcpy(&tmp, &x, sizeof(x));
    pack<uint64>(out, tmp);
    // ATTN: this fails: pack<uint64>(out, *((const uint64*)&x));
}

inline pack<String>::pack(Buffer& out, const String& x)
{
    pack<uint32>(out, x.size());
    out.append(x.c_str(), x.size());
}

inline pack<Datetime>::pack(Buffer& out, const Datetime& x)
{
    pack<uint64>(out, x.usec());
    pack<uint32>(out, x.offset());
}

inline pack<uint8>::pack(Buffer& out, const uint8* data, size_t size)
{
    out.append((char*)data, size);
}

inline pack<real32>::pack(Buffer& out, const real32* data, size_t size)
{
    pack<uint32>(out, (const uint32*)data, size);
}

inline pack<real64>::pack(Buffer& out, const real64* data, size_t size)
{
    pack<uint64>(out, (const uint64*)data, size);
}

inline pack<boolean>::pack(Buffer& out, const Array<boolean>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<boolean>(out, x.data(), x.size());
}

inline pack<uint8>::pack(Buffer& out, const Array<uint8>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<uint8>(out, x.data(), x.size());
}

inline pack<uint16>::pack(Buffer& out, const Array<uint16>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<uint16>(out, x.data(), x.size());
}

inline pack<uint32>::pack(Buffer& out, const Array<uint32>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<uint32>(out, x.data(), x.size());
}

inline pack<uint64>::pack(Buffer& out, const Array<uint64>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<uint64>(out, x.data(), x.size());
}

inline pack<real32>::pack(Buffer& out, const Array<real32>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<real32>(out, x.data(), x.size());
}

inline pack<real64>::pack(Buffer& out, const Array<real64>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<real64>(out, x.data(), x.size());
}

inline pack<String>::pack(Buffer& out, const Array<String>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<String>(out, x.data(), x.size());
}

inline pack<Datetime>::pack(Buffer& out, const Array<Datetime>& x)
{
    pack<uint32>(out, uint32(x.size()));
    pack<Datetime>(out, x.data(), x.size());
}

//==============================================================================
//
// unpack
//
//==============================================================================

template<class T>
struct unpack
{
};

template<>
struct unpack<boolean>
{
    unpack(const Buffer& in, size_t& pos, boolean& x);
    // unpack(const Buffer& in, size_t& pos, boolean* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<boolean>& x);
};

template<>
struct unpack<uint8>
{
    unpack(const Buffer& in, size_t& pos, uint8& x);
    // unpack(const Buffer& in, size_t& pos, uint8* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<uint8>& x);
};

template<>
struct unpack<uint16>
{
    unpack(const Buffer& in, size_t& pos, uint16& x);
    // unpack(const Buffer& in, size_t& pos, uint16* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<uint16>& x);
};

template<>
struct unpack<uint32>
{
    unpack(const Buffer& in, size_t& pos, uint32& x);
    // unpack(const Buffer& in, size_t& pos, uint32* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<uint32>& x);
};

template<>
struct unpack<uint64>
{
    unpack(const Buffer& in, size_t& pos, uint64& x);
    // unpack(const Buffer& in, size_t& pos, uint64* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<uint64>& x);
};

template<>
struct unpack<real32>
{
    unpack(const Buffer& in, size_t& pos, real32& x);
    // unpack(const Buffer& in, size_t& pos, real32* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<real32>& x);
};

template<>
struct unpack<real64>
{
    unpack(const Buffer& in, size_t& pos, real64& x);
    // unpack(const Buffer& in, size_t& pos, real64* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<real64>& x);
};

template<>
struct unpack<String>
{
    unpack(const Buffer& in, size_t& pos, String& x);
    // unpack(const Buffer& in, size_t& pos, String* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<String>& x);
};

template<>
struct unpack<Datetime>
{
    unpack(const Buffer& in, size_t& pos, Datetime& x);
    // unpack(const Buffer& in, size_t& pos, Datetime* data, size_t size);
    unpack(const Buffer& in, size_t& pos, Array<Datetime>& x);
};

inline unpack<uint8>::unpack(const Buffer& in, size_t& pos, uint8& x)
{
    x = in[pos++];
}

unpack<boolean>::unpack(const Buffer& in, size_t& pos, boolean& x)
{
    x = in[pos++] ? true : false;
}

inline unpack<real32>::unpack(const Buffer& in, size_t& pos, real32& x)
{
    uint32 tmp;
    unpack<uint32>(in, pos, tmp);
    memcpy(&x, &tmp, sizeof(tmp));
}

inline unpack<real64>::unpack(const Buffer& in, size_t& pos, real64& x)
{
    uint64 tmp;
    unpack<uint64>(in, pos, tmp);
    memcpy(&x, &tmp, sizeof(tmp));
}

#if 0

inline unpack<real32>::unpack(
    const Buffer& in, size_t& pos, real32* data, size_t size)
{
    unpack<uint32>(in, pos, (uint32*)data, size);
}

inline unpack<real64>::unpack(
    const Buffer& in, size_t& pos, real64* data, size_t size)
{
    unpack<uint64>(in, pos, (uint64*)data, size);
}

#endif

CIMPLE_NAMESPACE_END

#endif /* _cimple_Encoding_h */
