/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include "Meta_Method.h"
#include "flags.h"

CIMPLE_NAMESPACE_BEGIN

const Meta_Feature* find_feature(
    const Meta_Method* mm, 
    const char* name, 
    uint32 type)
{
    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
	const Meta_Feature* mf = mm->meta_features[i];

	if (strcasecmp(mf->name, name) == 0 && mf->flags & type)
	    return mf;
    }

    return 0;
}

const Meta_Property* find_parameter(const Meta_Method* mm, const char* name)
{
    return (const Meta_Property*)find_feature(mm, name, CIMPLE_FLAG_PROPERTY);
}

const Meta_Reference* find_reference(const Meta_Method* mm, const char* name)
{
    return (const Meta_Reference*)find_feature(mm, name, CIMPLE_FLAG_REFERENCE);
}

CIMPLE_NAMESPACE_END