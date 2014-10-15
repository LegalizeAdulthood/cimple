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
#include <cimple/cimple.h>
#include <cassert>
#include <cimple/Error.h>
#include "Converter.h"
#include "Str.h"
#include "Integer.h"

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
    P_CIMValue& value)
{
    CIMPLE_ASSERT(mp != 0);
    CIMPLE_ASSERT(mp->subscript == 0);
    CIMPLE_ASSERT(field != 0);

    if (null_of(mp, field))
    {
        const P_Boolean is_array = false;
        value.setNullValue(P_CIMType(mp->type), is_array);
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
            value.set(P_Char16(((char16*)field)->code()));
            break;

        case STRING:
            value.set(P_String((*((String*)field)).c_str()));
            break;

        case DATETIME:
        {
            char buffer[Datetime::BUFFER_SIZE];
            ((const Datetime*)field)->ascii(buffer);
            value.set(P_CIMDateTime(buffer));
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
        P_CIMValue& value)
    {
        const Array<CT>& tmp = *((const Array<CT>*)field);
        Pegasus::Array<PT> 
            array((const PT*)tmp.data(), P_Uint32(tmp.size()));
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
    P_CIMValue& v)
{
    CIMPLE_ASSERT(mp != 0);
    CIMPLE_ASSERT(mp->subscript != 0);
    CIMPLE_ASSERT(f != 0);

    CIMPLE_ASSERT(mp->subscript != 0);

    if (null_of(mp, f))
    {
        const P_Boolean is_array = true;
        const P_Uint32 array_size = 
            (mp->subscript > 0) ? mp->subscript : 0;
        v.setNullValue(P_CIMType(mp->type), is_array, array_size);
        return;
    }

    switch (Type(mp->type))
    {
        case BOOLEAN:
            _to_pegasus_array_helper<boolean, P_Boolean>::func(mp, f, v);
            break;

        case UINT8:
            _to_pegasus_array_helper<uint8, P_Uint8>::func(mp, f, v);
            break;

        case SINT8:
            _to_pegasus_array_helper<sint8, P_Sint8>::func(mp,f,v);
            break;

        case UINT16:
            _to_pegasus_array_helper<uint16, P_Uint16>::func(mp, f, v);
            break;

        case SINT16:
            _to_pegasus_array_helper<sint16, P_Sint16>::func(mp, f, v);
            break;

        case UINT32:
            _to_pegasus_array_helper<uint32, P_Uint32>::func(mp, f, v);
            break;

        case SINT32:
            _to_pegasus_array_helper<sint32, P_Sint32>::func(mp, f, v);
            break;

        case UINT64:
            _to_pegasus_array_helper<uint64, P_Uint64>::func(mp, f, v);
            break;

        case SINT64:
            _to_pegasus_array_helper<sint64, P_Sint64>::func(mp, f, v);
            break;

        case REAL32:
            _to_pegasus_array_helper<real32, P_Real32>::func(mp, f, v);
            break;

        case REAL64:
            _to_pegasus_array_helper<real64, P_Real64>::func(mp, f, v);
            break;

        case CHAR16:
            _to_pegasus_array_helper<char16, P_Char16>::func(mp, f, v);
            break;

        case STRING:
        {
            Array_String& tmp = *((Array_String*)f);

            Pegasus::Array<P_String> array;
            array.reserveCapacity(P_Uint32(tmp.size()));

            for (size_t i = 0; i < tmp.size(); i++)
                array.append(tmp[i].c_str());

            v.set(array);
            break;
        }

        case DATETIME:
        {
            Array<Datetime>& tmp = *((Array<Datetime>*)f);

            Pegasus::Array<P_CIMDateTime> array;
            array.reserveCapacity(P_Uint32(tmp.size()));

            for (size_t i = 0; i < tmp.size(); i++)
            {
                char buffer[Datetime::BUFFER_SIZE];
                tmp[i].ascii(buffer);
                array.append(P_CIMDateTime(buffer));
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
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* ci, 
    const Meta_Feature* mf, 
    P_CIMValue& value)
{
    CIMPLE_ASSERT(ci != 0);
    CIMPLE_ASSERT(ci->__magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(mf != 0);

    if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
    {
        const Meta_Reference* mr = (const Meta_Reference*)mf;
        const Instance* ref = __ref_of(ci, mr);

        // Skip null references:

        if (!ref)
            return 0;

        P_CIMInstance pi;

        if (Converter::to_pegasus_instance(hn, ns, ref, pi) != 0)
            return -1;

        P_CIMObject po(pi);

        value.set(po);

        return 0;
    }
    else if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;
        const void* prop = __property_of(ci, mp);

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

            value.setNullValue(P_CIMType(mp->type), is_array, 
                P_Uint32(array_size));

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

        if (mr->subscript)
        {
            const Array_Ref& refs = __array_ref_of(ci, mr);
            Pegasus::Array<P_CIMObjectPath> cops;

            for (size_t i = 0; i < refs.size(); i++)
            {
                Instance* ref = refs[i];

                if (!ref)
                {
                    CIMPLE_ERROR(("provider extrinsic method failed to supply "
                    "a value for an output reference parameter: %s", mr->name));
                    return -1;
                }

                P_CIMObjectPath cop;

                if (Converter::to_pegasus_object_path(hn, ns, ref, cop) != 0)
                    return -1;

                cops.append(cop);
            }

            value.set(cops);
        }
        else
        {
            const Instance* ref = __ref_of(ci, mr);

            // Skip null references:

            if (!ref)
            {
                // It is an error for a key to be null:

                if (mr->flags & CIMPLE_FLAG_KEY)
                {
                    CIMPLE_ERROR(("null key: %s", mr->name));
                    return -1;
                }

                // User did not fill in ref output parameter from intrisic
                // method.

                CIMPLE_ERROR(("provider extrinsic method failed to supply a "
                    "value for an output reference parameter: %s", mr->name));

                return -1;
            }

            P_CIMObjectPath op;

            if (Converter::to_pegasus_object_path(hn, ns, ref, op) != 0)
                return -1;

            value.set(op);
        }

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
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* ci, 
    P_CIMInstance& pi)
{
    CIMPLE_ASSERT(ci != 0);
    CIMPLE_ASSERT(ci->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ci->meta_class;

    // Create Pegasus instance of the given class.

    pi = P_CIMInstance(mc->name);

    // Copy properties from CIMPLE to Pegasus instance and to object path.

    Pegasus::Array<P_CIMKeyBinding> bindings;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        if (mf->flags & CIMPLE_FLAG_METHOD)
            continue;

        // Create Pegasus value.

        P_CIMValue cv;

        if (_to_pegasus_value(hn, ns, ci, mf, cv) != 0)
            return -1;

        // Add key binding.

        if (mf->flags & CIMPLE_FLAG_KEY)
            bindings.append(P_CIMKeyBinding(mf->name, cv));

        // Add property to instance.

        try
        {
            pi.addProperty(P_CIMProperty(mf->name, cv));
        }
        catch(...)
        {
            CIMPLE_ERROR(("addProperty() failed: %s", mf->name));
            return -1;
        }
    }

    // Set the object path.

    pi.setPath(P_CIMObjectPath(hn, ns, mc->name, bindings));

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
        const P_CIMValue& value,
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

template<> 
struct _to_cimple_scalar<P_Char16, char16>
{
    typedef P_Char16 PT;
    typedef char16 CT;

    static void func(
        const P_CIMValue& value,
        Instance* ci,
        char* field)
    {
        PT pt;
        value.get(pt);
        CT ct = uint16(pt);
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
        const P_CIMValue& value,
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
    const P_CIMValue& v,
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
                _to_cimple_scalar<P_Boolean, boolean>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT8:
                _to_cimple_scalar<P_Uint8, uint8>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT8:
                _to_cimple_scalar<P_Sint8, sint8>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT16:
                _to_cimple_scalar<P_Uint16, uint16>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT16:
                _to_cimple_scalar<P_Sint16, sint16>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT32:
                _to_cimple_scalar<P_Uint32, uint32>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT32:
                _to_cimple_scalar<P_Sint32, sint32>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT64:
                _to_cimple_scalar<P_Uint64, uint64>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT64:
                _to_cimple_scalar<P_Sint64, sint64>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_REAL32:
                _to_cimple_scalar<P_Real32, real32>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_REAL64:
                _to_cimple_scalar<P_Real64, real64>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_CHAR16:
                _to_cimple_scalar<P_Char16, char16>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_STRING:
            {
                P_String str;
                v.get(str);
                (*((Property<String>*)f)).value = *Str(str);
                (*((Property<String>*)f)).null = v.isNull() ? 1 : 0;
                break;
            }

            case Pegasus::CIMTYPE_DATETIME:
            {
                P_CIMDateTime dt;
                v.get(dt);
                (*((Property<Datetime>*)f)).value.set(*Str(dt));
                (*((Property<Datetime>*)f)).null = v.isNull() ? 1 : 0;
                break;
            }

            case Pegasus::CIMTYPE_REFERENCE:
            case Pegasus::CIMTYPE_OBJECT:
            default:
                CIMPLE_ERROR(("3unexpected condition"));
                return -1;
        }
    }
    else
    {
        switch (v.getType())
        {
            case Pegasus::CIMTYPE_BOOLEAN:
                _to_cimple_array<P_Boolean, boolean>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT8:
                _to_cimple_array<P_Uint8, uint8>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT8:
                _to_cimple_array<P_Sint8, sint8>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT16:
                _to_cimple_array<P_Uint16, uint16>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT16:
                _to_cimple_array<P_Sint16, sint16>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT32:
                _to_cimple_array<P_Uint32, uint32>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT32:
                _to_cimple_array<P_Sint32, sint32>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_UINT64:
                _to_cimple_array<P_Uint64, uint64>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_SINT64:
                _to_cimple_array<P_Sint64, sint64>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_REAL32:
                _to_cimple_array<P_Real32, real32>::func(v, ci, f);

            case Pegasus::CIMTYPE_REAL64:
                _to_cimple_array<P_Real64, real64>::func(v, ci, f);
                break;

            case Pegasus::CIMTYPE_CHAR16:
            {
                Pegasus::Array<P_Char16> tmp;
                v.get(tmp);

                ((Property< Array<char16> >*)f)->value.assign(
                    (char16*)tmp.getData(), tmp.size());

                ((Property< Array<char16> >*)f)->null = 0;
                break;
            }

            case Pegasus::CIMTYPE_STRING:
            {
                Pegasus::Array<P_String> tmp;
                v.get(tmp);

                Array<String> a;

                for (P_Uint32 i = 0; i < tmp.size(); i++)
                    a.append(*Str(tmp[i]));

                (*((Property<Array_String>*)f)).value = a;
                (*((Property<Array_String>*)f)).null = v.isNull() ? 1 : 0;
                break;
            }

            case Pegasus::CIMTYPE_DATETIME:
            {
                Pegasus::Array<P_CIMDateTime> tmp;
                v.get(tmp);

                Array<Datetime> a;

                for (P_Uint32 i = 0; i < tmp.size(); i++)
                {
                    Datetime dt;
                    dt.set(*Str(tmp[i]));
                    a.append(dt);
                }

                (*((Property<Array_Datetime>*)f)).value = a;
                (*((Property<Array_Datetime>*)f)).null = 0;
                break;
            }

            case Pegasus::CIMTYPE_REFERENCE:
            case Pegasus::CIMTYPE_OBJECT:
            default:
                CIMPLE_ERROR(("2unexpected condition"));
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

typedef const Pegasus::Array<P_CIMParamValue> Params;

typedef const P_String (*Get_Name_Proc)(const void* data, size_t index);

typedef int (*Get_Value_Proc)(
    const void* data, 
    size_t index, 
    P_CIMType expected_type,
    P_CIMValue& value);

static const P_String _bindings_get_name(const void* data, size_t index)
{
    Key_Bindings* bindings = (Key_Bindings*)data;
    return (*bindings)[P_Uint32(index)].getName().getString();
}

static int _bindings_get_value(
    const void* data, 
    size_t index, 
    P_CIMType expected_type,
    P_CIMValue& v)
{
    Key_Bindings& bindings = *((Key_Bindings*)data);

    try
    {
        Str str(bindings[P_Uint32(index)].getValue());

        switch(expected_type)
        {
            case Pegasus::CIMTYPE_REFERENCE:
            {
                v = P_CIMValue(P_CIMObjectPath(*str));
                return 0;
            }

            case Pegasus::CIMTYPE_DATETIME:
            {
                v = P_CIMValue(P_CIMDateTime(*str));
                return 0;
            }

            case Pegasus::CIMTYPE_STRING:
            {
                v = P_CIMValue(P_String(*str));
                return 0;
            }

            case Pegasus::CIMTYPE_BOOLEAN:
            {
                if (strcasecmp(*str, "true") == 0)
                {
                    v = P_CIMValue(true);
                    return 0;
                }

                if (strcasecmp(*str, "false") == 0)
                {
                    v = P_CIMValue(false);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_UINT8:
            {
                P_Uint8 x;

                if (Uint8_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_SINT8:
            {
                P_Sint8 x;

                if (Sint8_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_UINT16:
            {
                P_Uint16 x;

                if (Uint16_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_SINT16:
            {
                P_Sint16 x;

                if (Sint16_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_UINT32:
            {
                P_Uint32 x;

                if (Uint32_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_SINT32:
            {
                P_Sint32 x;

                if (Sint32_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_UINT64:
            {
                P_Uint64 x;

                if (Uint64_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            case Pegasus::CIMTYPE_SINT64:
            {
                P_Sint64 x;

                if (Sint64_From_Str(x, *str) == 0)
                {
                    v = P_CIMValue(x);
                    return 0;
                }

                break;
            }

            default:
                break;
        }
    }
    catch (...)
    {
    }

    CIMPLE_ERROR(("key binding conversion error"));
    return -1;
}

static const P_String _instance_get_name(const void* data, size_t index)
{
    P_CIMInstance* instance = (P_CIMInstance*)data;
    return (*instance).getProperty(
        P_Uint32(index)).getName().getString();
}

static int _instance_get_value(
    const void* data, 
    size_t index, 
    P_CIMType expected_type,
    P_CIMValue& v)
{
    P_CIMInstance* instance = (P_CIMInstance*)data;
    v = (*instance).getProperty(P_Uint32(index)).getValue();
    return 0;
}

static const P_String _params_get_name(const void* data, size_t index)
{
    Params* params = (Params*)data;
    return (*params)[P_Uint32(index)].getParameterName();
}

static int _params_get_value(
    const void* data, 
    size_t index,
    P_CIMType expected_type,
    P_CIMValue& v)
{
    Params* params = (Params*)data;
    v = (*params)[P_Uint32(index)].getValue();
    return 0;
}

static Instance* _make_cimple_instance(
    const void* data,
    size_t count,
    Get_Name_Proc get_name_proc,
    Get_Value_Proc get_value_proc,
    const Meta_Class* mc,
    bool keys_only,
    const String& name_space = String())
{
    // Create a new instance:

    Instance* instance = create(mc);

    // Nullify the properties:

    nullify_properties(instance);

    // Convert each of the name-value pairs:

    for (size_t i = 0; i < count; i++)
    {
        Str name(get_name_proc(data, i));

        // Find the corresponding CIMPLE feature:

        const Meta_Feature* mf = find_feature(mc, name);

        if (!mf)
        {
            // CIMPLE does not have this property but Pegasus does.
            continue;
        }

        // Skip non-keys if so requested.

        if (keys_only && !(mf->flags & CIMPLE_FLAG_KEY))
            continue;

        // Initialize the feature:

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;

            P_CIMValue v;
            
            if (get_value_proc(data, i, P_CIMType(mp->type), v) != 0)
            {
                CIMPLE_ERROR(("type conversion error on %s", mp->name));
                destroy(instance);
                return 0;
            }

            if (_to_cimple_property(v, instance, mp) != 0)
            {
                CIMPLE_ERROR(("type mismatch on %s", mp->name));
                destroy(instance);
                return 0;
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;

            if (mr->subscript)
            {
                P_CIMValue v;
                
                if (get_value_proc(data, i, Pegasus::CIMTYPE_REFERENCE, v) != 0)
                {
                    CIMPLE_ERROR(("type conversion error on %s", mr->name));
                    destroy(instance);
                    return 0;
                }

                Pegasus::Array<P_CIMObjectPath> x;

                try
                {
                    v.get(x);
                }
                catch (...)
                {
                    CIMPLE_ERROR(("type mismatch on ref feature %s", mf->name));
                    destroy(instance);
                    return 0;
                }

                for (P_Uint32 i = 0; i < x.size(); i++)
                {
                    if (Converter::_append_cimple_ref(x[i], instance, mr) != 0)
                    {
                        destroy(instance);
                        return 0;
                    }
                }
            }
            else
            {
                P_CIMValue v;
                
                if (get_value_proc(data, i, Pegasus::CIMTYPE_REFERENCE, v) != 0)
                {
                    destroy(instance);
                    return 0;
                }

                if (Converter::_to_cimple_ref(v, instance, mr) != 0)
                {
                    destroy(instance);
                    return 0;
                }
            }
        }
        else
        {
            CIMPLE_ERROR(("feature not found: %s", mf->name));
            destroy(instance);
            return 0;
        }
    }

    if (name_space.size())
        instance->__name_space = name_space;

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
    const P_CIMValue& v,
    Instance* ci,
    const Meta_Reference* mr)
{
    Instance*& ref = __ref_of(ci, mr);

    if (ref != 0)
    {
        CIMPLE_ASSERT(ref->__magic == CIMPLE_INSTANCE_MAGIC);
        destroy(ref);
        ref = 0;
        CIMPLE_ASSERT(0);
    }

    // Get the object path object:

    P_CIMObjectPath op;

    try
    {
        v.get(op);
    }
    catch (...)
    {
        CIMPLE_ERROR(("1unexpected failure"));
        return -1;
    }

    // Figure out which meta class to use. If the incoming class does not match
    // the reference class, then use the incoming class (so long as it derives
    // from the reference class).

    Str cn(op.getClassName());

    const Meta_Class* mc = mr->meta_class;

    if (strcasecmp(mr->name, *cn) != 0)
    {
        mc = find_meta_class(mr->meta_class->meta_repository, *cn);

        if (!mc)
        {
            CIMPLE_ERROR(("CIMPLE meta repository has no such class: %s", *cn));
            return -1;
        }

        if (!is_subclass(mr->meta_class, mc))
        {
            CIMPLE_ERROR(("Conversion of Pegasus object path to CIMPLE "
                "reference failed since the object path class (%s) is not a "
                "subclass of the reference class (%s)",
                *cn, mr->meta_class->name));
            return -1;
        }
    }
    else
        mc = mr->meta_class;

    // Check for same number of keys:

    const Pegasus::Array<P_CIMKeyBinding>& bindings = 
        op.getKeyBindings();

#if 0
    if (bindings.size() != mc->num_keys)
    {
        CIMPLE_ERROR(("key count mismatch"));
        return -1;
    }
#endif

    // Create the reference instance:

    ref = _make_cimple_instance(
        &bindings, 
        bindings.size(),
        _bindings_get_name,
        _bindings_get_value,
        mc,
        true,
        *Str(op.getNameSpace()));

    if (!ref)
        return -1;

    return 0;
}

//------------------------------------------------------------------------------
//
// _append_cimple_ref()
//
//------------------------------------------------------------------------------

int Converter::_append_cimple_ref(
    const P_CIMObjectPath& cop,
    cimple::Instance* ci,
    const cimple::Meta_Reference* mr)
{
    Array_Ref& ref = __array_ref_of(ci, mr);

    // Figure out which meta class to use. If the incoming class does not match
    // the reference class, then use the incoming class (so long as it derives
    // from the reference class).

    Str cn(cop.getClassName());

    const Meta_Class* mc = mr->meta_class;

    if (strcasecmp(mr->name, *cn) != 0)
    {
        mc = find_meta_class(mr->meta_class->meta_repository, *cn);

        if (!mc)
        {
            CIMPLE_ERROR(("CIMPLE meta repository has no such class: %s", *cn));
            return -1;
        }

        if (!is_subclass(mr->meta_class, mc))
        {
            CIMPLE_ERROR(("Conversion of Pegasus object path to CIMPLE "
                "reference failed since the object path class (%s) is not a "
                "subclass of the reference class (%s)",
                *cn, mr->meta_class->name));
            return -1;
        }
    }
    else
        mc = mr->meta_class;

    // Check for same number of keys:

    const Pegasus::Array<P_CIMKeyBinding>& bindings = 
        cop.getKeyBindings();

#if 0
    if (bindings.size() != mc->num_keys)
    {
        CIMPLE_ERROR(("key count mismatch"));
        return -1;
    }
#endif

    // Create the reference instance:

    Instance* r = _make_cimple_instance(
        &bindings, 
        bindings.size(),
        _bindings_get_name,
        _bindings_get_value,
        mc,
        true,
        *Str(cop.getNameSpace()));

    if (!r)
        return -1;

    ref.append(r);

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
    const P_CIMInstance& pi,
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

    if (!ci)
        return -1;

#if 0
    if (ci->meta_class == mc && bindings.size() != mc->num_keys)
    {
        CIMPLE_ERROR(("key count mismatch"));
        return -1;
    }
#endif

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
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* ci,
    P_CIMObjectPath& object_path)
{
    CIMPLE_ASSERT(ci->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ci->meta_class;

    // Build up key bindings from this CIMPLE instance.

    Pegasus::Array<P_CIMKeyBinding> bindings;

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

        P_CIMValue value;

        if (_to_pegasus_value(hn, ns, ci, mf, value) != 0)
            return -1;

        bindings.append(P_CIMKeyBinding(mf->name, value));
    }

    // Initialize the object path:

    P_CIMNamespaceName real_ns;

    if (ci->__name_space.size())
        real_ns = P_CIMNamespaceName(ci->__name_space.c_str());
    else
        real_ns = P_CIMNamespaceName(ns);

    object_path.set(hn, real_ns, mc->name, bindings);

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
    const P_CIMPropertyList& pl,
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
        Str name(pl[P_Uint32(i)]);

        const Meta_Property* mp = (Meta_Property*)find_feature(mc, *name);

        if (!mp)
        {
            // CIMPLE does not have this property but Pegasus does.
            continue;
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
    const Pegasus::Array<P_CIMParamValue>& in_params,
    const Meta_Class* mc,
    Instance*& meth)
{
/*
ATTN: handle conversion from REF arrays.
*/

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

    // Iterate the meta-method looking for missing input parameters:

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
        const Meta_Feature* mf = mm->meta_features[i];

        if (mf->flags & CIMPLE_FLAG_PROPERTY && mf->flags & CIMPLE_FLAG_IN)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            bool found = false;

            const P_CIMParamValue* data = in_params.getData();

            for (P_Uint32 j = 0, n = in_params.size(); j < n; j++)
            {
                Str param_name(data[j].getParameterName());

                if (strcasecmp(param_name, mp->name) == 0)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                CIMPLE_ERROR(("missing input parameter: %s", mp->name));
                meth = 0;
                destroy(meth);
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
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* meth,
    Pegasus::Array<P_CIMParamValue>& out_params,
    P_CIMValue& return_value)
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

                if (_to_pegasus_value(hn, ns, meth, mf, return_value) != 0)
                    return -1;
            }
            else
            {
                P_CIMValue value;

                if (_to_pegasus_value(hn, ns, meth, mf, value) != 0)
                    return -1;

                out_params.append(P_CIMParamValue(mf->name, value));
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

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/adapter/Converter.cpp,v 1.42 2007/04/17 19:45:11 mbrasher-public Exp $");
