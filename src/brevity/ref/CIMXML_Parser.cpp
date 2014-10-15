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

#include "CIMXML_Parser.h"

#define CIMXML_ASSUME(COND) \
    do \
    { \
        if (!(COND)) \
        { \
            raise("%s(%u): assumption failed: \"%s\"",  \
                __FILE__, __LINE__, #COND); \
            return; \
        } \
    } \
    while (0)

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local definitions:
//
//==============================================================================

static const char* _tag_names[] =
{
    "NULL",
    "CIM",
    "DECLARATION",
    "DECLGROUP",
    "DECLGROUP.WITHNAME",
    "DECLGROUP.WITHPATH",
    "QUALIFIER.DECLARATION",
    "SCOPE",
    "VALUE",
    "VALUE.ARRAY",
    "VALUE.REFERENCE",
    "VALUE.REFARRAY",
    "VALUE.OBJECT",
    "VALUE.NAMEDINSTANCE",
    "VALUE.NAMEDOBJECT",
    "VALUE.OBJECTWITHLOCALPATH",
    "VALUE.OBJECTWITHPATH",
    "VALUE.NULL",
    "NAMESPACEPATH",
    "LOCALNAMESPACEPATH",
    "HOST",
    "NAMESPACE",
    "CLASSPATH",
    "LOCALCLASSPATH",
    "CLASSNAME",
    "INSTANCEPATH",
    "LOCALINSTANCEPATH",
    "INSTANCENAME",
    "OBJECTPATH",
    "KEYBINDING",
    "KEYVALUE",
    "CLASS",
    "INSTANCE",
    "QUALIFIER",
    "PROPERTY",
    "PROPERTY.ARRAY",
    "PROPERTY.REFERENCE",
    "METHOD",
    "PARAMETER",
    "PARAMETER.REFERENCE",
    "PARAMETER.ARRAY",
    "PARAMETER.REFARRAY",
    "TABLECELL.DECLARATION",
    "TABLECELL.REFERENCE",
    "TABLEROW.DECLARATION",
    "TABLE",
    "TABLEROW",
    "MESSAGE",
    "MULTIREQ",
    "MULTIEXPREQ",
    "SIMPLEREQ",
    "SIMPLEEXPREQ",
    "IMETHODCALL",
    "METHODCALL",
    "EXPMETHODCALL",
    "PARAMVALUE",
    "IPARAMVALUE",
    "EXPPARAMVALUE",
    "MULTIRSP",
    "MULTIEXPRSP",
    "SIMPLERSP",
    "SIMPLEEXPRSP",
    "METHODRESPONSE",
    "EXPMETHODRESPONSE",
    "IMETHODRESPONSE",
    "ERROR",
    "RETURNVALUE",
    "IRETURNVALUE",
    "RESPONSEDESTINATION",
    "SIMPLEREQACK",
};

static int _name_to_tag(const char* s, size_t n)
{
    CIMPLE_ASSERT(n != 0);

    switch (n + s[0] + s[n-1])
    {
        case 145:
            if (n == 9 && memcmp("CLASSNAME", s, 9) == 0)
                return TAG_CLASSNAME;
            break;
        case 147:
            if (n == 3 && memcmp("CIM", s, 3) == 0)
                return TAG_CIM;
            break;
        case 148:
            if (n == 9 && memcmp("CLASSPATH", s, 9) == 0)
                return TAG_CLASSPATH;
            break;
        case 150:
            if (n == 8 && memcmp("INSTANCE", s, 8) == 0)
                return TAG_INSTANCE;
            break;
        case 151:
            if (n == 6 && memcmp("METHOD", s, 6) == 0)
                return TAG_METHOD;
            if (n == 13 && memcmp("EXPPARAMVALUE", s, 13) == 0)
                return TAG_EXPPARAMVALUE;
            break;
        case 152:
            if (n == 8 && memcmp("KEYVALUE", s, 8) == 0)
                return TAG_KEYVALUE;
            break;
        case 153:
            if (n == 7 && memcmp("MESSAGE", s, 7) == 0)
                return TAG_MESSAGE;
            if (n == 11 && memcmp("IPARAMVALUE", s, 11) == 0)
                return TAG_IPARAMVALUE;
            break;
        case 154:
            if (n == 12 && memcmp("INSTANCENAME", s, 12) == 0)
                return TAG_INSTANCENAME;
            if (n == 12 && memcmp("IRETURNVALUE", s, 12) == 0)
                return TAG_IRETURNVALUE;
            break;
        case 155:
            if (n == 18 && memcmp("DECLGROUP.WITHNAME", s, 18) == 0)
                return TAG_DECLGROUP_WITHNAME;
            if (n == 5 && memcmp("CLASS", s, 5) == 0)
                return TAG_CLASS;
            if (n == 17 && memcmp("EXPMETHODRESPONSE", s, 17) == 0)
                return TAG_EXPMETHODRESPONSE;
            break;
        case 156:
            if (n == 9 && memcmp("NAMESPACE", s, 9) == 0)
                return TAG_NAMESPACE;
            if (n == 10 && memcmp("KEYBINDING", s, 10) == 0)
                return TAG_KEYBINDING;
            if (n == 5 && memcmp("ERROR", s, 5) == 0)
                return TAG_ERROR;
            break;
        case 157:
            if (n == 11 && memcmp("DECLARATION", s, 11) == 0)
                return TAG_DECLARATION;
            if (n == 9 && memcmp("DECLGROUP", s, 9) == 0)
                return TAG_DECLGROUP;
            if (n == 5 && memcmp("SCOPE", s, 5) == 0)
                return TAG_SCOPE;
            if (n == 12 && memcmp("INSTANCEPATH", s, 12) == 0)
                return TAG_INSTANCEPATH;
            if (n == 15 && memcmp("IMETHODRESPONSE", s, 15) == 0)
                return TAG_IMETHODRESPONSE;
            break;
        case 158:
            if (n == 18 && memcmp("DECLGROUP.WITHPATH", s, 18) == 0)
                return TAG_DECLGROUP_WITHPATH;
            if (n == 5 && memcmp("TABLE", s, 5) == 0)
                return TAG_TABLE;
            if (n == 13 && memcmp("EXPMETHODCALL", s, 13) == 0)
                return TAG_EXPMETHODCALL;
            break;
        case 159:
            if (n == 10 && memcmp("PARAMVALUE", s, 10) == 0)
                return TAG_PARAMVALUE;
            break;
        case 160:
            if (n == 5 && memcmp("VALUE", s, 5) == 0)
                return TAG_VALUE;
            if (n == 4 && memcmp("HOST", s, 4) == 0)
                return TAG_HOST;
            if (n == 11 && memcmp("IMETHODCALL", s, 11) == 0)
                return TAG_IMETHODCALL;
            if (n == 14 && memcmp("METHODRESPONSE", s, 14) == 0)
                return TAG_METHODRESPONSE;
            break;
        case 161:
            if (n == 10 && memcmp("OBJECTPATH", s, 10) == 0)
                return TAG_OBJECTPATH;
            break;
        case 162:
            if (n == 14 && memcmp("LOCALCLASSPATH", s, 14) == 0)
                return TAG_LOCALCLASSPATH;
            if (n == 11 && memcmp("RETURNVALUE", s, 11) == 0)
                return TAG_RETURNVALUE;
            break;
        case 163:
            if (n == 13 && memcmp("NAMESPACEPATH", s, 13) == 0)
                return TAG_NAMESPACEPATH;
            if (n == 10 && memcmp("METHODCALL", s, 10) == 0)
                return TAG_METHODCALL;
            break;
        case 165:
            if (n == 17 && memcmp("LOCALINSTANCEPATH", s, 17) == 0)
                return TAG_LOCALINSTANCEPATH;
            if (n == 8 && memcmp("MULTIRSP", s, 8) == 0)
                return TAG_MULTIRSP;
            break;
        case 166:
            if (n == 18 && memcmp("LOCALNAMESPACEPATH", s, 18) == 0)
                return TAG_LOCALNAMESPACEPATH;
            if (n == 8 && memcmp("MULTIREQ", s, 8) == 0)
                return TAG_MULTIREQ;
            break;
        case 167:
            if (n == 18 && memcmp("PROPERTY.REFERENCE", s, 18) == 0)
                return TAG_PROPERTY_REFERENCE;
            break;
        case 168:
            if (n == 19 && memcmp("PARAMETER.REFERENCE", s, 19) == 0)
                return TAG_PARAMETER_REFERENCE;
            if (n == 11 && memcmp("MULTIEXPRSP", s, 11) == 0)
                return TAG_MULTIEXPRSP;
            break;
        case 169:
            if (n == 11 && memcmp("MULTIEXPREQ", s, 11) == 0)
                return TAG_MULTIEXPREQ;
            break;
        case 170:
            if (n == 15 && memcmp("VALUE.REFERENCE", s, 15) == 0)
                return TAG_VALUE_REFERENCE;
            if (n == 12 && memcmp("SIMPLEREQACK", s, 12) == 0)
                return TAG_SIMPLEREQACK;
            break;
        case 171:
            if (n == 9 && memcmp("PARAMETER", s, 9) == 0)
                return TAG_PARAMETER;
            break;
        case 172:
            if (n == 10 && memcmp("VALUE.NULL", s, 10) == 0)
                return TAG_VALUE_NULL;
            if (n == 9 && memcmp("QUALIFIER", s, 9) == 0)
                return TAG_QUALIFIER;
            if (n == 19 && memcmp("TABLECELL.REFERENCE", s, 19) == 0)
                return TAG_TABLECELL_REFERENCE;
            if (n == 9 && memcmp("SIMPLERSP", s, 9) == 0)
                return TAG_SIMPLERSP;
            break;
        case 173:
            if (n == 9 && memcmp("SIMPLEREQ", s, 9) == 0)
                return TAG_SIMPLEREQ;
            break;
        case 174:
            if (n == 19 && memcmp("VALUE.NAMEDINSTANCE", s, 19) == 0)
                return TAG_VALUE_NAMEDINSTANCE;
            break;
        case 175:
            if (n == 12 && memcmp("SIMPLEEXPRSP", s, 12) == 0)
                return TAG_SIMPLEEXPRSP;
            break;
        case 176:
            if (n == 12 && memcmp("SIMPLEEXPREQ", s, 12) == 0)
                return TAG_SIMPLEEXPREQ;
            break;
        case 177:
            if (n == 8 && memcmp("PROPERTY", s, 8) == 0)
                return TAG_PROPERTY;
            break;
        case 178:
            if (n == 20 && memcmp("VALUE.OBJECTWITHPATH", s, 20) == 0)
                return TAG_VALUE_OBJECTWITHPATH;
            break;
        case 179:
            if (n == 8 && memcmp("TABLEROW", s, 8) == 0)
                return TAG_TABLEROW;
            if (n == 19 && memcmp("RESPONSEDESTINATION", s, 19) == 0)
                return TAG_RESPONSEDESTINATION;
            break;
        case 180:
            if (n == 21 && memcmp("QUALIFIER.DECLARATION", s, 21) == 0)
                return TAG_QUALIFIER_DECLARATION;
            break;
        case 182:
            if (n == 12 && memcmp("VALUE.OBJECT", s, 12) == 0)
                return TAG_VALUE_OBJECT;
            if (n == 20 && memcmp("TABLEROW.DECLARATION", s, 20) == 0)
                return TAG_TABLEROW_DECLARATION;
            break;
        case 183:
            if (n == 25 && memcmp("VALUE.OBJECTWITHLOCALPATH", s, 25) == 0)
                return TAG_VALUE_OBJECTWITHLOCALPATH;
            if (n == 14 && memcmp("PROPERTY.ARRAY", s, 14) == 0)
                return TAG_PROPERTY_ARRAY;
            if (n == 21 && memcmp("TABLECELL.DECLARATION", s, 21) == 0)
                return TAG_TABLECELL_DECLARATION;
            break;
        case 184:
            if (n == 15 && memcmp("PARAMETER.ARRAY", s, 15) == 0)
                return TAG_PARAMETER_ARRAY;
            break;
        case 186:
            if (n == 11 && memcmp("VALUE.ARRAY", s, 11) == 0)
                return TAG_VALUE_ARRAY;
            break;
        case 187:
            if (n == 17 && memcmp("VALUE.NAMEDOBJECT", s, 17) == 0)
                return TAG_VALUE_NAMEDOBJECT;
            if (n == 18 && memcmp("PARAMETER.REFARRAY", s, 18) == 0)
                return TAG_PARAMETER_REFARRAY;
            break;
        case 189:
            if (n == 14 && memcmp("VALUE.REFARRAY", s, 14) == 0)
                return TAG_VALUE_REFARRAY;
            break;
    }

    return TAG_NULL;
}

static const char _CIM_children[] =
{
    TAG_MESSAGE, /* done */
    TAG_DECLARATION,
    TAG_NULL,
};

static const char _MESSAGE_children[] =
{
    TAG_SIMPLEREQ,
    TAG_MULTIREQ,
    TAG_SIMPLERSP, /* done */
    TAG_MULTIRSP,
    TAG_SIMPLEEXPREQ,
    TAG_MULTIEXPREQ,
    TAG_SIMPLEEXPRSP,
    TAG_MULTIEXPRSP,
    TAG_NULL,
};

static const char _SIMPLERSP_children[] =
{
    TAG_METHODRESPONSE,
    TAG_IMETHODRESPONSE, /* done */
    TAG_SIMPLEREQACK,
    TAG_NULL,
};

static const char _IMETHODRESPONSE_children[] =
{
    TAG_ERROR,
    TAG_IRETURNVALUE, /* done */
    TAG_NULL,
};

static const char _IRETURNVALUE_children[] =
{
    TAG_CLASSNAME,
    TAG_INSTANCENAME,
    TAG_VALUE,
    TAG_VALUE_OBJECTWITHPATH,
    TAG_VALUE_OBJECTWITHLOCALPATH,
    TAG_VALUE_OBJECT,
    TAG_OBJECTPATH,
    TAG_QUALIFIER_DECLARATION,
    TAG_VALUE_ARRAY,
    TAG_VALUE_REFERENCE,
    TAG_CLASS,
    TAG_INSTANCE,
    TAG_VALUE_NAMEDINSTANCE, /* done */
    TAG_TABLE,
    TAG_NULL,
};

static const char _VALUE_NAMEDINSTANCE_children[] =
{
    TAG_INSTANCENAME,  /* done */
    TAG_INSTANCE, /* done */
    TAG_NULL,
};

static const char _INSTANCENAME_children[] =
{
    TAG_KEYBINDING, /* done */
    TAG_KEYVALUE,
    TAG_VALUE_REFERENCE,
    TAG_NULL,
};

static const char _INSTANCE_children[] =
{
    TAG_QUALIFIER,
    TAG_PROPERTY,
    TAG_PROPERTY_ARRAY,
    TAG_PROPERTY_REFERENCE,
    TAG_NULL,
};

static const char _PROPERTY_children[] =
{
    TAG_QUALIFIER,
    TAG_VALUE, /* done */
    TAG_NULL,
};

static const char _PROPERTY_ARRAY_children[] =
{
    TAG_QUALIFIER, 
    TAG_VALUE_ARRAY, /* done */
    TAG_NULL,
};

static const char _PROPERTY_REFERENCE_children[] =
{
    TAG_QUALIFIER, 
    TAG_VALUE_REFERENCE,
    TAG_NULL,
};

static const char _VALUE_children[] =
{
    TAG_NULL,
};

static const char _VALUE_ARRAY_children[] =
{
    TAG_VALUE,
    TAG_NULL,
};

static const char _VALUE_REFERENCE_children[] =
{
    TAG_CLASSPATH,
    TAG_LOCALCLASSPATH,
    TAG_CLASSNAME,
    TAG_INSTANCEPATH,
    TAG_LOCALINSTANCEPATH,
    TAG_INSTANCENAME,
    TAG_NULL,
};

static const char _LOCALINSTANCEPATH_children[] =
{
    TAG_LOCALNAMESPACEPATH,
    TAG_INSTANCENAME,
    TAG_NULL,
};

static const char _LOCALNAMESPACEPATH_children[] =
{
    TAG_NAMESPACE,
    TAG_NULL,
};

static const char _NAMESPACE_children[] =
{
    TAG_NULL,
};

static const char _KEYBINDING_children[] =
{
    TAG_KEYVALUE,
    TAG_VALUE_REFERENCE,
    TAG_NULL,
};

static const char _KEYVALUE_children[] =
{
    TAG_NULL,
};

static const char _ERROR_children[] =
{
    TAG_INSTANCE,
    TAG_NULL,
};

static const char* _children[] =
{
    0, // NULL
    _CIM_children, // CIM
    0, // DECLARATION
    0, // DECLGROUP
    0, // DECLGROUP_WITHNAME
    0, // DECLGROUP_WITHPATH
    0, // QUALIFIER_DECLARATION
    0, // SCOPE
    _VALUE_children, // VALUE
    _VALUE_ARRAY_children, // VALUE_ARRAY
    _VALUE_REFERENCE_children, // VALUE_REFERENCE
    0, // VALUE_REFARRAY
    0, // VALUE_OBJECT
    _VALUE_NAMEDINSTANCE_children, // VALUE_NAMEDINSTANCE
    0, // VALUE_NAMEDOBJECT
    0, // VALUE_OBJECTWITHLOCALPATH
    0, // VALUE_OBJECTWITHPATH
    0, // VALUE_NULL
    0, // NAMESPACEPATH
    _LOCALNAMESPACEPATH_children, // LOCALNAMESPACEPATH
    0, // HOST
    _NAMESPACE_children, // NAMESPACE
    0, // CLASSPATH
    0, // LOCALCLASSPATH
    0, // CLASSNAME
    0, // INSTANCEPATH
    _LOCALINSTANCEPATH_children, // LOCALINSTANCEPATH
    _INSTANCENAME_children, // INSTANCENAME
    0, // OBJECTPATH
    _KEYBINDING_children, // KEYBINDING
    _KEYVALUE_children, // KEYVALUE
    0, // CLASS
    _INSTANCE_children, // INSTANCE
    0, // QUALIFIER
    _PROPERTY_children, // PROPERTY
    _PROPERTY_ARRAY_children, // PROPERTY_ARRAY
    _PROPERTY_REFERENCE_children, // PROPERTY_REFERENCE
    0, // METHOD
    0, // PARAMETER
    0, // PARAMETER_REFERENCE
    0, // PARAMETER_ARRAY
    0, // PARAMETER_REFARRAY
    0, // TABLECELL_DECLARATION
    0, // TABLECELL_REFERENCE
    0, // TABLEROW_DECLARATION
    0, // TABLE
    0, // TABLEROW
    _MESSAGE_children, // MESSAGE
    0, // MULTIREQ
    0, // MULTIEXPREQ
    0, // SIMPLEREQ
    0, // SIMPLEEXPREQ
    0, // IMETHODCALL
    0, // METHODCALL
    0, // EXPMETHODCALL
    0, // PARAMVALUE
    0, // IPARAMVALUE
    0, // EXPPARAMVALUE
    0, // MULTIRSP
    0, // MULTIEXPRSP
    _SIMPLERSP_children, // SIMPLERSP
    0, // SIMPLEEXPRSP
    0, // METHODRESPONSE
    0, // EXPMETHODRESPONSE
    _IMETHODRESPONSE_children, // IMETHODRESPONSE
    0, // ERROR
    0, // RETURNVALUE
    _IRETURNVALUE_children, // IRETURNVALUE
    0, // RESPONSEDESTINATION
    0, // SIMPLEREQACK
};

static inline Tag _name_to_tag(const char* s)
{
    return Tag(_name_to_tag(s, strlen(s)));
}

static int _parse_version(Version& version, const char* value)
{
    do
    {
        char* end;
        long major;
        long minor;

        // Parse minor version.

        major = strtol(value, &end, 10);

        if (major < 0 || major > 255 || *end != '.')
            return -1;

        // Parse major version.

        value = end + 1;
        minor = strtol(value, &end, 10);

        if (minor < 0 || minor > 255 || *end != '\0')
            return -1;

        version.major = (unsigned char)major;
        version.minor = (unsigned char)minor;
    }
    while (0);

    // Success.
    return 0;
}

static inline const char* _find_attr(const char** attrs, const char* name)
{
    for (; attrs[0]; attrs += 2)
    {
        if (strcmp(attrs[0], name) == 0)
            return attrs[1];
    }

    // Not found!
    return 0;
}

//==============================================================================
//
// class CIMXML_Context
//
//==============================================================================

CIMXML_Context::CIMXML_Context()
{
    clear();
}

void CIMXML_Context::clear()
{
    found_cim_element = false;

    CIM_CIMVERSION.minor = 0;
    CIM_CIMVERSION.major = 0;

    CIM_DTDVERSION.minor = 0;
    CIM_DTDVERSION.major = 0;

    MESSAGE_ID[0] = '\0';

    MESSAGE_PROTOCOLVERSION.minor = 0;
    MESSAGE_PROTOCOLVERSION.major = 0;

    IMETHODRESPONSE_NAME[0] = '\0';

    for (size_t i = 0; i < instance_names.size(); i++)
        destroy(instance_names[i]);

    instance_names.clear();

    for (size_t i = 0; i < instances.size(); i++)
        destroy(instances[i]);

    instances.clear();

    // Error information:
    error = false;
    code = Exception::FAILED;
    message[0] = '\0';
}

void CIMXML_Context::print() const
{
    printf("CIMXML_Context:\n");
    printf("  CIM_CIMVERSION: %u.%u\n", 
        CIM_CIMVERSION.major, CIM_CIMVERSION.minor);
    printf("  CIM_DTDVERSION: %u.%u\n",
        CIM_DTDVERSION.major, CIM_DTDVERSION.minor);
    printf("  MESSAGE_ID: %s\n", MESSAGE_ID);
    printf("  MESSAGE_PROTOCOLVERSION: %u.%u\n",
        MESSAGE_PROTOCOLVERSION.major, MESSAGE_PROTOCOLVERSION.minor);
    printf("  IMETHODRESPONSE_NAME: %s\n", IMETHODRESPONSE_NAME);
}

//==============================================================================
//
// class CIMXML_Parser
//
//==============================================================================

CIMXML_Parser::CIMXML_Parser(const Meta_Repository* mr) : _mr(mr), _mc(0)
{
}

CIMXML_Parser::~CIMXML_Parser()
{
    // Cleanup instances stack:

    while (_instances.size())
    {
        destroy(_instances.top().instance);
        _instances.pop();
    }
}

void CIMXML_Parser::handle_start_element(const char* el, const char** attrs)
{
    // Convert tag name to integer:

    Tag tag = _name_to_tag(el);

    // Verifty that parent can have an element of this type.

    if (!_tags.empty())
    {
        const char* children = _children[_tags.top()];

        if (!children || strchr(children, tag) == 0)
        {
            raise("\"%s\" is not a valid subelement of \"%s\"", 
                el, _tag_names[_tags.top()]);
            return;
        }
    }

    // Reject non-CIM root elements:

// ATTN: this fails in case in which root is INSTANCE.
#if 0

    if (_tags.empty() && tag != TAG_CIM)
    {
        raise("expected CIM root element but encountered %s instead", el);
        return;
    }

#endif

    // Dispatch element handler:

    switch (tag)
    {
        case TAG_CIM:
            _start_CIM(attrs);
            break;

        case TAG_MESSAGE:
            _start_MESSAGE(attrs);
            break;

        case TAG_SIMPLERSP:
            _start_SIMPLERSP(attrs);
            break;

        case TAG_IMETHODRESPONSE:
            _start_IMETHODRESPONSE(attrs);
            break;

        case TAG_IRETURNVALUE:
            _start_IRETURNVALUE(attrs);
            break;

        case TAG_VALUE_NAMEDINSTANCE:
            _start_VALUE_NAMEDINSTANCE(attrs);
            break;

        case TAG_INSTANCENAME:
            _start_INSTANCENAME(attrs);
            break;

        case TAG_INSTANCE:
            _start_INSTANCE(attrs);
            break;

        case TAG_PROPERTY:
            _start_PROPERTY(attrs);
            break;

        case TAG_PROPERTY_ARRAY:
            _start_PROPERTY_ARRAY(attrs);
            break;

        case TAG_PROPERTY_REFERENCE:
            _start_PROPERTY_REFERENCE(attrs);
            break;

        case TAG_VALUE:
            _start_VALUE(attrs);
            break;

        case TAG_VALUE_ARRAY:
            _start_VALUE_ARRAY(attrs);
            break;

        case TAG_VALUE_REFERENCE:
            _start_VALUE_REFERENCE(attrs);
            break;

        case TAG_KEYBINDING:
            _start_KEYBINDING(attrs);
            break;

        case TAG_KEYVALUE:
            _start_KEYVALUE(attrs);
            break;

        case TAG_LOCALINSTANCEPATH:
            _start_LOCALINSTANCEPATH(attrs);
            break;

        case TAG_LOCALNAMESPACEPATH:
            _start_LOCALNAMESPACEPATH(attrs);
            break;

        case TAG_NAMESPACE:
            _start_NAMESPACE(attrs);
            break;

        case TAG_ERROR:
            _start_ERROR(attrs);
            break;

        default:
        {
            CIMPLE_WARN(("ignored unknown element: %s", _tag_names[tag]));
            break;
        }
    }

    // Push tag:

    _tags.push(tag);
}

void CIMXML_Parser::handle_end_element(const char* el)
{
    // Convert tag to integer:

    Tag tag = _name_to_tag(el);

    // Pop this element:

    if (_tags.empty())
    {
        raise("tag stack underflow");
        return;
    }

    _tags.pop();

    // Dispatch element handler:

    switch (tag)
    {
        case TAG_NULL:
            raise("unknown end element type: %s", el);
            break;

        case TAG_CIM:
            _end_CIM();
            break;

        case TAG_MESSAGE:
            _end_MESSAGE();
            break;

        case TAG_SIMPLERSP:
            _end_SIMPLERSP();
            break;

        case TAG_IMETHODRESPONSE:
            _end_IMETHODRESPONSE();
            break;

        case TAG_IRETURNVALUE:
            _end_IRETURNVALUE();
            break;

        case TAG_VALUE_NAMEDINSTANCE:
            _end_VALUE_NAMEDINSTANCE();
            break;

        case TAG_INSTANCENAME:
            _end_INSTANCENAME();
            break;

        case TAG_INSTANCE:
            _end_INSTANCE();
            break;

        case TAG_PROPERTY:
            _end_PROPERTY();
            break;

        case TAG_PROPERTY_ARRAY:
            _end_PROPERTY_ARRAY();
            break;

        case TAG_PROPERTY_REFERENCE:
            _end_PROPERTY_REFERENCE();
            break;

        case TAG_VALUE:
            _end_VALUE();
            break;

        case TAG_VALUE_ARRAY:
            _end_VALUE_ARRAY();
            break;

        case TAG_VALUE_REFERENCE:
            _end_VALUE_REFERENCE();
            break;

        case TAG_KEYBINDING:
            _end_KEYBINDING();
            break;

        case TAG_KEYVALUE:
            _end_KEYVALUE();
            break;

        case TAG_LOCALINSTANCEPATH:
            _end_LOCALINSTANCEPATH();
            break;

        case TAG_LOCALNAMESPACEPATH:
            _end_LOCALNAMESPACEPATH();
            break;

        case TAG_NAMESPACE:
            _end_NAMESPACE();
            break;

        case TAG_ERROR:
            _end_ERROR();
            break;

        default:
            // Unknown elements.
            break;
    }
}

void CIMXML_Parser::handle_character_data(const char* s, int len)
{
    if (_top() == TAG_VALUE || _top() == TAG_KEYVALUE)
    {
        _char_data.append(s, len);
    }
}

int CIMXML_Parser::_find_required_attr(
    const char** attrs, 
    const char* name, 
    const char*& value)
{
    value = _find_attr(attrs, name);

    if (!value)
    {
        raise("missing required %s attribute", name);
        return -1;
    }

    return 0;
}

int CIMXML_Parser::_find_version_attr(
    const char** attrs, 
    const char* name, 
    Version& version)
{
    const char* value;

    if (_find_required_attr(attrs, name, value) != 0)
        return -1;

    if (_parse_version(version, value) != 0)
    {
        raise("invalid %s attribute: %s", name, value);
        return -1;
    }

    return 0;
}

int CIMXML_Parser::_find_fixed_str_attr(
    const char** attrs, 
    const char* name, 
    char str[CIMXML_STRING_SIZE])
{
    const char* value;

    if (_find_required_attr(attrs, name, value) != 0)
        return -1;

    if (strlen(value) >= CIMXML_STRING_SIZE)
    {
        raise("%s attribute value too long", name);
        return -1;
    }

    strcpy(str, value);
    return 0;
}

int CIMXML_Parser::_find_type_attr(
    const char** attrs, 
    const char* name, 
    Type& type)
{
    const char* value;

    if (_find_required_attr(attrs, name, value) != 0)
        return -1;

    if (type_name_to_type(value, type) != 0)
    {
        raise("bad value %s attribute: %s", name, value);
        return -1;
    }

    return 0;
}

int CIMXML_Parser::_find_uint32_attr(
    const char** attrs, 
    const char* name, 
    uint32& x)
{
    const char* value;

    if (_find_required_attr(attrs, name, value) != 0)
        return -1;

    if (str_to_uint32(value, x) != 0)
    {
        raise("bad value %s attribute: %s", name, value);
        return -1;
    }

    return 0;
}

int CIMXML_Parser::_resolve_meta_class(const char* name, const Meta_Class*& mc)
{
    mc = find_meta_class(_mr, name);

    if (mc)
        return 0;

    if (_instances.empty())
    {
        if (!_mc)
            return -1;

        mc = _mc;
        return 0;
    }

    Working_Instance& wi = _instances.top();

    if (wi.mf && (wi.mf->flags & CIMPLE_FLAG_REFERENCE))
    {
        const Meta_Reference* mr = (const Meta_Reference*)wi.mf;
        mc = mr->meta_class;
        return 0;
    }

    raise("failed to find meta class for \"%s\"", name);
    return -1;
}

void CIMXML_Parser::_start_CIM(const char** attrs)
{
    // Check whether CIM element encountered.

    if (_ctx.found_cim_element)
    {
        raise("encountered multiple CIM elements");
        return;
    }

    _ctx.found_cim_element = true;

    // CIM must be root element:

    if (!_tags.empty())
    {
        raise("CIM must be root element");
        return;
    }

    // CIM.DTDVERSION:

    if (_find_version_attr(attrs, "DTDVERSION", _ctx.CIM_DTDVERSION) != 0)
        return;

    // CIM.CIMVERSION:

    if (_find_version_attr(attrs, "CIMVERSION", _ctx.CIM_CIMVERSION) != 0)
        return;
}

void CIMXML_Parser::_end_CIM()
{
}

void CIMXML_Parser::_start_MESSAGE(const char** attrs)
{
    // MESSAGE.ID:

    if (_find_fixed_str_attr(attrs, "ID", _ctx.MESSAGE_ID) != 0)
        return;

    // MESSAGE.PROTOCOLVERSION:

    if (_find_version_attr(
        attrs, "PROTOCOLVERSION", _ctx.MESSAGE_PROTOCOLVERSION) != 0)
    {
        return;
    }
}

void CIMXML_Parser::_end_MESSAGE()
{
}

void CIMXML_Parser::_start_SIMPLERSP(const char** attrs)
{
}

void CIMXML_Parser::_end_SIMPLERSP()
{
}

void CIMXML_Parser::_start_IMETHODRESPONSE(const char** attrs)
{
    if (_find_fixed_str_attr(attrs, "NAME", _ctx.IMETHODRESPONSE_NAME) != 0)
        return;
}

void CIMXML_Parser::_end_IMETHODRESPONSE()
{
}

void CIMXML_Parser::_start_IRETURNVALUE(const char** attrs)
{
}

void CIMXML_Parser::_end_IRETURNVALUE()
{
}

void CIMXML_Parser::_start_VALUE_NAMEDINSTANCE(const char** attrs)
{
}

void CIMXML_Parser::_end_VALUE_NAMEDINSTANCE()
{
}

void CIMXML_Parser::_start_INSTANCENAME(const char** attrs)
{
    // INSTANCENAME.CLASSNAME:

    const char* classname;
    
    if (_find_required_attr(attrs, "CLASSNAME", classname) != 0)
        return;

    // Find the meta class:

    const Meta_Class* mc;
    
    if (_resolve_meta_class(classname, mc) != 0)
    {
        raise("failed to resolve meta class for %s", classname);
        return;
    }

    // Create the working instance:

    Instance* instance = create(mc);
    CIMXML_ASSUME(instance != 0);
    nullify_properties(instance);

    // Fill in the namespace if any:

    if (!_instances.empty())
    {
        const Working_Instance& wi = _instances.top();

        if (*wi.name_space)
            instance->__name_space = wi.name_space;
    }

    _instances.push(Working_Instance(instance));
}

void CIMXML_Parser::_end_INSTANCENAME()
{
    if (_instances.empty())
        return;

#if 0
    print(_instances.top().instance, true);
#endif

    if (_instances.size() > 1)
    {
        // Get instance at top and pop:

        Instance* instance = _instances.top().instance;
        _instances.pop();

        // Set instance into parent reference feature.

        Working_Instance& wi = _instances.top();

        if (!wi.mf)
        {
            raise("%s(%u): missing meta feature", __FILE__, __LINE__);
            return;
        }

        if (wi.mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)wi.mf;
            *((Instance**)((uint8*)wi.instance + mr->offset)) =
                instance;
        }
    }
    else
    {
        // Add instance to context.
        _ctx.instance_names.append(_instances.top().instance);
        _instances.pop();
    }
}

