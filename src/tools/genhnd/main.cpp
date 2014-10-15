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

#include <cimple/config.h>
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
#include <tools/gencommon/gencommon.h>
#include "usage.h"
#include <mof/MOF_Parser.h>

using namespace std;

const char* arg0;
typedef set<string> Duplicate_Classes;
Duplicate_Classes duplicate_classes;
static vector<string> _generated_classes;
static FILE* _os = 0;
bool schema_opt = false;

static bool _contains(const vector<string>& v, const string& s)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (strcasecmp(v[i].c_str(), s.c_str()) == 0)
            return true;
    }

    return false;
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

const char* get_embedded_class_name(const MOF_Qualified_Element* mqe)
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

static size_t ind = 0;

static
CIMPLE_PRINTF_ATTR(1, 2)
void out(const char* format, ...)
{
    for (size_t i = 0; i < ind; i++)
        fprintf(_os, "    ");

    va_list ap;
    va_start(ap, format);
    vfprintf(_os, format, ap);
    va_end(ap);
}

static inline const char* _to_string(int data_type)
{
    if (data_type == TOK_STRING)
        return "String";
    else if (data_type == TOK_DATETIME)
        return "Datetime";

    return MOF_Data_Type::to_string(data_type);
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
    out("AUTOMATICALLY GENERATED BY GENHND.\n");
    out("//\n");
    gen_comment_line(80);
}

void gen_method_head(
    const MOF_Class_Decl* cd, 
    const MOF_Method_Decl* md,
    bool decl)
{
    const char* fn = md->name;
    const char* ecn;

    // Indent:

    if (decl)
        out("    ");

    // Static modifier:

    if (decl)
    {
        if (md->qual_mask & MOF_QT_STATIC)
            out("static ");
    }
    else
        out("inline ");

    // Return type:

    if (md->qual_mask & MOF_QT_EMBEDDEDOBJECT)
        out("Arg<Instance_Hnd> ");
    else if ((ecn = get_embedded_class_name(md)))
        out("Arg<%s_Hnd> ", ecn);
    else
        out("Arg<%s> ", _to_string(md->data_type));

    // Method name:

    if (decl)
        out("%s(\n", md->name);
    else
        out("%s_Ref::%s(\n", cd->name, md->name);

    // Indent:

    if (decl)
        out("        ");
    else
        out("    ");

    out("Ops& __ops,\n");

    if (decl)
        out("        ");
    else
        out("    ");

    out("const String& __name_space");

    for (MOF_Parameter* p = md->parameters; p; p =(MOF_Parameter*)p->next)
    {
        out(",\n");

        if (decl)
            out("        ");
        else
            out("    ");

        if (!(p->qual_mask & MOF_QT_OUT))
            out("const ");

        if (p->qual_mask & MOF_QT_EMBEDDEDOBJECT)
        {
            if (p->array_index)
                out("Arg< Array<Instance_Hnd> >& %s", p->name);
            else
                out("Arg<Instance_Hnd>& %s", p->name);
        }
        else if ((ecn = get_embedded_class_name(p)))
        {
            if (p->array_index)
                out("Arg< Array<%s_Hnd> >& %s", ecn, p->name);
            else
                out("Arg<%s_Hnd>& %s", ecn, p->name);
        }
        else if (p->data_type == TOK_REF)
        {
            if (p->array_index)
                out("Arg< Array<%s_Ref> >& %s", p->ref_name, p->name);
            else
                out("Arg<%s_Ref>& %s", p->ref_name, p->name);
        }
        else
        {
            if (p->array_index == 0)
                out("Arg<%s>& %s", _to_string(p->data_type), p->name);
            else
                out("Arg<Array_%s>& %s", _to_string(p->data_type), p->name);
        }
    }

    if (decl)
    {
        out(");\n");
        nl();
    }
    else
        out(")\n");
}

