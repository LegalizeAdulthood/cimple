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

#include "MOF_Qualifier_Decl.h"
#include "MOF_Error.h"
#include "MOF_String.h"

MOF_Qualifier_Decl* MOF_Qualifier_Decl::list = 0;

MOF_Qualifier_Decl::MOF_Qualifier_Decl()
    : data_type(0), array_index(0), initializer(0), scope(0), flavor(0)
{

}

MOF_Qualifier_Decl::~MOF_Qualifier_Decl()
{
    initializer->delete_list();
}

MOF_Element* MOF_Qualifier_Decl::clone() const
{
    MOF_Qualifier_Decl* tmp = new MOF_Qualifier_Decl();
    tmp->name = strdup(name);
    tmp->data_type = data_type;
    tmp->array_index = array_index;
    tmp->initializer = (MOF_Literal*)initializer->clone();
    tmp->scope = scope;
    tmp->flavor = flavor;

    return tmp;
}

MOF_Qualifier_Decl* MOF_Qualifier_Decl::find(char* name)
{
    MOF_Qualifier_Decl* p;

    for (p = MOF_Qualifier_Decl::list; p; p = (MOF_Qualifier_Decl*)p->next)
    {
        if (MOF_stricmp(p->name, name) == 0)
        {
            if (strcmp(name, p->name) != 0)
            {
#if 0
                MOF_warning_printf("changing case of \"%s\" to \"%s\"",
                    name, p->name);
#endif
                strcpy(name, p->name);
            }
            return p;
        }
    }

    return 0;
}

void MOF_Qualifier_Decl::validate()
{
    /*
     * Be sure the qualifier is not already defined:
     */

    if (MOF_Qualifier_Decl::find(name))
        MOF_error_printf("qualifier already defined: \"%s\"", name);

    /*
     * Validate the initializer.
     */

    if (initializer)
    {
        initializer->validate(
            "qualifier", name, data_type, array_index);
    }
}

void MOF_Qualifier_Decl::handle(MOF_Qualifier_Decl* qual_decl)
{
    qual_decl->validate();

    if (MOF_Qualifier_Decl::list == 0)
        MOF_Qualifier_Decl::list = qual_decl;
    else
        MOF_Qualifier_Decl::list->append(qual_decl);
}

void MOF_Qualifier_Decl::print() const
{
    printf("+ qualifier %s\n", name);
}

void MOF_Qualifier_Decl::print_static_list()
{
    MOF_Qualifier_Decl* p = MOF_Qualifier_Decl::list; 

    for (; p; p = (MOF_Qualifier_Decl*)p->next)
        p->print();
}

