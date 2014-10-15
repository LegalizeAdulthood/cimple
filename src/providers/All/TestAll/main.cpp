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

#include <pegasus/utils/pegasus.h>
#include <pegasus/utils/print.h>
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>

#define NAMESPACE "root/cimv2"

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

inline CIMType TypeOf(const Boolean*) { return CIMTYPE_BOOLEAN; }
inline CIMType TypeOf(const Uint8*) { return CIMTYPE_UINT8; }
inline CIMType TypeOf(const Sint8*) { return CIMTYPE_SINT8; }
inline CIMType TypeOf(const Uint16*) { return CIMTYPE_UINT16; }
inline CIMType TypeOf(const Sint16*) { return CIMTYPE_SINT16; }
inline CIMType TypeOf(const Uint32*) { return CIMTYPE_UINT32; }
inline CIMType TypeOf(const Sint32*) { return CIMTYPE_SINT32; }
inline CIMType TypeOf(const Uint64*) { return CIMTYPE_UINT64; }
inline CIMType TypeOf(const Sint64*) { return CIMTYPE_SINT64; }
inline CIMType TypeOf(const Real32*) { return CIMTYPE_REAL32; }
inline CIMType TypeOf(const Real64*) { return CIMTYPE_REAL64; }
inline CIMType TypeOf(const Char16*) { return CIMTYPE_CHAR16; }
inline CIMType TypeOf(const String*) { return CIMTYPE_STRING; }
inline CIMType TypeOf(const CIMDateTime*) { return CIMTYPE_DATETIME; }
inline CIMType TypeOf(const CIMInstance*) { return CIMTYPE_INSTANCE; }
inline CIMType TypeOf(const CIMObject*) { return CIMTYPE_OBJECT; }
inline CIMType TypeOf(const CIMObjectPath*) { return CIMTYPE_REFERENCE; }

template<class T>
inline bool _equal(const T& x, const T& y)
{
    return x == y;
}

inline bool _equal(const CIMInstance& x, const CIMInstance& y)
{
    return x.identical(y);
}

inline bool _equal(const CIMObject& x, const CIMObject& y)
{
    return x.identical(y);
}

template<class T>
struct Sca
{
};

template<> struct Sca<Boolean> 
{ 
    static Boolean get() { return true; } 
    static CIMValue null() { return CIMValue(CIMTYPE_BOOLEAN, false); }
};

template<> struct Sca<Uint8> 
{ 
    static Uint8 get() { return 8; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT8, false); }
};

template<> struct Sca<Sint8> 
{ 
    static Sint8 get() { return -8; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT8, false); }
};

template<> struct Sca<Uint16> 
{ 
    static Uint16 get() { return 16; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT16, false); }
};

template<> struct Sca<Sint16> 
{ 
    static Sint16 get() { return -16; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT16, false); }
};

template<> struct Sca<Uint32> 
{ 
    static Uint32 get() { return 32; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT32, false); }
};

template<> struct Sca<Sint32> 
{ 
    static Sint32 get() { return -32; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT32, false); }
};

template<> struct Sca<Uint64> 
{ 
    static Uint64 get() { return 64; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT64, false); }
};

template<> struct Sca<Sint64> 
{ 
    static Sint64 get() { return -64; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT64, false); }
};

template<> struct Sca<Real32> 
{ 
    static Real32 get() { return 32.32; } 
    static CIMValue null() { return CIMValue(CIMTYPE_REAL32, false); }
};

template<> struct Sca<Real64> 
{ 
    static Real64 get() { return 64.64; }
    static CIMValue null() { return CIMValue(CIMTYPE_REAL64, false); }
};

template<> struct Sca<Char16> 
{ 
    static Char16 get() { return 'A'; } 
    static CIMValue null() { return CIMValue(CIMTYPE_CHAR16, false); }
};

template<> struct Sca<String> 
{ 
    static String get() { return String("String"); } 
    static CIMValue null() { return CIMValue(CIMTYPE_STRING, false); }
};

