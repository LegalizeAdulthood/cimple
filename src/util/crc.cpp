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

#include "crc.h"

//==============================================================================
//
// This code adapted from RFC 1952 (GZIP file format specification version 4.3)
//
//==============================================================================

static unsigned int _table[256];
static bool _table_computed = false;

void _compute_table(void)
{
    unsigned int c;

    int n;
    int k;

    for (n = 0; n < 256; n++) 
    {
        c = (unsigned int) n;

        for (k = 0; k < 8; k++) 
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }

        _table[n] = c;
    }

    _table_computed = true;
}

unsigned int crc_update(unsigned int crc, unsigned char *buf, int len)
{
    unsigned int c = crc ^ 0xffffffffL;
    int n;

    if (!_table_computed)
        _compute_table();

    for (n = 0; n < len; n++) 
        c = _table[(c ^ buf[n]) & 0xff] ^ (c >> 8);

    return c ^ 0xffffffffL;
}

unsigned int crc_compute(unsigned char *buf, int len)
{
    return crc_update(0L, buf, len);
}

