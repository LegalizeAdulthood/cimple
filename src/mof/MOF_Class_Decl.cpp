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

#include "MOF_Class_Decl.h"
#include "MOF_Error.h"
#include "MOF_String.h"
#include "MOF_Qualifier_Info.h"
#include "MOF_Instance_Decl.h"
#include "MOF_Yacc.h"

MOF_Class_Decl* MOF_Class_Decl::list = 0;

MOF_Class_Decl::MOF_Class_Decl() : alias(0), super_class_name(0), 
    super_class(0), features(0), all_features(0)
{

}

MOF_Class_Decl::~MOF_Class_Decl()
{
    free(alias);
    free(super_class_name);
    features->delete_list();
    all_features->delete_list();
}

MOF_Element* MOF_Class_Decl::clone() const
{
    MOF_ASSERT("not implemented" == 0);
    return 0;
}

static void _print_all_features(const MOF_Class_Decl* class_decl)
{
    if (class_decl->all_features)
        class_decl->all_features->print_list();
}

void MOF_Class_Decl::print() const
{
#if 0
    MOF_Feature* p;
#endif

    /* 
     * Print the class header:
     */

    printf("+ class %s : %s as %s\n", name, super_class_name, alias);

    /* 
     * Print local qualifiers:
     */

    qualifiers->print_list(1);

    /*
     * Print all qualifiers list:
     */

    all_qualifiers->print_list(1);

#if 0
    /* 
     * Print class features:
     */

    for (p = features; p; p = p->next)
        MOF_Feature_print(p);
#endif

    /*
     * Print all features list:
     */

    _print_all_features(this);
}

static void _check_duplicate_features(
    MOF_Class_Decl* class_decl)
{
    MOF_Feature* p;
    MOF_Feature* q;
    
    for (p = (MOF_Feature*)class_decl->features; p; p = (MOF_Feature*)p->next)
    {
        for (q = class_decl->features; q != p; q = (MOF_Feature*)q->next)
        {
            if (MOF_stricmp(p->name, q->name) == 0)
                MOF_error_printf("duplicate class feature: \"%s\"", p->name);
        }
    }
}

static void _validate_feature_compatibility(
    const char* class_name,
    MOF_Feature* p,
    MOF_Feature* q)
{
    const char MESSAGE[] =
        "feature incompatible with inherited feature with same name: \"%s\"\n";

    if (p->type != q->type)
        MOF_error_printf(MESSAGE, p->name);

    if (p->type == MOF_FEATURE_METHOD)
    {
        MOF_Method_Decl* pp = (MOF_Method_Decl*)p;
        MOF_Method_Decl* qq = (MOF_Method_Decl*)q;

        MOF_Method_Decl::check_compatibility(class_name, pp, qq);
    }
    else if (p->type == MOF_FEATURE_REF)
    {
        MOF_Reference_Decl* pp = (MOF_Reference_Decl*)p;
        MOF_Reference_Decl* qq = (MOF_Reference_Decl*)q;

        // Validate that if the reference changes the class, that the new
        // class decends from the old class.

        if (MOF_stricmp(pp->class_name, qq->class_name) != 0)
        {
            const char* descendent = pp->class_name;
            const char* ancestor = pp->class_name;

            // Be sure that descendent descends from ancestor.

            const MOF_Class_Decl* tmp_class_decl =
                MOF_Class_Decl::find((char*)pp->class_name);

            if (!tmp_class_decl)
            {
                MOF_error_printf(
                    "class used in reference %s does not exist: %s\n",
                    pp->name, pp->class_name);
            }

            if (!tmp_class_decl->find_ancestor(qq->class_name))
            {
                MOF_error_printf(
                    "illegal override of reference \"%s\": overriden reference "
                    "class (%s) must descend from inherited reference "
                    "class (%s)", pp->name, pp->class_name, qq->class_name);
            }
        }
    }
    else if (p->type == MOF_FEATURE_PROP)
    {
        MOF_Property_Decl* pp = (MOF_Property_Decl*)p;
        MOF_Property_Decl* qq = (MOF_Property_Decl*)q;

        if (pp->data_type != qq->data_type)
            MOF_error_printf(MESSAGE, p->name);

        if (pp->array_index != qq->array_index)
            MOF_error_printf(MESSAGE, p->name);
    }
    else 
        MOF_ASSERT(0);
}

