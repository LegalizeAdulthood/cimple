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

#ifndef _pegadapter_Integer_h
#define _pegadapter_Integer_h

#include <cimple/config.h>
#include <pegasus/utils/pegasus.h>
#include "typedefs.h"

CIMPLE_NAMESPACE_BEGIN

int Sint8_From_Str(P_Sint8& self, const char* str);
int Sint16_From_Str(P_Sint16& self, const char* str);
int Sint32_From_Str(P_Sint32& self, const char* str);
int Sint64_From_Str(P_Sint64& self, const char* str);

int Uint8_From_Str(P_Uint8& self, const char* str);
int Uint16_From_Str(P_Uint16& self, const char* str);
int Uint32_From_Str(P_Uint32& self, const char* str);
int Uint64_From_Str(P_Uint64& self, const char* str);

CIMPLE_NAMESPACE_END

#endif /* _pegadapter_Integer_h */
