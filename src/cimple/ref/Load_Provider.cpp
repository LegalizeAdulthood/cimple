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

#include "Load_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Load_Provider_Base::Load_Provider_Base(const Meta_Class* meta_class) :
    _map(meta_class)
{
}

Load_Provider_Base::~Load_Provider_Base()
{
}

Unload_Status Load_Provider_Base::unload()
{
    _map.clear();
    return UNLOAD_OK;
}

Get_Instance_Status Load_Provider_Base::get_instance(
    const Instance* model,
    Instance*& instance)
{
    size_t pos = _map._find(instance);

    if (pos != size_t(-1))
    {
        instance = clone(_map._instances[pos]);
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Load_Provider_Base::_enum_instances(
    const Instance* inst, 
    Enum_Instances_Handler_Base* handler)
{
    for (size_t i = 0; i < _map._instances.size(); i++)
        handler->_proc(_map._instances[i], handler->_client_data);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Load_Provider_Base::create_instance(
    const Instance* inst)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Load_Provider_Base::delete_instance(
    const Instance* inst)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Load_Provider_Base::modify_instance(
    const Instance* inst)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

size_t Load_Provider_Base::add_instance(Instance* inst)
{
    return _map._insert(inst);
}

CIMPLE_NAMESPACE_END
