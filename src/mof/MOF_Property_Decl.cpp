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

#include "MOF_Property_Decl.h"
#include "MOF_String.h"
#include "MOF_Error.h"
#include "MOF_Qualifier_Decl.h"
#include "MOF_Indent.h"
#include "MOF_Data_Type.h"
#include "MOF_Yacc.h"

MOF_Property_Decl::MOF_Property_Decl() 
    : data_type(0), array_index(0), initializer(0) 
{ 
}

void MOF_Property_Decl::print() const
{
    MOF_Indent(1);
    printf("+ prop %s %s\n", MOF_Data_Type::to_string(data_type), name);
    qualifiers->print_list(3);
}

void MOF_Property_Decl::validate()
{
    /* Check the initializer */

    if (initializer)
        initializer->validate("property", name, data_type, array_index);

#if 0
    /*
     * Print out key properties:
     */

    if (qual_mask | MOF_QT_KEY)
    {
        printf("KEY PROPERTY: %s[%d] %s\n", 
            MOF_Data_Type::to_string(data_type),
            array_index,
            name);
    }
#endif
}

MOF_Element* MOF_Property_Decl::clone() const
{
    MOF_Property_Decl* tmp;
    
    if ((tmp = new MOF_Property_Decl()) == 0)
        return 0;

    tmp->type = type;
    tmp->name = strdup(name);
    tmp->qualifiers = qualifiers;
    tmp->all_qualifiers = all_qualifiers;
    tmp->qual_mask = qual_mask;
    tmp->data_type = data_type;
    tmp->array_index = array_index;
    tmp->initializer = initializer;

    return tmp;
}


