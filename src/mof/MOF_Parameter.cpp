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

#include "MOF_Parameter.h"
#include "MOF_String.h"
#include "MOF_Error.h"

MOF_Element* MOF_Parameter::clone() const 
{
    MOF_ASSERT("not implemented" == 0);
    return 0;
}

int MOF_Parameter::compatible(
    const char* class_name,
    const char* method_name,
    MOF_Parameter* p1,
    MOF_Parameter* p2)
{
    if (MOF_stricmp(p1->name, p2->name) != 0)
        return -1;

    if (strcmp(p1->name, p2->name) != 0)
    {
#if 0
        MOF_warning_printf("changing case of \"%s\" to \"%s\"",
                p1->name, p2->name);
#endif
        strcpy(p1->name, p2->name);
    }

    if (p1->data_type != p2->data_type)
        return -1;

    if (p1->array_index != p2->array_index)
        return -1;

    if (p1->ref_name || p2->ref_name)
    {
        if (p1->ref_name == 0)
            return -1;

        if (p2->ref_name == 0)
            return -1;

        if (MOF_stricmp(p1->ref_name, p2->ref_name) != 0)
            return -1;

        if (strcmp(p1->ref_name, p2->ref_name) != 0)
        {
#if 0
            MOF_warning_printf("changing case of \"%s\" to \"%s\"",
                    p1->ref_name, p2->ref_name);
#endif
            strcpy(p1->ref_name, p2->ref_name);
        }
    }

    return 0;
}

void MOF_Parameter::check_duplicates() const
{
    const MOF_Parameter* p;
    const MOF_Parameter* q;

    /*
     * Check for duplicate parameters:
     */

    for (p = this; p; p = (MOF_Parameter*)p->next)
    {
        for (q = this; q != p; q = (MOF_Parameter*)q->next)
        {
            if (MOF_stricmp(p->name, q->name) == 0)
                MOF_error_printf("duplicate parameter: \"%s\"", p->name);
        }
    }
}