static void _build_param_qual_info_list(
    const char* class_name,
    MOF_Feature* feature1,
    MOF_Feature* feature2)
{
    MOF_Parameter* param1;
    MOF_Parameter* param2;

    if (feature1->type != MOF_FEATURE_METHOD)
        return;

    param1 = ((MOF_Method_Decl*)feature1)->parameters;
    param2 = feature2 ? ((MOF_Method_Decl*)feature2)->parameters : 0;

    while (param1)
    {
        MOF_Qualifier_Info* all_qualifiers;

        if (param2)
            all_qualifiers = param2->all_qualifiers;
        else
            all_qualifiers = 0;

        param1->all_qualifiers = MOF_Qualifier_Info::make_all_qualifiers(
            class_name,
            0, /* instance name */
            feature1->name, /* feature name */
            param1->name, /* parameter name */
            param1->qualifiers, /* local qualifiers */
            all_qualifiers, /* inherited qualifiers */
            &param1->qual_mask,
            false); /* prop */

#if 0
        printf("class_name[%s]\n", class_name);
        MOF_Qualifier_info_print_list(param1->all_qualifiers, 0);
#endif

        param1 = (MOF_Parameter*)param1->next;

        if (param2)
            param2 = (MOF_Parameter*)param2->next;
    }
}

static void _build_all_features(MOF_Class_Decl* class_decl)
{
    /*
     * Propagate class features from super class (if any):
     */

    if (class_decl->super_class)
    {
        MOF_Feature_Info* p = class_decl->super_class->all_features;

        for (; p; p = (MOF_Feature_Info*)p->next)
        {
            MOF_Feature_Info* info;
            
            if ((info = new MOF_Feature_Info()) == 0)
            {
                MOF_error("out of memory");
                return;
            }

            info->class_origin = p->class_origin;
            info->propagated = true;
            info->feature = p->feature;

            if (class_decl->all_features == 0)
                class_decl->all_features = info;
            else
                class_decl->all_features->append(info);
        }
    }

    /*
     * Now merge in locally defined features (either override or append).
     */

    {
        MOF_Feature* p;
        MOF_Feature_Info* q;

        for (p = class_decl->features; p; p = (MOF_Feature*)p->next)
        {
            bool override = false;

            /*
             * If all features already contains this feature, override it.
             */

            for (q = class_decl->all_features; q; q =(MOF_Feature_Info*)q->next)
            {
                if (MOF_stricmp(p->name, q->feature->name) == 0)
                {
                    /*
                     * Fix case to match original case.
                     */

                    MOF_fix_case(p->name, q->feature->name);

                    /*
                     * Validate two features are compatible.
                     */

                    _validate_feature_compatibility(class_decl->name,
                        p, q->feature);

                    /*
                     * Build the all-qualifiers list.
                     */

                    p->all_qualifiers = MOF_Qualifier_Info::make_all_qualifiers(
                        class_decl->name,
                        0, /* instance name */
                        p->name, /* feature name */
                        0, /* parameter name */
                        p->qualifiers, /* local qualifiers */
                        q->feature->all_qualifiers, /* inherited qualifiers */
                        &p->qual_mask,
                        p->type == MOF_FEATURE_PROP);

#if 0
                printf("=== class_name[%s]\n", class_decl->name);
                MOF_Qualifier_info_print_list(p->all_qualifiers, 0);
#endif

                    /*
                     * Build the all-qualifiers list for each parameter (for
                     * methods only).
                     */

                    _build_param_qual_info_list(
                        class_decl->name, p, q->feature);
                    
                    /*
                     * Override the feature.
                     */

                    q->propagated = false;
                    q->feature = p;
                    override = true;
                    break;
                }
            }

            /*
             * If not an overriding feature, then append new feature.
             */

            if (!override)
            {
                MOF_Feature_Info* info;

                /*
                 * Build the qualifier list.
                 */

                p->all_qualifiers = MOF_Qualifier_Info::make_all_qualifiers(
                    class_decl->name,
                    0, /* instance name */
                    p->name, /* feature name */
                    0, /* parameter name */
                    p->qualifiers, /* local qualifiers */
                    0, /* inherited qualifiers */
                    &p->qual_mask,
                    p->type == MOF_FEATURE_PROP);

#if 0
                printf("=== class_name[%s]\n", class_decl->name);
                MOF_Qualifier_info_print_list(p->all_qualifiers, 0);
#endif

                /*
                 * Build the all-qualifiers list for each parameter (for
                 * methods only).
                 */

                _build_param_qual_info_list(class_decl->name, p, 0);

                /*
                 * Create a new class feature info entry and insert it.
                 */
                
                if ((info = new MOF_Feature_Info()) == 0)
                {
                    MOF_error("out of memory");
                    return;
                }

                info->class_origin = class_decl;
                info->propagated = false;
                info->feature = p;

                if (class_decl->all_features == 0)
                    class_decl->all_features = info;
                else
                    class_decl->all_features->append(info);
            }

        }
    }
}

