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
#include <cimple/Adapter_Tracer.h>

CIMPLE_NAMESPACE_BEGIN

Container::Container(const Meta_Repository* mr) : _mr(mr)
{
}

Container::~Container()
{
}
/*
    Convert an instance from the adapter format to CIMPLE. Creates a new
    instance if inst is NULL. Only property and references are converted.
    This uses the adapter get_value(), get_size(), and get_name() functions
    to access the characteristics of each feature to be converted.
*/
int Container::convert(const Meta_Class* mc, uint32 flags, Instance*& inst)
{
    PENTRY("Container::convert");
    const char* cn = mc->name;

    // Create hew new instance (if incoming one is null) and nullify
    // all properties

    if (!inst)
        inst = create(mc);

    nullify_properties(inst);

    // get property count from the adapter

    size_t size = get_size();

    // for each feature in the adapter instance, get the name, match
    // with the Meta_Feature, filter features that do not match flags,
    // and get the feature value from the adapter and insert into the
    // CIMPLE instance
    
    for (size_t i = 0; i < size; i++)
    {
        // Get name of this feature from the adapter

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

        // Get value of this feature from adapter Useing the get_value()
        // defined by the adapter subclass to get the value from the adapter
        // feature

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
    PEXIT_RTN_VAL(0);
    return 0;
}

/*
    Convert a CIMPLE instance to the type for the adapter that invokes
    this call.  It only converts features with flags corresponding to the
    flags parameter. Uses set_value, from the adapter definition to 
    create/modify the features in the adapter instance. 
    This function is the general conversion for all adapters.
    This convertes only the instance and is intended to be applied after
    any unwanted properties are nullified in the CIMPLE instance.
*/
int Container::convert(const Instance* instance, uint32 flags)
{
    PENTRY("Container::convert");
    if (!instance)
    {
        CIMPLE_WARN(("ignored null instance arg"));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    const Meta_Class* mc = instance->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        // Filter features that do not match the flags.

        if (flags && !(mf->flags & flags))
            continue;

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

        // Set the value. This calls the set_value defined for the
        // adapter which is responsible for setting the value into
        // the feature for the adapter specific instance.

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
    PEXIT_RTN_VAL(0);
    return 0;
}

CIMPLE_NAMESPACE_END
