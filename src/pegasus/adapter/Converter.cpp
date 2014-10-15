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

#include <cimple/config.h>
#include <cassert>
#include <Pegasus/Common/XmlReader.h>
#include <cimple/Error.h>
#include "Converter.h"
#include "CStr.h"

CIMPLE_NAMESPACE_BEGIN

//------------------------------------------------------------------------------
//
// _to_pegasus_scalar()
//
//     Convert a CIMPLE property to a Pegasus value.
//
//------------------------------------------------------------------------------

static void _to_pegasus_scalar(
    const Meta_Property* mp,
    const void* field, 
    Pegasus::CIMValue& value)
{
    CIMPLE_ASSERT(mp != 0);
    CIMPLE_ASSERT(mp->subscript == 0);
    CIMPLE_ASSERT(field != 0);

    if (null_of(mp, field))
    {
	const Pegasus::Boolean is_array = false;
	value.setNullValue(Pegasus::CIMType(mp->type), is_array);
	return;
    }

    switch (Type(mp->type))
    {
	case BOOLEAN:
	    value.set(*((boolean*)field));
            break;

	case UINT8:
	    value.set(*((uint8*)field));
            break;

	case SINT8:
	    value.set(*((sint8*)field));
            break;

	case UINT16:
	    value.set(*((uint16*)field));
            break;

	case SINT16:
	    value.set(*((sint16*)field));
            break;

	case UINT32:
	    value.set(*((uint32*)field));
            break;

	case SINT32:
	    value.set(*((sint32*)field));
            break;

	case UINT64:
	    value.set(*((uint64*)field));
            break;

	case SINT64:
	    value.set(*((sint64*)field));
            break;

	case REAL32:
	    value.set(*((real32*)field));
            break;

	case REAL64:
	    value.set(*((real64*)field));
            break;

	case CHAR16:
	    value.set(Pegasus::Char16(*((char16*)field)));
            break;

	case STRING:
	    value.set(Pegasus::String((*((String*)field)).c_str()));
            break;

	case DATETIME:
	{
	    char buffer[Datetime::BUFFER_SIZE];
	    ((const Datetime*)field)->ascii(buffer);
	    value.set(Pegasus::CIMDateTime(buffer));
            break;
	}
    }
}

//------------------------------------------------------------------------------
//
// _to_pegasus_array_helper()
//
//     Helps convert a CIMPLE array to a Pegasus array.
//
//------------------------------------------------------------------------------

template<class CT, class PT>
struct _to_pegasus_array_helper
{
    static void func(
	const Meta_Property* mp,
	const void* field, 
	Pegasus::CIMValue& value)
    {
	const Array<CT>& tmp = *((const Array<CT>*)field);
	Pegasus::Array<PT> array((const PT*)tmp.data(), tmp.size());
	value.set(array);
    }
};

//------------------------------------------------------------------------------
//
// _to_pegasus_array()
//
//     Converts a CIMPLE array to a Pegasus array.
//
//------------------------------------------------------------------------------

