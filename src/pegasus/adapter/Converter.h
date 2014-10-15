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

#ifndef _pegadapter_Converter_h
#define _pegadapter_Converter_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>
#include <Pegasus/Common/CIMObjectPath.h>
#include <Pegasus/Common/CIMParamValue.h>
#include <cimple/cimple.h>
#include "typedefs.h"

CIMPLE_NAMESPACE_BEGIN

typedef Pegasus::Array<P_CIMKeyBinding> Key_Bindings;

class Converter
{
public:

    static int to_pegasus_instance(
        const P_String& host_name,
        const P_CIMNamespaceName& name_space,
        const cimple::Instance* cimple_instance,
        P_CIMInstance& pegasus_instance);

    static int to_cimple_instance(
        const P_CIMInstance& pegasus_instance,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& cimple_instance);

    static int to_cimple_key(
        const Key_Bindings& bindings,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& cimple_key);

    static int to_pegasus_object_path(
        const P_String& host_name,
        const P_CIMNamespaceName& name_space,
        const cimple::Instance* cimple_key,
        P_CIMObjectPath& object_path);

    static int to_cimple_method(
        const char* meth_name,
        const Pegasus::Array<P_CIMParamValue>& in_params,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& meth);

    static int to_pegasus_method(
        const P_String& host_name,
        const P_CIMNamespaceName& name_space,
        const cimple::Instance* meth,
        Pegasus::Array<P_CIMParamValue>& out_params,
        P_CIMValue& return_value);

    static int de_nullify_properties(
        const P_CIMPropertyList& propertyList,
        cimple::Instance* cimple_instance);

    static int _to_cimple_ref(
        const P_CIMValue& v,
        cimple::Instance* ci,
        const cimple::Meta_Reference* mr);

    static int _append_cimple_ref(
        const P_CIMObjectPath& cop,
        cimple::Instance* ci,
        const cimple::Meta_Reference* mr);
};

CIMPLE_NAMESPACE_END

#endif /* _pegadapter_Converter_h */
