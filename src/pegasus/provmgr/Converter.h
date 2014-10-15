/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#ifndef _provmgr_Converter_h
#define _provmgr_Converter_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>
#include <Pegasus/Common/CIMObjectPath.h>
#include <Pegasus/Common/CIMParamValue.h>
#include <cimple/cimple.h>

PEGASUS_NAMESPACE_BEGIN

typedef Array<CIMKeyBinding> Key_Bindings;

class Converter
{
public:

    CIMPLE_HIDE static int to_pegasus_instance(
	const String& host_name,
	const CIMNamespaceName& name_space,
	const cimple::Instance* cimple_instance,
	CIMInstance& pegasus_instance);

    CIMPLE_HIDE static int to_cimple_instance(
	const CIMInstance& pegasus_instance,
	const cimple::Meta_Class* meta_class,
	cimple::Instance*& cimple_instance);

    CIMPLE_HIDE static int to_cimple_key(
	const Key_Bindings& bindings,
	const cimple::Meta_Class* meta_class,
	cimple::Instance*& cimple_key);

    CIMPLE_HIDE static int to_pegasus_object_path(
	const String& host_name,
	const CIMNamespaceName& name_space,
	const cimple::Instance* cimple_key,
	CIMObjectPath& object_path);

    CIMPLE_HIDE static int to_cimple_method(
	const char* meth_name,
	const Array<CIMParamValue>& in_params,
	const cimple::Meta_Class* meta_class,
	cimple::Instance*& meth);

    CIMPLE_HIDE static int to_pegasus_method(
	const String& host_name,
	const CIMNamespaceName& name_space,
	const cimple::Instance* meth,
	Array<CIMParamValue>& out_params,
	CIMValue& return_value);

    CIMPLE_HIDE static int de_nullify_properties(
	const CIMPropertyList& propertyList,
	cimple::Instance* cimple_instance);

    CIMPLE_HIDE static int _to_cimple_ref(
	const CIMValue& v,
	cimple::Instance* ci,
	const cimple::Meta_Reference* mr);
};

PEGASUS_NAMESPACE_END

#endif /* _provmgr_Converter_h */
