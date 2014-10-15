/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** Copyright (c) 2007 Novell, Inc.
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
#include <cimple/Error.h>
#include <openwbem/OW_config.h>
#include <openwbem/OW_Types.hpp>
#include <openwbem/OW_Bool.hpp>
#include <openwbem/OW_Char16.hpp>
#include <openwbem/OW_CIMObjectPath.hpp>
#include <openwbem/OW_CIMProperty.hpp>
#include <openwbem/OW_CIMValue.hpp>
#include <openwbem/OW_CIMDateTime.hpp>
#include <openwbem/OW_CIMNameSpace.hpp>
#include "Converter.h"


#define CIMPLE_HAVE_CIMTYPE_INSTANCE

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

CIMPLE_NAMESPACE_BEGIN

namespace Converter
{

using namespace OpenWBEM; 

///////////////////////////////////////////////////////////////////////////////
static void _to_openwbem_scalar(
    const Meta_Property* mp,
    const void* field, 
    OpenWBEM::CIMValue& value)
{
    CIMPLE_ASSERT(mp != 0);
    CIMPLE_ASSERT(mp->subscript == 0);
    CIMPLE_ASSERT(field != 0);


    switch (Type(mp->type))
    {
        case BOOLEAN:
            value.set(CIMValue(*((boolean*)field)));
            break;

        case UINT8:
            value.set(CIMValue(*((UInt8*)field)));
            break;

        case SINT8:
            value.set(CIMValue(*((Int8*)field)));
            break;

        case UINT16:
            value.set(CIMValue(*((UInt16*)field)));
            break;

        case SINT16:
            value.set(CIMValue(*((Int16*)field)));
            break;

        case UINT32:
            value.set(CIMValue(*((UInt32*)field)));
            break;

        case SINT32:
            value.set(CIMValue(*((Int32*)field)));
            break;

        case UINT64:
            value.set(CIMValue(*((UInt64*)field)));
            break;

        case SINT64:
            value.set(CIMValue(*((Int64*)field)));
            break;

        case REAL32:
            value.set(CIMValue(*((Real32*)field)));
            break;

        case REAL64:
            value.set(CIMValue(*((Real64*)field)));
            break;

        case CHAR16:
            //value.set(Pegasus::Char16(*((char16*)field)));
            value.set(CIMValue(OpenWBEM::String((*((char16*)field))))); 
            break;

        case STRING:
            value.set(CIMValue(OpenWBEM::String(
                (*((String*)field)).c_str(), (*((String*)field)).size()))); 
            break;

        case DATETIME:
        {
            char buffer[Datetime::BUFFER_SIZE];
            ((const Datetime*)field)->ascii(buffer);
            value.set(CIMValue(OpenWBEM::CIMDateTime(buffer)));
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
template<class CT, class OT>
struct _to_openwbem_array_helper
{
    static void func(
        const Meta_Property* mp,
        const void* field, 
        OpenWBEM::CIMValue& value)
    {
        const Array<CT>& tmp = *((const Array<CT>*)field);
        OpenWBEM::Array<OT> array; 
        array.reserve(tmp.size());
        for (size_t i = 0; i < tmp.size();  ++i)
        {
            array.push_back(tmp[i]); 
        }
        value.set(CIMValue(array));
    }
};
///////////////////////////////////////////////////////////////////////////////
static void _to_openwbem_array(
    const Meta_Property* mp,
    const void* f, 
    OpenWBEM::CIMValue& v)
{
    CIMPLE_ASSERT(mp != 0);
    CIMPLE_ASSERT(mp->subscript != 0);
    CIMPLE_ASSERT(f != 0);


    if (null_of(mp, f))
    {
        v.set(CIMValue(StringArray())); 
        v.setNull(); 
        return;
    }

    switch (Type(mp->type))
    {
        case BOOLEAN:
            _to_openwbem_array_helper<boolean, OpenWBEM::Bool>::func(mp, f, v);
            break;

        case UINT8:
            _to_openwbem_array_helper<uint8, OpenWBEM::UInt8>::func(mp, f, v);
            break;

        case SINT8:
            _to_openwbem_array_helper<sint8, OpenWBEM::Int8>::func(mp,f,v);
            break;

        case UINT16:
            _to_openwbem_array_helper<uint16, OpenWBEM::UInt16>::func(mp, f, v);
            break;

        case SINT16:
            _to_openwbem_array_helper<sint16, OpenWBEM::Int16>::func(mp, f, v);
            break;

        case UINT32:
            _to_openwbem_array_helper<uint32, OpenWBEM::UInt32>::func(mp, f, v);
            break;

        case SINT32:
            _to_openwbem_array_helper<sint32, OpenWBEM::Int32>::func(mp, f, v);
            break;

        case UINT64:
            _to_openwbem_array_helper<uint64, OpenWBEM::UInt64>::func(mp, f, v);
            break;

        case SINT64:
            _to_openwbem_array_helper<sint64, OpenWBEM::Int64>::func(mp, f, v);
            break;

        case REAL32:
            _to_openwbem_array_helper<real32, OpenWBEM::Real32>::func(mp, f, v);
            break;

        case REAL64:
            _to_openwbem_array_helper<real64, OpenWBEM::Real64>::func(mp, f, v);
            break;

        case CHAR16:
            // TODO _to_openwbem_array_helper<
            //     char16, OpenWBEM::Char16>::func(mp, f, v);
            assert(0); 
            break;

        case STRING:
        {
            Array_String& tmp = *((Array_String*)f);

            OpenWBEM::StringArray array;
            array.reserve(tmp.size());

            for (size_t i = 0; i < tmp.size(); ++i)
            {
                array.append(OpenWBEM::String(tmp[i].c_str()));
            }

            v.set(OpenWBEM::CIMValue(array));
            break;
        }

        case DATETIME:
        {
            Array<Datetime>& tmp = *((Array<Datetime>*)f);

            OpenWBEM::Array<OpenWBEM::CIMDateTime> array;
            array.reserve(tmp.size());

            for (size_t i = 0; i < tmp.size(); i++)
            {
                char buffer[Datetime::BUFFER_SIZE];
                tmp[i].ascii(buffer);
                array.append(OpenWBEM::CIMDateTime(buffer));
            }

            v.set(OpenWBEM::CIMValue(array));
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
static int _to_openwbem_value(
    const OpenWBEM::String& ns,
    const Instance* ci, 
    const Meta_Feature* mf, 
    OpenWBEM::CIMValue& value)
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
        {
            return 0;
        }

        OpenWBEM::CIMInstance oi;

        if (Converter::to_openwbem_instance(ns, ref, oi) != 0)
        {
            return -1;
        }

        value.set(OpenWBEM::CIMValue(oi));

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

            if (is_array)
            {
                value.set(OpenWBEM::CIMValue(OpenWBEM::StringArray())); 
            }

            value.setNull(); 

            return 0;
        }

        if (mp->subscript == 0)
            _to_openwbem_scalar(mp, prop, value);
        else
            _to_openwbem_array(mp, prop, value);

        return 0;
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (const Meta_Reference*)mf;
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

            return 0;
        }

        OpenWBEM::CIMObjectPath op;

        if (Converter::to_openwbem_object_path(ns, ref, op) != 0)
            return -1;

        value.set(OpenWBEM::CIMValue(op));

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

///////////////////////////////////////////////////////////////////////////////
int to_openwbem_instance(
        const OpenWBEM::String& ns,
        const cimple::Instance* ci,
        OpenWBEM::CIMInstance& oi)
{
    TRACE ; 
    CIMPLE_ASSERT(ci != 0);
    CIMPLE_ASSERT(ci->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ci->meta_class;

    // Create OpenWBEM instance of the given class.

    oi.setClassName(mc->name);
    oi.setNameSpace(ns); 

    // Copy properties from CIMPLE to OpenWBEM instance and to object path.

    OpenWBEM::CIMPropertyArray cpa; 

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        if (mf->flags & CIMPLE_FLAG_METHOD)
            continue;

        // Create OpenWBEM value.

        OpenWBEM::CIMValue cv(CIMNULL);

        if (_to_openwbem_value(ns, ci, mf, cv) != 0)
        {
            return -1;
        }

        // Add key binding.

        try
        {
            oi.setProperty(mf->name, cv); 
        }
        catch(...)
        {
            CIMPLE_ERROR(("addProperty() failed: %s", mf->name));
            return -1;
        }
    }

    oi.setKeys(cpa); 

    TRACE ; 
    return 0;
}

//------------------------------------------------------------------------------
//
// _to_cimple_scalar()
//
//     Converts OpenWBEM scalar to a CIMPLE one.
//
//------------------------------------------------------------------------------

template<class OT, class CT>
struct _to_cimple_scalar
{
    static void func(
        const OpenWBEM::CIMValue& value,
        Instance* ci,
        char* field)
    {
        if (value)
        {
            OT ot;
            value.get(ot);
            CT ct = ot;
            ((Property<CT>*)field)->value = ct;
            ((Property<CT>*)field)->null = 0; 
        }
        else
        {
            ((Property<CT>*)field)->null = 1; 
        }
    }
};

template<> 
struct _to_cimple_scalar<OpenWBEM::Char16, char16>
{
    typedef OpenWBEM::Char16 OT;
    typedef char16 CT;

    static void func(
        const OpenWBEM::CIMValue& value,
        Instance* ci,
        char* field)
    {
        if (value)
        {
            OT ot;
            value.get(ot);
            CT ct = uint16(ot);
            ((Property<CT>*)field)->value = ct;
            ((Property<CT>*)field)->null = 0; 
        }
        else
        {
            ((Property<CT>*)field)->null = 1; 
        }
    }
};

//------------------------------------------------------------------------------
//
// _to_cimple_array()
//
//     Converts a Pegasus array to a CIMPLE one.
//
//------------------------------------------------------------------------------

template<typename OT, typename CT>
struct _to_cimple_array
{
    static void func(
        const OpenWBEM::CIMValue& value,
        Instance* ci,
        char* field)
    {
        if (value)
        {
            OpenWBEM::Array<OT> tmp;
            value.get(tmp);
            for (typename OpenWBEM::Array<OT>::const_iterator iter = 
                tmp.begin(); iter != tmp.end(); ++iter)
            {
                CT ct = *iter; 
                ((Property< Array<CT> >*)field)->value.append(ct); 
            }
            ((Property< Array<CT> >*)field)->null = 0; 
        }
        else
        {
            ((Property< Array<CT> >*)field)->null = 1; 
        }
    }
};

//------------------------------------------------------------------------------
//
// _to_cimple_property()
//
//     Converts an OpenWBEM value to a CIMPLE one.
//
//------------------------------------------------------------------------------

#define _cimple_check_type(ctype) \
    if (mp->type != ctype) \
    { \
        CIMPLE_ERROR(("type mismatch")); \
        return -1; \
    }

#define _to_cimple_property_macro(cimple_type_id, ow_type, cimple_type) \
    _cimple_check_type(cimple_type_id);                                 \
    if (mp->subscript == 0)                                             \
    {           \
        _to_cimple_scalar<ow_type, cimple_type>::func(v, ci, f);        \
    }           \
    else        \
    {           \
        _to_cimple_array<ow_type, cimple_type>::func(v, ci, f);         \
    }           

static int _to_cimple_property(
    const OpenWBEM::CIMValue& v,
    Instance* ci,
    const Meta_Property* mp)
{
    CIMPLE_ASSERT(ci != 0);

    if (v.isArray() && mp->subscript == 0)
    {
        CIMPLE_ERROR(("array/scalar type mismatch"));
        return -1;
    }

    //  Set property value.
    char* f = (char*)ci + mp->offset;

    switch (v.getType())
    {
    case OpenWBEM::CIMDataType::UINT8:
        _to_cimple_property_macro(UINT8, OpenWBEM::UInt8, uint8); 
        break;
    case OpenWBEM::CIMDataType::SINT8:
        _to_cimple_property_macro(SINT8, OpenWBEM::Int8, sint8); 
        break;
    case OpenWBEM::CIMDataType::UINT16:
        _to_cimple_property_macro(UINT16, OpenWBEM::UInt16, uint16); 
        break; 
    case OpenWBEM::CIMDataType::SINT16:
        _to_cimple_property_macro(SINT16, OpenWBEM::Int16, sint16); 
        break;
    case OpenWBEM::CIMDataType::UINT32:
        _to_cimple_property_macro(UINT32, OpenWBEM::UInt32, uint32); 
        break;
    case OpenWBEM::CIMDataType::SINT32: 
        _to_cimple_property_macro(SINT32, OpenWBEM::Int32, sint32); 
        break; 
    case OpenWBEM::CIMDataType::UINT64:
        _to_cimple_property_macro(UINT64, OpenWBEM::UInt64, uint64); 
        break;
    case OpenWBEM::CIMDataType::SINT64:
        _to_cimple_property_macro(SINT64, OpenWBEM::Int64, sint64); 
        break;
    case OpenWBEM::CIMDataType::STRING:
        _cimple_check_type(STRING); 
        if (!v)
        {
            (*((Property<String>*)f)).null = 1; 
        }
        else
        {
            (*((Property<String>*)f)).null = 0; 
            if (mp->subscript == 0)
            {
                OpenWBEM::String str;
                v.get(str);
                (*((Property<String>*)f)).value = str.c_str(); 
            }
            else
            {
                OpenWBEM::StringArray sa; 
                v.get(sa); 
                Array<String> a;

                for (OpenWBEM::StringArray::const_iterator iter = sa.begin(); 
                      iter != sa.end(); ++iter)
                {
                    a.append(String(iter->c_str())); 
                }
                (*((Property<Array_String>*)f)).value = a;
            }
        }
        break; 
    case OpenWBEM::CIMDataType::BOOLEAN:
        _to_cimple_property_macro(BOOLEAN, OpenWBEM::Bool, boolean); 
        break; 
    case OpenWBEM::CIMDataType::REAL32:
        _to_cimple_property_macro(REAL32, OpenWBEM::Real32, real32); 
        break;
    case OpenWBEM::CIMDataType::REAL64:
        _to_cimple_property_macro(REAL64, OpenWBEM::Real64, real64); 
        break; 
    case OpenWBEM::CIMDataType::DATETIME:
        _cimple_check_type(DATETIME); 
        if (!v)
        {
            (*((Property<Datetime>*)f)).null = 1; 
        }
        else
        {
            (*((Property<Datetime>*)f)).null = 0; 
            if (mp->subscript == 0)
            {
                OpenWBEM::CIMDateTime dt;
                v.get(dt);
                (*((Property<Datetime>*)f)).value.set(dt.toString().c_str());
            }
            else
            {
                OpenWBEM::Array<CIMDateTime> cdta; 
                v.get(cdta); 
                Array<Datetime> a;
                for (OpenWBEM::Array<CIMDateTime>::const_iterator iter = 
                      cdta.begin(); 
                      iter != cdta.end(); ++iter)
                {
                    Datetime dt;
                    dt.set(iter->toString().c_str()); 
                    a.append(dt);
                }
                (*((Property<Array_Datetime>*)f)).value = a;
            }
        }
        break; 
    case OpenWBEM::CIMDataType::CHAR16:
        // TODO _to_cimple_property_macro(CHAR16, OpenWBEM::Char16, char16); 
        // break;
    case OpenWBEM::CIMDataType::REFERENCE:
    case OpenWBEM::CIMDataType::EMBEDDEDCLASS:
    case OpenWBEM::CIMDataType::EMBEDDEDINSTANCE:
    default: 
        CIMPLE_ERROR(("unexpected condition"));
        return -1;
        break; 
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
template <typename ParmOrProp>
Instance* _make_cimple_instance(const OpenWBEM::Array<ParmOrProp>& bindings, 
                                       const Meta_Class* mc, 
                                       bool keys_only)
{
    Instance* instance = create(mc); 
    //CIMPLE_ASSERT(mc->__magic == CIMPLE_INSTANCE_MAGIC); 

    // nullify properties: 
    nullify_properties(instance); 

    for (typename OpenWBEM::Array<ParmOrProp>::const_iterator iter = 
          bindings.begin(); 
          iter != bindings.end(); ++iter)
    {
        const Meta_Feature* mf = find_feature(mc, iter->getName().c_str()); 
        if (!mf)
        {
            CIMPLE_ERROR(("no such feature: %s", iter->getName().c_str())); 
            destroy(instance); 
            return 0; 
        }
        // skip non-keys if requested. 
        if (keys_only && !(mf->flags & CIMPLE_FLAG_KEY))
        {
            continue; 
        }
        // initialize the feature. 
        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf; 
            const OpenWBEM::CIMValue value = iter->getValue(); 
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
            const OpenWBEM::CIMValue value = iter->getValue(); 
            // TODO finish this. 
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

///////////////////////////////////////////////////////////////////////////////
int to_cimple_instance(
        const OpenWBEM::CIMInstance& ow_instance,
        const cimple::Meta_Class* mc,
        cimple::Instance*& ci)
{
    ci = _make_cimple_instance<OpenWBEM::CIMProperty>(
                 ow_instance.getProperties(), mc, false);

    return ci ? 0 : -1;
}

///////////////////////////////////////////////////////////////////////////////
int to_cimple_key(
        const OpenWBEM::CIMObjectPath& bindings,
        const cimple::Meta_Class* mc,
        cimple::Instance*& ci)
{
    if (bindings.getKeys().size() != mc->num_keys)
    {
        CIMPLE_ERROR(("key count mismatch"));
        return -1;
    }

    ci = _make_cimple_instance<OpenWBEM::CIMProperty>(bindings.getKeys(), 
                                                      mc, false);

    return ci ? 0 : -1;
}

///////////////////////////////////////////////////////////////////////////////
int to_openwbem_object_path(
        const OpenWBEM::String& name_space,
        const cimple::Instance* ci,
        OpenWBEM::CIMObjectPath& object_path)
{
    CIMPLE_ASSERT(ci->__magic == CIMPLE_INSTANCE_MAGIC); 
    const Meta_Class* mc = ci->meta_class; 

    // TODO hostname? 
    object_path.setNameSpace(name_space); 
    object_path.setClassName(mc->name); 

    // build up key bindings from this CIMPLE instance. 
    for (size_t i = 0; i < mc->num_meta_features; ++i)
    {
        const Meta_Feature* mf = mc->meta_features[i]; 
        // Ignore non-key features: 
        if (!(mf->flags & CIMPLE_FLAG_KEY))
        {
            continue; 
        }

        // Ignore methods: 
        if (mf->flags & CIMPLE_FLAG_METHOD)
        {
            continue; 
        }

        // convert feature to property
        OpenWBEM::CIMValue value(CIMNULL); 
        if (_to_openwbem_value(name_space, ci, mf, value) != 0)
        {
            return -1; 
        }
        object_path.setKeyValue(mf->name, value);
    }
    return 0; 
}

///////////////////////////////////////////////////////////////////////////////
int de_nullify_properties(
        const OpenWBEM::StringArray* propertyList,
        cimple::Instance* ci)
{
    // If the property list is null, define all the properties (the requestor
    // wants them all).

    if (!propertyList)
    {
        cimple::de_nullify_properties(ci);
        return 0;
    }

    // Nullify all properties.

    nullify_non_keys(ci);

    // Denullify requested properties:

    const Meta_Class* mc = ci->meta_class;

    for (OpenWBEM::StringArray::const_iterator iter = propertyList->begin(); 
          iter != propertyList->end(); ++iter)
    {
        const Meta_Property* mp = 
            (Meta_Property*)find_feature(mc, iter->c_str());

        if (!mp)
        {
            CIMPLE_ERROR(("no such property: %s", iter->c_str()));
            return -1;
        }

        if (mp->flags & CIMPLE_FLAG_KEY)
        {
            continue;
        }

        if (mp->flags & CIMPLE_FLAG_PROPERTY)
        {
            null_of(mp, (char*)ci + mp->offset) = 0;
        }
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int to_openwbem_method(const OpenWBEM::CIMObjectPath& path, 
                                  const cimple::Instance* meth, 
                                  OpenWBEM::CIMParamValueArray& out_params, 
                                  OpenWBEM::CIMValue& return_value)
{
    CIMPLE_ASSERT(meth != 0); 
    out_params.clear();  // TODO: is this wise? 
    // iterate the meta-method to initialize out_params and return value; 
    const Meta_Method* mm = (const Meta_Method*)meth->meta_class; 
    CIMPLE_ASSERT(mm->flags & CIMPLE_FLAG_METHOD); 
    bool found_return_value(false); 

    for (size_t i = 0; i < mm->num_meta_features; ++i)
    {
        const Meta_Feature* mf = mm->meta_features[i]; 
        // convert to OpenWBEM value; 
        if (mf->flags & CIMPLE_FLAG_OUT)
        {
            if (strcasecmp(mf->name, "return_value") == 0)
            {
                found_return_value = true; 
                _to_openwbem_value(path.getFullNameSpace().getNameSpace(), 
                                   meth, mf, return_value); 
            }
            else
            {
                OpenWBEM::CIMValue value(CIMNULL); 
                _to_openwbem_value(path.getFullNameSpace().getNameSpace(), 
                                   meth, mf, value); 
                out_params.append(OpenWBEM::CIMParamValue(mf->name, value)); 
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

///////////////////////////////////////////////////////////////////////////////
int to_cimple_method(const OpenWBEM::String& methodName, 
                                const OpenWBEM::CIMParamValueArray& in_params, 
                                const cimple::Meta_Class* mc, 
                                cimple::Instance*& meth)
{
    meth = 0; 
    // first look up method:
    const Meta_Method* mm = find_method(mc, methodName.c_str()); 
    if (!mm)
    {
        CIMPLE_ERROR(("no such method: %s", methodName.c_str())); 
        return -1; 
    }
    // create new method instance
    meth = _make_cimple_instance<OpenWBEM::CIMParamValue>(in_params, 
        (Meta_Class*)mm, false); 
    if (!meth)
    {
        return -1; 
    }
    // Create reference output parameters
    for (size_t i = 0; i < mm->num_meta_features; ++i)
    {
        const Meta_Feature* mf = mm->meta_features[i]; 
        if (mf->flags & CIMPLE_FLAG_REFERENCE && mf->flags & CIMPLE_FLAG_OUT)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf; 
            Instance*& ref = __ref_of(meth, mr); 
            if (!ref)
            {
                ref = create(mr->meta_class); 
            }
        }
    }
    // Iterate the meta-method looking for missing input parameters; 
    for (size_t i = 0; i < mm->num_meta_features; ++i)
    {
        const Meta_Feature* mf = mm->meta_features[i]; 
        if (mf->flags & CIMPLE_FLAG_PROPERTY && mf->flags & CIMPLE_FLAG_IN)
        {
            const Meta_Property* mp = (const Meta_Property*) mf; 
            bool found = false; 
            for (OpenWBEM::CIMParamValueArray::const_iterator iter = 
                  in_params.begin(); 
                  iter != in_params.end(); ++iter)
            {
                if (iter->getName().equalsIgnoreCase(mp->name))
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

} // end Converter namespace

CIMPLE_NAMESPACE_END

