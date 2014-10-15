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

#include "MOF_Reference_Decl.h"
#include "MOF_Error.h"
#include "MOF_Indent.h"
#include "MOF_Class_Decl.h"
#include "MOF_Object_Reference.h"

MOF_Reference_Decl::MOF_Reference_Decl() 
    : class_name(0), class_decl(0), alias(0), obj_ref(0) 
{ 
}

void MOF_Reference_Decl::print() const
{
    MOF_Indent(1);
    printf("+ ref %s %s alias(%s) obj_ref(%p)\n", 
        class_name, name, alias, obj_ref);
    qualifiers->print_list(3);
}

/*TODO: what's this doing here? */
void MOF_Reference_Decl::validate_obj_ref(MOF_Object_Reference* obj_ref)
{
    MOF_Class_Decl* ref_init_class_decl;

    if (!obj_ref)
        return;
    
    if ((ref_init_class_decl = 
        MOF_Class_Decl::find(obj_ref->class_name)) == 0)
    {
        MOF_error_printf("undefined class (%s) in ref initializer (%s)",
            obj_ref->class_name, class_name);
        return;
    }

    if (!ref_init_class_decl->is_a(class_decl))
    {
        MOF_error_printf(
            "reference initializer refers to a class (%s) "
            "which is not a sub-type of the reference (%s)",
            ref_init_class_decl->name, class_decl->name);
        return;
    }
}

void MOF_Reference_Decl::validate()
{
    MOF_Class_Decl* ref_class_decl;

    /*
     * Be sure the class exists:
     */

    if ((ref_class_decl = MOF_Class_Decl::find(class_name)) == 0)
    {
        MOF_error_printf(
            "class referred to by ref \"%s\" is undefined: \"%s\"",
            name, class_name);
    }

    /*
     * Cache this so we don't have to look it up later when we validate
     * the ref initializer.
     */

    class_decl = ref_class_decl;

    /*
     * If an object reference was provided, test is-a relationship:
     */

    validate_obj_ref(obj_ref);
}

MOF_Element* MOF_Reference_Decl::clone() const
{
    MOF_Reference_Decl* tmp;
    
    if ((tmp = new MOF_Reference_Decl()) == 0)
        return 0;

    tmp->type = type;
    tmp->name = name;
    tmp->qualifiers = qualifiers;
    tmp->all_qualifiers = all_qualifiers;
    tmp->qual_mask = qual_mask;
    tmp->alias = alias;
    tmp->class_decl = class_decl;
    tmp->obj_ref = obj_ref;

    return tmp;
}

