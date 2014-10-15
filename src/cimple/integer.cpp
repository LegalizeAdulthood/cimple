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

#include "integer.h"
#include <cstddef>
#include <cstdio>
#include <cctype>

CIMPLE_NAMESPACE_BEGIN

static int _digit[256] = 
{
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

static int _isdigit[256] = 
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

static int _hex_str_to_uint64(const char* str, uint64* px)
{
    const char* p;
    uint64 x = 0;
    uint64 r = 1;
    size_t n = 0;

    /* Skip over '0x' or '0X'. */

    if (!(str[0] == '0' && tolower(str[1]) == 'x'))
        return -1;

    str += 2;

    /* Reject empty strings. */

    if (*str == '\0')
        return -1;

    /* Seek the end of the string. */

    for (p = str; *p; p++)
        ;

    /* Handle digit by digit. */

    for (n = 0; p != str; n++)
    {
        char c = *--p;
        uint64 t;
        uint64 d;
        uint64 digit;

        if (n == 16)
            return -1;

        /* ATTN: Optimize this with a lookup table. */
        switch (c)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                digit = c - '0';
                break;

            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                digit = c - 'A' + 10;
                break;

            default:
                return -1;
        }

        d = r * digit;
        t = x + d;
        x = t;
        r *= 16;
    }

    *px = x;
    return 0;
}

static int _dec_str_to_uint64(const char* str, uint64* px)
{
    const char* p;
    uint64 x = 0;
    uint64 r = 1;

    /* Reject empty strings. */

    if (*str == '\0')
        return -1;

    /* Seek end of string. */

    for (p = str; *p; p++)
        ;

    /* Reject strings that start with '0' and are longer than one digit. */

    if (*str == '0' && p - str > 1)
        return -1;

    /* Process each digit. */

    while (p != str)
    {
        char c = *--p;
        uint64 t;
        uint64 d;

        {
            int digit = _digit[(unsigned char)c];

            if (digit < 0)
                return -1;

            d = r * digit;
        }

        if (d && d < x)
            return -1;

        t = x + d;

        if (t < x)
            return -1;

        x = t;
        r *= 10;
    }

    *px = x;
    return 0;
}

int str_to_uint64(const char* str, uint64& self)
{
    int w;

    /* Optimize for single-digit case. */

    w = _digit[(unsigned char)str[0]];

    if (w >= 0)
    {
        int x;

        if (str[1] == '\0')
        {
            self = w;
            return 0;
        }

        /* Optimize for double-digit case. */

        x = _digit[(unsigned char)str[1]];

        if (x >= 0)
        {
            int y;

            if (str[2] == '\0')
            {
                self = w * 10 + x;
                return 0;
            }

            /* Optimize for tripple-digit case. */

            y = _digit[(unsigned char)str[2]];

            if (y >= 0)
            { 
                int z;

                if (str[3] == '\0')
                {
                    self = w * 100 + x * 10 + y;
                    return 0;
                }

                /* Optimize for quaddruple-digit case. */

                z = _digit[(unsigned char)str[3]];

                if (z >= 0)
                {
                    if (str[4] == '\0')
                    {
                        self = w * 1000 + x * 100 + y * 10 + z;
                        return 0;
                    }
                }

                /* Handle remaining digits with loop. */
                {
                    int digits[20];
                    size_t n;
                    uint64 r;
                    uint64 d;

                    digits[0] = w;
                    digits[1] = x;
                    digits[2] = y;
                    digits[3] = z;

                    str += 4;
                    n = 4;
                    r = 1;
                    d = 0;

                    while (*str)
                    {
                        int digit;

                        if (n == 20)
                            return -1;

                        digit = _digit[(unsigned char)*str++];

                        if (digit < 0)
                            return -1;

                        digits[n++] = digit;
                    }

                    while (n--)
                    {
                        d += r * digits[n];
                        r *= 10;
                    }

                    self = d;
                    return 0;
                }
            }
        }
    }

    if (_dec_str_to_uint64(str, &self) == 0)
        return 0;

    if (_hex_str_to_uint64(str, &self) == 0)
        return 0;

    return -1;
}

