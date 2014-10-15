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

#include <cstring>
#include <cctype>
#include <cstdarg>
#include "Instance.h"
#include "flags.h"
#include "Array.h"
#include "Property.h"
#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "Strings.h"
#include "Enc.h"
#include "Ref.h"
#include "io.h"
#include "boolean.h"
#include "integer.h"
#include "real.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Instance pack() and unpack()
//
//==============================================================================

static void _pack_value(
    Buffer& out, 
    const Instance* inst,
    const Meta_Property* mp)
{
    const void* prop = __property_of(inst, mp);

    // Put null flag.

    if (null_of(mp, prop))
    {
    pack_boolean(out, true);
    return;
    }

    pack_boolean(out, false);

    // Put value:

    if (mp->subscript == 0)
    {
    switch (mp->type)
    {
        case BOOLEAN:
        {
        pack_boolean(out, *((boolean*)prop));
        break;
        }

        case UINT8:
        case SINT8:
        {
        pack_uint8(out, *((uint8*)prop));
        break;
        }

        case UINT16:
        case SINT16:
        case CHAR16:
        {
        pack_uint16(out, *((uint16*)prop));
        break;
        }

        case UINT32:
        case SINT32:
        {
        pack_uint32(out, *((uint32*)prop));
        break;
        }

        case UINT64:
        case SINT64:
        {
        pack_uint64(out, *((uint64*)prop));
        break;
        }

        case REAL32:
        {
        pack_real32(out, *((real32*)prop));
        break;
        }

        case REAL64:
        {
        pack_real64(out, *((real64*)prop));
        break;
        }

        case DATETIME:
        {
        pack_datetime(out, *((Datetime*)prop));
        break;
        }

        case STRING:
        {
        pack_string(out, *((String*)prop));
        break;
        }
    }
    }
    else
    {
    switch (mp->type)
    {
        case BOOLEAN:
        {
        pack_boolean_array(out, *((Array<boolean>*)prop));
        break;
        }

        case UINT8:
        case SINT8:
        {
        pack_uint8_array(out, *((Array<uint8>*)prop));
        break;
        }

        case UINT16:
        case SINT16:
        case CHAR16:
        {
        pack_uint16_array(out, *((Array<uint16>*)prop));
        break;
        }

        case UINT32:
        case SINT32:
        {
        pack_uint32_array(out, *((Array<uint32>*)prop));
        break;
        }

        case UINT64:
        case SINT64:
        {
        pack_uint64_array(out, *((Array<uint64>*)prop));
        break;
        }

        case REAL32:
        {
        pack_real32_array(out, *((Array<real32>*)prop));
        break;
        }

        case REAL64:
        {
        pack_real64_array(out, *((Array<real64>*)prop));
        break;
        }

        case DATETIME:
        {
        pack_datetime_array(out, *((Array<Datetime>*)prop));
        break;
        }

        case STRING:
        {
        pack_string_array(out, *((Array<String>*)prop));
        break;
        }
    }
    }
}

static void _pack_value_local(
    Buffer& out, 
    const Instance* inst,
    const Meta_Property* mp)
{
    // ATTN: consolidate with _pack_value().

    const void* prop = __property_of(inst, mp);

    if (mp->subscript == 0 && mp->type == STRING)
    {
    pack_string(out, *((String*)prop));
    return;
    }

    switch (mp->type)
    {
    case BOOLEAN:
    {
        pack_boolean_array(out, *((Array<boolean>*)prop));
        break;
    }

    case UINT8:
    case SINT8:
    {
        pack_uint8_array(out, *((Array<uint8>*)prop));
        break;
    }

    case UINT16:
    case SINT16:
    case CHAR16:
    {
        pack_uint16_array(out, *((Array<uint16>*)prop));
        break;
    }

    case UINT32:
    case SINT32:
    {
        pack_uint32_array(out, *((Array<uint32>*)prop));
        break;
    }

    case UINT64:
    case SINT64:
    {
        pack_uint64_array(out, *((Array<uint64>*)prop));
        break;
    }

    case REAL32:
    {
        pack_real32_array(out, *((Array<real32>*)prop));
        break;
    }

    case REAL64:
    {
        pack_real64_array(out, *((Array<real64>*)prop));
        break;
    }

    case DATETIME:
    {
        pack_datetime_array(out, *((Array<Datetime>*)prop));
        break;
    }

    case STRING:
    {
        pack_string_array(out, *((Array<String>*)prop));
        break;
    }
    }
}

