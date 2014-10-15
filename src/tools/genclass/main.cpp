/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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
#include <cimple/version.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <set>
#include <cstdarg>
#include <string>
#include <util/util.h>
#include <util/crc.h>
#include <tools/gencommon/gencommon.h>
#include "usage.h"
#include "MOF_Parser.h"

using namespace std;

const char* arg0;
static FILE* _os = 0;
bool linkage_opt = false;
bool enum_opt = false;

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

size_t find(vector<string>& array, const string& x)
{
    for (size_t i = 0; i < array.size(); i++)
    {
	if (array[i] == x)
	    return i;
    }

    return size_t(-1);
}

void append_unique(vector<string>& array, const string& x)
{
    size_t pos = find(array, x);

    if (pos == size_t(-1))
	array.push_back(x);
}

void print(vector<string>& array)
{
    for (size_t i = 0; i < array.size(); i++)
	printf("[%s]\n", array[i].c_str());
}

void nl()
{
    fputc('\n', _os);
}

static void out(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(_os, format, ap);
    va_end(ap);
}

#if 0
static void _print_include_paths()
{
    for (size_t i = 0; i < MOF_num_include_paths; i++)
	printf("MOF_include_paths[%u]=\"%s\"\n", (int)i, MOF_include_paths[i]);
}
#endif

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

void gen_property_decl(const MOF_Property_Decl* prop)
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

	    out("    struct\n");
	    out("    {\n");
	    out("        enum\n");
	    out("        {\n");

	    for (size_t i = 0; i < values.size(); i++)
	    {
		out("            ");
		out("enum_%s = %ld,\n", values[i].c_str(), value_map[i]);
	    }

	    out("        };\n");

	    out("        %s value;\n", _to_string(prop->data_type));
	    out("        uint8 null;\n");
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
	out("    Property<Array_%s> %s;\n", 
	    tmp, prop->name);
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
		out("    Instance* %s;\n", prop->name);
	    else
		gen_property_decl(prop);

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
			out("    %s* %s;\n", qref->class_name, qref->name);
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
    out("// PLEASE DO NOT EDIT THIS FILE; IT WAS ");
    out("AUTOMATICALLY GENERATED BY GENCLASS.\n");
    out("//\n");
    gen_comment_line(80);
}

void gen_class_decl(const MOF_Class_Decl* class_decl)
{
    const char* class_name = class_decl->name;
    MOF_Class_Decl* super_class = class_decl->super_class;

    // Generate class definition.

    const char* linkage = linkage_opt ? "CIMPLE_LINKAGE " : "";

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
	out("    Property<%s> %s;\n", tmp, param->name);
    }
    else
    {
	/* VLA */
	out("    Property<Array_%s> %s;\n", tmp, param->name);
    }
}

