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

#include "Instance_Name_Enum.h"
#include "Instance_Name_Enum_Rep.h"

CIMPLE_NAMESPACE_BEGIN

Instance_Name_Enum::Instance_Name_Enum() : _rep(0)
{
}

Instance_Name_Enum::Instance_Name_Enum(const Instance_Name_Enum& x)
{
    Instance_Name_Enum_Rep::ref(_rep = x._rep);
}

Instance_Name_Enum::~Instance_Name_Enum()
{
    Instance_Name_Enum_Rep::unref(_rep);
}

bool Instance_Name_Enum::more() const
{
    if (!_rep)
        throw Exception(Exception::BAD_ENUMERATOR);

    return _rep->pos != _rep->paths.size();
}

Instance_Ref Instance_Name_Enum::next()
{
    if (!_rep)
        throw Exception(Exception::BAD_ENUMERATOR);

    if (_rep->pos == _rep->paths.size())
        throw Exception(Exception::BAD_ENUMERATOR);

    const Pegasus::CIMObjectPath& cop = _rep->paths[_rep->pos];

    const Meta_Class* mc = find_meta_class(_rep->mc, *Str(cop.getClassName()));

    if (!mc)
        mc = _rep->mc;

    Instance* inst = 0;

    Str ns(cop.getNameSpace());

    if (Converter::to_cimple_key(ns, cop, mc, inst) != 0)
    {
        throw Exception(Exception::BAD_CONVERSION, 
            "cannot convert Pegasus instance to CIMPLE reference: %s",
            mc->name);
    }

    _rep->pos++;
    return Instance_Ref(inst);
}

Instance_Name_Enum& Instance_Name_Enum::operator=(const Instance_Name_Enum& x)
{
    if (_rep != x._rep)
    {
        Instance_Name_Enum_Rep::unref(_rep);
        Instance_Name_Enum_Rep::ref(_rep = x._rep);
    }

    return *this;
}

Instance_Name_Enum::Instance_Name_Enum(struct Instance_Name_Enum_Rep* rep) : 
    _rep(rep) 
{
}

CIMPLE_NAMESPACE_END
