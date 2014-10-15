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

#ifndef _cimple_cimom_h
#define _cimple_cimom_h

#include "config.h"
#include "Instance.h"
#include "Ref.h"

CIMPLE_NAMESPACE_BEGIN

struct Instance_Enumerator_Rep;

//==============================================================================
//
// Instance_Enumerator
//
//==============================================================================

class CIMPLE_CIMPLE_LINKAGE Instance_Enumerator
{
public:

    Instance_Enumerator();

    ~Instance_Enumerator();

    operator bool() const;

    void operator++(int);

    Ref<Instance> operator()() const;

private:
    Instance_Enumerator(const Instance_Enumerator&);
    Instance_Enumerator& operator=(const Instance_Enumerator&);
    void operator++();
    Instance_Enumerator_Rep* _rep;
    friend struct cimom;
};

//==============================================================================
//
// cimom
//
//==============================================================================

struct CIMPLE_CIMPLE_LINKAGE cimom
{
public:

    static int enum_instances(
        const char* name_space, 
        const Instance* model,
        Instance_Enumerator& enumerator);

    static Ref<Instance> get_instance(
        const char* name_space, 
        const Instance* model);

    static int create_instance(
        const char* name_space, 
        const Instance* instance);

    static int delete_instance(
        const char* name_space, 
        const Instance* instance);

    static int modify_instance(
        const char* name_space, 
        const Instance* instance);

    static void allow_unload(bool flag);
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_cimom_h */