void gen_method_body(
    const MOF_Class_Decl* cd, 
    const MOF_Method_Decl* md)
{
    out("{\n");

    // Declare return type:
    {
        out("    ");

        const char* ecn;

        if (md->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            out("Arg<Instance_Hnd> __return_value;\n");
        else if ((ecn = get_embedded_class_name(md)))
            out("Arg<%s_Hnd> __return_value;\n", ecn);
        else
            out("Arg<%s> __return_value;\n", _to_string(md->data_type));
    }

    // Invoke function:

    out("    __invoke(\n");
    out("        __ops,\n");
    out("        __name_space,\n");

    if (md->qual_mask & MOF_QT_STATIC)
        out("        %s_Ref(),\n", cd->name);
    else
        out("        *this,\n");

    out("        &%s_%s_method::static_meta_class,\n", cd->name, md->name);

    // Generate parameters.

    for (MOF_Parameter* p = md->parameters; p; p =(MOF_Parameter*)p->next)
    {
        out("        &%s,\n", p->name);
    }

    out("        &__return_value);\n");

    out("    return __return_value;\n");

    out("}\n");
    nl();
}

void gen_handle_decl(const MOF_Class_Decl* cd, bool ref)
{
    // Base class name:

    const char* bcn = ref ? "Instance_Ref" : "Instance_Hnd";

    // Class name:

    char cn[1024];
    sprintf(cn, "%s_%s", cd->name, (ref ? "Ref" : "Hnd"));

    // Super class name:

    char scn[1024];

    if (cd->super_class)
        sprintf(scn, "%s_%s", cd->super_class->name, (ref ? "Ref" : "Hnd"));
    else
        strcpy(scn, bcn);

    // Class header:

    out("class %s : public %s\n", cn, scn);

    // Class body:

    out("{\n");
    out("public:\n");

    ind++;
    out("typedef %s Class;\n", cd->name);

    out("%s();\n", cn);

    out("%s(const %s& x);\n", cn, cn);

    out("%s(%s* inst);\n", cn, cd->name);

    out("explicit %s(const %s& x);\n", cn, bcn);

    out("~%s();\n", cn);

    out("%s& operator=(const %s& x);\n", cn, cn);

    out("static bool is_a(const %s& x);\n", bcn);

    if (!ref)
        out("%s_Ref reference() const;\n", cd->name);

    nl();

    // Generate properties and references:

    for (const MOF_Feature* p = cd->features; p; p = (MOF_Feature*)p->next)
    {
        const char* fn = p->name;

        // Skip non-keys?

        if (ref && !(p->qual_mask & MOF_QT_KEY))
            continue;

        // Property.

        const MOF_Property_Decl* pd;
        const MOF_Reference_Decl* rd;

        if ((pd = dynamic_cast<const MOF_Property_Decl*>(p)))
        {
            out("// %s:\n", fn);

            const char* ecn = 0;

            if (pd->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            {
                if (pd->array_index)
                {
                    out("Array<%s> %s_value() const;\n", bcn, fn);
                    out("void %s_value(const Array<%s>& x);\n", fn, bcn);
                    out("bool %s_null() const;\n", fn);
                    out("void %s_clear();\n", fn);
                }
                else
                {
                    out("%s %s_value() const;\n", bcn, fn);
                    out("void %s_value(const %s& x);\n", fn, bcn);
                    out("bool %s_null() const;\n", fn);
                    out("void %s_clear();\n", fn);
                }
            }
            else if ((ecn = get_embedded_class_name(pd)))
            {
                if (pd->array_index)
                {
                    out("Array<%s_Hnd> %s_value() const;\n", ecn, fn);
                    out("void %s_value(const Array<%s_Hnd>& x);\n", fn, ecn);
                    out("bool %s_null() const;\n", fn);
                    out("void %s_clear();\n", fn);
                }
                else
                {
                    out("%s_Hnd %s_value() const;\n", ecn, fn);
                    out("void %s_value(const %s_Hnd& x);\n", fn, ecn);
                    out("bool %s_null() const;\n", fn);
                    out("void %s_clear();\n", fn);
                }
            }
            else
            {
                char tn[1024];

                if (pd->array_index == 0)
                    sprintf(tn, "%s", _to_string(pd->data_type));
                else
                    sprintf(tn, "Array_%s", _to_string(pd->data_type));

                out("const %s& %s_value() const;\n", tn, fn);
                out("void %s_value(const %s& x);\n", fn, tn);
                out("bool %s_null() const;\n", fn);
                out("void %s_clear();\n", fn);
            }
            nl();
        }
        else if ((rd = dynamic_cast<const MOF_Reference_Decl*>(p)))
        {
            out("// %s:\n", fn);
            out("%s_Ref %s_value() const;\n", rd->class_name, fn);
            out("void %s_value(const %s_Ref& x);\n", fn, rd->class_name);
            out("bool %s_null() const;\n", fn);
            out("void %s_clear();\n", fn);
            nl();
        }
    }

    ind--;

    // Generate methods (references only):

    if (ref)
    {
        for (const MOF_Feature* p = cd->features; p; p = (MOF_Feature*)p->next)
        {
            const MOF_Method_Decl* md;

            if ((md = dynamic_cast<const MOF_Method_Decl*>(p)))
                gen_method_head(cd, md, true);
        }
    }

    // Private members:

    out("protected:\n");
    out("    %s(const Meta_Class* mc);\n", cn);
    out("    %s(const Meta_Class* mc, const %s& x);\n", cn, bcn);

    out("};\n");

    nl();
}

void gen_handle_def(const MOF_Class_Decl* cd, bool ref)
{
    // Base class name:

    const char* bcn = ref ? "Instance_Ref" : "Instance_Hnd";

    // Class name:

    char cn[1024];
    sprintf(cn, "%s_%s", cd->name, (ref ? "Ref" : "Hnd"));

    // Super class name:

    char scn[1024];
    char pcn[1024];

    if (cd->super_class)
    {
        strcpy(pcn, cd->super_class->name);
        sprintf(scn, "%s_%s", cd->super_class->name, (ref ? "Ref" : "Hnd"));
    }
    else
    {
        strcpy(pcn, "Instance");
        strcpy(scn, bcn);
    }

    // T::T()

    out("inline %s::%s() :\n", cn, cn);
    out("    %s(&%s::static_meta_class)\n", scn, cd->name);
    out("{\n");
    out("}\n");
    nl();

    // T::T(const T& x)

    out("inline %s::%s(const %s& x) :\n", cn, cn, cn);
    out("    %s(x)\n", scn);
    out("{\n");
    out("}\n");
    nl();

    // T::T(const C* inst)

    out("inline %s::%s(%s* inst) :\n", cn, cn, cd->name);
    out("    %s((%s*)inst)\n", scn, pcn);
    out("{\n");
    out("}\n");
    nl();

    // T::T(const C& x)

    out("inline %s::%s(const %s& x) : \n", cn, cn, bcn);
    out("    %s(&%s::static_meta_class, x)\n", scn, cd->name);
    out("{\n");
    out("}\n");
    nl();

    // T::T(const Meta_Class* mc)

    out("inline %s::%s(const Meta_Class* mc) : %s(mc)\n", cn, cn, scn);
    out("{\n");
    out("}\n");
    nl();

    // T::T(const Meta_Class* mc, const X& x)

    out("inline %s::%s(const Meta_Class* mc, const %s& x) : %s(mc, x)\n", 
        cn, cn, bcn, scn);
    out("{\n");
    out("}\n");
    nl();

    // T::~T()

    out("inline %s::~%s()\n", cn, cn);
    out("{\n");
    out("}\n");
    nl();

    // T& operator=(const T& x)

    out("inline %s& %s::operator=(const %s& x)\n", cn, cn, cn);
    out("{\n");
    out("    %s::operator=(x);\n", scn);
    out("    return *this;\n");
    out("}\n");
    nl();

    // is_a()

    out("inline bool %s::is_a(const %s& x)\n", cn, bcn);
    out("{\n");
    out("    return is_subclass(&%s::static_meta_class, x.meta_class());\n",
        cd->name);
    out("}\n");
    nl();

    // reference()

    if (!ref)
    {
        out("inline %s_Ref %s::reference() const\n", cd->name, cn);
        out("{\n");
        out("    return %s_Ref((%s*)key_clone(_inst));\n", cd->name, cd->name);
        out("}\n");
        nl();
    }

    // Features.

    const MOF_Feature* p = cd->features;

    for (; p; p = (const MOF_Feature*)p->next)
    {
        const char* fn = p->name;

        char fr[1024];
        sprintf(fr, "((Class*)_inst)->%s", fn);

        // Skip non-keys?

        if (ref && !(p->qual_mask & MOF_QT_KEY))
            continue;

        const MOF_Property_Decl* pd;
        const MOF_Reference_Decl* rd;

        if ((pd = dynamic_cast<const MOF_Property_Decl*>(p)))
        {
            const char* ecn = 0;

            if (pd->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            {
                if (pd->array_index)
                {
                    out("inline Array<%s> %s::%s_value() const\n", 
                        bcn, cn, fn);
                    out("{\n");
                    out("    Array<%s> tmp;\n", bcn);
                    out("    _get_inst_array(&%s, &tmp);\n", fr);
                    out("    return tmp;\n");
                    out("}\n");
                    nl();

                    out("inline void %s::%s_value(const Array<%s>& x)\n", 
                        cn, fn, bcn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    _set_inst_array(&%s, &x);\n", fr);
                    out("    %s.null = 0;\n", fr);
                    out("}\n");
                    nl();

                    out("inline bool %s::%s_null() const\n", cn, fn);
                    out("{\n");
                    out("    return %s.null;\n", fr);
                    out("}\n");
                    nl();

                    out("inline void %s::%s_clear()\n", cn, fn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    _clear_inst_array(&%s);\n", fr);
                    out("    %s.null = 1;\n", fr);
                    out("}\n");
                    nl();
                }
                else
                {
                    out("inline %s %s::%s_value() const\n", bcn, cn, fn);
                    out("{\n");
                    out("    if (!%s)\n", fr);
                    out("        _throw_null_access(\"%s\");\n", fn);
                    out("    ref(%s);\n", fr);
                    out("    return %s(%s);\n", bcn, fr);
                    out("}\n");
                    nl();

                    out("inline void %s::%s_value(const %s& x)\n", 
                        cn, fn, bcn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    unref(%s);\n", fr);
                    out("    ref(%s = (Instance*)x.instance());\n", fr);
                    out("}\n");
                    nl();

                    out("inline bool %s::%s_null() const\n", cn, fn);
                    out("{\n");
                    out("    return ((Class*)_inst)->%s == 0;\n", fn);
                    out("}\n");
                    nl();

                    out("inline void %s::%s_clear()\n", cn, fn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    unref(%s);\n", fr);
                    out("    %s = 0;\n", fr);
                    out("}\n");
                    nl();
                }
            }
            else if ((ecn = get_embedded_class_name(pd)))
            {
                if (pd->array_index)
                {
                    out("inline Array<%s_Hnd> %s::%s_value() const\n", 
                        ecn, cn, fn);
                    out("{\n");
                    out("    Array<%s_Hnd> tmp;\n", ecn);
                    out("    _get_inst_array(&%s, &tmp);\n", fr);
                    out("    return tmp;\n");
                    out("}\n");
                    nl();

                    out("inline void %s::%s_value(const Array<%s_Hnd>& x)\n", 
                        cn, fn, ecn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    _set_inst_array(&%s, &x);\n", fr);
                    out("    %s.null = 0;\n", fr);
                    out("}\n");
                    nl();

                    out("inline bool %s::%s_null() const\n", cn, fn);
                    out("{\n");
                    out("    return %s.null;\n", fr);
                    out("}\n");
                    nl();

                    out("inline void %s::%s_clear()\n", cn, fn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    _clear_inst_array(&%s);\n", fr);
                    out("    %s.null = 1;\n", fr);
                    out("}\n");
                    nl();
                }
                else
                {
                    out("inline %s_Hnd %s::%s_value() const\n", ecn, cn, fn);
                    out("{\n");
                    out("    if (!%s)\n", fr);
                    out("        _throw_null_access(\"%s\");\n", fn);
                    out("    ref(%s);\n", fr);
                    out("    return %s_Hnd(%s);\n", ecn, fr);
                    out("}\n");
                    nl();

                    out("inline void %s::%s_value(const %s_Hnd& x)\n", 
                        cn, fn, ecn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    unref(%s);\n", fr);
                    out("    ref(%s = (%s*)x.instance());\n", fr, ecn);
                    out("}\n");
                    nl();

                    out("inline bool %s::%s_null() const\n", cn, fn);
                    out("{\n");
                    out("    return ((Class*)_inst)->%s == 0;\n", fn);
                    out("}\n");
                    nl();

                    out("inline void %s::%s_clear()\n", cn, fn);
                    out("{\n");
                    out("    _cow();\n");
                    out("    unref(%s);\n", fr);
                    out("    %s = 0;\n", fr);
                    out("}\n");
                    nl();
                }
            }
            else
            {
                char tn[1024];

                if (pd->array_index == 0)
                    sprintf(tn, "%s", _to_string(pd->data_type));
                else
                    sprintf(tn, "Array_%s", _to_string(pd->data_type));

                out("inline const %s& %s::%s_value() const\n", tn, cn, fn);
                out("{\n");
                out("    if (%s.null)\n", fr);
                out("        _throw_null_access(\"%s\");\n", fn);
                out("   return %s.value;\n", fr);
                out("}\n");
                nl();

                out("inline void %s::%s_value(const %s& x)\n", cn, fn, tn);
                out("{\n");
                out("    _cow();\n");
                out("   %s.value = x;\n", fr);
                out("   %s.null = false;\n", fr);
                out("}\n");
                nl();

                out("inline bool %s::%s_null() const\n", cn, fn);
                out("{\n");
                out("   return %s.null;\n", fr);
                out("}\n");
                nl();

                out("inline void %s::%s_clear()\n", cn, fn);
                out("{\n");
                out("    _cow();\n");
                out("    __clear(%s.value);\n", fr);
                out("    %s.null = true;;\n", fr);
                out("}\n");
                nl();
            }
        }
        else if ((rd = dynamic_cast<const MOF_Reference_Decl*>(p)))
        {
            const char* rcn = rd->class_name;

            out("inline %s_Ref %s::%s_value() const\n", rcn, cn, fn);
            out("{\n");
            out("    if (!%s)\n", fr);
            out("        _throw_null_access(\"%s\");\n", fn);
            out("    ref(%s);\n", fr);
            out("    return %s_Ref(%s);\n", rcn, fr);
            out("}\n");
            nl();

            out("inline void %s::%s_value(const %s_Ref& x)\n", cn, fn, rcn);
            out("{\n");
            out("    _cow();\n");
            out("    unref(%s);\n", fr);
            out("    ref(%s = (%s*)x.instance());\n", fr, rcn);
            out("}\n");
            nl();

            out("inline bool %s::%s_null() const\n", cn, fn);
            out("{\n");
            out("    return %s == 0;\n", fr);
            out("}\n");
            nl();

            out("inline void %s::%s_clear()\n", cn, fn);
            out("{\n");
            out("    _cow();\n");
            out("    unref(%s);\n", fr);
            out("    %s = 0;\n", fr);
            out("}\n");
            nl();
        }
    }

    // Generate methods (references only):

    if (ref)
    {
        for (const MOF_Feature* p = cd->features; p; p = (MOF_Feature*)p->next)
        {
            const MOF_Method_Decl* md;

            if ((md = dynamic_cast<const MOF_Method_Decl*>(p)))
            {
                gen_method_head(cd, md, false);
                gen_method_body(cd, md);
            }
        }
    }
}

void gen_ref_includes(
    const MOF_Class_Decl* cd, 
    vector<string>& includes)
{
    MOF_Feature* p = cd->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(p);

        if (ref && !_contains(includes, ref->class_name))
        {
            out("#include \"%s_Hnd.h\"\n", ref->class_name);
            includes.push_back(ref->class_name);
        }
    }
}

void gen_param_ref_includes(
    const MOF_Class_Decl* cd, 
    vector<string>& includes)
{
    MOF_Feature* p = cd->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p);

        if (!meth)
            continue;

        for (MOF_Parameter* q = meth->parameters; q; q =(MOF_Parameter*)q->next)
        {
            if (q->data_type == TOK_REF && !_contains(includes, q->ref_name))
            {
                out("#include \"%s_Hnd.h\"\n", q->ref_name);
                includes.push_back(q->ref_name);
            }
        }
    }
}

void gen_embedded_includes(
    const MOF_Class_Decl* mcd, 
    vector<string>& includes)
{
    // Handle EmbeddedInstance on properties.
    {
        for (MOF_Feature* p = mcd->features; p; p = (MOF_Feature*)p->next)
        {
            MOF_Property_Decl* mpd = dynamic_cast<MOF_Property_Decl*>(p);

            if (mpd)
            {
                const char* ecn = get_embedded_class_name(mpd);

                if (ecn && !_contains(includes, ecn))
                {
                    out("#include \"%s_Hnd.h\"\n", ecn);
                    includes.push_back(ecn);
                }
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

                if (ecn && !_contains(includes, ecn))
                {
                    out("#include \"%s_Hnd.h\"\n", ecn);
                    includes.push_back(ecn);
                }
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

                if (ecn && !_contains(includes, ecn))
                {
                    out("#include \"%s_Hnd.h\"\n", ecn);
                    includes.push_back(ecn);
                }
            }
        }
    }
}

void gen_header_file(const MOF_Class_Decl* cd)
{
    vector<string> includes;

    gen_comment_block();
    nl();

    out("#ifndef _cimple_%s_Hnd\n", cd->name);
    out("#define _cimple_%s_Hnd\n", cd->name);
    nl();

    out("#include <cimple/cimple.h>\n");

    out("#include \"%s.h\"\n", cd->name);
    includes.push_back(cd->name);

    if (cd->super_class)
    {
        out("#include \"%s_Hnd.h\"\n", cd->super_class->name);
        includes.push_back(cd->super_class->name);
    }

    gen_ref_includes(cd, includes);
    gen_param_ref_includes(cd, includes);
    gen_embedded_includes(cd, includes);
    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    gen_handle_decl(cd, true);
    gen_handle_decl(cd, false);

    gen_handle_def(cd, true);
    gen_handle_def(cd, false);

    out("CIMPLE_NAMESPACE_END\n");
    nl();

    out("#endif /* _cimple_%s_Hnd_h */\n", cd->name);
}

static const MOF_Class_Decl* _find_class(const string& class_name)
{
    const MOF_Class_Decl* cd = 
        MOF_Class_Decl::find((char*)class_name.c_str());

    if (!cd)
    {
        err("error: no such class: \"%s\"", class_name.c_str());
        exit(1);
    }

    return cd;
}

void gen_class(const char* class_name)
{
    void gen_ancestor_classes(const char* class_name);
    void gen_ref_clases(const char* class_name);
    void gen_param_ref_clases(const char* class_name);
    void gen_embedded_classes(const char* class_name);

    // Avoid generating any class more than once:

    if (duplicate_classes.find(class_name) != duplicate_classes.end())
        return;

    duplicate_classes.insert(class_name);

    // Generate dependent classes:

    gen_ancestor_classes(class_name);
    gen_ref_clases(class_name);
    gen_param_ref_clases(class_name);
    gen_embedded_classes(class_name);

    // Find the class.

    const MOF_Class_Decl* cd = _find_class(class_name);

    // Remember all generated classes:

    _generated_classes.push_back(class_name);

    // Generate header file:
    {
        char path[1024];
        sprintf(path, "%s_Hnd.h", class_name);
        
        if ((_os = fopen(path, "wb")) == NULL)
            err("error: cannot open \"%s\"", path);

        gen_header_file(cd);

        fclose(_os);
        printf("Created %s\n", path);
    }
}

void gen_ancestor_classes(const char* class_name)
{
    const MOF_Class_Decl* cd = _find_class(class_name);
    const MOF_Class_Decl* scd = cd->super_class;

    if (!scd)
        return;

    gen_ancestor_classes(scd->name);
    gen_class(scd->name);
}

void gen_ref_clases(const char* class_name)
{
    const MOF_Class_Decl* cd = _find_class(class_name);
    MOF_Feature* p = cd->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Reference_Decl* ref = dynamic_cast<MOF_Reference_Decl*>(p);

        if (ref)
            gen_class(ref->class_name);
    }

    return;
}

void gen_param_ref_clases(const char* class_name)
{
    const MOF_Class_Decl* cd = _find_class(class_name);
    MOF_Feature* p = cd->features;

    for (; p; p = (MOF_Feature*)p->next)
    {
        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p);

        if (!meth)
            continue;

        for (MOF_Parameter* q = meth->parameters; q; q =(MOF_Parameter*)q->next)
        {
            if (q->data_type == TOK_REF)
                gen_class(q->ref_name);
        }
    }
}

void gen_embedded_classes(const char* class_name)
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
                    gen_class(ecn);
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
                    gen_class(ecn);
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
                    gen_class(ecn);
            }
        }
    }

    return;
}

int main(int argc, char** argv)
{
    arg0 = argv[0];
    set_arg0(arg0);
    vector<string> mof_files;
    vector<string> extra_mof_files;

    // Add the current directory to the search path:

    MOF_include_paths[MOF_num_include_paths++] = ".";

    // Process command-line options.

    for (int opt; (opt = getopt(argc, argv, "I:M:Vhs")) != -1; )
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

            case 'V':
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
                break;

            case 's':
                schema_opt = true;
                break;

            default:
                err("invalid option: %c; try -h for help", opt);
                break;
        }
    }

    // We expect at least one argument (or -c option)

    if (optind == argc && !schema_opt)
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

    if (schema_opt)
    {
        // Generate entire CIM schema:

        for (const MOF_Class_Decl* p = MOF_Class_Decl::list;
            p;
            p = (const MOF_Class_Decl*)(p->next))
        {
            gen_class(p->name);
        }

        exit(0);
    }

    for (size_t i = 0; i < classes.size(); i++)
        gen_class(classes[i].c_str());

    return 0;
}
