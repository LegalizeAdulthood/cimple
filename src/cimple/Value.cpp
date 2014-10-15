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

#include "log.h"
#include "Value.h"
#include "Property.h"

CIMPLE_NAMESPACE_BEGIN

Value::Value() : _type(Value::NONE), _null(false)
{
}

Value::Value(const Value& x)
{
    memcpy(this, &x, sizeof(x));
    _construct(x);
}

Value::~Value()
{
    clear();
}

Value& Value::operator=(const Value& x)
{
    if (this != &x)
    {
        clear();
        memcpy(this, &x, sizeof(x));
        _construct(x);
    }

    return *this;
}

void Value::clear()
{
    switch (_type)
    {
        case NONE:
        case BOOLEAN:
        case UINT8:
        case SINT8:
        case UINT16:
        case SINT16:
        case UINT32:
        case SINT32:
        case UINT64:
        case SINT64:
        case REAL32:
        case REAL64:
        case CHAR16:
            break;

        case STRING:
            ((String*)_string)->~String();
            break;

        case DATETIME:
            ((Datetime*)_string)->~Datetime();
            break;

        case INSTANCE:
            unref(_instance);
            break;

        case BOOLEAN_ARRAY:
        case UINT8_ARRAY:
        case SINT8_ARRAY:
        case UINT16_ARRAY:
        case SINT16_ARRAY:
        case UINT32_ARRAY:
        case SINT32_ARRAY:
        case UINT64_ARRAY:
        case SINT64_ARRAY:
        case REAL32_ARRAY:
        case REAL64_ARRAY:
        case CHAR16_ARRAY:
        case STRING_ARRAY:
        case DATETIME_ARRAY:
            __destruct(((__Array_Base*)_array)->rep);
            break;

        case INSTANCE_ARRAY:
        {
            Array_Instance* inst = (Array_Instance*)(void*)_array;
            Instance** p = inst->data();
            Instance** end = inst->data() + inst->size();

            while (p != end)
                unref(*p++);

            __destruct(((__Array_Base*)_array)->rep);
            break;
        }
    }

    _type = NONE;
    _null = true;
}

void Value::_construct(const Value& x)
{
    memcpy(this, &x, sizeof(x));

    switch (_type)
    {
        case NONE:
        case BOOLEAN:
        case UINT8:
        case SINT8:
        case UINT16:
        case SINT16:
        case UINT32:
        case SINT32:
        case UINT64:
        case SINT64:
        case REAL32:
        case REAL64:
        case CHAR16:
            break;

        case STRING:
            new((String*)_string) String(*(String*)x._string);
            break;

        case DATETIME:
            new((Datetime*)_datetime) Datetime(*(Datetime*)x._datetime);
            break;

        case INSTANCE:
            ref(_instance = x._instance);
            break;

        case BOOLEAN_ARRAY:
        case UINT8_ARRAY:
        case SINT8_ARRAY:
        case UINT16_ARRAY:
        case SINT16_ARRAY:
        case UINT32_ARRAY:
        case SINT32_ARRAY:
        case UINT64_ARRAY:
        case SINT64_ARRAY:
        case REAL32_ARRAY:
        case REAL64_ARRAY:
        case CHAR16_ARRAY:
        case STRING_ARRAY:
        case DATETIME_ARRAY:
            __construct(
                ((__Array_Base*)_array)->rep, ((__Array_Base*)x._array)->rep);
            break;

        case INSTANCE_ARRAY:
        {
            __construct(
                ((__Array_Base*)_array)->rep, ((__Array_Base*)x._array)->rep);

            Array_Instance* inst = (Array_Instance*)_array;
            Instance** p = inst->data();
            Instance** end = p + inst->size();

            while (p != end)
                ref(*p++);

            break;
        }
    }
}

int Value::get_value(boolean& x) const
{
    if (_type != Value::BOOLEAN)
        return -1;

    x = _boolean;
    return 0;
}

int Value::get_value(uint8& x) const
{
    if (_type != Value::UINT8)
        return -1;

    x = _uint8;
    return 0;
}

int Value::get_value(sint8& x) const
{
    if (_type != Value::SINT8)
        return -1;

    x = _sint8;
    return 0;
}

int Value::get_value(uint16& x) const
{
    if (_type != Value::UINT16)
        return -1;

    x = _uint16;
    return 0;
}

