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

#include "Meta_Qualifier.h"
#include "Type.h"
#include "io.h"
#include "ptr_array.h"

CIMPLE_NAMESPACE_BEGIN

void print(const Meta_Qualifier* mq, bool& first, size_t level)
{
    // Print comma if first one:

    if (first)
        first  = false;
    else
    {
        printf(",\n");
        iprintf(level, " ");
    }

    // Print name:

    printf("%s", mq->name);

    // Print value:

    if (mq->value)
    {
        // Print opener:

        if (!mq->subscript)
            putchar('(');

        // Print value:

        print(mq->value, Type(mq->type), mq->subscript);

        // Print closer:

        if (!mq->subscript)
            putchar(')');
    }
}

static void _print_bool_qualifier(
    uint32 index, bool flag, bool& first, size_t level)
{
    if (first)
        first  = false;
    else
    {
        printf(",\n");
        iprintf(level, " ");
    }

    printf("%s", flag_names[index]);

    if (!flag)
        printf("(False)");
}

void print(
    const Meta_Qualifier* const* meta_qualifiers,
    size_t num_meta_qualifiers,
    uint32 flags,
    bool param,
    size_t level)
{
    // Count the qualifiers:

    size_t num_qualifiers = num_meta_qualifiers;

    for (uint32 i = 4; i < 32; i++)
    {
        if (CIMPLE_FLAG_READ & CIMPLE_BIT(i))
        {
            if ((flags & CIMPLE_FLAG_PROPERTY) && !param &&
                !(flags & CIMPLE_FLAG_READ))
            {
                num_qualifiers++;
            }
            continue;
        }

        if (CIMPLE_FLAG_IN & CIMPLE_BIT(i))
        {
            if (param)
                num_qualifiers++;
            continue;
        }

        if (flags & CIMPLE_BIT(i))
            num_qualifiers++;
    }

    // If no qualifiers, return now.

    if (num_qualifiers == 0)
        return;

    // Print header:

    iprintf(level, "");
    printf("[");
    bool first = true;

    // First print boolean qualifiers (the first four flags are not qualifiers).

    for (uint32 i = 4; i < 32; i++)
    {
        // Other boolean qualifiers:

        if (flags & CIMPLE_BIT(i) ||
            CIMPLE_FLAG_READ & CIMPLE_BIT(i) ||
            CIMPLE_FLAG_IN & CIMPLE_BIT(i))
        {
            if (CIMPLE_FLAG_READ & CIMPLE_BIT(i))
            {
                if ((flags & CIMPLE_FLAG_PROPERTY) && !param &&
                    !(flags & CIMPLE_FLAG_READ))
                {
                    _print_bool_qualifier(
                        i, flags & CIMPLE_FLAG_READ, first, level);
                }
                continue;
            }

            if (CIMPLE_FLAG_IN & CIMPLE_BIT(i))
            {
                if (param)
                {
                    _print_bool_qualifier(
                        i, flags & CIMPLE_FLAG_IN, first, level);
                }
                continue;
            }

            _print_bool_qualifier(i, true, first, level);
        }
    }

    // Print non-boolean qualifiers.

    for (size_t i = 0; i < num_meta_qualifiers; i++)
    {
        // Skip standard boolean qualifiers:

        if (meta_qualifiers[i]->type == BOOLEAN &&
            flag_name_to_index(meta_qualifiers[i]->name) != size_t(-1))
        {
            continue;
        }

        // Print qualifier:

        print(meta_qualifiers[i], first, level);
    }

    // Print trailer:

    printf("]");

    putchar('\n');
}

Meta_Qualifier* clone(const Meta_Qualifier* x)
{
    // Meta_Qualifier:

    Meta_Qualifier* mq = CIMPLE_CALLOC(Meta_Qualifier);
    memcpy(mq, x, sizeof(Meta_Qualifier));

    // Meta_Qualifier.name:

    mq->name = strdup(x->name);

    // Meta_Qualifier.value:

    mq->value = clone(x->value, Type(x->type), x->subscript);

    return mq;
}

Meta_Qualifier** clone(
    const Meta_Qualifier* const* meta_qualifiers,
    size_t num_meta_qualifiers)
{
    if (num_meta_qualifiers == 0)
        return 0;

    Meta_Qualifier** mqs = (Meta_Qualifier**)malloc(
        sizeof(Meta_Qualifier*) * num_meta_qualifiers);

    for (size_t i = 0; i < num_meta_qualifiers; i++)
        mqs[i] = clone(meta_qualifiers[i]);

    return mqs;
}

void destroy(Meta_Qualifier* x)
{
    // Meta_Qualifier.name:

    free((char*)x->name);

    // Meta_Qualifier.value:

    destroy((Meta_Value*)x->value, Type(x->type), x->subscript);

    // Meta_Qualifier:

    free(x);
}

const Meta_Qualifier* find(
    const Meta_Qualifier* const* meta_qualifiers, 
    size_t num_meta_qualifiers,
    const char* name)
{
    for (size_t i = 0 ; i < num_meta_qualifiers; i++)
    {
        if (strcasecmp(meta_qualifiers[i]->name, name) == 0)
            return meta_qualifiers[i];
    }

    // Not found!
    return 0;
}

void append(
    const Meta_Qualifier* const*& meta_qualifiers,
    size_t& num_meta_qualifiers,
    const Meta_Qualifier* meta_qualifier)
{
    append_ptr_array(
        *((void***)&meta_qualifiers), 
        num_meta_qualifiers, 
        (void*)meta_qualifier);
}

void filter_qualifiers(
    Meta_Qualified_Object* mqo,
    const char* const* names,
    size_t num_names)
{
    Meta_Qualifier** p = (Meta_Qualifier**)mqo->meta_qualifiers;
    size_t n = mqo->num_meta_qualifiers;
    size_t m = 0;

    for (size_t i = 0; i < n; )
    {
        bool remove = false;

        if (names)
        {
            for (size_t j = 0; j < num_names; j++)
            {
                if (eqi(names[j], p[i]->name))
                {
                    remove = true;
                    break;
                }
            }
        }
        else
            remove = true;

        if (remove)
        {
            destroy(p[i]);
            memcpy(&p[i], &p[i+1], (n - i - 1) * sizeof(Meta_Qualifier*));
            n--;
        }
        else
            i++;
    }

    if (n)
    {
        // ATTN-C: size down array to n.
        mqo->meta_qualifiers = p;
        mqo->num_meta_qualifiers = n;
    }
    else
    {
        free(p);
        mqo->meta_qualifiers = 0;
        mqo->num_meta_qualifiers = 0;
    }
}

CIMPLE_NAMESPACE_END