int str_to_sint64(const char* str, sint64& self)
{
    char sign;
    uint64 t;

    /* Get sign. */

    if (*str == '+')
    {
        sign = '+';
        str++;
    }
    else if (*str == '-')
    {
        sign = '-';
        str++;
    }
    else
        sign = '+';

    /* Convert to uint64. */

    if (str_to_uint64(str, t) != 0)
        return -1;

    /* See if it is within range for sint64. */

    if (sign == '+')
    {
        if (t > CIMPLE_UINT64_LITERAL(9223372036854775807))
            return -1;

        self = (sint64)t;
    }
    else if (sign == '-')
    {
        if (t > CIMPLE_UINT64_LITERAL(9223372036854775808))
            return -1;

        self = (sint64)-t;
    }

    return 0;
}

int str_to_sint8(const char* str, sint8& self)
{
    sint64 x;

    if (str_to_sint64(str, x) != 0 || 
        x < CIMPLE_SINT8_MIN || x > CIMPLE_SINT8_MAX)
    {
        return -1;
    }

    self = (sint8)x;

    return 0;
}

int str_to_sint16(const char* str, sint16& self)
{
    sint64 x;

    if (str_to_sint64(str, x) != 0 || 
        x < CIMPLE_SINT16_MIN || x > CIMPLE_SINT16_MAX)
    {
        return -1;
    }

    self = (sint16)x;

    return 0;
}

int str_to_sint32(const char* str, sint32& self)
{
    sint64 x;

    if (str_to_sint64(str, x) != 0 || 
        x < CIMPLE_SINT32_MIN || x > CIMPLE_SINT32_MAX)
    {
        return -1;
    }

    self = (sint32)x;

    return 0;
}

int str_to_uint8(const char* str, uint8& self)
{
    uint64 x;

    if (str_to_uint64(str, x) != 0 || x > CIMPLE_UINT8_MAX)
        return -1;

    self = (uint8)x;
    return 0;
}

int str_to_uint16(const char* str, uint16& self)
{
    uint64 x;

    if (str_to_uint64(str, x) != 0 || x > CIMPLE_UINT16_MAX)
        return -1;

    self = (uint16)x;
    return 0;
}

int str_to_uint32(const char* str, uint32& self)
{
    uint64 x;

    if (str_to_uint64(str, x) != 0 || x > CIMPLE_UINT32_MAX)
        return -1;

    self = (uint32)x;
    return 0;
}

struct Uint_Str
{
    const char* str;
    size_t size;
};

