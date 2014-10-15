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
** THE SOFTWARE IS PROVIDER "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#ifndef _cimpl_Load_Provider_h
#define _cimpl_Load_Provider_h

#include <cimple/Provider.h>
#include <cimple/Instance_Map.h>

CIMPLE_NAMESPACE_BEGIN

/** Base class for Load_Provider (more at Load_Provider).
*/
class Load_Provider_Base
{
public:

    Load_Provider_Base(const Meta_Class* meta_class);

    ~Load_Provider_Base();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Instance* model,
        Instance*& instance);

    Enum_Instances_Status _enum_instances(
        const Instance* instance,
        Enum_Instances_Handler_Base* handler);

    Create_Instance_Status create_instance(const Instance* instance);

    Delete_Instance_Status delete_instance(const Instance* inst);

    Modify_Instance_Status modify_instance(const Instance* inst);

    size_t add_instance(Instance* inst);

private:

    const Meta_Class* _meta_class;
    Instance_Map_Base _map;
};

/** This class implements the 'Load Provider' pattern. A load provider only
    needs to implement the load() operation. All of the other operations are 
    implemented by this base class. This class helps develop a read-only
    provider.
*/
template<class PROVIDER, class CLASS>
class Load_Provider : public Load_Provider_Base
{
public:

    typedef CLASS Class;

    Load_Provider() : Load_Provider_Base(
        &PROVIDER::Class::static_meta_class) { }

    Enum_Instances_Status enum_instances(
        const Instance* instance,
        Enum_Instances_Handler<CLASS>* handler);

    static Create_Provider_Status create_provider(PROVIDER** provider);

    static Destroy_Provider_Status destroy_provider(PROVIDER* provider);

    static int proc(
        int operation, void* arg0, void* arg1, void* arg2, void* arg3);
};

template<class PROVIDER, class CLASS>
Create_Provider_Status 
    Load_Provider<PROVIDER, CLASS>::create_provider(
    PROVIDER** provider)
{
    *provider = new PROVIDER;
    return CREATE_PROVIDER_OK;
}

template<class PROVIDER, class CLASS>
Destroy_Provider_Status 
    Load_Provider<PROVIDER, CLASS>::destroy_provider(
    PROVIDER* provider)
{
    delete provider;
    return DESTROY_PROVIDER_OK;
}

template<class PROVIDER, class CLASS>
inline int Load_Provider<PROVIDER, CLASS>::proc(
    int operation, void* arg0, void* arg1, void* arg2, void* arg3)
{
    return Provider_Proc_T<PROVIDER>::proc(operation, arg0, arg1, arg2, arg3);
}

CIMPLE_NAMESPACE_END

#endif /* _cimpl_Load_Provider_h */
