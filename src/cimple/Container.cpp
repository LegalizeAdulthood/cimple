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

#include "log.h"
#include "Container.h"
#include "Buffer.h"
#include "Property.h"

CIMPLE_NAMESPACE_BEGIN

Container::Container(const Meta_Repository* mr) : _mr(mr)
{
}

Container::~Container()
{
}

int Container::convert(const Meta_Class* mc, uint32 flags, Instance*& inst)
{
    const char* cn = mc->name;

    // Create hew new instance (if incoming one is null).

    if (!inst)
        inst = create(mc);

    nullify_properties(inst);

    size_t size = get_size();

    for (size_t i = 0; i < size; i++)
    {
        // Get name of this element.

        String name;

        if (get_name(i, name) != 0)
        {
            CIMPLE_WARN((
                "get_name() failed: class=%s, index=%u", cn, uint32(i)));
            continue;
        }

        const Meta_Feature* mf = find_feature(
            mc, name.c_str(), CIMPLE_FLAG_PROPERTY | CIMPLE_FLAG_REFERENCE);

        if (!mf)
        {
            CIMPLE_WARN(("unknown feature: %s.%s", cn, name.c_str()));
            continue;
        }

        // Filter features that do not match the flags.

        if (flags && !(mf->flags & flags))
            continue;

        // Get type:

        Value::Type type = type_of(mf);

        if (type == Value::NONE)
        {
            CIMPLE_WARN(("unexpected error: %s.%s", cn, name.c_str()));
            continue;
        }

        // Get value of this element.

        Value value;

        if (get_value(i, type, value) != 0)
        {
            CIMPLE_WARN(("conversion error: %s.%s", cn, name.c_str()));
            continue;
        }

        // Assign value into instance.

        if (value.get(inst, mf) != 0)
        {
            CIMPLE_WARN(("conversion error: %s.%s", cn, name.c_str()));
            continue;
        }
    }

    return 0;
}

int Container::convert(const Instance* instance, uint32 flags)
{
    if (!instance)
    {
        CIMPLE_WARN(("ignored null instance arg"));
        return -1;
    }

    const Meta_Class* mc = instance->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        // Filter features that do not match the flags.

        if (flags && !(mf->flags & flags))
            continue;

        // ATTN: is skipping null properties correct?

        // Skip methods, null properties, and null references.

        if (mf->flags & CIMPLE_FLAG_METHOD)
        {
            continue;
        }
        else if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            const char* field = (const char*)instance + mp->offset;

            if (null_of(mp, field))
                continue;
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;
            const char* field = (const char*)instance + mr->offset;

            if (mr->subscript)
            {
                if (((Property<Array_Ref>*)field)->null)
                    continue;
            }
            else
            {
                if (*((Instance**)field) == 0)
                    continue;
            }
        }

        // Set the value.

        Value v;

        if (v.set(instance, mf) == 0)
        {
            if (set_value(mf->name, v, mf->flags) != 0)
            {
                CIMPLE_WARN(("conversion error: %s.%s", mc->name, mf->name));
            }
        }
        else
        {
            CIMPLE_WARN(("unexpected failure: %s.%s", mc->name, mf->name));
        }
    }

    return 0;
}

CIMPLE_NAMESPACE_END
