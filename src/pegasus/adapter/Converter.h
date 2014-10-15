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

#ifndef _provmgr_Converter_h
#define _provmgr_Converter_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>
#include <Pegasus/Common/CIMObjectPath.h>
#include <Pegasus/Common/CIMParamValue.h>
#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

typedef Pegasus::Array<Pegasus::CIMKeyBinding> Key_Bindings;

class Converter
{
public:

    static CIMPLE_HIDE int to_pegasus_instance(
	const Pegasus::String& host_name,
	const Pegasus::CIMNamespaceName& name_space,
	const cimple::Instance* cimple_instance,
	Pegasus::CIMInstance& pegasus_instance);

    static CIMPLE_HIDE int to_cimple_instance(
	const Pegasus::CIMInstance& pegasus_instance,
	const cimple::Meta_Class* meta_class,
	cimple::Instance*& cimple_instance);

    static CIMPLE_HIDE int to_cimple_key(
	const Key_Bindings& bindings,
	const cimple::Meta_Class* meta_class,
	cimple::Instance*& cimple_key);

    static CIMPLE_HIDE int to_pegasus_object_path(
	const Pegasus::String& host_name,
	const Pegasus::CIMNamespaceName& name_space,
	const cimple::Instance* cimple_key,
	Pegasus::CIMObjectPath& object_path);

    static CIMPLE_HIDE int to_cimple_method(
	const char* meth_name,
	const Pegasus::Array<Pegasus::CIMParamValue>& in_params,
	const cimple::Meta_Class* meta_class,
	cimple::Instance*& meth);

    static CIMPLE_HIDE int to_pegasus_method(
	const Pegasus::String& host_name,
	const Pegasus::CIMNamespaceName& name_space,
	const cimple::Instance* meth,
	Pegasus::Array<Pegasus::CIMParamValue>& out_params,
	Pegasus::CIMValue& return_value);

    static CIMPLE_HIDE int de_nullify_properties(
	const Pegasus::CIMPropertyList& propertyList,
	cimple::Instance* cimple_instance);

    static CIMPLE_HIDE int _to_cimple_ref(
	const Pegasus::CIMValue& v,
	cimple::Instance* ci,
	const cimple::Meta_Reference* mr);
};

CIMPLE_NAMESPACE_END

#endif /* _provmgr_Converter_h */
