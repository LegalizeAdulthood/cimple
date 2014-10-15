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
    Test functions in cimple/integer.cpp
*/

#include <cassert>
#include <cimple/config.h>
#include <cimple/Type.h>
#include <cimple/Array.h>
#include <cimple/integer.h>

using namespace cimple;

int main(int argc, char** argv)
{
    for (uint64 i = CIMPLE_UINT8_MIN ; i <= CIMPLE_UINT8_MAX; i++ )
    {
        char buf[22];
        size_t size;
        const char* sout = uint8_to_str(buf, i, size);
        assert(size != 0);
        uint8 out;
        assert(str_to_uint8(sout, out) == 0);
        assert(out == i);
    }

    for (sint64 i = CIMPLE_SINT8_MIN ; i <= CIMPLE_SINT8_MAX; i++ )
    {
        char buf[22];
        size_t size;
        const char* sout = sint8_to_str(buf, i, size);
        assert(size != 0);
        sint8 out;
        assert(str_to_sint8(sout, out) == 0);
        assert(out == i);
    }
    for (uint64 i = CIMPLE_UINT16_MIN ; i <= CIMPLE_UINT16_MAX; i++ )
    {
        char buf[22];
        size_t size;
        const char* sout = uint16_to_str(buf, i, size);
        assert(size != 0);
        uint16 out;
        assert(str_to_uint16(sout, out) == 0);
        assert(out == i);
    }

    for (sint64 i = CIMPLE_SINT16_MIN ; i <= CIMPLE_SINT16_MAX; i++ )
    {
        char buf[22];
        size_t size;
        const char* sout = sint16_to_str(buf, i, size);
        assert(size != 0);
        sint16 out;
        assert(str_to_sint16(sout, out) == 0);
        assert(out == i);
    }

    {
        Array<uint32> testList;
        testList.append(CIMPLE_UINT32_MIN);
        testList.append(CIMPLE_UINT32_MIN + 1);
        testList.append(CIMPLE_UINT32_MAX /2);
        testList.append(CIMPLE_UINT32_MAX - 1);
        testList.append(CIMPLE_UINT32_MAX);
    
        for (uint64 i = 0 ; i < testList.size(); i++ )
        {
            char buf[22];
            size_t size;
            const char* sout = uint32_to_str(buf, testList[i], size);
            //printf("str %s, size %u i %X\n", sout, size, testList[i]);
            assert(size != 0);
            uint32 out;
            assert(str_to_uint32(sout, out) == 0);
            assert(out == testList[i]);
        }
    }

    {
        Array<sint32> testList;
        testList.append(CIMPLE_SINT32_MIN);
        testList.append(CIMPLE_SINT32_MIN + 1);
        testList.append(-CIMPLE_SINT32_MAX /4);
        testList.append(-1);
        testList.append(0);
        testList.append(1);
        testList.append(CIMPLE_SINT32_MAX /4);
        testList.append(CIMPLE_SINT32_MAX - 1);
        testList.append(CIMPLE_SINT32_MAX);
    
        for (uint64 i = 0 ; i < testList.size(); i++ )
        {
            char buf[22];
            size_t size;
            const char* sout = sint32_to_str(buf, testList[i], size);
            //printf("str %s, size %d i %X\n", sout, size, testList[i]);
            assert(size != 0);
            sint32 out;
            assert(str_to_sint32(sout, out) == 0);
            assert(out == testList[i]);
        }
    }

    {
        Array<uint64> testList;
        testList.append(CIMPLE_UINT64_MIN);
        testList.append(CIMPLE_UINT64_MIN + 1);
        testList.append(CIMPLE_UINT64_MAX /2);
        testList.append(CIMPLE_UINT64_MAX - 1);
        testList.append(CIMPLE_UINT64_MAX);
    
        for (uint64 i = 0 ; i < testList.size(); i++ )
        {
            char buf[22];
            size_t size;
            const char* sout = uint64_to_str(buf, testList[i], size);
            //printf("str %s, size %u i %X\n", sout, size, testList[i]);
            assert(size != 0);
            uint64 out;
            assert(str_to_uint64(sout, out) == 0);
            assert(out == testList[i]);
        }
    }

    {
        Array<sint64> testList;
        testList.append(CIMPLE_SINT64_MIN);
        testList.append(CIMPLE_SINT64_MIN + 1);
        testList.append(-CIMPLE_SINT64_MAX /4);
        testList.append(-1);
        testList.append(0);
        testList.append(1);
        testList.append(CIMPLE_SINT64_MAX /4);
        testList.append(CIMPLE_SINT64_MAX - 1);
        testList.append(CIMPLE_SINT64_MAX);
    
        for (uint64 i = 0 ; i < testList.size(); i++ )
        {
            char buf[22];
            size_t size;
            const char* sout = sint64_to_str(buf, testList[i], size);
            //printf("str %s, size %d i %X\n", sout, size, testList[i]);
            assert(size != 0);
            sint64 out;
            assert(str_to_sint64(sout, out) == 0);
            assert(out == testList[i]);
        }
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}

