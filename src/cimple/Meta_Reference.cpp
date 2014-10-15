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

#include "Meta_Reference.h"
#include "Meta_Class.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

Meta_Reference* clone(const Meta_Reference* x)
{
    Meta_Reference* mr = (Meta_Reference*)malloc(sizeof(Meta_Reference));
    memcpy(mr, x, sizeof(Meta_Reference));
    mr->name = strdup(x->name);
    ref(mr->meta_class = x->meta_class);

    return mr;
}

void destroy(Meta_Reference* mr)
{
    // Meta_Reference.name:
    free((char*)(mr->name));

    // Meta_Reference.meta_qualifiers:

    for (size_t i = 0; i < mr->num_meta_qualifiers; i++)
        destroy((Meta_Qualifier*)mr->meta_qualifiers[i]);

    free((Meta_Qualifier*)mr->meta_qualifiers);

    // Meta_Reference.meta_class:
    unref(mr->meta_class);

    // Meta_Reference:
    free(mr);
}

//==============================================================================
//
// print()
//
//==============================================================================

void print(const Meta_Reference* mr)
{
    printf("%s ref %s", mr->meta_class->name, mr->name);

    if (mr->subscript > 0)
        printf("[%d]", mr->subscript);
    else if (mr->subscript < 0)
        printf("[]");
}

CIMPLE_NAMESPACE_END

