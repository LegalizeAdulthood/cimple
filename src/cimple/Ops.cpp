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

#include <cstdarg>
#include "Instance_Hnd.h"
#include "Ops.h"
#include "Arg.h"
#include "Property.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Ops
//
//==============================================================================

Ops::Ops() : _rep(0)
{
}

Ops::Ops(const Ops& x)
{
    Ops_Rep::ref(_rep = x._rep);
}

Ops::~Ops()
{
    Ops_Rep::unref(_rep);
}

Ops& Ops::operator=(const Ops& x)
{
    if (x._rep != _rep)
        Ops_Rep::ref(_rep = x._rep);

    return *this;
}

template<class T>
struct Set_Property
{
    static void func(void* field, void* arg)
    {
        const Arg<T>* a = (const Arg<T>*)arg;
        Property<T>* f = (Property<T>*)field;

        f->value = a->value();
        f->null = a->null();
    }
};

template<class T>
struct Get_Property
{
    static void func(void* field, void* arg)
    {
        Arg<T>* a = (Arg<T>*)arg;
        const Property<T>* f = (const Property<T>*)field;

        if (f->null)
            a->clear();
        else
            a->value(f->value);
    }
};

void __invoke(
    Ops& ops, 
    const String& ns,
    const Instance_Ref& in,
    const Meta_Method* mm, 
    ...)
{
    // Create method instance.

    Instance* meth = create(mm);
    nullify_properties(meth);

    // Convert input arguments:
    {
        va_list ap;
        va_start(ap, mm);

        for (size_t i = 0; i < mm->num_meta_features; i++)
        {
            const Meta_Feature* mf = mm->meta_features[i];
            void* arg = va_arg(ap, void*);

            if (!(mf->flags & CIMPLE_FLAG_IN))
                continue;

            if (mf->flags & CIMPLE_FLAG_PROPERTY)
            {
                const Meta_Property* mp = (Meta_Property*)mf;
                void* field = (char*)meth + mp->offset;

                if (mp->subscript)
                {
                    switch (mp->type)
                    {
                        case BOOLEAN:
                            Set_Property<Array_boolean>::func(field, arg);
                            break;
                        case UINT8:
                            Set_Property<Array_uint8>::func(field, arg);
                            break;
                        case SINT8:
                            Set_Property<Array_sint8>::func(field, arg);
                            break;
                        case UINT16:
                            Set_Property<Array_uint16>::func(field, arg);
                            break;
                        case SINT16:
                            Set_Property<Array_sint16>::func(field, arg);
                            break;
                        case UINT32:
                            Set_Property<Array_uint32>::func(field, arg);
                            break;
                        case SINT32:
                            Set_Property<Array_sint32>::func(field, arg);
                            break;
                        case UINT64:
                            Set_Property<Array_uint64>::func(field, arg);
                            break;
                        case SINT64:
                            Set_Property<Array_sint64>::func(field, arg);
                            break;
                        case REAL32:
                            Set_Property<Array_real32>::func(field, arg);
                            break;
                        case REAL64:
                            Set_Property<Array_real64>::func(field, arg);
                            break;
                        case CHAR16:
                            Set_Property<Array_char16>::func(field, arg);
                            break;
                        case STRING:
                            Set_Property<Array_String>::func(field, arg);
                            break;
                        case DATETIME:
                            Set_Property<Array_Datetime>::func(field, arg);
                            break;
                    }
                }
                else
                {
                    switch (mp->type)
                    {
                        case BOOLEAN:
                            Set_Property<boolean>::func(field, arg);
                            break;
                        case UINT8:
                            Set_Property<uint8>::func(field, arg);
                            break;
                        case SINT8:
                            Set_Property<sint8>::func(field, arg);
                            break;
                        case UINT16:
                            Set_Property<uint16>::func(field, arg);
                            break;
                        case SINT16:
                            Set_Property<sint16>::func(field, arg);
                            break;
                        case UINT32:
                            Set_Property<uint32>::func(field, arg);
                            break;
                        case SINT32:
                            Set_Property<sint32>::func(field, arg);
                            break;
                        case UINT64:
                            Set_Property<uint64>::func(field, arg);
                            break;
                        case SINT64:
                            Set_Property<sint64>::func(field, arg);
                            break;
                        case REAL32:
                            Set_Property<real32>::func(field, arg);
                            break;
                        case REAL64:
                            Set_Property<real64>::func(field, arg);
                            break;
                        case CHAR16:
                            Set_Property<char16>::func(field, arg);
                            break;
                        case STRING:
                            Set_Property<String>::func(field, arg);
                            break;
                        case DATETIME:
                            Set_Property<Datetime>::func(field, arg);
                            break;
                    }
                }
            }
            else if (mf->flags & CIMPLE_FLAG_REFERENCE)
            {
                const Meta_Reference* mr = (Meta_Reference*)mf;
                void* field = (char*)meth + mr->offset;

                if (mr->subscript)
                {
                    Arg<Array_Instance_Hnd>* a = (Arg<Array_Instance_Hnd>*)arg;
                    Property<Array_Instance>* f = 
                        (Property<Array_Instance>*)field;

                    if (a->null())
                        f->null = 1;
                    else
                    {
                        const Array_Instance_Hnd& t = a->value();

                        for (size_t i = 0; i < t.size(); i++)
                        {
                            Instance* inst = (Instance*)t[i].instance();
                            ref(inst);
                            f->value.append(inst);
                        }

                        f->null = 0;
                    }
                }
                else
                {
                    Arg<Instance_Hnd>* a = (Arg<Instance_Hnd>*)arg;
                    Instance** f = (Instance**)field;

                    if (a->null())
                        *f = 0;
                    else
                    {
                        Instance* inst = (Instance*)a->value().instance();
                        ref(*f = inst);
                    }
                }
            }
        }

        va_end(ap);
    }

    // Fix up namespace:
    // ATTN: this makes a copy (inefficient).

    Instance_Ref tin = in;

    if (tin.name_space().size() == 0)
        tin.name_space(ns);

    // Invoke the method using the Ops implementation:

    __rep(ops)->invoke(ns, tin, meth);

    // Convert output arguments:
    {
        va_list ap;
        va_start(ap, mm);

        for (size_t i = 0; i < mm->num_meta_features; i++)
        {
            const Meta_Feature* mf = mm->meta_features[i];
            void* arg = va_arg(ap, void*);

            if (!(mf->flags & CIMPLE_FLAG_OUT))
                continue;

            if (mf->flags & CIMPLE_FLAG_PROPERTY)
            {
                const Meta_Property* mp = (Meta_Property*)mf;
                void* field = (char*)meth + mp->offset;

                if (mp->subscript)
                {
                    switch (mp->type)
                    {
                        case BOOLEAN:
                            Get_Property<Array_boolean>::func(field, arg);
                            break;
                        case UINT8:
                            Get_Property<Array_uint8>::func(field, arg);
                            break;
                        case SINT8:
                            Get_Property<Array_sint8>::func(field, arg);
                            break;
                        case UINT16:
                            Get_Property<Array_uint16>::func(field, arg);
                            break;
                        case SINT16:
                            Get_Property<Array_sint16>::func(field, arg);
                            break;
                        case UINT32:
                            Get_Property<Array_uint32>::func(field, arg);
                            break;
                        case SINT32:
                            Get_Property<Array_sint32>::func(field, arg);
                            break;
                        case UINT64:
                            Get_Property<Array_uint64>::func(field, arg);
                            break;
                        case SINT64:
                            Get_Property<Array_sint64>::func(field, arg);
                            break;
                        case REAL32:
                            Get_Property<Array_real32>::func(field, arg);
                            break;
                        case REAL64:
                            Get_Property<Array_real64>::func(field, arg);
                            break;
                        case CHAR16:
                            Get_Property<Array_char16>::func(field, arg);
                            break;
                        case STRING:
                            Get_Property<Array_String>::func(field, arg);
                            break;
                        case DATETIME:
                            Get_Property<Array_Datetime>::func(field, arg);
                            break;
                    }
                }
                else
                {
                    switch (mp->type)
                    {
                        case BOOLEAN:
                            Get_Property<boolean>::func(field, arg);
                            break;
                        case UINT8:
                            Get_Property<uint8>::func(field, arg);
                            break;
                        case SINT8:
                            Get_Property<sint8>::func(field, arg);
                            break;
                        case UINT16:
                            Get_Property<uint16>::func(field, arg);
                            break;
                        case SINT16:
                            Get_Property<sint16>::func(field, arg);
                            break;
                        case UINT32:
                            Get_Property<uint32>::func(field, arg);
                            break;
                        case SINT32:
                            Get_Property<sint32>::func(field, arg);
                            break;
                        case UINT64:
                            Get_Property<uint64>::func(field, arg);
                            break;
                        case SINT64:
                            Get_Property<sint64>::func(field, arg);
                            break;
                        case REAL32:
                            Get_Property<real32>::func(field, arg);
                            break;
                        case REAL64:
                            Get_Property<real64>::func(field, arg);
                            break;
                        case CHAR16:
                            Get_Property<char16>::func(field, arg);
                            break;
                        case STRING:
                            Get_Property<String>::func(field, arg);
                            break;
                        case DATETIME:
                            Get_Property<Datetime>::func(field, arg);
                            break;
                    }
                }
            }
            else if (mf->flags & CIMPLE_FLAG_REFERENCE)
            {
                const Meta_Reference* mr = (Meta_Reference*)mf;
                void* field = (char*)meth + mr->offset;

                if (mr->subscript)
                {
                    Arg<Array_Instance_Hnd>* a = (Arg<Array_Instance_Hnd>*)arg;
                    Property<Array_Instance>* f = 
                        (Property<Array_Instance>*)field;

                    if (f->null)
                        a->clear();
                    else
                    {
                        Array_Instance_Hnd t;

                        for (size_t i = 0; i < f->value.size(); i++)
                        {
                            Instance* inst = f->value[i];

                            if (inst)
                            {
                                ref(inst);
                                t.append(Instance_Hnd(inst));
                            }

                            // ATTN: null instance elements ignored!
                        }
                    }
                }
                else
                {
                    Arg<Instance_Hnd>* a = (Arg<Instance_Hnd>*)arg;
                    Instance** f = (Instance**)field;

                    if (*f == 0)
                        a->clear();
                    else
                        a->value(Instance_Hnd(*f));
                }
            }
        }

        va_end(ap);
    }

    // Destroy the method:

    destroy(meth);
}

//==============================================================================
//
// Ops_Rep
//
//==============================================================================

Ops_Rep::Ops_Rep() : refs(1)
{
}

Ops_Rep::~Ops_Rep()
{
}

void Ops_Rep::ref(const Ops_Rep* rep)
{
    Ops_Rep* p = (Ops_Rep*)rep;
    p->refs.inc();
}

void Ops_Rep::unref(const Ops_Rep* rep)
{
    Ops_Rep* p = (Ops_Rep*)rep;

    if (p->refs.dec_and_test())
        delete p;
}

CIMPLE_NAMESPACE_END
