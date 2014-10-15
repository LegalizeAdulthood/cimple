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

#include "Instance_Ref.h"

CIMPLE_NAMESPACE_BEGIN

Instance_Ref::Instance_Ref(const Instance_Ref& x)
{
    ref(_instance = x._instance);
}

Instance_Ref::~Instance_Ref()
{
    unref(_instance);
}

Instance_Ref& Instance_Ref::operator=(const Instance_Ref& x)
{
    if (_instance != x._instance)
    {
	unref(_instance);
	ref(_instance = x._instance);
    }
    return *this;
}

Instance_Ref Instance_Ref::clone() const
{
    return Instance_Ref(cimple::clone(_instance));
}

Instance_Ref::Instance_Ref(const Meta_Class* meta_class)
{
    // Called by the derived class's default constructor.
    _instance = create(meta_class);
}

Instance_Ref::Instance_Ref(Instance* instance)
{
    // Called by the derived class's copy constructor.
    ref(_instance = instance);
}

CIMPLE_NAMESPACE_END
