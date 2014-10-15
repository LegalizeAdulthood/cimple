/*
**==============================================================================
**
** Copyright (c) 2003 - 2008, Michael Brasher, Karl Schopmeyer
** Copyright (c) 2007 - 2011 Inova Development Inc.
** Copyright (c) 2009 - 2011 Karl Schopmeyer
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

// Truncated debugger symbols.

#include <cimple/config.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <unistd.h>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <set>
#include <cstdarg>
#include <string>
#include <util/util.h>
#include <tools/gencommon/gencommon.h>
#include "usage.h"
#include <mof/MOF_Parser.h>
#include <mof/MOF_Options.h>

using namespace std;

const char* arg0;
static FILE* _os = 0;
static bool linkage_opt = false;
static bool enum_opt = false;
static bool gen_repository_opt = false;
static bool schema_opt = false;
static bool qualifier_opt = false;
static bool descriptions_opt = false;
static bool boolean_qualifiers_opt = false;
static string class_list_file;
static bool sources_opt = false;
static bool verbose_opt = false;

string meta_repository_name;

/*******************************************************************************
**
**  create the CRC for a class.
**
*******************************************************************************/
// ATTN: do we need to implement qualifiers for parameters?
// ATTN: optimize out empty Meta_Qualifier arrays (MQAs).

char data_type_tag(int data_type)
{
    switch (data_type)
    {
        case TOK_BOOLEAN:
            return 'O';
        case TOK_UINT8:
            return 'B';
        case TOK_SINT8:
            return 'b';
        case TOK_UINT16:
            return 'S';
        case TOK_SINT16:
            return 's';
        case TOK_UINT32:
            return 'I';
        case TOK_SINT32:
            return 'i';
        case TOK_UINT64:
            return 'L';
        case TOK_SINT64:
            return 'l';
        case TOK_REAL32:
            return 'F';
        case TOK_REAL64:
            return 'D';
        case TOK_CHAR16:
            return 'C';
        case TOK_STRING:
            return 'Z';
        case TOK_DATETIME:
            return 'T';
        default:
            assert(0);
    }

    return 0;
}

void put_qual_sig(int qual_mask, string& sig)
{
    string tmp;

    if (qual_mask & MOF_QT_KEY)
        tmp += 'K';

    if (qual_mask & MOF_QT_EMBEDDEDOBJECT)
        tmp += 'E';

    if (qual_mask & MOF_QT_STATIC)
        tmp += 'S';

    if (qual_mask & MOF_QT_IN)
        tmp += 'I';

    if (qual_mask & MOF_QT_OUT)
        tmp += 'O';

    if (tmp.size())
    {
        sig += '[';
        sig += tmp;
        sig += ']';
    }
}

void put_data_type_sig(int data_type, int array_index, string& sig)
{
    // Subscript:

    if (array_index == -1)
        sig += "@";
    else if (array_index > 0)
    {
        char buffer[16];
        sprintf(buffer, "@%d", array_index);
        sig += buffer;
    }

    // Type:

    sig += data_type_tag(data_type);
}

void make_signature(const MOF_Class_Decl* cd, string& sig)
{
    sig.erase(sig.begin(), sig.end());

    // Object type tag: [A]ssociation, [I]ndication, [C]lass.

    if (cd->qual_mask & MOF_QT_ASSOCIATION)
        sig += 'A';
    else if (cd->qual_mask & MOF_QT_INDICATION)
        sig += 'N';
    else
        sig += 'C';

    // Class name:

    sig += cd->name;

    // Super class name:

    if (cd->super_class_name)
    {
        sig += ';';
        sig += cd->super_class_name;
    }

    sig += '\n';

    // Class features:

    MOF_Feature_Info* p = cd->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* f = p->feature;

        // The next character written is a tag which represents the data type.
        // It will be one of the following:
        //
        //     'O' - boolean
        //     'B' - uint8 (unsigned byte)
        //     'b' - sint8 (signed byte)
        //     'S' - uint16 (unsigned short)
        //     's' - sint16 (signed short)
        //     'I' - uint32 (unsigned integer)
        //     'i' - sint32 (sint32 integer)
        //     'L' - uint64 (unsigned long)
        //     'l' - sint64 (singed long)
        //     'F' - real32 (float)
        //     'D' - real64 (double)
        //     'C' - char16
        //     'Z' - string
        //     'T' - datetime
        //     'R' - reference
        //     'M' - method

        // Property:

        MOF_Property_Decl* prop = dynamic_cast<MOF_Property_Decl*>(f);

        if (prop)
        {
            // Qualifiers:

            put_qual_sig(
                prop->qual_mask & (MOF_QT_EMBEDDEDOBJECT|MOF_QT_KEY), sig);

            // Type:

            put_data_type_sig(prop->data_type, prop->array_index, sig);

            // Name:

            sig += f->name;

            sig += '\n';
        }

        // Reference:

        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(f);

        if (ref)
        {
            // Qualifiers:

            put_qual_sig(ref->qual_mask & MOF_QT_KEY, sig);

            sig += 'R';
            sig += ref->class_name;
            sig += ';';
            sig += ref->name;
            sig += '\n';
        }

        // Method:

        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(f);

        if (meth)
        {
            put_qual_sig(meth->qual_mask & MOF_QT_STATIC, sig);

            sig += 'M';
            sig += data_type_tag(meth->data_type);
            sig += meth->name;
            sig += ';';

            MOF_Parameter* param = meth->parameters;

            for (; param; param = (MOF_Parameter*)param->next)
            {
                // Qualifiers:

                put_qual_sig(param->qual_mask & (MOF_QT_IN|MOF_QT_OUT), sig);

                // Data type:

                if (param->data_type == TOK_REF)
                {
                    sig += 'R';
                    sig += param->ref_name;
                    sig += ';';
                }
                else
                {
                    put_data_type_sig(
                        param->data_type, param->array_index, sig);
                }

                // Param name:

                sig += param->name;
                sig += ';';
            }

            sig += "\n";
        }
    }
}

/*******************************************************************************
**
**
**
*******************************************************************************/

void print(vector<string>& array)
{
    for (size_t i = 0; i < array.size(); i++)
        printf("[%s]\n", array[i].c_str());
}

void nl()
{
    fputc('\n', _os);
}

// vfprintf the formatted input definition.  out uses the va print structure
// to format the variable number of inputs and outputs to the stream defined
// by _os
static
CIMPLE_PRINTF_ATTR(1, 2)
void out(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(_os, format, ap);
    va_end(ap);
}


static void _print_include_paths()
{
    if (MOF_num_include_paths == 0)
        printf("No MOF_include_paths\n");
    else
        for (size_t i = 0; i < MOF_num_include_paths; i++)
            printf("MOF_include_paths[%u]=\"%s\"\n", (int)i,
            MOF_include_paths[i]);
}


static inline const char* _to_string(int data_type)
{
    if (data_type == TOK_STRING)
        return "String";
    else if (data_type == TOK_DATETIME)
        return "Datetime";

    return MOF_Data_Type::to_string(data_type);
}

string normalize_value_qual_name(const char* name)
{
    string r;

    for (const char* p = name; *p; p++)
    {
        if (isalnum(*p) || *p == '_')
            r += *p;
        else
            r += '_';
    }

    return r;
}

void str_literal_out(const char* str)
{
    out("\"");

    while (*str)
    {
        char c = *str++;

        switch (c)
        {
            case '\n':
                out("\\n");
                break;

            case '\r':
                out("\\r");
                break;

            case '\t':
                out("\\t");
                break;

            case '\f':
                out("\\f");
                break;

            case '"':
                out("\\\"");
                break;

            default:
                out("%c", c);
        }
    }

    out("\"");
}

void int_literal_out(const MOF_Literal* ml, const char* x)
{
    out(("%s(" CIMPLE_LLD  ")"), x, ml->int_value);
}

/*
    Output the literal value converted to string
    Note that sin64 and uint64 get wrapped in a macro because
    of issues with the literal constant definitions in the compilers
    i.e suffixes
*/
void literal_out(const MOF_Literal* ml, int data_type)
{
    switch (ml->value_type)
    {
        case TOK_INT_VALUE:
            // Some integer types need suffixing to avoid compiler
            // issues. Add the suffixes as defined by the
            // macros in config.h
            switch(data_type)
            {
                case TOK_SINT64:
                    int_literal_out(ml, "CIMPLE_SINT64_LITERAL");
                    break;

                case TOK_UINT64:
                    int_literal_out(ml, "CIMPLE_UINT64_LITERAL");
                    break;

                case TOK_UINT32:
                    int_literal_out(ml, "CIMPLE_UINT32_LITERAL");
                    break;

                case TOK_SINT32:
                    int_literal_out(ml, "CIMPLE_SINT32_LITERAL");
                    break;

                default:
                    out(CIMPLE_LLD, ml->int_value);
    
            }
            break;

        case TOK_REAL_VALUE:
            out("%f", ml->real_value);
            break;

        case TOK_CHAR_VALUE:
            out("%u", ml->char_value);
            break;

        case TOK_BOOL_VALUE:
            out("%s", ml->bool_value ? "true" : "false");
            break;

        case TOK_STRING_VALUE:
            str_literal_out(ml->string_value);
            break;

        default:
            assert(0);
    }
}

