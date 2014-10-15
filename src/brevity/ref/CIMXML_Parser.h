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

#ifndef _brevity_CIMXML_Parser_h
#define _brevity_CIMXML_Parser_h

#include <cimple/cimple.h>
#include "linkage.h"
#include "XML_Parser.h"

#define CIMXML_STRING_SIZE 256

CIMPLE_NAMESPACE_BEGIN

struct Version
{
    uint8 major;
    uint8 minor;
};

enum Tag
{
    TAG_NULL = 0,
    TAG_CIM,
    TAG_DECLARATION,
    TAG_DECLGROUP,
    TAG_DECLGROUP_WITHNAME,
    TAG_DECLGROUP_WITHPATH,
    TAG_QUALIFIER_DECLARATION,
    TAG_SCOPE,
    TAG_VALUE,
    TAG_VALUE_ARRAY,
    TAG_VALUE_REFERENCE,
    TAG_VALUE_REFARRAY,
    TAG_VALUE_OBJECT,
    TAG_VALUE_NAMEDINSTANCE,
    TAG_VALUE_NAMEDOBJECT,
    TAG_VALUE_OBJECTWITHLOCALPATH,
    TAG_VALUE_OBJECTWITHPATH,
    TAG_VALUE_NULL,
    TAG_NAMESPACEPATH,
    TAG_LOCALNAMESPACEPATH,
    TAG_HOST,
    TAG_NAMESPACE,
    TAG_CLASSPATH,
    TAG_LOCALCLASSPATH,
    TAG_CLASSNAME,
    TAG_INSTANCEPATH,
    TAG_LOCALINSTANCEPATH,
    TAG_INSTANCENAME,
    TAG_OBJECTPATH,
    TAG_KEYBINDING,
    TAG_KEYVALUE,
    TAG_CLASS,
    TAG_INSTANCE,
    TAG_QUALIFIER,
    TAG_PROPERTY,
    TAG_PROPERTY_ARRAY,
    TAG_PROPERTY_REFERENCE,
    TAG_METHOD,
    TAG_PARAMETER,
    TAG_PARAMETER_REFERENCE,
    TAG_PARAMETER_ARRAY,
    TAG_PARAMETER_REFARRAY,
    TAG_TABLECELL_DECLARATION,
    TAG_TABLECELL_REFERENCE,
    TAG_TABLEROW_DECLARATION,
    TAG_TABLE,
    TAG_TABLEROW,
    TAG_MESSAGE,
    TAG_MULTIREQ,
    TAG_MULTIEXPREQ,
    TAG_SIMPLEREQ,
    TAG_SIMPLEEXPREQ,
    TAG_IMETHODCALL,
    TAG_METHODCALL,
    TAG_EXPMETHODCALL,
    TAG_PARAMVALUE,
    TAG_IPARAMVALUE,
    TAG_EXPPARAMVALUE,
    TAG_MULTIRSP,
    TAG_MULTIEXPRSP,
    TAG_SIMPLERSP,
    TAG_SIMPLEEXPRSP,
    TAG_METHODRESPONSE,
    TAG_EXPMETHODRESPONSE,
    TAG_IMETHODRESPONSE,
    TAG_ERROR,
    TAG_RETURNVALUE,
    TAG_IRETURNVALUE,
    TAG_RESPONSEDESTINATION,
    TAG_SIMPLEREQACK,
    __TAG_NUM_TAGS,
};

struct CIMXML_Context
{
    bool found_cim_element;
    Version CIM_CIMVERSION;
    Version CIM_DTDVERSION;
    char MESSAGE_ID[CIMXML_STRING_SIZE];
    Version MESSAGE_PROTOCOLVERSION;
    char IMETHODRESPONSE_NAME[CIMXML_STRING_SIZE];
    Array<Instance*> instance_names;
    Array<Instance*> instances;

    // Error information:
    bool error;
    Exception::Code code;
    char message[CIMXML_STRING_SIZE];

    CIMXML_Context();
    void clear();
    void print() const;
};

// The current object being parsed, which may represent an intance or an
// instance name. Objects are "initiated" by INSTANCE and INSTANCENAME
// elements.
struct Working_Instance
{
    // Instance or instance name:
    Instance* instance;

