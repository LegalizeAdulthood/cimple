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

/*   CMPI implementation of the cimple container class
     Provides CMPI implementation of the get and set functions for
     CMPI instance information and storage of CMPI operation specific
     information such as the CMPI_Broker reference for the operation
*/

#ifndef _pegadapter_CMPI_Containers_h
#define _pegadapter_CMPI_Containers_h

#include <cimple/Container.h>
#include "../adapter/cmpi.h"

CIMPLE_NAMESPACE_BEGIN

class CMPIInstance_Container : public Container
{
public:

    typedef CMPIInstance Rep;

    CMPIInstance_Container(
        const Meta_Repository* mr, 
        const CMPIBroker* cb, 
        const char* name_space,
        Rep* rep);

    virtual ~CMPIInstance_Container();
    virtual size_t get_size();
    virtual int get_name(size_t pos, String& name);
    virtual int get_value(size_t pos, Value::Type type, Value& value);
    virtual int set_value(const char* name, const Value& value, uint32 flags);

private:
    CMPIInstance_Container(const CMPIInstance_Container&);
    CMPIInstance_Container& operator=(const CMPIInstance_Container&);
    const CMPIBroker* _cb;
    const char* _ns;
    Rep* _rep;
};

class CMPIObjectPath_Container : public Container
{
public:

    typedef CMPIObjectPath Rep;

    CMPIObjectPath_Container(
        const Meta_Repository* mr, 
        const CMPIBroker* cb, 
        const char* name_space,
        Rep* rep);
    virtual ~CMPIObjectPath_Container();
    virtual size_t get_size();
    virtual int get_name(size_t pos, String& name);
    virtual int get_value(size_t pos, Value::Type type, Value& value);
    virtual int set_value(const char* name, const Value& value, uint32 flags);

private:
    CMPIObjectPath_Container(const CMPIObjectPath_Container&);
    CMPIObjectPath_Container& operator=(const CMPIObjectPath_Container&);
    const CMPIBroker* _cb;
    const char* _ns;
    Rep* _rep;
};

class CMPIArgs_Container : public Container
{
public:

    typedef CMPIArgs Rep;

    CMPIArgs_Container(
        const Meta_Repository* mr, 
        const CMPIBroker* cb, 
        const char* name_space,
        Rep* rep);
    virtual ~CMPIArgs_Container();
    virtual size_t get_size();
    virtual int get_name(size_t pos, String& name);
    virtual int get_value(size_t pos, Value::Type type, Value& value);
    virtual int set_value(const char* name, const Value& value, uint32 flags);

    CMPIData& return_value() { return _return_value; }

private:
    CMPIArgs_Container(const CMPIArgs_Container&);
    CMPIArgs_Container& operator=(const CMPIArgs_Container&);
    const CMPIBroker* _cb;
    const char* _ns;
    Rep* _rep;
    CMPIData _return_value;
};

CIMPLE_NAMESPACE_END

#endif /* _pegadapter_CMPI_Containers_h */
