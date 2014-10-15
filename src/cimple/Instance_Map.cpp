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

#include "Instance_Map.h"
#include "Instance.h"

CIMPLE_NAMESPACE_BEGIN

Instance_Map_Base::Instance_Map_Base(const Meta_Class* meta_class)
    : _meta_class(meta_class)
{
}

Instance_Map_Base::~Instance_Map_Base()
{
    clear();
}

void Instance_Map_Base::clear()
{
    for (size_t i = 0; i < _instances.size(); i++)
	destroy(_instances[i]);

    _instances.clear();
}

size_t Instance_Map_Base::_insert(Instance* instance)
{
    if (_find(instance) != (size_t)-1)
	return (size_t)-1;

    size_t pos = _instances.size();
    _instances.append(instance);
    return pos;
}

size_t Instance_Map_Base::_find(const Instance* instance)
{
    for (size_t i = 0; i < _instances.size(); i++)
    {
	if (key_eq(_instances[i], instance))
	    return i;
    }

    return (size_t)-1;
}

Instance* Instance_Map_Base::_lookup(const Instance* instance)
{
    size_t pos = _find(instance);

    if (pos == (size_t)-1)
	return 0;

    return _instances[pos];
}

void Instance_Map_Base::_remove(size_t pos)
{
    if (pos < _instances.size())
	_instances.remove(pos);
}

CIMPLE_NAMESPACE_END
