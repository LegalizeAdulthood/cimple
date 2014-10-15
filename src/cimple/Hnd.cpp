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

#include "Hnd.h"

CIMPLE_NAMESPACE_BEGIN

Hnd::Hnd() : _inst(0), _ref(false)
{
}

Hnd::Hnd(const Hnd& x)
{
    ref(_inst = x._inst);
}

Hnd::~Hnd()
{
    unref(_inst);
}

Hnd& Hnd::operator=(const Hnd& x)
{
    if (x._inst != _inst)
    {
        unref(_inst);
        ref(_inst = x._inst);
    }
    return *this;
}

Hnd::Hnd(Instance* inst, bool ref) : _inst(inst), _ref(ref)
{
}

void Hnd::_cow()
{
    if (_inst && Atomic_get(&_inst->__refs) != 1)
        _inst = clone(_inst);
}

void Hnd::print() const
{
    if (_inst)
        cimple::print(_inst, _ref);
}

CIMPLE_NAMESPACE_END
