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

CIMPLE_NAMESPACE_BEGIN

struct Instance_Enum_Rep
{
public:

    Instance_Enum_Rep(const Array<Instance*>& x) 
        : instances(x), pos(0), refs(1)
    {
    }

    ~Instance_Enum_Rep()
    {
        for (size_t i = 0; i < instances.size(); i++)
            cimple::unref(instances[i]);
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

    Array<Instance*> instances;
    size_t pos;
    Atomic_Counter refs;

private:
    Instance_Enum_Rep() { }
    Instance_Enum_Rep(const Instance_Enum_Rep&) { }
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_Instance_Enum_Rep */