void CIMXML_Parser::_start_INSTANCE(const char** attrs)
{
    // INSTANCE.CLASSNAME:

    const char* classname;

    if (_find_required_attr(attrs, "CLASSNAME", classname) != 0)
        return;

    // Find the meta class:

    const Meta_Class* mc;
    
    if (_resolve_meta_class(classname, mc) != 0)
    {
        raise("failed to resolve meta class for %s", classname);
        return;
    }

    // Create the working instance:

    Instance* instance = create(mc);
    CIMXML_ASSUME(instance != 0);
    nullify_properties(instance);

    if (!_instances.empty())
    {
        const Working_Instance& wi = _instances.top();

        if (*wi.name_space)
            instance->__name_space = wi.name_space;
    }

    _instances.push(Working_Instance(instance));
}

void CIMXML_Parser::_end_INSTANCE()
{
    if (_instances.empty())
        return;

#if 0
    print(_instances.top().instance, false);
#endif

    if (_instances.size() > 1)
    {
        // Get instance at top and pop:

        Instance* instance = _instances.top().instance;
        _instances.pop();

        // Set instance into parent reference feature.

        Working_Instance& wi = _instances.top();

        if (!wi.mf)
        {
            raise("%s(%u): missing meta feature", __FILE__, __LINE__);
            return;
        }

        if (wi.mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)wi.mf;
            *((Instance**)((uint8*)wi.instance + mr->offset)) =
                instance;
        }
        else
            cimple::unref(instance);
    }
    else
    {
        // Add instance to context.
        _ctx.instances.append(_instances.top().instance);
        _instances.pop();
    }
}

