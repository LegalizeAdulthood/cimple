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

#ifndef _brevity_Instance_Enum_h
#define _brevity_Instance_Enum_h

#include <cimple/cimple.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_BREVITY_LINKAGE Instance_Enum
{
public:

    Instance_Enum();

    Instance_Enum(const Instance_Enum& x);

    ~Instance_Enum();

    Instance_Enum& operator=(const Instance_Enum& x);

    bool more() const;

    Instance_Hnd next();

private:

    Instance_Enum(struct Instance_Enum_Rep* rep);

    struct Instance_Enum_Rep* _rep;

    friend class Client;
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_Instance_Enum_h */
