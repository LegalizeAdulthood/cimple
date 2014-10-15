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

#include "MOF_Qualifier.h"
#include "MOF_Error.h"
#include "MOF_Yacc.h"
#include "MOF_String.h"
#include "MOF_Qualifier_Decl.h"
#include "MOF_Qualifier_Info.h"
#include "MOF_Indent.h"

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier()
**
**------------------------------------------------------------------------------
*/

MOF_Qualifier::MOF_Qualifier() : name(0), params(0), flavor(0), owning_class(0)
{
}

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier::~MOF_Qualifier()
**
**------------------------------------------------------------------------------
*/

MOF_Qualifier::~MOF_Qualifier()
{
    free(name);
    free(owning_class);
    params->delete_list();
}

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier::clone()
**
**------------------------------------------------------------------------------
*/

MOF_Element* MOF_Qualifier::clone() const
{
    MOF_Qualifier* tmp = new MOF_Qualifier();
    tmp->name = strdup(name);
    tmp->params = (MOF_Literal*)params->clone();
    tmp->owning_class = 0;
    return tmp;
}

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier::print()
**
**------------------------------------------------------------------------------
*/

void MOF_Qualifier::print(size_t nesting) const
{
    MOF_Indent(nesting);
    printf("+ qual %s\n", name);
}

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier::print_list()
**
**------------------------------------------------------------------------------
*/

void MOF_Qualifier::print_list(size_t nesting) const
{
    const MOF_Qualifier* p;

    for (p = this ; p; p = (MOF_Qualifier*)p->next)
        p->print(nesting);
}

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier::validate()
**
**------------------------------------------------------------------------------
*/

static const char DESCRIPTION[] = "Description";

void MOF_Qualifier::validate()
{
    MOF_Qualifier_Decl* qual_decl;

    /*
     * Find qualifier declaration:
     */

    if ((qual_decl = MOF_Qualifier_Decl::find(name)) == 0)
        MOF_error_printf("undefined qualifier: \"%s\"\n", name);

    /*
     * The presence of a scalar boolean qualifier without arguments implies
     * true.
     */

    if (qual_decl->data_type == TOK_BOOLEAN &&
        qual_decl->array_index == 0 &&
        (params == 0 || params->value_type == TOK_NULL_VALUE))
    {
        params->delete_list();
        params = new MOF_Literal();
        params->value_type = TOK_BOOL_VALUE;
        params->bool_value = true;
    }

    /*
     * Check the qualifier params (if any):
     */

    if (params)
    {
        params->validate("qualifier", name, qual_decl->data_type,
            qual_decl->array_index);
    }

    /*
     * Free descriptions:
     */

#if 0
    /*
     * Release descriptions (to see how much memory they take).
     */

    if (MOF_stricmp(name, "description") == 0)
    {
        if (params && params->u.string_value)
        {
            free (params->u.string_value);
            params->u.string_value = 0;

            free (params);
            params = 0;
        }

        free (name);
        name = (char*)DESCRIPTION;
    }

#endif

}

/*
**------------------------------------------------------------------------------
**
** MOF_Qualifier::validate_list()
**
**------------------------------------------------------------------------------
*/

void MOF_Qualifier::validate_list(int expected_scope)
{
    MOF_Qualifier* p;
    MOF_Qualifier* q;

    /*
     * Check for duplicates:
     */

    for (p = this; p != 0; p = (MOF_Qualifier*)p->next)
    {
        for (q = this; q != p; q = (MOF_Qualifier*)q->next)
        {
            if (strcmp(p->name, q->name) == 0)
                MOF_error_printf("duplicate qualifier: \"%s\"", p->name);
        }
    }

    /*
     * Validate scopes:
     */

    for (p = this; p != 0; p = (MOF_Qualifier*)p->next)
    {
        MOF_Qualifier_Decl* qual_decl;

        /*
         * Find qualifier declaration:
         */

        if ((qual_decl = MOF_Qualifier_Decl::find(p->name)) == 0)
            MOF_error_printf("undefined qualifier \"%s\"", p->name);

        /*
         * Check the scope:
         */

        if (!(qual_decl->scope & expected_scope))
            MOF_error_printf("invalid scope for qualifier \"%s\"", p->name);
    }
}

