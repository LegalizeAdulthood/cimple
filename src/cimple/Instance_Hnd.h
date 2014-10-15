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

#ifndef _cimple_Instance_Hnd_h
#define _cimple_Instance_Hnd_h

#include "config.h"
#include "Instance.h"
#include "Exception.h"
#include "Instance_Ref.h"

CIMPLE_NAMESPACE_BEGIN

/** Class Instance_Hnd.
*/
class CIMPLE_CIMPLE_LINKAGE Instance_Hnd
{
public:

    Instance_Hnd();

    Instance_Hnd(const Instance_Hnd& x);

    explicit Instance_Hnd(Instance* inst);

    ~Instance_Hnd();

    Instance_Hnd& operator=(const Instance_Hnd& x);

    void clear();

    const Instance* instance() const { return _inst; }

    Instance_Ref reference() const;

    const String& name_space() const;

    void name_space(const String& name_space);

    void name_space_recursive(const String& name_space);

    const char* class_name() const;

    const Meta_Class* meta_class() const;

    void print() const;

    static bool is_a(const Instance_Hnd& x);

protected:

    explicit Instance_Hnd(const Meta_Class* mc);

    explicit Instance_Hnd(const Meta_Class* mc, const Instance_Hnd& x);

    void _cow();

    void _throw_null_access(const char* name) const;

    static void _get_inst_array(const void* x, void* y);

    static bool _inst_array_null(const void* x);

    static void _clear_inst_array(void* x);

    static void _set_inst_array(void* x, const void* y);


    friend bool operator==(const Instance_Hnd& x, const Instance_Hnd& y);

    Instance* _inst;

private:
};

typedef Array<Instance_Hnd> Array_Instance_Hnd;

inline bool operator==(const Instance_Hnd& x, const Instance_Hnd& y)
{
    return identical(x._inst, y._inst);
}

inline void __clear(Instance_Hnd& x)
{
    x.clear();
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Instance_Hnd_h */
