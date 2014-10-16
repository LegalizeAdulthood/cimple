#include "Integer.h"
#include <cstddef>
#include <cstdio>
#include <cctype>

using namespace Pegasus;

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

static int _Hex_Str_To_Uint64(const char* str, P_Uint64* px)
{
    const char* p;
    P_Uint64 x = 0;
    P_Uint64 r = 1;
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
        P_Uint64 t;
        P_Uint64 d;
        P_Uint64 digit;

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

static int _Dec_Str_To_Uint64(const char* str, P_Uint64* px)
{
    const char* p;
    P_Uint64 x = 0;
    P_Uint64 r = 1;

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
        P_Uint64 t;
        P_Uint64 d;

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

int Uint64_From_Str(P_Uint64& self, const char* str)
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
                    P_Uint64 r;
                    P_Uint64 d;

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

    if (_Dec_Str_To_Uint64(str, &self) == 0)
        return 0;

    if (_Hex_Str_To_Uint64(str, &self) == 0)
        return 0;

    return -1;
}

int Sint64_From_Str(P_Sint64& self, const char* str)
{
    char sign;
    P_Uint64 t;

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

    /* Convert to Uint64. */

    if (Uint64_From_Str(t, str) != 0)
        return -1;

    /* See if it is within range for Sint64. */

    if (sign == '+')
    {
        if (t > CIMPLE_UINT64_LITERAL(9223372036854775807))
            return -1;

        self = (P_Sint64)t;
    }
    else if (sign == '-')
    {
        if (t > CIMPLE_UINT64_LITERAL(9223372036854775808))
            return -1;

        self = (P_Sint64)-t;
    }

    return 0;
}

int Sint8_From_Str(P_Sint8& self, const char* str)
{
    P_Sint64 x;

    if (Sint64_From_Str(x, str) != 0 ||
        x < CIMPLE_SINT8_MIN || x > CIMPLE_SINT8_MAX)
    {
        return -1;
    }

    self = (P_Sint8)x;

    return 0;
}

int Sint16_From_Str(P_Sint16& self, const char* str)
{
    P_Sint64 x;

    if (Sint64_From_Str(x, str) != 0 ||
        x < CIMPLE_SINT16_MIN || x > CIMPLE_SINT16_MAX)
    {
        return -1;
    }

    self = (P_Sint16)x;

    return 0;
}

int Sint32_From_Str(P_Sint32& self, const char* str)
{
    P_Sint64 x;

    if (Sint64_From_Str(x, str) != 0 ||
        x < CIMPLE_SINT32_MIN || x > CIMPLE_SINT32_MAX)
    {
        return -1;
    }

    self = (P_Sint32)x;

    return 0;
}

int Uint8_From_Str(P_Uint8& self, const char* str)
{
    P_Uint64 x;

    if (Uint64_From_Str(x, str) != 0 || x > CIMPLE_UINT8_MAX)
        return -1;

    self = (P_Uint8)x;
    return 0;
}

int Uint16_From_Str(P_Uint16& self, const char* str)
{
    P_Uint64 x;

    if (Uint64_From_Str(x, str) != 0 || x > CIMPLE_UINT16_MAX)
        return -1;

    self = (P_Uint16)x;
    return 0;
}

int Uint32_From_Str(P_Uint32& self, const char* str)
{
    P_Uint64 x;

    if (Uint64_From_Str(x, str) != 0 || x > CIMPLE_UINT32_MAX)
        return -1;

    self = (P_Uint32)x;
    return 0;
}

CIMPLE_NAMESPACE_END
