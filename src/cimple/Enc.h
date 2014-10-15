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

CIMPLE_NAMESPACE_BEGIN

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

CIMPLE_LIBCIMPLE_LINKAGE
void pack_uint16(Buffer& out, const uint16& x);

CIMPLE_LIBCIMPLE_LINKAGE
void pack_uint32(Buffer& out, const uint32& x);

CIMPLE_LIBCIMPLE_LINKAGE
void pack_uint64(Buffer& out, const uint64& x);

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

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_uint32(const Buffer& in, size_t& pos, uint32& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_uint64(const Buffer& in, size_t& pos, uint64& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_real32(const Buffer& in, size_t& pos, real32& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_real64(const Buffer& in, size_t& pos, real64& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_string(const Buffer& in, size_t& pos, String& x);

CIMPLE_LIBCIMPLE_LINKAGE
void unpack_c_str(const Buffer& in, size_t& pos, char*& str);

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

//==============================================================================
//
// pack<>
//
//==============================================================================

template<class T>
struct pack
{
};

template<>
struct pack<boolean>
{
    pack(Buffer& out, const boolean& x) 
    { 
	pack_boolean(out, x); 
    }

    pack(Buffer& out, const Array<boolean>& x) 
    { 
	pack_boolean_array(out, x); 
    }
};

template<>
struct pack<uint8>
{
    pack(Buffer& out, const uint8& x) 
    { 
	pack_uint8(out, x); 
    }

    pack(Buffer& out, const Array<uint8>& x) 
    { 
	pack_uint8_array(out, x); 
    }
};

template<>
struct pack<uint16>
{
    pack(Buffer& out, const uint16& x) 
    { 
	pack_uint16(out, x); 
    }

    pack(Buffer& out, const Array<uint16>& x) 
    { 
	pack_uint16_array(out, x); 
    }
};

template<>
struct pack<uint32>
{
    pack(Buffer& out, const uint32& x) 
    { 
	pack_uint32(out, x); 
    }

    pack(Buffer& out, const Array<uint32>& x) 
    { 
	pack_uint32_array(out, x); 
    }
};

template<>
struct pack<uint64>
{
    pack(Buffer& out, const uint64& x) 
    { 
	pack_uint64(out, x); 
    }

    pack(Buffer& out, const Array<uint64>& x) 
    { 
	pack_uint64_array(out, x); 
    }
};

template<>
struct pack<real32>
{
    pack(Buffer& out, const real32& x) 
    { 
	pack_real32(out, x); 
    }

    pack(Buffer& out, const Array<real32>& x) 
    { 
	pack_real32_array(out, x); 
    }
};

template<>
struct pack<real64>
{
    pack(Buffer& out, const real64& x) 
    { 
	pack_real64(out, x); 
    }

    pack(Buffer& out, const Array<real64>& x) 
    { 
	pack_real64_array(out, x); 
    }
};

template<>
struct pack<String>
{
    pack(Buffer& out, const String& x) 
    { 
	pack_string(out, x); 
    }

    pack(Buffer& out, const Array<String>& x) 
    { 
	pack_string_array(out, x); 
    }
};

template<>
struct pack<Datetime>
{
    pack(Buffer& out, const Datetime& x) 
    { 
	pack_datetime(out, x); 
    }

    pack(Buffer& out, const Array<Datetime>& x) 
    { 
	pack_datetime_array(out, x); 
    }
};

//==============================================================================
//
// unpack<>
//
//==============================================================================

template<class T>
struct unpack
{
};

template<>
struct unpack<boolean>
{
    unpack(const Buffer& in, size_t& pos, boolean& x) 
    { 
	unpack_boolean(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<boolean>& x) 
    { 
	unpack_boolean_array(in, pos, x); 
    }
};

template<>
struct unpack<uint8>
{
    unpack(const Buffer& in, size_t& pos, uint8& x) 
    { 
	unpack_uint8(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<uint8>& x) 
    { 
	unpack_uint8_array(in, pos, x); 
    }
};

template<>
struct unpack<uint16>
{
    unpack(const Buffer& in, size_t& pos, uint16& x) 
    { 
	unpack_uint16(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<uint16>& x) 
    { 
	unpack_uint16_array(in, pos, x); 
    }
};

template<>
struct unpack<uint32>
{
    unpack(const Buffer& in, size_t& pos, uint32& x) 
    { 
	unpack_uint32(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<uint32>& x) 
    { 
	unpack_uint32_array(in, pos, x); 
    }
};

template<>
struct unpack<uint64>
{
    unpack(const Buffer& in, size_t& pos, uint64& x) 
    { 
	unpack_uint64(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<uint64>& x) 
    { 
	unpack_uint64_array(in, pos, x); 
    }
};

template<>
struct unpack<real32>
{
    unpack(const Buffer& in, size_t& pos, real32& x) 
    { 
	unpack_real32(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<real32>& x) 
    { 
	unpack_real32_array(in, pos, x); 
    }
};

template<>
struct unpack<real64>
{
    unpack(const Buffer& in, size_t& pos, real64& x) 
    { 
	unpack_real64(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<real64>& x) 
    { 
	unpack_real64_array(in, pos, x); 
    }
};

template<>
struct unpack<String>
{
    unpack(const Buffer& in, size_t& pos, String& x) 
    { 
	unpack_string(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<String>& x) 
    { 
	unpack_string_array(in, pos, x); 
    }
};

template<>
struct unpack<Datetime>
{
    unpack(const Buffer& in, size_t& pos, Datetime& x) 
    { 
	unpack_datetime(in, pos, x); 
    }

    unpack(const Buffer& in, size_t& pos, Array<Datetime>& x) 
    { 
	unpack_datetime_array(in, pos, x); 
    }
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Enc_h */
