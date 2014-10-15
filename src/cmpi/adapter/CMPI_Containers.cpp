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
#include <cimple/integer.h>
#include "CMPI_Containers.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local routines:
//
//==============================================================================

static void _release(Array<Instance*>& a)
{
    for (size_t i = 0; i < a.size(); i++)
        unref(a[i]);
}

static inline const char* _c_str(const CMPIString* str)
{
    const char* s = CMGetCharsPtr(str, NULL);
    return s ? s : "";
}

template<class T>
struct to_cimple_scalar
{
};

template<> 
struct to_cimple_scalar<boolean>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, boolean& x) 
    {
        x = boolean(v.boolean);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<uint8>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, uint8& x) 
    {
        x = uint8(v.uint8);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<sint8>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, sint8& x) 
    {
        x = sint8(v.sint8);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<uint16>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, uint16& x) 
    {
        x = uint16(v.uint16);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<sint16>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, sint16& x) 
    {
        x = sint16(v.sint16);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<uint32>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, uint32& x) 
    {
        x = uint32(v.uint32);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<sint32>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, sint32& x) 
    {
        x = sint32(v.sint32);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<uint64>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, uint64& x) 
    {
        x = uint64(v.uint64);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<sint64>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, sint64& x) 
    {
        x = sint64(v.sint64);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<real32>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, real32& x) 
    {
        x = real32(v.real32);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<real64>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, real64& x) 
    {
        x = real64(v.real64);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<char16>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, char16& x) 
    {
        x = char16(v.char16);
        return 0;
    }
};

template<> 
struct to_cimple_scalar<Datetime>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, Datetime& x)
    {
        CMPIStatus status;
        CMPIString* s = CMGetStringFormat(v.dateTime, &status);

        if (status.rc != CMPI_RC_OK)
        {
            CIMPLE_WARN(("CMGetStringFormat() failed"));
            return -1;
        }

        if (!x.set(_c_str(CMGetStringFormat(v.dateTime, NULL))))
        {
            CIMPLE_WARN(("conversion error"));
            return -1;
        }

        return 0;
    }
};

template<> 
struct to_cimple_scalar<String>
{
    static int func(const Meta_Repository* mr, const CMPIValue& v, String& x)
    {
        x.clear();

        if (!v.string)
        {
            CIMPLE_INFO(("ignored null CMPI string"));
            return 0;
        }

        const char* s = CMGetCharsPtr(v.string, NULL);

        if (!s)
        {
            CIMPLE_WARN(("CMGetCharsPtr() failed"));
            return 0;
        }

        x = s;
        return 0;
    }
};

template<class T>
struct to_cimple_array_value
{
    static int func(const Meta_Repository* mr, const CMPIData& data, Value& v)
    {
        Array<T> x;

        //if (data.state & CMPI_nullValue)
        if (CMIsNullValue(data))
        {
            v.set_value(x);
            v.null(true);
            return 0;
        }

        if (!data.value.array)
        {
            return -1;
        }

        CMPICount n = CMGetArrayCount(data.value.array, NULL);
        //CIMPLE_DBG(("Convert to cimple array size %u", n));

        for (CMPICount i = 0; i < n; i++)
        {
            CMPIData tmp = CMGetArrayElementAt(data.value.array, i, NULL);

            if (tmp.type != (~CMPI_ARRAY & data.type))
            {
                CIMPLE_WARN(("type mismatch"));
                return -1;
            }

            //if (tmp.state & CMPI_nullValue)
            if (CMIsNullValue(tmp))
            {
                CIMPLE_WARN(("encountered null array element"));
                return -1;
            }

            T t;

            if (to_cimple_scalar<T>::func(mr, tmp.value, t) != 0)
            {
                CIMPLE_WARN(("conversion error"));
                return -1;
            }

            x.append(t);
        }

        v.set_value(x);
        return 0;
    }
};

template<class T>
struct to_cimple_scalar_value
{
    static int func(const Meta_Repository* mr, const CMPIData& data, Value& v)
    {
        v.clear();
        T x;

        if (to_cimple_scalar<T>::func(mr, data.value, x) != 0)
        {
            CIMPLE_WARN(("conversion error"));
            return -1;
        }

        v.set_value(x);
        //v.null(data.state & CMPI_nullValue);
        v.null(CMIsNullValue(data));
        return 0;
    }
};