static void _to_pegasus_array(
    const Meta_Property* mp,
    const void* f, 
    Pegasus::CIMValue& v)
{
    CIMPLE_ASSERT(mp != 0);
    CIMPLE_ASSERT(mp->subscript != 0);
    CIMPLE_ASSERT(f != 0);

    CIMPLE_ASSERT(mp->subscript != 0);

    if (null_of(mp, f))
    {
	const Pegasus::Boolean is_array = true;
	const Pegasus::Uint32 array_size = 
	    (mp->subscript > 0) ? mp->subscript : 0;
	v.setNullValue(Pegasus::CIMType(mp->type), is_array, array_size);
	return;
    }

    switch (Type(mp->type))
    {
	case BOOLEAN:
	    _to_pegasus_array_helper<boolean, Pegasus::Boolean>::func(mp, f, v);
            break;

	case UINT8:
	    _to_pegasus_array_helper<uint8, Pegasus::Uint8>::func(mp, f, v);
            break;

	case SINT8:
	    _to_pegasus_array_helper<sint8, Pegasus::Sint8>::func(mp,f,v);
            break;

	case UINT16:
	    _to_pegasus_array_helper<uint16, Pegasus::Uint16>::func(mp, f, v);
            break;

	case SINT16:
	    _to_pegasus_array_helper<sint16, Pegasus::Sint16>::func(mp, f, v);
            break;

	case UINT32:
	    _to_pegasus_array_helper<uint32, Pegasus::Uint32>::func(mp, f, v);
            break;

	case SINT32:
	    _to_pegasus_array_helper<sint32, Pegasus::Sint32>::func(mp, f, v);
            break;

	case UINT64:
	    _to_pegasus_array_helper<uint64, Pegasus::Uint64>::func(mp, f, v);
            break;

	case SINT64:
	    _to_pegasus_array_helper<sint64, Pegasus::Sint64>::func(mp, f, v);
            break;

	case REAL32:
	    _to_pegasus_array_helper<real32, Pegasus::Real32>::func(mp, f, v);
            break;

	case REAL64:
	    _to_pegasus_array_helper<real64, Pegasus::Real64>::func(mp, f, v);
            break;

	case CHAR16:
	    _to_pegasus_array_helper<char16, Pegasus::Char16>::func(mp, f, v);
            break;

	case STRING:
	{
	    Array_String& tmp = *((Array_String*)f);

	    Pegasus::Array<Pegasus::String> array;
	    array.reserveCapacity(tmp.size());

	    for (size_t i = 0; i < tmp.size(); i++)
		array.append(tmp[i].c_str());

	    v.set(array);
            break;
	}

	case DATETIME:
	{
	    Array<Datetime>& tmp = *((Array<Datetime>*)f);

	    Pegasus::Array<Pegasus::CIMDateTime> array;
	    array.reserveCapacity(tmp.size());

	    for (size_t i = 0; i < tmp.size(); i++)
	    {
		char buffer[Datetime::BUFFER_SIZE];
		tmp[i].ascii(buffer);
		array.append(Pegasus::CIMDateTime(buffer));
	    }

	    v.set(array);
            break;
	}
    }
}

//------------------------------------------------------------------------------
//
// _to_pegasus_value()
//
//     Converts a CIMPLE property to a Pegasus value:
//
//------------------------------------------------------------------------------

static int _to_pegasus_value(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* ci, 
    const Meta_Feature* mf, 
    Pegasus::CIMValue& value)
{
    CIMPLE_ASSERT(ci != 0);
    CIMPLE_ASSERT(ci->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(mf != 0);

    if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
    {
	const Meta_Reference* mr = (const Meta_Reference*)mf;
	const Instance* ref = reference_of(ci, mr);

	// Skip null references:

	if (!ref)
	    return 0;

	Pegasus::CIMInstance pi;

	if (Converter::to_pegasus_instance(hn, ns, ref, pi) != 0)
	    return -1;

	Pegasus::CIMObject po(pi);

	value.set(po);

	return 0;
    }
    else if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
	const Meta_Property* mp = (const Meta_Property*)mf;
	const void* prop = property_of(ci, mp);

	// Handle null properties:

	if (null_of(mp, prop))
	{
	    // It is an error for a key to be null:

	    if (mp->flags & CIMPLE_FLAG_KEY)
	    {
		CIMPLE_ERROR(("null key: %s", mp->name));
		return -1;
	    }

	    const bool is_array = mp->subscript != 0;
	    size_t array_size = 0;

	    if (is_array)
		array_size = mp->subscript == -1 ? 0 : mp->subscript;

	    value.setNullValue(Pegasus::CIMType(mp->type), is_array, array_size);
	    return 0;
	}

	if (mp->subscript == 0)
	    _to_pegasus_scalar(mp, prop, value);
	else
	    _to_pegasus_array(mp, prop, value);

	return 0;
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
	const Meta_Reference* mr = (const Meta_Reference*)mf;
	const Instance* ref = reference_of(ci, mr);

	// Skip null references:

	if (!ref)
	{
	    // It is an error for a key to be null:

	    if (mr->flags & CIMPLE_FLAG_KEY)
	    {
		CIMPLE_ERROR(("null key: %s", mr->name));
		return -1;
	    }

	    return 0;
	}

	Pegasus::CIMObjectPath op;

	if (Converter::to_pegasus_object_path(hn, ns, ref, op) != 0)
	    return -1;

	value.set(op);

	return 0;
    }
    else
    {
	CIMPLE_ERROR(("expected property or reference: %s", mf->name));
	return -1;
    }

    // Unreachable:
    return 0;
}

