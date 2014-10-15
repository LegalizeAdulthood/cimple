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

#ifndef _brevity_Client_h
#define _brevity_Client_h

#include <cimple/cimple.h>
#include "linkage.h"
#include "Instance_Enum.h"
#include "Instance_Name_Enum.h"

CIMPLE_NAMESPACE_BEGIN

class  CIMPLE_BREVITY_LINKAGE Client : public Ops
{
public:

    Client();

    ~Client();

    /** Connect to CIM server at given URL using the given username and
        password.
    */
    void connect(
        const String& url,
        const String& username,
        const String& password);

    /** Return true if connected.
    */
    bool connected() const;

    /** Disconnect from the CIM server.
    */
    void disconnect();

    /** Create an instance. 
    */
    Instance_Ref create_instance(
        const String& name_space,
        const Instance_Hnd& new_instance);

    /** Modify an instance. 
    */
    void modify_instance(
        const String& name_space,
        const Instance_Hnd& modified_instance);

    /** Modify an instance. 
    */
    void modify_instance(
        const String& name_space,
        const Instance_Hnd& modified_instance,
        const Array<String>& property_list);

    /** Get an instance. 
    */
    Instance_Hnd get_instance(
        const String& name_space,
        const Instance_Ref& instance_name);

    /** Enumerate instances.
    */
    Instance_Enum enum_instances(
        const String& name_space,
        const Instance_Ref& class_name, 
        bool deep_inheritance = true);

    /** Enumerate instance names.
    */
    Instance_Name_Enum enum_instance_names(
        const String& name_space,
        const Instance_Ref& class_name);

    /** Delete instance.
    */
    void delete_instance(
        const String& name_space,
        const Instance_Ref& instance_name);

    /** Enumerate associators.
    */
    Instance_Enum associators(
        const String& name_space,
        const Instance_Ref& instance_name, 
        const String& assoc_class = String(),
        const String& result_class = String(),
        const String& role = String(),
        const String& result_role = String());

    /** Enumerate associator names.
    */
    Instance_Name_Enum associator_names(
        const String& name_space,
        const Instance_Ref& instance_name, 
        const String& assoc_class = String(),
        const String& result_class = String(),
        const String& role = String(),
        const String& result_role = String());

    /** Enumerate references.
    */
    Instance_Enum references(
        const String& name_space,
        const Instance_Ref& instance_name, 
        const String& result_class = String(),
        const String& role = String());

    /** Enumerate reference names.
    */
    Instance_Name_Enum reference_names(
        const String& ns,
        const Instance_Ref& in, 
        const String& result_class = String(),
        const String& role = String());

private:

    // ATTN: implement reference counting so these can be public:
    Client(const Client& x);
    Client& operator=(const Client& x);
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_Client_h */
