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

#include "Variant.h"
#include <cimple/config.h>
#include <cimple/integer.h>
#include "WMI_Containers.h"
#include "SafeArr.h"
#include "BString.h"
#include "log.h"
#include "utils.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local routines:
//
//==============================================================================

static size_t _get_size(IWbemClassObject* _instance)
{
    if (!_instance)
        return 0;

    _instance->BeginEnumeration(WBEM_FLAG_NONSYSTEM_ONLY);

    size_t size = 0;


    while(_instance->Next(0, NULL, NULL, NULL, NULL) == WBEM_S_NO_ERROR) 
        size++;

    _instance->EndEnumeration();

    return size;
}

static int _get_name(
    IWbemClassObject* _instance, 
    size_t pos, 
    String& name_out)
{
    BSTR name = 0;

    if (!_instance)
        return -1;

    _instance->BeginEnumeration(WBEM_FLAG_NONSYSTEM_ONLY);

    size_t index = 0;

    while(_instance->Next(0, &name, NULL, NULL, NULL) == WBEM_S_NO_ERROR) 
    {
        BString name_(name, BSTR_TAG);

        if (index == pos)
        {
            name_out.assign(bstr2str(name));
            _instance->EndEnumeration();
            return 0;
        }

        index++;
    }

    _instance->EndEnumeration();

    // Not found!
    return -1;
}

static int _get_value(
    const Meta_Repository* _mr,
    IWbemClassObject* _instance,
    size_t pos, 
    Value::Type type, 
    Value& value)
{
    VARIANT var;
    CIMTYPE ct;

    if (!_instance)
        return -1;

    VariantInit(&var);

    _instance->BeginEnumeration(WBEM_FLAG_NONSYSTEM_ONLY);

    size_t index = 0;

    while(_instance->Next(0, NULL, &var, &ct, NULL) == WBEM_S_NO_ERROR) 
    {
        if (index == pos)
        {
            Variant tvar(var);

            VariantClear(&var);
            _instance->EndEnumeration();

            return tvar.to_value(ct, value, _mr);
        }

        VariantClear(&var);
        index++;
    }

    _instance->EndEnumeration();

    // Not found!
    return -1;
}

static int _set_value(
    const Meta_Repository* _mr,
    IWbemClassObject* _instance,
    const char* name, 
    const Value& value, 
    uint32 flags)
{
    Variant v;

    if (v.set_value(value) != 0)
        return -1;

    BString nm;

    if ((flags & CIMPLE_FLAG_OUT) && strcmp(name, "return_value") == 0)
    {
        nm.set("ReturnValue");
    }
    else
    {
        nm.set(name);
    }

    SCODE sc = _instance->Put(nm.rep(), 0, (VARIANT*)&v.rep(), 0);

    if (FAILED(sc))
        return -1;

    return 0;
}

//==============================================================================
//
// CMPIInstance_Container
//
//==============================================================================

WMI_Instance_Container::WMI_Instance_Container(
    const Meta_Repository* mr, 
    IWbemClassObject* instance) : Container(mr), _instance(instance)
{
}

WMI_Instance_Container::~WMI_Instance_Container()
{
}

size_t WMI_Instance_Container::get_size()
{
    return _get_size(_instance);
}

int WMI_Instance_Container::get_name(
    size_t pos, 
    String& name_out)
{
    return _get_name(_instance, pos, name_out);
}

int WMI_Instance_Container::get_value(
    size_t pos, 
    Value::Type type, 
    Value& value)
{
    return _get_value(_mr, _instance, pos, type, value);
}

int WMI_Instance_Container::set_value(
    const char* name, 
    const Value& value, 
    uint32 flags)
{
    return _set_value(_mr, _instance, name, value, flags);
}

//==============================================================================
//
// CMPIObjectPath_Container
//
//==============================================================================



//==============================================================================
//
// CMPIArgs_Container
//
//==============================================================================

WMI_Args_Container::WMI_Args_Container(
    const Meta_Repository* mr, 
    IWbemClassObject* instance) : Container(mr), _instance(instance)
{
}

WMI_Args_Container::~WMI_Args_Container()
{
}

size_t WMI_Args_Container::get_size()
{
    return _get_size(_instance);
}

int WMI_Args_Container::get_name(
    size_t pos, 
    String& name_out)
{
    return _get_name(_instance, pos, name_out);
}

int WMI_Args_Container::get_value(
    size_t pos, 
    Value::Type type, 
    Value& value)
{
    return _get_value(_mr, _instance, pos, type, value);
}

int WMI_Args_Container::set_value(
    const char* name, 
    const Value& value, 
    uint32 flags)
{
    return _set_value(_mr, _instance, name, value, flags);
}

CIMPLE_NAMESPACE_END