//------------------------------------------------------------------------------
//
// to_pegasus_instance()
//
//     Converts a CIMPLE instance to a Pegasus instance.
//
//------------------------------------------------------------------------------

int Converter::to_pegasus_instance(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* ci, 
    Pegasus::CIMInstance& pi)
{
    CIMPLE_ASSERT(ci != 0);
    CIMPLE_ASSERT(ci->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ci->meta_class;

    // Create Pegasus instance of the given class.

    pi = Pegasus::CIMInstance(mc->name);

    // Build the object path.

    Pegasus::CIMObjectPath object_path;

    if (to_pegasus_object_path(hn, ns, ci, object_path) != 0)
	return -1;

    pi.setPath(object_path);

    // Copy properties from CIMPLE to Pegasus instance.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];

	if (mf->flags & CIMPLE_FLAG_METHOD)
	    continue;

	Pegasus::CIMValue value;


	if (_to_pegasus_value(hn, ns, ci, mf, value) != 0)
	    return -1;

	try
	{
	    pi.addProperty(Pegasus::CIMProperty(mf->name, value));
	}
	catch(...)
	{
	    CIMPLE_ERROR(("addProperty() failed: %s", mf->name));
	    return -1;
	}
    }

    return 0;
}

//------------------------------------------------------------------------------
//
// _to_cimple_scalar()
//
//     Converts Pegasus scalar to a CIMPLE one.
//
//------------------------------------------------------------------------------

template<class PT, class CT>
struct _to_cimple_scalar
{
    static void func(
	const Pegasus::CIMValue& value,
	Instance* ci,
	char* field)
    {
	PT pt;
	value.get(pt);
	CT ct = pt;
	((Property<CT>*)field)->value = ct;
	((Property<CT>*)field)->null = value.isNull() ? 1 : 0;
    }
};

//------------------------------------------------------------------------------
//
// _to_cimple_array()
//
//     Converts a Pegasus array to a CIMPLE one.
//
//------------------------------------------------------------------------------

template<class PT, class CT>
struct _to_cimple_array
{
    static void func(
	const Pegasus::CIMValue& value,
	Instance* ci,
	char* field)
    {
	Pegasus::Array<PT> tmp;
	value.get(tmp);
	((Property< Array<CT> >*)field)->value.assign(
	    tmp.getData(), tmp.size());
	((Property< Array<CT> >*)field)->null = value.isNull() ? 1 : 0;
    }
};

//------------------------------------------------------------------------------
//
// _to_cimple_property()
//
//     Converts a Pegasus value to a CIMPLE one.
//
//------------------------------------------------------------------------------

