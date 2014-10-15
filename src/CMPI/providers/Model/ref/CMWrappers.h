#ifndef _CMWrappers_h
#define _CMWrappers_h

#include <cimple/cimple.h>
#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"

//==============================================================================
//
// type_name_of()
//
//==============================================================================

const char* type_name_of(CMPIType type)
{
    if (type & CMPI_boolean)
	return "boolean";

    if (type & CMPI_uint8)
	return "uint8";

    if (type & CMPI_sint8)
	return "sint8";

    if (type & CMPI_uint16)
	return "uint16";

    if (type & CMPI_sint16)
	return "sint16";

    if (type & CMPI_uint32)
	return "uint32";

    if (type & CMPI_sint32)
	return "sint32";

    if (type & CMPI_uint64)
	return "uint64";

    if (type & CMPI_sint64)
	return "sint64";

    if (type & CMPI_real32)
	return "real32";

    if (type & CMPI_real64)
	return "real64";

    if (type & CMPI_char16)
	return "char16";

    if (type & CMPI_string)
	return "string";

    return "unknown";
}

//==============================================================================
//
// get_boolean()
//
//==============================================================================

static void get_boolean(const CMPIValue& v, cimple::boolean& x)
{
    x = v.boolean; 
}

static void get_uint8(const CMPIValue& v, cimple::uint8& x)
{
    x = v.uint8; 
}

static void get_sint8(const CMPIValue& v, cimple::sint8& x)
{
    x = v.sint8; 
}

static void get_uint16(const CMPIValue& v, cimple::uint16& x)
{
    x = v.uint16; 
}

static void get_sint16(const CMPIValue& v, cimple::sint16& x)
{
    x = v.sint16; 
}

static void get_uint32(const CMPIValue& v, cimple::uint32& x)
{
    x = v.uint32; 
}

static void get_sint32(const CMPIValue& v, cimple::sint32& x)
{
    x = v.sint32; 
}

static void get_uint64(const CMPIValue& v, cimple::uint64& x)
{
    x = v.uint64; 
}

static void get_sint64(const CMPIValue& v, cimple::sint64& x)
{
    x = v.sint64; 
}

//==============================================================================
//
// value_of()
//
//==============================================================================

static void value_of(const CMPIData& d, bool& x) 
{
    x = d.value.boolean; 
}

static void value_of(const CMPIData& d, CMPIUint8& x) 
{
    x = d.value.uint8; 
}

static void value_of(const CMPIData& d, CMPISint8& x) 
{
    x = d.value.sint8; 
}

static void value_of(const CMPIData& d, CMPIUint16& x) 
{
    x = d.value.uint16; 
}

static void value_of(const CMPIData& d, CMPISint16& x) 
{
    x = d.value.sint16; 
}

static void value_of(const CMPIData& d, CMPIUint32& x) 
{
    x = d.value.uint32; 
}

static void value_of(const CMPIData& d, CMPISint32& x) 
{
    x = d.value.sint32; 
}

static void value_of(const CMPIData& d, CMPIUint64& x) 
{
    x = d.value.uint64; 
}

static void value_of(const CMPIData& d, CMPISint64& x) 
{
    x = d.value.sint64; 
}

static void value_of(const CMPIData& d, CMPIReal32& x) 
{
    x = d.value.real32; 
}

static void value_of(const CMPIData& d, CMPIReal64& x) 
{
    x = d.value.real64; 
}

static void value_of(const CMPIData& d, const char*& x)
{ 
    x = CMGetCharPtr(d.value.string); 
}

//==============================================================================
//
// type_of()
//
//==============================================================================


static CMPIType type_of(CMPIUint32& x) { return CMPI_uint32; }
static CMPIType type_of(const char*& x) { return CMPI_string; }

class CMW_Const_Object_Path
{
public:

    CMW_Const_Object_Path(const CMPIObjectPath* rep) : 
	_rep((CMPIObjectPath*)rep)
    {
    }

    ~CMW_Const_Object_Path()
    {
    } 

    CMPIObjectPath* clone() const
    {
	return CMClone(_rep, NULL);
    }

    const char* name_space() const
    {
	return CMGetCharsPtr(CMGetNameSpace(_rep, NULL), NULL);
    }

    const char* class_name() const
    {
	return CMGetCharsPtr(CMGetClassName(_rep, NULL), NULL);
    }

    const char* host_name() const
    {
	return CMGetCharsPtr(CMGetHostname(_rep, NULL), NULL);
    }

    size_t key_count() const
    {
	return CMGetKeyCount(_rep, NULL);
    }

    bool get_key_string(const char* name, const char*& value) const
    {
	return _get_key(name, value);
    }

    bool get_key_uint32(const char* name, CMPIUint32& value) const
    {
	return _get_key(name, value);
    }

    CMPIData get_key_at(size_t index, const char*& name) const
    {
	CMPIString* tmp = NULL;
	CMPIData data = CMGetKeyAt(_rep, index, &tmp, NULL);
	name = CMGetCharPtr(tmp);
	return data;
    }

    void dump() const
    {
	printf("CMPIObjectPath:\n");
	printf("    name_space[%s]\n", name_space());
	printf("    class_name[%s]\n", class_name());
	printf("    host_name[%s]\n", host_name());

	for (size_t i = 0; i < key_count(); i++)
	{
	    const char* name;
	    CMPIData d = get_key_at(i, name);

	    printf("    %s %s[", type_name_of(d.type), name);

	    if (d.type & CMPI_string)
	    {
		const char* x;
		value_of(d, x);
		printf("%s", x);
	    }
	    else if (d.type & CMPI_uint32)
	    {
		CMPIUint32 x;
		value_of(d, x);
		printf("%u", x);
	    }
	    else
	    {
	    }

	    printf("]\n");
	}
    }

protected:

    CMW_Const_Object_Path() { }

    CMPIObjectPath* _rep;

private:

    template<class T>
    bool _get_key(const char* name, T& value) const
    {
	CMPIStatus st;
	CMPIData data = CMGetKey(_rep, name, &st);

	if (st.rc == CMPI_RC_OK && (data.type & type_of(value)))
	{
	    value_of(data, value);
	    return true;
	}
	return false;
    }
};

class CMW_Object_Path : public CMW_Const_Object_Path
{
public:

    CMW_Object_Path(
	const CMPIBroker* broker,
	const char* name_space = 0,
	const char* class_name = 0,
	CMPIStatus* status = 0)
    {
	_rep = CMNewObjectPath(broker, name_space, class_name, status);
    }

    ~CMW_Object_Path()
    {
	if (_rep)
	    CMRelease(_rep);
    } 

    void name_space(const char* name_space)
    {
	CMSetNameSpace(_rep, name_space);
    }

    void class_name(const char* class_name)
    {
	CMSetClassName(_rep, class_name);
    }

    void host_name(const char* host_name)
    {
	CMSetHostname(_rep, host_name);
    }

    void add_key_string(const char* name, const char* value)
    {
	CMAddKey(_rep, name, value, CMPI_chars);
    }

    void add_key_uint32(const char* name, CMPIUint32 value)
    {
	CMAddKey(_rep, name, &value, CMPI_uint32);
    }

    CMPIObjectPath* rep()
    {
	return _rep;
    }

#if 0

    void get_key_at(
	CMPIObjectPath* _rep, size_t i, const char*& name)
    {
	key1 = CMGetKeyAt(object1, i, &keyname, &status);
    }

#endif
};

#endif /* _CMWrappers_h */