void CIMXML_Parser::_start_PROPERTY(const char** attrs)
{
    CIMXML_ASSUME(!_instances.empty());

    // NAME attribute:

    const char* name;

    if (_find_required_attr(attrs, "NAME", name) != 0)
        return;

    // TYPE attribute:

    Type type;

    if (_find_type_attr(attrs, "TYPE", type) != 0)
        return;

    // Set current meta feature.

    Working_Instance& wi = _instances.top();
    CIMXML_ASSUME(wi.instance != 0);

    wi.mf = find_feature(wi.instance->meta_class, name,
        CIMPLE_FLAG_PROPERTY | CIMPLE_FLAG_REFERENCE);
}

void CIMXML_Parser::_end_PROPERTY()
{
    if (!_instances.empty())
        _instances.top().reset();
}

void CIMXML_Parser::_start_KEYBINDING(const char** attrs)
{
    CIMXML_ASSUME(!_instances.empty());

    // NAME attribute:

    const char* name;

    if (_find_required_attr(attrs, "NAME", name) != 0)
        return;

    // Set current meta feature:

    Working_Instance& wi = _instances.top();
    CIMXML_ASSUME(wi.instance != 0);

    wi.mf = find_feature(wi.instance->meta_class, name,
        CIMPLE_FLAG_PROPERTY | CIMPLE_FLAG_REFERENCE);
}

