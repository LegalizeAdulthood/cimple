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
/*
    Test of the packing and unpacking functions in Enc
    
*/

//#include "Link.h"
#include <cimple/cimple.h>
#include <cassert>
#include <cstdio>
#include <cimple/Enc.h>
#include <cimple/Buffer.h>


using namespace cimple;

uint64 counter;
// generate a standard test function that packs the defined value
// and unpacks it.  The return is true if the unpacked value equals
// the packed value
// 
#define TESTSCALARFUNC(TYPE, NAME, PACK, UNPACK) \
boolean NAME(TYPE in) \
{ \
    Buffer b; \
    size_t pos = 0; \
    PACK(b, in); \
    TYPE out; \
    UNPACK(b, pos, out); \
    counter++; \
    return(in == out); \
}
#define TESTARRAYFUNC(TYPE, NAME, PACK, UNPACK) \
boolean NAME(Array< TYPE > in ) \
{ \
    Buffer b; \
    size_t pos = 0; \
    PACK(b, in); \
    Array< TYPE > out; \
    UNPACK(b, pos, out); \
    counter++; \
    return(in == out); \
}

TESTSCALARFUNC(uint8, testuint8, pack_uint8, unpack_uint8);
TESTSCALARFUNC(uint16, testuint16, pack_uint16, unpack_uint16);
TESTSCALARFUNC(uint32, testuint32, pack_uint32, unpack_uint32);
TESTSCALARFUNC(uint64, testuint64, pack_uint64, unpack_uint64);

TESTSCALARFUNC(sint8, testsint8, pack_sint8, unpack_sint8);
TESTSCALARFUNC(sint16, testsint16, pack_sint16, unpack_sint16);
TESTSCALARFUNC(sint32, testsint32, pack_sint32, unpack_sint32);
TESTSCALARFUNC(sint64, testsint64, pack_sint64, unpack_sint64);

TESTSCALARFUNC(real32, testreal32, pack_real32, unpack_real32);
TESTSCALARFUNC(real64, testreal64, pack_real64, unpack_real64);

TESTSCALARFUNC(Datetime, testdatetime, pack_datetime, unpack_datetime);

TESTSCALARFUNC(String, teststring, pack_string, unpack_string);

// Array test functions
TESTARRAYFUNC(uint8, testuint8Array, pack_uint8_array, unpack_uint8_array);
TESTARRAYFUNC(uint16, testuint16Array, pack_uint16_array, unpack_uint16_array);
TESTARRAYFUNC(uint32, testuint32Array, pack_uint32_array, unpack_uint32_array);
TESTARRAYFUNC(uint64, testuint64Array, pack_uint64_array, unpack_uint64_array);

TESTARRAYFUNC(sint8, testsint8Array, pack_sint8_array, unpack_sint8_array);
TESTARRAYFUNC(sint16, testsint16Array, pack_sint16_array, unpack_sint16_array);
TESTARRAYFUNC(sint32, testsint32Array, pack_sint32_array, unpack_sint32_array);
TESTARRAYFUNC(sint64, testsint64Array, pack_sint64_array, unpack_sint64_array);

TESTARRAYFUNC(String, teststringArray, pack_string_array, unpack_string_array);

TESTARRAYFUNC(real32, testreal32Array, pack_real32_array, unpack_real32_array);
TESTARRAYFUNC(real64, testreal64Array, pack_real64_array, unpack_real64_array);
TESTARRAYFUNC(Datetime, testdatetimeArray, pack_datetime_array, unpack_datetime_array);

/*
boolean testuint32Array(Array<uint32> in )
{
    Buffer b;
    pack_uint32_array(b, in);

    size_t pos = 0;
    Array<uint32> out;
    unpack_uint32_array(b, pos, out);

    for (size_t i = 0; i < out.size(); i++)
    {
        printf("====[%u][%u]\n", in[i], out[i]);
    }

    counter++;
    return(in == out);
}
*/