static Uint_Str _uint_strings[] =
{
    { "0", 1 },
    { "1", 1 },
    { "2", 1 },
    { "3", 1 },
    { "4", 1 },
    { "5", 1 },
    { "6", 1 },
    { "7", 1 },
    { "8", 1 },
    { "9", 1 },
    { "10", 2 },
    { "11", 2 },
    { "12", 2 },
    { "13", 2 },
    { "14", 2 },
    { "15", 2 },
    { "16", 2 },
    { "17", 2 },
    { "18", 2 },
    { "19", 2 },
    { "20", 2 },
    { "21", 2 },
    { "22", 2 },
    { "23", 2 },
    { "24", 2 },
    { "25", 2 },
    { "26", 2 },
    { "27", 2 },
    { "28", 2 },
    { "29", 2 },
    { "30", 2 },
    { "31", 2 },
    { "32", 2 },
    { "33", 2 },
    { "34", 2 },
    { "35", 2 },
    { "36", 2 },
    { "37", 2 },
    { "38", 2 },
    { "39", 2 },
    { "40", 2 },
    { "41", 2 },
    { "42", 2 },
    { "43", 2 },
    { "44", 2 },
    { "45", 2 },
    { "46", 2 },
    { "47", 2 },
    { "48", 2 },
    { "49", 2 },
    { "50", 2 },
    { "51", 2 },
    { "52", 2 },
    { "53", 2 },
    { "54", 2 },
    { "55", 2 },
    { "56", 2 },
    { "57", 2 },
    { "58", 2 },
    { "59", 2 },
    { "60", 2 },
    { "61", 2 },
    { "62", 2 },
    { "63", 2 },
    { "64", 2 },
    { "65", 2 },
    { "66", 2 },
    { "67", 2 },
    { "68", 2 },
    { "69", 2 },
    { "70", 2 },
    { "71", 2 },
    { "72", 2 },
    { "73", 2 },
    { "74", 2 },
    { "75", 2 },
    { "76", 2 },
    { "77", 2 },
    { "78", 2 },
    { "79", 2 },
    { "80", 2 },
    { "81", 2 },
    { "82", 2 },
    { "83", 2 },
    { "84", 2 },
    { "85", 2 },
    { "86", 2 },
    { "87", 2 },
    { "88", 2 },
    { "89", 2 },
    { "90", 2 },
    { "91", 2 },
    { "92", 2 },
    { "93", 2 },
    { "94", 2 },
    { "95", 2 },
    { "96", 2 },
    { "97", 2 },
    { "98", 2 },
    { "99", 2 },
    { "100", 3 },
    { "101", 3 },
    { "102", 3 },
    { "103", 3 },
    { "104", 3 },
    { "105", 3 },
    { "106", 3 },
    { "107", 3 },
    { "108", 3 },
    { "109", 3 },
    { "110", 3 },
    { "111", 3 },
    { "112", 3 },
    { "113", 3 },
    { "114", 3 },
    { "115", 3 },
    { "116", 3 },
    { "117", 3 },
    { "118", 3 },
    { "119", 3 },
    { "120", 3 },
    { "121", 3 },
    { "122", 3 },
    { "123", 3 },
    { "124", 3 },
    { "125", 3 },
    { "126", 3 },
    { "127", 3 },
};

template<class U>
struct uint_to_str
{
    static const char* func(char buf[22], U x, size_t& size)
    {
        if (x < 128)
        {
            size = _uint_strings[x].size;
            return _uint_strings[x].str;
        }

        char* p = &buf[21];
        *p = '\0';

        do
        {
            *--p = '0' + (x % 10);
            x = x / 10;
        }
        while (x);

        size = &buf[21] - p;
        return p;
    }
};

template<class S, class U>
struct sint_to_str
{
    static const char* func(char buf[22], S x, size_t& size)
    {
        if (x < 0)
        {
            char* p = &buf[21];
            *p = '\0';

            U t = U(-x);

            do
            {
                *--p = '0' + (t % 10);
                t = t / 10;
            }
            while (t);

            *--p = '-';

            size = &buf[21] - p;
            return p;
        }
        else
            return uint_to_str<U>::func(buf, U(x), size);
    }
};

const char* uint8_to_str(char buf[22], uint8 x, size_t& size)
{
    return uint_to_str<uint8>::func(buf, x, size);
}

const char* uint16_to_str(char buf[22], uint16 x, size_t& size)
{
    return uint_to_str<uint16>::func(buf, x, size);
}

const char* uint32_to_str(char buf[22], uint32 x, size_t& size)
{
    return uint_to_str<uint32>::func(buf, x, size);
}

const char* uint64_to_str(char buf[22], uint64 x, size_t& size)
{
    return uint_to_str<uint64>::func(buf, x, size);
}

const char* sint8_to_str(char buf[22], sint8 x, size_t& size)
{
    return sint_to_str<sint8, uint8>::func(buf, x, size);
}

const char* sint16_to_str(char buf[22], sint16 x, size_t& size)
{
    return sint_to_str<sint16,uint16>::func(buf, x, size);
}

const char* sint32_to_str(char buf[22], sint32 x, size_t& size)
{
    return sint_to_str<sint32, uint32>::func(buf, x, size);
}

const char* sint64_to_str(char buf[22], sint64 x, size_t& size)
{
    return sint_to_str<sint64, uint64>::func(buf, x, size);
}

CIMPLE_NAMESPACE_END
