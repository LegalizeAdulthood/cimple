/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009
**               Michael Brasher, Karl Schopmeyer
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

#include <cimple/cimple.h>
#include <pegasus/utils/pegasus.h>
#include <cassert>
#include <cimple/Error.h>
#include "Converter.h"
#include <pegasus/utils/Str.h>
#include <pegasus/utils/Containers.h>
#include <cimple/Adapter_Tracer.h>

CIMPLE_NAMESPACE_BEGIN

int Converter::to_cimple_instance(
    const char* ns,
    const Pegasus::CIMInstance& pi,
    const Meta_Class* mc,
    Instance*& inst)
{
    PENTRY("Converter::to_cimple_instance");
    const Meta_Repository* mr = mc->meta_repository;

    InstanceContainer cont(mr, ns, pi);
    inst = 0;

    int rc = cont.convert(mc, 0, inst);

    if (rc != 0 || !inst)
    {
        PEXIT_RTN_VAL(-1);
        return -1;
    }

    // set the namespace in the instance and any other
    // reachable instance if not already set.
    __set_name_space_recursive(inst, ns, false);

    PEXIT_RTN_VAL(0);
    return 0;
}

int Converter::to_cimple_key(
    const char* ns,
    const Pegasus::CIMObjectPath& op,
    const Meta_Class* mc,
    Instance*& inst)
{
    PENTRY("Converter::to_cimple_key");
    const Meta_Repository* mr = mc->meta_repository;

    ObjectPathContainer cont(mr, ns, op);
    inst = 0;

    int rc = cont.convert(mc, CIMPLE_FLAG_KEY, inst);

    if (rc != 0 || !inst)
    {
        PEXIT_RTN_VAL(-1)
        return -1;
    }

    // set the namespace in the instance and any other
    // reachable instance if not already set.
    __set_name_space_recursive(inst, ns, false);
    PEXIT_RTN_VAL(0)
    return 0;
}

int Converter::to_cimple_method(
    const char* ns,
    const Pegasus::Array<Pegasus::CIMParamValue>& params,
    const char* method_name,
    const Meta_Class* mc,
    uint32 flags,
    Instance*& meth)
{
    PENTRY("Converter::to_cimple_method");
    const Meta_Repository* mr = mc->meta_repository;
    assert(mr);

    const Meta_Method* mm = find_method(mc, method_name);

    if (!mm)
    {
        PEXIT_RTN_VAL(-1)
        return -1;
    }

    ParamValueContainer cont(mr, ns, params);

    int rc = cont.convert((const Meta_Class*)mm, flags, meth);

    if (rc != 0 || !meth)
    {
        PEXIT_RTN_VAL(-1)
        return -1;
    }

    __set_name_space_recursive(meth, ns, false);

    PEXIT_RTN_VAL(0)
    return 0;
}

int Converter::to_pegasus_instance(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* inst, 
    Pegasus::CIMInstance& ci_out)
{
    PENTRY("Converter::to_pegasus_instance");

    CIMPLE_ASSERT(inst);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    // First create object path:

    Pegasus::CIMObjectPath cop;
    {
        cop.setClassName(inst->meta_class->name);
        cop.setHost(hn);
        cop.setNameSpace(ns);

        Str tns(ns);

        ObjectPathContainer cont(
            inst->meta_class->meta_repository, *tns, cop);

        if (cont.convert(inst, CIMPLE_FLAG_KEY) != 0)
        {
            PEXIT_RTN_VAL(-1)
            return -1;
        }

        cop = cont.rep();
    }

    // Now create instance.

    Pegasus::CIMInstance ci(inst->meta_class->name);
    {
        Str tns(ns);

        InstanceContainer cont(inst->meta_class->meta_repository, *tns, ci);

        if (cont.convert(inst, 0) != 0)
        {
            PEXIT_RTN_VAL(-1)
            return -1;
        }

        ci = cont.rep();
    }

    // Set the object path.

    ci.setPath(cop);

    ci_out = ci;

    PEXIT_RTN_VAL(0)
    return 0;
}

