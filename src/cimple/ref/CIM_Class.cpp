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

#include <cctype>
#include "CIM_Class.h"

CIMPLE_NAMESPACE_BEGIN

// The maximum size occupied by a feature.
static const size_t _FEATURE_FOOTPRINT = 16;

//==============================================================================
//
// Local routines:
//
//==============================================================================

static bool _valid_ident(const char* p)
{
    if (!isalpha(*p) && *p != '_')
        return false;

    while (isalnum(*p) || *p == '_')
        p++;

    return *p == '\0';
}

static void _cow(Meta_Class*& mc)
{
    if (Atomic_get(&mc->refs) != 1)
    {
        Meta_Class* tmp = cimple::clone(mc);
        unref(mc);
        mc = tmp;
    }
}

static void _check_ident(const char* name)
{
    if (!_valid_ident(name))
        throw Exception(Exception::BAD_NAME, "%s", name);
}

static void _check_bounds(const Meta_Class* mc, size_t pos)
{
    if (pos >= mc->num_meta_features)
        throw Exception(Exception::BOUNDS, "%s", mc->name);
}

static void _check_subscript(
    const Meta_Class* mc, const char* name, uint32 subscript)
{
    if (subscript == 0)
    {
        throw Exception(Exception::BAD_SUBSCRIPT, 
            "%s.%s: encountered zero subscript", mc->name, name);
    }
}

static void _throw_type_mismatch(const char* class_name, const char* name)
{
    throw Exception(Exception::TYPE_MISMATCH, "%s.%s", class_name, name);
}

static void _throw_null_access(const char* class_name, const char* name)
{
    throw Exception(Exception::NULL_ACCESS, 
        "%s.%s: attempt to read value of a null property",
        class_name, name);
}

static void _throw_no_such_feature(const Meta_Class* mc, const char* name)
{
    throw Exception(Exception::NO_SUCH_FEATURE, "%s.%s", mc->name, name);
}

static size_t _find_feature_index(const Meta_Class* mc, const char* name)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        if (strcasecmp(name, mf->name) == 0)
            return i;
    }

    // Not found!
    return (size_t)-1;
}

static void _append_feature(Meta_Class* mc, Meta_Feature* mf)
{
    // Meta_Class.meta_features:

    mc->meta_features = CIMPLE_REALLOC(
        (Meta_Feature**)mc->meta_features,
        mc->num_meta_features + 1,
        Meta_Feature*);

    ((Meta_Feature**)mc->meta_features)[mc->num_meta_features] = mf;

    // Meta_Class.locals:

    mc->locals = CIMPLE_REALLOC(
        (Meta_Feature_Local*)mc->locals,
        mc->num_meta_features + 1,
        Meta_Feature_Local);

    ((Meta_Feature_Local*)mc->locals)[mc->num_meta_features].local = 1;

    // Meta_Class.num_meta_features:

    mc->num_meta_features++;

    // Meta_Class.size:

    mc->size += _FEATURE_FOOTPRINT;
}

static size_t _add_property(
    Meta_Class* mc,
    const char* name, 
    Type type, 
    sint32 subscript, 
    bool key)
{
    // ATTN-C: check whether adding this property modifies the key structure
    // of the superclas.

    // Find feature:

    size_t pos = _find_feature_index(mc, name);

    if (pos == size_t(-1))
    {
        _check_ident(name);

        Meta_Property* mp = create_meta_property(
            name, type, subscript, mc->size, key);

        _append_feature(mc, (Meta_Feature*)mp);

        return mc->num_meta_features - 1;
    }
    else
    {
        // See if local property already exists.

        if (mc->locals[pos].local)
        {
            throw Exception(
                Exception::ALREADY_EXISTS, "%s.%s: property already exists", 
                mc->name, name);
        }

        // Check compatiblity with superclass:

        Meta_Feature* mf = (Meta_Feature*)mc->meta_features[pos];

        if (!(mf->flags & CIMPLE_FLAG_PROPERTY) ||
            ((const Meta_Property*)mf)->type != type ||
            ((const Meta_Property*)mf)->subscript != subscript)
        {
            throw Exception(Exception::INCOMPATIBLE_OVERRIDE, 
                "%s.%s: attempted to override a superclass feature "
                "with an incompatible feature", mc->name, name);
        }

        // Mark feature local.

        ((Meta_Feature_Local*)mc->locals)[pos].local = true;

        if (key)
            mf->flags |= CIMPLE_FLAG_KEY;

        return pos;
    }

    return pos;
}

