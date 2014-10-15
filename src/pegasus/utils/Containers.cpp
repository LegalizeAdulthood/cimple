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

#include <cimple/config.h>
#include <cimple/log.h>
#include <cimple/integer.h>
#include "pegasus.h"
#include "Containers.h"
#include "Str.h"
#include <cimple/Adapter_Tracer.h>

// TODO - Remove this code.  This is old code to do a simple trace.
//        replaced by the Adapter_Tracer code
#if 0

struct Trc
{
    Trc(const char* file_, size_t line_) : file(file_), line(line_) 
    { 
        printf("ENTER[%s:%u]\n", file, line);
    }

    ~Trc()
    {
        printf("LEAVE[%s:%u]\n", file, line);
    }

    const char* file;
    size_t line;
};

#endif

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local routines.
//
//==============================================================================

static void _release(Array<Instance*>& a)
{
    for (size_t i = 0; i < a.size(); i++)
        unref(a[i]);
}

static Instance* _to_cimple_instance(
    const Meta_Repository* mr,
    const char* ns,
    const Pegasus::CIMInstance ci)
{
    PENTRY("_to_cimple_instance");
    Str cn(ci.getClassName());
    const Meta_Class* mc = find_meta_class(mr, *cn);

    if (!mc)
    {
        CIMPLE_WARN(("cannot find meta class: %s", *cn));
        PEXIT();
        return 0;
    }

    Instance* inst = 0;

    if (InstanceContainer(mr, ns, ci).convert(mc, 0, inst) != 0 || !inst)
    {
        PEXIT();
        return 0;
    }

    // Return only basic instance here because we have no trace function
    // for Instance * type.
    PEXIT();
    return inst;
}

