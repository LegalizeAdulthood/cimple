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

#ifndef _cimpl_PIP_h
#define _cimpl_PIP_h

#include <cimple/Provider.h>
#include <cimple/Instance_Map.h>

CIMPLE_NAMESPACE_BEGIN

class PIP_Base
{
public:

    PIP_Base(const Meta_Class* meta_class);

    ~PIP_Base();

    Unload_Status unload();

    Get_Instance_Status get_instance(Instance* instance);

    Enum_Instance_Status enum_instance(Instance* instance, uint64& state);

    Create_Instance_Status create_instance(const Instance* instance);

    Delete_Instance_Status delete_instance(const Instance* inst);

    Modify_Instance_Status modify_instance(const Instance* inst);

    size_t add_instance(Instance* inst);

private:

    const Meta_Class* _meta_class;
    Instance_Map_Base _map;
};

/** This class implements the 'Preloaded Instance Provider' pattern.
*/
template<class PROVIDER, class CLASS>
class PIP : public PIP_Base
{
public:

    PIP() : PIP_Base(&CLASS::static_meta_class) { }

    static Create_Provider_Status create_provider(PROVIDER** provider);

    static Destroy_Provider_Status destroy_provider(PROVIDER* provider);
};

template<class PROVIDER, class CLASS>
Create_Provider_Status PIP<PROVIDER,CLASS>::create_provider(
    PROVIDER** provider)
{
    *provider = new PROVIDER;
    return CREATE_PROVIDER_OK;
}

template<class PROVIDER, class CLASS>
Destroy_Provider_Status PIP<PROVIDER,CLASS>::destroy_provider(
    PROVIDER* provider)
{
    delete provider;
    return DESTROY_PROVIDER_OK;
}

CIMPLE_NAMESPACE_END

#endif /* _cimpl_PIP_h */
