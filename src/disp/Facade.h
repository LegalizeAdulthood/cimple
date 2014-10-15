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

#ifndef _cimple_Facade_h
#define _cimple_Facade_h

#include <cimple/Instance.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

/** A facade provides a "dynamic" interface to setting and getting instance
    properties. The example below shows how to set and get the "count" property
    of an instance.

    <pre>
	Instance* inst;
	...
	Facade facade(inst);

	facade.set_uint32("count", 10);

	uint32 count;
	facade.get_uint32("count", count);
    </pre>

    All set and get methods return 0 on success and -1 on failure. A failure
    indicates a type mismatch between field and the method (for example, 
    calling get_uint32() on a uint16 field is a type mismatch).
*/
class CIMPLEDISP_LINKAGE Facade
{
public:

    Facade(Instance* instance);

    ~Facade();

    Instance* steal();

    Instance* instance() { return _instance; }

    const Instance* instance() const { return _instance; }

    void print() const;

    int set_null(const char* name, bool null);

    int set_boolean(const char* name, boolean value, bool null);

    int set_uint8(const char* name, uint8 value, bool null);

    int set_sint8(const char* name, sint8 value, bool null);

    int set_uint16(const char* name, uint16 value, bool null);

    int set_sint16(const char* name, sint16 value, bool null);

    int set_uint32(const char* name, uint32 value, bool null);

    int set_sint32(const char* name, sint32 value, bool null);

    int set_uint64(const char* name, uint64 value, bool null);

    int set_sint64(const char* name, sint64 value, bool null);

    int set_real32(const char* name, real32 value, bool null);

    int set_real64(const char* name, real64 value, bool null);

    int set_char16(const char* name, char16 value, bool null);

    int set_string(const char* name, const String& value, bool null);

    int set_Datetime(const char* name, const Datetime& value, bool null);

    int set_ref(const char* name, Instance* ref);

    int set_boolean_array(
	const char* name, const Array<boolean>& value, bool null);

    int set_uint8_array(
	const char* name, const Array<uint8>& value, bool null);

    int set_sint8_array(
	const char* name, const Array<sint8>& value, bool null);

    int set_uint16_array(
	const char* name, const Array<uint16>& value, bool null);

    int set_sint16_array(
	const char* name, const Array<sint16>& value, bool null);

    int set_uint32_array(
	const char* name, const Array<uint32>& value, bool null);

    int set_sint32_array(
	const char* name, const Array<sint32>& value, bool null);

    int set_uint64_array(
	const char* name, const Array<uint64>& value, bool null);

    int set_sint64_array(
	const char* name, const Array<sint64>& value, bool null);

    int set_real32_array(
	const char* name, const Array<real32>& value, bool null);

    int set_real64_array(
	const char* name, const Array<real64>& value, bool null);

    int set_char16_array(
	const char* name, const Array<char16>& value, bool null);

    int set_string_array(
	const char* name, const Array<String>& value, bool null);

    int set_Datetime_array(
	const char* name, const Array<Datetime>& value, bool null);

    int get_boolean(const char* name, boolean& value, bool& null);

    int get_uint8(const char* name, uint8& value, bool& null);

    int get_sint8(const char* name, sint8& value, bool& null);

    int get_uint16(const char* name, uint16& value, bool& null);

    int get_sint16(const char* name, sint16& value, bool& null);

    int get_uint32(const char* name, uint32& value, bool& null);

    int get_sint32(const char* name, sint32& value, bool& null);

    int get_uint64(const char* name, uint64& value, bool& null);

    int get_sint64(const char* name, sint64& value, bool& null);

    int get_real32(const char* name, real32& value, bool& null);

    int get_real64(const char* name, real64& value, bool& null);

    int get_char16(const char* name, char16& value, bool& null);

    int get_string(const char* name, String& value, bool& null);

    int get_Datetime(const char* name, Datetime& value, bool& null);

    int get_ref(const char* name, Instance*& ref);

    int get_boolean_array(const char* name, Array<boolean>& value, bool& null);

    int get_uint8_array(const char* name, Array<uint8>& value, bool& null);

    int get_sint8_array(const char* name, Array<sint8>& value, bool& null);

    int get_uint16_array(const char* name, Array<uint16>& value, bool& null);

    int get_sint16_array(const char* name, Array<sint16>& value, bool& null);

    int get_uint32_array(const char* name, Array<uint32>& value, bool& null);

    int get_sint32_array(const char* name, Array<sint32>& value, bool& null);

    int get_uint64_array(const char* name, Array<uint64>& value, bool& null);

    int get_sint64_array(const char* name, Array<sint64>& value, bool& null);

    int get_real32_array(const char* name, Array<real32>& value, bool& null);

    int get_real64_array(const char* name, Array<real64>& value, bool& null);

    int get_char16_array(const char* name, Array<char16>& value, bool& null);

    int get_string_array(const char* name, Array<String>& value, bool& null);

    int get_Datetime_array(
	const char* name, Array<Datetime>& value, bool& null);

private:

    int _set_array(
	Type type, const char* name, const Array_Base& value, bool null);

    int _get_array(
	Type type, const char* name, Array_Base& value, bool& null);

    Instance* _instance;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Facade_h */
