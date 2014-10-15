/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include <cimple/Meta_Class.h>
#include <cimple/Property.h>
#include "Facade.h"

CIMPLE_NAMESPACE_BEGIN

#ifdef CIMPLE_USE_FACADE

static uint8* _set_scalar(
    Instance* instance, 
    Type type,
    const char* name, 
    bool null)
{
    const Meta_Property* mp = find_property(instance->meta_class, name);

    if (!mp || mp->subscript || mp->type != type)
	return 0;

    uint8* field = (uint8*)instance + mp->offset;
    *((uint8*)field + type_size[type]) = null ? 1 : 0;

    return field;
}

int _set_scalar_raw(
    Instance* instance,
    Type type,
    const char* name, 
    const void* value,
    bool null)
{
    uint8* field = _set_scalar(instance, type, name, null);

    if (field)
    {
	memcpy(field, value, type_size[type]);
	return 0;
    }

    return -1;
}

static const uint8* _get_scalar(
    const Instance* instance, 
    Type type,
    const char* name, 
    bool& null)
{
    const Meta_Property* mp = find_property(instance->meta_class, name);

    if (!mp || mp->subscript || mp->type != type)
	return 0;

    const uint8* field = (uint8*)instance + mp->offset;
    null = *((const uint8*)field + type_size[type]);
    return field;
}

int _get_scalar_raw(
    const Instance* instance,
    Type type,
    const char* name, 
    void* value,
    bool& null)
{
    const uint8* field = _get_scalar(instance, type, name, null);

    if (field)
    {
	memcpy(value, field, type_size[type]);
	return 0;
    }

    return -1;
}

int Facade::_set_array(
    Type type,
    const char* name, 
    const Array_Base& value,
    bool null)
{
    const Meta_Property* mp = find_property(_instance->meta_class, name);

    if (!mp || mp->subscript == 0 || mp->type != type)
	return -1;

    uint8* field = (uint8*)_instance + mp->offset;
    *((uint8*)field + sizeof(Array_Base)) = null ? 1 : 0;
    *((Array_Base*)field) = value;

    return 0;
}

int Facade::_get_array(
    Type type,
    const char* name, 
    Array_Base& value,
    bool& null)
{
    const Meta_Property* mp = find_property(_instance->meta_class, name);

    if (!mp || mp->subscript == 0 || mp->type != type)
	return -1;

    const uint8* field = (uint8*)_instance + mp->offset;
    null = *((const uint8*)field + type_size[type]);
    value = *((Array_Base*)field);

    return 0;
}

Facade::Facade(Instance* instance) : _instance(instance)
{
}

Facade::~Facade()
{
    if (_instance)
	cimple::destroy(_instance);
}

Instance* Facade::steal()
{
    Instance* tmp = _instance;
    _instance = 0;
    return tmp;
}

int Facade::set_null(const char* name, bool null)
{
    const Meta_Property* mp = find_property(_instance->meta_class, name);

    if (!mp)
	return 0;

    null_of(mp, (uint8*)_instance + mp->offset) = null;

    return 0;
}

void Facade::print() const
{
    cimple::print(_instance);
}

int Facade::set_boolean(const char* name, boolean value, bool null)
{
    return _set_scalar_raw(_instance, BOOLEAN, name, &value, null);
}

int Facade::set_uint8(const char* name, uint8 value, bool null)
{
    return _set_scalar_raw(_instance, UINT8, name, &value, null);
}

int Facade::set_sint8(const char* name, sint8 value, bool null)
{
    return _set_scalar_raw(_instance, SINT8, name, &value, null);
}

int Facade::set_uint16(const char* name, uint16 value, bool null)
{
    return _set_scalar_raw(_instance, UINT16, name, &value, null);
}

int Facade::set_sint16(const char* name, sint16 value, bool null)
{
    return _set_scalar_raw(_instance, SINT16, name, &value, null);
}

int Facade::set_uint32(const char* name, uint32 value, bool null)
{
    return _set_scalar_raw(_instance, UINT32, name, &value, null);
}

int Facade::set_sint32(const char* name, sint32 value, bool null)
{
    return _set_scalar_raw(_instance, SINT32, name, &value, null);
}