int Value::get_value(sint16& x) const
{
    if (_type != Value::SINT16)
        return -1;

    x = _sint16;
    return 0;
}

int Value::get_value(uint32& x) const
{
    if (_type != Value::UINT32)
        return -1;

    x = _uint32;
    return 0;
}

int Value::get_value(sint32& x) const
{
    if (_type != Value::SINT32)
        return -1;

    x = _sint32;
    return 0;
}

int Value::get_value(uint64& x) const
{
    if (_type != Value::UINT64)
        return -1;

    x = _uint64;
    return 0;
}

int Value::get_value(sint64& x) const
{
    if (_type != Value::SINT64)
        return -1;

    x = _sint64;
    return 0;
}

int Value::get_value(real32& x) const
{
    if (_type != Value::REAL32)
        return -1;

    x = _real32;
    return 0;
}

int Value::get_value(real64& x) const
{
    if (_type != Value::REAL64)
        return -1;

    x = _real64;
    return 0;
}

int Value::get_value(char16& x) const
{
    if (_type != Value::CHAR16)
        return -1;

    x = *((char*)_char16);
    return 0;
}

int Value::get_value(String& x) const
{
    if (_type != Value::STRING)
        return -1;

    x = *((String*)_string);
    return 0;
}

int Value::get_value(Datetime& x) const
{
    if (_type != Value::DATETIME)
        return -1;

    x = *((Datetime*)_datetime);
    return 0;
}

int Value::get_value(Instance*& x) const
{
    if (_type != Value::INSTANCE)
        return -1;

    x = _instance;
    return 0;
}

int Value::get_value(Array_boolean& x) const
{
    if (_type != Value::BOOLEAN_ARRAY)
        return -1;

    x = *((Array_boolean*)(void*)_array);
    return 0;
}

int Value::get_value(Array_uint8& x) const
{
    if (_type != Value::UINT8_ARRAY)
        return -1;

    x = *((Array_uint8*)(void*)_array);
    return 0;
}

int Value::get_value(Array_sint8& x) const
{
    if (_type != Value::SINT8_ARRAY)
        return -1;

    x = *((Array_sint8*)(void*)_array);
    return 0;
}

int Value::get_value(Array_uint16& x) const
{
    if (_type != Value::UINT16_ARRAY)
        return -1;

    x = *((Array_uint16*)(void*)_array);
    return 0;
}

int Value::get_value(Array_sint16& x) const
{
    if (_type != Value::SINT16_ARRAY)
        return -1;

    x = *((Array_sint16*)(void*)_array);
    return 0;
}

int Value::get_value(Array_uint32& x) const
{
    if (_type != Value::UINT32_ARRAY)
        return -1;

    x = *((Array_uint32*)(void*)_array);
    return 0;
}

int Value::get_value(Array_sint32& x) const
{
    if (_type != Value::SINT32_ARRAY)
        return -1;

    x = *((Array_sint32*)(void*)_array);
    return 0;
}

int Value::get_value(Array_uint64& x) const
{
    if (_type != Value::UINT64_ARRAY)
        return -1;

    x = *((Array_uint64*)(void*)_array);
    return 0;
}

int Value::get_value(Array_sint64& x) const
{
    if (_type != Value::SINT64_ARRAY)
        return -1;

    x = *((Array_sint64*)(void*)_array);
    return 0;
}

int Value::get_value(Array_real32& x) const
{
    if (_type != Value::REAL32_ARRAY)
        return -1;

    x = *((Array_real32*)(void*)_array);
    return 0;
}

int Value::get_value(Array_real64& x) const
{
    if (_type != Value::REAL64_ARRAY)
        return -1;

    x = *((Array_real64*)(void*)_array);
    return 0;
}

int Value::get_value(Array_char16& x) const
{
    if (_type != Value::CHAR16_ARRAY)
        return -1;

    x = *((Array_char16*)(void*)_array);
    return 0;
}

int Value::get_value(Array_String& x) const
{
    if (_type != Value::STRING_ARRAY)
        return -1;

    x = *((Array_String*)(void*)_array);
    return 0;
}

int Value::get_value(Array_Datetime& x) const
{
    if (_type != Value::DATETIME_ARRAY)
        return -1;

    x = *((Array_Datetime*)(void*)_array);
    return 0;
}

int Value::get_value(Array_Instance& x) const
{
    if (_type != Value::INSTANCE_ARRAY)
        return -1;

    x = *((Array_Instance*)(void*)_array);
    return 0;
}