static Instance* _to_cimple_instance(
    const Meta_Repository* mr,
    const CMPIBroker* cb,
    const char* ns,
    CMPIObjectPath* cop)
{
    if (!cop)
    {
        CIMPLE_WARN(("null instance"));
        return 0;
    }

    CMPIString* cn = CMGetClassName(cop, NULL);

    if (!cn)
    {
        CIMPLE_WARN(("CMGetClassName() failed"));
        return 0;
    }

    const Meta_Class* mc = find_meta_class(mr, _c_str(cn));

    if (!mc)
    {
        CIMPLE_WARN(("failed to find meta class: %s", _c_str(cn)));
        return 0;
    }

    Instance* inst = 0;

    CMPIObjectPath_Container cont(mr, cb, ns, cop);
    
    if (cont.convert(mc, CIMPLE_FLAG_KEY, inst) != 0 || !inst)
        return 0;

    return inst;
}

static Instance* _to_cimple_instance(
    const Meta_Repository* mr,
    const CMPIBroker* cb,
    const char* ns,
    CMPIInstance* ci)
{
    if (!ci)
    {
        return 0;
    }
    //CIMPLE_DBG(("_to_cimple_instance Enter"));
    CMPIObjectPath* cop = CMGetObjectPath(ci, NULL);

    if (!cop)
    {
        CIMPLE_WARN(("CMGetObjectPath() failed"));
        return 0;
    }

    CMPIString* cn = CMGetClassName(cop, NULL);

    if (!cn)
    {
        CIMPLE_WARN(("CMGetClassName() failed"));
        return 0;
    }
    //CIMPLE_DBG(("KS TRACE ClassName=%s", _c_str(cn)));
    const Meta_Class* mc = find_meta_class(mr, _c_str(cn));

    if (!mc)
    {
        CIMPLE_WARN(("failed to find meta class: %s", _c_str(cn)));
        return 0;
    }

    CMPIInstance_Container cont(mr, cb, ns, ci);
    
    Instance* inst = 0;

    //CIMPLE_DBG(("KS TRACE before convert ClassName=%s", _c_str(cn)));
    if (cont.convert(mc, 0, inst) != 0 || !inst)
        return 0;

    //CIMPLE_DBG(("KS TRACE before convert ClassName=%s", _c_str(cn)));
    //print(inst);
    return inst;
}