//==============================================================================
//
// _literal_type_name()
//
//==============================================================================

static const char* _literal_type_name(int data_type)
{
    switch (data_type)
    {
        case TOK_BOOLEAN:
            return "boolean";
        case TOK_UINT8:
            return "uint8";
        case TOK_SINT8:
            return "sint8";
        case TOK_UINT16:
            return "uint16";
        case TOK_SINT16:
            return "sint16";
        case TOK_UINT32:
            return "uint32";
        case TOK_SINT32:
            return "sint32";
        case TOK_UINT64:
            return "uint64";
        case TOK_SINT64:
            return "sint64";
        case TOK_REAL32:
            return "real32";
        case TOK_REAL64:
            return "real64";
        case TOK_CHAR16:
            return "char16";
        case TOK_STRING:
            return "const char*";
        case TOK_DATETIME:
            return "const char*";
    }

    // Unreachable
    return 0;
}

//==============================================================================
//
// gen_value_scalar_def()
//
//     Generate a Meta_Value_Scalar<> definition.
//
//==============================================================================

void gen_value_scalar_def(
    const char* class_name,
    const char* feature_name, /* can be null */
    const char* qualifier_name, /* can be null */
    int mof_data_type,
    const MOF_Literal* mof_literal)
{
    assert(mof_literal != 0);

    // Build variable name:

    string var = string("_") + class_name;

    if (feature_name)
        var += string("_") + string(feature_name);

    if (qualifier_name)
        var += string("_") + string(qualifier_name);

    // Generate code:

    out("/*[%u]*/\n", __LINE__);
    out("static const Meta_Value_Scalar<%s>\n%s_MV =\n",
        _literal_type_name(mof_data_type), var.c_str());

    out("{\n");
    out("    ");
    literal_out(mof_literal, mof_data_type);
    out("\n");
    out("};\n");
    nl();
}

void gen_flavors(const MOF_Qualifier_Decl* /* mqd */, const MOF_Qualifier* mq)
{
    // Now override with qualifier flavor.

    string str;

    if (mq->flavor & MOF_FLAVOR_RESTRICTED)
    {
        str += "CIMPLE_FLAVOR_RESTRICTED";
    }

    if (mq->flavor & MOF_FLAVOR_TOSUBCLASS)
    {
        if (str.size())
            str += "|\n    ";

        str += "CIMPLE_FLAVOR_TO_SUBCLASS";
    }

    if (mq->flavor & MOF_FLAVOR_ENABLEOVERRIDE)
    {
        if (str.size())
            str += "|\n    ";

        str += "CIMPLE_FLAVOR_ENABLE_OVERRIDE";
    }

    if (mq->flavor & MOF_FLAVOR_DISABLEOVERRIDE)
    {
        if (str.size())
            str += "|\n    ";

        str += "CIMPLE_FLAVOR_DISABLE_OVERRIDE";
    }

    if (mq->flavor & MOF_FLAVOR_TRANSLATABLE)
    {
        if (str.size())
            str += "|\n    ";

        str += "CIMPLE_FLAVOR_TRANSLATABLE";
    }

    if (str.size() == 0)
        str = "0 /* flavors */";

    out("    %s,\n", str.c_str());
}

void gen_qual_scalar_def(
    const char* class_name,
    const char* feature_name, /* can be null */
    const MOF_Qualifier_Decl* mqd,
    const MOF_Qualifier* mq)
{
    // Build var name:

    string var = string("_") + string(mq->owning_class);

    if (feature_name)
        var += string("_") + string(feature_name);

    var += string("_") + string(mq->name);

    // Get type string:

    const char* type_str = MOF_Data_Type::to_string(mqd->data_type);

    // Declaration:

    out("extern const Meta_Qualifier\n%s_MQ;\n", var.c_str());
    nl();

    if (strcasecmp(class_name, mq->owning_class) != 0)
        return;

    // Value:

    if (mq->params && mq->params->value_type != TOK_NULL_VALUE)
    {
        gen_value_scalar_def(class_name, feature_name, mq->name,
            mqd->data_type, mq->params);
    }

    // Definition:

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Qualifier\n%s_MQ =\n", var.c_str());
    out("{\n");
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");
    out("    \"%s\", /* name */\n", mq->name);
    out("    %s, /* type */\n", toupper(type_str).c_str());
    out("    0, /* array */\n");
    gen_flavors(mqd, mq);

    if (mq->params && mq->params->value_type != TOK_NULL_VALUE)
        out("    (const Meta_Value*)(void*)&%s_MV,\n", var.c_str());
    else
        out("    0, /* value */\n");

    out("};\n");
    nl();
}

//==============================================================================
//
// _type_name()
//
//==============================================================================

static const char* _type_name(int data_type)
{
    switch (data_type)
    {
        case TOK_BOOLEAN:
            return "BOOLEAN";
        case TOK_UINT8:
            return "UINT8";
        case TOK_SINT8:
            return "SINT8";
        case TOK_UINT16:
            return "UINT16";
        case TOK_SINT16:
            return "SINT16";
        case TOK_UINT32:
            return "UINT32";
        case TOK_SINT32:
            return "SINT32";
        case TOK_UINT64:
            return "UINT64";
        case TOK_SINT64:
            return "SINT64";
        case TOK_REAL32:
            return "REAL32";
        case TOK_REAL64:
            return "REAL64";
        case TOK_CHAR16:
            return "CHAR16";
        case TOK_STRING:
            return "STRING";
        case TOK_DATETIME:
            return "DATETIME";
    }

    // Unreachable
    return 0;
}

void gen_value_array_def(
    const char* class_name,
    const char* feature_name,
    const char* qualifier_name,
    int data_type,
    const MOF_Literal* mof_literal)
{
    // Build variable name:

    string var = string("_") + class_name;

    if (feature_name)
        var += string("_") + string(feature_name);

    if (qualifier_name)
        var += string("_") + string(qualifier_name);

    // Elements:

    out("/*[%u]*/\n", __LINE__);
    out("static %s\n%s_elements[] =\n", 
        _literal_type_name(data_type), var.c_str());

    out("{\n");

    for (const MOF_Literal* p = mof_literal; p; p = (const MOF_Literal*)p->next)
    {
        out("    ");
        literal_out(p, data_type);
        out(",\n");
    }

    out("};\n");
    nl();

    // Definition:

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Value_Array<%s>\n%s_MV =\n", 
        _literal_type_name(data_type), var.c_str());
    out("{\n");
    out("    %s_elements,\n", var.c_str());
    out("    CIMPLE_ARRAY_SIZE(%s_elements),\n", var.c_str());
    out("};\n");
    nl();
}

void gen_qual_array_def(
    const char* class_name,
    const char* feature_name, /* can be null */
    const MOF_Qualifier_Decl* mqd,
    const MOF_Qualifier* mq)
{
    // Bauild variable name:

    string var = string("_") + string(mq->owning_class);

    if (feature_name)
        var += string("_") + string(feature_name);

    var += string("_") + string(mq->name);

    // Declaration:

    out("extern const Meta_Qualifier\n%s_MQ;\n", var.c_str());
    nl();

    if (strcasecmp(class_name, mq->owning_class) != 0)
        return;

    // Value:

    if (mq->params && mq->params->value_type != TOK_NULL_VALUE)
    {
        gen_value_array_def(class_name, feature_name, mq->name,
            mqd->data_type, mq->params);
    }

    // Definition:

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Qualifier\n%s_MQ =\n", var.c_str());
    out("{\n");
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");
    out("    \"%s\", /* name */\n", mq->name);
    out("    %s, /* type */\n", _type_name(mqd->data_type));
    out("    1, /* array */\n");
    gen_flavors(mqd, mq);

    if (mq->params && mq->params->value_type != TOK_NULL_VALUE)
        out("    (const Meta_Value*)(void*)&%s_MV,\n", var.c_str());
    else
        out("    0, /* value */\n");

    out("};\n");
    nl();
}

void gen_qual_def(
    const char* class_name,
    const char* feature_name, /* can be null */
    const MOF_Qualifier_Decl* mqd,
    const MOF_Qualifier* mq)
{
    if (mqd->array_index == 0)
        gen_qual_scalar_def(class_name, feature_name, mqd, mq);
    else
        gen_qual_array_def(class_name, feature_name, mqd, mq);
}

