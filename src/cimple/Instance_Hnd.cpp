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

#include "Instance_Hnd.h"

CIMPLE_NAMESPACE_BEGIN

Instance_Hnd::Instance_Hnd()
{
    _inst = create(&Instance::static_meta_class);
}

Instance_Hnd::Instance_Hnd(const Instance_Hnd& x)
{
    ref(_inst = x._inst);
}

Instance_Hnd::~Instance_Hnd()
{
    unref(_inst);
}

Instance_Hnd::Instance_Hnd(const Meta_Class* mc)
{
    _inst = cimple::create(mc, true);
}

Instance_Hnd::Instance_Hnd(const Meta_Class* mc, const Instance_Hnd& x)
{
    if (!is_subclass(mc, x._inst->meta_class))
    {
        _inst = 0;
        String to_class = mc->name;
        String from_class = x._inst->meta_class->name;

        to_class.append("_Hnd");
        from_class.append("_Hnd");

        throw Exception(
            Exception::BAD_CAST, "while casting from from %s to %s", 
            from_class.c_str(),
            to_class.c_str());
    }

    ref(_inst = x._inst);
}

Instance_Hnd& Instance_Hnd::operator=(const Instance_Hnd& x)
{
    if (x._inst != _inst)
    {
        unref(_inst);
        ref(_inst = x._inst);
    }
    return *this;
}

void Instance_Hnd::clear()
{
    cimple::clear(_inst);
}

Instance_Hnd::Instance_Hnd(Instance* inst) : _inst(inst)
{
}

void Instance_Hnd::_cow()
{
    if (_inst && Atomic_get(&_inst->__refs) != 1)
    {
        Instance* inst = clone(_inst);
        unref(_inst);
        _inst = inst;
    }
}

const String& Instance_Hnd::name_space() const
{
    return _inst->__name_space;
}

void Instance_Hnd::name_space(const String& name_space)
{
    _inst->__name_space = name_space;
}

void Instance_Hnd::print() const
{
    if (_inst)
        cimple::print(_inst);
}

Instance_Ref Instance_Hnd::reference() const
{
    return Instance_Ref(key_clone(_inst));
}

void Instance_Hnd::_get_inst_array(const void* x_, void* y_)
{
    const Array<Instance*>& x = *((const Array<Instance*>*)x_);
    Array<Instance_Hnd>& y = *((Array<Instance_Hnd>*)y_);

    y.clear();

    for (size_t i = 0; i < x.size(); i++)
    {
        ref(x[i]);
        y.append(Instance_Hnd(x[i]));
    }
}

void Instance_Hnd::_clear_inst_array(void* x_)
{
    Array<Instance*>& x = *((Array<Instance*>*)x_);

    for (size_t i = 0; i < x.size(); i++)
        unref(x[i]);

    x.clear();

    *((uint8*)(&x + 1)) = 0;
}

void Instance_Hnd::_set_inst_array(void* x_, const void* y_)
{
    Instance_Hnd::_clear_inst_array(x_);

    Array<Instance*>& x = *((Array<Instance*>*)x_);
    const Array<Instance_Hnd>& y = *((const Array<Instance_Hnd>*)y_);

    for (size_t i = 0; i < y.size(); i++)
    {
        Instance* tmp = (Instance*)y[i].instance();
        ref(tmp);
        x.append(tmp);
    }
}

void Instance_Hnd::_throw_null_access(const char* name) const
{
    throw Exception(Exception::NULL_ACCESS, "on feature %s_Hnd.%s",
        _inst->meta_class->name, name);
}

const char* Instance_Hnd::class_name() const
{
    return _inst->meta_class->name;
}

const Meta_Class* Instance_Hnd::meta_class() const
{
    return _inst->meta_class;
}

bool Instance_Hnd::is_a(const Instance_Hnd& x)
{
    // Anything is a subclass of Instance.
    return true;
}

void Instance_Hnd::name_space_recursive(const String& name_space)
{
    __set_name_space_recursive(_inst, name_space.c_str(), true);
}

CIMPLE_NAMESPACE_END
