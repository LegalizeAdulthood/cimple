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

#ifndef _cimple_UUID_h
#define _cimple_UUID_h

#include "config.h"
#include "Type.h"

#define CIMPLE_UUID_STRING_SIZE 33

CIMPLE_NAMESPACE_BEGIN

struct UUID
{
    uint32 time_low;
    uint16 time_mid;
    uint16 time_hi_and_version;
    uint8 clock_seq_hi_and_reserved;
    uint8 clock_seq_low;
    uint8 node[6];
};

CIMPLE_CIMPLE_LINKAGE
int create_uuid(UUID& uuid);

CIMPLE_CIMPLE_LINKAGE
void uuid_to_string(const UUID& uuid, char str[CIMPLE_UUID_STRING_SIZE]);

CIMPLE_NAMESPACE_END

#endif /* _cimple_UUID_h */