int main(int argc, char** argv)
{
    printf("Test+++ %s\n",argv[0]);
    
    {
        boolean in;
        in = true;
        Buffer b;
        pack_boolean(b, in);
        boolean out = false;
        size_t pos = 0;
        unpack_boolean(b, pos, out);
        assert(in == out);
        assert(out == true);

        b.clear();
        pos = 0;
        in = false;
        pack_boolean(b, in);
        out = true;
        unpack_boolean(b, pos, out);
        assert(in == out);
        assert(out == false);
    }

    {
        uint8 interval = 1;
        for (uint8 i = 0 ; i < CIMPLE_UINT8_MAX - interval ; i+=interval)
        {
            assert(testuint8(i));
        }
        assert(testuint8(CIMPLE_UINT8_MAX));
    }
    {
        uint16 interval = CIMPLE_UINT16_MAX / 10;
        for (uint16 i = 0 ; i < CIMPLE_UINT16_MAX - interval ; i+=interval)
        {
            assert(testuint16(i));
        }
        assert(testuint16(CIMPLE_UINT16_MAX));
    }
    {
        uint32 interval = CIMPLE_UINT32_MAX / 10000;
        for (uint32 i = 0 ; i < CIMPLE_UINT32_MAX - interval ; i+=interval)
        {
            assert(testuint32(i));
        }
        assert(testuint32(CIMPLE_UINT32_MAX));
    }
    {
        uint64 interval = CIMPLE_UINT64_MAX / 10000;
        for (uint64 i = 0 ; i < CIMPLE_UINT64_MAX - interval ; i+=interval)
        {
            assert(testuint64(i));
        }
        assert(testuint64(CIMPLE_UINT64_MAX));
    }

    {
        sint8 interval = 1;
        for (sint8 i = 0 ; i < CIMPLE_SINT8_MAX - interval ; i+=interval)
        {
            assert(testsint8(i));
        }
        assert(testsint8(CIMPLE_SINT8_MAX));
    }
    {
        sint16 interval = CIMPLE_UINT16_MAX / 10;
        for (sint16 i = CIMPLE_SINT16_MIN ; i < CIMPLE_SINT16_MAX - interval
               ; i+=interval)
        {
            assert(testsint16(i));
        }
        assert(testsint16(CIMPLE_SINT16_MAX));
    }

    {
        sint32 interval = CIMPLE_SINT32_MAX / 10000;
        for (sint32 i = CIMPLE_SINT32_MIN ; i < CIMPLE_SINT32_MAX - interval
               ; i+=interval)
        {
            assert(testsint32(i));
        }
        assert(testsint32(CIMPLE_SINT32_MAX));
    }

    {
        sint64 interval = CIMPLE_SINT64_MAX / 10000;
        for (sint64 i = CIMPLE_SINT64_MIN ; i < (CIMPLE_SINT64_MAX - interval)
               ; i+=interval)
        {
            assert(testsint64(i));
        }
        assert(testsint64(CIMPLE_SINT64_MIN));
        assert(testsint64(CIMPLE_SINT64_MAX));
    }


    {
        real32 REAL_32_MAX = 10e5;
        real32 REAL_32_MIN = -10e5;
        assert(testsint64(1.75));
        assert(testsint64(0));
        assert(testsint64(REAL_32_MAX));
        assert(testsint64(REAL_32_MIN));

//      sint64 interval = CIMPLE_SINT64_MAX / 10000;
//      for (sint64 i = CIMPLE_SINT64_MIN ;
//          i < (CIMPLE_SINT64_MAX - interval) ; i+=interval)
//      {
//          assert(testsint64(i));
//      }
//      assert(testsint64(CIMPLE_SINT64_MIN));
//      assert(testsint64(CIMPLE_SINT64_MAX));
    }

    {
        real64 REAL_32_MAX = 10e5;
        real32 REAL_32_MIN = -10e5;
        assert(testsint64(1.75));
        assert(testsint64(0));
        assert(testsint64(REAL_32_MAX));
        assert(testsint64(REAL_32_MIN));

//      sint64 interval = CIMPLE_SINT64_MAX / 10000;
//      for (sint64 i = CIMPLE_SINT64_MIN ;
//           i < (CIMPLE_SINT64_MAX - interval) ; i+=interval)
//      {
//          assert(testsint64(i));
//      }
//      assert(testsint64(CIMPLE_SINT64_MIN));
//      assert(testsint64(CIMPLE_SINT64_MAX));
    }

    {
        assert(testdatetime(Datetime::now()));

    }
    String ASCIIString = "abcdefghijklmnopqurstuvwxyz0123456789" 
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "!\"#$%\'()*+`-,/:;<=>?@[\\]^_{|}~" ;
    String longString;
    {


        assert(teststring(String("This is a String")));
        assert(teststring(String(ASCIIString)));

        String longString;
        for (uint32 i = 0 ; i < 10000 ; i++)
        {
            longString.append(ASCIIString);
            assert(teststring(longString));
        }
        printf("Long String size = %u\n", (unsigned int)longString.size());
    }
    //
    //  Test the corresponding Array pack and unpack functions
    // 
    // 
    {
        assert(testuint32Array(Array<uint32>::make(0)));
        assert(testuint32Array(Array<uint32>::make(8192, 0, 16, 9999)));
        assert(testuint32Array(Array<uint32>::make(0, CIMPLE_UINT32_MAX)));

        Array<uint32> longArray;
        for (uint32 i = 0 ; i < 10000 ; i+=100)
        {
            longArray.append(i * 100);
            assert(testuint32Array(longArray));
        }
    }
    {
        assert(testsint32Array(Array<sint32>::make(0)));
        assert(testsint32Array(Array<sint32>::make(-8192, 0, 16, 9999)));
        assert(testsint32Array(Array<sint32>::make(CIMPLE_SINT32_MIN, 0, CIMPLE_SINT32_MAX)));

        Array<sint32> longArray;
        for (uint32 i = 0 ; i < 10000 ; i+=100)
        {
            longArray.append(i * 100);
            longArray.append(-(i*100));
            assert(testsint32Array(longArray));
        }
    }

    {
        String empty = "";
        assert(teststringArray(Array<String>::make(ASCIIString, ASCIIString)));

        assert(teststringArray(Array<String>::make(empty, ASCIIString)));
    }

    printf("Total tests run = %lu\n", (long unsigned int)counter);

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}