static int _to_cimple_property(
    const Pegasus::CIMValue& v,
    Instance* ci,
    const Meta_Property* mp)
{
    CIMPLE_ASSERT(ci != 0);

    // Check type compatibility.

    if (v.getType() != mp->type)
    {
	CIMPLE_ERROR(("type mismatch"));
	return -1;
    }

    if (v.isArray() && mp->subscript == 0)
    {
	CIMPLE_ERROR(("array/scalar type mismatch"));
	return -1;
    }

    //  Set property value.

    char* f = (char*)ci + mp->offset;

    if (mp->subscript == 0)
    {
	switch (v.getType())
	{
	    case Pegasus::CIMTYPE_BOOLEAN:
		_to_cimple_scalar<Pegasus::Boolean, boolean>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT8:
		_to_cimple_scalar<Pegasus::Uint8, uint8>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT8:
		_to_cimple_scalar<Pegasus::Sint8, sint8>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT16:
		_to_cimple_scalar<Pegasus::Uint16, uint16>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT16:
		_to_cimple_scalar<Pegasus::Sint16, sint16>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT32:
		_to_cimple_scalar<Pegasus::Uint32, uint32>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT32:
		_to_cimple_scalar<Pegasus::Sint32, sint32>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT64:
		_to_cimple_scalar<Pegasus::Uint64, uint64>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT64:
		_to_cimple_scalar<Pegasus::Sint64, sint64>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_REAL32:
		_to_cimple_scalar<Pegasus::Real32, real32>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_REAL64:
		_to_cimple_scalar<Pegasus::Real64, real64>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_CHAR16:
		_to_cimple_scalar<Pegasus::Char16, char16>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_STRING:
	    {
		Pegasus::String str;
		v.get(str);
		(*((Property<String>*)f)).value = CStr(str);
		(*((Property<String>*)f)).null = v.isNull() ? 1 : 0;
		break;
	    }

	    case Pegasus::CIMTYPE_DATETIME:
	    {
		Pegasus::CIMDateTime dt;
		v.get(dt);
		(*((Property<Datetime>*)f)).value.set(CStr(dt.toString()));
		(*((Property<Datetime>*)f)).null = v.isNull() ? 1 : 0;
		break;
	    }

	    case Pegasus::CIMTYPE_REFERENCE:
	    case Pegasus::CIMTYPE_OBJECT:
		CIMPLE_ERROR(("unexpected condition"));
		return -1;
	}
    }
    else
    {
	switch (v.getType())
	{
	    case Pegasus::CIMTYPE_BOOLEAN:
		_to_cimple_array<Pegasus::Boolean, boolean>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT8:
		_to_cimple_array<Pegasus::Uint8, uint8>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT8:
		_to_cimple_array<Pegasus::Sint8, sint8>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT16:
		_to_cimple_array<Pegasus::Uint16, uint16>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT16:
		_to_cimple_array<Pegasus::Sint16, sint16>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT32:
		_to_cimple_array<Pegasus::Uint32, uint32>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT32:
		_to_cimple_array<Pegasus::Sint32, sint32>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_UINT64:
		_to_cimple_array<Pegasus::Uint64, uint64>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_SINT64:
		_to_cimple_array<Pegasus::Sint64, sint64>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_REAL32:
		_to_cimple_array<Pegasus::Real32, real32>::func(v, ci, f);

	    case Pegasus::CIMTYPE_REAL64:
		_to_cimple_array<Pegasus::Real64, real64>::func(v, ci, f);
		break;

	    case Pegasus::CIMTYPE_CHAR16:
	    {
		Pegasus::Array<Pegasus::Char16> tmp;
		v.get(tmp);

		((Property< Array<char16> >*)f)->value.assign(
		    (char16*)tmp.getData(), tmp.size());

		((Property< Array<char16> >*)f)->null = 0;
		break;
	    }

	    case Pegasus::CIMTYPE_STRING:
	    {
		Pegasus::Array<Pegasus::String> tmp;
		v.get(tmp);

		Array<String> a;

		for (size_t i = 0; i < tmp.size(); i++)
		    a.append(String(CStr(tmp[i])));

		(*((Property<Array_String>*)f)).value = a;
		(*((Property<Array_String>*)f)).null = v.isNull() ? 1 : 0;
		break;
	    }

	    case Pegasus::CIMTYPE_DATETIME:
	    {
		Pegasus::Array<Pegasus::CIMDateTime> tmp;
		v.get(tmp);

		Array<Datetime> a;

		for (size_t i = 0; i < tmp.size(); i++)
		{
		    Datetime dt;
		    dt.set(CStr(tmp[i].toString()));
		    a.append(dt);
		}

		(*((Property<Array_Datetime>*)f)).value = a;
		(*((Property<Array_Datetime>*)f)).null = 0;
		break;
	    }

	    case Pegasus::CIMTYPE_REFERENCE:
	    case Pegasus::CIMTYPE_OBJECT:
		CIMPLE_ERROR(("unexpected condition"));
		return -1;
	}
    }

    return 0;
}

//------------------------------------------------------------------------------
//
// _to_cimple_instance()
//
//     This function converts an array of name/value pairs into a CIMPLE 
//     instance. This function is called to create the following kinds of
//     instances:
//
//         1. Ordinary instances
//         2. Method instances
//         3. Reference instances
//
//------------------------------------------------------------------------------

