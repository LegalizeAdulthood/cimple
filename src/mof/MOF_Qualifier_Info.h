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

#ifndef _MOF_Qualifier_info_h
#define _MOF_Qualifier_info_h

#include "MOF_Config.h"
#include "MOF_Literal.h"
#include "MOF_Qualifier.h"

class MOF_Qualifier;

class MOF_LINKAGE MOF_Qualifier_Info : public MOF_Element
{
public:

    MOF_Qualifier_Info();

    ~MOF_Qualifier_Info();

    virtual MOF_Element* clone() const;

    void print(size_t nesting) const;

    void print_list(size_t nesting) const;

    static MOF_Qualifier_Info* make_all_qualifiers(
        const char* class_name,
        const char* inst_name,
        const char* feature_name,
        const char* param_name,
        MOF_Qualifier* local_qualifiers,
        MOF_Qualifier_Info* inherited_qual_info_list,
        MOF_mask* qual_mask,
        bool prop);

    const MOF_Qualifier* qualifier;
    MOF_mask flavor;
    bool propagated;
};

#endif /* _MOF_Qualifier_info_h */
