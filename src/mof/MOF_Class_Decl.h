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

/*
    Defines the declaration of a single class. Since this is a qualified
    element it inherits the qualifier
*/
#ifndef _MOF_Class_Decl_h
#define _MOF_Class_Decl_h

#include "MOF_Config.h"
#include "MOF_Feature.h"
#include "MOF_Feature_Info.h"
#include "MOF_Property_Decl.h"
#include "MOF_Method_Decl.h"
#include "MOF_Reference_Decl.h"
#include "MOF_Qualified_Element.h"
#include "MOF_Qualifier.h"
#include "MOF_Qualifier_Info.h"
#include "MOF_Qualifier_Decl.h"

/** Class declaration.
*/
class MOF_LINKAGE MOF_Class_Decl : public MOF_Qualified_Element
{
public:

    MOF_Class_Decl();

    ~MOF_Class_Decl();

    virtual MOF_Element* clone() const;

    void validate();

    void print() const;

    bool is_a(const MOF_Class_Decl* ancestor) const;

    size_t count_keys() const;

    const MOF_Class_Decl* find_ancestor(const char* class_name) const;

    virtual void set_owning_class(const char* owning_class);

    static MOF_Class_Decl* find(
        char* class_name,
        bool fix_case = false);

    static MOF_Class_Decl* find_by_alias(
        char* alias,
        bool fix_case = false);

    static void handle(MOF_Class_Decl* class_decl);

    static void print_static_list();

#if 0
    static void print_nested_refs();
#endif

    static MOF_Class_Decl* list;
    char* alias;
    char* super_class_name;
    class MOF_Class_Decl* super_class;
    MOF_Feature* features;
    MOF_Feature_Info* all_features;
};

#endif /*_MOF_Class_Decl_h */
