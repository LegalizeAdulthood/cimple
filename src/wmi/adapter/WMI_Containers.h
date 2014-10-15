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

#ifndef _WMI_Containers_h
#define _WMI_Containers_h

#include <cimple/Container.h>
#include <wbemprov.h>
#include <objbase.h>

CIMPLE_NAMESPACE_BEGIN

class WMI_Instance_Container : public Container
{
public:

    WMI_Instance_Container(
        const Meta_Repository* mr, 
        IWbemClassObject* instance);

    virtual ~WMI_Instance_Container();

    virtual size_t get_size();

    virtual int get_name(size_t pos, String& name);

    virtual int get_value(size_t pos, Value::Type type, Value& value);

    virtual int set_value(const char* name, const Value& value, uint32 flags);

private:

    IWbemClassObject* _instance;

    WMI_Instance_Container(const WMI_Instance_Container&);
    WMI_Instance_Container& operator=(const WMI_Instance_Container&);
};

#if 0
class WMI_ObjectPath_Container : public Container
{
public:

    WMI_ObjectPath_Container(
        const Meta_Repository* mr, 
        IWbemServices* name_space, 
        BSTR object_path);

    virtual ~WMI_ObjectPath_Container();

    virtual size_t get_size();

    virtual int get_name(size_t pos, String& name);

    virtual int get_value(size_t pos, Value::Type type, Value& value);

    virtual int set_value(const char* name, const Value& value, uint32 flags);

private:
    WMI_ObjectPath_Container(const WMI_ObjectPath_Container&);
    WMI_ObjectPath_Container& operator=(const WMI_ObjectPath_Container&);
};
#endif

class WMI_Args_Container : public Container
{
public:

    WMI_Args_Container(
        const Meta_Repository* mr, 
        IWbemClassObject* _instance);

    virtual ~WMI_Args_Container();

    virtual size_t get_size();

    virtual int get_name(size_t pos, String& name);

    virtual int get_value(size_t pos, Value::Type type, Value& value);

    virtual int set_value(const char* name, const Value& value, uint32 flags);

private:

    IWbemClassObject* _instance;

    WMI_Args_Container(const WMI_Args_Container&);
    WMI_Args_Container& operator=(const WMI_Args_Container&);
};

CIMPLE_NAMESPACE_END

#endif /* _WMI_Containers_h */
