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

#ifndef _MOF_Literal_h
#define _MOF_Literal_h

#include "MOF_Config.h"
#include "MOF_Element.h"

class MOF_LINKAGE MOF_Literal : public MOF_Element
{
public:

    MOF_Literal() : value_type(0) { int_value = 0; }

    virtual ~MOF_Literal();

    virtual void print(FILE* stream, bool is_array) const;

    virtual MOF_Element* clone() const;

    void validate(
        const char* object_type,
        const char* object_name,
        int data_type,
        int array_index);

public:

    static bool identical(
        MOF_Literal* lit1,
        MOF_Literal* lit2);

public:

    /*
     * Value_type will be one of TOK_INT_VALUE TOK_REAL_VALUE TOK_CHAR_VALUE
     * TOK_BOOL_VALUE TOK_NULL_VALUE TOK_STRING_VALUE
     */
    int value_type;

    union
    {
        MOF_sint64 int_value;
        MOF_real64 real_value;
        MOF_char16 char_value;
        bool bool_value;
        MOF_String string_value;
    };
};

#endif /* _MOF_Literal_h */
