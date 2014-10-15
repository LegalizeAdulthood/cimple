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

#include "Meta_Repository.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// find_meta_class:
//
//==============================================================================

const Meta_Class* find_meta_class(
    const Meta_Repository* mr,
    const char* class_name)
{
    if (!mr)
        return 0;

    for (size_t i = 0; i < mr->num_meta_classes; i++)
    {
        if (eqi(mr->meta_classes[i]->name, class_name))
            return mr->meta_classes[i];
    }

    // Not found!
    return 0;
}

int is_subclass(
    const Meta_Repository* meta_repository,
    const char* super,
    const char* sub)
{
    if (!meta_repository || !super || !sub)
        return -1;

    const Meta_Class* super_mc = find_meta_class(meta_repository, super);

    if (!super_mc)
        return -1;

    const Meta_Class* sub_mc = find_meta_class(meta_repository, sub);

    if (!sub_mc)
        return -1;

    return is_subclass(super_mc, sub_mc) ? 0 : 1;
}

CIMPLE_NAMESPACE_END