void CIMXML_Parser::_end_KEYBINDING()
{
    if (!_instances.empty())
        _instances.top().reset();
}

void CIMXML_Parser::_start_PROPERTY_ARRAY(const char** attrs)
{
    CIMXML_ASSUME(!_instances.empty());

    // NAME attribute:

    const char* name;

    if (_find_required_attr(attrs, "NAME", name) != 0)
        return;

    // TYPE attribute:

    Type type;

    if (_find_type_attr(attrs, "TYPE", type) != 0)
        return;

    // Set current meta feature:

    Working_Instance& wi = _instances.top();
    CIMXML_ASSUME(wi.instance != 0);

    wi.mf = find_feature(wi.instance->meta_class, name,
        CIMPLE_FLAG_PROPERTY | CIMPLE_FLAG_REFERENCE);
}

void CIMXML_Parser::_end_PROPERTY_ARRAY()
{
    if (!_instances.empty())
        _instances.top().reset();
}

void CIMXML_Parser::_start_PROPERTY_REFERENCE(const char** attrs)
{
    CIMXML_ASSUME(!_instances.empty());

    // NAME attribute:

    const char* name;

    if (_find_required_attr(attrs, "NAME", name) != 0)
        return;

    // Set current meta feature:

    Working_Instance& wi = _instances.top();
    CIMXML_ASSUME(wi.instance != 0);

    wi.mf = find_feature(wi.instance->meta_class, name,
        CIMPLE_FLAG_PROPERTY | CIMPLE_FLAG_REFERENCE);
}

