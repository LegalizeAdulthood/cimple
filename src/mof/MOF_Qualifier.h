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

#ifndef _MOF_Qualifier_h
#define _MOF_Qualifier_h

#include "MOF_Config.h"
#include "MOF_Element.h"
#include "MOF_Literal.h"

class MOF_Qualifier;

class MOF_LINKAGE MOF_Qualifier : public MOF_Element
{
public:

    MOF_Qualifier();

    ~MOF_Qualifier();

    virtual MOF_Element* clone() const;

    void print(size_t nesting) const;

    void print_list(size_t nesting) const;

    void validate();

    void validate_list(int expected_scope);

    void set_owning_class(const char* owning_class_)
    {
        owning_class = strdup(owning_class_);
    }

    char* name;
    class MOF_Literal* params;
    MOF_mask flavor;
    char* owning_class;
};

#endif /* _MOF_Qualifier_h */