void Value::set_value(const boolean& x)
{
    clear();
    _type = Value::BOOLEAN;
    _null = false;
    _boolean = x;
}

void Value::set_value(const uint8& x)
{
    clear();
    _type = Value::UINT8;
    _null = false;
    _uint8 = x;
}

void Value::set_value(const sint8& x)
{
    clear();
    _type = Value::SINT8;
    _null = false;
    _sint8 = x;
}

void Value::set_value(const uint16& x)
{
    clear();
    _type = Value::UINT16;
    _null = false;
    _uint16 = x;
}

void Value::set_value(const sint16& x)
{
    clear();
    _type = Value::SINT16;
    _null = false;
    _sint16 = x;
}

void Value::set_value(const uint32& x)
{
    clear();
    _type = Value::UINT32;
    _null = false;
    _uint32 = x;
}

void Value::set_value(const sint32& x)
{
    clear();
    _type = Value::SINT32;
    _null = false;
    _sint32 = x;
}

void Value::set_value(const uint64& x)
{
    clear();
    _type = Value::UINT64;
    _null = false;
    _uint64 = x;
}

void Value::set_value(const sint64& x)
{
    clear();
    _type = Value::SINT64;
    _null = false;
    _sint64 = x;
}

void Value::set_value(const real32& x)
{
    clear();
    _type = Value::REAL32;
    _null = false;
    _real32 = x;
}

void Value::set_value(const real64& x)
{
    clear();
    _type = Value::REAL64;
    _null = false;
    _real64 = x;
}

void Value::set_value(const char16& x)
{
    clear();
    _type = Value::CHAR16;
    _null = false;
    new(_char16) char16(x);
}

void Value::set_value(const String& x)
{
    clear();
    _type = Value::STRING;
    _null = false;
    new(_string) String(x);
}

void Value::set_value(const char* x)
{
    set_value(String(x));
}

void Value::set_value(const Datetime& x)
{
    clear();
    _type = Value::DATETIME;
    _null = false;
    new(_datetime) Datetime(x);
}

void Value::set_value(Instance* x)
{
    clear();
    _type = Value::INSTANCE;
    _null = false;
    _instance = x;
}

void Value::set_value(const Array_boolean& x)
{
    clear();
    _type = Value::BOOLEAN_ARRAY;
    _null = false;
    new(_array) Array_boolean(x);
}

void Value::set_value(const Array_uint8& x)
{
    clear();
    _type = Value::UINT8_ARRAY;
    _null = false;
    new(_array) Array_uint8(x);
}

void Value::set_value(const Array_sint8& x)
{
    clear();
    _type = Value::SINT8_ARRAY;
    _null = false;
    new(_array) Array_sint8(x);
}

void Value::set_value(const Array_uint16& x)
{
    clear();
    _type = Value::UINT16_ARRAY;
    _null = false;
    new(_array) Array_uint16(x);
}

void Value::set_value(const Array_sint16& x)
{
    clear();
    _type = Value::SINT16_ARRAY;
    _null = false;
    new(_array) Array_sint16(x);
}

void Value::set_value(const Array_uint32& x)
{
    clear();
    _type = Value::UINT32_ARRAY;
    _null = false;
    new(_array) Array_uint32(x);
}

void Value::set_value(const Array_sint32& x)
{
    clear();
    _type = Value::SINT32_ARRAY;
    _null = false;
    new(_array) Array_sint32(x);
}

void Value::set_value(const Array_uint64& x)
{
    clear();
    _type = Value::UINT64_ARRAY;
    _null = false;
    new(_array) Array_uint64(x);
}

void Value::set_value(const Array_sint64& x)
{
    clear();
    _type = Value::SINT64_ARRAY;
    _null = false;
    new(_array) Array_sint64(x);
}

void Value::set_value(const Array_real32& x)
{
    clear();
    _type = Value::REAL32_ARRAY;
    _null = false;
    new(_array) Array_real32(x);
}

void Value::set_value(const Array_real64& x)
{
    clear();
    _type = Value::REAL64_ARRAY;
    _null = false;
    new(_array) Array_real64(x);
}

void Value::set_value(const Array_char16& x)
{
    clear();
    _type = Value::CHAR16_ARRAY;
    _null = false;
    new(_array) Array_char16(x);
}