template<> struct Sca<CIMDateTime> 
{
    static CIMDateTime get() {return CIMDateTime("20070101120000.000000-360");} 
    static CIMValue null() { return CIMValue(CIMTYPE_DATETIME, false); }
};

template<> struct Sca<CIMInstance> 
{
    static CIMInstance get() 
    {
        CIMInstance part("All_Part");
        part.addProperty(CIMProperty("Key", Uint32(8888)));
        return part;
    }

    static CIMValue null() { return CIMValue(CIMTYPE_INSTANCE, false); }
};

template<> struct Sca<CIMObject> 
{
    static CIMObject get() 
    {
        CIMInstance part("All_Part");
        part.addProperty(CIMProperty("Key", Uint32(7777)));
        return CIMObject(part);
    }

    static CIMValue null() { return CIMValue(CIMTYPE_OBJECT, false); }
};

template<> struct Sca<CIMObjectPath> 
{
    static CIMObjectPath get() 
    {
        return CIMObjectPath("All_Part.Key=7777");
    }

    static CIMValue null() { return CIMValue(CIMTYPE_REFERENCE, false); }
};

template<class T> 
struct Arr
{
    static Array<T> get(Uint32 size) 
    {
        Array<T> a;

        for (Uint32 i = 0; i < size; i++)
            a.append(Sca<T>::get());

        return a;
    }

    static CIMValue null() { return CIMValue(TypeOf((T*)0), true); }
};

void test_instance(CIMClient& client)
{
    // Create instance:

    CIMInstance ci1("All_Class");
    ci1.addProperty(CIMProperty("Key", Uint32(9999)));
    ci1.addProperty(CIMProperty("booleanScalar", Sca<Boolean>::get()));
    ci1.addProperty(CIMProperty("uint8Scalar", Sca<Uint8>::get()));
    ci1.addProperty(CIMProperty("sint8Scalar", Sca<Sint8>::get()));
    ci1.addProperty(CIMProperty("uint16Scalar", Sca<Uint16>::get()));
    ci1.addProperty(CIMProperty("sint16Scalar", Sca<Sint16>::get()));
    ci1.addProperty(CIMProperty("uint32Scalar", Sca<Uint32>::get()));
    ci1.addProperty(CIMProperty("sint32Scalar", Sca<Sint32>::get()));
    ci1.addProperty(CIMProperty("uint64Scalar", Sca<Uint64>::get()));
    ci1.addProperty(CIMProperty("sint64Scalar", Sca<Sint64>::get()));
    ci1.addProperty(CIMProperty("real32Scalar", Sca<Real32>::get()));
    ci1.addProperty(CIMProperty("real64Scalar", Sca<Real64>::get()));
    ci1.addProperty(CIMProperty("char16Scalar", Sca<Char16>::get()));
    ci1.addProperty(CIMProperty("stringScalar", Sca<String>::get()));
    ci1.addProperty(CIMProperty("datetimeScalar", Sca<CIMDateTime>::get()));
    ci1.addProperty(CIMProperty("instanceScalar", Sca<CIMInstance>::get()));
    ci1.addProperty(CIMProperty("objectScalar", Sca<CIMObject>::get()));

    ci1.addProperty(CIMProperty("booleanArray", Arr<Boolean>::get(2)));
    ci1.addProperty(CIMProperty("uint8Array", Arr<Uint8>::get(2)));
    ci1.addProperty(CIMProperty("sint8Array", Arr<Sint8>::get(2)));
    ci1.addProperty(CIMProperty("uint16Array", Arr<Uint16>::get(2)));
    ci1.addProperty(CIMProperty("sint16Array", Arr<Sint16>::get(2)));
    ci1.addProperty(CIMProperty("uint32Array", Arr<Uint32>::get(2)));
    ci1.addProperty(CIMProperty("sint32Array", Arr<Sint32>::get(2)));
    ci1.addProperty(CIMProperty("uint64Array", Arr<Uint64>::get(2)));
    ci1.addProperty(CIMProperty("sint64Array", Arr<Sint64>::get(2)));
    ci1.addProperty(CIMProperty("real32Array", Arr<Real32>::get(2)));
    ci1.addProperty(CIMProperty("real64Array", Arr<Real64>::get(2)));
    ci1.addProperty(CIMProperty("char16Array", Arr<Char16>::get(2)));
    ci1.addProperty(CIMProperty("stringArray", Arr<String>::get(2)));
    ci1.addProperty(CIMProperty("datetimeArray", Arr<CIMDateTime>::get(2)));
    ci1.addProperty(CIMProperty("instanceArray", Arr<CIMInstance>::get(2)));
    ci1.addProperty(CIMProperty("objectArray", Arr<CIMObject>::get(2)));

    CIMObjectPath cop = client.createInstance(NAMESPACE, ci1);
    assert(cop.toString() == "All_Class.Key=9999");

    // Get instance back and check whether identical.

    CIMInstance ci2 = client.getInstance(NAMESPACE, cop);
    assert(ci1.identical(ci2));

    // Create instance again:

    cop = client.createInstance(NAMESPACE, ci2);
    assert(cop.toString() == "All_Class.Key=9999");

    // Get instance back again:

    CIMInstance ci3 = client.getInstance(NAMESPACE, cop);
    assert(ci2.identical(ci3));
}

