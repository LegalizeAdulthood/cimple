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

#include <cctype>
#include "CMPI_Reference_Facade.h"

CIMPLE_NAMESPACE_BEGIN

static bool _valid_ident(const char* s)
{
    if (!isalpha(*s) && *s != '_')
        return false;

    for (s++; *s; s++)
    {
        if (!isalnum(*s) && *s != '_')
            return false;
    }

    return true;
}

static const char* _get_chars_ptr(CMPIString* str)
{
    CMPIStatus status;
    const char* s = CMGetCharsPtr(str, &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMGetCharsPtr(%p, %p) failed", 
            (void*)str, (void*)&status);
    }

    return s;
}

static CMPIData _get_key_at(CMPIObjectPath* cop, size_t i, const char*& name)
{
    CMPIStatus status;
    CMPIString* name_str;
    CMPIData data = CMGetKeyAt(cop, i, &name_str, &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMGetKeyAt(%p, %d, %p, %p) failed", 
            (void*)cop, (int)i, (void*)&name_str, (void*)&status);
    }

    name = _get_chars_ptr(name_str);

    if (!name)
    {
        throw_exception("CMGetKeyAt(%p, %d, %p, %p) produced null name", 
            (void*)cop, (int)i, (void*)&name_str, (void*)&status);
    }

    return data;
}

CMPI_Reference_Facade::CMPI_Reference_Facade()
{
}

CMPI_Reference_Facade::~CMPI_Reference_Facade()
{
}

void CMPI_Reference_Facade::host_name(const String& host_name)
{
    if (host_name.size() == 0)
    {
        throw_exception(
            "CMPI_Reference_Facade::host_name(%s): bad host_name arg",
            host_name.c_str());
    }

    CMPIStatus status = CMSetHostname(_cop, host_name.c_str());

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMSetHostname(%p, %s) failed", 
            (void*)_cop, host_name.c_str());
    }
}

String CMPI_Reference_Facade::host_name() const
{
    CMPIStatus status;
    CMPIString* str = CMGetHostname(_cop, &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMGetHostname(%p, %p) failed", 
            (void*)_cop, (void*)&status);
    }

    if (!str)
        return String();

    const char* s = _get_chars_ptr(str);

    if (!s)
        return String();

    return String(s);
}

void CMPI_Reference_Facade::name_space(const String& name_space)
{
    if (name_space.size() == 0)
    {
        throw_exception(
            "CMPI_Reference_Facade::name_space(%s): bad name_space arg",
            name_space.c_str());
    }

    CMPIStatus status = CMSetNameSpace(_cop, name_space.c_str());

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMSetNameSpace(%p, %s) failed", 
            (void*)_cop, name_space.c_str());
    }
}

String CMPI_Reference_Facade::name_space() const
{
    CMPIStatus status;
    CMPIString* str = CMGetNameSpace(_cop, &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMGetNameSpace(%p, %p) failed", 
            (void*)_cop, (void*)&status);
    }

    if (!str)
        return String();

    const char* s = _get_chars_ptr(str);

    if (!s)
        return String();

    return String(s);
}

void CMPI_Reference_Facade::class_name(const String& class_name)
{
    if (!_valid_ident(class_name.c_str()))
    {
        throw_exception(
            "CMPI_Reference_Facade::class_name(%s): bad class_name arg",
            class_name.c_str());
    }

    CMPIStatus status = CMSetClassName(_cop, class_name.c_str());

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMSetClassName(%p, %s) failed", 
            (void*)_cop, class_name.c_str());
    }
}

String CMPI_Reference_Facade::class_name() const
{
    CMPIStatus status;
    CMPIString* str = CMGetClassName(_cop, &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMGetClassName(%p, %p) failed", 
            (void*)_cop, (void*)&status);
    }

    if (!str)
        return String();

    const char* s = _get_chars_ptr(str);

    if (!s)
        return String();

    return String(s);
}

size_t CMPI_Reference_Facade::count() const
{
    CMPIStatus status;
    CMPICount n = CMGetKeyCount(_cop, &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMGetKeyCount(%p, %p) failed", 
            (void*)_cop, (void*)&status);
    }

    return size_t(n);
}

