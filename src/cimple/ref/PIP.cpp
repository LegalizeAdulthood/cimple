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

#include "PIP.h"

CIMPLE_NAMESPACE_BEGIN

PIP_Base::PIP_Base(const Meta_Class* meta_class) :
    _map(meta_class)
{
}

PIP_Base::~PIP_Base()
{
}

Unload_Status PIP_Base::unload()
{
    _map.clear();
    return UNLOAD_OK;
}

Get_Instance_Status PIP_Base::get_instance(
    Instance* inst)
{
    size_t pos = _map._find(inst);

    if (pos != size_t(-1))
    {
	Instance* person = _map._instances[pos];
	copy(inst, person);
	return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instance_Status PIP_Base::enum_instance(
    Instance* inst, uint64& state)
{
    if (state == _map._instances.size())
	return ENUM_INSTANCE_DONE;

    copy(inst, _map._instances[state]);

    state++;
    return ENUM_INSTANCE_MORE;
}

Create_Instance_Status PIP_Base::create_instance(
    const Instance* inst)
{
    if (_map._find(inst) != size_t(-1))
	return CREATE_INSTANCE_DUPLICATE;

    _map._insert(clone(inst));

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status PIP_Base::delete_instance(
    const Instance* inst)
{
    size_t pos = _map._find(inst);

    if (pos == size_t(-1))
	return DELETE_INSTANCE_NOT_FOUND;

    _map._remove(pos);

    return DELETE_INSTANCE_OK;
}

Modify_Instance_Status PIP_Base::modify_instance(
    const Instance* inst)
{
    size_t pos = _map._find(inst);

    if (pos == size_t(-1))
	return MODIFY_INSTANCE_NOT_FOUND;

    copy(_map._instances[pos], inst);

    return MODIFY_INSTANCE_OK;
}

size_t PIP_Base::add_instance(Instance* inst)
{
    return _map._insert(inst);
}

CIMPLE_NAMESPACE_END
