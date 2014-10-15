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

/* Create a cmpi object path based instance and namespace provided.
   NOTE: Ignores any namespace in the cimple instance.
*/
CMPIrc make_cmpi_object_path(
    const CMPIBroker* cb,
    const cimple::Instance* inst, 
    const char* ns,
    CMPIObjectPath*& cop)
{
    const Meta_Class* mc = inst->meta_class;
    const Meta_Repository* mr = mc->meta_repository;
    const char* cn = mc->name;

    cop = CMNewObjectPath(cb, ns, cn, 0);

    if (!cop)
        return CMPI_RC_ERR_FAILED;

    CMPIObjectPath_Container cont(mr, cb, ns, (CMPIObjectPath*)cop);

    if (cont.convert(inst, CIMPLE_FLAG_KEY) != 0)
        return CMPI_RC_ERR_FAILED;

    return CMPI_RC_OK;
}

/* Create a cmpi instance based on the input CIMPLE instance, the
   cop and the namespace provided.  If the cop does not exist, create it from
   the instance.
*/
CMPIrc make_cmpi_instance(
    const CMPIBroker* cb,
    const Instance* inst, 
    const char* ns,
    const CMPIObjectPath* cop,
    const char** properties,
    CMPIInstance*& ci)
{
    const Meta_Class* mc = inst->meta_class;
    const Meta_Repository* mr = mc->meta_repository;

    // Create CMPI object path (if not already created):

    if (!cop)
    {
        // TODO remove this warning before release. Primarily for testing
        CIMPLE_WARN(("No ObjectPath built before call to make_CMPI_instance"));
        CMPIObjectPath* tmp = 0;

        if (make_cmpi_object_path(cb, inst, ns, tmp) != CMPI_RC_OK)
            return CMPI_RC_ERR_FAILED;

        cop = tmp;
    }

    // Create CMPI instance using the CMNEWInstance function:

    ci = CMNewInstance(cb, cop, 0);

    // return error if no instance returned
    if (!ci)
        return CMPI_RC_ERR_FAILED;

    // Set the properties list into instance if there is a properties
    // list
    if (properties)
    {
        CMPIStatus status = CMSetPropertyFilter(ci, properties, 0);
        if (status.rc != CMPI_RC_OK)
        {
            return status.rc;
        }
    }

    {
        // create the instance container
        CMPIInstance_Container cont(mr, cb, ns, ci);

        // convert the CIMPLE instance to a CMPI instance. This calls
        // the cimple convert function which in turns will call the
        // set_value in the CMPI container for each feature to be
        // converted.        
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
    const CMPIObjectPath* cop,
    const CMPIInstance* ci,
    Instance*& inst)
{
    // Create the container for this instance

    CMPIInstance_Container cont(
        mc->meta_repository, cb, name_space(cop), (CMPIInstance*)ci);

    inst = 0;

    //Call the cimple convert function. Note that this function will,
    // in turn call the CMPI specific set_value() function to build the
    // CMPI instance.

    if (cont.convert(mc, 0, inst) != 0 || !inst)
        return CMPI_RC_ERR_FAILED;

    if (cop)
        __set_name_space_recursive(inst, name_space(cop), false);

    return CMPI_RC_OK;
}

CMPIrc make_cimple_reference(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const CMPIObjectPath* cop,
    Instance*& inst)
{
    CMPIObjectPath_Container cont(
        mc->meta_repository, cb, name_space(cop), (CMPIObjectPath*)cop);

    inst = 0;

    if (cont.convert(mc, CIMPLE_FLAG_KEY, inst) != 0 || !inst)
        return CMPI_RC_ERR_FAILED;

    if (cop)
        __set_name_space_recursive(inst, name_space(cop), false);

    return CMPI_RC_OK;
}

CMPIrc make_cimple_method(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const Meta_Method* mm,
    const CMPIObjectPath* cop,
    const CMPIArgs* in,
    void* client_data,
    Instance*& inst)
{
    CMPIArgs_Container cont(
        mc->meta_repository, cb, name_space(cop), (CMPIArgs*)in);

    inst = 0;

    if (cont.convert((Meta_Class*)mm, CIMPLE_FLAG_IN, inst) != 0 || !inst)
        return CMPI_RC_ERR_FAILED;

    if (cop)
        __set_name_space_recursive(inst, name_space(cop), false);

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
    CMPIArgs_Container cont(
        meth->meta_class->meta_repository, cb, ns, out);

    memset(&cont.return_value(), 0, sizeof(CMPIData));

    if (cont.convert(meth, CIMPLE_FLAG_OUT) != 0)
        return CMPI_RC_ERR_FAILED;

    return_value = cont.return_value().value;
    return_type = cont.return_value().type;

    return CMPI_RC_OK;
}

CIMPLE_NAMESPACE_END

