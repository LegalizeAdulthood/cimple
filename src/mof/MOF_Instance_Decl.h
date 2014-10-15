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

#ifndef MOF_Instance_Decl_h
#define MOF_Instance_Decl_h

#include "MOF_Config.h"
#include "MOF_Property.h"
#include "MOF_Qualified_Element.h"
#include "MOF_Qualifier.h"
#include "MOF_Qualifier_Info.h"
#include "MOF_Feature_Info.h"
#include "MOF_Class_Decl.h"

class MOF_LINKAGE MOF_Instance_Decl : public MOF_Qualified_Element
{
public:

    MOF_Instance_Decl();

    ~MOF_Instance_Decl();

    virtual MOF_Element* clone() const;

    static void handle(MOF_Instance_Decl* inst_decl);

    static MOF_Instance_Decl* find_by_alias(
        char* alias, 
        bool fix_case = false);

    static MOF_Instance_Decl* find(const char* inst_name);

    static MOF_Object_Reference* alias_to_obj_ref(const char* alias);

    void print() const;

    static void print_static_list();

    static MOF_Instance_Decl* list;
    char* inst_name;
    char* class_name;
    MOF_Class_Decl* class_decl;
    char* alias;
    class MOF_Property* properties;
    MOF_Feature_Info* all_features;
};

#endif /* MOF_Instance_Decl_h */