static Meta_Property* _get_property_throw(
    const Meta_Class* mc, size_t pos)
{
    _check_bounds(mc, pos);
    const Meta_Feature* mf = mc->meta_features[pos];

    if (!(mf->flags & CIMPLE_FLAG_PROPERTY))
        throw Exception(Exception::TYPE_MISMATCH, "%s.%s", mc->name, mf->name);

    return (Meta_Property*)mf;
}

static size_t _find_property_index_throw(const Meta_Class* mc, const char* name)
{
    size_t pos = _find_feature_index(mc, name);

    if (pos == (size_t)-1)
        throw Exception(Exception::NO_SUCH_PROPERTY, "%s.%s", mc->name, name);

    const Meta_Feature* mf = mc->meta_features[pos];

    if (!(mf->flags & CIMPLE_FLAG_PROPERTY))
        throw Exception(Exception::NO_SUCH_PROPERTY, "%s.%s", mc->name, name);

    return pos;
}

template<class T>
struct Get_Integer
{
    static void func(const Meta_Class* mc, size_t pos, T& x)
    {
        Meta_Property* mp = (Meta_Property*)_get_property_throw(mc, pos);

        if (!mp->value)
            _throw_null_access(mc->name, mp->name);

        switch (Type(mp->type))
        {
            case UINT8:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<uint8>*)mp->value)->value);
                break;
            }

            case SINT8:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<sint8>*)mp->value)->value);
                break;
            }

            case UINT16:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<uint16>*)mp->value)->value);
                break;
            }

            case SINT16:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<sint16>*)mp->value)->value);
                break;
            }

            case UINT32:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<uint32>*)mp->value)->value);
                break;
            }

            case SINT32:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<sint32>*)mp->value)->value);
                break;
            }

            case UINT64:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<uint64>*)mp->value)->value);
                break;
            }

            case SINT64:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                x = T(((const Meta_Value_Scalar<sint64>*)mp->value)->value);
                break;
            }

            default:
                _throw_type_mismatch(mc->name, mp->name);
                break;
        }
    }
};

template<class T>
struct Get_Real
{
    static void func(const Meta_Class* mc, size_t pos, T& x)
    {
        Meta_Property* mp = (Meta_Property*)_get_property_throw(mc, pos);

        if (!mp->value)
            _throw_null_access(mc->name, mp->name);

        switch (Type(mp->type))
        {
            case REAL32:
                x = T(((const Meta_Value_Scalar<real32>*)mp->value)->value);
                break;

            case REAL64:
                x = T(((const Meta_Value_Scalar<real64>*)mp->value)->value);
                break;

            default:
                _throw_type_mismatch(mc->name, mp->name);
                break;
        }
    }
};

template<class T>
struct Set_Integer
{
    static void func(Meta_Class* mc, size_t pos, const T& x)
    {
        Meta_Property* mp = _get_property_throw(mc, pos);

        if (mp->subscript != 0)
            _throw_type_mismatch(mc->name, mp->name);

        switch (Type(mp->type))
        {
            case UINT8:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<uint8> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = uint8(x);
                break;
            }

            case SINT8:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<sint8> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = sint8(x);
                break;
            }

            case UINT16:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<uint16> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = uint16(x);
                break;
            }

            case SINT16:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<sint16> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = sint16(x);
                break;
            }

            case UINT32:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<uint32> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = uint32(x);
                break;
            }

            case SINT32:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<sint32> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = sint32(x);
                break;
            }

            case UINT64:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<uint64> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = uint64(x);
                break;
            }

            case SINT64:
            {
                if (!is_integer(type_of(x)))
                    _throw_type_mismatch(mc->name, mp->name);

                typedef Meta_Value_Scalar<sint64> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = sint64(x);
                break;
            }

            default:
                _throw_type_mismatch(mc->name, mp->name);
                break;
        }
    }
};

