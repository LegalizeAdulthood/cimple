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

#ifndef _cimple_Type_h
#define _cimple_Type_h

#include "config.h"
#include "String.h"
#include "char16.h"
#include "Datetime.h"

CIMPLE_NAMESPACE_BEGIN

/** CIM data types.
*/
enum Type
{
    BOOLEAN,
    UINT8,
    SINT8,
    UINT16,
    SINT16,
    UINT32,
    SINT32,
    UINT64,
    SINT64,
    REAL32,
    REAL64,
    CHAR16,
    STRING,
    DATETIME,
};

CIMPLE_CIMPLE_LINKAGE 
extern size_t const type_size[];

CIMPLE_CIMPLE_LINKAGE 
extern size_t const literal_type_size[];

CIMPLE_CIMPLE_LINKAGE 
extern const char* const type_name[];

inline void __clear(boolean& x) { x = false; }
inline void __clear(uint8& x) { x = 0; }
inline void __clear(sint8& x) { x = 0; }
inline void __clear(uint16& x) { x = 0; }
inline void __clear(sint16& x) { x = 0; }
inline void __clear(uint32& x) { x = 0; }
inline void __clear(sint32& x) { x = 0; }
inline void __clear(uint64& x) { x = 0; }
inline void __clear(sint64& x) { x = 0; }
inline void __clear(real32& x) { x = 0.0; }
inline void __clear(real64& x) { x = 0.0; }

class String;

inline Type type_of(const boolean& x) { return BOOLEAN; }
inline Type type_of(const uint8& x) { return UINT8; }
inline Type type_of(const sint8& x) { return SINT8; }
inline Type type_of(const uint16& x) { return UINT16; }
inline Type type_of(const sint16& x) { return SINT16; }
inline Type type_of(const uint32& x) { return UINT32; }
inline Type type_of(const sint32& x) { return SINT32; }
inline Type type_of(const uint64& x) { return UINT64; }
inline Type type_of(const sint64& x) { return SINT64; }
inline Type type_of(const real32& x) { return REAL32; }
inline Type type_of(const real64& x) { return REAL64; }
inline Type type_of(const char16& x) { return CHAR16; }
inline Type type_of(const String& x) { return STRING; }
inline Type type_of(const Datetime& x) { return DATETIME; }

inline bool is_integer(Type type) { return type >= UINT8 && type <= SINT64; }

inline bool is_real(Type type) { return type == REAL32 || type == REAL64; }

CIMPLE_CIMPLE_LINKAGE 
int type_name_to_type(const char* name, Type& type);

CIMPLE_CIMPLE_LINKAGE
void fprint_scalar(FILE* os, Type type, const void* value);

CIMPLE_CIMPLE_LINKAGE
void print_scalar(Type type, const void* value);

CIMPLE_CIMPLE_LINKAGE
void fprint_array(
    FILE* os, Type type, const void* elements, size_t num_elements);

CIMPLE_CIMPLE_LINKAGE
void print_array(Type type, const void* elements, size_t num_elements);

extern void fprint_string(FILE* os, const char* str);

extern void print_string(const char* str);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Type_h */
