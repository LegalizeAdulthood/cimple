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

#include <cassert>
#include <cstring>
#include <cimple/Strings.h>
#include "Converter.h"

//==============================================================================
//
// RETURN(X)
//
//     Return tracing macro.
//
//==============================================================================

#if 0
# define RETURN(X) \
    do \
    { \
        printf("RETURN(%s): %s(%d)\n", #X, __FILE__, __LINE__); \
        return X; \
    } \
    while (0)
#else
# define RETURN(X) return(X)
#endif

// ATTN: handle embedded object properties (for indications).

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// set_cmpi_error()
//
//==============================================================================

const char* rc_to_str(CMPIrc rc)
{
    switch (rc)
    {
        case CMPI_RC_OK:
            return "CMPI_RC_OK";
        case CMPI_RC_ERR_FAILED:
            return "CMPI_RC_ERR_FAILED";
        case CMPI_RC_ERR_ACCESS_DENIED:
            return "CMPI_RC_ERR_ACCESS_DENIED";
        case CMPI_RC_ERR_INVALID_NAMESPACE:
            return "CMPI_RC_ERR_INVALID_NAMESPACE";
        case CMPI_RC_ERR_INVALID_PARAMETER:
            return "CMPI_RC_ERR_INVALID_PARAMETER";
        case CMPI_RC_ERR_INVALID_CLASS:
            return "CMPI_RC_ERR_INVALID_CLASS";
        case CMPI_RC_ERR_NOT_FOUND:
            return "CMPI_RC_ERR_NOT_FOUND";
        case CMPI_RC_ERR_NOT_SUPPORTED:
            return "CMPI_RC_ERR_NOT_SUPPORTED";
        case CMPI_RC_ERR_CLASS_HAS_CHILDREN:
            return "CMPI_RC_ERR_CLASS_HAS_CHILDREN";
        case CMPI_RC_ERR_CLASS_HAS_INSTANCES:
            return "CMPI_RC_ERR_CLASS_HAS_INSTANCES";
        case CMPI_RC_ERR_INVALID_SUPERCLASS:
            return "CMPI_RC_ERR_INVALID_SUPERCLASS";
        case CMPI_RC_ERR_ALREADY_EXISTS:
            return "CMPI_RC_ERR_ALREADY_EXISTS";
        case CMPI_RC_ERR_NO_SUCH_PROPERTY:
            return "CMPI_RC_ERR_NO_SUCH_PROPERTY";
        case CMPI_RC_ERR_TYPE_MISMATCH:
            return "CMPI_RC_ERR_TYPE_MISMATCH";
        case CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED:
            return "CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED";
        case CMPI_RC_ERR_INVALID_QUERY:
            return "CMPI_RC_ERR_INVALID_QUERY";
        case CMPI_RC_ERR_METHOD_NOT_AVAILABLE:
            return "CMPI_RC_ERR_METHOD_NOT_AVAILABLE";
        case CMPI_RC_ERR_METHOD_NOT_FOUND:
            return "CMPI_RC_ERR_METHOD_NOT_FOUND";
        case CMPI_RC_DO_NOT_UNLOAD:
            return "CMPI_RC_DO_NOT_UNLOAD";
        case CMPI_RC_NEVER_UNLOAD:
            return "CMPI_RC_NEVER_UNLOAD";
        case CMPI_RC_ERR_INVALID_HANDLE:
            return "CMPI_RC_ERR_INVALID_HANDLE";
        case CMPI_RC_ERR_INVALID_DATA_TYPE:
            return "CMPI_RC_ERR_INVALID_DATA_TYPE";
        case CMPI_RC_ERROR_SYSTEM:
            return "CMPI_RC_ERROR_SYSTEM";
        case CMPI_RC_ERROR:
            return "CMPI_RC_ERROR";
    }

    return NULL;
}

void set_cmpi_error(const CMPIrc &rc, const char* msg)
{
    Error::set("%s: %s", rc_to_str(rc), msg);
}

void set_cmpi_error(const CMPIStatus &status)
{
    if (status.msg)
        set_cmpi_error(status.rc, char_ptr(status.msg));
    else
        set_cmpi_error(status.rc, 0);
}

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
        case CMPI_boolean: return cimple::BOOLEAN ;
        case CMPI_uint8: return UINT8 ;
        case CMPI_sint8: return SINT8 ;
        case CMPI_uint16: return UINT16 ;
        case CMPI_sint16: return SINT16 ;
        case CMPI_uint32: return cimple::UINT32 ;
        case CMPI_sint32: return SINT32 ;
        case CMPI_uint64: return cimple::UINT64 ;
        case CMPI_sint64: return SINT64 ;
        case CMPI_real32: return REAL32 ;
        case CMPI_real64: return REAL64 ;
        case CMPI_char16: return CHAR16 ;
        case CMPI_string: return STRING ;
        case CMPI_dateTime: return DATETIME ;
        default: return 0 ;
    }
}

