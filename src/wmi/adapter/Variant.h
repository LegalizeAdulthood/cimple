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

#ifndef _Variant_h
#define _Variant_h

#include <cimple/cimple.h>
#include <objbase.h>
#include "SafeArr.h"
#include "log.h"
#include "utils.h"

CIMPLE_NAMESPACE_BEGIN

template<class CIMTYPE, long VT, class VTTYPE>
struct __Variant
{
    static int to_array(VARIANT& rep, Value& v)
    {
        if (rep.vt != (VT_ARRAY|VT) || !rep.parray)
            return -1;

        SafeArr sa(rep.parray);
        long n;
        
        if (!sa.size(n))
        {
            sa.steal();
            return -1;
        }

        Array<CIMTYPE> a;

        for (long i = 0; i < n; i++)
        {
            VTTYPE tmp;

            if (!sa.get(i, &tmp))
            {
                sa.steal();
                return -1;
            }

            a.append(CIMTYPE(tmp));
        }

        sa.steal();
        v.set_value(a);
        return 0;
    }
};

class Variant
{
public:

    Variant(const VARIANT& var)
    {
        VariantInit(&_rep);
        VariantCopy(&_rep, (VARIANT*)&var);
    }

    Variant()
    {
        VariantInit(&_rep);
    }

    ~Variant()
    {
        clear();
    }

    const VARIANT& rep() const
    {
        return _rep;
    }

    VARIANT& rep()
    {
        return _rep;
    }

    VARIANT steal()
    {
        VARIANT tmp;
        memcpy(&tmp, &_rep, sizeof(_rep));
        memset(&_rep, 0, sizeof(_rep));
        return tmp;
    }

    void clear()
    {
        VariantClear(&_rep);
        memset(&_rep, 0, sizeof(_rep));
    }

    void set_boolean(boolean x)
    {
        clear();
        _rep.vt = VT_BOOL;
        _rep.boolVal = (unsigned int)(x);
    }

    void set_uint8(uint8 x)
    {
        clear();
        _rep.vt = VT_UI1;
        _rep.bVal = x;
    }

    void set_sint8(sint8 x)
    {
        clear();
        _rep.vt = VT_I2;
        _rep.iVal = x;
    }

    void set_uint16(uint16 x)
    {
        clear();
        _rep.vt = VT_I4;
        _rep.lVal = x;
    }

    void set_sint16(sint16 x)
    {
        clear();
        _rep.vt = VT_I2;
        _rep.iVal = x;
    }

    void set_uint32(uint32 x)
    {
        clear();
        _rep.vt = VT_I4;
        _rep.lVal = x;
    }

    void set_sint32(sint32 x)
    {
        clear();
        _rep.vt = VT_I4;
        _rep.lVal = x;
    }

    void set_uint64(uint64 x)
    {
        clear();
        char buf[64];
        sprintf(buf, "%I64u", x);
        _rep.vt = VT_BSTR;
        _rep.bstrVal = cstr2bstr(buf);
    }

    void set_sint64(sint64 x)
    {
        clear();
        char buf[64];
        sprintf(buf, "%I64d", x);
        _rep.vt = VT_BSTR;
        _rep.bstrVal = cstr2bstr(buf);
    }

    void set_real32(real32 x)
    {
        clear();
        _rep.vt = VT_R4;
        _rep.fltVal = x;
    }

    void set_real64(real64 x)
    {
        clear();
        _rep.vt = VT_R8;
        _rep.dblVal = x;
    }

    void set_char16(const char16& x)
    {
        clear();
        _rep.vt = VT_I2;
        _rep.iVal = x.code();
    }

    void set_string(const String& x)
    {
        clear();
        _rep.vt = VT_BSTR;
        _rep.bstrVal = cstr2bstr(x.c_str());
    }

    void set_datetime(const Datetime& x)
    {
        clear();
        _rep.vt = VT_BSTR;
        char buf[Datetime::BUFFER_SIZE];
        x.ascii(buf);
        _rep.vt = VT_BSTR;
        _rep.bstrVal = cstr2bstr(buf);
    }

    void set_reference(const Instance* x)
    {
        clear();

        if (!x)
        {
            // ATTN: How to represent null refs?
            return;
        }

        String s;

        if (instance_to_model_path(x, s) == 0)
        {
            _rep.vt = VT_BSTR;
            _rep.bstrVal = cstr2bstr(s.c_str());
        }
    }