typedef const Pegasus::Array<Pegasus::CIMParamValue> Params;
typedef const Pegasus::String (*Get_Name_Proc)(const void* data, size_t index);
typedef const Pegasus::CIMValue (*Get_Value_Proc)(
    const void* data, size_t index, Pegasus::CIMType expected_type);

static const Pegasus::String _bindings_get_name(const void* data, size_t index)
{
    Key_Bindings* bindings = (Key_Bindings*)data;
    return (*bindings)[index].getName().getString();
}

static const Pegasus::CIMValue _bindings_get_value(
    const void* data, 
    size_t index, 
    Pegasus::CIMType expected_type)
{
    Key_Bindings& bindings = *((Key_Bindings*)data);

    try
    {
	CStr cstr(bindings[index].getValue());
	return Pegasus::XmlReader::stringToValue(0, cstr, expected_type);
    }
    catch (...)
    {
	return Pegasus::CIMValue();
    }
}

static const Pegasus::String _instance_get_name(const void* data, size_t index)
{
    Pegasus::CIMInstance* instance = (Pegasus::CIMInstance*)data;
    return (*instance).getProperty(index).getName().getString();
}

static const Pegasus::CIMValue _instance_get_value(
    const void* data, 
    size_t index, 
    Pegasus::CIMType expected_type)
{
    Pegasus::CIMInstance* instance = (Pegasus::CIMInstance*)data;
    return (*instance).getProperty(index).getValue();
}

static const Pegasus::String _params_get_name(const void* data, size_t index)
{
    Params* params = (Params*)data;
    return (*params)[index].getParameterName();
}

static const Pegasus::CIMValue _params_get_value(
    const void* data, 
    size_t index,
    Pegasus::CIMType expected_type)
{
    Params* params = (Params*)data;
    return (*params)[index].getValue();
}

static Instance* _make_cimple_instance(
    const void* data,
    size_t count,
    Get_Name_Proc get_name_proc,
    Get_Value_Proc get_value_proc,
    const Meta_Class* mc,
    bool keys_only)
{
    // Create a new instance:

    Instance* instance = create(mc);

    // Nullify the properties:

    nullify_properties(instance);

    // Convert each of the name-value pairs:

    for (size_t i = 0; i < count; i++)
    {
	CStr name(get_name_proc(data, i));

	// Find the corresponding CIMPLE feature:

	const Meta_Feature* mf = find_feature(mc, name);

	if (!mf)
	{
	    CIMPLE_ERROR(("no such feature: %s", (const char*)name));
	    destroy(instance);
	    return 0;
	}

	// Skip non-keys if so requested.

	if (keys_only && !(mf->flags & CIMPLE_FLAG_KEY))
	    continue;

	// Initialize the feature:

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (const Meta_Property*)mf;

	    const Pegasus::CIMValue value = get_value_proc(
		data, i, Pegasus::CIMType(mp->type));

	    if (_to_cimple_property(value, instance, mp) != 0)
	    {
		CIMPLE_ERROR(("type mismatch on %s", mp->name));
		destroy(instance);
		return 0;
	    }
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (const Meta_Reference*)mf;

	    const Pegasus::CIMValue value = get_value_proc(
		data, i, Pegasus::CIMTYPE_REFERENCE);

	    if (Converter::_to_cimple_ref(value, instance, mr) != 0)
	    {
		CIMPLE_ERROR(("failed to set reference: %s", mr->name));
		destroy(instance);
		return 0;
	    }
	}
	else
	{
	    CIMPLE_ERROR(("feature not found: %s\n", mf->name));
	    destroy(instance);
	    return 0;
	}
    }

    return instance;
}

//------------------------------------------------------------------------------
//
// _to_cimple_ref()
//
//     Converts a Pegasus value to a CIMPLE reference.
//
//------------------------------------------------------------------------------