void gen_param_decls(
    const char* class_name, 
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

    // Generate class definition.

    const char* linkage = linkage_opt ? "CIMPLE_LINKAGE " : "";

    out("class %s%s_%s_method : public Instance\n", 
	linkage, class_name, meth_name);

    out("{\n");
    out("public:\n");
    gen_param_decls(class_name, meth_decl);
    out("    Property<%s> return_value;\n", _to_string(meth_decl->data_type));
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
	    if (strcasecmp(class_decl->name, p->class_origin->name) == 0)
		gen_meth_decl(class_decl->name, meth);
	    else
		gen_meth_typedef(class_decl->name, p->class_origin->name, meth);
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

void gen_header_file(const MOF_Class_Decl* class_decl)
{
    gen_comment_block();
    nl();

    out("#ifndef _%s_h\n", class_decl->name);
    out("#define _%s_h\n", class_decl->name);
    nl();

    out("#include <cimple/cimple.h>\n");

    if (class_decl->super_class)
	out("#include \"%s.h\"\n", class_decl->super_class->name);

    generate_ref_includes(class_decl);
    generate_param_ref_includes(class_decl);

    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    gen_class_decl(class_decl);

    gen_meth_decls(class_decl);

    out("CIMPLE_NAMESPACE_END\n");
    nl();

    out("#endif /* _%s_h */\n", class_decl->name);
}

void gen_property_def(
    const char* class_name,
    const char* propagating_class_name,
    const MOF_Property_Decl* prop)
{
    // Write external definition (whether propagated or not).

    out("extern CIMPLE_HIDE const Meta_Property _%s_%s;\n", 
	propagating_class_name, prop->name);
    nl();

    // Go no further if property is propagated.

    if (strcasecmp(class_name, propagating_class_name) != 0)
	return;

    // Generate property definition.

    out("const Meta_Property _%s_%s =\n", class_name, prop->name);
    out("{\n");

    // Flags field:

    {
	out("    CIMPLE_FLAG_PROPERTY");

	if (prop->qual_mask & MOF_QT_KEY)
	    out("|CIMPLE_FLAG_KEY");

	out(",\n");
    }

    // Name field:

    out("    \"%s\",\n", prop->name);

    // Print type:

    {
	string tmp = toupper(MOF_Data_Type::to_string(prop->data_type));
	out("    %s,\n", tmp.c_str());
    }

    // Print array subscript:

    out("    %d,\n", prop->array_index);

    // Print offset to field.

    out("    CIMPLE_OFF(%s,%s)\n", class_name, prop->name);

    out("};\n");
    nl();
}

void gen_reference_def(
    const char* class_name,
    const char* propagating_class_name,
    const MOF_Reference_Decl* ref)
{
    // Write external definition (whether propagated or not).
    out("extern CIMPLE_HIDE const Meta_Reference _%s_%s;\n", 
	propagating_class_name, ref->name);
    nl();

    // If propagated, go no further.

    if (strcasecmp(class_name, propagating_class_name) != 0)
	return;

    // Write the reference declaration.

    out("const Meta_Reference _%s_%s =\n", 
	class_name, ref->name);
    out("{\n");

    // Flags field:

    {
	out("    CIMPLE_FLAG_REFERENCE");

	if (ref->qual_mask & MOF_QT_KEY)
	    out("|CIMPLE_FLAG_KEY");

	out(",\n");
    }

    // Name:

    {
	out("    \"%s\",\n", ref->name);
    }

    // Meta class:

    {
	out("    &%s::static_meta_class,\n" , ref->class_name);
    }

    // Print offset to field.

    out("    CIMPLE_OFF(%s,%s)\n", class_name, ref->name);
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
	out("static const Meta_Reference _%s_%s_%s =\n",
	    class_name, meth_name, param->name);
	out("{\n");
    }

    // Flags:
    {
	out("    CIMPLE_FLAG_REFERENCE");

	if (param->qual_mask & MOF_QT_IN)
	    out("|CIMPLE_FLAG_IN");

	if (param->qual_mask & MOF_QT_OUT)
	    out("|CIMPLE_FLAG_OUT");

	out(",\n");
    }

    // Name:
    {
	out("    \"%s\",\n", param->name);
    }

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

    out("static const Meta_Property _%s_%s_%s =\n",
	class_name, meth_name, param->name);
    out("{\n");

    /// Flags:

    {
	out("    CIMPLE_FLAG_PROPERTY");

	if (param->qual_mask & MOF_QT_IN)
	    out("|CIMPLE_FLAG_IN");

	if (param->qual_mask & MOF_QT_OUT)
	    out("|CIMPLE_FLAG_OUT");

	out(",\n");
    }

    /// Name:

    out("    \"%s\",\n", param->name);

    /// Type:

    string tmp = toupper(MOF_Data_Type::to_string(param->data_type));
    out("    %s,\n", tmp.c_str());

    /// Subscript:

    out("    %d,\n", param->array_index);

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
    out("static Meta_Feature* _%s_%s_meta_features[] =\n", 
	class_name, meth->name);
    out("{\n");

    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
	out("    (Meta_Feature*)&_%s_%s_%s,\n", class_name, meth->name, 
	    p->name);
    }

    out("    (Meta_Feature*)&_%s_%s_return_value\n", class_name, meth->name);

    out("};\n");
    nl();
}

void gen_meth_return_def(
    const char* class_name,
    const MOF_Method_Decl* meth)
{
    // Preamble:

    out("static const Meta_Property _%s_%s_return_value =\n",
	class_name, meth->name);
    out("{\n");

    // Flags:

    out("    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,\n");

    // Name:

    out("    \"return_value\",\n");

    // Type:

    string tmp = toupper(MOF_Data_Type::to_string(meth->data_type));
    out("    %s,\n", tmp.c_str());

    // Subscript:

    out("    0,\n");

    // Offset:

    out("    CIMPLE_OFF(%s_%s_method,return_value)\n", 
	class_name, meth->name);

    // Postamble:

    out("};\n\n");
}

