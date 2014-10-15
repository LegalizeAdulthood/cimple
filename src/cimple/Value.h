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

#ifndef _cimple_Value_h
#define _cimple_Value_h

#include "config.h"
#include "String.h"
#include "char16.h"
#include "Datetime.h"
#include "Type.h"
#include "Array.h"
#include "Instance.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_CIMPLE_LINKAGE Value
{
public:

    enum Type
    {
        NONE = -1,
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
    };

    Value();

    Value(const Value& x);

    ~Value();

    Value& operator=(const Value& x);

    void clear();

    int get(Instance* instance, const Meta_Feature* mf);

    int set(const Instance* instance, const Meta_Feature* mf);

    Type type() const { return _type; }

    bool null() const { return _null; }

    void null(bool null) { _null = null; }

    int get_value(boolean& x) const;
    int get_value(uint8& x) const;
    int get_value(sint8& x) const;
    int get_value(uint16& x) const;
    int get_value(sint16& x) const;
    int get_value(uint32& x) const;
    int get_value(sint32& x) const;
    int get_value(uint64& x) const;
    int get_value(sint64& x) const;
    int get_value(real32& x) const;
    int get_value(real64& x) const;
    int get_value(char16& x) const;
    int get_value(String& x) const;
    int get_value(Datetime& x) const;
    int get_value(Instance*& x) const;
    int get_value(Array_boolean& x) const;
    int get_value(Array_uint8& x) const;
    int get_value(Array_sint8& x) const;
    int get_value(Array_uint16& x) const;
    int get_value(Array_sint16& x) const;
    int get_value(Array_uint32& x) const;
    int get_value(Array_sint32& x) const;
    int get_value(Array_uint64& x) const;
    int get_value(Array_sint64& x) const;
    int get_value(Array_real32& x) const;
    int get_value(Array_real64& x) const;
    int get_value(Array_char16& x) const;
    int get_value(Array_String& x) const;
    int get_value(Array_Datetime& x) const;
    int get_value(Array_Instance& x) const;

    void set_value(const boolean& x);
    void set_value(const uint8& x);
    void set_value(const sint8& x);
    void set_value(const uint16& x);
    void set_value(const sint16& x);
    void set_value(const uint32& x);
    void set_value(const sint32& x);
    void set_value(const uint64& x);
    void set_value(const sint64& x);
    void set_value(const real32& x);
    void set_value(const real64& x);
    void set_value(const char16& x);
    void set_value(const String& x);
    void set_value(const char* x);
    void set_value(const Datetime& x);
    void set_value(Instance* x);
    void set_value(const Array_boolean& x);
    void set_value(const Array_uint8& x);
    void set_value(const Array_sint8& x);
    void set_value(const Array_uint16& x);
    void set_value(const Array_sint16& x);
    void set_value(const Array_uint32& x);
    void set_value(const Array_sint32& x);
    void set_value(const Array_uint64& x);
    void set_value(const Array_sint64& x);
    void set_value(const Array_real32& x);
    void set_value(const Array_real64& x);
    void set_value(const Array_char16& x);
    void set_value(const Array_String& x);
    void set_value(const Array_Datetime& x);
    void set_value(const Array_Instance& x);

    void fprint(FILE* os) const;

    void print() const;

private:

    void _construct(const Value& x);

    Type _type;
    bool _null;
    union
    {
        boolean _boolean;
        uint8 _uint8;
        sint8 _sint8;
        uint16 _uint16;
        sint16 _sint16;
        uint32 _uint32;
        sint32 _sint32;
        uint64 _uint64;
        sint64 _sint64;
        real32 _real32;
        real64 _real64;
        char _char16[sizeof(char16)];
        char _string[sizeof(String)];
        char _datetime[sizeof(Datetime)];
        Instance* _instance;
        char _array[sizeof(__Array_Base)];
        char _buffer[1];
    };
};

CIMPLE_CIMPLE_LINKAGE 
Value::Type type_of(const Meta_Feature* mf);

CIMPLE_CIMPLE_LINKAGE 
const char* name_of(Value::Type type);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Value_h */