int cmpi_to_cimple_value(
    const Meta_Repository* mr,
    const CMPIBroker* cb,
    const char* ns,
    const CMPIData& data,
    Value& v)
{
    // Handle nulls up-front:

    //CIMPLE_DBG(("cmpi_to_cimple_value Enter state %X", data.state));
    // TODO - Should be CMIsNullValue(data)  // from cmpimacs.h
    //if (data.state & CMPI_nullValue)
    if (CMIsNullValue(data))
    {
        //CIMPLE_DBG(("cmpi_to_cimple_value Enter NULL Process %X", data.state & CMPI_nullValue));
        switch (data.type)
        {
            case CMPI_boolean:
                v.set_value((boolean)0);
                break;

            case CMPI_uint8:
                v.set_value((uint8)0);
                break;

            case CMPI_sint8:
                v.set_value((sint8)0);
                break;

            case CMPI_uint16:
                v.set_value((uint16)0);
                break;

            case CMPI_sint16:
                v.set_value((sint16)0);
                break;

            case CMPI_uint32:
                v.set_value((uint32)0);
                break;

            case CMPI_sint32:
                v.set_value((sint32)0);
                break;

            case CMPI_uint64:
                v.set_value((uint64)0);
                break;

            case CMPI_sint64:
                v.set_value((sint64)0);
                break;

            case CMPI_real32:
                v.set_value((real32)0);
                break;

            case CMPI_real64:
                v.set_value((real64)0);
                break;

            case CMPI_char16:
                v.set_value((char16)0);
                break;

            case CMPI_string:
                v.set_value(String());
                break;

            case CMPI_dateTime:
                v.set_value(Datetime());
                break;

            case CMPI_instance:
            case CMPI_ref:
                v.set_value((Instance*)0);
                break;

            case CMPI_booleanA:
                v.set_value(Array<boolean>());
                break;

            case CMPI_uint8A:
                v.set_value(Array<uint8>());
                break;

            case CMPI_sint8A:
                v.set_value(Array<sint8>());
                break;

            case CMPI_uint16A:
                v.set_value(Array<uint16>());
                break;

            case CMPI_sint16A:
                v.set_value(Array<sint16>());
                break;

            case CMPI_uint32A:
                v.set_value(Array<uint32>());
                break;

            case CMPI_sint32A:
                v.set_value(Array<sint32>());
                break;

            case CMPI_uint64A:
                v.set_value(Array<uint64>());
                break;

            case CMPI_sint64A:
                v.set_value(Array<sint64>());
                break;

            case CMPI_real32A:
                v.set_value(Array<real32>());
                break;

            case CMPI_real64A:
                v.set_value(Array<real64>());
                break;

            case CMPI_char16A:
                v.set_value(Array<char16>());
                break;

            case CMPI_stringA:
                v.set_value(Array<String>());
                break;

            case CMPI_dateTimeA:
                v.set_value(Array<Datetime>());
                break;

            case CMPI_instanceA:
            case CMPI_refA:
                v.set_value(Array<Instance*>());
                break;

            default:
            {
                CIMPLE_WARN(("unknown cmpi type %u", data.state));
                return -1;
            }
        }

        v.null(true);
        return 0;
    };

    // Non handle non-nulls:

    //CIMPLE_DBG(("cmpi_to_cimple_value is nonNull"));
    switch (data.type)
    {
        case CMPI_boolean:
            return to_cimple_scalar_value<boolean>::func(mr, data, v);

        case CMPI_uint8:
            return to_cimple_scalar_value<uint8>::func(mr, data, v);

        case CMPI_sint8:
            return to_cimple_scalar_value<sint8>::func(mr, data, v);

        case CMPI_uint16:
            return to_cimple_scalar_value<uint16>::func(mr, data, v);

        case CMPI_sint16:
            return to_cimple_scalar_value<sint16>::func(mr, data, v);

        case CMPI_uint32:
            return to_cimple_scalar_value<uint32>::func(mr, data, v);

        case CMPI_sint32:
            return to_cimple_scalar_value<sint32>::func(mr, data, v);

        case CMPI_uint64:
            return to_cimple_scalar_value<uint64>::func(mr, data, v);

        case CMPI_sint64:
            return to_cimple_scalar_value<sint64>::func(mr, data, v);

        case CMPI_real32:
            return to_cimple_scalar_value<real32>::func(mr, data, v);

        case CMPI_real64:
            return to_cimple_scalar_value<real64>::func(mr, data, v);

        case CMPI_char16:
            return to_cimple_scalar_value<char16>::func(mr, data, v);

        case CMPI_string:
            return to_cimple_scalar_value<String>::func(mr, data, v);

        case CMPI_dateTime:
            return to_cimple_scalar_value<Datetime>::func(mr, data, v);

        case CMPI_instance:
        case CMPI_ref:
        {
            if (data.value.inst)
            {
                Instance* inst;
                
                if (data.type == CMPI_instance)
                    inst = _to_cimple_instance(mr, cb, ns, data.value.inst);
                else
                    inst = _to_cimple_instance(mr, cb, ns, data.value.ref);

                if (!inst)
                {
                    CIMPLE_WARN(("failed to create CIMPLE instance"));
                    return -1;
                }

                v.set_value(inst);
            }
            else
            {
                v.set_value((Instance*)0);
            }
            return 0;
        }

        case CMPI_booleanA:
            return to_cimple_array_value<boolean>::func(mr, data, v);

        case CMPI_uint8A:
            return to_cimple_array_value<uint8>::func(mr, data, v);

        case CMPI_sint8A:
            return to_cimple_array_value<sint8>::func(mr, data, v);

        case CMPI_uint16A:
            return to_cimple_array_value<uint16>::func(mr, data, v);

        case CMPI_sint16A:
            return to_cimple_array_value<sint16>::func(mr, data, v);

        case CMPI_uint32A:
            return to_cimple_array_value<uint32>::func(mr, data, v);

        case CMPI_sint32A:
            return to_cimple_array_value<sint32>::func(mr, data, v);

        case CMPI_uint64A:
            return to_cimple_array_value<uint64>::func(mr, data, v);

        case CMPI_sint64A:
            return to_cimple_array_value<sint64>::func(mr, data, v);

        case CMPI_real32A:
            return to_cimple_array_value<real32>::func(mr, data, v);

        case CMPI_real64A:
            return to_cimple_array_value<real64>::func(mr, data, v);

        case CMPI_char16A:
            return to_cimple_array_value<char16>::func(mr, data, v);

        case CMPI_stringA:
            return to_cimple_array_value<String>::func(mr, data, v);

        case CMPI_dateTimeA:
            return to_cimple_array_value<Datetime>::func(mr, data, v);

        case CMPI_instanceA:
        case CMPI_refA:
        {
            Array<Instance*> x;

            if (!data.value.array)
            {
                return -1;
                CIMPLE_WARN(("encountered null array"));
            }

            CMPICount n = CMGetArrayCount(data.value.array, NULL);

            for (CMPICount i = 0; i < n; i++)
            {
                CMPIData tmp = CMGetArrayElementAt(data.value.array, i, NULL);

                if (tmp.type != (~CMPI_ARRAY & data.type))
                {
                    _release(x);
                    CIMPLE_WARN(("array element type mismatch"));
                    return -1;
                }

                //if (tmp.state & CMPI_nullValue)
                if (CMIsNullValue(tmp))
                {
                    x.append(0);
                }
                else if (!tmp.value.inst)
                {
                    // Note: If tmp.value.inst is null, so is tmp.value.ref.
                    _release(x);
                    CIMPLE_WARN(("encountered null instance element"));
                    return -1;
                }
                else
                {
                    Instance* inst;
                    
                    if (data.type == CMPI_instanceA)
                        inst = _to_cimple_instance(mr, cb, ns, tmp.value.inst);
                    else
                        inst = _to_cimple_instance(mr, cb, ns, tmp.value.ref);

                    if (!inst)
                    {
                        _release(x);
                        CIMPLE_WARN(("failed to create CIMPLE instance"));
                        return -1;
                    }

                    x.append(inst);
                }
            }

            v.set_value(x);
            return 0;
        }
    }

    // Unreachable!
    CIMPLE_WARN(("unreachable"));
    return -1;
}