void gen_qual_defs(
    const MOF_Class_Decl* mcd,
    MOF_Qualifier_Info* all_qualifiers,
    const char* feature_name) /* may be null */
{
    // Generate individual qualifiers:

    for (const MOF_Qualifier_Info* p = all_qualifiers; 
        p; 
        p = (const MOF_Qualifier_Info*)p->next)
    {
        const MOF_Qualifier* mq = p->qualifier;
        const MOF_Qualifier_Decl* mqd = MOF_Qualifier_Decl::find(mq->name);
        assert(mqd != 0);

        if (!descriptions_opt && strcasecmp(mq->name, "Description") == 0)
            continue;

        if (!boolean_qualifiers_opt && mqd->data_type == TOK_BOOLEAN)
            continue;

        if (mqd->data_type == TOK_DATETIME)
            err("datetime qualifiers not supported");

        gen_qual_def(mcd->name, feature_name, mqd, mq);
    }

    // Build variable name:

    string var = string("_") + mcd->name;

    if (feature_name)
        var += string("_") + feature_name;

    // Generate qualifiers array:

    out("/*[%u]*/\n", __LINE__);
    out("static const Meta_Qualifier*\n%s_MQA[] =\n", var.c_str());

    out("{\n");

    for (const MOF_Qualifier_Info* p = all_qualifiers; 
        p; 
        p = (const MOF_Qualifier_Info*)p->next)
    {
        const MOF_Qualifier* mq = p->qualifier;
        const MOF_Qualifier_Decl* mqd = MOF_Qualifier_Decl::find(mq->name);

        if (!descriptions_opt && strcasecmp(mq->name, "Description") == 0)
            continue;

        if (!boolean_qualifiers_opt && mqd->data_type == TOK_BOOLEAN)
            continue;

        // Build variable name:

        string var = string("_") + string(mq->owning_class);

        if (feature_name)
            var += string("_") + string(feature_name);

        var += string("_") + string(mq->name);

        out("    (Meta_Qualifier*)(void*)&%s_MQ,\n", var.c_str());
    }

    out("};\n");
    nl();
}

const char* get_embedded_class_name(
    const MOF_Qualified_Element* mqe)
{
    for (const MOF_Qualifier_Info* p = mqe->all_qualifiers; 
        p; 
        p = (const MOF_Qualifier_Info*)p->next)
    {
        const MOF_Qualifier* mq = p->qualifier;

        if (strcasecmp(mq->name, "EmbeddedInstance") == 0)
        {
            MOF_Literal* ml = mq->params;

            if (ml && ml->value_type == TOK_STRING_VALUE && ml->string_value)
            {
                const char* ecn = ml->string_value;

                if (!MOF_Class_Decl::find((char*)ecn))
                    err("error: unknown embedded class: \"%s\"", ecn);

                return ecn;
            }
        }
    }

    // Not found!
    return 0;
}

void gen_property_decl(
    const MOF_Class_Decl* class_decl, 
    const MOF_Property_Decl* prop)
{
    // Process Values/ValueMap qualifiers.

    const MOF_Qualifier* values_qual  = 0;
    const MOF_Qualifier* value_map_qual  = 0;

    if (enum_opt)
    {
        for (const MOF_Qualifier* q = prop->qualifiers; 
            q; 
            q = (const MOF_Qualifier*)q->next)
        {
            if (strcasecmp(q->name, "Values") == 0)
                values_qual  = q;
            else if (strcasecmp(q->name, "ValueMap") == 0)
                value_map_qual  = q;
        }
    }

    do
    {
        if (values_qual && value_map_qual)
        {
            vector<string> values;
            vector<long> value_map;

            assert(values_qual->params);

            for (MOF_Literal* l = values_qual->params; 
                l; 
                l = (MOF_Literal*)l->next)
            {
                assert(l->value_type == TOK_STRING_VALUE);
                string tmp = normalize_value_qual_name(l->string_value);
                values.push_back(tmp);
            }

            for (MOF_Literal* l = value_map_qual->params; 
                l; l = (MOF_Literal*)l->next)
            {
                assert(l->value_type == TOK_STRING_VALUE);
                long tmp = atol(l->string_value);
                value_map.push_back(tmp);
            }

            // Check for duplicates:

            if (values.size() != value_map.size())
                break;

            // Generate enum property.

            out("    struct _%s\n", prop->name);
            out("    {\n");
            out("        enum\n");
            out("        {\n");

            for (size_t i = 0; i < values.size(); i++)
            {
                out("            ");
                out("enum_%s = %ld,\n", values[i].c_str(), value_map[i]);
            }

            out("        };\n");

            if (prop->array_index)
                out("        Array_%s value;\n", _to_string(prop->data_type));
            else
                out("        %s value;\n", _to_string(prop->data_type));

            out("        uint8 null;\n");

            switch (prop->data_type)
            {
                case TOK_UINT8:
                case TOK_SINT8:
                    break;

                case TOK_UINT16:
                case TOK_SINT16:
                    break;

                case TOK_UINT32:
                case TOK_SINT32:
                    break;

                case TOK_UINT64:
                case TOK_SINT64:
                    break;

                default:
                {
                    err("Values qualifier on non-integer property: %s.%s",
                        class_decl->name, prop->name);
                    break;
                }
            }

            out("    }\n");
            out("    %s;\n", prop->name);

            return;
        }
    }
    while (0);

    const char* tmp = _to_string(prop->data_type);
    int i = prop->array_index;

    if (i == 0)
    {
        /* Scalar */
        out("    Property<%s> %s;\n", tmp, prop->name);
    }
    else
    {
        /* VLA */
        out("    Property<Array_%s> %s;\n", tmp, prop->name);
    }
}

static size_t _count_keys(const MOF_Class_Decl* class_decl)
{
    MOF_Feature_Info* p = class_decl->all_features;

    size_t n = 0;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        if (p->feature->qual_mask & MOF_QT_KEY)
            n++;
    }

    return n;
}

