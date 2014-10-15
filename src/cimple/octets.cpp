
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

#include "octets.h"

CIMPLE_NAMESPACE_BEGIN

String octets_to_string(const unsigned char* data, uint32 size)
{
    char buffer[32];
    sprintf(buffer, "0x%08X", size + 4);

    String s = buffer;

    for (size_t i = 0; i < size; i++)
    {
        sprintf(buffer, "%02X", data[i]);
        s.append(buffer);
    }

    return s;
}

ssize_t string_to_octets(
    const String& str, 
    unsigned char* data, 
    uint32 size)
{
    if (str.size() % 2 || str.size() < 10)
        return -1;

    // Scan in the encoding length.

    const char* s = str.c_str();

    uint32 n;

    if (sscanf(s, "0x%08X", &n) != 1)
        return -1;

    if (n < 4)
        return -1;

    // Verify that string is proper size.

    n -= 4;

    if (str.size() != 10 + n * 2)
        return -1;

    // Scan in the octets themselves.

    s += 10;

    if (n > size)
        return n;

    for (uint32 i = 0; i < n; i++, s += 2)
    {
        uint32 m;

        if (sscanf(s, "%02X", &m) != 1)
            return -1;

        data[i] = m;
    }

    return n;
}

CIMPLE_CIMPLE_LINKAGE int string_to_octets(
    const String& str, 
    Array<unsigned char>& octets)
{
    octets.clear();

    ssize_t n = string_to_octets(str, 0, 0);

    if (n == -1)
        return -1;

    if (n)
    {
        octets.reserve(n);

        if (string_to_octets(str, octets.data(), size_t(n)) == -1)
            return -1;

        __Array_Rep** rep = (__Array_Rep**)&octets;
        (*rep)->size = n;
    }

    return 0;
}

CIMPLE_NAMESPACE_END