template<class T>
struct Set_Real
{
    static void func(Meta_Class* mc, size_t pos, const T& x)
    {
        Meta_Property* mp = _get_property_throw(mc, pos);

        if (mp->subscript != 0)
            _throw_type_mismatch(mc->name, mp->name);

        switch (Type(mp->type))
        {
            case REAL32:
            {
                typedef Meta_Value_Scalar<real32> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = real32(x);
                break;
            }

            case REAL64:
            {
                typedef Meta_Value_Scalar<real64> MVS;
                MVS* p = (MVS*)mp->value;

                if (!p)
                {
                    p = CIMPLE_MALLOC(MVS);
                    mp->value = (Meta_Value*)p;
                }

                p->value = real64(x);
                break;
            }

            default:
                _throw_type_mismatch(mc->name, mp->name);
                break;
        }
    }
};

template<class T>
struct Get_Array_Value
{
    static void func(const Meta_Class* mc, size_t pos, Array<T>& x)
    {
        x.clear();
        const Meta_Property* mp = _get_property_throw(mc, pos);

        if (!mp->value)
            _throw_null_access(mc->name, mp->name);

        typedef Meta_Value_Array<T> MVA;
        const MVA* mva = (const MVA*)mp->value;

        for (size_t i = 0; i < mva->num_elements; i++)
            x.append(mva->elements[i]);
    }
};

template<class T>
struct Set_Array_Value
{
    static void func(const Meta_Class* mc, size_t pos, const Array<T>& x)
    {
        Meta_Property* mp = _get_property_throw(mc, pos);

        if (mp->subscript == 0)
            _throw_type_mismatch(mc->name, mp->name);

        typedef Meta_Value_Array<T> MVA;
        MVA* mva = (MVA*)mp->value;

        if (!mva)
        {
            mva = (MVA*)malloc(sizeof(MVA));
            mp->value = (Meta_Value*)mva;
        }

        if (x.size())
        {
            mva->elements = (T*)malloc(sizeof(T) * x.size());
            memcpy((void*)mva->elements, x.data(), sizeof(T) * x.size());
            mva->num_elements = x.size();
        }
        else
        {
            mva->elements = 0;
            mva->num_elements = 0;
        }
    }
};

//==============================================================================
//
// CIM_Class
//
//==============================================================================

CIM_Class::CIM_Class(const char* name)
{
    _check_ident(name);
    _mc = create_meta_class(name, 0, CIMPLE_FLAG_CLASS);
}

CIM_Class::CIM_Class(const char* name, Association_Tag)
{
    _check_ident(name);
    _mc = create_meta_class(name, 0, CIMPLE_FLAG_ASSOCIATION);
}

CIM_Class::CIM_Class(const char* name, Indication_Tag)
{
    _check_ident(name);
    _mc = create_meta_class(name, 0, CIMPLE_FLAG_INDICATION);
}

CIM_Class::CIM_Class(const char* name, const CIM_Class& super_class)
{
    _check_ident(name);
    _mc = create_meta_class(name, super_class._mc, 0);
}

CIM_Class::CIM_Class(const CIM_Class& x)
{
    ref(_mc = x._mc);
}

CIM_Class::~CIM_Class()
{
    unref(_mc);
}

CIM_Class& CIM_Class::operator=(const CIM_Class& x)
{
    return *this;
}

void CIM_Class::print(bool local_only) const
{
    cimple::print(_mc, true, local_only);
}

bool CIM_Class::is_class() const
{
    return _mc->flags & CIMPLE_FLAG_CLASS;
}

bool CIM_Class::is_association() const
{
    return _mc->flags & CIMPLE_FLAG_ASSOCIATION;
}

