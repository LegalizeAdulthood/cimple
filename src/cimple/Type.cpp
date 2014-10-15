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

#include "Type.h"

CIMPLE_NAMESPACE_BEGIN

size_t const type_size[] =
{
    sizeof(boolean),
    sizeof(uint8),
    sizeof(sint8),
    sizeof(uint16),
    sizeof(sint16),
    sizeof(uint32),
    sizeof(sint32),
    sizeof(uint64),
    sizeof(sint64),
    sizeof(real32),
    sizeof(real64),
    sizeof(char16),
    sizeof(String),
    sizeof(Datetime),
};

const char* const type_name[] =
{
    "boolean",
    "uint8",
    "sint8",
    "uint16",
    "sint16",
    "uint32",
    "sint32",
    "uint64",
    "sint64",
    "real32",
    "real64",
    "char16",
    "string",
    "datetime",
};

CIMPLE_NAMESPACE_END