void CIMXML_Parser::_end_PROPERTY_REFERENCE()
{
    if (!_instances.empty())
        _instances.top().reset();
}

void CIMXML_Parser::_start_VALUE(const char** attrs)
{
    _char_data.clear();
}

void CIMXML_Parser::_end_VALUE()
{
    if (_instances.empty())
        return;

    const Working_Instance& wi = _instances.top();

    if (!wi.mf)
    {
        _char_data.clear();
        return;
    }

    const char* value = _char_data.c_str();

    if (wi.mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)wi.mf;
        const Meta_Class* mc =  wi.instance->meta_class;

        if (__put_property_from_str(wi.instance, mp, value) != 0)
        {
            raise("bad value for %s.%s: %s", mc->name, mp->name, value);
            return;
        }
    }
    else if (wi.mf->flags & CIMPLE_FLAG_REFERENCE)
    {
        const Meta_Reference* mr = (const Meta_Reference*)wi.mf;

        // Handle embedded instances and embedded objects.

        if (mr->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE ||
            mr->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
        {
            CIMXML_Parser parser(_mc->meta_repository);
            parser.meta_class(mr->meta_class);

            if (parser.parse(value, strlen(value)) != 0)
            {
                raise("%s", parser.error_msg().c_str());
                return;
            }

            const CIMXML_Context& ctx = parser.context();

            if (ctx.instances.size())
            {
                Instance* instance = ctx.instances[0];
                CIMPLE_ASSERT(instance);
                cimple::ref(instance);
                *((Instance**)((uint8*)wi.instance + mr->offset)) = instance;
            }
        }
    }

    _char_data.clear();
}

