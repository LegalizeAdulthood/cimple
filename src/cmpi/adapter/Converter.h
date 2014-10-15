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

#ifndef _cmpi_Converter_h
#define _cmpi_Converter_h

#include <cimple/config.h>
#include <cimple/cimple.h>
#include "cmpi.h"

CIMPLE_NAMESPACE_BEGIN

inline const char* char_ptr(const CMPIString* str)
{
    const char* s = CMGetCharsPtr(str, NULL);
    return s ? s : "";
}

inline const char* name_space(const CMPIObjectPath* op)
{
    return char_ptr(CMGetNameSpace(op, NULL));
}

inline const char* class_name(const CMPIObjectPath* op)
{
    return char_ptr(CMGetClassName(op, NULL));
}

inline const char* class_name(const CMPIInstance* instance)
{
    CMPIObjectPath* cop = CMGetObjectPath(instance, NULL);

    if (!cop)
        return 0;

    return class_name(cop);
}

inline const char* host_name(const CMPIObjectPath* op)
{
    return char_ptr(CMGetHostname(op, NULL));
}

/*
    Create a CIMPLE reference from a CMPI object path
*/
CMPIrc make_cimple_reference(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const CMPIObjectPath* op,
    Instance*& inst);

/*
    Create a CIMPLE instance from a CMPI instance and objectpath
*/
CMPIrc make_cimple_instance(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const CMPIObjectPath* cop,
    const CMPIInstance* ci,
    Instance*& inst);

CMPIrc make_cimple_method(
    const CMPIBroker* cb,
    const Meta_Class* mc,
    const Meta_Method* mm,
    const CMPIObjectPath* cop,
    const CMPIArgs* in,
    void* client_data,
    Instance*& meth);

CMPIrc make_cmpi_object_path(
    const CMPIBroker* cb,
    const Instance* inst, 
    const char* ns,
    CMPIObjectPath*& cop);

/*
    Create a CMPI instance from a CIMPLE instance.

    @param cb CMPI Broker
    @param inst CIMPLE Instance. This is the input instance for the 
    conversion
    @param ns Namespace
    @param cop CIMObjectPath for the cimple instance. Creates this
    cmpi object path if it does not already exist.
    @param properties - propertylist from input
    @ci CMPIInstance Instance that is created from the cimple instance
    @return CMPI status

*/
CMPIrc make_cmpi_instance(
    const CMPIBroker* cb,
    const Instance* inst, 
    const char* ns,
    const CMPIObjectPath* cop,
    const char**properties,
    CMPIInstance*& ci);

CMPIrc make_cmpi_method(
    const CMPIBroker* cb,
    const char* ns,
    const Instance* meth,
    CMPIArgs* out,
    CMPIValue& return_value,
    CMPIType& return_type);

CIMPLE_NAMESPACE_END

#endif /* _cmpi_Converter_h */