void gen_method_def(
    const MOF_Method_Decl* meth, 
    const char* class_name)
{
    // Generate parameter definitions.

    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
	if (p->data_type == TOK_REF)
	    gen_param_ref_def(class_name, meth->name, p);
	else
	    gen_param_prop_def(class_name, meth->name, p);
    }

    // Generate the return value.

    gen_meth_return_def(class_name, meth);

    // Parameter array

    gen_param_array(class_name, meth);

    // Preamble:

    out("const Meta_Method %s_%s_method::static_meta_class =\n", 
	class_name, meth->name);

    out("{\n");

    // Flags:

    out("    CIMPLE_FLAG_METHOD");

    if (meth->qual_mask & MOF_QT_STATIC)
	out("|CIMPLE_FLAG_STATIC");

    out(",\n");

    // Name:

    out("    \"%s\",\n", meth->name);

    // Feature array.

    out("    _%s_%s_meta_features,\n", class_name, meth->name);
    out("    CIMPLE_ARRAY_SIZE(_%s_%s_meta_features),\n", 
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

static const char _embedded_object_format[] =
    "const Meta_Reference _%s_%s =\n"
    "{\n"
    "    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,\n"
    "    \"%s\",\n"
    "    &Instance_meta_class,\n"
    "    CIMPLE_OFF(%s,%s)\n"
    "};\n"
    "\n";

void gen_embedded_object_def(
    const char* class_name, 
    const char* propagating_class_name, 
    const MOF_Property_Decl* prop)
{
    out("extern CIMPLE_HIDE const Meta_Reference _%s_%s;\n\n", 
	propagating_class_name, prop->name);

    if (strcasecmp(class_name, propagating_class_name) == 0)
    {
	out(_embedded_object_format, class_name, prop->name,
	    prop->name, class_name, prop->name, class_name, prop->name);
    }
}

const char* find_propagating_class(
    const MOF_Class_Decl* class_decl,
    const char* feature_name)
{
    // Find the name of the class that propagated this property:

    // Search the current class first:

    MOF_Feature_Info* p = class_decl->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
	if (!p->propagated && strcasecmp(p->feature->name, feature_name) == 0)
	    return class_decl->name;
    }

    // Now search the super class (if any)

    if (class_decl->super_class)
    {
	const char* class_name = find_propagating_class(
	    class_decl->super_class, feature_name);

	if (class_name)
	    return class_name;
    }

    // Not found!
    return 0;
}

void gen_feature_defs(const MOF_Class_Decl* class_decl)
{
    MOF_Feature_Info* p = class_decl->all_features;
    const char* class_name = class_decl->name;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
	MOF_Feature* feature = p->feature;

	MOF_Property_Decl* prop = dynamic_cast<MOF_Property_Decl*>(feature);

	// Find class that propagated this feature.

	const char* propagating_class_name = 
	    find_propagating_class(class_decl, feature->name);

	// Property.

	if (prop)
	{
	    if (prop->qual_mask & MOF_QT_EMBEDDEDOBJECT)
	    {
		gen_embedded_object_def(
		    class_name, propagating_class_name, prop);
	    }
	    else
	    {
		gen_property_def(
		    class_name, propagating_class_name, prop);
	    }
	}

	// Reference.

	MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(feature);

	if (ref)
	{
	    gen_reference_def(
		class_name, propagating_class_name, ref);
	}

	MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(feature);

	if (meth && !p->propagated)
	    gen_method_def(meth, class_decl->name);
    }
}

void gen_feature_array(const MOF_Class_Decl* class_decl)
{
    MOF_Feature_Info* p = class_decl->all_features;

    out("static Meta_Feature* _%s_meta_features[] =\n", class_decl->name);
    out("{\n");

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
	MOF_Feature* feature = p->feature;

	// Find name of class that propagated this feature.

	const char* class_name = 
	    find_propagating_class(class_decl, feature->name);

	if (!class_name)
	    err("unexpected error");

	// Property.

	MOF_Property_Decl* prop = dynamic_cast<MOF_Property_Decl*>(feature);

	if (prop)
	    out("    (Meta_Feature*)&_%s_%s,\n", class_name, prop->name);

	// Reference.

	MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(feature);

	if (ref)
	    out("    (Meta_Feature*)&_%s_%s,\n", class_name, ref->name);

	// Method.

	MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(feature);

	if (meth)
	{
	    out("    (Meta_Feature*)&%s_%s_method::static_meta_class,\n", 
		p->class_origin->name, meth->name);
	}
    }

    out("};\n");
    nl();
}

void gen_class_def(const MOF_Class_Decl* class_decl)
{
    out("const Meta_Class %s::static_meta_class =\n", 
	class_decl->name);
    out("{\n");

    // Flags:
    {
	if (class_decl->qual_mask & MOF_QT_ASSOCIATION)
	    out("    CIMPLE_FLAG_ASSOCIATION,\n");
	else if (class_decl->qual_mask & MOF_QT_INDICATION)
	    out("    CIMPLE_FLAG_INDICATION,\n");
	else
	    out("    CIMPLE_FLAG_CLASS,\n");
    }

    // Name:
    {
	out("    \"%s\",\n", class_decl->name);
    }

    // Features:
    {
	out("    _%s_meta_features,\n", class_decl->name);
	out("    CIMPLE_ARRAY_SIZE(_%s_meta_features),\n", class_decl->name);
    }

    // Size:
    {
	out("    sizeof(%s),\n", class_decl->name);
    }

    // Superclass:

    if (class_decl->super_class)
    {
	out("    &%s::static_meta_class,\n", class_decl->super_class->name);
    }
    else
    {
	out("    0,\n");
    }

    // Number of keys.
    {
	out("    %u,\n", _count_keys(class_decl));
    }

    // CRC:

    {
	string sig;
	make_signature(class_decl, sig);
	unsigned int crc = crc_compute((unsigned char*)sig.c_str(), sig.size());
	out("    0x%08X,\n", crc);
    }

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

    // Generate class meta data.

    gen_feature_defs(class_decl);
    gen_feature_array(class_decl);
    gen_class_def(class_decl);

    out("CIMPLE_NAMESPACE_END\n");
    nl();
}

