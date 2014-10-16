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

#ifndef _brevity_Instance_Enum_Rep
#define _brevity_Instance_Enum_Rep

#include <cimple/cimple.h>
#include <pegasus/utils/Containers.h>
#include <pegasus/utils/Converter.h>
#include <pegasus/utils/Str.h>

CIMPLE_NAMESPACE_BEGIN

struct Instance_Enum_Rep
{
public:

    Instance_Enum_Rep(
        const Meta_Class* mc_,
        const Pegasus::Array<Pegasus::CIMInstance>& instances_) :
        mc(mc_), instances(instances_), pos(0)
    {
    }

    static void ref(const Instance_Enum_Rep* rep_)
    {
        Instance_Enum_Rep* rep = (Instance_Enum_Rep*)rep_;

        if (rep)
            rep->refs.inc();
    }

    static void unref(const Instance_Enum_Rep* rep_)
    {
        Instance_Enum_Rep* rep = (Instance_Enum_Rep*)rep_;

        if (rep && rep->refs.dec_and_test())
            delete rep;
    }

    const Meta_Class* mc;
    Pegasus::Array<Pegasus::CIMInstance> instances;
    size_t pos;
    Atomic_Counter refs;
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_Instance_Enum_Rep */