bool CIM_Class::is_indication() const
{
    return _mc->flags & CIMPLE_FLAG_INDICATION;
}

size_t CIM_Class::add_property(const char* name, Type type)
{
    _cow(_mc);
    return _add_property(_mc, name, type, 0, false);
}

size_t CIM_Class::add_property(const char* name, Type type, Key_Tag)
{
    _cow(_mc);
    return _add_property(_mc, name, type, 0, true);
}

size_t CIM_Class::add_vla_property(const char* name, Type type)
{
    _cow(_mc);
    return _add_property(_mc, name, type, -1, false);
}

size_t CIM_Class::add_vla_property(const char* name, Type type, Key_Tag)
{
    _cow(_mc);
    return _add_property(_mc, name, type, -1, true);
}

size_t CIM_Class::add_fla_property(
    const char* name, 
    Type type,
    uint32 subscript)
{
    _cow(_mc);
    _check_subscript(_mc, name, subscript);
    return _add_property(_mc, name, type, sint32(subscript), false);
}

size_t CIM_Class::add_fla_property(
    const char* name, 
    Type type, 
    uint32 subscript, 
    Key_Tag)
{
    _cow(_mc);
    _check_subscript(_mc, name, subscript);
    return _add_property(_mc, name, type, sint32(subscript), true);
}

bool CIM_Class::is_null(size_t pos) const
{
    _check_bounds(_mc, pos);
    const Meta_Feature* mf = _mc->meta_features[pos];

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;
        return mp->value == 0;
    }

    // References and methods are always null.
    return true;
}

bool CIM_Class::is_null(const char* name) const
{
    const Meta_Feature* mf = find_feature(_mc, name);

    if (!mf)
        throw Exception(Exception::NO_SUCH_FEATURE, "%s.%s", _mc->name, name);

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;
        return mp->value == 0;
    }

    // References and methods are always null.
    return true;
}

bool CIM_Class::is_property(size_t pos) const
{
    _check_bounds(_mc, pos);
    return _mc->meta_features[pos]->flags & CIMPLE_FLAG_PROPERTY;
}

bool CIM_Class::is_reference(size_t pos) const
{
    _check_bounds(_mc, pos);
    return _mc->meta_features[pos]->flags & CIMPLE_FLAG_REFERENCE;
}

bool CIM_Class::is_method(size_t pos) const
{
    _check_bounds(_mc, pos);
    return _mc->meta_features[pos]->flags & CIMPLE_FLAG_METHOD;
}

CIM_Class::Type_Tag CIM_Class::get_type(size_t pos) const
{
    _check_bounds(_mc, pos);
    const Meta_Feature* mf = _mc->meta_features[pos];

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)mf;

        if (mp->subscript)
            return Type_Tag(0x80 | mp->type);
        else
            return Type_Tag(mp->type);
    }
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (const Meta_Reference*)mf;

        if (mr->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
            return mr->subscript ? INSTANCE_ARRAY : INSTANCE;
        else if (mr->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            return mr->subscript ? INSTANCE_ARRAY : INSTANCE;
        else
            return mr->subscript ? REFERENCE_ARRAY : REFERENCE;
    }
    else if (mf->flags & CIMPLE_FLAG_METHOD)
        return METHOD;

    // Unreachable!
    return BOOLEAN;
}

bool CIM_Class::is_array(size_t pos) const
{
    _check_bounds(_mc, pos);
    const Meta_Feature* mf = _mc->meta_features[pos];

    if (!(mf->flags & CIMPLE_FLAG_PROPERTY))
        throw Exception(Exception::TYPE_MISMATCH, "%s.%s", _mc->name, mf->name);

    const Meta_Property* mp = (const Meta_Property*)mf;

    return mp->subscript != 0;
}

const char* CIM_Class::get_name(size_t pos) const
{
    _check_bounds(_mc, pos);
    return _mc->meta_features[pos]->name;
}

size_t CIM_Class::count() const
{
    return _mc->num_meta_features;
}