void CIMXML_Parser::_start_VALUE_ARRAY(const char** attrs)
{
}

void CIMXML_Parser::_end_VALUE_ARRAY()
{
}

void CIMXML_Parser::_start_VALUE_REFERENCE(const char** attrs)
{
}

void CIMXML_Parser::_end_VALUE_REFERENCE()
{
}

void CIMXML_Parser::_start_KEYVALUE(const char** attrs)
{
    _char_data.clear();

    // KEYVALUE.VALUETYPE:

    const char* valuetype;

    if (_find_required_attr(attrs, "VALUETYPE", valuetype) != 0)
        return;
}

void CIMXML_Parser::_end_KEYVALUE()
{
    if (_instances.empty())
        return;

    const Working_Instance& wi = _instances.top();

    if (wi.mf && wi.mf->flags & CIMPLE_FLAG_PROPERTY)
    {
        const Meta_Property* mp = (const Meta_Property*)wi.mf;
        const Meta_Class* mc = wi.instance->meta_class;
        const char* value = _char_data.c_str();

        if (__put_property_from_str(wi.instance, mp, value) != 0)
        {
            raise("bad value for %s.%s: %s", mc->name, mp->name, value);
            return;
        }
    }

    _char_data.clear();
}

void CIMXML_Parser::_start_LOCALINSTANCEPATH(const char** attrs)
{
}

void CIMXML_Parser::_end_LOCALINSTANCEPATH()
{
}

void CIMXML_Parser::_start_LOCALNAMESPACEPATH(const char** attrs)
{
}

void CIMXML_Parser::_end_LOCALNAMESPACEPATH()
{
}

void CIMXML_Parser::_start_NAMESPACE(const char** attrs)
{
}

void CIMXML_Parser::_end_NAMESPACE()
{
}

void CIMXML_Parser::_start_ERROR(const char** attrs)
{
    // ERROR.CODE:

    uint32 code;

    if (_find_uint32_attr(attrs, "CODE", code) != 0)
        return;

    // ERROR.DESCRIPTION:

    const char* description = _find_attr(attrs, "DESCRIPTION");

    // Check code:

    _ctx.error = true;

    if (Exception::valid_cim_code(code))
        _ctx.code = Exception::Code(code);
    else
        _ctx.code = Exception::FAILED;

    if (description)
        strlcpy(_ctx.message, description, CIMXML_STRING_SIZE);
}

void CIMXML_Parser::_end_ERROR()
{
}

CIMPLE_NAMESPACE_END