int Facade::set_uint64(const char* name, uint64 value, bool null)
{
    return _set_scalar_raw(_instance, UINT64, name, &value, null);
}

int Facade::set_sint64(const char* name, sint64 value, bool null)
{
    return _set_scalar_raw(_instance, SINT64, name, &value, null);
}

int Facade::set_real32(const char* name, real32 value, bool null)
{
    return _set_scalar_raw(_instance, REAL32, name, &value, null);
}

int Facade::set_real64(const char* name, real64 value, bool null)
{
    return _set_scalar_raw(_instance, REAL64, name, &value, null);
}

int Facade::set_char16(const char* name, char16 value, bool null)
{
    return _set_scalar_raw(_instance, CHAR16, name, &value, null);
}

int Facade::set_string(const char* name, const String& value, bool null)
{
    uint8* field = _set_scalar(_instance, STRING, name, null);

    if (field)
    {
	*((String*)field) = value;
	return 0;
    }

    return -1;
}

int Facade::set_Datetime(const char* name, const Datetime& value, bool null)
{
    return _set_scalar_raw(_instance, DATETIME, name, &value, null);
}

int Facade::set_ref(const char* name, Instance* ref)
{
    const Meta_Reference* mr = find_reference(_instance->meta_class, name);

    if (mr)
    {
	// ATTN: change Meta_Reference so that it contains a meta-class
	// so that we can check to see if the ref is derived from it.
	// Otherwise we have no type-checking whatsoever.

	Instance* old_ref = *((Instance**)((uint8*)_instance + mr->offset));

	if (old_ref)
	    destroy(old_ref);

	*((Instance**)((uint8*)_instance + mr->offset)) = ref;

	return 0;
    }

    return -1;
}

int Facade::set_boolean_array(
    const char* name, const Array<boolean>& value, bool null)
{
    return _set_array(BOOLEAN, name, value, null);
}

int Facade::set_uint8_array(
    const char* name, const Array<uint8>& value, bool null)
{
    return _set_array(UINT8, name, value, null);
}

int Facade::set_sint8_array(
    const char* name, const Array<sint8>& value, bool null)
{
    return _set_array(SINT8, name, value, null);
}

int Facade::set_uint16_array(
    const char* name, const Array<uint16>& value, bool null)
{
    return _set_array(UINT16, name, value, null);
}

int Facade::set_sint16_array(
    const char* name, const Array<sint16>& value, bool null)
{
    return _set_array(SINT16, name, value, null);
}

int Facade::set_uint32_array(
    const char* name, const Array<uint32>& value, bool null)
{
    return _set_array(UINT32, name, value, null);
}

int Facade::set_sint32_array(
    const char* name, const Array<sint32>& value, bool null)
{
    return _set_array(SINT32, name, value, null);
}

int Facade::set_uint64_array(
    const char* name, const Array<uint64>& value, bool null)
{
    return _set_array(UINT64, name, value, null);
}

int Facade::set_sint64_array(
    const char* name, const Array<sint64>& value, bool null)
{
    return _set_array(SINT64, name, value, null);
}

int Facade::set_real32_array(
    const char* name, const Array<real32>& value, bool null)
{
    return _set_array(REAL32, name, value, null);
}

int Facade::set_real64_array(
    const char* name, const Array<real64>& value, bool null)
{
    return _set_array(REAL64, name, value, null);
}

int Facade::set_char16_array(
    const char* name, const Array<char16>& value, bool null)
{
    return _set_array(CHAR16, name, value, null);
}

int Facade::set_string_array(
    const char* name, const Array<String>& value, bool null)
{
    return _set_array(STRING, name, value, null);
}

int Facade::set_Datetime_array(
    const char* name, const Array<Datetime>& value, bool null)
{
    return _set_array(DATETIME, name, value, null);
}

int Facade::get_boolean(const char* name, boolean& value, bool& null)
{
    return _get_scalar_raw(_instance, BOOLEAN, name, &value, null);
}

int Facade::get_uint8(const char* name, uint8& value, bool& null)
{
    return _get_scalar_raw(_instance, UINT8, name, &value, null);
}

int Facade::get_sint8(const char* name, sint8& value, bool& null)
{
    return _get_scalar_raw(_instance, SINT8, name, &value, null);
}