MOF_Class_Decl* MOF_Class_Decl::find(
    char* class_name,
    bool fix_case)
{
    MOF_Class_Decl* p;

    for (p = MOF_Class_Decl::list; p; p = (MOF_Class_Decl*)p->next)
    {
        if (MOF_stricmp(p->name, class_name) == 0)
        {
            if (fix_case && strcmp(p->name, class_name) != 0)
            {
#if 0
                MOF_warning_printf("changing case of \"%s\" to \"%s\"",
                    class_name, p->name);
#endif
                strcpy(class_name, p->name);
            }
            return p;
        }
    }

    return 0;
}

MOF_Class_Decl* MOF_Class_Decl::find_by_alias(
    char* alias,
    bool fix_case)
{
    MOF_Class_Decl* p;

    if (!alias)
        return 0;

    for (p = MOF_Class_Decl::list; p; p = (MOF_Class_Decl*)p->next)
    {
        if (p->alias && MOF_stricmp(p->alias, alias) == 0)
        {
            if (fix_case && strcmp(p->alias, alias) != 0)
            {
#if 0
                MOF_warning_printf("changing case of \"%s\" to \"%s\"",
                    alias, p->alias);
#endif
                strcpy(alias, p->alias);
            }
            return p;
        }
    }

    return 0;
}

static void _check_EmbeddedInstance_value(const MOF_Qualifier* mq)
{
    MOF_Literal* ml = mq->params;

    if (!ml || !ml->string_value)
    {
        MOF_error_printf("EmbeddedInstance qualifier has null value");
    }

    if (ml->value_type != TOK_STRING_VALUE)
    {
        MOF_error_printf("EmbeddedInstance applied to non-string");
    }

    if (!MOF_Class_Decl::find(ml->string_value))
    {
        MOF_warning_printf("EmbeddedInstance qualifier refers "
            "to an unknown class: \"%s\"", ml->string_value);
    }
}

