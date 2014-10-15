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

#ifndef _pegadapter_Containers_h
#define _pegadapter_Containers_h

#include <cimple/Container.h>
#include "pegasus.h"

CIMPLE_NAMESPACE_BEGIN

class InstanceContainer : public Container
{
public:

    typedef Pegasus::CIMInstance Rep;

    InstanceContainer(
        const Meta_Repository* mr, const char* ns, const Rep& rep);
    virtual ~InstanceContainer();
    virtual size_t get_size();
    virtual int get_name(size_t pos, String& name);
    virtual int get_value(size_t pos, Value::Type type, Value& value);
    virtual int set_value(const char* name, const Value& value, uint32 flags);

    const Rep& rep() const { return _rep; }

private:
    InstanceContainer(const InstanceContainer&);
    InstanceContainer& operator=(const InstanceContainer&);
    const char* _ns;
    Rep _rep;
};

class ObjectPathContainer : public Container
{
public:

    typedef Pegasus::CIMObjectPath Rep;

    ObjectPathContainer(
        const Meta_Repository* mr, const char* ns, const Rep& rep);

    virtual ~ObjectPathContainer();

    virtual size_t get_size();
    virtual int get_name(size_t pos, String& name);
    virtual int get_value(size_t pos, Value::Type type, Value& value);
    virtual int set_value(const char* name, const Value& value, uint32 flags);

    const Rep& rep() const { return _rep; }

private:
    ObjectPathContainer(const ObjectPathContainer&);
    ObjectPathContainer& operator=(const ObjectPathContainer&);
    const char* _ns;
    Rep _rep;
};

class ParamValueContainer : public Container
{
public:

    typedef Pegasus::Array<Pegasus::CIMParamValue> Rep;

    ParamValueContainer(
        const Meta_Repository* mr, const char* ns, const Rep& rep);

    virtual ~ParamValueContainer();

    virtual size_t get_size();
    virtual int get_name(size_t pos, String& name);
    virtual int get_value(size_t pos, Value::Type type, Value& value);
    virtual int set_value(const char* name, const Value& value, uint32 flags);

    const Rep& rep() const { return _rep; }

    Pegasus::CIMValue& return_value() { return _return_value; }

private:
    ParamValueContainer(const ParamValueContainer&);
    ParamValueContainer& operator=(const ParamValueContainer&);
    const char* _ns;
    Rep _rep;
    Pegasus::CIMValue _return_value;
};

CIMPLE_NAMESPACE_END

#endif /* _pegadapter_Containers_h */