int Facade::get_uint16(const char* name, uint16& value, bool& null)
{
    return _get_scalar_raw(_instance, UINT16, name, &value, null);
}

int Facade::get_sint16(const char* name, sint16& value, bool& null)
{
    return _get_scalar_raw(_instance, SINT16, name, &value, null);
}

int Facade::get_uint32(const char* name, uint32& value, bool& null)
{
    return _get_scalar_raw(_instance, UINT32, name, &value, null);
}

int Facade::get_sint32(const char* name, sint32& value, bool& null)
{
    return _get_scalar_raw(_instance, SINT32, name, &value, null);
}

int Facade::get_uint64(const char* name, uint64& value, bool& null)
{
    return _get_scalar_raw(_instance, UINT64, name, &value, null);
}

int Facade::get_sint64(const char* name, sint64& value, bool& null)
{
    return _get_scalar_raw(_instance, SINT64, name, &value, null);
}

int Facade::get_real32(const char* name, real32& value, bool& null)
{
    return _get_scalar_raw(_instance, REAL32, name, &value, null);
}

int Facade::get_real64(const char* name, real64& value, bool& null)
{
    return _get_scalar_raw(_instance, REAL64, name, &value, null);
}

int Facade::get_char16(const char* name, char16& value, bool& null)
{
    return _get_scalar_raw(_instance, CHAR16, name, &value, null);
}

int Facade::get_string(const char* name, String& value, bool& null)
{
    const void* field = _get_scalar(_instance, STRING, name, null);

    if (field)
    {
	value = *((String*)field);
	return 0;
    }

    return -1;
}

int Facade::get_Datetime(const char* name, Datetime& value, bool& null)
{
    return _get_scalar_raw(_instance, DATETIME, name, &value, null);
}

int Facade::get_ref(const char* name, Instance*& ref)
{
    const Meta_Reference* mr = find_reference(_instance->meta_class, name);

    if (mr)
    {
	ref = *((Instance**)((uint8*)_instance + mr->offset));
	return 0;
    }

    return -1;
}

int Facade::get_boolean_array(
    const char* name, Array<boolean>& value, bool& null)
{
    return _get_array(BOOLEAN, name, value, null);
}

int Facade::get_uint8_array(
    const char* name, Array<uint8>& value, bool& null)
{
    return _get_array(UINT8, name, value, null);
}

int Facade::get_sint8_array(
    const char* name, Array<sint8>& value, bool& null)
{
    return _get_array(SINT8, name, value, null);
}

int Facade::get_uint16_array(
    const char* name, Array<uint16>& value, bool& null)
{
    return _get_array(UINT16, name, value, null);
}

int Facade::get_sint16_array(
    const char* name, Array<sint16>& value, bool& null)
{
    return _get_array(SINT16, name, value, null);
}

int Facade::get_uint32_array(
    const char* name, Array<uint32>& value, bool& null)
{
    return _get_array(UINT32, name, value, null);
}

int Facade::get_sint32_array(
    const char* name, Array<sint32>& value, bool& null)
{
    return _get_array(SINT32, name, value, null);
}

int Facade::get_uint64_array(
    const char* name, Array<uint64>& value, bool& null)
{
    return _get_array(UINT64, name, value, null);
}

int Facade::get_sint64_array(
    const char* name, Array<sint64>& value, bool& null)
{
    return _get_array(SINT64, name, value, null);
}

int Facade::get_real32_array(
    const char* name, Array<real32>& value, bool& null)
{
    return _get_array(REAL32, name, value, null);
}

int Facade::get_real64_array(
    const char* name, Array<real64>& value, bool& null)
{
    return _get_array(REAL64, name, value, null);
}

int Facade::get_char16_array(
    const char* name, Array<char16>& value, bool& null)
{
    return _get_array(CHAR16, name, value, null);
}

int Facade::get_string_array(
    const char* name, Array<String>& value, bool& null)
{
    return _get_array(STRING, name, value, null);
}

int Facade::get_Datetime_array(
    const char* name, Array<Datetime>& value, bool& null)
{
    return _get_array(DATETIME, name, value, null);
}

#endif /* CIMPLE_USE_FACADE */

CIMPLE_NAMESPACE_END
