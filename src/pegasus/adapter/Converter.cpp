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

#include <cimple/cimple.h>
#include <pegasus/utils/pegasus.h>
#include <cassert>
#include <cimple/Error.h>
#include "Converter.h"
#include <pegasus/utils/Str.h>
#include <pegasus/utils/Containers.h>
#include "Integer.h"

CIMPLE_NAMESPACE_BEGIN

int Converter::to_cimple_instance(
    const P_CIMInstance& pi,
    const Meta_Class* mc,
    Instance*& ci)
{
    const Meta_Repository* mr = mc->meta_repository;

    InstanceContainer cont(mr, pi);

    if ((ci = cont.convert(mc, 0)) == 0)
        return -1;

    return 0;
}

int Converter::to_cimple_key(
    const P_CIMObjectPath& op,
    const Meta_Class* mc,
    Instance*& ci)
{
    const Meta_Repository* mr = mc->meta_repository;

    ObjectPathContainer cont(mr, op);

    if ((ci = cont.convert(mc, CIMPLE_FLAG_KEY)) == 0)
        return -1;

    return 0;
}

int Converter::to_cimple_method(
    const Pegasus::Array<P_CIMParamValue>& in_params,
    const char* method_name,
    const Meta_Class* mc,
    Instance*& meth)
{
    const Meta_Repository* mr = mc->meta_repository;
    assert(mr);

    const Meta_Method* mm = find_method(mc, method_name);

    if (!mm)
        return -1;

    ParamValueContainer cont(mr, in_params);

    meth = cont.convert((const Meta_Class*)mm, CIMPLE_FLAG_IN);

    if (!meth)
        return -1;

    return 0;
}

int Converter::to_pegasus_instance(
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* inst, 
    P_CIMInstance& ci_out)
{
    CIMPLE_ASSERT(inst);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    // First create object path:

    Pegasus::CIMObjectPath cop;
    {
        cop.setClassName(inst->meta_class->name);
        cop.setHost(hn);
        cop.setNameSpace(ns);

        ObjectPathContainer cont(inst->meta_class->meta_repository, cop);

        if (cont.convert(inst, CIMPLE_FLAG_KEY) != 0)
            return -1;

        cop = cont.rep();
    }

    // Now create instance.

    Pegasus::CIMInstance ci(inst->meta_class->name);
    {
        InstanceContainer cont(inst->meta_class->meta_repository, ci);

        if (cont.convert(inst, 0) != 0)
            return -1;

        ci = cont.rep();
    }

    // Set the object path.

    ci.setPath(cop);

    ci_out = ci;
    return 0;
}

int Converter::to_pegasus_object_path(
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* inst,
    P_CIMObjectPath& cop_out)
{
    CIMPLE_ASSERT(inst);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    Pegasus::CIMObjectPath cop;
    {
        cop.setClassName(inst->meta_class->name);
        cop.setHost(hn);
        cop.setNameSpace(ns);

        ObjectPathContainer cont(inst->meta_class->meta_repository, cop);

        if (cont.convert(inst, CIMPLE_FLAG_KEY) != 0)
            return -1;

        cop = cont.rep();
    }

    cop_out = cop;
    return 0;
}

int Converter::to_pegasus_method(
    const P_String& hn,
    const P_CIMNamespaceName& ns,
    const Instance* meth,
    Pegasus::Array<P_CIMParamValue>& cpvs_out,
    P_CIMValue& return_value)
{
    CIMPLE_ASSERT(meth != 0);
    CIMPLE_ASSERT(meth->__magic == CIMPLE_INSTANCE_MAGIC);

    Pegasus::Array<P_CIMParamValue> cpvs;
    {
        ParamValueContainer cont(meth->meta_class->meta_repository, cpvs);
        cont.return_value().clear();

        if (cont.convert(meth, CIMPLE_FLAG_OUT) != 0)
            return -1;

        cpvs = cont.rep();
        return_value = cont.return_value();
    }

    cpvs_out = cpvs;
    return 0;
}

CIMPLE_NAMESPACE_END