void generate_ancestor_classes(const char* class_name);
void generate_ref_clases(const char* class_name);
void generate_param_ref_clases(const char* class_name);

typedef set<string> Duplicate_Classes;
Duplicate_Classes duplicate_classes;

static vector<string> _generated_classes;

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

    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
	err("error: no such class: \"%s\"", class_name);
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
	
	if ((_os = fopen(buffer, "wb")) == 0)
	{
	    err("error: cannot open \"%s\"", buffer);
	    exit(1);
	}

	gen_header_file(class_decl);

	fclose(_os);
	printf("Created %s\n", buffer);
    }

    // Generate source file:

    {
	char buffer[1024];
	sprintf(buffer, "%s.cpp", class_name);
	
	if ((_os = fopen(buffer, "wb")) == 0)
	{
	    err("error: cannot open \"%s\"", buffer);
	    exit(1);
	}

	gen_source_file(class_decl);

	fclose(_os);
	printf("Created %s\n", buffer);
    }
}

void generate_ancestor_classes(const char* class_name)
{
    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
	err("error: no such class: \"%s\"", class_name);
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
	err("error: no such class: \"%s\"", class_name);
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

void generate_param_ref_clases(const char* class_name)
{
    // Find the class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
    {
	err("error: no such class: \"%s\"", class_name);
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

    out("CIMPLE_ENTRY_POINT void cimple_repository(\n");
    out("    const Meta_Class* const*& meta_classes,\n");
    out("    size_t& num_meta_classes);\n");
    nl();

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

    out("static const Meta_Class* _meta_classes[] =\n");
    out("{\n");

    for (size_t i = 0; i < classes.size(); i++)
	out("    &%s::static_meta_class,\n", classes[i].c_str());

    out("};\n");
    nl();
    out("static const size_t _num_meta_classes = ");
    out("CIMPLE_ARRAY_SIZE(_meta_classes);\n");
    nl();

    out("CIMPLE_ENTRY_POINT void cimple_repository(\n");
    out("    const Meta_Class* const*& meta_classes,\n");
    out("    size_t& num_meta_classes)\n");
    out("{\n");
    out("   meta_classes = _meta_classes; \n");
    out("   num_meta_classes = _num_meta_classes; \n");
    out("}\n");
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
	//
	// Open the file.
	//

	const char FILENAME[] = "repository.cpp";

	if ((_os = fopen(FILENAME, "wb")) == 0)
	{
	    err("error: cannot open \"%s\"", FILENAME);
	    exit(1);
	}

	//
	// Generate file.
	//

	gen_repository_source_file(classes);

	//
	// Generate entry point: cimple_repository()
	//

	printf("Created %s\n", FILENAME);

	//
	// Close the file.
	//

	fclose(_os);
    }
}

CIMPLE_INJECT_VERSION_TAG;

int main(int argc, char** argv)
{
    arg0 = argv[0];
    set_arg0(arg0);
    vector<string> mof_files;
    vector<string> extra_mof_files;

    // Add the current directory to the search path:

    MOF_include_paths[MOF_num_include_paths++] = ".";

    // Process command-line options.

    bool gen_repository_opt = false;

    for (int opt; (opt = getopt(argc, argv, "I:M:hrvle")) != -1; )
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
		printf((char*)USAGE);
		exit(0);
		break;

            case 'v':
		printf("genclass: version 0.91\n\n");
		exit(0);
		break;

            case 'r':
		gen_repository_opt = true;
		break;

            case 'l':
		linkage_opt = true;
		break;

            case 'e':
		enum_opt = true;
		break;

	    default:
		err("invalid option: %c; try -h for help", opt);
		break;
	}
    }

    // We expect at least one argument.

    if (optind == argc)
    {
	printf((char*)USAGE);
	exit(1);
    }

    // Setup the MOF include path.

    setup_mof_path();

    // Load the repository:

    load_repository(extra_mof_files);

    // Generate classes:

    vector<string> classes;

    for (int i = optind; i < argc; i++)
	append_unique(classes, argv[i]);

    for (size_t i = 0; i < classes.size(); i++)
	generate_class(classes[i].c_str());

    // Generate the repository:

    if (gen_repository_opt)
	gen_repository(_generated_classes);

    return 0;
}