void test_instance_null(CIMClient& client)
{
    // Create instance:

    CIMInstance ci1("All_Class");
    ci1.addProperty(CIMProperty("Key", Uint32(9999)));
    ci1.addProperty(CIMProperty("booleanScalar", Sca<Boolean>::null()));
    ci1.addProperty(CIMProperty("uint8Scalar", Sca<Uint8>::null()));
    ci1.addProperty(CIMProperty("sint8Scalar", Sca<Sint8>::null()));
    ci1.addProperty(CIMProperty("uint16Scalar", Sca<Uint16>::null()));
    ci1.addProperty(CIMProperty("sint16Scalar", Sca<Sint16>::null()));
    ci1.addProperty(CIMProperty("uint32Scalar", Sca<Uint32>::null()));
    ci1.addProperty(CIMProperty("sint32Scalar", Sca<Sint32>::null()));
    ci1.addProperty(CIMProperty("uint64Scalar", Sca<Uint64>::null()));
    ci1.addProperty(CIMProperty("sint64Scalar", Sca<Sint64>::null()));
    ci1.addProperty(CIMProperty("real32Scalar", Sca<Real32>::null()));
    ci1.addProperty(CIMProperty("real64Scalar", Sca<Real64>::null()));
    ci1.addProperty(CIMProperty("char16Scalar", Sca<Char16>::null()));
    ci1.addProperty(CIMProperty("stringScalar", Sca<String>::null()));
    ci1.addProperty(CIMProperty("datetimeScalar", Sca<CIMDateTime>::null()));
    ci1.addProperty(CIMProperty("instanceScalar", Sca<CIMInstance>::null()));
    ci1.addProperty(CIMProperty("objectScalar", Sca<CIMObject>::null()));

    ci1.addProperty(CIMProperty("booleanArray", Arr<Boolean>::null()));
    ci1.addProperty(CIMProperty("uint8Array", Arr<Uint8>::null()));
    ci1.addProperty(CIMProperty("sint8Array", Arr<Sint8>::null()));
    ci1.addProperty(CIMProperty("uint16Array", Arr<Uint16>::null()));
    ci1.addProperty(CIMProperty("sint16Array", Arr<Sint16>::null()));
    ci1.addProperty(CIMProperty("uint32Array", Arr<Uint32>::null()));
    ci1.addProperty(CIMProperty("sint32Array", Arr<Sint32>::null()));
    ci1.addProperty(CIMProperty("uint64Array", Arr<Uint64>::null()));
    ci1.addProperty(CIMProperty("sint64Array", Arr<Sint64>::null()));
    ci1.addProperty(CIMProperty("real32Array", Arr<Real32>::null()));
    ci1.addProperty(CIMProperty("real64Array", Arr<Real64>::null()));
    ci1.addProperty(CIMProperty("char16Array", Arr<Char16>::null()));
    ci1.addProperty(CIMProperty("stringArray", Arr<String>::null()));
    ci1.addProperty(CIMProperty("datetimeArray", Arr<CIMDateTime>::null()));
    ci1.addProperty(CIMProperty("instanceArray", Arr<CIMInstance>::null()));
    ci1.addProperty(CIMProperty("objectArray", Arr<CIMObject>::null()));

    CIMObjectPath cop = client.createInstance(NAMESPACE, ci1);
    assert(cop.toString() == "All_Class.Key=9999");
}