/*
    Converter for CIMPLE associator instances.  Tests for namespace in the
    instance and uses this one in place of the input namespace to
    create the instance.  This is part of associators where the
    namespace may be part of the returned associations in cross
    namespace associations
*/
int Converter::to_pegasus_assoc_instance(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* inst, 
    Pegasus::CIMInstance& ci_out)
{
    PENTRY("Converter::to_pegasus_assoc_instance");
    CIMPLE_ASSERT(inst);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    Pegasus::CIMNamespaceName result_namespace;

    if(inst->__name_space.empty())
    {
        result_namespace = ns;
    }
    else
    {
       result_namespace = 
           Pegasus::CIMNamespaceName(inst->__name_space.c_str());
    }

    int rtnVal = to_pegasus_instance(hn, result_namespace, inst, ci_out);
    PEXIT_RTN_VAL(rtnVal);
    return(rtnVal);
}

/*
    Convert for CIMPLE object paths.  Creates a pegasus
    Object Path using the key information from the input instance,
    the host information, and the namespace information provided
    Note that this function takes only the key information from
    the CIMPLE instance.
*/
int Converter::to_pegasus_object_path(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* inst,
    Pegasus::CIMObjectPath& cop_out)
{
    PENTRY("Converter::to_pegasus_object_path");
    CIMPLE_ASSERT(inst);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    Pegasus::CIMObjectPath cop;
    {
        cop.setClassName(inst->meta_class->name);
        cop.setHost(hn);
        cop.setNameSpace(ns);

        Str tns(ns);

        ObjectPathContainer cont(
            inst->meta_class->meta_repository, *tns, cop);

        if (cont.convert(inst, CIMPLE_FLAG_KEY) != 0)
        {
            PEXIT_RTN_VAL(-1);
            return -1;
        }

        cop = cont.rep();
    }

    cop_out = cop;
    PEXIT_RTN_VAL(0);
    return 0;
}

/*
    Create object path from CIMPLE Instance.  If there is no namespace
    defined in the path, use the namespace provided by ns. This differs
    from to_pegasus_object_path in using the existing path namespace if
    it exists.
    NOTE: This concept needs to be in Provider_Handler to be adapter
    independent.
*/
int Converter::to_pegasus_assoc_object_path(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* inst,
    Pegasus::CIMObjectPath& cop_out)
{
    PENTRY("Converter::to_pegasus_assoc_object_path");
    CIMPLE_ASSERT(inst);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    Pegasus::CIMNamespaceName result_namespace;

    if(inst->__name_space.empty())
    {
        result_namespace = ns;
    }
    else
    {
       result_namespace = 
           Pegasus::CIMNamespaceName(inst->__name_space.c_str());
    }

    int rtnVal = to_pegasus_object_path(hn, result_namespace, inst, cop_out);
    PEXIT_RTN_VAL(rtnVal);
    return(rtnVal);
}

int Converter::to_pegasus_method(
    const Pegasus::String& hn,
    const Pegasus::CIMNamespaceName& ns,
    const Instance* meth,
    uint32 flags,
    Pegasus::Array<Pegasus::CIMParamValue>& params,
    Pegasus::CIMValue& return_value)
{
    PENTRY("Converter::to_pegasus_method");
    CIMPLE_ASSERT(meth != 0);
    CIMPLE_ASSERT(meth->__magic == CIMPLE_INSTANCE_MAGIC);

    {
        Pegasus::Array<Pegasus::CIMParamValue> cpvs;
        Str tmp_ns(ns);
        ParamValueContainer cont(
            meth->meta_class->meta_repository, *tmp_ns, cpvs);
        cont.return_value().clear();

        if (cont.convert(meth, flags) != 0)
        {
            PEXIT_RTN_VAL(-1);
            return -1;
        }

        params = cont.rep();
        return_value = cont.return_value();
    }

    PEXIT_RTN_VAL(0);
    return 0;
}

CIMPLE_NAMESPACE_END