static void _unpack_value(
    const Buffer& in, 
    size_t& pos,
    Instance* inst,
    const Meta_Property* mp)
{
    void* prop = __property_of(inst, mp);

    boolean null_flag;
    unpack_boolean(in, pos, null_flag);

    if (null_flag)
    {
    null_of(mp, prop) = 1;
    return;
    }

    null_of(mp, prop) = 0;

    if (mp->subscript == 0)
    {
    switch (mp->type)
    {
        case BOOLEAN:
        {
        unpack_boolean(in, pos, *((boolean*)prop));
        break;
        }

        case UINT8:
        case SINT8:
        {
        unpack_uint8(in, pos, *((uint8*)prop));
        break;
        }

        case UINT16:
        case SINT16:
        case CHAR16:
        {
        unpack_uint16(in, pos, *((uint16*)prop));
        break;
        }

        case UINT32:
        case SINT32:
        {
        unpack_uint32(in, pos, *((uint32*)prop));
        break;
        }

        case UINT64:
        case SINT64:
        {
        unpack_uint64(in, pos, *((uint64*)prop));
        break;
        }

        case REAL32:
        {
        unpack_real32(in, pos, *((real32*)prop));
        break;
        }

        case REAL64:
        {
        unpack_real64(in, pos, *((real64*)prop));
        break;
        }

        case DATETIME:
        {
        unpack_datetime(in, pos, *((Datetime*)prop));
        break;
        }

        case STRING:
        {
        unpack_string(in, pos, *((String*)prop));
        break;
        }
    }
    }
    else
    {
    switch (mp->type)
    {
        case BOOLEAN:
        {
        unpack_boolean_array(in, pos, *((Array<boolean>*)prop));
        break;
        }

        case UINT8:
        case SINT8:
        {
        unpack_uint8_array(in, pos, *((Array<uint8>*)prop));
        break;
        }

        case UINT16:
        case SINT16:
        case CHAR16:
        {
        unpack_uint16_array(in, pos, *((Array<uint16>*)prop));
        break;
        }

        case UINT32:
        case SINT32:
        {
        unpack_uint32_array(in, pos, *((Array<uint32>*)prop));
        break;
        }

        case UINT64:
        case SINT64:
        {
        unpack_uint64_array(in, pos, *((Array<uint64>*)prop));
        break;
        }

        case REAL32:
        {
        unpack_real32_array(in, pos, *((Array<real32>*)prop));
        break;
        }

        case REAL64:
        {
        unpack_real64_array(in, pos, *((Array<real64>*)prop));
        break;
        }

        case DATETIME:
        {
        unpack_datetime_array(in, pos, *((Array<Datetime>*)prop));
        break;
        }

        case STRING:
        {
        unpack_string_array(in, pos, *((Array<String>*)prop));
        break;
        }
    }
    }
}

static void _unpack_value_local(
    const Buffer& in, 
    size_t& pos,
    Instance* inst,
    const Meta_Property* mp)
{
    void* prop = __property_of(inst, mp);

    if (mp->subscript == 0 && mp->type == STRING)
    {
    unpack_string(in, pos, *((String*)prop));
    return;
    }

    switch (mp->type)
    {
    case BOOLEAN:
    {
        unpack_boolean_array(in, pos, *((Array<boolean>*)prop));
        break;
    }

    case UINT8:
    case SINT8:
    {
        unpack_uint8_array(in, pos, *((Array<uint8>*)prop));
        break;
    }

    case UINT16:
    case SINT16:
    case CHAR16:
    {
        unpack_uint16_array(in, pos, *((Array<uint16>*)prop));
        break;
    }

    case UINT32:
    case SINT32:
    {
        unpack_uint32_array(in, pos, *((Array<uint32>*)prop));
        break;
    }

    case UINT64:
    case SINT64:
    {
        unpack_uint64_array(in, pos, *((Array<uint64>*)prop));
        break;
    }

    case REAL32:
    {
        unpack_real32_array(in, pos, *((Array<real32>*)prop));
        break;
    }

    case REAL64:
    {
        unpack_real64_array(in, pos, *((Array<real64>*)prop));
        break;
    }

    case DATETIME:
    {
        unpack_datetime_array(in, pos, *((Array<Datetime>*)prop));
        break;
    }

    case STRING:
    {
        unpack_string_array(in, pos, *((Array<String>*)prop));
        break;
    }
    }
}

void pack_instance(Buffer& out, const Instance* inst, bool keys_only)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);
    const Meta_Class* mc = inst->meta_class;

    // Class name:

    pack_c_str(out, mc->name);

    // Features:

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
    const Meta_Feature* mf = (Meta_Feature*)mc->meta_features[i];

    // Skip non keys (if requested).

    if (keys_only && !(mf->flags & CIMPLE_FLAG_KEY))
        continue;

    // Flags:

    pack_uint32(out, mf->flags);

    // Name:

    pack_c_str(out, mf->name);

    // Index:

#if 0
    pack_uint16(out, i);
#endif

    // Property/Reference.

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (Meta_Property*)mf;

        // Pack property type.

        pack_uint16(out, mp->type);
        pack_uint16(out, mp->subscript);

        // Pack property value:

        _pack_value(out, inst, mp);
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (Meta_Reference*)mf;

        // Pack reference type.

        pack_c_str(out, mr->meta_class->name);

        // Pack reference itself.

        Instance* tmp = *((Instance**)((uint8*)inst + mr->offset));

        if (tmp)
        {
        // Null flag:
        pack_boolean(out, false);

        if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            pack_instance(out, tmp, false);
        else
            pack_instance(out, tmp, true);
        }
        else
        {
        // Null flag:
        pack_boolean(out, true);
        }
    }
    }

    // Features terminated with null flags.

    pack_uint32(out, 0xFFFFFFFF);
}