int Converter::_to_cimple_ref(
    const Pegasus::CIMValue& v,
    Instance* ci,
    const Meta_Reference* mr)
{
    Instance*& ref = reference_of(ci, mr);

    if (ref != 0)
    {
	CIMPLE_ASSERT(ref->magic == CIMPLE_INSTANCE_MAGIC);
	destroy(ref);
	ref = 0;
	CIMPLE_ASSERT(0);
    }

    // Get the object path object:

    Pegasus::CIMObjectPath op;

    try
    {
	v.get(op);
    }
    catch (...)
    {
	CIMPLE_ERROR(("unexpected failure"));
	return -1;
    }

    // Check for same number of keys:

    const Pegasus::Array<Pegasus::CIMKeyBinding>& bindings = op.getKeyBindings();

    if (bindings.size() != mr->meta_class->num_keys)
    {
	CIMPLE_ERROR(("key count mismatch"));
	return -1;
    }

    // Create the reference instance:

    ref = _make_cimple_instance(
	&bindings, 
	bindings.size(),
	_bindings_get_name,
	_bindings_get_value,
	mr->meta_class, 
	true); 

    if (!ref)
	return -1;

    return 0;
}

//------------------------------------------------------------------------------
//
// to_cimple_instance()
//
//     Converts a Pegasus instance to a CIMPLE one.
//
//------------------------------------------------------------------------------

int Converter::to_cimple_instance(
    const Pegasus::CIMInstance& pi,
    const Meta_Class* mc,
    Instance*& ci)
{
    ci = _make_cimple_instance(&pi, pi.getPropertyCount(),
	_instance_get_name, _instance_get_value, mc, false);

    return ci ? 0 : -1;
}

//------------------------------------------------------------------------------
//
// to_cimple_key()
//
//     Converts a Pegasus object path to a CIMPLE instance, initializing only
//     the key fields.
//
//------------------------------------------------------------------------------

int Converter::to_cimple_key(
    const Key_Bindings& bindings,
    const Meta_Class* mc,
    Instance*& ci)
{
    ci = _make_cimple_instance(&bindings, bindings.size(),
	_bindings_get_name, _bindings_get_value, mc, false);

    if (bindings.size() != mc->num_keys)
    {
	CIMPLE_ERROR(("key count mismatch"));
	return -1;
    }

    return ci ? 0 : -1;
}

//------------------------------------------------------------------------------
//
// to_pegasus_object_path()
//
//     Converts a cimple key coponents of a CIMPLE instance to a Pegasus object 
//     path. Pegasus object paths have four elements: 
//
//         - host
//         - namespace
//         - class name
//         - key bindings.
//
//------------------------------------------------------------------------------

int Converter::to_pegasus_object_path(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* ci,
    Pegasus::CIMObjectPath& object_path)
{
    CIMPLE_ASSERT(ci->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ci->meta_class;

    // Build up key bindings from this CIMPLE instance.

    Pegasus::Array<Pegasus::CIMKeyBinding> bindings;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];

	// Ignore non-keys features:

	if (!(mf->flags & CIMPLE_FLAG_KEY))
	    continue;

	// Ignore methods:

	if (mf->flags & CIMPLE_FLAG_METHOD)
	    continue;

	// Convert feature to key binding:

	Pegasus::CIMValue value;

	if (_to_pegasus_value(hn, ns, ci, mf, value) != 0)
	    return -1;

	bindings.append(Pegasus::CIMKeyBinding(mf->name, value));
    }

    // Initialize the object path:

    object_path.set(hn, ns, Pegasus::CIMName(mc->name), bindings);

    return 0;
}

//------------------------------------------------------------------------------
//
// de_nullify_properties()
//
//     Validates (makes non-null) all properties of a CIMPLE instance which 
//     are mentioned in the property list.
//
//------------------------------------------------------------------------------

