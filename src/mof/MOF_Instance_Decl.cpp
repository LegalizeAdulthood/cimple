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

#include "MOF_Instance_Decl.h"
#include "MOF_Class_Decl.h"
#include "MOF_Error.h"
#include "MOF_Indent.h"
#include "MOF_Yacc.h"
#include "MOF_String.h"
#include "REF_Parser.h"

MOF_Instance_Decl* MOF_Instance_Decl::list = 0;

MOF_Instance_Decl::MOF_Instance_Decl() : inst_name(0), class_name(0), 
    class_decl(0), alias(0), properties(0), all_features(0)
{

}

MOF_Instance_Decl::~MOF_Instance_Decl()
{
    free(inst_name);
    free(class_name);
    free(alias);
    properties->delete_list();
    all_features->delete_list();
}

MOF_Element* MOF_Instance_Decl::clone() const
{
    MOF_ASSERT("not implemented" == 0);
    return 0;
}

void _print(const MOF_Instance_Decl* inst_decl)
{
    /*
     * Print header:
     */

    printf("+ instance of %s as %s\n", inst_decl->class_name, inst_decl->alias);

    /*
     * Print qualifiers:
     */

    inst_decl->qualifiers->print_list(1);

    /*
     * Print all qualifiers:
     */

    inst_decl->all_qualifiers->print_list(1);

    /*
     * Print the all properties list:
     */

    if (inst_decl->all_features)
        inst_decl->all_features->print_list();
}

void _make_obj_ref(
    MOF_Instance_Decl* inst_decl,
    MOF_Object_Reference*& obj_ref)
{
    MOF_Feature_Info* p;
    bool found_key = false;

    /*
     * Allocate the MOF_Object_Reference object:
     */

    if ((obj_ref = new MOF_Object_Reference()) == 0)
    {
        MOF_error("out of memory");
        return;
    }

    /*
     * Set class name:
     */

    if ((obj_ref->class_name = strdup(inst_decl->class_name)) == 0)
    {
        MOF_error("out of memory");
        return;
    }

    /*
     * Iterate the features looking for keys:
     */

    for (p = inst_decl->all_features; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* feature = p->feature;

        if (feature->qual_mask & MOF_QT_KEY)
        {
            found_key = true;

            /*
             * The feature cannot be a method because the the key qualifier
             * (which we just checked for) only applies to references and
             * properties.
             */

            MOF_ASSERT(feature->type != MOF_FEATURE_METHOD);

            /* 
             * Create new MOF_Key_Value_Pair.
             */

            MOF_Key_Value_Pair* pair = new MOF_Key_Value_Pair();

            if (pair == 0)
            {
                MOF_error("out of memory");
                return;
            }

            /* 
             * Initialize MOF_Key_Value_Pair object.
             */

            if ((pair->key = strdup(feature->name)) == 0)
            {
                MOF_error("out of memory");
                return;
            }

            /*
             * If property; else reference.
             */

            if (feature->type == MOF_FEATURE_PROP)
            {
                MOF_Property_Decl* prop_decl = (MOF_Property_Decl*)feature;

                /*
                 * Grab is_array flag.
                 */

                pair->is_array 
                    = prop_decl->array_index == 0 ? false : true;

                /*
                 * Clone the initializer.
                 */

                if (prop_decl->initializer)
                {
                    if ((pair->value = (MOF_Literal*)
                        prop_decl->initializer->clone_list()) == 0)
                    {
                        MOF_error("out of memory");
                        return;
                    }
                }
                else
                    pair->value = 0;
            }
            else if (feature->type == MOF_FEATURE_REF)
            {
                MOF_Reference_Decl* ref_decl = (MOF_Reference_Decl*)feature;

                /*
                 * It can't be an array if its a reference.
                 */

                pair->is_array = false;

                /*
                 * If the initializer is non-null.
                 */

                if (ref_decl->obj_ref)
                {
                    MOF_Literal* value = new MOF_Literal();
                    value->value_type = TOK_STRING_VALUE;
                    value->string_value = ref_decl->obj_ref->to_string();
                    pair->value = value;
                }
                else
                    pair->value = 0;
            }
            else
            {
                /* Logically unreachable. */
                MOF_ASSERT(0);
            }

            /*
             * Append to list
             */
            
            if (obj_ref->pairs)
                obj_ref->pairs->append(pair);
            else
                obj_ref->pairs = pair;
        }
    }

    if (!found_key)
        MOF_error("instance has no key fields");

    obj_ref->validate();
    obj_ref->normalize();
}

