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

#include <cassert>
#include <cstring>
#include <cimple/Strings.h>
#include "Converter.h"

// #define VOID /* */

#if 1
# define RETURN(X) return X
#else
# define RETURN(X) CIMPLE_RETURN(X)
#endif

// ATTN: handle embedded object properties (for indications).

using namespace cimple;

static CMPIType _cmpi_type[] = 
{
    CMPI_boolean,
    CMPI_uint8,
    CMPI_sint8,
    CMPI_uint16,
    CMPI_sint16,
    CMPI_uint32,
    CMPI_sint32,
    CMPI_uint64,
    CMPI_sint64,
    CMPI_real32,
    CMPI_real64,
    CMPI_char16,
    CMPI_string,
    CMPI_dateTime,
};

static uint16 _to_cimple_type(CMPIType type)
{
    switch (type)
    {
        case CMPI_boolean: RETURN(cimple::BOOLEAN);
        case CMPI_uint8: RETURN(UINT8);
        case CMPI_sint8: RETURN(SINT8);
        case CMPI_uint16: RETURN(UINT16);
        case CMPI_sint16: RETURN(SINT16);
        case CMPI_uint32: RETURN(cimple::UINT32);
        case CMPI_sint32: RETURN(SINT32);
        case CMPI_uint64: RETURN(cimple::UINT64);
        case CMPI_sint64: RETURN(SINT64);
        case CMPI_real32: RETURN(REAL32);
        case CMPI_real64: RETURN(REAL64);
        case CMPI_char16: RETURN(CHAR16);
        case CMPI_string: RETURN(STRING);
        case CMPI_dateTime: RETURN(DATETIME);
        default: RETURN(0);
    }
}

static CMPIrc _set_cimple_scalar(
    const Meta_Property* mp, 
    void* prop, 
    const CMPIData& data)
{
    // Scalar case:

    if (CMIsArray(data))
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Set null flag:

    if (data.state & CMPI_nullValue)
    {
        null_of(mp, prop) = 1;
        RETURN(CMPI_RC_OK);
    }
    else
        null_of(mp, prop) = 0;

    // Check the type:

    if (data.type != _cmpi_type[mp->type])
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);

    // Handle integer types up front:

    if (is_raw[mp->type] && mp->type != cimple::BOOLEAN)
    {
        memcpy(prop, &data.value, type_size[mp->type]);
        RETURN(CMPI_RC_OK);
    }

    // Set value:

    switch(mp->type)
    {
        case cimple::BOOLEAN:
            *((cimple::boolean*)prop) = data.value.boolean;
            break;

        case STRING:
            *((String*)prop) = CMGetCharPtr(data.value.string);
            break;

        case DATETIME:
            ((Datetime*)prop)->set(
                CMGetCharPtr(CMGetStringFormat(data.value.dateTime, NULL)));
            break;

        default:
            break;
    }

    RETURN(CMPI_RC_OK);
}

static sint64 _promote(const CMPIData& data)
{
    switch(data.type)
    {
        case CMPI_uint8:
            RETURN(sint64(data.value.uint8));

        case CMPI_sint8:
            RETURN(sint64(data.value.sint8));

        case CMPI_uint16:
            RETURN(sint64(data.value.uint16));

        case CMPI_sint16:
            RETURN(sint64(data.value.sint16));

        case CMPI_uint32:
            RETURN(sint64(data.value.uint32));

        case CMPI_sint32:
            RETURN(sint64(data.value.sint32));

        case CMPI_uint64:
            RETURN(sint64(data.value.uint64));

        case CMPI_sint64:
            RETURN(sint64(data.value.sint64));

        default:
            RETURN(0);
    }
}

static bool _type_compatible(uint16 type1, uint16 type2)
{
    RETURN((type1 == type2) || (is_integer[type1] && is_integer[type2]));
}

