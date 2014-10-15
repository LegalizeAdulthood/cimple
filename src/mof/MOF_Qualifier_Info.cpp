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

#include "MOF_Qualifier_Info.h"
#include "MOF_Yacc.h"
#include "MOF_Class_Decl.h"
#include "MOF_Error.h"
#include "MOF_Indent.h"
#include "MOF_String.h"

MOF_Qualifier_Info::MOF_Qualifier_Info() 
    : qualifier(0), flavor(0), propagated(false)
{

}

MOF_Qualifier_Info::~MOF_Qualifier_Info()
{
    /* Nothing to do */
}

MOF_Element* MOF_Qualifier_Info::clone() const
{
    MOF_ASSERT("not implemented" == 0);
    return 0;
}

struct MOF_Pair
{
    const char* name;
    MOF_uint32 mask;
};

static MOF_Pair _pairs[] =
{
    { "Abstract", MOF_QT_ABSTRACT },
    { "Aggregate", MOF_QT_AGGREGATE },
    { "Aggregation", MOF_QT_AGGREGATION },
    { "Association", MOF_QT_ASSOCIATION },
    { "Counter", MOF_QT_COUNTER },
    { "Delete", MOF_QT_DELETE },
    { "DN", MOF_QT_DN },
    { "EmbeddedObject", MOF_QT_EMBEDDEDOBJECT },
    { "Expensive", MOF_QT_EXPENSIVE },
    { "Experimental", MOF_QT_EXPERIMENTAL },
    { "Gauge", MOF_QT_GAUGE },
    { "Ifdeleted", MOF_QT_IFDELETED },
    { "In", MOF_QT_IN },
    { "Indication", MOF_QT_INDICATION },
    { "Invisible", MOF_QT_INVISIBLE },
    { "Key", MOF_QT_KEY },
    { "Large", MOF_QT_LARGE },
    { "Octetstring", MOF_QT_OCTETSTRING },
    { "Out", MOF_QT_OUT },
    { "Read", MOF_QT_READ },
    { "Required", MOF_QT_REQUIRED },
    { "Static", MOF_QT_STATIC },
    { "Terminal", MOF_QT_TERMINAL },
    { "Weak", MOF_QT_WEAK },
    { "Write", MOF_QT_WRITE }
};

static const size_t NUM_PAIRS = (sizeof(_pairs) / sizeof(_pairs[0]));

static MOF_mask _make_qual_mask(
    MOF_Qualifier_Info* qual_info_list,
    bool prop,
    bool param)
{
    MOF_Qualifier_Info* p;
    MOF_mask mask = 0;
    size_t i;

    /*
     * Set bits for qualifiers whose default is true.
     */
    
    if (prop)
        mask |= MOF_QT_READ;

    if (param)
        mask |= MOF_QT_IN;

    /*
     * Iterate over qualifier list and either set or clear the corresponding
     * qualifier bit.
     */

    for (p = qual_info_list; p != 0; p = (MOF_Qualifier_Info*)p->next)
    {
        for (i = 0; i < NUM_PAIRS; i++)
        {
            if (MOF_stricmp(_pairs[i].name, p->qualifier->name) == 0)
            {
                MOF_Literal* lit = p->qualifier->params;
                bool flag = true;

                /* 
                 * Ignore errors (these are checked elsewhere). 
                 */

                if (lit && (lit->next || lit->value_type != TOK_BOOL_VALUE))
                    continue;

                if (lit && !lit->bool_value)
                    flag = false;

                if (flag)
                    mask |= _pairs[i].mask;
                else
                    mask &= ~_pairs[i].mask;
            }
        }
    }

    return mask;
}

MOF_Qualifier_Info* _find(
    MOF_Qualifier_Info* qual_info_list,
    const char* name)
{
    MOF_Qualifier_Info* p;

    for (p = qual_info_list; p; p = (MOF_Qualifier_Info*)p->next)
    {
        if (strcmp(p->qualifier->name, name) == 0)
            return p;
    }

    return 0;
}

