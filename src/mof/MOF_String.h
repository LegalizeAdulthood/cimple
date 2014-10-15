/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#ifndef _MOF_String_h
#define _MOF_String_h

#include <MOF_Config.h>

#define MOF_stricmp strcasecmp

extern void MOF_fix_case(
    char* p, 
    const char* q);

extern void MOF_strtolower(
    char* s);

extern size_t MOF_count_char(
    const char* str, 
    size_t length, 
    char ch);

size_t MOF_char16_to_asc7(
    MOF_char16 ch, 
    char str[7]);

size_t MOF_asc7_to_char16(
    const char* str,
    MOF_char16* ch);

char* MOF_unescape(
    const char* asc7); 

char* MOF_escape(
    const char* asc7);

#endif /* _MOF_String_h */
