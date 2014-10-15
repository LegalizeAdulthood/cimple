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

#ifndef _pegadapter_Converter_h
#define _pegadapter_Converter_h

#include <pegasus/utils/pegasus.h>
#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

typedef Pegasus::Array<Pegasus::CIMKeyBinding> Key_Bindings;

class Converter
{
public:

    //
    // Conversions to CIMPLE types.
    // 

    static int to_cimple_instance(
        const char* ns,
        const Pegasus::CIMInstance& pegasus_instance,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& cimple_instance);

    static int to_cimple_key(
        const char* ns,
        const Pegasus::CIMObjectPath& op,
        const cimple::Meta_Class* meta_class,
        cimple::Instance*& cimple_key);

    static int to_cimple_method(
        const char* ns,
        const Pegasus::Array<Pegasus::CIMParamValue>& params,
        const char* method_name,
        const cimple::Meta_Class* mc,
        uint32 flags, /* CIMPLE_FLAG_IN or CIMPLE_FLAG_OUT */
        cimple::Instance*& meth);

    //
    // Conversions to Pegasus types.
    // 

    static int to_pegasus_instance(
        const Pegasus::String& host_name,
        const Pegasus::CIMNamespaceName& name_space,
        const cimple::Instance* cimple_instance,
        Pegasus::CIMInstance& pegasus_instance);

    static int to_pegasus_assoc_instance(
        const Pegasus::String& host_name,
        const Pegasus::CIMNamespaceName& name_space,
        const cimple::Instance* cimple_instance,
        Pegasus::CIMInstance& pegasus_instance);

    static int to_pegasus_object_path(
        const Pegasus::String& host_name,
        const Pegasus::CIMNamespaceName& name_space,
        const cimple::Instance* cimple_key,
        Pegasus::CIMObjectPath& object_path);

    static int to_pegasus_assoc_object_path(
        const Pegasus::String& host_name,
        const Pegasus::CIMNamespaceName& name_space,
        const cimple::Instance* cimple_key,
        Pegasus::CIMObjectPath& object_path);

    static int to_pegasus_method(
        const Pegasus::String& host_name,
        const Pegasus::CIMNamespaceName& name_space,
        const cimple::Instance* meth,
        uint32 flags, /* CIMPLE_FLAG_IN or CIMPLE_FLAG_OUT */
        Pegasus::Array<Pegasus::CIMParamValue>& params,
        Pegasus::CIMValue& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _pegadapter_Converter_h */