void gen_feature_decls(
    const MOF_Class_Decl* class_decl,
    const MOF_Class_Decl* leaf_class_decl)
{
    MOF_Feature_Info* p = class_decl->all_features;

    out ("    // %s features:\n", class_decl->name);

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        // Skip non-local properties:

        if (strcasecmp(class_decl->name, p->class_origin->name) != 0)
            continue;

        // Is it a property?

        MOF_Property_Decl* prop = dynamic_cast<MOF_Property_Decl*>(p->feature);

        if (prop)
        {
            if (prop->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            {
                if (prop->array_index == 0)
                    out("    Instance* %s;\n", prop->name);
                else
                    out("    Property< Array<Instance*> > %s;\n", prop->name);
            }
            else
            {
                const char* ecn = get_embedded_class_name(prop);

                if (ecn)
                {
                    if (prop->array_index == 0)
                        out("    %s* %s;\n", ecn, prop->name);
                    else
                        out("    Property< Array<%s*> > %s;\n", ecn,prop->name);
                }
                else
                    gen_property_decl(class_decl, prop);
            }

            continue;
        }

        // Is is a reference?

        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(p->feature);

        if (ref)
        {
            // Search the leaf class and use its class name for this reference
            // since it may have been overriden.

            MOF_Feature_Info* q = leaf_class_decl->all_features;
            bool found = false;

            for (; q; q = (MOF_Feature_Info*)q->next)
            {
                if (strcasecmp(q->feature->name, ref->name) == 0)
                {
                    MOF_Reference_Decl* qref = 
                        dynamic_cast<MOF_Reference_Decl*>(q->feature);

                    if (qref)
                    {
                        out("    %s* %s;\n", 
                            qref->class_name, qref->name);
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
            {
                err("failed to find reference in leaf class: %s.%s", 
                    leaf_class_decl->name, ref->name);
            }

            continue;
        }
    }

    out("\n");
}

void gen_feature_decls_recursive(
    const MOF_Class_Decl* class_decl,
    const MOF_Class_Decl* leaf_class_decl)
{
    if (class_decl->super_class)
        gen_feature_decls_recursive(class_decl->super_class, leaf_class_decl);

    gen_feature_decls(class_decl, leaf_class_decl);
}

void gen_comment_line(size_t n)
{
    n -= 2;
    out("//");

    for (size_t i = 0; i < n; i++)
        fputc('=', _os);

    out("\n");
}

void gen_comment_block()
{
    gen_comment_line(80);
    out("//\n");
    out("// PLEASE DO NOT EDIT; THIS FILE WAS ");
    out("AUTOMATICALLY GENERATED BY GENCLASS %s\n", CIMPLE_VERSION_STRING);
    out("//\n");
    gen_comment_line(80);
}

void gen_class_decl(const MOF_Class_Decl* class_decl)
{
    const char* class_name = class_decl->name;
    MOF_Class_Decl* super_class = class_decl->super_class;

    // Generate class definition.

    const char* linkage = linkage_opt ? "CIMPLE_LINKAGE " : "";

    // Print keys comment:
    {
        MOF_Feature_Info* p = class_decl->all_features;

        out("// %s keys:\n", class_decl->name);

        for (; p; p = (MOF_Feature_Info*)p->next)
        {
            MOF_Property_Decl* prop = 
                dynamic_cast<MOF_Property_Decl*>(p->feature);

            if (prop && (prop->qual_mask & MOF_QT_KEY))
                out("//     %s\n", prop->name);
        }

        out("\n");
    }

    out("/*[%u]*/\n", __LINE__);
    out("class %s%s : public Instance\n", linkage, class_name);

    out("{\n");
    out("public:\n");
    gen_feature_decls_recursive(class_decl, class_decl);
    out("    CIMPLE_CLASS(%s)\n", class_name);
    out("};\n");

    nl();
}

void gen_param_ref_decl(const MOF_Parameter* param)
{
    if (param->array_index)
        out("    Property< Array<%s*> > %s;\n", param->ref_name, param->name);
    else
        out("    %s* %s;\n", param->ref_name, param->name);
}

void gen_param_prop_decl(
    const MOF_Parameter* param)
{
    const char* tmp = _to_string(param->data_type);
    int i = param->array_index;

    if (i == 0)
    {
        /* Scalar */

        const char* ecn = get_embedded_class_name(param);

        if (ecn)
            out("    %s* %s;\n", ecn, param->name);
        else if (param->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            out("    Instance* %s;\n", param->name);
        else
            out("    Property<%s> %s;\n", tmp, param->name);
    }
    else
    {
        /* VLA */

        const char* ecn = get_embedded_class_name(param);

        if (ecn)
            out("    Property< Array<%s*> > %s;\n", ecn, param->name);
        else if (param->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            out("    Property< Array<Instance*> > %s;\n", param->name);
        else
            out("    Property<Array_%s> %s;\n", tmp, param->name);
    }
}

void gen_param_decls(
    const char* /* class_name */, 
    const MOF_Method_Decl* meth)
{
    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
        if (p->data_type == TOK_REF)
            gen_param_ref_decl(p);
        else
            gen_param_prop_decl(p);
    }
}

void gen_meth_decl(
    const char* class_name,
    const MOF_Method_Decl* meth_decl)
{
    const char* meth_name = meth_decl->name;

#if 0
    // ATTN: Do we need this?
    if (qualifier_opt)
    {
        string tmp = string(suffix) + string("_") + mq->name;
        gen_qual_def(mcd, mqd, mq, tmp.c_str());
    }
#endif

    // Generate class definition.

    const char* linkage = linkage_opt ? "CIMPLE_LINKAGE " : "";

    out("/*[%u]*/\n", __LINE__);
    out("class %s%s_%s_method : public Instance\n", 
        linkage, class_name, meth_name);

    out("{\n");
    out("public:\n");
    gen_param_decls(class_name, meth_decl);

    {
        const char* ecn = get_embedded_class_name(meth_decl);

        if (ecn)
        {
            out ("    %s* return_value;\n", ecn);
        }
        else if (meth_decl->qual_mask & MOF_QT_EMBEDDEDOBJECT)
        {
            out ("    Instance* return_value;\n");
        }
        else
        {
            out("    Property<%s> return_value;\n", 
                _to_string(meth_decl->data_type));
        }
    }

    out("    CIMPLE_METHOD(%s_%s_method)\n", class_name, meth_name);
    out("};\n");
    nl();
}

void gen_meth_typedef(
    const char* class_name,
    const char* class_origin_name,
    const MOF_Method_Decl* meth_decl)
{
    const char* meth_name = meth_decl->name;

    // Generate class definition.

    out("typedef %s_%s_method %s_%s_method;\n\n", 
        class_origin_name, meth_name, class_name, meth_name);
}

void gen_meth_decls(
    const MOF_Class_Decl* class_decl)
{
    MOF_Feature_Info* p = class_decl->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p->feature);

        if (meth)
        {
            if (strcasecmp(class_decl->name, p->class_origin->name) == 0 ||
                !p->propagated)
            {
                gen_meth_decl(class_decl->name, meth);
            }
            else
            {
                gen_meth_typedef(class_decl->name, p->class_origin->name, meth);
            }
        }
    }
}

void generate_ref_includes(const MOF_Class_Decl* class_decl)
{
    // For each reference, generate the required #include statement.

    MOF_Feature* p = class_decl->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(p);

        if (ref)
            out("#include \"%s.h\"\n", ref->class_name);
    }
}

void generate_param_ref_includes(const MOF_Class_Decl* class_decl)
{
    MOF_Feature* p = class_decl->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p);

        if (!meth)
            continue;

        for (MOF_Parameter* q = meth->parameters; q; q =(MOF_Parameter*)q->next)
        {
            if (q->data_type == TOK_REF)
                out("#include \"%s.h\"\n", q->ref_name);
        }
    }
}

void generate_embedded_includes(const MOF_Class_Decl* mcd)
{
    // Handle EmbeddedInstance on properties.
    {
        for (MOF_Feature* p = mcd->features; p; p = (MOF_Feature*)p->next)
        {
            MOF_Property_Decl* mpd = dynamic_cast<MOF_Property_Decl*>(p);

            if (mpd)
            {
                const char* ecn = get_embedded_class_name(mpd);

                if (ecn)
                    out("#include \"%s.h\"\n", ecn);
            }
        }
    }

    // Handle EmbeddedInstance on methods.
    {
        for (MOF_Feature* p = mcd->features; p; p = (MOF_Feature*)p->next)
        {
            MOF_Method_Decl* mmd = dynamic_cast<MOF_Method_Decl*>(p);

            if (mmd)
            {
                const char* ecn = get_embedded_class_name(mmd);

                if (ecn)
                    out("#include \"%s.h\"\n", ecn);
            }
        }
    }

    // Handle EmbeddedInstance on parameters.
    {
        for (MOF_Feature* p = mcd->features; p; p = (MOF_Feature*)p->next)
        {
            MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p);

            if (!meth)
                continue;

            for (MOF_Parameter* q = meth->parameters; q; 
                q = (MOF_Parameter*)q->next)
            {
                const char* ecn = get_embedded_class_name(q);

                if (ecn)
                    out("#include \"%s.h\"\n", ecn);
            }
        }
    }
}

void generate_version_check()
{
    {
        const char FORMAT[] =
            "# error \""
            "The version of genclass used to generate this file (%s) is newer "
            "than the version of <cimple/cimple.h> found on the include path. "
            "Please place the matching version of <cimple/cimple.h> on "
            "the include path.\"\n";

        out ("#if (0x%08X > CIMPLE_VERSION)\n", CIMPLE_VERSION);
        out (FORMAT, CIMPLE_VERSION_STRING);
        out ("#endif\n");
        nl();
    }

    {
        const char FORMAT[] =
            "# error \""
            "The version of genclass used to generate this file (%s) is older "
            "than the version of <cimple/cimple.h> found on the include path. "
            "Please regenerate the sources with the matching version of "
            "genclass.\"\n";

        out ("#if (0x%08X < CIMPLE_VERSION)\n", CIMPLE_VERSION);
        out (FORMAT, CIMPLE_VERSION_STRING);
        out ("#endif\n");
        nl();
    }
}

void gen_header_file(const MOF_Class_Decl* class_decl)
{
    gen_comment_block();
    nl();

    out("#ifndef _cimple_%s_h\n", class_decl->name);
    out("#define _cimple_%s_h\n", class_decl->name);
    nl();

    out("#include <cimple/cimple.h>\n");

    if (class_decl->super_class)
        out("#include \"%s.h\"\n", class_decl->super_class->name);

    generate_ref_includes(class_decl);
    generate_param_ref_includes(class_decl);
    generate_embedded_includes(class_decl);
    nl();

#if 0
    generate_version_check();
    nl();
#endif

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    gen_class_decl(class_decl);
    gen_meth_decls(class_decl);

    out("CIMPLE_NAMESPACE_END\n");
    nl();

    out("#endif /* _cimple_%s_h */\n", class_decl->name);
}