    void set_boolean_array(const Array<boolean>& x)
    {
        SafeArr arr(VT_BOOL, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.boolVal = (unsigned int)x[i];
            arr.put(i, &v.boolVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_BOOL;
    }

    void set_uint8_array(const Array<uint8>& x)
    {
        SafeArr arr(VT_UI1, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.bVal = x[i];
            arr.put(i, &v.bVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_UI1;
    }

    void set_sint8_array(const Array<sint8>& x)
    {
        SafeArr arr(VT_I2, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.iVal = x[i];
            arr.put(i, &v.iVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_I2;
    }

    void set_uint16_array(const Array<uint16>& x)
    {
        SafeArr arr(VT_I4, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.lVal = x[i];
            arr.put(i, &v.lVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_I4;
    }

    void set_sint16_array(const Array<sint16>& x)
    {
        SafeArr arr(VT_I2, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.iVal = x[i];
            arr.put(i, &v.iVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_I2;
    }

    void set_uint32_array(const Array<uint32>& x)
    {
        SafeArr arr(VT_I4, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.lVal = x[i];
            arr.put(i, &v.lVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_I4;
    }

    void set_sint32_array(const Array<sint32>& x)
    {
        SafeArr arr(VT_I4, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.lVal = x[i];
            arr.put(i, &v.lVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_I4;
    }

    void set_uint64_array(const Array<uint64>& x)
    {
        SafeArr arr(VT_BSTR, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            Variant tmp;
            tmp.set_uint64(x[i]);

            VARIANT v = tmp.steal();
            arr.put(i, v.bstrVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_BSTR;
    }

    void set_sint64_array(const Array<sint64>& x)
    {
        SafeArr arr(VT_BSTR, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            Variant tmp;
            tmp.set_sint64(x[i]);

            VARIANT v = tmp.steal();
            arr.put(i, v.bstrVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_BSTR;
    }

    void set_real32_array(const Array<real32>& x)
    {
        SafeArr arr(VT_R4, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.fltVal = x[i];
            arr.put(i, &v.fltVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_R4;
    }

    void set_real64_array(const Array<real64>& x)
    {
        SafeArr arr(VT_R8, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.dblVal = x[i];
            arr.put(i, &v.dblVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_R8;
    }

    void set_char16_array(const Array<char16>& x)
    {
        SafeArr arr(VT_I2, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            VARIANT v;
            v.iVal = x[i].code();
            arr.put(i, &v.iVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_I2;
    }

    void set_string_array(const Array<String>& x)
    {
        SafeArr arr(VT_BSTR, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            Variant tmp;
            tmp.set_string(x[i]);

            VARIANT v = tmp.steal();
            arr.put(i, v.bstrVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_BSTR;
    }

    void set_datetime_array(const Array<Datetime>& x)
    {
        SafeArr arr(VT_BSTR, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            Variant tmp;
            tmp.set_datetime(x[i]);

            VARIANT v = tmp.steal();
            arr.put(i, v.bstrVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_BSTR;
    }

    void set_reference_array(const Array<Instance*> x)
    {
        SafeArr arr(VT_BSTR, x.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            Variant tmp;
            tmp.set_reference(x[i]);

            VARIANT v = tmp.steal();
            arr.put(i, v.bstrVal);
        }

        _rep.parray = arr.steal();
        _rep.vt = VT_ARRAY|VT_BSTR;
    }

    int set_value(const Value& v)
    {
        if (v.null())
            return -1;

        switch (v.type())
        {
            case Value::BOOLEAN:
            {
                boolean x;
                v.get_value(x);
                set_boolean(x);
                return 0;
            }

            case Value::UINT8:
            {
                uint8 x;
                v.get_value(x);
                set_uint8(x);
                return 0;
            }

            case Value::SINT8:
            {
                sint8 x;
                v.get_value(x);
                set_sint8(x);
                return 0;
            }

            case Value::UINT16:
            {
                uint16 x;
                v.get_value(x);
                set_uint16(x);
                return 0;
            }

            case Value::SINT16:
            {
                sint16 x;
                v.get_value(x);
                set_sint16(x);
                return 0;
            }

            case Value::UINT32:
            {
                uint32 x;
                v.get_value(x);
                set_uint32(x);
                return 0;
            }

            case Value::SINT32:
            {
                sint32 x;
                v.get_value(x);
                set_sint32(x);
                return 0;
            }

            case Value::UINT64:
            {
                uint64 x;
                v.get_value(x);
                set_uint64(x);
                return 0;
            }

            case Value::SINT64:
            {
                sint64 x;
                v.get_value(x);
                set_sint64(x);
                return 0;
            }

            case Value::REAL32:
            {
                real32 x;
                v.get_value(x);
                set_real32(x);
                return 0;
            }

            case Value::REAL64:
            {
                real64 x;
                v.get_value(x);
                set_real64(x);
                return 0;
            }

            case Value::CHAR16:
            {
                char16 x;
                v.get_value(x);
                set_char16(x);
                return 0;
            }

            case Value::STRING:
            {
                String x;
                v.get_value(x);
                set_string(x);
                return 0;
            }

            case Value::DATETIME:
            {
                Datetime x;
                v.get_value(x);
                set_datetime(x);
                return 0;
            }

            case Value::INSTANCE:
            {
                Instance* inst;
                v.get_value(inst);
                set_reference(inst);
                return 0;
            }

            case Value::BOOLEAN_ARRAY:
            {
                Array<boolean> x;
                v.get_value(x);
                set_boolean_array(x);
                return 0;
            }

            case Value::UINT8_ARRAY:
            {
                Array<uint8> x;
                v.get_value(x);
                set_uint8_array(x);
                return 0;
            }

            case Value::SINT8_ARRAY:
            {
                Array<sint8> x;
                v.get_value(x);
                set_sint8_array(x);
                return 0;
            }

            case Value::UINT16_ARRAY:
            {
                Array<uint16> x;
                v.get_value(x);
                set_uint16_array(x);
                return 0;
            }

            case Value::SINT16_ARRAY:
            {
                Array<sint16> x;
                v.get_value(x);
                set_sint16_array(x);
                return 0;
            }

            case Value::UINT32_ARRAY:
            {
                Array<uint32> x;
                v.get_value(x);
                set_uint32_array(x);
                return 0;
            }

            case Value::SINT32_ARRAY:
            {
                Array<sint32> x;
                v.get_value(x);
                set_sint32_array(x);
                return 0;
            }

            case Value::UINT64_ARRAY:
            {
                Array<uint64> x;
                v.get_value(x);
                set_uint64_array(x);
                return 0;
            }

            case Value::SINT64_ARRAY:
            {
                Array<sint64> x;
                v.get_value(x);
                SafeArr tmp(VT_I8, x.size());
                set_sint64_array(x);
                return 0;
            }

            case Value::REAL32_ARRAY:
            {
                Array<real32> x;
                v.get_value(x);
                set_real32_array(x);
                return 0;
            }

            case Value::REAL64_ARRAY:
            {
                Array<real64> x;
                v.get_value(x);
                set_real64_array(x);
                return 0;
            }

            case Value::CHAR16_ARRAY:
            {
                Array<char16> x;
                v.get_value(x);
                set_char16_array(x);
                return 0;
            }

            case Value::STRING_ARRAY:
            {
                Array<String> x;
                v.get_value(x);
                set_string_array(x);
                return 0;
            }

            case Value::DATETIME_ARRAY:
            {
                Array<Datetime> x;
                v.get_value(x);
                set_datetime_array(x);
                return 0;
            }

            case Value::INSTANCE_ARRAY:
            {
                Array<Instance*> x;
                v.get_value(x);
                set_reference_array(x);
                return 0;
            }

            case Value::NONE:
            default:
                return -1;
        }

        // Unreachable!
        return 0;
    }

    int to_value(CIMTYPE cimtype, Value& v, const Meta_Repository* mr)
    {
        v.clear();

        if (_rep.vt == VT_NULL)
        {
            return -1;
        }

        switch (cimtype)
        {
            case CIM_BOOLEAN:
            {
                if (_rep.vt != VT_BOOL)
                    return -1;

                v.set_value(boolean(_rep.boolVal));
                return 0;
            }

            case CIM_UINT8:
            {
                if (_rep.vt != VT_UI1)
                    return -1;

                v.set_value(uint8(_rep.bVal));
                return 0;
            }

            case CIM_SINT8:
            {
                if (_rep.vt != VT_I2)
                    return -1;

                v.set_value(sint8(_rep.iVal));
                return 0;
            }

            case CIM_UINT16:
            {
                if (_rep.vt != VT_I4)
                    return -1;

                v.set_value(uint16(_rep.lVal));
                return 0;
            }

            case CIM_SINT16:
            {
                if (_rep.vt != VT_I2)
                    return -1;

                v.set_value(sint16(_rep.iVal));
                return 0;
            }

            case CIM_UINT32:
            {
                if (_rep.vt != VT_I4)
                    return -1;

                v.set_value(uint32(_rep.lVal));
                return 0;
            }

            case CIM_SINT32:
            {
                if (_rep.vt != VT_I4)
                    return -1;

                v.set_value(sint32(_rep.lVal));
                return 0;
            }

            case CIM_UINT64:
            {
                if (_rep.vt != VT_BSTR || !_rep.bstrVal)
                    return -1;

                String s = bstr2str(_rep.bstrVal);
                uint64 x;

                if (str_to_uint64(s.c_str(), x) != 0)
                    return -1;

                v.set_value(x);
                return 0;
            }

            case CIM_SINT64:
            {
                if (_rep.vt != VT_BSTR || !_rep.bstrVal)
                    return -1;

                String s = bstr2str(_rep.bstrVal);
                sint64 x;

                if (str_to_sint64(s.c_str(), x) != 0)
                    return -1;

                v.set_value(x);
                return 0;
            }

            case CIM_REAL32:
            {
                if (_rep.vt != VT_R4)
                    return -1;

                v.set_value(real32(_rep.fltVal));
                return 0;
            }

            case CIM_REAL64:
            {
                if (_rep.vt != VT_R8)
                    return -1;

                v.set_value(real64(_rep.dblVal));
                return 0;
            }

            case CIM_CHAR16:
            {
                if (_rep.vt != VT_I2)
                    return -1;
                v.set_value(char16(_rep.iVal));
                return 0;
            }

            case CIM_STRING:
            {
                if (_rep.vt != VT_BSTR || !_rep.bstrVal)
                    return -1;

                v.set_value(bstr2str(_rep.bstrVal));
                return 0;
            }

            case CIM_DATETIME:
            {
                if (_rep.vt != VT_BSTR || !_rep.bstrVal)
                    return -1;

                String s = bstr2str(_rep.bstrVal);
                Datetime dt;

                if (!dt.set(s.c_str()))
                    return -1;

                v.set_value(dt);
                return 0;
            }

            case CIM_REFERENCE:
            {
                if (_rep.vt != VT_BSTR || !_rep.bstrVal)
                    return -1;

                if (!mr || !mr->meta_classes)
                    return -1;

                const Meta_Class* mc = mr->meta_classes[0];
                String path = bstr2str(_rep.bstrVal);

                Instance* inst = model_path_to_instance(mc, path.c_str());

                if (!inst)
                    return -1;

                v.set_value(inst);
                return 0;
            }

            case CIM_OBJECT:
            {
                return -1;
            }

            case CIM_EMPTY|CIM_FLAG_ARRAY:
            {
                return -1;
            }

            case CIM_SINT8|CIM_FLAG_ARRAY:
            {
                return __Variant<sint8, VT_I2, SHORT>::to_array(_rep, v);
            }

            case CIM_UINT8|CIM_FLAG_ARRAY:
            {
                return __Variant<uint8, VT_UI1, BYTE>::to_array(_rep, v);
            }

            case CIM_SINT16|CIM_FLAG_ARRAY:
            {
                return __Variant<sint16, VT_I2, SHORT>::to_array(_rep, v);
            }

            case CIM_UINT16|CIM_FLAG_ARRAY:
            {
                return __Variant<uint16, VT_I4, LONG>::to_array(_rep, v);
            }

            case CIM_SINT32|CIM_FLAG_ARRAY:
            {
                return __Variant<sint32, VT_I4, LONG>::to_array(_rep, v);
            }

            case CIM_UINT32|CIM_FLAG_ARRAY:
            {
                return __Variant<uint32, VT_I4, LONG>::to_array(_rep, v);
            }

            case CIM_SINT64|CIM_FLAG_ARRAY:
            {
                if (_rep.vt != (VT_ARRAY|VT_BSTR) || !_rep.parray)
                    return -1;

                SafeArr sa(_rep.parray);
                long n;
                
                if (!sa.size(n))
                {
                    sa.steal();
                    return -1;
                }

                Array<sint64> a;

                for (long i = 0; i < n; i++)
                {
                    BSTR tmp;

                    if (!sa.get(i, &tmp) || !tmp)
                    {
                        sa.steal();
                        return -1;
                    }

                    String s = bstr2str(tmp);
                    sint64 x = 0;
                    sscanf(s.c_str(), "%I64d", &x);
                    a.append(x);
                }

                sa.steal();
                v.set_value(a);
                return 0;
            }

            case CIM_UINT64|CIM_FLAG_ARRAY:
            {
                if (_rep.vt != (VT_ARRAY|VT_BSTR) || !_rep.parray)
                    return -1;

                SafeArr sa(_rep.parray);
                long n;
                
                if (!sa.size(n))
                {
                    sa.steal();
                    return -1;
                }

                Array<uint64> a;

                for (long i = 0; i < n; i++)
                {
                    BSTR tmp;

                    if (!sa.get(i, &tmp) || !tmp)
                    {
                        sa.steal();
                        return -1;
                    }

                    String s = bstr2str(tmp);
                    uint64 x = 0;
                    sscanf(s.c_str(), "%I64u", &x);
                    a.append(x);
                }

                sa.steal();
                v.set_value(a);
                return 0;
            }

            case CIM_REAL32|CIM_FLAG_ARRAY:
            {
                return __Variant<real32, VT_R4, FLOAT>::to_array(_rep, v);
            }

            case CIM_REAL64|CIM_FLAG_ARRAY:
            {
                return __Variant<real64, VT_R8, DOUBLE>::to_array(_rep, v);
            }

            case CIM_BOOLEAN|CIM_FLAG_ARRAY:
            {
                return 0;
            }

            case CIM_STRING|CIM_FLAG_ARRAY:
            {
                if (_rep.vt != (VT_ARRAY|VT_BSTR) || !_rep.parray)
                    return -1;

                SafeArr sa(_rep.parray);
                long n;
                
                if (!sa.size(n))
                {
                    sa.steal();
                    return -1;
                }

                Array<String> a;

                for (long i = 0; i < n; i++)
                {
                    BSTR tmp;

                    if (!sa.get(i, &tmp) || !tmp)
                    {
                        sa.steal();
                        return -1;
                    }

                    a.append(bstr2str(tmp));
                }

                sa.steal();
                v.set_value(a);
                return 0;
            }

            case CIM_CHAR16|CIM_FLAG_ARRAY:
            {
                return __Variant<char16, VT_I2, DOUBLE>::to_array(_rep, v);
            }

            case CIM_DATETIME|CIM_FLAG_ARRAY:
            {
                if (_rep.vt != (VT_ARRAY|VT_BSTR) || !_rep.parray)
                    return -1;

                SafeArr sa(_rep.parray);
                long n;
                
                if (!sa.size(n))
                {
                    sa.steal();
                    return -1;
                }

                Array<Datetime> a;

                for (long i = 0; i < n; i++)
                {
                    BSTR tmp;

                    if (!sa.get(i, &tmp) || !tmp)
                    {
                        sa.steal();
                        return -1;
                    }

                    String s= bstr2str(tmp);

                    a.append(Datetime(s.c_str()));
                }

                sa.steal();
                v.set_value(a);
                return 0;
            }

            case CIM_REFERENCE|CIM_FLAG_ARRAY:
            {
                if (_rep.vt != (VT_ARRAY|VT_BSTR) || !_rep.parray)
                    return -1;

                if (!mr || !mr->meta_classes)
                    return -1;

                SafeArr sa(_rep.parray);
                long n;
                
                if (!sa.size(n))
                {
                    sa.steal();
                    return -1;
                }

                Array<Instance*> a;

                for (long i = 0; i < n; i++)
                {
                    BSTR tmp;

                    if (!sa.get(i, &tmp) || !tmp)
                    {
                        sa.steal();
                        a.append(0);
                        continue;
                    }

                    String path = bstr2str(tmp);
                    const Meta_Class* mc = mr->meta_classes[0];

                    Instance* inst = model_path_to_instance(mc, path.c_str());

                    a.append(inst);
                }

                sa.steal();
                v.set_value(a);
                return 0;
            }

            case CIM_OBJECT|CIM_FLAG_ARRAY:
            {
                return -1;
            }

            default:
            {
                return -1;
            }
        }

        // Unreachable!
        return -1;
    }

private:

    Variant(const Variant&) 
    { 
    }

    Variant& operator=(const Variant&) 
    { 
        return *this; 
    }


    VARIANT _rep;
};


CIMPLE_NAMESPACE_END

#endif /* _Variant_h */