size_t CMPI_Reference_Facade::find(const String& name) const
{
    for (size_t i = 0, n = count(); i < n; i++)
    {
        const char* s;
        _get_key_at(_cop, i, s);

        if (eqi(name, s))
            return i;
    }

    // Not found.
    return size_t(-1);
}

String CMPI_Reference_Facade::get_name(size_t pos) const
{
    if (pos > count())
    {
        throw_exception("CMPI_Reference_Facade::get_name(%d) : bad pos arg)",
            int(pos));
    }

    const char* name;
    _get_key_at(_cop, pos, name);

    return String(name);
}

bool CMPI_Reference_Facade::is_reference(size_t pos) const
{
}

#if 0

Type CMPI_Reference_Facade::get_type(size_t pos) const
{
}

void CMPI_Reference_Facade::set_null(const String& name, Type type)
{
}

void CMPI_Reference_Facade::set_null(size_t pos, bool null)
{
}

bool CMPI_Reference_Facade::get_null(const String& name) const
{
}

bool CMPI_Reference_Facade::get_null(size_t pos) const
{
}

void CMPI_Reference_Facade::set_boolean(const String& name, const boolean& x)
{
}

void CMPI_Reference_Facade::set_boolean(size_t pos, const boolean& x)
{
}

boolean CMPI_Reference_Facade::get_boolean(const String& name) const
{
}

boolean CMPI_Reference_Facade::get_boolean(size_t pos) const
{
}

void CMPI_Reference_Facade::set_uint8(const String& name, const uint8& x)
{
}

void CMPI_Reference_Facade::set_uint8(size_t pos, const uint8& x)
{
}

uint8 CMPI_Reference_Facade::get_uint8(const String& name) const
{
}

uint8 CMPI_Reference_Facade::get_uint8(size_t pos) const
{
}

void CMPI_Reference_Facade::set_sint8(const String& name, const sint8& x)
{
}

void CMPI_Reference_Facade::set_sint8(size_t pos, const sint8& x)
{
}

sint8 CMPI_Reference_Facade::get_sint8(const String& name) const
{
}

sint8 CMPI_Reference_Facade::get_sint8(size_t pos) const
{
}

void CMPI_Reference_Facade::set_uint16(const String& name, const uint16& x)
{
}

void CMPI_Reference_Facade::set_uint16(size_t pos, const uint16& x)
{
}

uint16 CMPI_Reference_Facade::get_uint16(const String& name) const
{
}

uint16 CMPI_Reference_Facade::get_uint16(size_t pos) const
{
}

void CMPI_Reference_Facade::set_sint16(const String& name, const sint16& x)
{
}

void CMPI_Reference_Facade::set_sint16(size_t pos, const sint16& x)
{
}

sint16 CMPI_Reference_Facade::get_sint16(const String& name) const
{
}

sint16 CMPI_Reference_Facade::get_sint16(size_t pos) const
{
}

void CMPI_Reference_Facade::set_uint32(const String& name, const uint32& x)
{
}

void CMPI_Reference_Facade::set_uint32(size_t pos, const uint32& x)
{
}

uint32 CMPI_Reference_Facade::get_uint32(const String& name) const
{
}

uint32 CMPI_Reference_Facade::get_uint32(size_t pos) const
{
}

void CMPI_Reference_Facade::set_sint32(const String& name, const sint32& x)
{
}

void CMPI_Reference_Facade::set_sint32(size_t pos, const sint32& x)
{
}

sint32 CMPI_Reference_Facade::get_sint32(const String& name) const
{
}

sint32 CMPI_Reference_Facade::get_sint32(size_t pos) const
{
}

void CMPI_Reference_Facade::set_uint64(const String& name, const uint64& x)
{
}

void CMPI_Reference_Facade::set_uint64(size_t pos, const uint64& x)
{
}

uint64 CMPI_Reference_Facade::get_uint64(const String& name) const
{
}

uint64 CMPI_Reference_Facade::get_uint64(size_t pos) const
{
}

void CMPI_Reference_Facade::set_sint64(const String& name, const sint64& x)
{
}

void CMPI_Reference_Facade::set_sint64(size_t pos, const sint64& x)
{
}