void gen_bool_qual_list(MOF_mask mask, bool param)
{
#if 0
    // Generated beforehand!
    if (mask & MOF_QT_ASSOCIATION)
        out("|CIMPLE_FLAG_ASSOCIATION");
    if (mask & MOF_QT_INDICATION)
        out("|CIMPLE_FLAG_INDICATION");
#endif

    if (mask & MOF_QT_KEY)
        out("|CIMPLE_FLAG_KEY");
    if (param && (mask & MOF_QT_IN))
        out("|CIMPLE_FLAG_IN");
    if (param && (mask & MOF_QT_OUT))
        out("|CIMPLE_FLAG_OUT");
    if (mask & MOF_QT_ABSTRACT)
        out("|CIMPLE_FLAG_ABSTRACT");
    if (mask & MOF_QT_AGGREGATE)
        out("|CIMPLE_FLAG_AGGREGATE");
    if (mask & MOF_QT_AGGREGATION)
        out("|CIMPLE_FLAG_AGGREGATION");
    if (mask & MOF_QT_COUNTER)
        out("|CIMPLE_FLAG_COUNTER");
    if (mask & MOF_QT_DELETE)
        out("|CIMPLE_FLAG_DELETE");
    if (mask & MOF_QT_DN)
        out("|CIMPLE_FLAG_DN");
    if (mask & MOF_QT_EMBEDDEDOBJECT)
        out("|CIMPLE_FLAG_EMBEDDED_OBJECT");
    if (mask & MOF_QT_EXPENSIVE)
        out("|CIMPLE_FLAG_EXPENSIVE");
    if (mask & MOF_QT_EXPERIMENTAL)
        out("|CIMPLE_FLAG_EXPERIMENTAL");
    if (mask & MOF_QT_GAUGE)
        out("|CIMPLE_FLAG_GAUGE");
    if (mask & MOF_QT_IFDELETED)
        out("|CIMPLE_FLAG_IFDELETED");
    if (mask & MOF_QT_INVISIBLE)
        out("|CIMPLE_FLAG_INVISIBLE");
    if (mask & MOF_QT_LARGE)
        out("|CIMPLE_FLAG_LARGE");
    if (mask & MOF_QT_OCTETSTRING)
        out("|CIMPLE_FLAG_OCTET_STRING");
    if (mask & MOF_QT_READ)
        out("|CIMPLE_FLAG_READ");
    if (mask & MOF_QT_REQUIRED)
        out("|CIMPLE_FLAG_REQUIRED");
    if (mask & MOF_QT_STATIC)
        out("|CIMPLE_FLAG_STATIC");
    if (mask & MOF_QT_TERMINAL)
        out("|CIMPLE_FLAG_TERMINAL");
    if (mask & MOF_QT_WEAK)
        out("|CIMPLE_FLAG_WEAK");
    if (mask & MOF_QT_WRITE)
        out("|CIMPLE_FLAG_WRITE");
}