template<class T>
struct to_cmpi_scalar
{
    static int func(const Meta_Repository* mr, const CMPIBroker* cb, 
        const char* ns, const T& x, CMPIType type, CMPIData& d)
    {
        d.state = 0;
        d.type = type;
        *((T*)&d.value) = x;
        return 0;
    }
};

template<>
struct to_cmpi_scalar<boolean>
{
    static int func(const Meta_Repository* mr, const CMPIBroker* cb, 
        const char* ns, const boolean& x, CMPIType type, CMPIData& d)
    {
        d.state = 0;
        d.type = type;
        d.value.boolean = x;
        return 0;
    }
};

template<>
struct to_cmpi_scalar<String>
{
    static int func(const Meta_Repository* mr, const CMPIBroker* cb, 
        const char* ns, const String& x, CMPIType type, CMPIData& d)
    {
        d.state = 0;
        d.type = type;
        d.value.string = CMNewString(cb, x.c_str(), 0);
        return 0;
    }
};

template<>
struct to_cmpi_scalar<Datetime>
{
    static int func(const Meta_Repository* mr, const CMPIBroker* cb, 
        const char* ns, const Datetime& x, CMPIType type, CMPIData& d)
    {
        d.state = 0;
        d.type = type;
        d.value.dateTime = CMNewDateTimeFromChars(cb, x.ascii().c_str(), 0);
        return 0;
    }
};

template<>
struct to_cmpi_scalar<Instance*>
{
    static int func(const Meta_Repository* mr, const CMPIBroker* cb, 
        const char* ns_, Instance* x, CMPIType type, CMPIData& d)
    {
        memset(&d, 0, sizeof(d));

        if (!x)
        {
            CIMPLE_WARN(("null instance argument"));
            return -1;
        }

        // Get namespace:

        const char* ns = x->__name_space.c_str();

        if (*ns == '\0')
            ns = ns_;

        if (!ns || *ns == '\0')
        {
            CIMPLE_WARN(("null namespace"));
            return -1;
        }

        // Get classname:

        const char* cn = x->meta_class->name;

        if (*cn == '\0')
        {
            CIMPLE_WARN(("null classname"));
            return -1;
        }

        // Whether CMPI_ref or CMPI_instance, always create an object path.

        CMPIStatus status;
        CMPIObjectPath* cop = CMNewObjectPath(cb, ns, cn, &status);
        {
            if (status.rc != CMPI_RC_OK || !cop)
            {
                CIMPLE_WARN(("CMNewObjectPath() failed"));
                return -1;
            }

            CMPIObjectPath_Container cont(mr, cb, ns, cop);

            if (cont.convert(x, CIMPLE_FLAG_KEY) != 0)
            {
                CIMPLE_WARN(("Container::convert() failed"));
                return -1;
            }
        }

        // Either CMPI_ref or CMPI_instance:

        if (type == CMPI_ref)
        {
            d.type = CMPI_ref;
            d.value.ref = cop;
            return 0;
        }
        else if (type == CMPI_instance)
        {
            CMPIStatus status_l;
            CMPIInstance* ci = CMNewInstance(cb, cop, &status_l);

            if (status_l.rc != CMPI_RC_OK || !ci)
            {
                CIMPLE_WARN(("CMNewInstance() failed"));
                return -1;
            }

            CMPIInstance_Container cont(mr, cb, ns, ci);

            if (cont.convert(x, 0) != 0)
            {
                CIMPLE_WARN(("Container::convert() failed"));
                return -1;
            }

            d.type = CMPI_instance;
            d.value.inst = ci;
            return 0;
        }
        else
        {
            CIMPLE_WARN(("unexpected type"));
            return -1;
        }
    }
};