void MOF_Class_Decl::validate()
{
    MOF_mask expected_scope = 0;
    MOF_Qualifier_Info* super_class_qualifiers = 0;

    /*
     * Is class already defined?
     */

    if (MOF_Class_Decl::find(name))
    {
        MOF_error_printf(
            "class already defined: \"%s\"", name);
    }

    /*
     * Is alias already used?
     */

    if (alias)
    {
        if (MOF_Class_Decl::find_by_alias(alias) ||
            MOF_Instance_Decl::find_by_alias(alias))
        {
            MOF_error_printf(
                "alias name already defined: \"%s\"", alias);
        }
    }

    /*
     * Does the super class exist? If so, set pointer to it and build the
     * all_qualifiers list.
     */

    if (super_class_name)
    {
        MOF_Class_Decl* super_class_decl;

        super_class_decl = MOF_Class_Decl::find(super_class_name, true);

        if (super_class_decl == 0)
        {
            MOF_error_printf("no such super class: \"%s\"", 
                super_class_name);
        }

        super_class = super_class_decl;
        super_class_qualifiers = super_class_decl->all_qualifiers;
    }

    /*
     * Disallow inheritance operation if super-class is terminal.
     */

    if (super_class)
    {
        if (super_class->qual_mask & MOF_QT_TERMINAL)
        {
            MOF_error("attempt to inherit from a terminal class");
            return;
        }
    }

    /*
     * Set self as owning class.
     */
    set_owning_class(this->name);

    /*
     * Build the all-qualifiers list:
     */

    all_qualifiers = MOF_Qualifier_Info::make_all_qualifiers(
        name, 
        0, 
        0, 
        0,
        qualifiers, 
        super_class_qualifiers,
        &qual_mask,
        false); /* prop */

#if 0
        MOF_Qualifier_info_print_list(all_qualifiers, 0);
#endif

    /*
     * Check for duplicate features:
     */

    _check_duplicate_features(this);

    /*
     * Validate class features:
     */

    {
        MOF_Feature* p;

        for (p = features; p; p = (MOF_Feature*)p->next)
            p->validate();
    }

    /*
     * Build a combined feature list (combine inherited and local features
     * into a single list for easier processing).
     */
    
    _build_all_features(this);

    if (qual_mask & MOF_QT_ASSOCIATION)
        expected_scope |= MOF_SCOPE_ASSOCIATION;
    else if (qual_mask & MOF_QT_INDICATION)
        expected_scope |= MOF_SCOPE_INDICATION;
    else
        expected_scope |= MOF_SCOPE_CLASS;

    /*
     * Check for EmbeddedObject qualifier.
     */

    for (MOF_Feature* p = features; p; p = (MOF_Feature*)p->next)
    {
        if (p->qual_mask & MOF_QT_EMBEDDEDOBJECT)
        {
#if 0
            if (!(qual_mask & MOF_QT_INDICATION))
            {
                MOF_error_printf("EmbeddedObject qualifier allowed only on "
                    "the properties of indications");
            }
#endif
            if (p->type == MOF_FEATURE_METHOD)
            {
                MOF_Method_Decl* meth = (MOF_Method_Decl*)p;

                if (meth->data_type != TOK_STRING)
                {
                    MOF_error_printf("EmbeddedObject qualifier allowed "
                        "only for string return values: %s.%s", name, p->name);
                }
            }
            else if (p->type == MOF_FEATURE_PROP)
            {
                MOF_Property_Decl* prop = (MOF_Property_Decl*)p;

                if (prop->data_type != TOK_STRING)
                {
                    MOF_error_printf("EmbeddedObject qualifier allowed "
                        "only on string properties: %s.%s", name, p->name);
                }
            }
            else
            {
                MOF_error_printf(
                    "EmbeddedObject qualifier only allowed on properties, "
                    "methods, and parameters: %s.%s", name, p->name);
            }
        }
    }

    /*
     * Check EmbeddedInstance qualifier (on properties and methods).
     */

    for (MOF_Feature* p = features; p; p = (MOF_Feature*)p->next)
    {
        for (MOF_Qualifier_Info* q = p->all_qualifiers; 
            q; 
            q = (MOF_Qualifier_Info*)q->next)
        {
            if (strcasecmp(q->qualifier->name, "EmbeddedInstance") != 0)
                continue;

            _check_EmbeddedInstance_value(q->qualifier);

            if (p->type == MOF_FEATURE_PROP)
            {
                MOF_Property_Decl* prop = (MOF_Property_Decl*)p;

                if (prop->data_type != TOK_STRING)
                {
                    MOF_warning_printf("EmbeddedInstance qualifier allowed "
                        "only on string properties: %s.%s", name, prop->name);
                }
            }
            else if (p->type == MOF_FEATURE_METHOD)
            {
                MOF_Method_Decl* meth = (MOF_Method_Decl*)p;

                if (meth->data_type != TOK_STRING)
                {
                    MOF_warning_printf("EmbeddedInstance qualifier allowed "
                        "only on string properties: %s.%s", name, meth->name);
                }
            }
        }
    }

    /*
     * Check EmbeddedInstance qualifier (on parameters)
     */

    for (MOF_Feature* p = features; p; p = (MOF_Feature*)p->next)
    {
        if (p->type != MOF_FEATURE_METHOD)
            continue;

        MOF_Method_Decl* meth = (MOF_Method_Decl*)p;

        for (MOF_Parameter* q = meth->parameters; q; q =(MOF_Parameter*)q->next)
        {
            // Lookup EmbeddedInstance qualifier.

            for (MOF_Qualifier_Info* r = q->all_qualifiers; r;
                r = (MOF_Qualifier_Info*)r->next)
            {
                if (strcasecmp(r->qualifier->name, "EmbeddedInstance") != 0)
                    continue;

                _check_EmbeddedInstance_value(r->qualifier);

                // Check EmbeddedInstance qualifier on this parameter.

                if (q->data_type != TOK_STRING)
                {
                    MOF_error_printf(
                        "EmbeddedInstance qualifier allowed only "
                        "on string parameters: %s.%s().%s", name, meth->name,
                        q->name);
                }
            }
        }
    }

    /*
     * Only associations can have references (CIM-2.1)
     */

    if (expected_scope != MOF_SCOPE_ASSOCIATION)
    {
        MOF_Feature* p;

        for (p = features; p; p = (MOF_Feature*)p->next)
        {
            if (p->type == MOF_FEATURE_REF)
            {
                MOF_error_printf(
                    "only associations can have references: \"%s\"", 
                    name);
            }
        }
    }

    /*
     * Associations must contain two or more references (CIM-2.1)
     */

    if (qual_mask & MOF_QT_ASSOCIATION)
    {
        size_t num_refs = 0;
        MOF_Feature_Info* p;

        for (p = all_features; p; p = (MOF_Feature_Info*)p->next)
        {
            if (p->feature->type == MOF_FEATURE_REF)
                num_refs++;
        }

        if (num_refs < 2)
        {
            MOF_error_printf(
                "associations must contain two or more references: \"%s\"", 
                name);
        }
    }

    /*
     * Associations cannot be a subclass of a non-association (CIM-2.1)
     */

    if (qual_mask & MOF_QT_ASSOCIATION && super_class)
    {
        if (!(super_class->qual_mask & MOF_QT_ASSOCIATION))
        {
            MOF_error_printf("associations cannot be a subclass "
                "of a non-association: \"%s\"", name);
        }
    }

    /*
     * When an association is sub-classed, its arity cannot change:
     */

    if (qual_mask & MOF_QT_ASSOCIATION && super_class)
    {
        MOF_Feature_Info* p;
        size_t num_refs1 = 0;
        size_t num_refs2 = 0;

        for (p = all_features; p; p = (MOF_Feature_Info*)p->next)
        {
            if (p->feature->type == MOF_FEATURE_REF)
                num_refs1++;
        }

        for (p = super_class->all_features; p; p = (MOF_Feature_Info*)p->next)
        {
            if (p->feature->type == MOF_FEATURE_REF)
                num_refs2++;
        }

        if (num_refs1 != num_refs2)
        {
            MOF_error_printf(
                "an association sub-class cannot add new references: \"%s\"", 
                name);
            return;
        }
    }

    /*
     * Validate that scope is correct on all qualifiers:
     */

    qualifiers->validate_list(expected_scope);

    /*
     * Disallow key definitions if any ancestor has already defined a key.
     */

    if (super_class)
    {
        size_t n1 = super_class->count_keys();
        size_t n2 = count_keys();

        if (n1 && n1 != n2)
        {
            MOF_error_printf(
                "a subclass cannot define any keys if the superclass has");
            return;
        }
    }

#if 0
    // Track average number of features.

    {
        static size_t _max_features = 0;

        MOF_Feature_Info* p;

        size_t n = 0;

        for (p = all_features; p; p = (MOF_Feature_Info*)p->next)
            n++;

        if (n > _max_features)
        {
            _max_features = n;
            printf("new max features: %s: %zu\n", name, _max_features);
        }
    }
#endif
}
/*
    Validate the class declaration and add it to the class decl list
*/
void MOF_Class_Decl::handle(MOF_Class_Decl* class_decl)
{
    class_decl->validate();

    /*
     * Add class to list.
     */

    if (MOF_Class_Decl::list)
        MOF_Class_Decl::list->append(class_decl);
    else
        MOF_Class_Decl::list = class_decl;

#if 0
    class_decl->print();
#endif
}