void gen_property_def(
    const char* class_name,
    const MOF_Property_Decl* mp)
{
    // Write external definition (whether propagated or not).

    out("/*[%u]*/\n", __LINE__);
    out("extern const Meta_Property\n_%s_%s;\n", mp->owning_class, mp->name);
    nl();

    // Go no further if property is propagated.

    if (strcasecmp(class_name, mp->owning_class) != 0)
        return;

    // Generate Meta_Value:

    if (mp->initializer && mp->initializer->value_type != TOK_NULL_VALUE)
    {
        if (mp->array_index == 0)
            gen_value_scalar_def(
                class_name, mp->name, 0, mp->data_type, mp->initializer);
        else
            gen_value_array_def(
                class_name, mp->name, 0, mp->data_type, mp->initializer);
    }

    // Generate property definition.

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Property\n_%s_%s =\n", class_name, mp->name);
    out("{\n");

    // Refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags field:
    {
        out("    CIMPLE_FLAG_PROPERTY");
        gen_bool_qual_list(mp->qual_mask, false);
        out(",\n");
    }

    // Name field:

    out("    \"%s\",\n", mp->name);

    // Qualifiers:

    if (qualifier_opt && mp->all_qualifiers)
    {
        out("    _%s_%s_MQA,\n", mp->owning_class, mp->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_MQA),\n", mp->owning_class, mp->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Print type:

    {
        string tmp = toupper(MOF_Data_Type::to_string(mp->data_type));
        out("    %s,\n", tmp.c_str());
    }

    // Print array subscript:

    out("    %d, /* subscript */\n", mp->array_index);

    // Print offset to field.

    out("    CIMPLE_OFF(%s,%s),\n", class_name, mp->name);

    // Meta_Property.value:

    if (mp->initializer && mp->initializer->value_type != TOK_NULL_VALUE)
        out("    (const Meta_Value*)(void*)&_%s_%s_MV,\n", class_name,mp->name);
    else
        out("    0, /* value */\n");

    out("};\n");
    nl();
}

void gen_reference_def(
    const char* class_name,
    const MOF_Reference_Decl* mr)
{
    // Write external definition (whether propagated or not).
    out("/*[%u]*/\n", __LINE__);
    out("extern const Meta_Reference\n_%s_%s;\n", mr->owning_class, mr->name);
    nl();

    // If propagated, go no further.

    if (strcasecmp(class_name, mr->owning_class) != 0)
        return;

    // Write the reference declaration.

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Reference\n_%s_%s =\n", class_name, mr->name);
    out("{\n");

    // Meta_Reference.refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Meta_Reference.flags:
    {
        out("    CIMPLE_FLAG_REFERENCE");
        gen_bool_qual_list(mr->qual_mask, false);
        out(",\n");
    }

    // Meta_Reference.name:

    {
        out("    \"%s\",\n", mr->name);
    }

    // Meta_Reference.qualifiers:
    // Meta_Reference.num_qualifiers:

    if (qualifier_opt && mr->all_qualifiers)
    {
        out("    _%s_%s_MQA,\n", mr->owning_class, mr->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_MQA),\n", mr->owning_class, mr->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Meta_Reference.subscript (as class features, these cannot be arrays).

    out("    0, /* subscript */\n");

    // Print meta class:

    out("    &%s::static_meta_class,\n" , mr->class_name);

    // Meta_Reference.offset:

    out("    CIMPLE_OFF(%s,%s)\n", class_name, mr->name);

    out("};\n");
    nl();
}

void gen_param_ref_def(
    const char* class_name,
    const char* meth_name,
    const MOF_Parameter* param)
{
    // Preamble:
    {
        out("/*[%u]*/\n", __LINE__);
        out("static const Meta_Reference\n");
        out("_%s_%s_%s =\n", class_name, meth_name, param->name);
        out("{\n");
    }

    // Refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags:
    {
        out("    CIMPLE_FLAG_REFERENCE");
        gen_bool_qual_list(param->qual_mask, true);
        out(",\n");
    }

    // Name:
    {
        out("    \"%s\",\n", param->name);
    }

    // Qualifiers:

    if (qualifier_opt && param->all_qualifiers)
    {
        out("    _%s_%s_%s_MQA,\n", class_name, meth_name, param->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_%s_MQA),\n",
            class_name, meth_name, param->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Subscript:

    out("    %d, /* subscript */\n", param->array_index);

    // Meta class:
    {
        out("    &%s::static_meta_class,\n" , param->ref_name);
    }

    /// Offset:

    out("    CIMPLE_OFF(%s_%s_method,%s)\n", 
        class_name, meth_name, param->name);

    /// Postamble:

    out("};\n\n");
}

void gen_param_prop_def(
    const char* class_name,
    const char* meth_name,
    const MOF_Parameter* param)
{
    /// Preamble:

    out("/*[%u]*/\n", __LINE__);
    out("static const Meta_Property\n_%s_%s_%s =\n",
        class_name, meth_name, param->name);
    out("{\n");

    // Refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags:
    {
        out("    CIMPLE_FLAG_PROPERTY");
        gen_bool_qual_list(param->qual_mask, true);
        out(",\n");
    }

    /// Name:

    out("    \"%s\",\n", param->name);

    // Qualifiers:

    if (qualifier_opt && param->all_qualifiers)
    {
        out("    _%s_%s_%s_MQA,\n", class_name, meth_name, param->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_%s_MQA),\n",
            class_name, meth_name, param->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    /// Type:

    string tmp = toupper(MOF_Data_Type::to_string(param->data_type));
    out("    %s,\n", tmp.c_str());

    /// Subscript:

    out("    %d,\n", param->array_index);

    /// Offset:

    out("    CIMPLE_OFF(%s_%s_method,%s),\n", 
        class_name, meth_name, param->name);

    // Meta_Property.value:

    out("    0, /* value */\n");

    /// Postamble:

    out("};\n\n");
}

void gen_embedded_param_def(
    const char* class_name,
    const char* meth_name,
    const MOF_Parameter* param,
    const char* embedded_class_name)
{
    // Preamble:
    {
        out("/*[%u]*/\n", __LINE__);
        out("static const Meta_Reference\n");
        out("_%s_%s_%s =\n", class_name, meth_name, param->name);
        out("{\n");
    }

    // Refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags:
    {
        if (embedded_class_name)
            out("    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_INSTANCE");
        else
            out("    CIMPLE_FLAG_REFERENCE");

        gen_bool_qual_list(param->qual_mask, true);
        out(",\n");
    }

    // Name:
    {
        out("    \"%s\",\n", param->name);
    }

    // Qualifiers:

    if (qualifier_opt && param->all_qualifiers)
    {
        out("    _%s_%s_%s_MQA,\n", class_name, meth_name, param->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_%s_MQA),\n",
            class_name, meth_name, param->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Subscript:

    out("    %d, /* subscript */\n", param->array_index);

    // Meta class:
    {
        if (embedded_class_name)
            out("    &%s::static_meta_class,\n" , embedded_class_name);
        else
            out("    &Instance::static_meta_class,\n");
    }

    /// Offset:

    out("    CIMPLE_OFF(%s_%s_method,%s)\n", 
        class_name, meth_name, param->name);

    /// Postamble:

    out("};\n\n");
}

void gen_param_array(
    const char* class_name,
    const MOF_Method_Decl* meth)
{
    out("/*[%u]*/\n", __LINE__);
    out("static Meta_Feature* _%s_%s_MFA[] =\n", 
        class_name, meth->name);
    out("{\n");

    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
        out("    (Meta_Feature*)(void*)&_%s_%s_%s,\n", class_name, meth->name, 
            p->name);
    }

    out("    (Meta_Feature*)(void*)&_%s_%s_return_value\n", 
        class_name, meth->name);

    out("};\n");
    nl();
}

void gen_meth_return_def(
    const char* class_name,
    const MOF_Method_Decl* meth)
{
    // Preamble:

    out("/*[%u]*/\n", __LINE__);
    out("static const Meta_Property\n_%s_%s_return_value =\n",
        class_name, meth->name);
    out("{\n");

    // Refs:

    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags:
    // ATTN: can boolean qualifiers appear on the return value?
    out("    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,\n");

    // Name:

    out("    \"return_value\",\n");

    // Qualifiers:

    if (qualifier_opt && meth->all_qualifiers)
    {
        out("    _%s_%s_MQA,\n", class_name, meth->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_MQA),\n", class_name, meth->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Type:

    string tmp = toupper(MOF_Data_Type::to_string(meth->data_type));
    out("    %s,\n", tmp.c_str());

    // Subscript:

    out("    0,\n");

    // Offset:

    out("    CIMPLE_OFF(%s_%s_method,return_value),\n", 
        class_name, meth->name);

    // Meta_Property.value:

    out("    0, /* value */\n");

    // Postamble:

    out("};\n\n");
}

void gen_meth_embedded_return_def(
    const char* class_name,
    const MOF_Method_Decl* mmd,
    const char* embedded_class_name)
{
    // Preamble:

    out("/*[%u]*/\n", __LINE__);
    out("static const Meta_Reference\n_%s_%s_return_value =\n",
        class_name, mmd->name);
    out("{\n");

    // Meta_Reference.refs:

    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Meta_Reference.flags:

    if (embedded_class_name)
    {
        out("    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_INSTANCE|"
            "CIMPLE_FLAG_OUT");
    }
    else
    {
        out("    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_OUT");
    }

    gen_bool_qual_list(mmd->qual_mask, true);
    out(",\n");

    // Field name:
    out("    \"return_value\",\n");

    // Meta_Reference.meta_qualifiers:

    if (qualifier_opt && mmd->all_qualifiers)
    {
        out("    _%s_%s_MQA,\n", mmd->owning_class, mmd->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_MQA),\n", 
            mmd->owning_class, mmd->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qualifiers */\n");
    }

    // Meta_Reference.subscript:
    out("    0, /* subscript */\n");

    // Meta_Reference.super_meta_class:

    if (embedded_class_name)
        out("    &%s::static_meta_class,\n", embedded_class_name);
    else
        out("    &Instance::static_meta_class,\n");

    // Meta_Reference.offset:

    out("    CIMPLE_OFF(%s_%s_method, return_value),\n", class_name, mmd->name);

    // Postamble:

    out("};\n\n");
}

void gen_method_def(
    const MOF_Class_Decl* mcd,
    const MOF_Method_Decl* meth, 
    const char* class_name)
{
    // Generate parameter definitions.

    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
        // Generate param qualifiers:

        if (qualifier_opt && p->all_qualifiers)
        {
            // Compound feature name (Method-name + Parameter-name)
            string feature_name = 
                string(meth->name) + string("_") + string(p->name);
            gen_qual_defs(mcd, p->all_qualifiers, feature_name.c_str());
        }

        // Generate param:

        if (p->data_type == TOK_REF)
        {
            gen_param_ref_def(class_name, meth->name, p);
        }
        else if (p->qual_mask & MOF_QT_EMBEDDEDOBJECT)
        {
            gen_embedded_param_def(class_name, meth->name, p, 0);
        }
        else
        {
            const char* ecn = get_embedded_class_name(p);

            if (ecn)
                gen_embedded_param_def(class_name, meth->name, p, ecn);
            else
                gen_param_prop_def(class_name, meth->name, p);
        }
    }

    // Generate the return value.
    {
        const char* ecn = get_embedded_class_name(meth);

        if (meth->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            gen_meth_embedded_return_def(class_name, meth, 0);
        else if (ecn)
            gen_meth_embedded_return_def(class_name, meth, ecn);
        else
            gen_meth_return_def(class_name, meth);
    }

    // Parameter array

    gen_param_array(class_name, meth);

    // Preamble:

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Method\n%s_%s_method::static_meta_class =\n", 
        class_name, meth->name);

    out("{\n");

    // Refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags:

    out("    CIMPLE_FLAG_METHOD");
    gen_bool_qual_list(meth->qual_mask, false);
    out(",\n");

    // Name:

    out("    \"%s\",\n", meth->name);

    // Qualifier array.

    if (qualifier_opt && meth->all_qualifiers)
    {
        out("    _%s_%s_MQA,\n", class_name, meth->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_MQA),\n", class_name, meth->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Feature array.

    out("    _%s_%s_MFA,\n", class_name, meth->name);
    out("    CIMPLE_ARRAY_SIZE(_%s_%s_MFA),\n", 
        class_name, meth->name);

    // Size of parameter block

    out("    sizeof(%s_%s_method),\n", class_name, meth->name);

    // Return type:

    {
        string tmp = toupper(MOF_Data_Type::to_string(meth->data_type));
        out("    %s,\n", tmp.c_str());
    }

    // Postamble:

    out("};\n\n");
}

void gen_embedded_def(
    const char* class_name, 
    const MOF_Property_Decl* mpd,
    const char* embedded_class_name)
{
    // Meta_Reference (declaration):
    out("extern const Meta_Reference\n_%s_%s;\n\n", 
        mpd->owning_class, mpd->name);

    if (strcasecmp(class_name, mpd->owning_class) != 0)
        return;

    // Meta_Reference (definition):
    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Reference _%s_%s =\n", class_name, mpd->name);
    out("{\n");

    // Meta_Reference.refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Meta_Reference.flags:
    // ATTN: can boolean qualifiers appear here?

    if (embedded_class_name)
        out("    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_INSTANCE,\n");
    else
        out("    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,\n");

    // Meta_Reference.name:
    out("    \"%s\",\n", mpd->name);

    // Meta_Reference.meta_qualifiers:

    if (qualifier_opt && mpd->all_qualifiers)
    {
        out("    _%s_%s_MQA,\n", mpd->owning_class, mpd->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_%s_MQA),\n", 
            mpd->owning_class, mpd->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qualifiers */\n");
    }

    // Meta_Reference.subscript:

    if (mpd->array_index == 0)
        out("    0, /* subscript */\n");
    else
        out("    -1, /* subscript */\n");

    // Meta_Reference.super_meta_class:

    if (embedded_class_name)
        out("    &%s::static_meta_class,\n", embedded_class_name);
    else
        out("    &Instance::static_meta_class,\n");

    // Meta_Reference.offset:
    out("    CIMPLE_OFF(%s,%s)\n", class_name, mpd->name);

    // Trailer:
    out("};\n");
    nl();
}

void gen_feature_defs(const MOF_Class_Decl* cd)
{
    MOF_Feature_Info* p = cd->all_features;
    const char* class_name = cd->name;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* mf = p->feature;

        // Generate qualifier definitions:

        if (qualifier_opt && mf->all_qualifiers)
            gen_qual_defs(cd, mf->all_qualifiers, mf->name);

        MOF_Property_Decl* prop = dynamic_cast<MOF_Property_Decl*>(mf);

        // Find class that propagated this feature.

        // Property.

        if (prop)
        {
            if (prop->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            {
                gen_embedded_def(class_name, prop, 0);
            }
            else
            {
                const char* ecn = get_embedded_class_name(prop);

                if (ecn)
                    gen_embedded_def(class_name, prop, ecn);
                else
                    gen_property_def(class_name, prop);
            }
        }

        // Reference:

        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(mf);

        if (ref)
            gen_reference_def(class_name, ref);

        // Method:

        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(mf);

        if (meth && !p->propagated)
            gen_method_def(cd, meth, cd->name);
    }
}

void gen_feature_array(const MOF_Class_Decl* class_decl)
{
    MOF_Feature_Info* p = class_decl->all_features;

    out("/*[%u]*/\n", __LINE__);
    out("static Meta_Feature* _%s_MFA[] =\n", class_decl->name);
    out("{\n");

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* feature = p->feature;

        // Find name of class that propagated this feature.

        const char* class_name = feature->owning_class;

        // Property.

        MOF_Property_Decl* prop = dynamic_cast<MOF_Property_Decl*>(feature);

        if (prop)
            out("    (Meta_Feature*)(void*)&_%s_%s,\n", class_name, prop->name);

        // Reference.

        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(feature);

        if (ref)
            out("    (Meta_Feature*)(void*)&_%s_%s,\n", class_name, ref->name);

        // Method.

        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(feature);

        if (meth)
        {
            out("    (Meta_Feature*)(void*)&%s_%s_method::static_meta_class,\n",
                p->class_origin->name, meth->name);
        }
    }

    out("};\n");
    nl();
}

void gen_class_def(const MOF_Class_Decl* class_decl)
{
    // Generate _locals[] array.

    if (class_decl->all_features)
    {
        out("/*[%u]*/\n", __LINE__);
        out("static const Meta_Feature_Local _locals[] =\n");
        out("{\n");

        MOF_Feature_Info* p = class_decl->all_features;

        for (; p; p = (MOF_Feature_Info*)p->next)
            out("    {%u},\n", p->propagated ? 0 : 1);

        out("};\n");
        nl();
    }

    // qualifiers:

    if (qualifier_opt && class_decl->all_qualifiers)
        gen_qual_defs(class_decl, class_decl->all_qualifiers, 0);

    // static_meta_class:

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Class %s::static_meta_class =\n", 
        class_decl->name);
    out("{\n");

    // Refs:
    out("    CIMPLE_ATOMIC_INITIALIZER, /* refs */\n");

    // Flags:
    {
        if (class_decl->qual_mask & MOF_QT_ASSOCIATION)
            out("    CIMPLE_FLAG_ASSOCIATION");
        else if (class_decl->qual_mask & MOF_QT_INDICATION)
            out("    CIMPLE_FLAG_INDICATION");
        else
            out("    CIMPLE_FLAG_CLASS");

        gen_bool_qual_list(class_decl->qual_mask, false);
        out(",\n");
    }

    // Name:
    {
        out("    \"%s\",\n", class_decl->name);
    }

    // Qualifiers:

    if (qualifier_opt && class_decl->all_qualifiers)
    {
        out("    _%s_MQA,\n", class_decl->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_MQA),\n", class_decl->name);
    }
    else
    {
        out("    0, /* meta_qualifiers */\n");
        out("    0, /* num_meta_qaulifiers */\n");
    }

    // Features:

    if (class_decl->all_features)
    {
        out("    _%s_MFA,\n", class_decl->name);
        out("    CIMPLE_ARRAY_SIZE(_%s_MFA),\n", class_decl->name);
    }
    else
    {
        out("    0, /* meta_features*/\n");
        out("    0, /* num_meta_features */\n");
    }

    // Size:
    {
        out("    sizeof(%s),\n", class_decl->name);
    }

    // Local:

    if (class_decl->all_features)
        out("    _locals,\n");
    else
        out("    0, /* locals */\n");

    // Superclass:

    if (class_decl->super_class)
        out("    &%s::static_meta_class,\n", class_decl->super_class->name);
    else
        out("    0, /* super_class */ \n");

    // Number of keys.
    {
        out("    %u, /* num_keys */\n", int(_count_keys(class_decl)));
    }

    // meta_repository:

    if (gen_repository_opt)
        out("    &%s,\n", meta_repository_name.c_str());
    else
        out("    0,\n");

    out("};\n");
    nl();
}

void gen_source_file(const MOF_Class_Decl* class_decl)
{
#if 0
    string sig;
    make_signature(class_decl, sig);
    printf("%s", sig.c_str());
#endif

    gen_comment_block();
    nl();

    out("#include <cimple/Meta_Class.h>\n");
    out("#include <cimple/Meta_Property.h>\n");
    out("#include <cimple/Meta_Reference.h>\n");
    out("#include \"%s.h\"\n", class_decl->name);
    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    out("using namespace cimple;\n");
    nl();

    if (gen_repository_opt)
    {
        out("extern const Meta_Repository %s;\n", meta_repository_name.c_str());
        nl();
    }

    // Generate class meta data.

    gen_feature_defs(class_decl);

    if (class_decl->all_features)
        gen_feature_array(class_decl);

    gen_class_def(class_decl);

    out("CIMPLE_NAMESPACE_END\n");
    nl();
}

void generate_ancestor_classes(const char* class_name);
void generate_ref_clases(const char* class_name);
void generate_param_ref_clases(const char* class_name);
void generate_embedded_clases(const char* class_name);

typedef set<string> Duplicate_Classes;
Duplicate_Classes duplicate_classes;

static vector<string> _generated_classes;

static void _append_genmak(const char* buffer)
{
    // Append generated source file name to .genclass file

    if (sources_opt)
    {
        if (verbose_opt)
        {
            printf("Append %s to .getclass file\n", buffer);
        }
        FILE* os = fopen(".genclass", "a");

        if (!os)
            err("failed to open .genclass");

        fprintf(os, "%s\n", buffer);
        fclose(os);
    }
}

void generate_class(const char* class_name)
{
    // Avoid generating any class more than once:

    if (duplicate_classes.find(class_name) != duplicate_classes.end())
        return;

    duplicate_classes.insert(class_name);

    // First generate any ancestor classes:

    generate_ancestor_classes(class_name);

    // Now generate any ref classes (any classes that associations refer to).

    generate_ref_clases(class_name);

    // Now generate any param ref classes.

    generate_param_ref_clases(class_name);

    // Now generate any embedded classes.

    generate_embedded_clases(class_name);

    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
        err("error: [1] no such class: \"%s\"", class_name);
        exit(1);
    }

    // Remember all generated classes:

    _generated_classes.push_back(class_name);

    // Disallow generation of abstract classes.

#if 0
    // ATTN: need to generate abstract references (for associations).
    if (class_decl->qual_mask & MOF_QT_ABSTRACT)
    {
        err("%s: attempt to generate an abstract class: \"%s\"", 
            arg0, class_name);
        exit(1);
    }
#endif

    // Generate header file:

    {
        char buffer[1024];
        sprintf(buffer, "%s.h", class_name);
        
        // Open the output file and save the FILE pointer
        if ((_os = fopen(buffer, "wb")) == 0)
        {
            err("error: cannot open \"%s\"", buffer);
            exit(1);
        }
        // required for Pegasus and CIMPLE src length test tools
        out("/*NOCHKSRC*/\n");

        gen_header_file(class_decl);

        fclose(_os);
        printf("Created %s\n", buffer);
    }

    // Generate source file:

    {
        // open the <classname>.cpp file
        char buffer[1024];
        sprintf(buffer, "%s.cpp", class_name);
        
        if ((_os = fopen(buffer, "wb")) == 0)
        {
            err("error: cannot open \"%s\"", buffer);
            exit(1);
        }

        out("/*NOCHKSRC*/\n");

        gen_source_file(class_decl);

        fclose(_os);
        printf("Created %s\n", buffer);
        _append_genmak(buffer);
    }
}

void generate_ancestor_classes(const char* class_name)
{
    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
        err("error: [2] no such class: \"%s\"", class_name);
        exit(1);
    }

    // Generate the super class (and its superclass)

    const MOF_Class_Decl* super_class_decl = class_decl->super_class;

    if (!super_class_decl)
        return;

    generate_ancestor_classes(super_class_decl->name);

    generate_class(super_class_decl->name);
}

void generate_ref_clases(const char* class_name)
{
    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
        err("error: [3] no such class: \"%s\"", class_name);
        exit(1);
    }

    // For each reference, generate the association class.

    MOF_Feature* p = class_decl->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(p);

        if (ref)
            generate_class(ref->class_name);
    }

    return;
}