sint64 CMPI_Reference_Facade::get_sint64(const String& name) const
{
}

sint64 CMPI_Reference_Facade::get_sint64(size_t pos) const
{
}

void CMPI_Reference_Facade::set_real32(const String& name, const real32& x)
{
}

void CMPI_Reference_Facade::set_real32(size_t pos, const real32& x)
{
}

real32 CMPI_Reference_Facade::get_real32(const String& name) const
{
}

real32 CMPI_Reference_Facade::get_real32(size_t pos) const
{
}

void CMPI_Reference_Facade::set_real64(const String& name, const real64& x)
{
}

void CMPI_Reference_Facade::set_real64(size_t pos, const real64& x)
{
}

real64 CMPI_Reference_Facade::get_real64(const String& name) const
{
}

real64 CMPI_Reference_Facade::get_real64(size_t pos) const
{
}

void CMPI_Reference_Facade::set_char16(const String& name, const char16& x)
{
}

void CMPI_Reference_Facade::set_char16(size_t pos, const char16& x)
{
}

char16 CMPI_Reference_Facade::get_char16(const String& name) const
{
}

char16 CMPI_Reference_Facade::get_char16(size_t pos) const
{
}

void CMPI_Reference_Facade::set_string(const String& name, const String& x)
{
}

void CMPI_Reference_Facade::set_string(size_t pos, const String& x)
{
}

String CMPI_Reference_Facade::get_string(const String& name) const
{
}

String CMPI_Reference_Facade::get_string(size_t pos) const
{
}

void CMPI_Reference_Facade::set_datetime(const String& name, const Datetime& x)
{
}

void CMPI_Reference_Facade::set_datetime(size_t pos, const Datetime& x)
{
}

Datetime CMPI_Reference_Facade::get_datetime(const String& name) const
{
}

Datetime CMPI_Reference_Facade::get_datetime(size_t pos) const
{
}

void CMPI_Reference_Facade::set_reference(
    const String& name, const Reference_Facade*)
{
}

void CMPI_Reference_Facade::set_reference(size_t pos, const Reference_Facade*)
{
}

Reference_Facade* CMPI_Reference_Facade::get_reference(const String& name) const
{
}

Reference_Facade* CMPI_Reference_Facade::get_reference(size_t pos) const
{
}

#endif

CMPI_Reference_Facade* CMPI_Reference_Facade::create(
    CMPIBroker* broker,
    const String& name_space,
    const String& class_name)
{
    if (!broker)
    {
        throw_exception(
            "CMPI_Reference_Facade::create(%p, %s, %s): bad broker arg",
            (void*)broker, name_space.c_str(), class_name.c_str());
    }

    if (name_space.size() == 0)
    {
        throw_exception(
            "CMPI_Reference_Facade::create(%p, %s, %s): bad name_space arg",
            (void*)broker, name_space.c_str(), class_name.c_str());
    }

    if (!_valid_ident(class_name.c_str()))
    {
        throw_exception(
            "CMPI_Reference_Facade::create(%p, %s, %s): bad class_name arg",
            (void*)broker, name_space.c_str(), class_name.c_str());
    }

    CMPIStatus status;
    CMPIObjectPath* cop = CMNewObjectPath(
        broker, name_space.c_str(), class_name.c_str(), &status);

    if (status.rc != CMPI_RC_OK)
    {
        throw_exception(status, "CMNewObjectPath(%p, %s, %s, %p)", 
            (void*)broker, 
            name_space.c_str(), 
            class_name.c_str(), 
            (void*)&status);
    }

    if (!cop)
    {
        throw_exception("CMNewObjectPath(%p, %s, %s, %p) returned null", 
            (void*)broker, 
            name_space.c_str(), 
            class_name.c_str(), 
            (void*)&status);
    }

    CMPI_Reference_Facade* rf = new CMPI_Reference_Facade;
    rf->_cb = broker;
    rf->_cop = cop;

    return rf;
}

static CMPI_Reference_Facade::_check_bounds(const char* func, size_t pos)
{
    if (pos > count())
    {
    }
}

CIMPLE_NAMESPACE_END
