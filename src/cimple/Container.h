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

#ifndef _cimple_Container_h
#define _cimple_Container_h

#include "config.h"
#include "Type.h"
#include "Value.h"
#include "Meta_Repository.h"

CIMPLE_NAMESPACE_BEGIN

/** Virtual base class for container abstraction.
*/
class CIMPLE_CIMPLE_LINKAGE Container
{
public:

    Container(const Meta_Repository* mr);

    virtual ~Container();

    virtual size_t get_size() = 0;

    virtual int get_name(size_t pos, String& name) = 0;

    virtual int get_value(size_t pos, Value::Type type, Value& value) = 0;

    virtual int set_value(
        const char* name, const Value& value, uint32 flags) = 0;

    // Only features with the given flags are converted.
    Instance* convert(const Meta_Class* mc, uint32 flags);

    // Only features with the given flags are converted.
    int convert(const Instance* instance, uint32 flags);

private:
    Container(const Container&);
    Container& operator=(const Container&);

protected:
    const Meta_Repository* _mr;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Container_h */