template<class T>
struct Tst_Ret
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        CIMValue value = client.invokeMethod(
            NAMESPACE, CIMObjectPath("All_Class.Key=9999"), name, in, out);

        T x;
        value.get(x);

        if (!_equal(x, Sca<T>::get()))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

template<class T>
struct Tst_Sca_Parms
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        in.append(CIMParamValue("p1", Sca<T>::get()));

        CIMValue value = client.invokeMethod(
            NAMESPACE, CIMObjectPath("All_Class.Key=9999"), name, in, out);

        Uint32 rv;
        value.get(rv);

        if (value.isNull() || rv != 100)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        if (out.size() != 1)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        CIMParamValue cpv = out[0];
        assert(cpv.getParameterName() == "p2");
        T x;
        cpv.getValue().get(x);

        if (!_equal(x, Sca<T>::get()))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

template<class T>
struct Tst_Arr_Parms
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        in.append(CIMParamValue("p1", Arr<T>::get(3)));

        CIMValue value = client.invokeMethod(
            NAMESPACE, CIMObjectPath("All_Class.Key=9999"), name, in, out);

        Uint32 rv;
        value.get(rv);

        if (value.isNull() || rv != 100)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        if (out.size() != 1)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        CIMParamValue cpv = out[0];
        assert(cpv.getParameterName() == "p2");
        Array<T> x;
        cpv.getValue().get(x);

        if (!_equal(x, Arr<T>::get(3)))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

void test_invoke(CIMClient& client)
{
    printf("===== test_invoke()\n");

    try
    {
        // Call foo1().

        CIMInstance ci;
        {
            Array<CIMParamValue> inParams;
            Array<CIMParamValue> outParams;

            CIMValue value = client.invokeMethod(
                "root/cimv2",
                CIMObjectPath("CMPL_Embedded.Key=1"),
                "foo1",
                inParams,
                outParams);

            assert(value.getType() == CIMTYPE_INSTANCE);

            value.get(ci);
            // cimple::print(ci);
        }

        // Call foo2().
        {
            Array<CIMParamValue> inParams;
            Array<CIMParamValue> outParams;

            CIMInstance arg2("CMPL_Embedded2");
            arg2.addProperty(CIMProperty("Key", Uint32(22222)));

            inParams.append(CIMParamValue("arg1", ci));
            inParams.append(CIMParamValue("arg2", arg2));

            CIMValue value = client.invokeMethod(
                "root/cimv2",
                CIMObjectPath("CMPL_Embedded.Key=1"),
                "foo2",
                inParams,
                outParams);

            for (size_t i = 0; i < outParams.size(); i++)
            {
                const CIMParamValue& pv = outParams[i];
                const CIMValue v = pv.getValue();

                if (pv.getParameterName() == "arg3")
                {
                    CIMInstance t;
                    assert(v.getType() == CIMTYPE_INSTANCE);
                    v.get(t);
                    // cimple::print(t);
                }
            }

            // Check return value:
            {
                assert(value.getType() == CIMTYPE_STRING);
                String x;
                value.get(x);
                assert(x == "Hello");
            }
        }
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        assert(0);
    }
}

