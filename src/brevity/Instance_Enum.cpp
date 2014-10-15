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

#include "Instance_Enum.h"
#include "Instance_Enum_Rep.h"

CIMPLE_NAMESPACE_BEGIN

Instance_Enum::Instance_Enum() : _rep(0)
{
}

Instance_Enum::Instance_Enum(const Instance_Enum& x)
{
    Instance_Enum_Rep::ref(_rep = x._rep);
}

Instance_Enum::~Instance_Enum()
{
    Instance_Enum_Rep::unref(_rep);
}

bool Instance_Enum::more() const
{
    if (!_rep)
        throw Exception(Exception::BAD_ENUMERATOR);

    return _rep->pos != _rep->instances.size();
}

Instance_Hnd Instance_Enum::next()
{
    if (!_rep)
        throw Exception(Exception::BAD_ENUMERATOR);

    if (_rep->pos == _rep->instances.size())
        throw Exception(Exception::BAD_ENUMERATOR);

    const Pegasus::CIMInstance& ci = _rep->instances[_rep->pos];

    const Meta_Class* mc = find_meta_class(_rep->mc, *Str(ci.getClassName()));

    if (!mc)
        mc = _rep->mc;

    Instance* inst = 0;
    Str ns(ci.getPath().getNameSpace());

    if (Converter::to_cimple_instance(*ns, ci, mc, inst) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION, 
            "cannot convert Pegasus instance to CIMPLE instance: %s",
            mc->name);
    }

    _rep->pos++;
    return Instance_Hnd(inst);
}

Instance_Enum& Instance_Enum::operator=(const Instance_Enum& x)
{
    if (_rep != x._rep)
    {
        Instance_Enum_Rep::unref(_rep);
        Instance_Enum_Rep::ref(_rep = x._rep);
    }

    return *this;
}

Instance_Enum::Instance_Enum(struct Instance_Enum_Rep* rep) : _rep(rep) 
{
}

CIMPLE_NAMESPACE_END
