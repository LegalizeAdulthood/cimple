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

#ifndef _cimple_Instance_Map_h
#define _cimple_Instance_Map_h

#include "Meta_Class.h"
#include "Raw_Array.h"
#include "Provider.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LIBCIMPLE_LINKAGE Instance_Map_Base
{
public:

    Instance_Map_Base(const Meta_Class* meta_class);

    ~Instance_Map_Base();

    void clear();

protected:

    size_t _insert(Instance* instance);

    size_t _find(const Instance* instance);

    Instance* _lookup(const Instance* instance);

    void _remove(size_t pos);

    const Meta_Class* _meta_class;

    Raw_Array<Instance*> _instances;

    Get_Instance_Status _get_instance(
	const Instance* model, 
	Instance*& instance);

    Enum_Instances_Status _enum_instances(
	const Instance* model,
	Enum_Instances_Proc proc,
	void* client_data);

    Create_Instance_Status _create_instance(
	const Instance* instance);

    Delete_Instance_Status _delete_instance(
	const Instance* instance);

    Modify_Instance_Status _modify_instance(
	const Instance* instance);

    friend class Load_Provider_Base;
};

template<class CLASS>
class Instance_Map : public Instance_Map_Base
{
public:

    Instance_Map();

    ~Instance_Map();

    size_t insert(CLASS* instance);

    size_t find(const CLASS* instance);

    CLASS* lookup(const CLASS* instance);

    void remove(size_t pos);

    size_t size() const;

    CLASS* operator[](size_t pos);

    const CLASS* operator[](size_t pos) const;

    Get_Instance_Status get_instance(
	const CLASS* model, 
	CLASS*& instance);

    Enum_Instances_Status enum_instances(
	const CLASS* model,
	Enum_Instances_Handler<CLASS>* handler);

    Create_Instance_Status create_instance(
	const CLASS* instance);

    Delete_Instance_Status delete_instance(
	const CLASS* instance);

    Modify_Instance_Status modify_instance(
	const CLASS* instance);
};

template<class CLASS>
inline Instance_Map<CLASS>::Instance_Map() 
    : Instance_Map_Base(&CLASS::static_meta_class)
{
}

template<class CLASS>
inline Instance_Map<CLASS>::~Instance_Map()
{
}

template<class CLASS>
inline size_t Instance_Map<CLASS>::insert(CLASS* instance)
{
    return _insert(instance);
}

template<class CLASS>
inline size_t Instance_Map<CLASS>::find(const CLASS* instance)
{
    return _find(instance);
}

template<class CLASS>
inline CLASS* Instance_Map<CLASS>::lookup(const CLASS* instance)
{
    return (CLASS*)_lookup(instance);
}

template<class CLASS>
inline void Instance_Map<CLASS>::remove(size_t pos)
{
    _remove(pos);
}

template<class CLASS>
size_t Instance_Map<CLASS>::size() const
{
    return _instances.size();
}

template<class CLASS>
CLASS* Instance_Map<CLASS>::operator[](size_t pos)
{
    return (CLASS*)_instances[pos];
}

template<class CLASS>
const CLASS* Instance_Map<CLASS>::operator[](size_t pos) const
{
    return (CLASS*)_instances[pos];
}

template<class CLASS>
Get_Instance_Status Instance_Map<CLASS>::get_instance(
    const CLASS* model, 
    CLASS*& instance)
{
    return _get_instance((const Instance*)model, (Instance*&)instance);
}

template<class CLASS>
Enum_Instances_Status Instance_Map<CLASS>::enum_instances(
    const CLASS* model,
    Enum_Instances_Handler<CLASS>* handler)
{
    return _enum_instances(
	(const Instance*)model, handler->_proc, handler->_client_data);
}


template<class CLASS>
Create_Instance_Status Instance_Map<CLASS>::create_instance(
    const CLASS* instance)
{
    return _create_instance(instance);
}

template<class CLASS>
Delete_Instance_Status Instance_Map<CLASS>::delete_instance(
    const CLASS* instance)
{
    return _delete_instance(instance);
}

template<class CLASS>
Modify_Instance_Status Instance_Map<CLASS>::modify_instance(
    const CLASS* instance)
{
    return _modify_instance(instance);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Instance_Map<CLASS>_h */