void Value::set_value(const Array_String& x)
{
    clear();
    _type = Value::STRING_ARRAY;
    _null = false;
    new(_array) Array_String(x);
}

void Value::set_value(const Array_Datetime& x)
{
    clear();
    _type = Value::DATETIME_ARRAY;
    _null = false;
    new(_array) Array_Datetime(x);
}

void Value::set_value(const Array_Instance& x)
{
    clear();
    _type = Value::INSTANCE_ARRAY;
    _null = false;
    new(_array) Array_Instance(x);
}

const char* _type_name(Value::Type type)
{
    switch (type)
    {
        case Value::NONE: return "NONE";
        case Value::BOOLEAN: return "BOOLEAN";
        case Value::UINT8: return "UINT8";
        case Value::SINT8: return "SINT8";
        case Value::UINT16: return "UINT16";
        case Value::SINT16: return "SINT16";
        case Value::UINT32: return "UINT32";
        case Value::SINT32: return "SINT32";
        case Value::UINT64: return "UINT64";
        case Value::SINT64: return "SINT64";
        case Value::REAL32: return "REAL32";
        case Value::REAL64: return "REAL64";
        case Value::CHAR16: return "CHAR16";
        case Value::STRING: return "STRING";
        case Value::DATETIME: return "DATETIME";
        case Value::INSTANCE: return "INSTANCE";
        case Value::BOOLEAN_ARRAY: return "BOOLEAN_ARRAY";
        case Value::UINT8_ARRAY: return "UINT8_ARRAY";
        case Value::SINT8_ARRAY: return "SINT8_ARRAY";
        case Value::UINT16_ARRAY: return "UINT16_ARRAY";
        case Value::SINT16_ARRAY: return "SINT16_ARRAY";
        case Value::UINT32_ARRAY: return "UINT32_ARRAY";
        case Value::SINT32_ARRAY: return "SINT32_ARRAY";
        case Value::UINT64_ARRAY: return "UINT64_ARRAY";
        case Value::SINT64_ARRAY: return "SINT64_ARRAY";
        case Value::REAL32_ARRAY: return "REAL32_ARRAY";
        case Value::REAL64_ARRAY: return "REAL64_ARRAY";
        case Value::CHAR16_ARRAY: return "CHAR16_ARRAY";
        case Value::STRING_ARRAY: return "STRING_ARRAY";
        case Value::DATETIME_ARRAY: return "DATETIME_ARRAY";
        case Value::INSTANCE_ARRAY: return "INSTANCE_ARRAY";
    }

    return 0;
}

