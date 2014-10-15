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

#include <vector>
#include "MOF_Object_Reference.h"
#include "MOF_Error.h"
#include "MOF_String.h"
#include "MOF_Yacc.h"
#include "MOF_Class_Decl.h"
#include "REF_Parser.h"

#ifdef __USE_GNU
extern "C" FILE* open_memstream(char **, size_t *);
#endif

MOF_Object_Reference::~MOF_Object_Reference()
{
    if (class_name)
        free(class_name);

    if (pairs)
        pairs->delete_list();
}

void MOF_Object_Reference::validate()
{
    MOF_Class_Decl* class_decl;
    MOF_Key_Value_Pair* p;

    /*
     * Does class exist?
     */

    if ((class_decl = MOF_Class_Decl::find(class_name)) == 0)
    {
        MOF_error_printf("class undefined in reference initializer: \"%s\"", 
            class_name);
    }

    /*
     * Validate each key-value pair:
     */

    for (p = pairs; p; p = (MOF_Key_Value_Pair*)p->next)
        p->validate(class_decl);

    /*
     * Check to see that there are as many key-value pairs as keys in the
     * the class.
     */

    if (class_decl->count_keys() != pairs->list_size())
    {
        MOF_error("class contains keys which are missing "
            "from the reference initializer");
    }
}

static int _compare(const void* ptr1, const void* ptr2)
{
    MOF_Key_Value_Pair** p1 = (MOF_Key_Value_Pair**)ptr1;
    MOF_Key_Value_Pair** p2 = (MOF_Key_Value_Pair**)ptr2;

    return strcmp((*p1)->key, (*p2)->key);
}

void MOF_Object_Reference::normalize()
{
    size_t count;

    /*
     * Sort the key-value pairs:
     */

    if ((count = pairs->list_size()))
    {
        MOF_Key_Value_Pair* p;
        MOF_Key_Value_Pair** tmp_pairs;
        size_t i;

        /*
         * Allocate an array of pointers to the key-value pairs:
         */

        if ((tmp_pairs = (MOF_Key_Value_Pair**)calloc(
            1, sizeof(MOF_Key_Value_Pair*) * count)) == 0)
        {
            MOF_error("out of memory");
            return;
        }

        /*
         * Initialize the array of pointers and shift key names to lower
         * case as you go.
         */

        for (p = pairs, i = 0; p; p = (MOF_Key_Value_Pair*)p->next, i++)
        {
            tmp_pairs[i] = p;
            MOF_strtolower(p->key);
        }

        /*
         * Sort the array (in ascending order by key):
         */

        qsort(tmp_pairs, count, sizeof(MOF_Key_Value_Pair*), _compare);

        /*
         * Reset the linked list pointers so the linked list is in sorted order.
         */

        for (i = 0; i < count; i++)
            tmp_pairs[i]->next = 0;

        for (i = 1; i < count; i++)
            tmp_pairs[i-1]->append(tmp_pairs[i]);

        MOF_ASSERT(tmp_pairs[0]->list_size() == count);

        /*
         * Set new pairs head:
         */

        pairs = tmp_pairs[0];

        /*
         * Release the temporary array.
         */

        free(tmp_pairs);
    }

    /*
     * Shift the class name to lower case:
     */

    MOF_strtolower(class_name);
}

void MOF_Object_Reference::print(FILE* stream) const
{
    MOF_Key_Value_Pair* p;

    /*
     * Print the class name:
     */

    fprintf(stream, "%s", class_name);

    if (pairs)
        fprintf(stream, ".");

    /*
     * Print key-value pairs:
     */

    for (p = pairs; p; p = (MOF_Key_Value_Pair*)p->next)
    {
        /*
         * Print the name:
         */

        fprintf(stream, "%s=", p->key);

        if (p->value)
            p->value->print(stream, p->is_array);
        else
            fprintf(stream, "NULL");

        if (p->next)
            fprintf(stream, ",");
    }
}

char* MOF_Object_Reference::to_string() const
{

#ifdef __USE_GNU

    char* buffer = 0;
    size_t buffer_size = 0;
    FILE* stream = open_memstream(&buffer, &buffer_size);
    print(stream);
    fputc('\0', stream);
    fclose(stream);

    return buffer;

#else /* __USE_GNU */

    const char FILE_NAME[] = "memstream.tmp";

    // Write memstream temporary file:

    FILE* stream = fopen(FILE_NAME, "wb");

    if (!stream)
        MOF_error_printf("failed to open %s for write", FILE_NAME);

    print(stream);
    fclose(stream);

    // Reopen file for read:

    stream = fopen(FILE_NAME, "rb");

    if (!stream)
        MOF_error_printf("failed to open %s for read", FILE_NAME);

    size_t n;
    char buffer[4096];
    std::vector<char> v;

    while ((n = fread(buffer, 1, sizeof(buffer), stream)) > 0)
        v.insert(v.end(), buffer, buffer + n);

    v.push_back('\0');
    fclose(stream);

    return strdup(&v[0]);

#endif /* __USE_GNU */
}

char* MOF_Object_Reference::normalize(const char* asc7)
{
    /*
     * Parse the string (to create an obj-ref).
     */

    MOF_Object_Reference* obj_ref;

    if (REF_parse(asc7, &obj_ref) != 0)
    {
        MOF_error_printf(
            "malformed object reference: \"%s\"", ref_error_message);
    }

    /*
     * Validate (causing further parsing of object references).
     */

    obj_ref->validate();

    /*
     * Normalize the obj-ref.
     */

    obj_ref->normalize();

    /*
     * Convert to string.
     */

    char* tmp = obj_ref->to_string();

    delete obj_ref;

    return tmp;
}