int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connectLocal();
        test_instance(client);
        test_instance_null(client);
        assert(Tst_Ret<Boolean>::func(client, "booleanReturn"));
        assert(Tst_Ret<Uint8>::func(client, "uint8Return"));
        assert(Tst_Ret<Sint8>::func(client, "sint8Return"));
        assert(Tst_Ret<Uint16>::func(client, "uint16Return"));
        assert(Tst_Ret<Sint16>::func(client, "sint16Return"));
        assert(Tst_Ret<Uint32>::func(client, "uint32Return"));
        assert(Tst_Ret<Sint32>::func(client, "sint32Return"));
        assert(Tst_Ret<Uint64>::func(client, "uint64Return"));
        assert(Tst_Ret<Sint64>::func(client, "sint64Return"));
        assert(Tst_Ret<Real32>::func(client, "real32Return"));
        assert(Tst_Ret<Real64>::func(client, "real64Return"));
        assert(Tst_Ret<Char16>::func(client, "char16Return"));
        assert(Tst_Ret<String>::func(client, "stringReturn"));
        assert(Tst_Ret<CIMDateTime>::func(client, "datetimeReturn"));
        assert(Tst_Ret<CIMInstance>::func(client, "instanceReturn"));
        assert(Tst_Ret<CIMObject>::func(client, "objectReturn"));

        assert(Tst_Sca_Parms<Boolean>::func(client, "booleanScalarParams"));
        assert(Tst_Sca_Parms<Uint8>::func(client, "uint8ScalarParams"));
        assert(Tst_Sca_Parms<Sint8>::func(client, "sint8ScalarParams"));
        assert(Tst_Sca_Parms<Uint16>::func(client, "uint16ScalarParams"));
        assert(Tst_Sca_Parms<Sint16>::func(client, "sint16ScalarParams"));
        assert(Tst_Sca_Parms<Uint32>::func(client, "uint32ScalarParams"));
        assert(Tst_Sca_Parms<Sint32>::func(client, "sint32ScalarParams"));
        assert(Tst_Sca_Parms<Uint64>::func(client, "uint64ScalarParams"));
        assert(Tst_Sca_Parms<Sint64>::func(client, "sint64ScalarParams"));
        assert(Tst_Sca_Parms<Real32>::func(client, "real32ScalarParams"));
        assert(Tst_Sca_Parms<Real64>::func(client, "real64ScalarParams"));
        assert(Tst_Sca_Parms<Char16>::func(client, "char16ScalarParams"));
        assert(Tst_Sca_Parms<String>::func(client, "stringScalarParams"));
        assert(Tst_Sca_Parms<CIMDateTime>::func(client,"datetimeScalarParams"));
        assert(Tst_Sca_Parms<CIMInstance>::func(client,"instanceScalarParams"));
        assert(Tst_Sca_Parms<CIMObject>::func(client, "objectScalarParams"));
        assert(Tst_Sca_Parms<CIMObjectPath>::func(
            client, "referenceScalarParams"));

        assert(Tst_Arr_Parms<Boolean>::func(client, "booleanArrayParams"));
        assert(Tst_Arr_Parms<Uint8>::func(client, "uint8ArrayParams"));
        assert(Tst_Arr_Parms<Sint8>::func(client, "sint8ArrayParams"));
        assert(Tst_Arr_Parms<Uint16>::func(client, "uint16ArrayParams"));
        assert(Tst_Arr_Parms<Sint16>::func(client, "sint16ArrayParams"));
        assert(Tst_Arr_Parms<Uint32>::func(client, "uint32ArrayParams"));
        assert(Tst_Arr_Parms<Sint32>::func(client, "sint32ArrayParams"));
        assert(Tst_Arr_Parms<Uint64>::func(client, "uint64ArrayParams"));
        assert(Tst_Arr_Parms<Sint64>::func(client, "sint64ArrayParams"));
        assert(Tst_Arr_Parms<Real32>::func(client, "real32ArrayParams"));
        assert(Tst_Arr_Parms<Real64>::func(client, "real64ArrayParams"));
        assert(Tst_Arr_Parms<Char16>::func(client, "char16ArrayParams"));
        assert(Tst_Arr_Parms<String>::func(client, "stringArrayParams"));
        assert(Tst_Arr_Parms<CIMDateTime>::func(client, "datetimeArrayParams"));
        assert(Tst_Arr_Parms<CIMInstance>::func(client, "instanceArrayParams"));
        assert(Tst_Arr_Parms<CIMObjectPath>::func(
            client,"referenceArrayParams"));
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