static char _is_integer[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, };

static char _is_raw[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, };


static CMPIrc _set_cimple_scalar(
    const Meta_Property* mp, 
    void* prop, 
    const CMPIData& data)
{
    // Scalar case:

    if (CMIsArray(data))
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);

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

    if (_is_raw[mp->type] && mp->type != cimple::BOOLEAN)
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
            *((String*)prop) = char_ptr(data.value.string);
            break;

        case DATETIME:
            ((Datetime*)prop)->set(
                char_ptr(CMGetStringFormat(data.value.dateTime, NULL)));
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
            return sint64(data.value.uint8);

        case CMPI_sint8:
            return sint64(data.value.sint8);

        case CMPI_uint16:
            return sint64(data.value.uint16);

        case CMPI_sint16:
            return sint64(data.value.sint16);

        case CMPI_uint32:
            return sint64(data.value.uint32);

        case CMPI_sint32:
            return sint64(data.value.sint32);

        case CMPI_uint64:
            return sint64(data.value.uint64);

        case CMPI_sint64:
            return sint64(data.value.sint64);

        default:
            return 0;
    }
}

static bool _type_compatible(uint16 type1, uint16 type2)
{
    return (type1 == type2) || (_is_integer[type1] && _is_integer[type2]);
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
            *((String*)prop) = char_ptr(data.value.string);
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
    __reserve(((__Array_Base*)prop)->rep, n);

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
                __append(((__Array_Base*)prop)->rep, &t.value, 1);
            }

            break;
        }

        case STRING:
        {
            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData t = CMGetArrayElementAt(data.value.array, i, NULL);
                ((Array_String*)prop)->append(
                    char_ptr(t.value.string));
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
                    char_ptr(CMGetStringFormat(t.value.dateTime, NULL))))
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

    __reserve(((__Array_Base*)prop)->rep, n);

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
                    char_ptr(t.value.string));
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
    Instance*& ref = __ref_of(instance, mr);

    if (op)
        RETURN(make_cimple_reference(mr->meta_class, op, ref));

    ref = 0;
    RETURN(CMPI_RC_OK);
}

static CMPIrc _append_cimple_reference(
    Instance* inst,
    const Meta_Reference* mr,
    const CMPIData& data,
    bool clear)
{
    if (data.type != CMPI_ref)
        RETURN(CMPI_RC_ERR_TYPE_MISMATCH);

    Array_Ref& ref = __array_ref_of(inst, mr);

    if (clear)
        ref.clear();

    if (data.value.ref)
    {
        Instance* r = 0;
        CMPIrc rc = make_cimple_reference(mr->meta_class, data.value.ref, r);
        
        if (rc != CMPI_RC_OK)
            RETURN(CMPI_RC_ERR_FAILED);

        ref.append(r);
    }
    else
        ref.append(0);

    RETURN(CMPI_RC_OK);
}