static int _to_cimple_value(
    const Meta_Repository* mr,
    const char* ns,
    const Pegasus::CIMValue& cv, 
    Value& v)
{
    PENTRY("_to_cimple_value");
    if (cv.isArray())
    {
        switch (cv.getType())
        {
            case Pegasus::CIMTYPE_BOOLEAN:
            {
                Pegasus::Array<Pegasus::Boolean> x;
                cv.get(x);

                v.set_value(Array<boolean>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT8:
            {
                Pegasus::Array<Pegasus::Uint8> x;
                cv.get(x);
                v.set_value(Array<uint8>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT8:
            {
                Pegasus::Array<Pegasus::Sint8> x;
                cv.get(x);
                v.set_value(Array<sint8>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT16:
            {
                Pegasus::Array<Pegasus::Uint16> x;
                cv.get(x);
                v.set_value(Array<uint16>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT16:
            {
                Pegasus::Array<Pegasus::Sint16> x;
                cv.get(x);
                v.set_value(Array<sint16>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT32:
            {
                Pegasus::Array<Pegasus::Uint32> x;
                cv.get(x);
                v.set_value(Array<uint32>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT32:
            {
                Pegasus::Array<Pegasus::Sint32> x;
                cv.get(x);
                v.set_value(Array<sint32>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT64:
            {
                Pegasus::Array<Pegasus::Uint64> x;
                cv.get(x);
                v.set_value(Array<uint64>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT64:
            {
                Pegasus::Array<Pegasus::Sint64> x;
                cv.get(x);
                v.set_value(Array<sint64>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_REAL32:
            {
                Pegasus::Array<Pegasus::Real32> x;
                cv.get(x);
                v.set_value(Array<real32>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_REAL64:
            {
                Pegasus::Array<Pegasus::Real64> x;
                cv.get(x);
                v.set_value(Array<real64>(x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_CHAR16:
            {
                Pegasus::Array<Pegasus::Char16> x;
                cv.get(x);
                v.set_value(Array<char16>((char16*)x.getData(), x.size()));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_STRING:
            {
                Pegasus::Array<Pegasus::String> x;
                cv.get(x);

                Array<String> tmp;

                for (size_t i = 0; i < x.size(); i++)
                    tmp.append(*Str(x[i]));

                v.set_value(tmp);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_DATETIME:
            {
                Pegasus::Array<Pegasus::CIMDateTime> x;
                cv.get(x);

                Array<Datetime> tmp;

                for (size_t i = 0; i < x.size(); i++)
                    tmp.append(Datetime(*Str(x[i].toString())));

                v.set_value(tmp);
                v.null(cv.isNull());
                break;
            }

#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
            case Pegasus::CIMTYPE_INSTANCE:
            {
                Pegasus::Array<Pegasus::CIMInstance> x;
                cv.get(x);

                Array<Instance*> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    Instance* inst = _to_cimple_instance(mr, ns, x[i]);

                    if (!inst)
                    {
                        _release(a);
                        CIMPLE_WARN(("_to_cimple_instance() failed: %s",
                            *Str(x[i].getClassName())));
                        return -1;
                    }

                    a.append(inst);
                }

                v.set_value(a);
                v.null(cv.isNull());
                break;
            }
#endif /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */

            case Pegasus::CIMTYPE_OBJECT:
            {
                Pegasus::Array<Pegasus::CIMObject> x;
                cv.get(x);

                Array<Instance*> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    if (!x[i].isInstance())
                    {
                        _release(a);
                        CIMPLE_WARN(("embedded classes not supported: %s", 
                            *Str(x[i].getClassName())));
                        return -1;
                    }

                    Pegasus::CIMInstance ci(x[i]);
                    Instance* inst = _to_cimple_instance(mr, ns, ci);

                    if (!inst)
                    {
                        _release(a);
                        CIMPLE_WARN(("_to_cimple_instance() failed: %s",
                            *Str(x[i].getClassName())));
                        return -1;
                    }

                    a.append(inst);
                }

                v.set_value(a);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_REFERENCE:
            {
                Pegasus::Array<Pegasus::CIMObjectPath> x;
                cv.get(x);

                Array<Instance*> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    Str cn(x[i].getClassName());
                    const Meta_Class* mc = find_meta_class(mr, *cn);

                    if (!mc)
                    {
                        CIMPLE_WARN(("cannot find meta class: %s", *cn));
                        _release(a);
                        return -1;
                    }

                    Instance* inst = 0;
                    
                    int rc = ObjectPathContainer(mr, ns, x[i]).convert(
                        mc, CIMPLE_FLAG_KEY, inst);

                    if (rc != 0 || !inst)
                    {
                        _release(a);
                        CIMPLE_WARN((
                            "ObjectPathContainer::convert() failed: %s", 
                            mc->name));
                        return -1;
                    }

                    a.append(inst);
                }

                v.set_value(a);
                v.null(cv.isNull());
                break;
            }

            default:
                CIMPLE_WARN(("unexpected value type"));
                PEXIT_RTN_VAL(-1);
                return -1;
        }
    }
    else
    {
        switch (cv.getType())
        {
            case Pegasus::CIMTYPE_BOOLEAN:
            {
                Pegasus::Boolean x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT8:
            {
                Pegasus::Uint8 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT8:
            {
                Pegasus::Sint8 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT16:
            {
                Pegasus::Uint16 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT16:
            {
                Pegasus::Sint16 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT32:
            {
                Pegasus::Uint32 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT32:
            {
                Pegasus::Sint32 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_UINT64:
            {
                Pegasus::Uint64 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_SINT64:
            {
                Pegasus::Sint64 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_REAL32:
            {
                Pegasus::Real32 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_REAL64:
            {
                Pegasus::Real64 x;
                cv.get(x);
                v.set_value(x);
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_CHAR16:
            {
                Pegasus::Char16 x;
                cv.get(x);
                v.set_value(char16(x));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_STRING:
            {
                Pegasus::String x;
                cv.get(x);
                v.set_value(String(*Str(x)));
                v.null(cv.isNull());
                break;
            }

            case Pegasus::CIMTYPE_DATETIME:
            {
                Pegasus::CIMDateTime x;
                cv.get(x);
                v.set_value(Datetime(*Str(x.toString())));
                v.null(cv.isNull());
                break;
            }

#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
            case Pegasus::CIMTYPE_INSTANCE:
            {
                if (cv.isNull())
                {
                    v.set_value((Instance*)0);
                    v.null(true);
                }
                else
                {
                    Pegasus::CIMInstance x;
                    cv.get(x);

                    Instance* inst = _to_cimple_instance(mr, ns, x);

                    if (!inst)
                    {
                        CIMPLE_WARN(("_to_cimple_instance() failed: %s",
                            *Str(x.getClassName())));
                        return -1;
                    }

                    v.set_value(inst);
                }
                break;
            }
#endif /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */

            case Pegasus::CIMTYPE_OBJECT:
            {
                if (cv.isNull())
                {
                    v.set_value((Instance*)0);
                    v.null(true);
                }
                else
                {
                    Pegasus::CIMObject x;
                    cv.get(x);

                    if (!x.isInstance())
                    {
                        CIMPLE_WARN(("embedded classes not supported: %s",
                            *Str(x.getClassName())));
                        return -1;
                    }

                    Pegasus::CIMInstance ci(x);
                    Instance* inst = _to_cimple_instance(mr, ns, ci);

                    v.set_value(inst);
                    v.null(cv.isNull());
                }
                break;
            }

            case Pegasus::CIMTYPE_REFERENCE:
            {
                Pegasus::CIMObjectPath x;
                cv.get(x);
                Str cn(x.getClassName());

                const Meta_Class* mc = find_meta_class(mr, *cn);

                if (!mc)
                {
                    CIMPLE_WARN(("cannot find meta class: %s", *cn));
                    return -1;
                }

                Instance* inst = 0;
                
                int rc = ObjectPathContainer(mr, ns, x).convert(
                    mc, CIMPLE_FLAG_KEY, inst);

                if (rc != 0 || !inst)
                {
                    CIMPLE_WARN(("ObjectPathContainer::convert() failed: %s", 
                        *cn));
                    return -1;
                }

                v.set_value(inst);
                v.null(cv.isNull());
                break;
            }

            default:
                CIMPLE_WARN(("Unexpected value type"));
                PEXIT_RTN_VAL(-1);
                return -1;
        }
    }

    PEXIT_RTN_VAL(0);
    return 0;
}

static int _to_pegasus_instance(
    const Meta_Repository* mr,
    const char* ns,
    const Instance* x, 
    Pegasus::CIMInstance& ci)
{
    PENTRY("_to_pegasus_instance");
    if (!x)
    {
        CIMPLE_WARN(("unexpected null instance"));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    Pegasus::CIMInstance tmp(x->meta_class->name);

    InstanceContainer cont(mr, ns, tmp);

    if (cont.convert(x, 0) != 0)
    {
        CIMPLE_WARN(("InstanceContainer::convert() failed"));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    ci = cont.rep();
    PEXIT_RTN_VAL(0);
    return 0;
}

static int _to_pegasus_object_path(
    const Meta_Repository* mr,
    const char* ns,
    const Instance* x, 
    Pegasus::CIMObjectPath& cop)
{
    PENTRY("_to_pegasus_object_path");
    if (!x)
    {
        CIMPLE_WARN(("unexpected null instance"));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    Pegasus::CIMObjectPath tmp;
    tmp.setClassName(x->meta_class->name);

    if (x->__name_space.size())
        tmp.setNameSpace(x->__name_space.c_str());
    else if (ns)
        tmp.setNameSpace(ns);

    ObjectPathContainer cont(mr, ns, tmp);

    if (cont.convert(x, CIMPLE_FLAG_KEY) != 0)
    {
        CIMPLE_WARN(("ObjectPathContainer::convert() failed"));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    cop = cont.rep();

    PEXIT_RTN_VAL(0);
    return 0;
}

int _to_pegasus_value(
    const Meta_Repository* mr,
    const char* ns,
    const Value& v,
    uint32 flags,
    Pegasus::CIMValue& cv)
{
    cv.clear();

    // Handle null-case up front.

    // TODO Improve the following sligtly by removing all of the
    // return 0s in favor of break and single return.
    if (v.null())
    {
        switch (v.type())
        {
            case Value::NONE:
                CIMPLE_WARN(("unexpected value type"));
                return -1;

            case Value::BOOLEAN:
                cv.setNullValue(Pegasus::CIMTYPE_BOOLEAN, false);
                return 0;

            case Value::UINT8:
                cv.setNullValue(Pegasus::CIMTYPE_UINT8, false);
                return 0;

            case Value::SINT8:
                cv.setNullValue(Pegasus::CIMTYPE_SINT8, false);
                return 0;

            case Value::UINT16:
                cv.setNullValue(Pegasus::CIMTYPE_UINT16, false);
                return 0;

            case Value::SINT16:
                cv.setNullValue(Pegasus::CIMTYPE_SINT16, false);
                return 0;

            case Value::UINT32:
                cv.setNullValue(Pegasus::CIMTYPE_UINT32, false);
                return 0;

            case Value::SINT32:
                cv.setNullValue(Pegasus::CIMTYPE_SINT32, false);
                return 0;

            case Value::UINT64:
                cv.setNullValue(Pegasus::CIMTYPE_UINT64, false);
                return 0;

            case Value::SINT64:
                cv.setNullValue(Pegasus::CIMTYPE_SINT64, false);
                return 0;

            case Value::REAL32:
                cv.setNullValue(Pegasus::CIMTYPE_REAL32, false);
                return 0;

            case Value::REAL64:
                cv.setNullValue(Pegasus::CIMTYPE_REAL64, false);
                return 0;

            case Value::CHAR16:
                cv.setNullValue(Pegasus::CIMTYPE_CHAR16, false);
                return 0;

            case Value::STRING:
                cv.setNullValue(Pegasus::CIMTYPE_STRING, false);
                return 0;

            case Value::DATETIME:
                cv.setNullValue(Pegasus::CIMTYPE_DATETIME, false);
                return 0;

            case Value::INSTANCE:
            {
                if (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
                {
                    cv.setNullValue(Pegasus::CIMTYPE_OBJECT, false);
                }
                else if (flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
                {
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
                    cv.setNullValue(Pegasus::CIMTYPE_INSTANCE, false);
#else
                    cv.setNullValue(Pegasus::CIMTYPE_OBJECT, false);
#endif
                }
                else if (flags & CIMPLE_FLAG_REFERENCE)
                {
                    cv.setNullValue(Pegasus::CIMTYPE_REFERENCE, false);
                }
                else
                    CIMPLE_WARN(("unexpected branch"));

                return 0;
            }

            case Value::BOOLEAN_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_BOOLEAN, true);
                return 0;

            case Value::UINT8_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_UINT8, true);
                return 0;

            case Value::SINT8_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_SINT8, true);
                return 0;

            case Value::UINT16_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_UINT16, true);
                return 0;

            case Value::SINT16_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_SINT16, true);
                return 0;

            case Value::UINT32_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_UINT32, true);
                return 0;

            case Value::SINT32_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_SINT32, true);
                return 0;

            case Value::UINT64_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_UINT64, true);
                return 0;

            case Value::SINT64_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_SINT64, true);
                return 0;

            case Value::REAL32_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_REAL32, true);
                return 0;

            case Value::REAL64_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_REAL64, true);
                return 0;

            case Value::CHAR16_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_CHAR16, true);
                return 0;

            case Value::STRING_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_STRING, true);
                return 0;

            case Value::DATETIME_ARRAY:
                cv.setNullValue(Pegasus::CIMTYPE_DATETIME, true);
                return 0;

            case Value::INSTANCE_ARRAY:
            {
                if (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
                {
                    cv.setNullValue(Pegasus::CIMTYPE_OBJECT, true);
                }
                else if (flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
                {
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
                    cv.setNullValue(Pegasus::CIMTYPE_INSTANCE, true);
#else
                    cv.setNullValue(Pegasus::CIMTYPE_OBJECT, true);
#endif
                }
                else if (flags & CIMPLE_FLAG_REFERENCE)
                {
                    cv.setNullValue(Pegasus::CIMTYPE_REFERENCE, true);
                }
                else
                {
                    CIMPLE_WARN(("unexpected branch"));
                }

                return 0;
            }
        }

        // Unreachable!
        return 0;
    }

    // Handle non-null case.

    switch (v.type())
    {
        case Value::NONE:
        {
            CIMPLE_WARN(("unexpected value type"));
            return -1;
        }

        case Value::BOOLEAN:
        {
            boolean x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::UINT8:
        {
            uint8 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::SINT8:
        {
            sint8 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::UINT16:
        {
            uint16 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::SINT16:
        {
            sint16 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::UINT32:
        {
            uint32 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::SINT32:
        {
            sint32 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::UINT64:
        {
            uint64 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::SINT64:
        {
            sint64 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::REAL32:
        {
            real32 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::REAL64:
        {
            real64 x;
            v.get_value(x);
            cv.set(x);
            return 0;
        }

        case Value::CHAR16:
        {
            char16 x;
            v.get_value(x);
            uint16 code = x.code();
            cv.set(Pegasus::Char16(code));
            return 0;
        }

        case Value::STRING:
        {
            String x;
            v.get_value(x);
            cv.set(Pegasus::String(x.c_str()));
            return 0;
        }

        case Value::DATETIME:
        {
            Datetime x;
            v.get_value(x);
            cv.set(Pegasus::CIMDateTime(x.ascii().c_str()));
            return 0;
        }

        case Value::INSTANCE:
        {
            Instance* x;
            v.get_value(x);

            if (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            {
                Pegasus::CIMInstance ci;

                if (_to_pegasus_instance(mr, ns, x, ci) != 0)
                {
                    CIMPLE_WARN(("_to_pegasus_instance() failed"));
                    return -1;
                }

                cv.set(Pegasus::CIMObject(ci));
            }
            else if (flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
            {
                Pegasus::CIMInstance ci;

                if (_to_pegasus_instance(mr, ns, x, ci) != 0)
                {
                    CIMPLE_WARN(("_to_pegasus_instance() failed"));
                    return -1;
                }

                cv.set(ci);
            }
            else if (flags & CIMPLE_FLAG_REFERENCE)
            {
                Pegasus::CIMObjectPath cop;

                if (_to_pegasus_object_path(mr, ns, x, cop) != 0)
                {
                    CIMPLE_WARN(("_to_pegasus_object_path() failed"));
                    return -1;
                }
                cv.set(cop);
            }
            return 0;
        }

        case Value::BOOLEAN_ARRAY:
        {
            Array<boolean> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Boolean>(x.data(), x.size()));
            return 0;
        }

        case Value::UINT8_ARRAY:
        {
            Array<uint8> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Uint8>(x.data(), x.size()));
            return 0;
        }

        case Value::SINT8_ARRAY:
        {
            Array<sint8> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Sint8>(x.data(), x.size()));
            return 0;
        }

        case Value::UINT16_ARRAY:
        {
            Array<uint16> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Uint16>(x.data(), x.size()));
            return 0;
        }

        case Value::SINT16_ARRAY:
        {
            Array<sint16> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Sint16>(x.data(), x.size()));
            return 0;
        }

        case Value::UINT32_ARRAY:
        {
            Array<uint32> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Uint32>(x.data(), x.size()));
            return 0;
        }

        case Value::SINT32_ARRAY:
        {
            Array<sint32> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Sint32>(x.data(), x.size()));
            return 0;
        }

        case Value::UINT64_ARRAY:
        {
            Array<uint64> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Uint64>(x.data(), x.size()));
            return 0;
        }

        case Value::SINT64_ARRAY:
        {
            Array<sint64> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Sint64>(x.data(), x.size()));
            return 0;
        }

        case Value::REAL32_ARRAY:
        {
            Array<real32> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Real32>(x.data(), x.size()));
            return 0;
        }

        case Value::REAL64_ARRAY:
        {
            Array<real64> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Real64>(x.data(), x.size()));
            return 0;
        }

        case Value::CHAR16_ARRAY:
        {
            Array<char16> x;
            v.get_value(x);
            cv.set(Pegasus::Array<Pegasus::Char16>(
                (Pegasus::Char16*)x.data(), x.size()));
            return 0;
        }

        case Value::STRING_ARRAY:
        {
            Array<String> x;
            v.get_value(x);
            Pegasus::Array<Pegasus::String> a;

            for (size_t i = 0; i < x.size(); i++)
                a.append(x[i].c_str());

            cv.set(a);
            return 0;
        }

        case Value::DATETIME_ARRAY:
        {
            Array<Datetime> x;
            v.get_value(x);
            Pegasus::Array<Pegasus::CIMDateTime> a;

            for (size_t i = 0; i < x.size(); i++)
            {
                try
                {
                    Pegasus::CIMDateTime dt(x[i].ascii().c_str());
                    a.append(dt);
                }
                catch (Pegasus::Exception& e)
                {
                    CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
                    return -1;
                }
                catch (...)
                {
                    CIMPLE_WARN(("unknown exception"));
                    return -1;
                }
            }

            cv.set(a);
            return 0;
        }

        case Value::INSTANCE_ARRAY:
        {
            Array<Instance*> x;
            v.get_value(x);

            if (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            {
                Pegasus::Array<Pegasus::CIMObject> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    Pegasus::CIMInstance tmp;

                    if (_to_pegasus_instance(mr, ns, x[i], tmp) != 0)
                    {
                        CIMPLE_WARN(("_to_pegasus_instance() failed"));
                        return -1;
                    }

                    a.append(Pegasus::CIMObject(tmp));
                }

                cv.set(a);
            }
            else if (flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
            {
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES

                Pegasus::Array<Pegasus::CIMInstance> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    Pegasus::CIMInstance tmp;

                    if (_to_pegasus_instance(mr, ns, x[i], tmp) != 0)
                    {
                        CIMPLE_WARN(("_to_pegasus_instance() failed"));
                        return -1;
                    }

                    a.append(tmp);
                }

                cv.set(a);

#else /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */

                Pegasus::Array<Pegasus::CIMObject> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    Pegasus::CIMInstance tmp;

                    if (_to_pegasus_instance(mr, ns, x[i], tmp) != 0)
                    {
                        CIMPLE_WARN(("_to_pegasus_instance() failed"));
                        return -1;
                    }

                    a.append(Pegasus::CIMObject(tmp));
                }

                cv.set(a);

#endif /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */
            }
            else if (flags & CIMPLE_FLAG_REFERENCE)
            {
                Pegasus::Array<Pegasus::CIMObjectPath> a;

                for (size_t i = 0; i < x.size(); i++)
                {
                    Pegasus::CIMObjectPath tmp;

                    if (_to_pegasus_object_path(mr, ns, x[i], tmp) != 0)
                    {
                        CIMPLE_WARN(("_to_pegasus_object_path() failed"));
                        return -1;
                    }

                    a.append(tmp);
                }

                cv.set(a);
            }
            return 0;
        }
    }

    return 0;
}

//==============================================================================
//
// InstanceContainer
//
//==============================================================================

InstanceContainer::InstanceContainer(
    const Meta_Repository* mr,
    const char* ns,
    const InstanceContainer::Rep& rep)
    : 
    Container(mr),
    _ns(ns),
    _rep(rep)
{
    PENTRY("InstanceContainer::InstanceContainer");
    PEXIT();
}

InstanceContainer::~InstanceContainer()
{
}

size_t InstanceContainer::get_size()
{
    PENTRY("InstanceContainer::get_size");
    try
    {
        PEXIT();
        return _rep.getPropertyCount();
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        PEXIT();
        return 0;
    }
}

int InstanceContainer::get_name(size_t pos, String& name)
{
    PENTRY("InstanceContainer::get_name");
    try
    {
        if (pos > _rep.getPropertyCount())
        {
            CIMPLE_ERR(("bounds error"));
            PEXIT_RTN_VAL(-1);
            return -1;
        }

        Pegasus::CIMProperty cp = _rep.getProperty(pos);
        name = *Str(cp.getName());
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    PEXIT_RTN_VAL(0);
    return 0;
}

int InstanceContainer::get_value(size_t pos, Value::Type type, Value& value)
{
    PENTRY("InstanceContainer::get_value");
    try
    {
        value.clear();

        if (pos > _rep.getPropertyCount())
        {
            CIMPLE_ERR(("bounds error"));
            PEXIT_RTN_VAL(-1);
            return -1;
        }

        value.clear();
        Pegasus::CIMProperty cp = _rep.getProperty(pos);
        const Pegasus::CIMValue& cv = cp.getValue();

        if (_to_cimple_value(_mr, _ns, cv, value) != 0)
        {
            CIMPLE_WARN(("_to_cimple_value() failed"));
            PEXIT_RTN_VAL(-1);
            return -1;
        }

        // Adjust for Pegasus bug that sends instance-arrays as string-arrays.

        if (value.type() == Value::STRING_ARRAY && 
            type == Value::INSTANCE_ARRAY)
        {
            Array<Instance*> a;
            value.set_value(a);
            value.null(true);
        }

        if (value.type() != type)
        {
            CIMPLE_WARN((
                "type mismatch: %s/%s", name_of(value.type()), name_of(type)));
            PEXIT_RTN_VAL(-1);
            return -1;
        }
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    PEXIT_RTN_VAL(0);
    return 0;
}

int InstanceContainer::set_value(
    const char* name, const Value& value, uint32 flags)
{
    PENTRY("InstanceContainer::set_value");
    try
    {
        // Convert to Pegasus value.

        Pegasus::CIMValue cv;

        if (_to_pegasus_value(_mr, _ns, value, flags, cv) != 0)
        {
            CIMPLE_WARN(("_to_pegasus_value() failed"));
            PEXIT_RTN_VAL(-1);
            return -1;
        }

        // Set the property (implicitly create if it does not exist).

        Pegasus::Uint32 pos = _rep.findProperty(name);

        if (pos == Pegasus::PEG_NOT_FOUND)
        {
            try
            {
                Pegasus::CIMProperty cp(name, cv);
            }
            catch (Pegasus::Exception& e)
            {
                CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
                PEXIT_RTN_VAL(-1);
                return -1;
            }
            catch (...)
            {
                CIMPLE_WARN(("unknown exception"));
                PEXIT_RTN_VAL(-1);
                return -1;
            }
            _rep.addProperty(Pegasus::CIMProperty(name, cv));
        }
        else
        {
            Pegasus::CIMProperty cp = _rep.getProperty(pos);
            cp.setValue(cv);
        }
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    PEXIT_RTN_VAL(0);
    return 0;
}

//==============================================================================
//
// ObjectPathContainer
//
//==============================================================================

ObjectPathContainer::ObjectPathContainer(
    const Meta_Repository* mr,
    const char* ns,
    const ObjectPathContainer::Rep& rep)
    : 
    Container(mr),
    _ns(ns),
    _rep(rep)
{
}

ObjectPathContainer::~ObjectPathContainer()
{
}

size_t ObjectPathContainer::get_size()
{
    try
    {
        return _rep.getKeyBindings().size();
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return 0;
    }
}

int ObjectPathContainer::get_name(size_t pos, String& name)
{
    try
    {
        const Pegasus::Array<Pegasus::CIMKeyBinding>& bindings = 
            _rep.getKeyBindings();

        if (pos > bindings.size())
        {
            CIMPLE_ERR(("bounds error"));
            return -1;
        }

        name = *Str(bindings[pos].getName());
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return -1;
    }

    return 0;
}

int ObjectPathContainer::get_value(size_t pos, Value::Type type, Value& value)
{
    try
    {
        value.clear();

        const Pegasus::Array<Pegasus::CIMKeyBinding>& bindings = 
            _rep.getKeyBindings();

        if (pos > bindings.size())
        {
            CIMPLE_ERR(("bounds error"));
            return -1;
        }

        const Pegasus::CIMKeyBinding& kb = bindings[pos];
        Str str(kb.getValue());

        switch (type)
        {
            case Value::INSTANCE:
            {
                try
                {
                    Pegasus::CIMObjectPath op(kb.getValue());
                    Str cn(op.getClassName());

                    const Meta_Class* mc = find_meta_class(_mr, *cn);

                    if (!mc)
                    {
                        CIMPLE_WARN(("failed to find meta class: %s", *cn));
                        return -1;
                    }

                    Instance* inst = 0;
                    
                    int rc = ObjectPathContainer(_mr, _ns, op).convert(
                        mc, CIMPLE_FLAG_KEY, inst);

                    if (rc != 0 || !inst)
                    {
                        CIMPLE_WARN(("ObjectPathContainer::convert() failed"));
                        return -1;
                    }

                    value.set_value(inst);
                    return 0;
                }
                catch (Pegasus::Exception& e)
                {
                    CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
                    return -1;
                }
                catch (...)
                {
                    CIMPLE_WARN(("unknown exception"));
                    return -1;
                }
                break;
            }

            case Value::DATETIME:
            {
                Datetime x;

                if (!x.set(*str))
                {
                    CIMPLE_WARN(("datetime conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::STRING:
            {
                value.set_value(*str);
                return 0;
            }

            case Value::BOOLEAN:
            {
                if (strcasecmp(*str, "true") == 0)
                {
                    value.set_value(true);
                    return 0;
                }

                if (strcasecmp(*str, "false") == 0)
                {
                    value.set_value(false);
                    return 0;
                }

                CIMPLE_WARN(("boolean conversion error: %s", *str));
                return -1;
            }

            case Value::UINT8:
            {
                uint8 x;

                if (str_to_uint8(*str, x) != 0)
                {
                    CIMPLE_WARN(("uint8 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::SINT8:
            {
                sint8 x;

                if (str_to_sint8(*str, x) != 0)
                {
                    CIMPLE_WARN(("sint8 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::UINT16:
            {
                uint16 x;

                if (str_to_uint16(*str, x) != 0)
                {
                    CIMPLE_WARN(("uint16 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::SINT16:
            {
                sint16 x;

                if (str_to_sint16(*str, x) != 0)
                {
                    CIMPLE_WARN(("sint16 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::UINT32:
            {
                uint32 x;

                if (str_to_uint32(*str, x) != 0)
                {
                    CIMPLE_WARN(("uint32 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::SINT32:
            {
                sint32 x;

                if (str_to_sint32(*str, x) != 0)
                {
                    CIMPLE_WARN(("sint32 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::UINT64:
            {
                uint64 x;

                if (str_to_uint64(*str, x) != 0)
                {
                    CIMPLE_WARN(("uint64 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            case Value::SINT64:
            {
                sint64 x;

                if (str_to_sint64(*str, x) != 0)
                {
                    CIMPLE_WARN(("sint64 conversion error: %s", *str));
                    return -1;
                }

                value.set_value(x);
                return 0;
            }

            default:
            {
                CIMPLE_WARN(("unexpected branch"));
                return -1;
            }
        }
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return -1;
    }

    // Unreachable:
    CIMPLE_WARN(("unreachable"));
    return -1;
}

int ObjectPathContainer::set_value(
    const char* name, const Value& value, uint32 flags)
{
    try
    {
        // Convert to Pegasus value.

        Pegasus::CIMValue cv;

        if (_to_pegasus_value(_mr, _ns, value, flags, cv) != 0)
        {
            CIMPLE_WARN(("_to_pegasus_value() failed"));
            return -1;
        }

        // Create the key binding.

        Pegasus::CIMKeyBinding ckb;
        
        try 
        {
            ckb = Pegasus::CIMKeyBinding(name, cv);
        }
        catch (Pegasus::Exception& e)
        {
            CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
            return -1;
        }
        catch (...)
        {
            CIMPLE_WARN(("unknown exception"));
            return -1;
        }

        // Set key binding or update it if it already exists.

        typedef Pegasus::Array<Pegasus::CIMKeyBinding> Bindings;
        Bindings bindings = _rep.getKeyBindings();

        for (Pegasus::Uint32 i = 0; i < bindings.size(); i++)
        {
            if (bindings[i].getName() == name)
            {
                bindings[i] = ckb;
                return 0;
            }
        }

        bindings.append(ckb);
        _rep.setKeyBindings(bindings);
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return -1;
    }

    return 0;
}

//==============================================================================
//
// ParamValueContainer
//
//==============================================================================

ParamValueContainer::ParamValueContainer(
    const Meta_Repository* mr,
    const char* ns,
    const ParamValueContainer::Rep& rep)
    : 
    Container(mr),
    _ns(ns),
    _rep(rep)
{
}

ParamValueContainer::~ParamValueContainer()
{
}

size_t ParamValueContainer::get_size()
{
    return _rep.size();
}

int ParamValueContainer::get_name(size_t pos, String& name)
{
    try
    {
        if (pos > _rep.size())
        {
            CIMPLE_WARN(("bounds error"));
            return -1;
        }

        name = *Str(_rep[pos].getParameterName());
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return -1;
    }

    return 0;
}

int ParamValueContainer::get_value(size_t pos, Value::Type type, Value& value)
{
    try
    {
        value.clear();

        if (pos > _rep.size())
        {
            CIMPLE_WARN(("bounds error"));
            return -1;
        }

        value.clear();
        Pegasus::CIMParamValue pv = _rep[pos];
        const Pegasus::CIMValue& cv = pv.getValue();

        if (_to_cimple_value(_mr, _ns, cv, value) != 0)
        {
            CIMPLE_WARN(("_to_cimple_value() failed"));
            return -1;
        }

        // Adjust for Pegasus bug that sends null ref-arrays as boolean.

        if (value.type() == Value::BOOLEAN && type == Value::INSTANCE_ARRAY)
        {
            Array<Instance*> a;
            value.set_value(a);
            value.null(true);
        }

        if (value.type() != type)
        {
            CIMPLE_WARN((
                "type mismatch: %s/%s", name_of(value.type()), name_of(type)));
            return -1;
        }
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return -1;
    }

    return 0;
}

int ParamValueContainer::set_value(
    const char* name, const Value& value, uint32 flags)
{
    try
    {
        // Convert to Pegasus value.

        Pegasus::CIMValue cv;

        if (_to_pegasus_value(_mr, _ns, value, flags, cv) != 0)
        {
            CIMPLE_WARN(("_to_pegasus_value() failed"));
            return -1;
        }

        if (strcmp(name, "return_value") == 0)
        {
            _return_value = cv;
        }
        else
        {
            // Crete the parameter value.

            Pegasus::CIMParamValue cpv;

            try
            {
                cpv = Pegasus::CIMParamValue(name, cv);
            }
            catch (Pegasus::Exception& e)
            {
                CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
                return -1;
            }
            catch (...)
            {
                CIMPLE_WARN(("unknown exception"));
                return -1;
            }

            // Set the parameter (implicitly create if it does not exist).

            for (Pegasus::Uint32 i = 0; i < _rep.size(); i++)
            {
                if (strcasecmp(*Str(_rep[i].getParameterName()), name) == 0)
                {
                    _rep[i] = cpv;
                    return 0;
                }
            }

            _rep.append(cpv);
        }
    }
    catch (Pegasus::Exception& e)
    {
        CIMPLE_WARN(("unexpected exception: %s", *Str(e)));
        return -1;
    }

    return 0;
}

CIMPLE_NAMESPACE_END
