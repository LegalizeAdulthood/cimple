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

#include "MOF_Key_Value_Pair.h"
#include "MOF_Feature_Info.h"
#include "MOF_Class_Decl.h"
#include "MOF_String.h"
#include "MOF_Yacc.h"
#include "MOF_Error.h"

MOF_Element* MOF_Key_Value_Pair::clone() const
{
    MOF_Key_Value_Pair* tmp = new MOF_Key_Value_Pair;

    tmp->key = strdup(key);
    tmp->value = (MOF_Literal*)value->clone();
    tmp->is_array = is_array;

    return tmp;
}

MOF_Key_Value_Pair::~MOF_Key_Value_Pair()
{
    free(key);
    delete value;
}

void MOF_Key_Value_Pair::validate(MOF_Class_Decl* class_decl)
{
    MOF_Feature_Info* p;
    int data_type = 0;
    int array_index = 0;
    bool is_key = false;
    bool is_ref = false;

    /*
     * Find the property or reference with this name:
     */

    for (p = class_decl->all_features; p; p = (MOF_Feature_Info*)p->next)
    {
        if (MOF_stricmp(p->feature->name, key) == 0)
        {
            if (p->feature->type == MOF_FEATURE_PROP)
            {
                MOF_Property_Decl* prop_decl = (MOF_Property_Decl*)p->feature;
                data_type = prop_decl->data_type;
                array_index = prop_decl->array_index;
                is_key = (p->feature->qual_mask & MOF_QT_KEY) ? true : false;
                is_ref = false;
                break;
            }
            else if (p->feature->type == MOF_FEATURE_REF)
            {
                data_type = TOK_STRING;
                array_index = 0;
                is_key = (p->feature->qual_mask & MOF_QT_KEY) ? true : false;
                is_ref = true;
                break;
            }
        }
    }

    /*
     * If property or reference not found.
     */

    if (data_type == 0)
    {
        MOF_error_printf(
            "undefined property name in reference initializer \"%s\"",
            key);
    }

    /*
     * If property or reference is not a key.
     */

    if (!is_key)
    {
        MOF_error_printf(
            "reference initializer contains a non-key property: \"%s\"",
            key);
    }

    /*
     * Check that the value is compatible with the property declaration:
     */

    if (value)
    {
        /*
         * Validate the value.
         */

        value->validate(
            "reference initializer key", key, data_type, array_index);

        /*
         * If it's a reference we must normalize.
         */

        if (is_ref && value->string_value)
        {
            MOF_ASSERT(data_type == TOK_STRING);
            char* str = MOF_Object_Reference::normalize(value->string_value);
            MOF_ASSERT(str != 0);

            free(value->string_value);
            value->string_value = str;
        }
    }
}
