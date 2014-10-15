/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** Copyright (c) 2007 Novell, Inc.
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

#ifndef _owadapter_Converter_h
#define _owadapter_Converter_h

#include <openwbem/OW_config.h>
#include <openwbem/OW_CIMInstance.hpp>
#include <openwbem/OW_CIMObjectPath.hpp>
#include <openwbem/OW_CIMParamValue.hpp>
#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

namespace  Converter
{
    int to_openwbem_instance(
        const OpenWBEM::String& name_space,
        const cimple::Instance* cimple_instance,
        OpenWBEM::CIMInstance& ow_instance);

    int to_cimple_instance(
        const OpenWBEM::CIMInstance& ow_instance,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& cimple_instance);

    int to_cimple_key(
        const OpenWBEM::CIMObjectPath& bindings,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& cimple_key);

    int to_openwbem_object_path(
        const OpenWBEM::String& name_space,
        const cimple::Instance* cimple_key,
        OpenWBEM::CIMObjectPath& object_path);

    int de_nullify_properties(
        const OpenWBEM::StringArray* propertyList,
        cimple::Instance* cimple_instance);

    int to_openwbem_method(const OpenWBEM::CIMObjectPath& path, 
        const cimple::Instance* meth, 
        OpenWBEM::CIMParamValueArray& out, 
        OpenWBEM::CIMValue& return_value); 

    int to_cimple_method(const OpenWBEM::String& methodName, 
        const OpenWBEM::CIMParamValueArray& in, 
        const cimple::Meta_Class* mc, 
        cimple::Instance*& meth); 
}; 

CIMPLE_NAMESPACE_END

#endif /* _owadapter_Converter_h */
