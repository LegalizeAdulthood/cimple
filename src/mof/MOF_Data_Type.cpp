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

#include "MOF_Data_Type.h"
#include "MOF_Error.h"
#include "MOF_String.h"
#include "MOF_Yacc.h"

const char* MOF_Data_Type::to_string(int data_type)
{
    switch (data_type)
    {
        case TOK_UINT8: 
            return "uint8";

        case TOK_SINT8: 
            return "sint8";

        case TOK_UINT16: 
            return "uint16";

        case TOK_SINT16: 
            return "sint16";

        case TOK_UINT32: 
            return "uint32";

        case TOK_SINT32: 
            return "sint32";

        case TOK_UINT64: 
            return "uint64";

        case TOK_SINT64: 
            return "sint64";

        case TOK_REAL32: 
            return "real32";

        case TOK_REAL64: 
            return "real64";

        case TOK_CHAR16: 
            return "char16";

        case TOK_STRING: 
            return "string";

        case TOK_BOOLEAN: 
            return "boolean";

        case TOK_DATETIME: 
            return "datetime";

        default:
            MOF_ASSERT(false);
            return 0;
    }

    /* Unreachable */
    return 0;
}
