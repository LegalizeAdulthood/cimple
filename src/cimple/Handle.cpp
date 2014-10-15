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

#include "Handle.h"

CIMPLE_NAMESPACE_BEGIN

Handle::Handle() : _inst(0)
{
}

Handle::Handle(const Handle& x)
{
    ref(_inst = x._inst);
}

Handle::~Handle()
{
    unref(_inst);
}

Handle& Handle::operator=(const Handle& x)
{
    if (x._inst != _inst)
    {
        unref(_inst);
        ref(_inst = x._inst);
    }
    return *this;
}

Handle::Handle(Instance* inst) : _inst(inst)
{
}

void Handle::_cow()
{
    if (_inst && Atomic_get(&_inst->__refs) != 1)
        _inst = clone(_inst);
}

void Handle::print() const
{
    if (_inst)
        cimple::print(_inst);
}

void Handle::_construct(
    Handle& to_handle,
    const Meta_Class& to_mc,
    const Handle& from_handle)
{
    if (!is_subclass(&to_mc, from_handle._inst->meta_class))
    {
        to_handle._inst = 0;
        String to_class = to_mc.name;
        String from_class = from_handle._inst->meta_class->name;

        to_class.append("_Handle");
        from_class.append("_Handle");

        throw Exception(
            Exception::BAD_CAST, "while casting from from %s to %s", 
            from_class.c_str(),
            to_class.c_str());
    }

    ref(to_handle._inst = from_handle._inst);
}

CIMPLE_NAMESPACE_END
