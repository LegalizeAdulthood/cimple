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

#include "MOF_Method_Decl.h"
#include "MOF_Error.h"
#include "MOF_Data_Type.h"
#include "MOF_Indent.h"

MOF_Method_Decl::MOF_Method_Decl() : data_type(0), parameters(0) 
{ 

}

void MOF_Method_Decl::print() const
{
    MOF_Indent(1);
    printf("+ method %s %s\n", 
        MOF_Data_Type::to_string(data_type), name);
    qualifiers->print_list(3);
}

void MOF_Method_Decl::validate()
{
    assert(owning_class != 0);
    parameters->check_duplicates();
}

MOF_Element* MOF_Method_Decl::clone() const
{
    /* ATTN: not implemented */
    MOF_ASSERT(false);
    return 0;
}

void MOF_Method_Decl::check_compatibility(
    const char* class_name,
    const MOF_Method_Decl* m1,
    const MOF_Method_Decl* m2)
{
    MOF_Parameter* p1 = m1->parameters;
    MOF_Parameter* p2 = m2->parameters;

    if (m1->data_type != m2->data_type)
    {
        MOF_error_printf("conflicting types for method \"%s\"", m1->name);
        return;
    }

    while (p1 && p2)
    {
        if (MOF_Parameter::compatible(class_name, m1->name, p1, p2) != 0)
        {
            MOF_error_printf(
                "conflicting types for method \"%s\"", m1->name);
            return;
        }

        p1 = (MOF_Parameter*)p1->next;
        p2 = (MOF_Parameter*)p2->next;
    }

    if (p1 || p2)
    {
        MOF_error_printf(
            "conflicting types for method \"%s\"", m1->name);
        return;
    }
}

void MOF_Method_Decl::set_owning_class(const char* owning_class)
{
    MOF_Qualified_Element::set_owning_class(owning_class);

    for (MOF_Parameter* p = parameters; p; p = (MOF_Parameter*)p->next)
        p->set_owning_class(owning_class);
}
