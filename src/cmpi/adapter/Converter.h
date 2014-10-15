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
#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

inline const char* name_space(const CMPIObjectPath* op)
{
    return CMGetCharsPtr(CMGetNameSpace(op, NULL), NULL);
}

inline const char* class_name(const CMPIObjectPath* op)
{
    return CMGetCharsPtr(CMGetClassName(op, NULL), NULL);
}

inline const char* host_name(const CMPIObjectPath* op)
{
    return CMGetCharsPtr(CMGetHostname(op, NULL), NULL);
}

CMPIrc make_cimple_reference(
    const Meta_Class* mc,
    const CMPIObjectPath* op,
    Instance*& inst);

CMPIrc make_cimple_instance(
    const Meta_Class* mc,
    const CMPIInstance* cmpi_inst,
    Instance*& cimple_inst);

CMPIrc make_cmpi_object_path(
    const CMPIBroker* broker,
    const Instance* cimple_inst, 
    const char* name_space,
    CMPIObjectPath*& cmpi_op);

CMPIrc make_cmpi_instance(
    const CMPIBroker* broker,
    const Instance* cimple_inst, 
    const char* name_space,
    const CMPIObjectPath* cmpi_op,
    CMPIInstance*& cmpi_inst);

CMPIrc make_method(
    const Meta_Method* mm,
    const CMPIArgs* in,
    const Meta_Class* find_meta_class(const char*, void*),
    void* client_data,
    Instance*& cimple_meth);

CMPIrc make_method_out(
    const CMPIBroker* broker,
    const char* name_space,
    const Instance* cimple_meth,
    const CMPIArgs* out,
    CMPIValue& return_value,
    CMPIType& return_type);

#ifdef CIMPLE_NEED_CMPI_IO

void print_scalar(const CMPIData& data);

void print(const CMPIData& data);

void print(const CMPIObjectPath* op);

void print(const CMPIInstance* inst);

#endif /* CIMPLE_NEED_CMPI_IO */

CIMPLE_NAMESPACE_END

#endif /* _cmpi_Converter_h */