void CIM_Class::clear(const char* name)
{
    _cow(_mc);

    Meta_Property* mp = (Meta_Property*)find_property(_mc, name);

    if (!mp)
        _throw_no_such_feature(_mc, name);

    destroy((Meta_Value*)mp->value, Type(mp->type), mp->subscript != 0);
    mp->value = 0;
}

void CIM_Class::set_property(size_t pos, boolean x)
{
    _cow(_mc);
    Meta_Property* mp = _get_property_throw(_mc, pos);

    if (!(mp->type == cimple::BOOLEAN && mp->subscript == 0))
        _throw_type_mismatch(_mc->name, mp->name);

    typedef Meta_Value_Scalar<boolean> MVS;
    MVS* p = (MVS*)mp->value;

    if (!p)
    {
        p = CIMPLE_MALLOC(MVS);
        mp->value = (Meta_Value*)p;
    }

    p->value = x;
}

void CIM_Class::set_property(size_t pos, uint8 x)
{
    _cow(_mc);
    Set_Integer<uint8>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, sint8 x)
{
    _cow(_mc);
    Set_Integer<sint8>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, uint16 x)
{
    _cow(_mc);
    Set_Integer<uint16>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, sint16 x)
{
    _cow(_mc);
    Set_Integer<sint16>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, uint32 x)
{
    _cow(_mc);
    Set_Integer<uint32>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, sint32 x)
{
    _cow(_mc);
    Set_Integer<sint32>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, uint64 x)
{
    _cow(_mc);
    Set_Integer<uint64>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, sint64 x)
{
    _cow(_mc);
    Set_Integer<sint64>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, real32 x)
{
    _cow(_mc);
    Set_Real<real32>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, real64 x)
{
    _cow(_mc);
    Set_Real<real64>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const char16& x)
{
    _cow(_mc);
    Meta_Property* mp = _get_property_throw(_mc, pos);

    if (!(mp->type == cimple::CHAR16 && mp->subscript == 0))
        _throw_type_mismatch(_mc->name, mp->name);

    typedef Meta_Value_Scalar<char16> MVS;
    MVS* p = (MVS*)mp->value;

    if (!p)
    {
        p = CIMPLE_MALLOC(MVS);
        mp->value = (Meta_Value*)p;
    }

    p->value = x;
}

void CIM_Class::set_property(size_t pos, const char* x)
{
    _cow(_mc);
    Meta_Property* mp = _get_property_throw(_mc, pos);

    if (!(mp->type == cimple::STRING && mp->subscript == 0))
        _throw_type_mismatch(_mc->name, mp->name);

    typedef Meta_Value_Scalar<char*> MVS;
    MVS* p = (MVS*)mp->value;

    if (p)
        free((char*)mp->value);
    else
    {
        p = CIMPLE_MALLOC(MVS);
        mp->value = (Meta_Value*)p;
    }

    p->value = strdup(x);
}

void CIM_Class::set_property(size_t pos, const String& x)
{
    _cow(_mc);
    set_property(pos, x.c_str());
}

void CIM_Class::set_property(size_t pos, const Datetime& x)
{
    _cow(_mc);
    Meta_Property* mp = _get_property_throw(_mc, pos);

    if (!(mp->type == cimple::DATETIME && mp->subscript == 0))
        _throw_type_mismatch(_mc->name, mp->name);

    typedef Meta_Value_Scalar<char*> MVS;
    MVS* p = (MVS*)mp->value;

    if (p)
        free((char*)mp->value);
    else
    {
        p = CIMPLE_MALLOC(MVS);
        mp->value = (Meta_Value*)p;
    }

    p->value = strdup(x.ascii().c_str());
}

