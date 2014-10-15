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

#ifndef _cimple_Class_h
#define _cimple_Class_h

#include "config.h"
#include "Meta_Class.h"
#include "Exception.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_CIMPLE_LINKAGE CIM_Class
{
public:

    enum Type_Tag
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
        INSTANCE,
        REFERENCE,
        METHOD,
        BOOLEAN_ARRAY = (0x80 | BOOLEAN),
        UINT8_ARRAY = (0x80 | UINT8),
        SINT8_ARRAY = (0x80 | SINT8),
        UINT16_ARRAY = (0x80 | UINT16),
        SINT16_ARRAY = (0x80 | SINT16),
        UINT32_ARRAY = (0x80 | UINT32),
        SINT32_ARRAY = (0x80 | SINT32),
        UINT64_ARRAY = (0x80 | UINT64),
        SINT64_ARRAY = (0x80 | SINT64),
        REAL32_ARRAY = (0x80 | REAL32),
        REAL64_ARRAY = (0x80 | REAL64),
        CHAR16_ARRAY = (0x80 | CHAR16),
        STRING_ARRAY = (0x80 | STRING),
        DATETIME_ARRAY = (0x80 | DATETIME),
        INSTANCE_ARRAY = (0x80 | INSTANCE),
        REFERENCE_ARRAY = (0x80 | REFERENCE),
        METHOD_ARRAY = (0x80 | METHOD),
    };

    enum Association_Tag { ASSOCIATION };

    enum Indication_Tag { INDICATION };

    enum Key_Tag { KEY };

    CIM_Class(const char* name);

    CIM_Class(const char* name, Association_Tag);

    CIM_Class(const char* name, Indication_Tag);

    CIM_Class(const char* name, const CIM_Class& super_class);

    CIM_Class(const CIM_Class& x);

    ~CIM_Class();

    CIM_Class& operator=(const CIM_Class& x);

    void print(bool local_only = true) const;

    bool is_class() const;

    bool is_association() const;

    bool is_indication() const;

    bool is_null(size_t pos) const;

    bool is_null(const char* name) const;

    bool is_property(size_t pos) const;

    bool is_reference (size_t pos) const;

    bool is_method(size_t pos) const;

    Type_Tag get_type(size_t pos) const;

    bool is_array(size_t pos) const;

    const char* get_name(size_t pos) const;

    size_t count() const;

    size_t add_property(const char* name, Type type);

    size_t add_property(const char* name, Type type, Key_Tag);

    size_t add_vla_property(const char* name, Type type);

    size_t add_vla_property(const char* name, Type type, Key_Tag);

    size_t add_fla_property(const char* name, Type type, uint32 subscript);

    size_t add_fla_property(
        const char* name, Type type, uint32 subscript, Key_Tag);

    void clear(const char* name);

    void set_property(size_t pos, boolean x);
    void set_property(size_t pos, uint8 x);
    void set_property(size_t pos, sint8 x);
    void set_property(size_t pos, uint16 x);
    void set_property(size_t pos, sint16 x);
    void set_property(size_t pos, uint32 x);
    void set_property(size_t pos, sint32 x);
    void set_property(size_t pos, uint64 x);
    void set_property(size_t pos, sint64 x);
    void set_property(size_t pos, real32 x);
    void set_property(size_t pos, real64 x);
    void set_property(size_t pos, const char16& x);
    void set_property(size_t pos, const char* x);
    void set_property(size_t pos, const String& x);
    void set_property(size_t pos, const Datetime& x);
    void set_property(size_t pos, const Array<boolean>& x);
    void set_property(size_t pos, const Array<uint8>& x);
    void set_property(size_t pos, const Array<sint8>& x);
    void set_property(size_t pos, const Array<uint16>& x);
    void set_property(size_t pos, const Array<sint16>& x);
    void set_property(size_t pos, const Array<uint32>& x);
    void set_property(size_t pos, const Array<sint32>& x);
    void set_property(size_t pos, const Array<uint64>& x);
    void set_property(size_t pos, const Array<sint64>& x);
    void set_property(size_t pos, const Array<real32>& x);
    void set_property(size_t pos, const Array<real64>& x);
    void set_property(size_t pos, const Array<char16>& x);
    void set_property(size_t pos, const Array<String>& x);
    void set_property(size_t pos, const Array<Datetime>& x);
    void set_property(const char* name, boolean x);
    void set_property(const char* name, uint8 x);
    void set_property(const char* name, sint8 x);
    void set_property(const char* name, uint16 x);
    void set_property(const char* name, sint16 x);
    void set_property(const char* name, uint32 x);
    void set_property(const char* name, sint32 x);
    void set_property(const char* name, uint64 x);
    void set_property(const char* name, sint64 x);
    void set_property(const char* name, real32 x);
    void set_property(const char* name, real64 x);
    void set_property(const char* name, const char16& x);
    void set_property(const char* name, const char* x);
    void set_property(const char* name, const String& x);
    void set_property(const char* name, const Datetime& x);
    void set_property(const char* name, const Array<boolean>& x);
    void set_property(const char* name, const Array<uint8>& x);
    void set_property(const char* name, const Array<sint8>& x);
    void set_property(const char* name, const Array<uint16>& x);
    void set_property(const char* name, const Array<sint16>& x);
    void set_property(const char* name, const Array<uint32>& x);
    void set_property(const char* name, const Array<sint32>& x);
    void set_property(const char* name, const Array<uint64>& x);
    void set_property(const char* name, const Array<sint64>& x);
    void set_property(const char* name, const Array<real32>& x);
    void set_property(const char* name, const Array<real64>& x);
    void set_property(const char* name, const Array<char16>& x);
    void set_property(const char* name, const Array<String>& x);
    void set_property(const char* name, const Array<Datetime>& x);

    void get_property(size_t pos, boolean& x) const;
    void get_property(size_t pos, uint8& x) const;
    void get_property(size_t pos, sint8& x) const;
    void get_property(size_t pos, uint16& x) const;
    void get_property(size_t pos, sint16& x) const;
    void get_property(size_t pos, uint32& x) const;
    void get_property(size_t pos, sint32& x) const;
    void get_property(size_t pos, uint64& x) const;
    void get_property(size_t pos, sint64& x) const;
    void get_property(size_t pos, real32& x) const;
    void get_property(size_t pos, real64& x) const;
    void get_property(size_t pos, char16& x) const;
    void get_property(size_t pos, String& x) const;
    void get_property(size_t pos, Datetime& x) const;
    void get_property(size_t pos, Array<boolean>& x) const;
    void get_property(size_t pos, Array<uint8>& x) const;
    void get_property(size_t pos, Array<sint8>& x) const;
    void get_property(size_t pos, Array<uint16>& x) const;
    void get_property(size_t pos, Array<sint16>& x) const;
    void get_property(size_t pos, Array<uint32>& x) const;
    void get_property(size_t pos, Array<sint32>& x) const;
    void get_property(size_t pos, Array<uint64>& x) const;
    void get_property(size_t pos, Array<sint64>& x) const;
    void get_property(size_t pos, Array<real32>& x) const;
    void get_property(size_t pos, Array<real64>& x) const;
    void get_property(size_t pos, Array<char16>& x) const;
    void get_property(size_t pos, Array<String>& x) const;
    void get_property(size_t pos, Array<Datetime>& x) const;
    void get_property(const char* name, boolean& x) const;
    void get_property(const char* name, uint8& x) const;
    void get_property(const char* name, sint8& x) const;
    void get_property(const char* name, uint16& x) const;
    void get_property(const char* name, sint16& x) const;
    void get_property(const char* name, uint32& x) const;
    void get_property(const char* name, sint32& x) const;
    void get_property(const char* name, uint64& x) const;
    void get_property(const char* name, sint64& x) const;
    void get_property(const char* name, real32& x) const;
    void get_property(const char* name, real64& x) const;
    void get_property(const char* name, char16& x) const;
    void get_property(const char* name, String& x) const;
    void get_property(const char* name, Datetime& x) const;
    void get_property(const char* name, Array<boolean>& x) const;
    void get_property(const char* name, Array<uint8>& x) const;
    void get_property(const char* name, Array<sint8>& x) const;
    void get_property(const char* name, Array<uint16>& x) const;
    void get_property(const char* name, Array<sint16>& x) const;
    void get_property(const char* name, Array<uint32>& x) const;
    void get_property(const char* name, Array<sint32>& x) const;
    void get_property(const char* name, Array<uint64>& x) const;
    void get_property(const char* name, Array<sint64>& x) const;
    void get_property(const char* name, Array<real32>& x) const;
    void get_property(const char* name, Array<real64>& x) const;
    void get_property(const char* name, Array<char16>& x) const;
    void get_property(const char* name, Array<String>& x) const;
    void get_property(const char* name, Array<Datetime>& x) const;

    // ATTN: references!
    // ATTN: methods!
    // ATTN: qualifiers!

private:
    CIM_Class();
    Meta_Class* _mc;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Class_h */
