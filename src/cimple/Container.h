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

/*
    Define a virtual base class for containers. The containers provide a 
    common abstraction for the conversion of instances between CIMPLE and
    the adapter instance formats.  
    Each adapter must implement the following functions:
    get_size() - Number of features in the adapter instance
    get_value() - Get the value of a particular feature from the adapter
        instance
    get_name() - get the Name of the feature
    set_Value - set the value into the adapter instance.  Ex. create the
    property with this value or modify an existing property.
*/
#ifndef _cimple_Container_h
#define _cimple_Container_h

#include "config.h"
#include "Type.h"
#include "Value.h"
#include "Meta_Repository.h"

CIMPLE_NAMESPACE_BEGIN

/** Virtual base class for container abstraction. The container
 *  abstraction provides a common based for the feature
 *  converters for each adapter.  The common code in this class
 *  provides the instance conversion main loop and each adapter
 *  provides the specific information interface get and setting
 *  data to specific features.
*/
class CIMPLE_CIMPLE_LINKAGE Container
{
public:

    Container(const Meta_Repository* mr);

    virtual ~Container();

    virtual size_t get_size() = 0;

    virtual int get_name(size_t pos, String& name) = 0;

    virtual int get_value(size_t pos, Value::Type type, Value& value) = 0;

    /* Set the defined feature including its value into the instance
       defined by the container.
       @paramname char* name of the feature (reference or property)
       @param value Value& reference to the value to be set into the feature
       @ Flags defining feature types to be set
       @return int with 0 value if successful.  Non-zero if not successful
    */
    virtual int set_value(
        const char* name, const Value& value, uint32 flags) = 0;

    // Convert an adapter instance to a CIMPLE instance. Only features
    // with the given flags are converted. Creates a new CIMPLE instance from
    // mc if instance does not exist.  Uses the adapter get_value(), get_size()
    // and get)name() functions get features from the adapter instance. Only
    // property and reference features are converted.
    int convert(const Meta_Class* mc, uint32 flags, Instance*& instance);

    // Convert a CIMPLE instance to the instance type defined by the
    // adapter. Only features with the given flags are converted.
    int convert(const Instance* instance, uint32 flags);

private:
    Container(const Container&);
    Container& operator=(const Container&);

protected:
    const Meta_Repository* _mr;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Container_h */