void CIM_Class::set_property(const char* name, boolean x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, uint8 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, sint8 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, uint16 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, sint16 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, uint32 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, sint32 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, uint64 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, sint64 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, real32 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, real64 x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const char16& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const char* x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const String& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Datetime& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(size_t pos, const Array<boolean>& x)
{
    _cow(_mc);
    Set_Array_Value<boolean>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<uint8>& x)
{
    _cow(_mc);
    Set_Array_Value<uint8>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<sint8>& x)
{
    _cow(_mc);
    Set_Array_Value<sint8>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<uint16>& x)
{
    _cow(_mc);
    Set_Array_Value<uint16>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<sint16>& x)
{
    _cow(_mc);
    Set_Array_Value<sint16>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<uint32>& x)
{
    _cow(_mc);
    Set_Array_Value<uint32>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<sint32>& x)
{
    _cow(_mc);
    Set_Array_Value<sint32>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<uint64>& x)
{
    _cow(_mc);
    Set_Array_Value<uint64>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<sint64>& x)
{
    _cow(_mc);
    Set_Array_Value<sint64>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<real32>& x)
{
    _cow(_mc);
    Set_Array_Value<real32>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<real64>& x)
{
    _cow(_mc);
    Set_Array_Value<real64>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<char16>& x)
{
    _cow(_mc);
    Set_Array_Value<char16>::func(_mc, pos, x);
}

void CIM_Class::set_property(size_t pos, const Array<String>& x)
{
    _cow(_mc);
    Meta_Property* mp = _get_property_throw(_mc, pos);

    if (!(mp->type == cimple::STRING && mp->subscript != 0))
        _throw_type_mismatch(_mc->name, mp->name);

    typedef Meta_Value_Array<char*> MVA;
    MVA* mva = (MVA*)mp->value;

    if (!mva)
    {
        mva = (MVA*)malloc(sizeof(MVA));
        mp->value = (Meta_Value*)mva;
    }

    if (x.size())
    {
        char** elements = (char**)malloc(sizeof(char*) * x.size());

        for (size_t i = 0; i < x.size(); i++)
            elements[i] = strdup(x[i].c_str());

        mva->elements = elements;
        mva->num_elements = x.size();
    }
    else
    {
        mva->elements = 0;
        mva->num_elements = 0;
    }
}

void CIM_Class::set_property(size_t pos, const Array<Datetime>& x)
{
    _cow(_mc);
    Meta_Property* mp = _get_property_throw(_mc, pos);

    if (!(mp->type == cimple::DATETIME && mp->subscript != 0))
        _throw_type_mismatch(_mc->name, mp->name);

    typedef Meta_Value_Array<char*> MVA;
    MVA* mva = (MVA*)mp->value;

    if (!mva)
    {
        mva = (MVA*)malloc(sizeof(MVA));
        mp->value = (Meta_Value*)mva;
    }

    if (x.size())
    {
        char** elements = (char**)malloc(sizeof(char*) * x.size());

        for (size_t i = 0; i < x.size(); i++)
            elements[i] = strdup(x[i].ascii().c_str());

        mva->elements = elements;
        mva->num_elements = x.size();
    }
    else
    {
        mva->elements = 0;
        mva->num_elements = 0;
    }
}

void CIM_Class::set_property(const char* name, const Array<boolean>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<uint8>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<sint8>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<uint16>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<sint16>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<uint32>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<sint32>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<uint64>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<sint64>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<real32>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<real64>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<char16>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<String>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::set_property(const char* name, const Array<Datetime>& x)
{
    set_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(size_t pos, boolean& x) const
{
    const Meta_Property* mp = _get_property_throw(_mc, pos);

    if (mp->type != BOOLEAN)
        _throw_type_mismatch(_mc->name, mp->name);

    if (!mp->value)
        _throw_null_access(_mc->name, mp->name);

    x = ((Meta_Value_Scalar<boolean>*)mp->value)->value;
}

void CIM_Class::get_property(size_t pos, uint8& x) const
{
    Get_Integer<uint8>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, sint8& x) const
{
    Get_Integer<sint8>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, uint16& x) const
{
    Get_Integer<uint16>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, sint16& x) const
{
    Get_Integer<sint16>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, uint32& x) const
{
    Get_Integer<uint32>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, sint32& x) const
{
    Get_Integer<sint32>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, uint64& x) const
{
    Get_Integer<uint64>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, sint64& x) const
{
    Get_Integer<sint64>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, real32& x) const
{
    Get_Real<real32>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, real64& x) const
{
    Get_Real<real64>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, char16& x) const
{
    const Meta_Property* mp = _get_property_throw(_mc, pos);

    if (mp->type != CHAR16)
        _throw_type_mismatch(_mc->name, mp->name);

    if (!mp->value)
        _throw_null_access(_mc->name, mp->name);

    Meta_Value_Scalar<char16>* p = (Meta_Value_Scalar<char16>*)mp->value;

    if (!p)
        _throw_null_access(_mc->name, mp->name);

    x = p->value;
}

void CIM_Class::get_property(size_t pos, String& x) const
{
    const Meta_Property* mp = _get_property_throw(_mc, pos);

    if (mp->type != type_of(x))
        _throw_type_mismatch(_mc->name, mp->name);

    if (!mp->value)
        _throw_null_access(_mc->name, mp->name);

    Meta_Value_Scalar<char*>* p = (Meta_Value_Scalar<char*>*)mp->value;

    if (!p)
        _throw_null_access(_mc->name, mp->name);

    x = p->value;
}

void CIM_Class::get_property(size_t pos, Datetime& x) const
{
    const Meta_Property* mp = _get_property_throw(_mc, pos);

    if (mp->type != type_of(x))
        _throw_type_mismatch(_mc->name, mp->name);

    Meta_Value_Scalar<char*>* p = (Meta_Value_Scalar<char*>*)mp->value;

    if (!p)
        _throw_null_access(_mc->name, mp->name);

    x = Datetime(p->value);
}

void CIM_Class::get_property(const char* name, boolean& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, uint8& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, sint8& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, uint16& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, sint16& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, uint32& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, sint32& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, uint64& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, sint64& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, real32& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, real64& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, char16& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, String& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Datetime& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(size_t pos, Array<boolean>& x) const
{
    Get_Array_Value<boolean>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<uint8>& x) const
{
    Get_Array_Value<uint8>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<sint8>& x) const
{
    Get_Array_Value<sint8>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<uint16>& x) const
{
    Get_Array_Value<uint16>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<sint16>& x) const
{
    Get_Array_Value<sint16>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<uint32>& x) const
{
    Get_Array_Value<uint32>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<sint32>& x) const
{
    Get_Array_Value<sint32>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<uint64>& x) const
{
    Get_Array_Value<uint64>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<sint64>& x) const
{
    Get_Array_Value<sint64>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<real32>& x) const
{
    Get_Array_Value<real32>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<real64>& x) const
{
    Get_Array_Value<real64>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<char16>& x) const
{
    Get_Array_Value<char16>::func(_mc, pos, x);
}

void CIM_Class::get_property(size_t pos, Array<String>& x) const
{
    const Meta_Property* mp = _get_property_throw(_mc, pos);

    x.clear();

    if (!mp->value)
        _throw_null_access(_mc->name, mp->name);

    typedef Meta_Value_Array<const char*> MVA;
    const MVA* mva = (const MVA*)mp->value;

    for (size_t i = 0; i < mva->num_elements; i++)
        x.append(mva->elements[i]);
}

void CIM_Class::get_property(size_t pos, Array<Datetime>& x) const
{
    const Meta_Property* mp = _get_property_throw(_mc, pos);

    x.clear();

    if (!mp->value)
        _throw_null_access(_mc->name, mp->name);

    typedef Meta_Value_Array<const char*> MVA;
    const MVA* mva = (const MVA*)mp->value;

    for (size_t i = 0; i < mva->num_elements; i++)
        x.append(Datetime(mva->elements[i]));
}

void CIM_Class::get_property(const char* name, Array<boolean>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<uint8>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<sint8>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<uint16>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<sint16>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<uint32>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<sint32>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<uint64>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<sint64>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<real32>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<real64>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<char16>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<String>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

void CIM_Class::get_property(const char* name, Array<Datetime>& x) const
{
    get_property(_find_property_index_throw(_mc, name), x);
}

CIMPLE_NAMESPACE_END