/*
    Return true if this class Decl is in the class hiearchy above the
    object class.
*/
bool MOF_Class_Decl::is_a(const MOF_Class_Decl* ancestor) const
{
    const MOF_Class_Decl* p;

    for (p = this; p; p = p->super_class)
    {
        if (p == ancestor)
            return true;
    }

    return false;
}

size_t MOF_Class_Decl::count_keys() const
{
    MOF_Feature_Info* p;
    size_t count = 0;

    for (p = all_features; p; p = (MOF_Feature_Info*)p->next)
    {
        if (p->feature->qual_mask & MOF_QT_KEY)
            count++;
    }

    return count;
}

void MOF_Class_Decl::print_static_list()
{
    MOF_Class_Decl* p = MOF_Class_Decl::list; 

    for (; p; p = (MOF_Class_Decl*)p->next)
        p->print();
}

/*
    Find the ansestor to the current class with the
    classname provided.  Returns 0 if none found.
*/
const MOF_Class_Decl* MOF_Class_Decl::find_ancestor(
    const char* class_name) const
{
    for (const MOF_Class_Decl* p = this; p; p = p->super_class)
    {
        if (strcasecmp(p->name, class_name) == 0)
            return p;
    }

    return 0;
}

//
// Finds Associations which have references to other association classes.
//
#if 0