static MOF_Qualifier_Info* _clone_propagated(
    MOF_Qualifier_Info* info)
{
    MOF_Qualifier_Info* tmp;

    if ((tmp = new MOF_Qualifier_Info()) == 0)
        return 0;

    tmp->qualifier = info->qualifier;
    tmp->flavor = info->flavor;
    tmp->propagated = true;

    return tmp;
}

MOF_Qualifier_Info* MOF_Qualifier_Info::make_all_qualifiers(
    const char* class_name,
    const char* inst_name,
    const char* feature_name,
    const char* param_name,
    MOF_Qualifier* local_qualifiers,
    MOF_Qualifier_Info* inherited_qual_info_list,
    MOF_mask* qual_mask,
    bool prop)
{
    MOF_Qualifier_Info* all_qualifiers_list = 0;
    MOF_Qualifier_Info* qi;
    MOF_Qualifier* q;

    /*
     * Check for illegal qualifier overrides and append local qualifiers to
     * output list.
     */

    for (q = local_qualifiers; q; q = (MOF_Qualifier*)q->next)
    {
        MOF_Qualifier_Info* new_qi;
        MOF_Qualifier_Decl* qual_decl;

        /*
         * Find qualifier declaration for this qualifier:
         */

        if ((qual_decl = MOF_Qualifier_Decl::find(q->name)) == 0)
        {
            /* This cannot happen since it is checked earlier */
            MOF_error_printf("undeclared qualifier: %s", q->name);
        }

        /*
         * Was this qualifier overriden? If so, be sure there was no
         * attempt to change the value:
         */

        qi = _find(inherited_qual_info_list, q->name);

        if (qi && 
            (qi->flavor & MOF_FLAVOR_DISABLEOVERRIDE) &&
            !MOF_Literal::identical(q->params, qi->qualifier->params))
        {
            char context[1024];
            *context = '\0';

            if (class_name)
            {
                strcat(context, class_name);

                if (feature_name)
                {
                    strcat(context, ".");
                    strcat(context, feature_name);

                    if (param_name)
                    {
                        strcat(context, "().");
                        strcat(context, param_name);
                    }
                }
            }

            MOF_error_printf("attempt to override non-overridable qualifier "
                "(%s) on %s", 
                q->name, context);
        }

        /*
         * Create qualifier info object and append to list:
         */

        if ((new_qi = new MOF_Qualifier_Info()) == 0)
            MOF_error_printf("out of memory");

        new_qi->qualifier = q;

        /* 
         * If overriding, else use declaration:
         */

        if (qi)
            new_qi->flavor = MOF_Flavor::merge(q->flavor, qi->flavor);
        else
            new_qi->flavor = MOF_Flavor::merge(q->flavor, qual_decl->flavor);

        if (all_qualifiers_list == 0)
            all_qualifiers_list = new_qi;
        else
            all_qualifiers_list->append(new_qi);
    }

    /*
     * Propagate inherited qualifiers.
     */

    for (qi = inherited_qual_info_list; qi; qi = (MOF_Qualifier_Info*)qi->next)
    {
        /*
         * Propagate qualifier if necessary (if TOSUBCLASS flavor is present
         * and qualifier not already present locally).
         */

        if ((qi->flavor & MOF_FLAVOR_TOSUBCLASS) && 
            !_find(all_qualifiers_list, qi->qualifier->name))
        {
            MOF_Qualifier_Info* new_qi;
            
            if ((new_qi = _clone_propagated(qi)) == 0)
                MOF_error_printf("out of memory");

            if (all_qualifiers_list == 0)
                all_qualifiers_list = new_qi;
            else
                all_qualifiers_list->append(new_qi);
        }
    }

    /*
     * Now build the resulting mask of all boolean qualifiers.
     */

    *qual_mask = _make_qual_mask(all_qualifiers_list, prop, param_name != 0);

    return all_qualifiers_list;
}

void MOF_Qualifier_Info::print(size_t nesting) const
{
    MOF_Indent(nesting);
    printf("+ qual_info %s ", qualifier->name);
    MOF_Flavor::print(flavor);
}

void MOF_Qualifier_Info::print_list(size_t nesting) const
{
    const MOF_Qualifier_Info* p;

    for (p = this; p; p = (MOF_Qualifier_Info*)p->next)
        p->print(nesting);
}