MOF_Instance_Decl* MOF_Instance_Decl::find_by_alias(
    char* alias,
    bool fix_case)
{
    MOF_Instance_Decl* p;

    if (!alias)
        return 0;

    for (p = MOF_Instance_Decl::list; p; p = (MOF_Instance_Decl*)p->next)
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

MOF_Instance_Decl* MOF_Instance_Decl::find(const char* inst_name)
{
    MOF_Instance_Decl* p;

    if (!inst_name)
        return 0;

    for (p = MOF_Instance_Decl::list; p; p = (MOF_Instance_Decl*)p->next)
    {
        MOF_ASSERT(p->inst_name);

        if (strcmp(p->inst_name, inst_name) == 0)
            return p;
    }

    return 0;
}

static void _build_all_features_list(
    const MOF_Class_Decl* class_decl, 
    MOF_Instance_Decl* inst_decl)
{
    MOF_Feature_Info* p;
    MOF_Feature_Info* all_features = 0;
    MOF_Property* q;

    /*
     * Iterate the properties in the class and build the all-properties list.
     */

    for (p = class_decl->all_features; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* feature = p->feature;
        MOF_Feature_Info* new_feature_info;
        MOF_Property* inst_prop = 0;

        /*
         * First, search for this feature in the instance declaration.
         */

        for (q = inst_decl->properties; q; q = (MOF_Property*)q->next)
        {
            if (MOF_stricmp(feature->name, q->name) == 0)
            {
                inst_prop = q;
                break;
            }
        }

        /*
         * Create a new MOF_Feature_Info object.
         */

        if ((new_feature_info = new MOF_Feature_Info()) == 0)
        {
            MOF_error("out of memory");
            return;
        } 

        /*
         * If instance contains a property with this name:
         */

        if (inst_prop)
        {
            if (feature->type == MOF_FEATURE_PROP)
            {
                MOF_Property_Decl* prop_decl;

                /*
                 * Clone the feature (and initialize).
                 */

                prop_decl = (MOF_Property_Decl*)
                    ((MOF_Property_Decl*)feature)->clone();

                if (prop_decl == 0)
                {
                    MOF_error("out of memory");
                    return;
                }

                prop_decl->qualifiers = inst_prop->qualifiers;
                prop_decl->all_qualifiers = 0;
                prop_decl->qual_mask = 0;
                prop_decl->initializer = inst_prop->initializer;

                /*
                 * Initialize the new_feature_info structure:
                 */

                new_feature_info->feature = (MOF_Feature*)prop_decl;
                new_feature_info->class_origin = p->class_origin;
                new_feature_info->propagated = p->propagated;

                /*
                 * Build the all qualifiers list
                 */

                prop_decl->all_qualifiers = 
                    MOF_Qualifier_Info::make_all_qualifiers(
                        class_decl->name, 
                        0, 
                        inst_prop->name, 
                        0,
                        prop_decl->qualifiers, 
                        feature->all_qualifiers,
                        &prop_decl->qual_mask,
                        true); /* prop */

                /*
                 * Validate the initializer (if any).
                 */

                if (inst_prop->initializer)
                {
                    inst_prop->initializer->validate("property", 
                        inst_prop->name, prop_decl->data_type, 
                        prop_decl->array_index);
                }
            }
            else if (feature->type == MOF_FEATURE_REF)
            {
                MOF_Reference_Decl* ref_decl;

                /*
                 * Clone the feature (and initialize).
                 */

                ref_decl = (MOF_Reference_Decl*)
                    ((MOF_Reference_Decl*)feature)->clone();

                if (ref_decl == 0)
                {
                    MOF_error("out of memory");
                    return;
                }

                ref_decl->qualifiers = inst_prop->qualifiers;
                ref_decl->all_qualifiers = 0;
                ref_decl->qual_mask = 0;
                ref_decl->alias = 0;

                /*
                 * Initialize the new_feature_info structure:
                 */

                new_feature_info->feature = (MOF_Feature*)ref_decl;
                new_feature_info->class_origin = p->class_origin;
                new_feature_info->propagated = p->propagated;

                /*
                 * Build the all qualifiers list
                 */

                ref_decl->all_qualifiers = 
                    MOF_Qualifier_Info::make_all_qualifiers(
                    class_decl->name, 
                    0, 
                    inst_prop->name, 
                    0,
                    ref_decl->qualifiers, 
                    feature->all_qualifiers,
                    &ref_decl->qual_mask,
                    false); /* prop */

                /*
                 * Validate the alias (ATTN) OR object reference.
                 */

                if (inst_prop->initializer)
                {
                    MOF_Object_Reference* obj_ref = 0;

                    /*
                     * Since it's a reference, we expect a string initializer.
                     */

                    if (inst_prop->initializer->value_type != TOK_STRING_VALUE)
                    {
                        MOF_error_printf(
                            "bad ref initializer for property: \"%s\"",
                            inst_prop->name);
                        return;
                    }

                    /*
                     * Parse the object reference string:
                     */

                    if (REF_parse(
                        inst_prop->initializer->string_value, &obj_ref) != 0)
                    {
                        MOF_error_printf(
                            "bad ref initializer for property: \"%s\"",
                            inst_prop->name);
                        return;
                    }

                    /*
                     * Validate and normalize new object reference.
                     */

                    obj_ref->validate();
                    obj_ref->normalize();

                    /*
                     * Be sure the class of the initializer is a sub-class 
                     * of the class of the class's ref decl.
                     */

                    ref_decl->validate_obj_ref(obj_ref);
                    ref_decl->obj_ref = obj_ref;
                }
                else if (inst_prop->alias)
                {
                    MOF_Object_Reference* obj_ref = 
                        MOF_Instance_Decl::alias_to_obj_ref(inst_prop->alias);

                    /*
                     * Be sure the class of the initializer is a sub-class 
                     * of the class of the class's ref decl.
                     */

                    ref_decl->validate_obj_ref(obj_ref);
                    ref_decl->obj_ref = obj_ref;
                }
            }
        }
        else
        {
            /*
             * Propagate feature from class.
             */

            new_feature_info->feature = p->feature;
            new_feature_info->class_origin = p->class_origin;
            new_feature_info->propagated = true;
        }

        /*
         * Append to list:
         */

        if (all_features)
            all_features->append(new_feature_info);
        else
            all_features = new_feature_info;
    }

    inst_decl->all_features = all_features;
}

static void _check_undefined_properties(
    const MOF_Class_Decl* class_decl, 
    MOF_Instance_Decl* inst_decl)
{
    MOF_Property* p;

    /* 
     * First check that all instance properties are declared in class
     * and that the types are consistent.
     */

    for (p = inst_decl->properties; p; p = (MOF_Property*)p->next)
    {
        bool found;
        MOF_Feature_Info* q;

        found = false;

        for (q = class_decl->all_features; q; q = (MOF_Feature_Info*)q->next)
        {
            MOF_Feature* feature = q->feature;

            if (MOF_stricmp(p->name, feature->name) == 0)
            {
                MOF_fix_case(p->name, feature->name);

                if (feature->type != MOF_FEATURE_METHOD)
                    found = true;

                break;
            }
        }

        if (!found)
        {
            MOF_error_printf("no such property found in class: \"%s\"",
                p->name);
            return;
        }
    }
}

static void _check_duplicate_properties(
    MOF_Instance_Decl* inst_decl)
{
    MOF_Property* p;
    MOF_Property* q;
    
    for (p = inst_decl->properties; p; p = (MOF_Property*)p->next)
    {
        for (q = inst_decl->properties; q != p; q = (MOF_Property*)q->next)
        {
            if (MOF_stricmp(p->name, q->name) == 0)
                MOF_error_printf("duplicate property: \"%s\"", p->name);
        }
    }
}

void MOF_Instance_Decl::handle(MOF_Instance_Decl* inst_decl)
{
    MOF_Class_Decl* class_decl;

    /*
     * Does class exist?
     */

    if ((class_decl = MOF_Class_Decl::find(
        inst_decl->class_name, true)) == 0)
    {
        MOF_error_printf("instance refers to undefined class: \"%s\"",
            inst_decl->class_name);
    }

    inst_decl->class_decl = class_decl;

    /*
     * Is alias already defined?
     */

    if (inst_decl->alias)
    {
        if (MOF_Class_Decl::find_by_alias(inst_decl->alias) ||
            MOF_Instance_Decl::find_by_alias(inst_decl->alias))
        {
            MOF_error_printf(
                "alias name already defined: \"%s\"", inst_decl->alias);
        }
    }

    /*
     * Build the all qualifiers list:
     */

    inst_decl->all_qualifiers = MOF_Qualifier_Info::make_all_qualifiers(
        class_decl->name, 
        0, 
        0, 
        0,
        inst_decl->qualifiers, 
        class_decl->all_qualifiers,
        &inst_decl->qual_mask,
        false); /* prop */

    /*
     * Check for duplicate features:
     */

    _check_duplicate_properties(inst_decl);

    /*
     * Validate the properties against the class:
     */

    _check_undefined_properties(class_decl, inst_decl);

    /*
     * Build the all-features list:
     */

    _build_all_features_list(class_decl, inst_decl);

    /*
     * Create an instance-name for this instance.
     */

    MOF_Object_Reference* tmp_obj_ref = 0;
    _make_obj_ref(inst_decl, tmp_obj_ref);
    char* inst_name = tmp_obj_ref->to_string();
    delete tmp_obj_ref;

    /*
     * Check that the instance name can be reparsed (sanity check).
     */

    {
        char* tmp = MOF_Object_Reference::normalize(inst_name);
        MOF_ASSERT(strcmp(inst_name, tmp) == 0);
        free(tmp);
    }

    inst_decl->inst_name = inst_name;

    // printf("=== new instance: [%s]\n", inst_name);

    /*
     * See if instance is already defined:
     */

    if (MOF_Instance_Decl::find(inst_name))
    {
        MOF_error_printf("instance already defined: \"%s\"", inst_name);
        return;
    }

    /*
     * Append instance to list:
     */

    if (MOF_Instance_Decl::list)
        MOF_Instance_Decl::list->append(inst_decl);
    else
        MOF_Instance_Decl::list = inst_decl;

#if 0
    _print(inst_decl);
#endif
}

MOF_Object_Reference* MOF_Instance_Decl::alias_to_obj_ref(const char* alias)
{
    /*
     * Lookup the instance for this alias:
     */

    MOF_Instance_Decl* inst_decl = 
        MOF_Instance_Decl::find_by_alias((char*)alias, false);

    if (!inst_decl)
        MOF_error_printf("undefined alias: \"%s\"", alias);

    /*
     * Create object reference for this instance:
     */

    MOF_Object_Reference* obj_ref = 0;
    _make_obj_ref(inst_decl, obj_ref);
    MOF_ASSERT(obj_ref != 0);

    return obj_ref;
}

void MOF_Instance_Decl::print() const
{
    printf("+ instance %s (%s)\n", inst_name, class_name);
}

void MOF_Instance_Decl::print_static_list()
{
    MOF_Instance_Decl* p = MOF_Instance_Decl::list; 

    for (; p; p = (MOF_Instance_Decl*)p->next)
        p->print();
}
