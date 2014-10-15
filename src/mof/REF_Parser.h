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

#ifndef _REF_Parser_h
#define _REF_Parser_h

#include "MOF_Config.h"
#include "MOF_Object_Reference.h"

extern size_t ref_line_num;
extern const char* ref_input_first;
extern const char* ref_input_last;
extern char* ref_error_message;
extern int ref_error_code;
extern  MOF_Object_Reference* ref_obj_ref;

/*
 * This is the entry point to the ref parser. Upon completion,
 * obj_ref will point to an object of type MOF_Object_Reference. The
 * user is responsible for freeing it.
 */
MOF_LINKAGE extern int REF_parse(
    const char* asc7,
    MOF_Object_Reference** obj_ref); 

MOF_LINKAGE void REF_error(
    const char* message);

#endif /* _REF_Parser_h */