template<class T>
struct to_cmpi_array
{
    static int func(
        const Meta_Repository* mr, 
        const CMPIBroker* cb, 
        const char* ns,
        const Array<T>& a, 
        CMPIType type, 
        CMPIData& d)
    {
        d.state = 0;
        d.type = (CMPI_ARRAY | type);
        d.value.array = CMNewArray(cb, a.size(), type, 0);

        for (size_t i = 0; i < a.size(); i++)
        {
            CMPIData tmp;

            if (to_cmpi_scalar<T>::func(mr, cb, ns, a[i], type, tmp) != 0)
            {
                CIMPLE_WARN(("element conversion failed"));
                return -1;
            }

            CMPIStatus status = CMSetArrayElementAt(
                d.value.array, i, &tmp.value, type);

            if (status.rc != CMPI_RC_OK)
            {
                CIMPLE_WARN(("CMSetArrayElementAt() failed"));
                return -1;
            }
        }

        return 0;
    }
};

static int _to_cmpi_data(
    const Meta_Repository* mr, 
    const CMPIBroker* cb, 
    const char* ns,
    const Value& v, 
    uint32 flags,
    CMPIData& data)
{
    memset(&data, 0, sizeof(data));

    switch (v.type())
    {
        case Value::NONE:
        {
            CIMPLE_WARN(("missing type"));
            return -1;
        }

        case Value::BOOLEAN:
        {
            boolean x;
            v.get_value(x);
            return to_cmpi_scalar<boolean>::func(
                mr, cb, ns, x, CMPI_boolean, data);
        }

        case Value::UINT8:
        {
            uint8 x;
            v.get_value(x);
            return to_cmpi_scalar<uint8>::func(
                mr, cb, ns, x, CMPI_uint8, data);
        }

        case Value::SINT8:
        {
            sint8 x;
            v.get_value(x);
            return to_cmpi_scalar<sint8>::func(
                mr, cb, ns, x, CMPI_sint8, data);
        }

        case Value::UINT16:
        {
            uint16 x;
            v.get_value(x);
            return to_cmpi_scalar<uint16>::func(
                mr, cb, ns, x, CMPI_uint16, data);
        }

        case Value::SINT16:
        {
            sint16 x;
            v.get_value(x);
            return to_cmpi_scalar<sint16>::func(
                mr, cb, ns, x, CMPI_sint16, data);
        }

        case Value::UINT32:
        {
            uint32 x;
            v.get_value(x);
            return to_cmpi_scalar<uint32>::func(
                mr, cb, ns, x, CMPI_uint32, data);
        }

        case Value::SINT32:
        {
            sint32 x;
            v.get_value(x);
            return to_cmpi_scalar<sint32>::func(
                mr, cb, ns, x, CMPI_sint32, data);
        }

        case Value::UINT64:
        {
            uint64 x;
            v.get_value(x);
            return to_cmpi_scalar<uint64>::func(
                mr, cb, ns, x, CMPI_uint64, data);
        }

        case Value::SINT64:
        {
            sint64 x;
            v.get_value(x);
            return to_cmpi_scalar<sint64>::func(
                mr, cb, ns, x, CMPI_sint64, data);
        }

        case Value::REAL32:
        {
            real32 x;
            v.get_value(x);
            return to_cmpi_scalar<real32>::func(
                mr, cb, ns, x, CMPI_real32, data);
        }

        case Value::REAL64:
        {
            real64 x;
            v.get_value(x);
            return to_cmpi_scalar<real64>::func(
                mr, cb, ns, x, CMPI_real64, data);
        }

        case Value::CHAR16:
        {
            char16 x;
            v.get_value(x);
            return to_cmpi_scalar<char16>::func(
                mr, cb, ns, x, CMPI_char16, data);
        }

        case Value::STRING:
        {
            String x;
            v.get_value(x);
            return to_cmpi_scalar<String>::func(
                mr, cb, ns, x, CMPI_string, data);
        }

        case Value::DATETIME:
        {
            Datetime x;
            v.get_value(x);
            return to_cmpi_scalar<Datetime>::func(
                mr, cb, ns, x, CMPI_dateTime, data);
        }

        case Value::INSTANCE:
        {
            Instance* x;
            v.get_value(x);

            if (flags & CIMPLE_FLAG_EMBEDDED_INSTANCE ||
                flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            {
                return to_cmpi_scalar<Instance*>::func(
                    mr, cb, ns, x, CMPI_instance, data);
            }
            else
            {
                return to_cmpi_scalar<Instance*>::func(
                    mr, cb, ns, x, CMPI_ref, data);
            }
        }

        case Value::BOOLEAN_ARRAY:
        {
            Array<boolean> x;
            v.get_value(x);
            return to_cmpi_array<boolean>::func(
                mr, cb, ns, x, CMPI_boolean, data);
        }

        case Value::UINT8_ARRAY:
        {
            Array<uint8> x;
            v.get_value(x);
            return to_cmpi_array<uint8>::func(
                mr, cb, ns, x, CMPI_uint8, data);
        }

        case Value::SINT8_ARRAY:
        {
            Array<sint8> x;
            v.get_value(x);
            return to_cmpi_array<sint8>::func(
                mr, cb, ns, x, CMPI_sint8, data);
        }

        case Value::UINT16_ARRAY:
        {
            Array<uint16> x;
            v.get_value(x);
            return to_cmpi_array<uint16>::func(
                mr, cb, ns, x, CMPI_uint16, data);
        }

        case Value::SINT16_ARRAY:
        {
            Array<sint16> x;
            v.get_value(x);
            return to_cmpi_array<sint16>::func(
                mr, cb, ns, x, CMPI_sint16, data);
        }

        case Value::UINT32_ARRAY:
        {
            Array<uint32> x;
            v.get_value(x);
            return to_cmpi_array<uint32>::func(
                mr, cb, ns, x, CMPI_uint32, data);
        }

        case Value::SINT32_ARRAY:
        {
            Array<sint32> x;
            v.get_value(x);
            return to_cmpi_array<sint32>::func(
                mr, cb, ns, x, CMPI_sint32, data);
        }

        case Value::UINT64_ARRAY:
        {
            Array<uint64> x;
            v.get_value(x);
            return to_cmpi_array<uint64>::func(
                mr, cb, ns, x, CMPI_uint64, data);
        }

        case Value::SINT64_ARRAY:
        {
            Array<sint64> x;
            v.get_value(x);
            return to_cmpi_array<sint64>::func(
                mr, cb, ns, x, CMPI_sint64, data);
        }

        case Value::REAL32_ARRAY:
        {
            Array<real32> x;
            v.get_value(x);
            return to_cmpi_array<real32>::func(
                mr, cb, ns, x, CMPI_real32, data);
        }

        case Value::REAL64_ARRAY:
        {
            Array<real64> x;
            v.get_value(x);
            return to_cmpi_array<real64>::func(
                mr, cb, ns, x, CMPI_real64, data);
        }

        case Value::CHAR16_ARRAY:
        {
            Array<char16> x;
            v.get_value(x);
            return to_cmpi_array<char16>::func(
                mr, cb, ns, x, CMPI_char16, data);
        }

        case Value::STRING_ARRAY:
        {
            Array<String> x;
            v.get_value(x);
            return to_cmpi_array<String>::func(
                mr, cb, ns, x, CMPI_string, data);
        }

        case Value::DATETIME_ARRAY:
        {
            Array<Datetime> x;
            v.get_value(x);
            return to_cmpi_array<Datetime>::func(
                mr, cb, ns, x, CMPI_dateTime, data);
        }

        case Value::INSTANCE_ARRAY:
        {
            Array<Instance*> x;
            v.get_value(x);

            if (flags & CIMPLE_FLAG_EMBEDDED_INSTANCE ||
                flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            {
                return to_cmpi_array<Instance*>::func(
                    mr, cb, ns, x, CMPI_instance, data);
            }
            else
            {
                return to_cmpi_array<Instance*>::func(
                    mr, cb, ns, x, CMPI_ref, data);
            }
        }
    }

    if (v.null())
        data.state |= CMPI_nullValue;

    return 0;
}

//==============================================================================
//
// CMPIInstance_Container
//
//==============================================================================

CMPIInstance_Container::CMPIInstance_Container(
    const Meta_Repository* mr, 
    const CMPIBroker* cb, 
    const char* ns,
    Rep* rep)
    : 
    Container(mr), _cb(cb), _ns(ns), _rep(rep)
{
}

CMPIInstance_Container::~CMPIInstance_Container()
{
}

size_t CMPIInstance_Container::get_size()
{
    return CMGetPropertyCount(_rep, NULL);
}

int CMPIInstance_Container::get_name(size_t pos, String& name)
{
    if (pos >= get_size())
    {
        CIMPLE_WARN(("bounds error"));
        return -1;
    }

    CMPIString* tmp = 0;

    try
    {
        CMPIStatus status;
        CMGetPropertyAt(_rep, pos, &tmp, &status);

        if (status.rc != CMPI_RC_OK)
        {
            CIMPLE_WARN(("CMGetPropertyAt() failed"));
            return -1;
        }
    }
    catch (...)
    {
        CMPICount n = CMGetPropertyCount(_rep, NULL);
        CIMPLE_WARN((
            "CMGetPropertyAt() threw exception: index=%u size=%u", 
                (uint32)pos, (uint32)n));
        return -1;
    }

    name = _c_str(tmp);
    //CIMPLE_DBG(("name=%s pos=%u", name, pos));
    return 0;
}

int CMPIInstance_Container::get_value(
    size_t pos, Value::Type type, Value& value)
{
    value.clear();

    if (pos >= get_size())
    {
        CIMPLE_WARN(("bounds error"));
        return -1;
    }

    CMPIString* name;
    CMPIData data = CMGetPropertyAt(_rep, pos, &name, NULL);

    if (cmpi_to_cimple_value(_mr, _cb, _ns, data, value) != 0)
    {
        CIMPLE_WARN(("cmpi_to_cimple_value() failed"));
        return -1;
    }

    if (value.type() != type)
    {
        CIMPLE_WARN(("type mismatch on %s: %s/%s", 
            _c_str(name), name_of(value.type()), name_of(type)));
        return -1;
    }

    return 0;
}

/*
    Extension of virtual method in cimple/Container. Sets value input
    into CMPI property defined by name using the CMPI function
    CMSetProperty. Returns 0 if the set_value is valid. Returns
    -1 and does a log entry if invalid.
*/
int CMPIInstance_Container::set_value(
    const char* name, const Value& value, uint32 flags)
{
    CMPIData data;
    if (_to_cmpi_data(_mr, _cb, _ns, value, flags, data) != 0)
    {
        CIMPLE_WARN(("_to_cmpi_data() failed: feature=%s", name));
        return -1;
    }

    CMPIStatus status = CMSetProperty(_rep, name, &data.value, data.type);

    if (status.rc != CMPI_RC_OK)
    {
        CIMPLE_WARN(("CMSetProperty() failed: %s", name));
        return -1;
    }

    return 0;
}

//==============================================================================
//
// CMPIObjectPath_Container
//
//==============================================================================

CMPIObjectPath_Container::CMPIObjectPath_Container(
    const Meta_Repository* mr, 
    const CMPIBroker* cb, 
    const char* ns,
    Rep* rep)
    : 
    Container(mr),
    _cb(cb),
    _ns(ns),
    _rep(rep)
{
}

CMPIObjectPath_Container::~CMPIObjectPath_Container()
{
}

size_t CMPIObjectPath_Container::get_size()
{
    // KS_TODO Dec 2010. Possible issue with this and Pegasus 2.10.  
    // Need if zero, need to try the zeroth and determine from this
    // if keycount really zero. Issue introduced by Pegasus v 2.10
    // Note that we already commented out code elsewhere to correct this issue
    // but we need to add code here to prevent any misuse in the future.
    // See the adapter for more comments.
    return CMGetKeyCount(_rep, NULL);
}

int CMPIObjectPath_Container::get_name(size_t pos, String& name)
{
    if (pos >= get_size())
    {
        CIMPLE_WARN(("bounds error"));
        return -1;
    }

    CMPIString* tmp;
    CMGetKeyAt(_rep, pos, &tmp, NULL);

    name = _c_str(tmp);
    return 0;
}

int CMPIObjectPath_Container::get_value(
    size_t pos, Value::Type type, Value& value)
{
    value.clear();

    if (pos >= get_size())
    {
        CIMPLE_WARN(("bounds error"));
        return -1;
    }

    CMPIString* name;
    CMPIData data = CMGetKeyAt(_rep, pos, &name, NULL);

    if (cmpi_to_cimple_value(_mr, _cb, _ns, data, value) != 0)
    {
        CIMPLE_WARN(("cmpi_to_cimple_value() failed"));
        return -1;
    }

    // Integer types must be "fixed up" since CMPI promotes all integer
    // keys to uint64.

    if (value.type() == Value::UINT64 && type != Value::UINT64)
    {
        uint64 x;
        value.get_value(x);
        bool null = value.null();

        switch (type)
        {
            case UINT8:
                value.set_value(uint8(x));
                break;

            case SINT8:
                value.set_value(sint8(x));
                break;

            case UINT16:
                value.set_value(uint16(x));
                break;

            case SINT16:
                value.set_value(sint16(x));
                break;

            case UINT32:
                value.set_value(uint32(x));
                break;

            case SINT32:
                value.set_value(sint32(x));
                break;

            case UINT64:
                value.set_value(uint64(x));
                break;

            case SINT64:
                value.set_value(sint64(x));
                break;

            default:
                break;
        }

        value.null(null);
    }


    // CMPI (in Pegasus 2.5.2) passes uint32 as sint64 in some cases.
    // Adjust the type in this case.

    if (value.type() == Value::SINT64 && type == Value::UINT32)
    {
        sint64 tmp;
        value.get_value(tmp);
        value.set_value(uint32(tmp));
    }

    // Check for type mismatch.

    if (value.type() != type)
    {
        CIMPLE_WARN(("type mismatch on %s: %s/%s", 
            _c_str(name), name_of(value.type()), name_of(type)));
        return -1;
    }

    return 0;
}

int CMPIObjectPath_Container::set_value(
    const char* name, const Value& value, uint32 flags)
{
    CMPIData data;

    if (_to_cmpi_data(_mr, _cb, _ns, value, flags, data) != 0)
    {
        CIMPLE_WARN(("_to_cmpi_data() failed: feature=%s", name));
        return -1;
    }

    CMPIStatus status = CMAddKey(_rep, name, &data.value, data.type);

    if (status.rc != CMPI_RC_OK)
    {
        CIMPLE_WARN(("CMAddKey() failed"));
        return -1;
    }

    return 0;
}

//==============================================================================
//
// CMPIArgs_Container
//
//==============================================================================

CMPIArgs_Container::CMPIArgs_Container(
    const Meta_Repository* mr, 
    const CMPIBroker* cb, 
    const char* ns,
    Rep* rep)
    : 
    Container(mr),
    _cb(cb),
    _ns(ns),
    _rep(rep)
{
}

CMPIArgs_Container::~CMPIArgs_Container()
{
}

size_t CMPIArgs_Container::get_size()
{
    return CMGetArgCount(_rep, NULL);
}

int CMPIArgs_Container::get_name(size_t pos, String& name)
{
    if (pos >= get_size())
    {
        CIMPLE_WARN(("bounds error"));
        return -1;
    }

    CMPIString* tmp;
    CMGetArgAt(_rep, pos, &tmp, NULL);

    name = _c_str(tmp);
    return 0;
}

int CMPIArgs_Container::get_value(size_t pos, Value::Type type, Value& value)
{
    value.clear();

    if (pos >= get_size())
    {
        CIMPLE_WARN(("bounds error"));
        return -1;
    }

    CMPIString* name;
    CMPIData data = CMGetArgAt(_rep, pos, &name, NULL);

    if (cmpi_to_cimple_value(_mr, _cb, _ns, data, value) != 0)
    {
        CIMPLE_WARN(("cmpi_to_cimple_value() failed"));
        return -1;
    }

    // Adjust for Pegasus bug that sends null ref-arrays as boolean.

    if (value.type() == Value::BOOLEAN && type == Value::INSTANCE_ARRAY)
    {
        Array<Instance*> a;
        value.set_value(a);
        value.null(true);
    }

    if (value.type() != type)
    {
        CIMPLE_WARN(("type mismatch on %s: %s/%s", 
            _c_str(name), name_of(value.type()), name_of(type)));
        return -1;
    }

    return 0;
}

int CMPIArgs_Container::set_value(
    const char* name, const Value& value, uint32 flags)
{
    CMPIData data;

    if (_to_cmpi_data(_mr, _cb, _ns, value, flags, data) != 0)
    {
        CIMPLE_WARN(("_to_cmpi_data() failed: feature=%s", name));
        return -1;
    }

    if (strcmp(name, "return_value") == 0)
    {
        _return_value = data;
    }
    else
    {
        CMPIStatus status = CMAddArg(_rep, name, &data.value, data.type);

        if (status.rc != CMPI_RC_OK)
        {
            CIMPLE_WARN(("CMAddArg() failed"));
            return -1;
        }
    }

    return 0;
}

CIMPLE_NAMESPACE_END