int Converter::de_nullify_properties(
    const Pegasus::CIMPropertyList& pl,
    Instance* ci)
{
    // If the property list is null, define all the properties (the requestor
    // wants them all).

    if (pl.isNull())
    {
	cimple::de_nullify_properties(ci);
	return 0;
    }

    // Nullify all properties.

    nullify_non_keys(ci);

    // Denullify requested properties:

    const Meta_Class* mc = ci->meta_class;

    for (size_t i = 0; i < pl.size(); i++)
    {
	// Do not denullify keys.

	CStr name(pl[i]);

	const Meta_Property* mp = (Meta_Property*)find_feature(mc, name);

	if (!mp)
	{
	    CIMPLE_ERROR(("no such property: %s", name.c_str()));
	    return -1;
	}

	if (mp->flags & CIMPLE_FLAG_KEY)
	    continue;

	if (mp->flags & CIMPLE_FLAG_PROPERTY)
	    null_of(mp, (char*)ci + mp->offset) = 0;
    }

    return 0;
}

//------------------------------------------------------------------------------
//
// to_cimple_method()
//
//     Convert the Pegasus method name and input parameter list into a CIMPLE
//     method object.
//
//------------------------------------------------------------------------------

int Converter::to_cimple_method(
    const char* meth_name,
    const Pegasus::Array<Pegasus::CIMParamValue>& in_params,
    const Meta_Class* mc,
    Instance*& meth)
{
    meth = 0;

    // First look up the method:

    const Meta_Method* mm = find_method(mc, meth_name);

    if (!mm)
    {
	CIMPLE_ERROR(("no such method: %s", meth_name));
	return -1;
    }

    // Create new method instance:

    meth = _make_cimple_instance(&in_params, in_params.size(),
	_params_get_name, _params_get_value, (Meta_Class*)mm, false);

    if (!meth)
	return -1;

    // Create reference output parameters.

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
	const Meta_Feature* mf = mm->meta_features[i];

	if (mf->flags & CIMPLE_FLAG_REFERENCE && mf->flags & CIMPLE_FLAG_OUT)
	{
	    const Meta_Reference* mr = (const Meta_Reference*)mf;
	    Instance*& ref = reference_of(meth, mr);

	    if (!ref)
		ref = create(mr->meta_class);
	}
    }

    // Iterate the meta-method looking for missing input parameters:

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
	const Meta_Feature* mf = mm->meta_features[i];

	if (mf->flags & CIMPLE_FLAG_PROPERTY && mf->flags & CIMPLE_FLAG_IN)
	{
	    const Meta_Property* mp = (const Meta_Property*)mf;
	    bool found = false;

	    const Pegasus::CIMParamValue* data = in_params.getData();

	    for (Pegasus::Uint32 j = 0, n = in_params.size(); j < n; j++)
	    {
		CStr param_name(data[j].getParameterName());

		if (strcasecmp(param_name, mp->name) == 0)
		{
		    found = true;
		    break;
		}
	    }

	    if (!found)
	    {
		CIMPLE_ERROR(("missing input parameter: %s", mp->name));
		return -1;
	    }
	}
    }

    return 0;
}

//------------------------------------------------------------------------------
//
// to_cimple_method()
//
//     Convert the CIMPLE method object into a Pegasus output parameter list
//     and return value.
//
//------------------------------------------------------------------------------

int Converter::to_pegasus_method(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* meth,
    Pegasus::Array<Pegasus::CIMParamValue>& out_params,
    Pegasus::CIMValue& return_value)
{
    CIMPLE_ASSERT(meth != 0);

    out_params.clear();

    // Iterate the meta-method to initialize out_params and return_value.

    const Meta_Method* mm = (const Meta_Method*)meth->meta_class;
    CIMPLE_ASSERT(mm->flags & CIMPLE_FLAG_METHOD);

    bool found_return_value = false;

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
	const Meta_Feature* mf = mm->meta_features[i];

	// Convert to Pegasus value.

	if (mf->flags & CIMPLE_FLAG_OUT)
	{
	    if (strcasecmp(mf->name, "return_value") == 0)
	    {
		found_return_value = true;
		_to_pegasus_value(hn, ns, meth, mf, return_value);
	    }
	    else
	    {
		Pegasus::CIMValue value;
		_to_pegasus_value(hn, ns, meth, mf, value);
		out_params.append(Pegasus::CIMParamValue(mf->name, value));
	    }
	}
    }

    if (!found_return_value)
    {
	CIMPLE_ERROR(("return value missing"));
	return -1;
    }

    return 0;
}

CIMPLE_NAMESPACE_END