void Value::fprint(FILE* os) const
{
    fprintf(os, "Value\n");
    fprintf(os, "{\n");

    fprintf(os, "    type=%s\n", _type_name(_type));
    fprintf(os, "    null=%s\n", _null ? "true" : "false");
    // Don't display values when null set.  Info unreliable at least
    // for strings.
    if (_null)
    {
        fprintf(os, "    value= NONE\n");
        return;
    }
    fprintf(os, "    value=");

    switch (_type)
    {
        case NONE:
            fputc('\n', os);
            break;

        case BOOLEAN:
            __print_scalar(os, _type, &_boolean);
            fputc('\n', os);
            break;

        case UINT8:
            __print_scalar(os, _type, &_uint8);
            fputc('\n', os);
            break;

        case SINT8:
            __print_scalar(os, _type, &_sint8);
            fputc('\n', os);
            break;

        case UINT16:
            __print_scalar(os, _type, &_uint16);
            fputc('\n', os);
            break;

        case SINT16:
            __print_scalar(os, _type, &_sint16);
            fputc('\n', os);
            break;

        case UINT32:
            __print_scalar(os, _type, &_uint32);
            fputc('\n', os);
            break;

        case SINT32:
            __print_scalar(os, _type, &_sint32);
            fputc('\n', os);
            break;

        case UINT64:
            __print_scalar(os, _type, &_uint64);
            fputc('\n', os);
            break;

        case SINT64:
            __print_scalar(os, _type, &_sint64);
            fputc('\n', os);
            break;

        case REAL32:
            __print_scalar(os, _type, &_real32);
            fputc('\n', os);
            break;

        case REAL64:
            __print_scalar(os, _type, &_real64);
            fputc('\n', os);
            break;

        case CHAR16:
            __print_scalar(os, _type, &_char16);
            fputc('\n', os);
            break;

        case STRING:
            __print_scalar(os, _type, &_string);
            fputc('\n', os);
            break;

        case DATETIME:
            __print_scalar(os, _type, &_datetime);
            fputc('\n', os);
            break;

        case INSTANCE:
            cimple::fprint(os,_instance);
            break;

        case BOOLEAN_ARRAY:
            __print_array(os, _type & 0x7F, &_boolean, 1);
            fputc('\n', os);
            break;

        case UINT8_ARRAY:
            __print_array(os, _type & 0x7F, &_uint8, 1);
            fputc('\n', os);
            break;

        case SINT8_ARRAY:
            __print_array(os, _type & 0x7F, &_sint8, 1);
            fputc('\n', os);
            break;

        case UINT16_ARRAY:
            __print_array(os, _type & 0x7F, &_uint16, 1);
            fputc('\n', os);
            break;

        case SINT16_ARRAY:
            __print_array(os, _type & 0x7F, &_sint16, 1);
            fputc('\n', os);
            break;

        case UINT32_ARRAY:
            __print_array(os, _type & 0x7F, &_uint32, 1);
            fputc('\n', os);
            break;

        case SINT32_ARRAY:
            __print_array(os, _type & 0x7F, &_sint32, 1);
            fputc('\n', os);
            break;

        case UINT64_ARRAY:
            __print_array(os, _type & 0x7F, &_uint64, 1);
            fputc('\n', os);
            break;

        case SINT64_ARRAY:
            __print_array(os, _type & 0x7F, &_sint64, 1);
            fputc('\n', os);
            break;

        case REAL32_ARRAY:
            __print_array(os, _type & 0x7F, &_real32, 1);
            fputc('\n', os);
            break;

        case REAL64_ARRAY:
            __print_array(os, _type & 0x7F, &_real64, 1);
            fputc('\n', os);
            break;

        case CHAR16_ARRAY:
            __print_array(os, _type & 0x7F, &_char16, 1);
            fputc('\n', os);
            break;

        case STRING_ARRAY:
            __print_array(os, _type & 0x7F, &_string, 1);
            fputc('\n', os);
            break;

        case DATETIME_ARRAY:
            __print_array(os, _type & 0x7F, &_datetime, 1);
            fputc('\n', os);
            break;

        case INSTANCE_ARRAY:
        {
            fprintf(os, "\n    {\n");

            const Array_Instance& arr = *((Array_Instance*)_array);

            for (size_t i = 0; i < arr.size(); i++)
                __print_aux(os, arr[i], 0, 2, false);

            fprintf(os, "    }\n");
            break;
        }

        default:
            break;
    }

    fprintf(os, "}\n");
}

void Value::print() const
{
    fprint(stdout);
}

Value::Type type_of(const Meta_Feature* mf)
{
    if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (const Meta_Reference*)mf;

        if (mr->subscript)
            return Value::INSTANCE_ARRAY;
        else
            return Value::INSTANCE;
    }
    else if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;

        if (mp->subscript)
            return Value::Type(0x80 | mp->type);
        else
            return Value::Type(mp->type);
    }
    else
        return Value::NONE;
}