    // Current feature under construction:
    const Meta_Feature* mf;
    const Meta_Class* mc;
    char name_space[CIMXML_STRING_SIZE];

    Working_Instance(Instance* instance_) : instance(instance_), mf(0), mc(0) 
    {
        *name_space = '\0';
    }

    void reset()
    {
        mf = 0;
        mc = 0;
        *name_space = '\0';
    }

    friend bool operator==(const Working_Instance&, const Working_Instance&) 
    { 
        return false; 
    }
};

template<> struct __Array_Traits_Factory<Working_Instance> :
    public __Array_Traits_Factory_Raw<Working_Instance> { };

class CIMPLE_BREVITY_LINKAGE CIMXML_Parser : public XML_Parser
{
public:

    CIMXML_Parser(const Meta_Repository* mr);

    virtual ~CIMXML_Parser();

    virtual void handle_start_element(const char* el, const char** attrs);

    virtual void handle_end_element(const char* el);

    virtual void handle_character_data(const char* s, int len);

    CIMXML_Context& context() { return _ctx; }

    void meta_class(const Meta_Class* mc) { _mc = mc; }

private:

    CIMXML_Parser(const CIMXML_Parser& x);

    CIMXML_Parser& operator=(const CIMXML_Parser& x);

    Tag _top() const
    {
        return _tags.size() ? _tags.top() : TAG_NULL;
    }

    int _find_required_attr(
        const char** attrs, 
        const char* name, 
        const char*& value);

    int _find_version_attr(
        const char** attrs, 
        const char* name, 
        Version& version);

    int _find_fixed_str_attr(
        const char** attrs, 
        const char* name, 
        char str[CIMXML_STRING_SIZE]);

    int _find_uint32_attr(
        const char** attrs, 
        const char* name, 
        uint32& x);

    int _find_type_attr(const char** attrs, const char* name, Type& type);

    int _resolve_meta_class(const char* name, const Meta_Class*& mc);

    void _start_CIM(const char** attrs);

    void _end_CIM();

    void _start_MESSAGE(const char** attrs);

    void _end_MESSAGE();

    void _start_SIMPLERSP(const char** attrs);

    void _end_SIMPLERSP();

    void _start_IMETHODRESPONSE(const char** attrs);

    void _end_IMETHODRESPONSE();

    void _start_IRETURNVALUE(const char** attrs);

    void _end_IRETURNVALUE();

    void _start_VALUE_NAMEDINSTANCE(const char** attrs);

    void _end_VALUE_NAMEDINSTANCE();

    void _start_INSTANCENAME(const char** attrs);

    void _end_INSTANCENAME();

    void _start_INSTANCE(const char** attrs);

    void _end_INSTANCE();

    void _start_PROPERTY(const char** attrs);

    void _end_PROPERTY();

    void _start_PROPERTY_ARRAY(const char** attrs);

    void _end_PROPERTY_ARRAY();

    void _start_PROPERTY_REFERENCE(const char** attrs);

    void _end_PROPERTY_REFERENCE();

    void _start_VALUE(const char** attrs);

    void _end_VALUE();

    void _start_VALUE_ARRAY(const char** attrs);

    void _end_VALUE_ARRAY();

    void _start_VALUE_REFERENCE(const char** attrs);

    void _end_VALUE_REFERENCE();

    void _start_KEYBINDING(const char** attrs);

    void _end_KEYBINDING();

    void _start_KEYVALUE(const char** attrs);

    void _end_KEYVALUE();

    void _start_LOCALINSTANCEPATH(const char** attrs);

    void _end_LOCALINSTANCEPATH();

    void _start_LOCALNAMESPACEPATH(const char** attrs);

    void _end_LOCALNAMESPACEPATH();

    void _start_NAMESPACE(const char** attrs);

    void _end_NAMESPACE();

    void _start_ERROR(const char** attrs);

    void _end_ERROR();

    const Meta_Repository* _mr;
    const Meta_Class* _mc;
    String _char_data;
    Stack<Tag> _tags;
    CIMXML_Context _ctx;

    Stack<Working_Instance> _instances;
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_CIMXML_Parser_h */
