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

#ifndef _MOF_Key_Value_Pair_h
#define _MOF_Key_Value_Pair_h

#include "MOF_Config.h"
#include "MOF_Element.h"
#include "MOF_Literal.h"

class MOF_LINKAGE MOF_Key_Value_Pair : public MOF_Element
{
public:

    MOF_Key_Value_Pair() : key(0), value(0), is_array(false) { }

    ~MOF_Key_Value_Pair();

    void validate(class MOF_Class_Decl* class_decl);

    virtual MOF_Element* clone() const;

    char* key;
    MOF_Literal* value;
    bool is_array;
};

#endif /*_MOF_Key_Value_Pair_h */