void pack_instance_local(Buffer& out, const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);
    const Meta_Class* mc = inst->meta_class;

    // Class name:

    pack_c_str(out, mc->name);

    // CRC:

    //pack_uint32(out, mc->crc);

    // Pack footprint first:

    out.append((const char*)inst, mc->size);

    // Pack non-flat features:

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
    const Meta_Feature* mf = (Meta_Feature*)mc->meta_features[i];

    // Property/Reference.

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        // ATTN: Skip nulls?

        const Meta_Property* mp = (Meta_Property*)mf;

        if (mp->subscript || mp->type == STRING)
        _pack_value_local(out, inst, mp);
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (Meta_Reference*)mf;
        Instance* tmp = *((Instance**)((uint8*)inst + mr->offset));

        if (tmp)
        {
        if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            pack_instance_local(out, tmp);
        else
            pack_instance_local(out, tmp);
        }
    }
    }
}

Instance* unpack_instance(
    const Buffer& in, 
    size_t& pos, 
    const Meta_Class* (*lookup)(const char* class_name, void* client_data),
    void* client_data)
{
    // Class name:

    const char* class_name;
    size_t class_name_size;
    unpack_c_str(in, pos, class_name, class_name_size);

    // Lookup the class:

    const Meta_Class* mc = (*lookup)(class_name, client_data);

    if (!mc)
    return 0;

    // Create the inst:

    Ref<Instance> inst(create(mc));

    // Pack each feature.

    for (;;)
    {
    // Flags:

    uint32 flags;
    unpack_uint32(in, pos, flags);

    if (flags == 0xFFFFFFFF)
        break;

    // Name:

    const char* name;
    size_t size;
    unpack_c_str(in, pos, name, size);

    // Index:

#if 0
    uint16 index;
    unpack_uint16(in, pos, index);
#endif

    // Find meta feature.

#if 0
    const Meta_Feature* mf;

    if (index < mc->num_meta_features && 
        eqi(name, mc->meta_features[index]->name))
    {
        mf = mc->meta_features[index];
    }
    else
        mf = find_feature(mc, name);
#else
    const Meta_Feature* mf = find_feature(mc, name);
#endif

    if (!mf || mf->flags != flags)
        return 0;

    // Property/Reference.

    if (flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (Meta_Property*)mf;

        // Type:

        uint16 type;
        unpack_uint16(in, pos, type);

        if (type != mp->type)
        return 0;

        // Subscript:

        sint16 subscript;
        unpack_uint16(in, pos, *((uint16*)&subscript));

        if (subscript != mp->subscript)
        return 0;

        // Unpack property value.

        _unpack_value(in, pos, inst.ptr(), mp);
    }
    else if (flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (Meta_Reference*)mf;

        // Reference class name.

        const char* class_name;
        size_t class_name_size;
        unpack_c_str(in, pos, class_name, class_name_size);

        const Meta_Class* rc = (*lookup)(class_name, client_data);

        if (!rc)
        return 0;

        // Null flag:

        boolean null_flag;
        unpack_boolean(in, pos, null_flag);

        Instance*& ri = *((Instance**)((uint8*)inst.ptr() + mr->offset));

        if (null_flag)
        ri = 0;
        else
        {
        if (!(ri = unpack_instance(in, pos, lookup, client_data)))
            return 0;
        }
    }
    }

    return inst.steal();
}

Instance* unpack_instance_local(
    const Buffer& in, 
    size_t& pos, 
    const Meta_Class* (*lookup)(const char* class_name, void* client_data),
    void* client_data)
{
    // Unpack class_name:

    const char* class_name;
    size_t class_name_size;
    unpack_c_str(in, pos, class_name, class_name_size);

    // Lookup the class:

    const Meta_Class* mc = (*lookup)(class_name, client_data);

    if (!mc)
    return 0;

    // Unpack the CRC:

    //uint32 crc;
    //unpack_uint32(in, pos, crc);

    //if (crc != mc->crc)
    //return 0;

    // Unpack the footprint:

    Instance* footprint = (Instance*)::operator new(mc->size);
    memcpy(footprint, in.data() + pos, mc->size);
    pos += mc->size;
    __default_construct(mc, footprint, false, true);
    Ref<Instance> inst((Instance*)footprint);

    // Unpack non-flat features.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
    const Meta_Feature* mf = mc->meta_features[i];

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        // ATTN: Skip nulls?
        const Meta_Property* mp = (Meta_Property*)mf;

        if (mp->subscript || mp->type == STRING)
        _unpack_value_local(in, pos, inst.ptr(), mp);
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (Meta_Reference*)mf;

        Instance*& ri = *((Instance**)((uint8*)inst.ptr() + mr->offset));

        if (ri)
        {
        ri = unpack_instance_local(in, pos, lookup, client_data);

        if (!ri)
            return 0;
        }
    }
    }

    return inst.steal();
}


CIMPLE_NAMESPACE_END