static bool _is_assoc(MOF_Class_Decl* cd)
{
    MOF_Qualifier_Info* p = cd->all_qualifiers;

    for (; p; p = (MOF_Qualifier_Info*)(p->next))
    {
        if (strcasecmp(p->qualifier->name, "association") == 0)
            return true;
    }

    return false;
}

#include <vector>
#include <string>

using namespace std;

void MOF_Class_Decl::print_nested_refs()
{
    MOF_Class_Decl* p = MOF_Class_Decl::list; 
    vector<string> v;

    for (; p; p = (MOF_Class_Decl*)p->next)
    {
        // Ignore non-reference classes.

        if (p->qual_mask & MOF_QT_ASSOCIATION)
            v.push_back(p->name);
        else if (_is_assoc(p))
        {
            printf("************************* YES\n");
        }
    }

    p = MOF_Class_Decl::list; 

    for (; p; p = (MOF_Class_Decl*)p->next)
    {
        // Ignore non-reference classes.

        if (!(p->qual_mask & MOF_QT_ASSOCIATION))
            continue;

        // printf("ASSOC[%s]\n", p->name);

        MOF_Feature_Info* fi = p->all_features;

        for (; fi; fi = (MOF_Feature_Info*)(fi->next))
        {
            MOF_Feature* f = fi->feature;

            if (f->type == MOF_FEATURE_REF)
            {
                MOF_Reference_Decl* ref = (MOF_Reference_Decl*)f;

                // printf("REF[%s]\n", ref->class_name);

                for (size_t i = 0; i < v.size(); i++)
                {
                    if (v[i] == ref->class_name)
                    {
                        printf(
                            "Nested assoc: %s %s\n", p->name, ref->class_name);
                    }
                }
            }
        }
    }
}

#endif

void MOF_Class_Decl::set_owning_class(const char* owning_class_)
{
    MOF_Qualified_Element::set_owning_class(owning_class_);

    for (MOF_Feature* p = features; p; p = (MOF_Feature*)p->next)
        p->set_owning_class(owning_class_);
}
