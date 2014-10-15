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

static char _digit[256] = 
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

CIMPLE_NAMESPACE_END
