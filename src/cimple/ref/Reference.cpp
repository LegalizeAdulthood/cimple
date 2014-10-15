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

#include "Reference.h"

CIMPLE_NAMESPACE_BEGIN

Reference::Reference() : _inst(0)
{
}

Reference::Reference(const Reference& x)
{
    ref(_inst = x._inst);
}

Reference::~Reference()
{
    unref(_inst);
}

Reference& Reference::operator=(const Reference& x)
{
    if (x._inst != _inst)
    {
        unref(_inst);
        ref(_inst = x._inst);
    }
    return *this;
}

Reference::Reference(Instance* inst) : _inst(inst)
{
}

void Reference::_cow()
{
    if (_inst && Atomic_get(&_inst->__refs) != 1)
        _inst = clone(_inst);
}

void Reference::print() const
{
    if (_inst)
        cimple::print(_inst, true);
}

void Reference::_construct(
    Reference& to_handle,
    const Meta_Class& to_mc,
    const Reference& from_handle)
{
    if (!is_subclass(&to_mc, from_handle._inst->meta_class))
    {
        to_handle._inst = 0;
        String to_class = to_mc.name;
        String from_class = from_handle._inst->meta_class->name;

        to_class.append("_Reference");
        from_class.append("_Reference");

        throw Exception(
            Exception::BAD_CAST, "while casting from from %s to %s", 
            from_class.c_str(),
            to_class.c_str());
    }

    ref(to_handle._inst = from_handle._inst);
}

CIMPLE_NAMESPACE_END