int Value::get(Instance* instance, const Meta_Feature* mf)
{
    if (!instance)
    {
        CIMPLE_WARN(("null instance argument"));
        return -1;
    }

    const Meta_Class* mc = instance->meta_class;
    void* field = 0;

    if (type_of(mf) != _type)
    {
        CIMPLE_WARN(("type mismatch: %s.%s", mc->name, mf->name));
        return -1;
    }

    if (mf->flags & CIMPLE_FLAG_METHOD)
    {
        return -1;
    }
    else if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;
        field = (char*)instance + mp->offset;

        if (_null)
            null_of(mp, field) = 1;
        else
            null_of(mp, field) = 0;
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (const Meta_Reference*)mf;
        field = (char*)instance + mr->offset;
    }

    switch (_type)
    {
        case NONE:
            return -1;

        case BOOLEAN:
            *((boolean*)field) = *((boolean*)_buffer);
            return 0;

        case UINT8:
            *((uint8*)field) = *((uint8*)_buffer);
            return 0;

        case SINT8:
            *((sint8*)field) = *((sint8*)_buffer);
            return 0;

        case UINT16:
            *((uint16*)field) = *((uint16*)_buffer);
            return 0;

        case SINT16:
            *((sint16*)field) = *((sint16*)_buffer);
            return 0;

        case UINT32:
            *((uint32*)field) = *((uint32*)_buffer);
            return 0;

        case SINT32:
            *((sint32*)field) = *((sint32*)_buffer);
            return 0;

        case UINT64:
            *((uint64*)field) = *((uint64*)_buffer);
            return 0;

        case SINT64:
            *((sint64*)field) = *((sint64*)_buffer);
            return 0;

        case REAL32:
            *((real32*)field) = *((real32*)_buffer);
            return 0;

        case REAL64:
            *((real64*)field) = *((real64*)_buffer);
            return 0;

        case CHAR16:
            *((char16*)field) = *((char16*)_buffer);
            return 0;

        case STRING:
            *((String*)field) = *((String*)_buffer);
            return 0;

        case DATETIME:
            *((Datetime*)field) = *((Datetime*)_buffer);
            return 0;

        case INSTANCE:
        {
            Instance* x = *((Instance**)_buffer);

            const Meta_Reference* mr = (const Meta_Reference*)mf;

            if (x && !is_subclass(mr->meta_class, x->meta_class))
            {
                CIMPLE_WARN(("failed to assign instance of %s to %s.%s",
                    x->meta_class->name, mc->name, mf->name));
                return -1;
            }

            ref(x);
            *((Instance**)field) = x;
            return 0;
        }

        case BOOLEAN_ARRAY:
            *((Array_boolean*)field) = *((Array_boolean*)_buffer);
            return 0;

        case UINT8_ARRAY:
            *((Array_uint8*)field) = *((Array_uint8*)_buffer);
            return 0;

        case SINT8_ARRAY:
            *((Array_sint8*)field) = *((Array_sint8*)_buffer);
            return 0;

        case UINT16_ARRAY:
            *((Array_uint16*)field) = *((Array_uint16*)_buffer);
            return 0;

        case SINT16_ARRAY:
            *((Array_sint16*)field) = *((Array_sint16*)_buffer);
            return 0;

        case UINT32_ARRAY:
            *((Array_uint32*)field) = *((Array_uint32*)_buffer);
            return 0;

        case SINT32_ARRAY:
            *((Array_sint32*)field) = *((Array_sint32*)_buffer);
            return 0;

        case UINT64_ARRAY:
            *((Array_uint64*)field) = *((Array_uint64*)_buffer);
            return 0;

        case SINT64_ARRAY:
            *((Array_sint64*)field) = *((Array_sint64*)_buffer);
            return 0;

        case REAL32_ARRAY:
            *((Array_real32*)field) = *((Array_real32*)_buffer);
            return 0;

        case REAL64_ARRAY:
            *((Array_real64*)field) = *((Array_real64*)_buffer);
            return 0;

        case CHAR16_ARRAY:
            *((Array_char16*)field) = *((Array_char16*)_buffer);
            return 0;

        case STRING_ARRAY:
            *((Array_String*)field) = *((Array_String*)_buffer);
            return 0;

        case DATETIME_ARRAY:
            *((Array_Datetime*)field) = *((Array_Datetime*)_buffer);
            return 0;

        case INSTANCE_ARRAY:
        {
            *((Array_Instance*)field) = *((Array_Instance*)_buffer);

            const Array_Instance& x = *((Array_Instance*)_buffer);
            const Meta_Reference* mr = (const Meta_Reference*)mf;

            for (size_t i = 0; i < x.size(); i++)
            {
                if (x[i] && !is_subclass(mr->meta_class, x[i]->meta_class))
                {
                    CIMPLE_WARN(("failed to assign instance of %s to %s.%s",
                        x[i]->meta_class->name, mc->name, mf->name));
                    return -1;
                }
                ref(x[i]);
            }

            return 0;
        }
    }

    return -1;
}

