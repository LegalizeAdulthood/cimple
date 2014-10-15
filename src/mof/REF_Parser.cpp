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

#include "REF_Parser.h"
#include "MOF_String.h"

size_t ref_line_num = 0;

const char* ref_input_first = 0;
const char* ref_input_last = 0;
char* ref_error_message = 0;
int ref_error_code = 0;
MOF_Object_Reference* ref_obj_ref = 0;

extern int REF_parse();

int REF_parse(
    const char* asc7,
    MOF_Object_Reference** obj_ref)
{
    ref_error_code = 0;

    if (ref_error_message != 0)
    {
        free(ref_error_message);
        ref_error_message = 0;
    }

    ref_input_first = asc7;
    ref_input_last = asc7 + strlen(asc7);
    REF_parse();

    if (ref_error_code)
        return ref_error_code;

    if (!ref_obj_ref)
        return -1;

    *obj_ref = ref_obj_ref;
    return 0;
}

void REF_error(
    const char* message)
{
    message = strdup(message);
    ref_error_code = -1;
}