static CMPIrc _set_cimple_scalar_key(
    const Meta_Property* mp, 
    void* prop, 
    const CMPIData& data)
{
    // Scalar case:

    if (CMIsArray(data))
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Set null flag:

    if (data.state & CMPI_nullValue)
    {
        null_of(mp, prop) = 1;
        RETURN(CMPI_RC_OK);
    }
    else
        null_of(mp, prop) = 0;

    // Check for type compatibility:

    if (!_type_compatible(mp->type, _to_cimple_type(data.type)))
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Set value:

    switch(mp->type)
    {
        case cimple::BOOLEAN:
            *((cimple::boolean*)prop) = data.value.boolean;
            break;

        case UINT8:
            *((uint8*)prop) = _promote(data);
            break;

        case SINT8:
            *((sint8*)prop) = _promote(data);
            break;

        case UINT16:
            *((uint16*)prop) = _promote(data);
            break;

        case SINT16:
            *((sint16*)prop) = _promote(data);
            break;

        case cimple::UINT32:
            *((uint32*)prop) = _promote(data);
            break;

        case SINT32:
            *((sint32*)prop) = _promote(data);
            break;

        case cimple::UINT64:
            *((uint64*)prop) = _promote(data);
            break;

        case SINT64:
            *((sint64*)prop) = _promote(data);
            break;

        case STRING:
            *((String*)prop) = CMGetCharPtr(data.value.string);
            RETURN(CMPI_RC_OK);

        default:
            RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    RETURN(CMPI_RC_OK);
}

static CMPIrc _set_cimple_array(
    const Meta_Property* mp, 
    void* prop, 
    const CMPIData& data)
{
    // Scalar case:

    if (!CMIsArray(data))
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Set null flag:

    if (data.state & CMPI_nullValue)
    {
        null_of(mp, prop) = 1;
        RETURN(CMPI_RC_OK);
    }
    else
        null_of(mp, prop) = 0;

    // Check the type:

    if (CMGetArrayType(data.value.array, NULL) != _cmpi_type[mp->type])
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Get size of array and reserve memory in new array.

    CMPICount n = CMGetArrayCount(data.value.array, NULL);
    ((Array_Base*)prop)->reserve(n);

    // Reserve memory for n elements:

    switch(mp->type)
    {
        case cimple::BOOLEAN:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_boolean*)prop)->append(t.value.boolean);
            }

            break;
        }

        case UINT8:
        case SINT8:
        case UINT16:
        case SINT16:
        case cimple::UINT32:
        case SINT32:
        case cimple::UINT64:
        case SINT64:
        case REAL32:
        case REAL64:
        case CHAR16:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_Base*)prop)->append_raw(&t.value, 1);
            }

            break;
        }

        case STRING:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_String*)prop)->append(
                    CMGetCharPtr(t.value.string));
            }

            break;
        }

        case DATETIME:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                Datetime dt;

                if (!dt.set(
                    CMGetCharPtr(CMGetStringFormat(t.value.dateTime, NULL))))
                    RETURN(CMPI_RC_ERR_TYPE_MISMATCH);

                ((Array_Datetime*)prop)->append(dt);
            }

            break;
        }
    }

    RETURN(CMPI_RC_OK);
}

static CMPIrc _set_cimple_array_key(
    const Meta_Property* mp, 
    void* prop, 
    const CMPIData& data)
{
    // Scalar case:

    if (!CMIsArray(data))
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Set null flag:

    if (data.state & CMPI_nullValue)
    {
        null_of(mp, prop) = 1;
        RETURN(CMPI_RC_OK);
    }
    else
        null_of(mp, prop) = 0;

    // Get size of array and reserve memory in new array.

    CMPICount n = CMGetArrayCount(data.value.array, NULL);

    // Reserve memory for n elements:

    ((Array_Base*)prop)->reserve(n);

    // Check for type compatibility:

    CMPIType array_type = CMGetArrayType(data.value.array, NULL);

    if (!_type_compatible(mp->type, _to_cimple_type(array_type)))
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    // Assign the array values:

    switch(mp->type)
    {
        case cimple::BOOLEAN:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_boolean*)prop)->append(t.value.boolean);
            }
            break;
        }

        case UINT8:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_uint8*)prop)->append(_promote(t));
            }
            break;
        }

        case SINT8:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_sint8*)prop)->append(_promote(t));
            }
            break;
        }

        case UINT16:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_uint16*)prop)->append(_promote(t));
            }
            break;
        }

        case SINT16:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_sint16*)prop)->append(_promote(t));
            }
            break;
        }

        case cimple::UINT32:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_uint32*)prop)->append(_promote(t));
            }
            break;
        }

        case SINT32:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_sint32*)prop)->append(_promote(t));
            }
            break;
        }

        case cimple::UINT64:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_uint64*)prop)->append(_promote(t));
            }
            break;
        }

        case SINT64:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_sint64*)prop)->append(_promote(t));
            }
            break;
        }

        case STRING:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_String*)prop)->append(
                    CMGetCharPtr(t.value.string));
            }
        }
    }

    RETURN(CMPI_RC_OK);
}

