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

#include <string.h>
#include <ctype.h>
#include "MOF_String.h"
#include "MOF_Buffer.h"
#include "MOF_Error.h"

void MOF_fix_case(char* p, const char* q)
{
    if (MOF_stricmp(p, q) == 0 && strcmp(p, q) != 0)
    {
        strcpy(p, q);
        MOF_warning_printf("changed case of \"%s\" to \"%s\"", p, q);
    }
}

void MOF_strtolower(char* s)
{
    for (; *s; s++)
        *s = tolower(*s);
}

size_t MOF_count_char(
    const char* str, 
    size_t length, 
    char ch)
{
    size_t i;
    size_t count = 0;

    for (i = 0; i < length; i++)
    {
        if (str[i] == ch)
            count++;
    }

    return count;
}

size_t MOF_char16_to_asc7(
    MOF_char16 ch, 
    char str[7])
{
    if(ch < 0x80) 
    {
        str[0] = (char)ch;
        str[1] = '\0';
        return 1;
    }
    else
        return sprintf(str, "\\X%04X", ch);
}

size_t MOF_asc7_to_char16(
    const char* str,
    MOF_char16* ch)
{
    const char* p = str;

    if (p[0] == '\\' && (p[1] == 'X' || p[1] == 'x'))
    {
        char hex_digits[5];
        size_t i;
        unsigned long x;
        char* end = 0;

        p += 2;

        /* 
         * Count the number of hex digits (but not more than four).
         */

        for (i = 0; i < 4; i++, p++)
        {
            if (!isxdigit(*p))
                break;

            hex_digits[i] = *p;
        }

        if (i == 0)
            return (size_t)-1;

        hex_digits[i] = '\0';

        /*
         * Convert to unsigned long:
         */

        x = strtoul(hex_digits, &end, 16);
        MOF_ASSERT(end != 0 && *end == '\0');

        *ch = (MOF_char16)x;
        return 2 + i;
    }
    else
    {
        *ch = *p;
        return 1;
    }
}

char* MOF_unescape(const char* asc7)
{
    char* result = (char*)malloc(strlen(asc7) + 1);

    if (result == 0)
        return 0;

    char* p = result;

    for (; *asc7; asc7++)
    {
        if (*asc7 == '\\')
        {
            asc7++;

            if (*asc7 == '\0')
            {
                free(result);
                return 0;
            }

            switch (*asc7)
            {
                case 'b':
                    *p++ = '\b';
                    break;

                case 't':
                    *p++ = '\t';
                    break;

                case 'n':
                    *p++ = '\n';
                    break;

                case 'f':
                    *p++ = '\f';
                    break;

                case 'r':
                    *p++ = '\r';
                    break;

                case '"':
                    *p++ = '"';
                    break;

                case '\'':
                    *p++ = '\'';
                    break;

                case '\\':
                    *p++ = '\\';
                    break;

                case 'X':
                case 'x':
                {
                    MOF_char16 ch;

                    /*
                     * Convert asc7 to char16. The asc7 points to the 'X'
                     * character (not the '\' as the next routine expects).
                     */

                    size_t m = MOF_asc7_to_char16(&asc7[-1], &ch);

                    if (m == (size_t)-1)
                        return 0;

                    /*
                     * Convert char16 to asc7:
                     */

                    size_t n = MOF_char16_to_asc7(ch, p);

                    p += n;
                    asc7 += m - 2;

                    break;
                }

                default:
                    *p++ = *asc7;
            }
        }
        else
            *p++ = *asc7;
    }

    *p++ = '\0';
    return result;
}

char* MOF_escape(const char* asc7)
{
    MOF_Buffer buf;

    buf.reserve(strlen(asc7) + 1);

    for (const char* p = asc7; *p; )
    {
        MOF_char16 ch;
        
        p += MOF_asc7_to_char16(p, &ch);

        switch (ch)
        {
            case '\b':
                buf.append('\\');
                buf.append('b');
                break;

            case '\t':
                buf.append('\\');
                buf.append('t');
                break;

            case '\n':
                buf.append('\\');
                buf.append('n');
                break;

            case '\f':
                buf.append('\\');
                buf.append('f');
                break;

            case '\r':
                buf.append('\\');
                buf.append('r');
                break;

            case '"':
                buf.append('\\');
                buf.append('"');
                break;

            case '\'':
                buf.append('\\');
                buf.append('\'');
                break;

            case '\\':
                buf.append('\\');
                buf.append('\\');
                break;

            default:
            {
                char tmp[7];
                MOF_char16_to_asc7(ch, tmp);
                buf.append(tmp, strlen(tmp));
            }
        }
    }

    buf.append('\0');
    return buf.steal_data();
}