int Value::set(const Instance* instance, const Meta_Feature* mf)
{
    clear();

    const void* field = 0;

    if (mf->flags & CIMPLE_FLAG_METHOD)
    {
        return -1;
    }
    else if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;
        field = (const char*)instance + mp->offset;
        _null = null_of(mp, field);
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (const Meta_Reference*)mf;
        field = (char*)instance + mr->offset;

        if (mr->subscript)
        {
            _null = ((Property<Array_Ref>*)field)->null;
        }
        else
        {
            _null = *((Instance**)field) == 0;
        }
    }

    _type = type_of(mf);

    switch (_type)
    {
        case NONE:
            return -1;

        case BOOLEAN:
            *((boolean*)_buffer) = *(const boolean*)field;
            return 0;

        case UINT8:
            *((uint8*)_buffer) = *(const uint8*)field;
            return 0;

        case SINT8:
            *((sint8*)_buffer) = *(const sint8*)field;
            return 0;

        case UINT16:
            *((uint16*)_buffer) = *(const uint16*)field;
            return 0;

        case SINT16:
            *((sint16*)_buffer) = *(const sint16*)field;
            return 0;

        case UINT32:
            *((uint32*)_buffer) = *(const uint32*)field;
            return 0;

        case SINT32:
            *((sint32*)_buffer) = *(const sint32*)field;
            return 0;

        case UINT64:
            *((uint64*)_buffer) = *(const uint64*)field;
            return 0;

        case SINT64:
            *((sint64*)_buffer) = *(const sint64*)field;
            return 0;

        case REAL32:
            *((real32*)_buffer) = *(const real32*)field;
            return 0;

        case REAL64:
            *((real64*)_buffer) = *(const real64*)field;
            return 0;

        case CHAR16:
            *((char16*)_buffer) = *(const char16*)field;
            return 0;

        case STRING:
            new(_buffer) String(*(const String*)field);
            return 0;

        case DATETIME:
            new(_buffer) Datetime(*(const Datetime*)field);
            return 0;

        case INSTANCE:
        {
            _instance = *((Instance**)field);
            ref(_instance);
            return 0;
        }

        case BOOLEAN_ARRAY:
            new(_buffer) Array_boolean(*(Array_boolean*)field);
            return 0;

        case UINT8_ARRAY:
            new(_buffer) Array_uint8(*(Array_uint8*)field);
            return 0;

        case SINT8_ARRAY:
            new(_buffer) Array_sint8(*(Array_sint8*)field);
            return 0;

        case UINT16_ARRAY:
            new(_buffer) Array_uint16(*(Array_uint16*)field);
            return 0;

        case SINT16_ARRAY:
            new(_buffer) Array_sint16(*(Array_sint16*)field);
            return 0;

        case UINT32_ARRAY:
            new(_buffer) Array_uint32(*(Array_uint32*)field);
            return 0;

        case SINT32_ARRAY:
            new(_buffer) Array_sint32(*(Array_sint32*)field);
            return 0;

        case UINT64_ARRAY:
            new(_buffer) Array_uint64(*(Array_uint64*)field);
            return 0;

        case SINT64_ARRAY:
            new(_buffer) Array_sint64(*(Array_sint64*)field);
            return 0;

        case REAL32_ARRAY:
            new(_buffer) Array_real32(*(Array_real32*)field);
            return 0;

        case REAL64_ARRAY:
            new(_buffer) Array_real64(*(Array_real64*)field);
            return 0;

        case CHAR16_ARRAY:
            new(_buffer) Array_char16(*(Array_char16*)field);
            return 0;

        case STRING_ARRAY:
            new(_buffer) Array_String(*(Array_String*)field);
            return 0;

        case DATETIME_ARRAY:
            new(_buffer) Array_Datetime(*(Array_Datetime*)field);
            return 0;

        case INSTANCE_ARRAY:
        {
            const Array_Instance& a = *((const Array_Instance*)field);
            new(_buffer) Array_Instance(a);

            for (size_t i = 0; i < a.size(); i++)
                ref(a[i]);

            return 0;
        }
    }

    // Unreachable!
    return 0;
}

static const char* const _scalar_names[] =
{
    "boolean",
    "uint8",
    "sint8",
    "uint16",
    "sint16",
    "uint32",
    "sint32",
    "uint64",
    "sint64",
    "real32",
    "real64",
    "char16",
    "string",
    "datetime",
    "instance",
};

static const char* const _array_names[] =
{
    "boolean_array",
    "uint8_array",
    "sint8_array",
    "uint16_array",
    "sint16_array",
    "uint32_array",
    "sint32_array",
    "uint64_array",
    "sint64_array",
    "real32_array",
    "real64_array",
    "char16_array",
    "string_array",
    "datetime_array",
    "instance_array",
};

const char* name_of(Value::Type type)
{
    if (type == Value::NONE)
        return "none";

    if (type & 0x80)
        return _array_names[~0x80 & type];
    else
        return _scalar_names[type];
}

CIMPLE_NAMESPACE_END