static CMPIrc _set_cimple_property(
    Instance* instance,
    const Meta_Property* mp,
    const CMPIData& data)
{
    void* prop = (char*)instance + mp->offset;

    if (mp->subscript == 0)
        RETURN(_set_cimple_scalar(mp, prop, data));
    else
        RETURN(_set_cimple_array(mp, prop, data));
}

static CMPIrc _set_cimple_key_property(
    Instance* instance,
    const Meta_Property* mp,
    const CMPIData& data)
{
    void* prop = (char*)instance + mp->offset;

    if (mp->subscript == 0)
        RETURN(_set_cimple_scalar_key(mp, prop, data));
    else
        RETURN(_set_cimple_array_key(mp, prop, data));
}

static CMPIrc _set_cimple_reference(
    Instance* instance,
    const Meta_Reference* mr,
    const CMPIData& data)
{
    if (data.type != CMPI_ref)
    {
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
    }

    CMPIObjectPath* op = data.value.ref;
    Instance*& ref = reference_of(instance, mr);

    if (op)
        RETURN(make_cimple_reference(mr->meta_class, op, ref));

    ref = 0;
    RETURN(CMPI_RC_OK);
}

CMPIrc make_cimple_reference(
    const Meta_Class* mc,
    const CMPIObjectPath* op,
    Instance*& inst)
{
    // Create the instance:

    inst = create(mc);
    nullify_non_keys(inst);

    // For each property of the CMPI object path:

    for (size_t i = 0, n = CMGetKeyCount(op, NULL); i < n; i++)
    {
        // Get the CMPI data object:

        CMPIString* name;
        CMPIData data = CMGetKeyAt(op, i, &name, NULL);

        // Find the corresponding CIMPLE meta feature:

        const Meta_Feature* mf = find_feature(mc, CMGetCharPtr(name));

        if (!mf)
        {
            destroy(inst);
            inst = 0;
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
        }

        if (!(mf->flags & CIMPLE_FLAG_KEY))
        {
            destroy(inst);
            inst = 0;
            RETURN(CMPI_RC_ERR_TYPE_MISMATCH);
        }

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mf;
            CMPIrc rc = _set_cimple_key_property(inst, mp, data);

            if (rc != CMPI_RC_OK)
            {
                destroy(inst);
                inst = 0;
                RETURN(rc);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mf;
            CMPIrc rc = _set_cimple_reference(inst, mr, data);

            if (rc != CMPI_RC_OK)
            {
                destroy(inst);
                inst = 0;
                RETURN(rc);
            }
        }
    }

    RETURN(CMPI_RC_OK);
}

static CMPIDateTime* _to_cmpi_datetime(
    const CMPIBroker* broker, 
    const Datetime& x)
{
    char buf[Datetime::BUFFER_SIZE];
    x.ascii(buf);
    RETURN(CMNewDateTimeFromChars(broker, buf, NULL));
}

static CMPIString* _to_cmpi_string(
    const CMPIBroker* broker, 
    const String& x)
{
    RETURN(CMNewString(broker, x.c_str(), NULL));
}

static void _to_cmpi_value(
    const CMPIBroker* broker,
    const Meta_Property* mp,
    const void* prop,
    CMPIValue& value,
    CMPIType& type)
{
    type = _cmpi_type[mp->type];

    if (mp->subscript == 0)
    {
        if (is_raw[mp->type] && mp->type != cimple::BOOLEAN)
        {
            memcpy(&value, prop, type_size[mp->type]);
        }
        else switch (mp->type)
        {
            case cimple::BOOLEAN:
                value.boolean = *((cimple::boolean*)prop) ? 1 : 0;
                break;

            case STRING:
            {
                value.string = _to_cmpi_string(broker, *((String*)prop));
                break;
            }

            case DATETIME:
                value.dateTime = _to_cmpi_datetime(broker, *((Datetime*)prop));
                break;

            default:
                CIMPLE_ASSERT(0);
                break;
        }
    }
    else
    {
        const Array_Base* array = (const Array_Base*)prop;
        value.array = CMNewArray(broker, array->size(), type, NULL);

        if (is_raw[mp->type] && mp->type != cimple::BOOLEAN)
        {
            for (size_t i = 0; i < array->size(); i++)
                CMSetArrayElementAt(value.array, i, array->get_raw(i), type);
        }
        else switch (mp->type)
        {
            case cimple::BOOLEAN:
            {
                const Array_boolean& array = *((const Array_boolean*)prop);

                for (size_t i = 0; i < array.size(); i++)
                {
                    CMPIBoolean x = array[i] ? 1 : 0;
                    CMSetArrayElementAt(value.array, i, &x, type);
                }
                break;
            }

            case STRING:
            {
                const Array_String& array = *((const Array_String*)prop);

                for (size_t i = 0; i < array.size(); i++)
                {
                    CMPIString* tmp = _to_cmpi_string(broker, array[i]);
                    CMSetArrayElementAt(value.array, i, &tmp, type);
                }
                break;
            }

            case DATETIME:
            {
                const Array_Datetime& array = *((const Array_Datetime*)prop);

                for (size_t i = 0; i < array.size(); i++)
                {
                    CMPIDateTime* tmp = _to_cmpi_datetime(broker, array[i]);
                    CMSetArrayElementAt(value.array, i, &tmp, type);
                }
                break;
            }

            default:
                CIMPLE_ASSERT(0);
                break;
        }

        type |= CMPI_ARRAY;
    }
}

