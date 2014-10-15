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

#ifndef _cimple_Reference_Facade_h
#define _cimple_Reference_Facade_h

#include <cstdio>
#include "config.h"
#include "Type.h"
#include "Exception.h"

CIMPLE_NAMESPACE_BEGIN

class Reference_Facade
{
public:

    Reference_Facade();

    virtual ~Reference_Facade();

    virtual void host_name(const String& host_name) = 0;

    virtual String host_name() const = 0;

    virtual void name_space(const String& name_space) = 0;

    virtual String name_space() const = 0;

    virtual void class_name(const String& class_name) = 0;

    virtual String class_name() const = 0;

    virtual size_t count() const = 0;

    virtual size_t find(const String& name) const = 0;

    virtual String get_name(size_t pos) const = 0;

    virtual bool is_reference(size_t pos) const = 0;

    virtual Type get_type(size_t pos) const = 0;

    // null:

    virtual void set_null(const String& name, Type type) = 0;
    virtual void set_null(size_t pos, bool null) = 0;
    virtual bool get_null(const String& name) const = 0;
    virtual bool get_null(size_t pos) const = 0;

    // boolean:

    virtual void set_boolean(const String& name, const boolean& x) = 0;
    virtual void set_boolean(size_t pos, const boolean& x) = 0;
    virtual boolean get_boolean(const String& name) const = 0;
    virtual boolean get_boolean(size_t pos) const = 0;

    // uint8:

    virtual void set_uint8(const String& name, const uint8& x) = 0;
    virtual void set_uint8(size_t pos, const uint8& x) = 0;
    virtual uint8 get_uint8(const String& name) const = 0;
    virtual uint8 get_uint8(size_t pos) const = 0;

    // sint8:

    virtual void set_sint8(const String& name, const sint8& x) = 0;
    virtual void set_sint8(size_t pos, const sint8& x) = 0;
    virtual sint8 get_sint8(const String& name) const = 0;
    virtual sint8 get_sint8(size_t pos) const = 0;

    // uint16:

    virtual void set_uint16(const String& name, const uint16& x) = 0;
    virtual void set_uint16(size_t pos, const uint16& x) = 0;
    virtual uint16 get_uint16(const String& name) const = 0;
    virtual uint16 get_uint16(size_t pos) const = 0;

    // sint16:

    virtual void set_sint16(const String& name, const sint16& x) = 0;
    virtual void set_sint16(size_t pos, const sint16& x) = 0;
    virtual sint16 get_sint16(const String& name) const = 0;
    virtual sint16 get_sint16(size_t pos) const = 0;

    // uint32:

    virtual void set_uint32(const String& name, const uint32& x) = 0;
    virtual void set_uint32(size_t pos, const uint32& x) = 0;
    virtual uint32 get_uint32(const String& name) const = 0;
    virtual uint32 get_uint32(size_t pos) const = 0;

    // sint32:

    virtual void set_sint32(const String& name, const sint32& x) = 0;
    virtual void set_sint32(size_t pos, const sint32& x) = 0;
    virtual sint32 get_sint32(const String& name) const = 0;
    virtual sint32 get_sint32(size_t pos) const = 0;

    // uint64:

    virtual void set_uint64(const String& name, const uint64& x) = 0;
    virtual void set_uint64(size_t pos, const uint64& x) = 0;
    virtual uint64 get_uint64(const String& name) const = 0;
    virtual uint64 get_uint64(size_t pos) const = 0;

    // sint64:

    virtual void set_sint64(const String& name, const sint64& x) = 0;
    virtual void set_sint64(size_t pos, const sint64& x) = 0;
    virtual sint64 get_sint64(const String& name) const = 0;
    virtual sint64 get_sint64(size_t pos) const = 0;

    // real32:

    virtual void set_real32(const String& name, const real32& x) = 0;
    virtual void set_real32(size_t pos, const real32& x) = 0;
    virtual real32 get_real32(const String& name) const = 0;
    virtual real32 get_real32(size_t pos) const = 0;

    // real64:

    virtual void set_real64(const String& name, const real64& x) = 0;
    virtual void set_real64(size_t pos, const real64& x) = 0;
    virtual real64 get_real64(const String& name) const = 0;
    virtual real64 get_real64(size_t pos) const = 0;

    // char16:

    virtual void set_char16(const String& name, const char16& x) = 0;
    virtual void set_char16(size_t pos, const char16& x) = 0;
    virtual char16 get_char16(const String& name) const = 0;
    virtual char16 get_char16(size_t pos) const = 0;

    // string:

    virtual void set_string(const String& name, const String& x) = 0;
    virtual void set_string(size_t pos, const String& x) = 0;
    virtual String get_string(const String& name) const = 0;
    virtual String get_string(size_t pos) const = 0;

    // datetime:

    virtual void set_datetime(const String& name, const Datetime& x) = 0;
    virtual void set_datetime(size_t pos, const Datetime& x) = 0;
    virtual Datetime get_datetime(const String& name) const = 0;
    virtual Datetime get_datetime(size_t pos) const = 0;

    // reference:

    virtual void set_reference(const String& name, const Reference_Facade*) = 0;
    virtual void set_reference(size_t pos, const Reference_Facade*) = 0;
    virtual Reference_Facade* get_reference(const String& name) const = 0;
    virtual Reference_Facade* get_reference(size_t pos) const = 0;

    // print:
    void print(FILE* os, size_t level = 0) const;

private:

    Reference_Facade(const Reference_Facade& x);
    Reference_Facade& operator=(const Reference_Facade& x);
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Reference_Facade_h */