CMPIrc make_cimple_reference(
    const Meta_Class* mc,
    const CMPIObjectPath* op,
    Instance*& inst)
{
    Error::clear();

    // Create the instance:

    inst = create(mc);
    nullify_properties(inst);

    // Set the namespace if the CMPI object path has one.

    CMPIString* ns = CMGetNameSpace(op, NULL);

    if (ns)
        inst->__name_space = char_ptr(ns);

    // For each property of the CMPI object path:

    for (size_t i = 0, n = CMGetKeyCount(op, NULL); i < n; i++)
    {
        // Get the CMPI data object:

        CMPIString* name;
        CMPIData data = CMGetKeyAt(op, i, &name, NULL);

        // Find the corresponding CIMPLE meta feature:

        const Meta_Feature* mf = find_feature(mc, char_ptr(name));

        if (!mf)
        {
            // Ignore properties that appear in the source class but not
            // in the target class. These properties may be introduced by
            // subclasses or by newer versions.
            continue;
        }

        if (!(mf->flags & CIMPLE_FLAG_KEY))
        {
            destroy(inst);
            inst = 0;
            set_cmpi_error(
                CMPI_RC_ERR_TYPE_MISMATCH, "make_cimple_reference()");
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
                set_cmpi_error(rc, "make_cimple_reference()");
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
                set_cmpi_error(rc, "make_cimple_reference()");
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
        if (_is_raw[mp->type] && mp->type != cimple::BOOLEAN)
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
        const __Array_Base* array = (const __Array_Base*)prop;
        value.array = CMNewArray(broker, array->rep->size, type, NULL);

        if (_is_raw[mp->type] && mp->type != cimple::BOOLEAN)
        {
            for (size_t i = 0, n = array->rep->size; i < n; i++)
                CMSetArrayElementAt(value.array, i, __at(array->rep, i), type);
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
    Error::clear();

    const char* class_name = cimple_inst->meta_class->name;

    const char* real_name_space;

    if (cimple_inst->__name_space.size())
        real_name_space = cimple_inst->__name_space.c_str();
    else
        real_name_space = name_space;

    CMPIStatus status;
    cmpi_op = CMNewObjectPath(broker, real_name_space, class_name, &status);

    if (cmpi_op == 0 || status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
        RETURN(status.rc);
    }

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
            const Instance* ref = __ref_of(cimple_inst, mr);
            
            if (ref)
            {
                CMPIValue value;

                CMPIrc rc = make_cmpi_object_path(
                    broker, ref, real_name_space, value.ref);

                if (rc != CMPI_RC_OK)
                {
                    cmpi_op = 0;
                    // Propagate error of make_cmpi_object_path().
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
    Error::clear();

    cmpi_inst = 0;

    // If cmpi_op argument is null, create an object path from the instance.

    CMPIObjectPath* cop = 0;

    if (!cmpi_op)
    {
        make_cmpi_object_path(broker, cimple_inst, name_space, cop);
        cmpi_op = cop;
    }

    // Create a new instance:

    CMPIStatus status;
    cmpi_inst = CMNewInstance(broker, cmpi_op, &status);

    if (cmpi_inst == 0 || status.rc != CMPI_RC_OK)
    {
        set_cmpi_error(status);
        RETURN(status.rc);
    }

    // ATTN: check that the properties that CMPI added to the object,
    // are compatible with the ones in the meta-data.

    const Meta_Class* mc = cimple_inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;
            const Instance* inst = __ref_of(cimple_inst, mr);

            if (inst)
            {
                CMPIValue v;

                if (make_cmpi_instance(
                    broker, inst, name_space, 0, v.inst) == CMPI_RC_OK)
                {
                    CMSetProperty(cmpi_inst, mr->name, &v, CMPI_instance);
                }
            }
        }
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
            const Instance* ref = __ref_of(cimple_inst, mr);
            
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

CMPIrc make_cimple_instance(
    const cimple::Meta_Class* mc,
    const CMPIInstance* cmpi_inst,
    Instance*& cimple_inst_out)
{
    Error::clear();

    cimple_inst_out = 0;

    // Create the instance:

    Instance* cimple_inst = create(mc);
    nullify_properties(cimple_inst);
    Ref<Instance> cimple_inst_d(cimple_inst);

    // For each property of the CMPI instance.

    for (size_t i = 0, n = CMGetPropertyCount(cmpi_inst, NULL); i < n; i++)
    {
        // Get the CMPI data object:

        CMPIString* name;
        CMPIData data = CMGetPropertyAt(cmpi_inst, i, &name, NULL);

        // Find the corresponding CIMPLE meta feature:

        const Meta_Feature* mf = find_feature(mc, char_ptr(name));

        if (!mf)
        {
            // Ignore properties that appear in the source class but not
            // in the target class. These properties may be introduced by
            // subclasses or by newer versions.
            continue;
        }

        // Set the feature:

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mf;
            CMPIrc rc = _set_cimple_property(cimple_inst, mp, data);

            if (rc != CMPI_RC_OK)
            {
                set_cmpi_error(rc, "make_cimple_instance()");
                RETURN(rc);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mf;
            CMPIrc rc = _set_cimple_reference(cimple_inst, mr, data);

            if (rc != CMPI_RC_OK)
            {
                set_cmpi_error(rc, "make_cimple_instance()");
                RETURN(rc);
            }
        }
        else
        {
            set_cmpi_error(
                CMPI_RC_ERR_NO_SUCH_PROPERTY, "make_cimple_instance()");
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
        }
    }

    cimple_inst_out = cimple_inst_d.steal();
    RETURN(CMPI_RC_OK);
}

CMPIrc make_method(
    const Meta_Method* mm,
    const CMPIArgs* in,
    const Meta_Class* find_meta_class(const char*, void*),
    void* client_data,
    Instance*& meth_out)
{
    Error::clear();

    // ATTN: are some arguments required in the model?

    meth_out = 0;

    Instance* meth = create(mm);
    nullify_properties(meth);
    Ref<Instance> meth_d(meth);

    for (size_t i = 0, n = CMGetArgCount(in, NULL); i < n; i++)
    {
        CMPIString* name;
        CMPIData data = CMGetArgAt(in, i, &name, NULL);

        const Meta_Feature* mf = find_feature(mm, char_ptr(name));

        if (!mf)
        {
            set_cmpi_error(
                CMPI_RC_ERR_NO_SUCH_PROPERTY, "make_method()");
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
        }

        if (!(mf->flags & CIMPLE_FLAG_IN))
        {
            set_cmpi_error(
                CMPI_RC_ERR_NO_SUCH_PROPERTY, "make_method()");
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
        }

        if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mf;
            CMPIrc rc = _set_cimple_property(meth, mp, data);

            if (rc != CMPI_RC_OK)
            {
                set_cmpi_error(rc, "make_method()");
                RETURN(rc);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = ((const Meta_Reference*)mf);

            // Raise error if not a reference type.

            if (!(data.type & CMPI_ref))
            {
                set_cmpi_error(CMPI_RC_ERR_FAILED, "type mismatch");
                RETURN(CMPI_RC_ERR_FAILED);
            }

            if (CMIsArray(data))
            {
                if (mr->subscript == 0)
                    RETURN(CMPI_RC_ERR_TYPE_MISMATCH);

                CMPICount n = CMGetArrayCount(data.value.array, NULL);

                for (CMPICount i = 0; i < n; i++)
                {
                    Meta_Reference tmp_mr = *mr;
                    CMPIData td = CMGetArrayElementAt(data.value.array, i,NULL);

                    const Meta_Class* mc = 0;
                    
                    if (td.value.ref)
                    {
                        mc = find_meta_class(
                            class_name(td.value.ref), client_data);
                    }

                    if (mc)
                        tmp_mr.meta_class = mc;

                    CMPIrc rc = _append_cimple_reference(
                        meth, &tmp_mr, td, i == 0);

                    if (rc != CMPI_RC_OK)
                        RETURN(rc);
                }
            }
            else if (data.value.ref)
            {
                if (mr->subscript != 0)
                    RETURN(CMPI_RC_ERR_TYPE_MISMATCH);

                Meta_Reference tmp_mr = *mr;

                const Meta_Class* mc = find_meta_class(
                    class_name(data.value.ref), client_data);

                if (mc)
                    tmp_mr.meta_class = mc;

                CMPIrc rc = _set_cimple_reference(meth, &tmp_mr, data);

                if (rc != CMPI_RC_OK)
                {
                    set_cmpi_error(rc, "make_method()");
                    RETURN(rc);
                }
            }
        }
        else
        {
            set_cmpi_error(CMPI_RC_ERR_NO_SUCH_PROPERTY, "make_method()");
            RETURN(CMPI_RC_ERR_NO_SUCH_PROPERTY);
        }
    }

    meth_out = meth_d.steal();
    RETURN(CMPI_RC_OK);
}

static CMPIrc _to_cmpi_ref_array(
    const CMPIBroker* broker,
    const char* ns,
    const Array_Ref& r,
    CMPIValue& value)
{
    value.array = CMNewArray(broker, r.size(), CMPI_ref, NULL);

    for (size_t i = 0; i < r.size(); i++)
    {
        const Instance* ref = r[i];

        CMPIValue tmp;
        memset(&tmp, 0, sizeof(tmp));

        if (ref)
        {
            const char* tns = ns;

            if (ref->__name_space.size())
                tns = ref->__name_space.c_str();

            CMPIrc rc = make_cmpi_object_path(broker, ref, tns, tmp.ref);

            if (rc != CMPI_RC_OK)
                RETURN(CMPI_RC_ERR_FAILED);
        }
        else
        {
            set_cmpi_error(CMPI_RC_ERR_FAILED, "encountered null reference");
            RETURN(CMPI_RC_ERR_FAILED);
        }

        CMSetArrayElementAt(value.array, i, &tmp, CMPI_ref);
    }

    RETURN(CMPI_RC_OK);
}

CMPIrc make_method_out(
    const CMPIBroker* broker,
    const char* name_space,
    const Instance* cimple_meth,
    const CMPIArgs* out,
    CMPIValue& return_value,
    CMPIType& return_type)
{
    Error::clear();

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

            if (strcasecmp(mp->name, "return_value") == 0)
            {
                return_value = value;
                return_type = type;
            }
            else
                CMAddArg(out, mp->name, &value, type);
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;

            if (mr->subscript)
            {
                const Array_Ref& r = __array_ref_of(cimple_meth, mr);
                CMPIValue value;
                CMPIrc rc = _to_cmpi_ref_array(broker, name_space, r, value);

                if (rc != CMPI_RC_OK)
                    RETURN(rc);

                CMAddArg(out, mr->name, &value, CMPI_ref | CMPI_ARRAY);
            }
            else
            {
                const Instance* ref = __ref_of(cimple_meth, mr);
                
                if (ref)
                {
                    CMPIValue value;

                    CMPIrc rc = make_cmpi_object_path(
                        broker, ref, name_space, value.ref);

                    if (rc != CMPI_RC_OK)
                    {
                        // Propagate make_cmpi_object_path() error.
                        RETURN(CMPI_RC_ERR_FAILED);
                    }

                    CMAddArg(out, mr->name, &value, CMPI_ref);
                }
            }
        }
    }

    RETURN(CMPI_RC_OK);
}

static const char* type_name_of(CMPIType type)
{
    switch(type & ~CMPI_ARRAY)
    {
        case CMPI_boolean:
            return "boolean";
        case CMPI_uint8:
            return "uint8";
        case CMPI_sint8:
            return "sint8";
        case CMPI_uint16:
            return "uint16";
        case CMPI_sint16:
            return "sint16";
        case CMPI_uint32:
            return "uint32";
        case CMPI_sint32:
            return "sint32";
        case CMPI_uint64:
            return "uint64";
        case CMPI_sint64:
            return "sint64";
        case CMPI_real32:
            return "real32";
        case CMPI_real64:
            return "real64";
        case CMPI_char16:
            return "char16";
        case CMPI_string:
            return "string";
        case CMPI_dateTime:
            return "datetime";
        case CMPI_ref:
            return "ref";
        default:
            printf("[%d]\n", type);
            assert(0);
    }

    return "<unknown>";
}

void print_scalar(const CMPIData& data)
{
    switch(data.type)
    {
        case CMPI_boolean:
            printf("\"%s\"", data.value.boolean ? "true" : "false");
            break;

        case CMPI_uint8:
            printf("%u", data.value.uint8);
            break;

        case CMPI_sint8:
            printf("%d", data.value.sint8);
            break;

        case CMPI_uint16:
            printf("%u", data.value.uint16);
            break;

        case CMPI_sint16:
            printf("%d", data.value.sint16);
            break;

        case CMPI_uint32:
            printf("%u", data.value.uint32);
            break;

        case CMPI_sint32:
            printf("%d", data.value.sint32);
            break;

        case CMPI_uint64:
            printf("%llu", data.value.uint64);
            break;

        case CMPI_sint64:
            printf("%lld", data.value.sint64);
            break;

        case CMPI_real32:
            printf("%f", data.value.real32);
            break;

        case CMPI_real64:
            printf("%lf", data.value.real64);
            break;

        case CMPI_char16:
            printf("%u", data.value.char16);
            break;

        case CMPI_string:
            printf("%s", char_ptr(data.value.string));
            break;

        case CMPI_dateTime:
        {
            CMPIString* tmp = CMGetStringFormat(data.value.dateTime, NULL);
            printf("%s", char_ptr(tmp));
            break;
        }

        case CMPI_ref:
        {
            print(data.value.ref);
            break;
        }

        default:
            assert(0);
            break;
    }
}

void print(const CMPIData& data)
{
    if (data.state & CMPI_nullValue)
    {
        printf("null");
        return;
    }

    if (CMIsArray(data))
    {
        printf("{");

        CMPICount n = CMGetArrayCount(data.value.array, NULL);

        for (CMPICount i = 0; i < n; i++)
        {
            CMPIData td = CMGetArrayElementAt(data.value.array, i, NULL);
            print_scalar(td);

            if (i + 1 != n)
                printf(",");
        }

        printf("}");
    }
    else
        print_scalar(data);
}

void print(const CMPIObjectPath* op)
{
    printf("CMPIObjectPath\n");
    printf("{\n");

    printf("    name_space: \"%s\"\n", name_space(op));
    printf("    class_name: \"%s\"\n", class_name(op));
    printf("    host_name: \"%s\"\n", host_name(op));
    printf("    ---\n");

    for (size_t i = 0, n = CMGetKeyCount(op, NULL); i < n; i++)
    {
        CMPIString* name;
        CMPIData data = CMGetKeyAt(op, i, &name, NULL);

        printf("    %s(%s): ", char_ptr(name), type_name_of(data.type));
        print(data);
        putchar('\n');
    }

    printf("}\n");
}

void print(const CMPIInstance* inst)
{
    printf("CMPIInstance\n");
    printf("{\n");

    for (size_t i = 0, n = CMGetPropertyCount(inst, NULL); i < n; i++)
    {
        CMPIString* name;
        CMPIData data = CMGetPropertyAt(inst, i, &name, NULL);

        if (data.type == 0)
        {
            // FIXME: for some reason the data type is zero here. Embedded
            // object types are not converted correctly here.
            continue;
        }

        printf("    %s(%s): ", char_ptr(name), type_name_of(data.type));
        print(data);
        putchar('\n');
    }

    printf("}\n");
}

CIMPLE_NAMESPACE_END

/*  TO DO:

    1.  check class name consistency between CIMPLE and CMPI.
    2.  revisit filtering of return instances (use the model).
*/

CIMPLE_ID("$Header: /home/cvs/cimple/src/cmpi/adapter/Converter.cpp,v 1.36 2007/04/24 21:21:58 mbrasher-public Exp $");