CMPIrc make_cmpi_object_path(
    const CMPIBroker* broker,
    const cimple::Instance* cimple_inst, 
    const char* name_space,
    CMPIObjectPath*& cmpi_op)
{
    const char* class_name = cimple_inst->meta_class->name;
    cmpi_op = CMNewObjectPath(broker, name_space, class_name, NULL);
    const Meta_Class* mc = cimple_inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        // Ignore non-keys:

        if (!(mf->flags & CIMPLE_FLAG_KEY))
            continue;

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            const void* prop = (const char*)cimple_inst + mp->offset;

            // Ignore null properties:

            if (!null_of(mp, prop))
            {
                CMPIValue value;
                CMPIType type;
                _to_cmpi_value(broker, mp, prop, value, type);
                CMAddKey(cmpi_op, mp->name, &value, type);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;
            const Instance* ref = reference_of(cimple_inst, mr);
            
            if (ref)
            {
                CMPIValue value;

                CMPIrc rc = make_cmpi_object_path(
                    broker, ref, name_space, value.ref);

                if (rc != CMPI_RC_OK)
                {
                    cmpi_op = 0;
                    RETURN(CMPI_RC_ERR_FAILED);
                }

                CMAddKey(cmpi_op, mr->name, &value, CMPI_ref);
            }
        }
    }

    RETURN(CMPI_RC_OK);
}

CMPIrc make_cmpi_instance(
    const CMPIBroker* broker,
    const Instance* cimple_inst, 
    const char* name_space,
    const CMPIObjectPath* cmpi_op,
    CMPIInstance*& cmpi_inst)
{
    cmpi_inst = 0;

    // If cmpi_op argument is null, create an object path from the instance.

    CMPIObjectPath* cop = 0;

    if (!cmpi_op)
    {
        make_cmpi_object_path(broker, cimple_inst, name_space, cop);
        cmpi_op = cop;
    }

    // Create a new instance:

    cmpi_inst = CMNewInstance(broker, cmpi_op, NULL);

    // ATTN: check that the properties that CMPI added to the object,
    // are compatible with the ones in the meta-data.

    const Meta_Class* mc = cimple_inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            const void* prop = (const char*)cimple_inst + mp->offset;

            // Ignore null properties:

            if (!null_of(mp, prop))
            {
                CMPIValue value;
                CMPIType type;
                _to_cmpi_value(broker, mp, prop, value, type);
                CMSetProperty(cmpi_inst, mp->name, &value, type);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;
            const Instance* ref = reference_of(cimple_inst, mr);
            
            if (ref)
            {
                CMPIValue value;

                CMPIrc rc = make_cmpi_object_path(
                    broker, ref, name_space, value.ref);

                if (rc != CMPI_RC_OK)
                {
                    cmpi_inst = 0;
                    RETURN(CMPI_RC_ERR_FAILED);
                }

                CMSetProperty(cmpi_inst, mr->name, &value, CMPI_ref);
            }
        }
    }

    RETURN(CMPI_RC_OK);
}

int filter_properties(Instance* instance, const char* const* properties)
{
    // If properties is non-null, all properties in the list are set non-null
    // and all properties not in the list are set to null. If properties is
    // null, all properties are set to non-null. Key properties are never
    // nullified whether they are absent from the properties array or not.

    CIMPLE_ASSERT(instance != 0);
    CIMPLE_ASSERT(instance->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = instance->meta_class;

    // Handle case where properties null.

    if (!properties)
    {
        de_nullify_properties(instance);
        RETURN(0);
    }

    // Handle case where properties is non-null.

    nullify_non_keys(instance);

    while (*properties)
    {
        // Find the property:

        const Meta_Feature* mf = find_feature(mc, *properties++);

        if (!mf)
        {
            // No such property!
            RETURN(-1);
        }

        // Skip keys:

        if (mf->flags & CIMPLE_FLAG_KEY)
            continue;

        // Validate the property:

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            null_of(mp, property_of(instance, mp)) = 0;
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;
            Instance*& ref = reference_of(instance, mr);

            if (!ref)
                ref = create(mr->meta_class);
        }
        else
        {
            // Must be a method!
            RETURN(-1);
        }
    }

    RETURN(0);
}