void generate_embedded_clases(const char* class_name)
{
    // Find the class.

    const MOF_Class_Decl* mcd = 
        MOF_Class_Decl::find((char*)class_name);

    if (!mcd)
    {
        err("error: no such class: \"%s\"", class_name);
        exit(1);
    }

    // Handle EmbeddedInstance() on properties.
    {
        // For each reference, generate the association class.

        MOF_Feature* p = mcd->features;

        for (; p; p = (MOF_Feature*)p->next)
        {
            MOF_Property_Decl* mpd = dynamic_cast<MOF_Property_Decl*>(p);

            if (mpd)
            {
                const char* ecn = get_embedded_class_name(mpd);

                if (ecn)
                    generate_class(ecn);
            }
        }
    }

    // Handle EmbeddedInstance() on methods.
    {
        // For each reference, generate the association class.

        MOF_Feature* p = mcd->features;

        for (; p; p = (MOF_Feature*)p->next)
        {
            MOF_Method_Decl* mmd = dynamic_cast<MOF_Method_Decl*>(p);

            if (mmd)
            {
                const char* ecn = get_embedded_class_name(mmd);

                if (ecn)
                    generate_class(ecn);
            }
        }
    }

    // Handle EmbeddedInstance() on parameters.
    {
        MOF_Feature* p = mcd->features;

        for (; p; p = (MOF_Feature*)p->next)
        {
            MOF_Method_Decl* mmd = dynamic_cast<MOF_Method_Decl*>(p);

            if (!mmd)
                continue;

            for (MOF_Parameter* q=mmd->parameters; q; q=(MOF_Parameter*)q->next)
            {
                const char* ecn = get_embedded_class_name(q);

                if (ecn)
                    generate_class(ecn);
            }
        }
    }

    return;
}

