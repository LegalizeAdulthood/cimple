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

#ifndef _cimple_Ops_h
#define _cimple_Ops_h

#include "config.h"
#include "linkage.h"
#include "Instance_Ref.h"
#include "Atomic_Counter.h"

CIMPLE_NAMESPACE_BEGIN

/** Base class for CIM operation implementers (e.g., CIM clients).
*/
class CIMPLE_CIMPLE_LINKAGE Ops
{
public:

    Ops();

    Ops(const Ops& x);

    Ops& operator=(const Ops& x);

    ~Ops();

protected:

    class Ops_Rep* _rep;

private:

    friend Ops_Rep* __rep(Ops& ops);
    friend const Ops_Rep* __rep(const Ops& ops);
};

CIMPLE_CIMPLE_LINKAGE
void __invoke(
    Ops& ops, 
    const String& ns,
    const Instance_Ref& ref, 
    const Meta_Method* mm, 
    ...);

inline Ops_Rep* __rep(Ops& ops)
{
    return ops._rep;
}

inline const Ops_Rep* __rep(const Ops& ops)
{
    return ops._rep;
}

/** Internal class.
*/
class CIMPLE_CIMPLE_LINKAGE Ops_Rep
{
public:

    Ops_Rep();

    virtual ~Ops_Rep();

    virtual void invoke(
        const String& name_space,
        const Instance_Ref& instance_name,
        Instance* meth) = 0;

    static void ref(const Ops_Rep* rep);

    static void unref(const Ops_Rep* rep);

    Atomic_Counter refs;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Ops_h */
