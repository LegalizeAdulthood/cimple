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

#include <cassert>
#include <cstring>
#include <cimple/Strings.h>
#include "CMPI_Containers.h"
#include "Converter.h"

CIMPLE_NAMESPACE_BEGIN

static void _set_namespace_callback(Instance* inst, void* data)
{
    const char* ns = (const char*)data;

    if (inst->__name_space.size() == 0)
        inst->__name_space = ns;
}

CMPIrc make_cmpi_object_path(
    const CMPIBroker* cb,
    const cimple::Instance* inst, 
    const char* ns,
    CMPIObjectPath*& cop)
{
    const Meta_Class* mc = inst->meta_class;
    const Meta_Repository* mr = mc->meta_repository;
    const char* cn = mc->name;

    visit((Instance*)inst, _set_namespace_callback, (void*)ns);

    cop = CMNewObjectPath(cb, ns, cn, 0);

    if (!cop)
        return CMPI_RC_ERR_FAILED;

    CMPIObjectPath_Container cont(mr, cb, (CMPIObjectPath*)cop);

    if (cont.convert(inst, CIMPLE_FLAG_KEY) != 0)
        return CMPI_RC_ERR_FAILED;

    return CMPI_RC_OK;
}

CMPIrc make_cmpi_instance(
    const CMPIBroker* cb,
    const Instance* inst, 
    const char* ns,
    const CMPIObjectPath* cop,
    CMPIInstance*& ci)
{
    const Meta_Class* mc = inst->meta_class;
    const Meta_Repository* mr = mc->meta_repository;

    // Fill in namespace (if still empty):

    visit((Instance*)inst, _set_namespace_callback, (void*)ns);

    // Create CMPI object path (if not already created):

    if (!cop)
    {
        CMPIObjectPath* tmp = 0;

        if (make_cmpi_object_path(cb, inst, ns, tmp) != CMPI_RC_OK)
            return CMPI_RC_ERR_FAILED;

        cop = tmp;
    }

    // Create CMPI instance:

    ci = CMNewInstance(cb, cop, 0);
    {
        CMPIInstance_Container cont(mr, cb, ci);

        if (cont.convert(inst, 0) != 0)
        {
            return CMPI_RC_ERR_FAILED;
        }
    }

    return CMPI_RC_OK;
}

CMPIrc make_cimple_instance(
    const CMPIBroker* cb,
    const cimple::Meta_Class* mc,
    const CMPIInstance* ci,
    Instance*& inst)
{
    CMPIInstance_Container cont(mc->meta_repository, cb, (CMPIInstance*)ci);
    inst = cont.convert(mc, 0);

    if (!inst)
        return CMPI_RC_ERR_FAILED;

    return CMPI_RC_OK;
}

CMPIrc make_cimple_reference(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const CMPIObjectPath* op,
    Instance*& inst)
{
    CMPIObjectPath_Container cont(mc->meta_repository, cb, (CMPIObjectPath*)op);
    inst = cont.convert(mc, CIMPLE_FLAG_KEY);

    if (!inst)
        return CMPI_RC_ERR_FAILED;

    return CMPI_RC_OK;
}

CMPIrc make_cimple_method(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const Meta_Method* mm,
    const CMPIArgs* in,
    void* client_data,
    Instance*& inst)
{
    CMPIArgs_Container cont(mc->meta_repository, cb, (CMPIArgs*)in);
    inst = cont.convert((Meta_Class*)mm, CIMPLE_FLAG_IN);

    if (!inst)
        return CMPI_RC_ERR_FAILED;

    return CMPI_RC_OK;
}

CMPIrc make_cmpi_method(
    const CMPIBroker* cb,
    const char* ns,
    const Instance* meth,
    CMPIArgs* out,
    CMPIValue& return_value,
    CMPIType& return_type)
{
    visit((Instance*)meth, _set_namespace_callback, (void*)ns);

    CMPIArgs_Container cont(meth->meta_class->meta_repository, cb, out);
    memset(&cont.return_value(), 0, sizeof(CMPIData));

    if (cont.convert(meth, CIMPLE_FLAG_OUT) != 0)
        return CMPI_RC_ERR_FAILED;

    return_value = cont.return_value().value;
    return_type = cont.return_value().type;

    return CMPI_RC_OK;
}

CIMPLE_NAMESPACE_END