CMPIrc make_cimple_instance(
    const cimple::Meta_Class* mc,
    const CMPIInstance* cmpi_inst,
    Instance*& cimple_inst_out)
{
    cimple_inst_out = 0;

    // Create the instance:

    Instance* cimple_inst = create(mc);
    Destroyer<Instance> cimple_inst_d(cimple_inst);

    // For each property of the CMPI instance.

    for (size_t i = 0, n = CMGetPropertyCount(cmpi_inst, NULL); i < n; i++)
    {
        // Get the CMPI data object:

        CMPIString* name;
        CMPIData data = CMGetPropertyAt(cmpi_inst, i, &name, NULL);

        // Find the corresponding CIMPLE meta feature:

        const Meta_Feature* mf = find_feature(mc, CMGetCharPtr(name));

        if (!mf)
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);

        // Set the feature:

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mf;
            CMPIrc rc = _set_cimple_property(cimple_inst, mp, data);

            if (rc != CMPI_RC_OK)
                RETURN(rc);
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mf;
            CMPIrc rc = _set_cimple_reference(cimple_inst, mr, data);

            if (rc != CMPI_RC_OK)
                RETURN(rc);
        }
        else
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
    }

    cimple_inst_out = cimple_inst_d.steal();
    RETURN(CMPI_RC_OK);
}

CMPIrc make_method(
    const Meta_Method* mm,
    const CMPIArgs* in,
    Instance*& cimple_meth)
{
    // ATTN: are some argument required in the model?

    cimple_meth = 0;

    Instance* meth = create(mm);
    nullify_properties(meth);
    Destroyer<Instance> meth_d(meth);

    for (size_t i = 0, n = CMGetArgCount(in, NULL); i < n; i++)
    {
        CMPIString* name;
        CMPIData data = CMGetArgAt(in, i, &name, NULL);

        const Meta_Feature* mf = find_feature(mm, CMGetCharPtr(name));

        if (!mf)
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);

        if (!(mf->flags & CIMPLE_FLAG_IN))
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mf;
            CMPIrc rc = _set_cimple_property(meth, mp, data);

            if (rc != CMPI_RC_OK)
                RETURN(rc);
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mf;
            CMPIrc rc = _set_cimple_reference(meth, mr, data);

            if (rc != CMPI_RC_OK)
                RETURN(rc);
        }
        else
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
    }

    cimple_meth = meth_d.steal();
    RETURN(CMPI_RC_OK);
}

CMPIrc make_method_out(
    const CMPIBroker* broker,
    const char* name_space,
    const Instance* cimple_meth,
    const CMPIArgs* out,
    CMPIValue& RETURN_value,
    CMPIType& RETURN_type)
{
    const Meta_Method* mm = (const Meta_Method*)cimple_meth->meta_class;

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
        const Meta_Feature* mf = mm->meta_features[i];

        // Ignore non-out-args:

        if (!(mf->flags & CIMPLE_FLAG_OUT))
            continue;

        // Add the feature to the CMPI object:

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            const void* prop = (const char*)cimple_meth + mp->offset;

            CMPIValue value;
            CMPIType type;
            _to_cmpi_value(broker, mp, prop, value, type);

            if (strcasecmp(mp->name, "RETURN_value") == 0)
            {
                RETURN_value = value;
                RETURN_type = type;
            }
            else
                CMAddArg(out, mp->name, &value, type);
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;
            const Instance* ref = reference_of(cimple_meth, mr);
            
            if (ref)
            {
                CMPIValue value;

                CMPIrc rc = make_cmpi_object_path(
                    broker, ref, name_space, value.ref);

                if (rc != CMPI_RC_OK)
                    RETURN(CMPI_RC_ERR_FAILED);

                CMAddArg(out, mr->name, &value, CMPI_ref);
            }
            else
            {
                // ATTN: add a null reference anyway?
            }
        }
    }

    RETURN(CMPI_RC_OK);
}

/*  TO DO:

    1.  check class name consistency between CIMPLE and CMPI.
    2.  revisit filtering of RETURN instances (use the model).
*/