void generate_param_ref_clases(const char* class_name)
{
    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
        err("error: [4] no such class: \"%s\"", class_name);
        exit(1);
    }

    // Look for methods with ref parameters.

    MOF_Feature* p = class_decl->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p);

        if (!meth)
            continue;

        for (MOF_Parameter* q = meth->parameters; q; q =(MOF_Parameter*)q->next)
        {
            if (q->data_type == TOK_REF)
            {
                generate_class(q->ref_name);
            }
        }
    }
}

void gen_repository_header_file(const vector<string>& classes)
{
    gen_comment_block();
    nl();

    out("#ifndef _repository_h\n");
    out("#define _repository_h\n");
    nl();

    out("#include <cimple/cimple.h>\n");

    for (size_t i = 0; i < classes.size(); i++)
        out("#include \"%s.h\"\n", classes[i].c_str());

    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

#if 0
    out("CIMPLE_ENTRY_POINT void cimple_repository(\n");
    out("    const Meta_Class* const*& meta_classes,\n");
    out("    size_t& num_meta_classes);\n");
    nl();
#endif

    out("CIMPLE_NAMESPACE_END\n");
    nl();

    out("#endif /* _repository_h */\n");
}

void gen_repository_source_file(const vector<string>& classes)
{
    gen_comment_block();
    nl();

    out("#include <cimple/cimple.h>\n");
    out("#include \"repository.h\"\n");
    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    out("/*[%u]*/\n", __LINE__);
    out("static const Meta_Class* _meta_classes[] =\n");
    out("{\n");

    for (size_t i = 0; i < classes.size(); i++)
        out("    &%s::static_meta_class,\n", classes[i].c_str());

    out("};\n");
    nl();
    out("static const size_t _num_meta_classes = ");
    out("CIMPLE_ARRAY_SIZE(_meta_classes);\n");
    nl();

#if 0
    out("CIMPLE_ENTRY_POINT void cimple_repository(\n");
    out("    const Meta_Class* const*& meta_classes,\n");
    out("    size_t& num_meta_classes)\n");
    out("{\n");
    out("   meta_classes = _meta_classes; \n");
    out("   num_meta_classes = _num_meta_classes; \n");
    out("}\n");
    nl();
#endif

    out("extern const Meta_Repository %s;\n", meta_repository_name.c_str());
    nl();

    out("/*[%u]*/\n", __LINE__);
    out("const Meta_Repository %s =\n", meta_repository_name.c_str());
    out("{\n");
    out("    _meta_classes,\n");
    out("    _num_meta_classes,\n");
    out("};\n");
    nl();

    out("CIMPLE_NAMESPACE_END\n");
}

void gen_repository(const vector<string>& classes)
{
    // Generate header:

    {
        //
        // Open the file.
        //

        const char FILENAME[] = "repository.h";

        if ((_os = fopen(FILENAME, "wb")) == 0)
        {
            err("error: cannot open \"%s\"", FILENAME);
            exit(1);
        }

        //
        // Generate file.
        //

        gen_repository_header_file(classes);

        printf("created %s\n", FILENAME);

        //
        // Close the file.
        //

        fclose(_os);
    }

    // Generate source:

    {
        // Open the file.

        const char FILENAME[] = "repository.cpp";

        if ((_os = fopen(FILENAME, "wb")) == 0)
        {
            err("error: cannot open \"%s\"", FILENAME);
            exit(1);
        }

        // Generate file.

        gen_repository_source_file(classes);
        printf("Created %s\n", FILENAME);
        fclose(_os);
        _append_genmak(FILENAME);
    }
}

//static bool legal_class_name(const string& ident)
//{
//    const char* p = ident.c_str();
//
//    if (!isalpha(*p) && *p != '_')
//        return false;
//
//    while (isalnum(*p) || *p == '_')
//        p++;
//
//    return *p == '\0';
//}

//void load_class_list_file(vector<string>& classes, const string& path)
//{
//    FILE* is = fopen(path.c_str(), "r");
//
//    if (!is)
//        err("failed to open class list input file \"%s\"", path.c_str());
//
//    char buffer[1024];
//
//    for (int line = 1; fgets(buffer, sizeof(buffer), is) != NULL; line++)
//    {
//        if (buffer[0] == '#')
//            continue;
//
//        char* start = buffer;
//
//        /* Remove leading whitespace. */
//
//        while (isspace(*start))
//            start++;
//
//        /* Remove trailing whitespace. */
//
//        char* p = start;
//
//        while (*p)
//            p++;
//
//        while (p != start && isspace(p[-1]))
//            *--p = '\0';
//
//        /* Skip empty lines. */
//
//        if (*start == '\0')
//            continue;
//
//        /* Check whether legal class name. */
//
//        if (!legal_class_name(start))
//        {
//            err("illegal class name on line %d of %s: \"%s\"",
//                line, path.c_str(), start);
//        }
//
//        /* Append class to list. */
//
//        append_unique(classes, start);
//    }
//
//    fclose(is);
//}

int main(int argc, char** argv)
{
    arg0 = argv[0];
    set_arg0(arg0);
    vector<string> mof_files;
    vector<string> extra_mof_files;

    MOF_Options::warn = true;

    // Remove .genclass file if any.

    unlink(".genclass");

    if (verbose_opt )
    {
        printf("Remove any existing .genclass");
    }
    // Add the current directory to the search path:

    MOF_include_paths[MOF_num_include_paths++] = ".";

    // Process command-line options.

    for (int opt; (opt = getopt(argc, argv, "SI:M:hrVvlesqdbf:F:H")) != -1; )
    {
        switch (opt)
        {
            case 'I':
            {
                if (!optarg)
                {
                    err("missing argument on -I option");
                    exit(1);
                }

                if (MOF_num_include_paths == MAX_INCLUDES)
                {
                    err("too many -I options");
                    exit(1);
                }

                MOF_include_paths[MOF_num_include_paths++] = optarg;
                break;
            }

            case 'M':
            {
                if (!optarg)
                {
                    err("missing argument on -M option");
                    exit(1);
                }

                extra_mof_files.push_back(optarg);
                break;
            }

            case 'h':
                printf("%s", (char*)USAGE);
                exit(0);
                break;

            case 'V':
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
                break;

            case 'r':
                gen_repository_opt = true;
                break;

            case 'v':
                verbose_opt = true;
                break;
            case 'l':
                linkage_opt = true;
                break;

            case 'e':
                enum_opt = true;
                break;

            case 's':
                schema_opt = true;
                break;

            case 'q':
                qualifier_opt = true;
                break;

            case 'd':
                descriptions_opt = true;
                break;

            case 'b':
                boolean_qualifiers_opt = true;
                break;

            case 'f':
            case 'F':
			 {
                if (!optarg)
                {
                    err("missing argument on -f or -F option");
                    exit(1);
                }

                class_list_file = optarg;
                break;
			}

            case 'S':
                sources_opt = true;
                break;

            default:
                err("invalid option: %c; try -h for help", opt);
                break;
        }
    }

    if (verbose_opt)
    {
        _print_include_paths();
    }

    // Build meta-repository symbol name:
    if (gen_repository_opt)
    {
        cimple::UUID uuid;
        cimple::create_uuid(uuid);
        char uuid_str[CIMPLE_UUID_STRING_SIZE];
        cimple::uuid_to_string(uuid, uuid_str);
        meta_repository_name = string("__meta_repository_") + string(uuid_str);

        if (verbose_opt)
            printf("Generate Repository option set."
                   "meta-repository name = %s\n",meta_repository_name.c_str());
    }

    // We expect at least one argument (or -f option)

    if (optind == argc && !schema_opt && class_list_file.size() == 0)
    {
        printf("Error: Classed defined (-F or -s or class arguments\n");
        printf("%s",(char*)USAGE);
        exit(1);
    }

    // Setup the MOF include path.

    setup_mof_path(verbose_opt);

    // Load the repository:

    load_repository(extra_mof_files, verbose_opt);

    // Read class list file given by -f (if any).

    vector<string> classes;

    if (class_list_file.size())
        load_class_list_file(classes, class_list_file);

    // Get class list from command line and add to list of
    // classes to process

    for (int i = optind; i < argc; i++)
        append_unique(classes, argv[i]);

    // if schema opt set, generate the entire CIM Schema
    if (schema_opt)
    {
        // Generate entire CIM schema:

        if (verbose_opt)
        {
            printf("Generate complete Schema\n");
        }

        for (const MOF_Class_Decl* p = MOF_Class_Decl::list; p; 
            p = (const MOF_Class_Decl*)(p->next))
        {
            generate_class(p->name);
        }
    }

    if (verbose_opt)
    {
        bool first = true;
        printf("Class list =");
        for (size_t i = 0; i < classes.size(); i++)
        {
            printf("%s %s", (first? " ":", "), classes[i].c_str());
            first = false;
        }
        printf("\n");
    }

    for (size_t i = 0; i < classes.size(); i++)
        generate_class(classes[i].c_str());

    // Generate the repository:

    if (gen_repository_opt)
        gen_repository(_generated_classes);

    return 0;
}
