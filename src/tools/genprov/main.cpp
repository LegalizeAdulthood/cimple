#include <cimple/config.h>
#include <cassert>
#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <cstdarg>
#include <sys/types.h>
#include <util/util.h>
#include <sys/stat.h>
#include <unistd.h>
#include <tools/gencommon/gencommon.h>
#include "MOF_Parser.h"
#include "usage.h"
#include <vector>
#include <string>

using namespace std;

#include "header_suffix.h"
#include "header_prefix.h"
#include "source_suffix.h"
#include "source_prefix.h"
#include "indication_header_prefix.h"
#include "indication_header_suffix.h"
#include "indication_source_prefix.h"
#include "association_header.h"
#include "association_source.h"

bool force_opt = false;

// ATTN: handle break in method name between class name and method name.

const char END[] = "/*@END@*/";

static inline const char* _to_string(int data_type)
{
    if (data_type == TOK_STRING)
        return "String";
    else if (data_type == TOK_DATETIME)
        return "Datetime";

    return MOF_Data_Type::to_string(data_type);
}

void write_file(
    FILE* os,
    const char* class_name, 
    const unsigned char* template_file)
{
    string tmp = (char*)template_file; 
    size_t pos;

    while ((pos = tmp.find("<CLASS>")) != size_t(-1))
        tmp = tmp.substr(0, pos) + string(class_name) + tmp.substr(pos + 7);

    size_t n = tmp.size();
    size_t r = 0;

    while ((n = fwrite(&tmp[r], 1, tmp.size() - r, os)) > 0)
        r += n;
}

void write_method(
    FILE* os,
    const char* class_name, 
    const MOF_Method_Decl* meth,
    bool do_definition)
{
    // Set up indentation level:

    char indent_chars[64];
    memset(indent_chars, ' ', sizeof(indent_chars));

    if (do_definition)
        indent_chars[0] = '\0';
    else
        indent_chars[4] = '\0';

    // Print method declaration/definition:

    if (do_definition)
    {
        fprintf(os, "%sInvoke_Method_Status %s_Provider::%s(\n", indent_chars,
            class_name, meth->name);
    }
    else
    {
        fprintf(os, "%sInvoke_Method_Status %s(\n", indent_chars,
            meth->name);
    }

    // This:

    if (!(meth->qual_mask & MOF_QT_STATIC))
        fprintf(os, "%s    const %s* self,\n", indent_chars, class_name);

    // Parameters:

    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
        fprintf(os, "%s    ", indent_chars);

        if (!(p->qual_mask & MOF_QT_OUT))
            fprintf(os, "const ");

        if (p->data_type == TOK_REF)
        {
            if (p->array_index)
            {
                fprintf(os, "Array<%s*>& %s", p->ref_name, p->name);
            }
            else
            {
                if (p->qual_mask & MOF_QT_OUT)
                    fprintf(os, "%s*& %s", p->ref_name, p->name);
                else
                    fprintf(os, "%s* %s", p->ref_name, p->name);
            }
        }
        else
        {
            fprintf(os, "Property<");

            if (p->array_index)
            {
                fprintf(os, "Array_");
            }

            fprintf(os, "%s>& %s", _to_string(p->data_type), p->name);
        }

        fprintf(os, ",\n");
    }

    // Return value:

    fprintf(os, "%s    Property<%s>& return_value)",
        indent_chars, _to_string(meth->data_type));

    if (do_definition)
    {
        fprintf(os, "\n");
        fprintf(os, "{\n");
        fprintf(os, "    return INVOKE_METHOD_UNSUPPORTED;\n");
        fprintf(os, "}\n");
    }
    else
        fprintf(os, ";\n");

    fprintf(os, "\n");
}

void write_methods(
    FILE* os,
    const char* class_name, 
    const MOF_Class_Decl* class_decl,
    bool do_definition)
{
    MOF_Feature_Info* p = class_decl->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* feature = p->feature;

        MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(feature);

        if (meth)
            write_method(os, class_name, meth, do_definition);
    }

    if (do_definition)
        fprintf(os, "%s\n", END);
    else
        fprintf(os, "    %s\n", END);
}

void write_provider_header(
    const char* class_name, 
    const string& path,
    const MOF_Class_Decl* class_decl)
{
    FILE* os = fopen(path.c_str(), "wb");

    if (!os)
        err("cannot open %s\n", path.c_str());

    write_file(os, class_name, header_prefix);

    if (class_decl->qual_mask & MOF_QT_ASSOCIATION)
        write_file(os, class_name, association_header);

    write_methods(os, class_name, class_decl, false);
    write_file(os, class_name, header_suffix);
    printf("Created %s\n", path.c_str());

    fclose(os);
}

void write_indication_provider_header(
    const char* class_name, 
    const string& path,
    const MOF_Class_Decl* class_decl)
{
    FILE* os = fopen(path.c_str(), "wb");

    if (!os)
        err("cannot open %s\n", path.c_str());

    write_file(os, class_name, indication_header_prefix);
    write_methods(os, class_name, class_decl, false);
    write_file(os, class_name, indication_header_suffix);
    printf("Created %s\n", path.c_str());

    fclose(os);
}

void write_skeleton(
    FILE* os,
    const char* class_name, 
    const MOF_Method_Decl* meth)
{
    fprintf(os, "    if (strcasecmp(meth_name, \"%s\") == 0)\n", 
        meth->name);
    fprintf(os, "    {\n");

    fprintf(os, "        typedef %s_%s_method Method;\n", 
        class_name, meth->name);

    fprintf(os, "        Method* method = (Method*)arg2;\n");

    fprintf(os, "        return provider->%s(\n", meth->name);

    if (!(meth->qual_mask & MOF_QT_STATIC))
        fprintf(os, "            self,\n");

    for (MOF_Parameter* p = meth->parameters; p; p = (MOF_Parameter*)p->next)
    {
        fprintf(os, "            method->%s", p->name);
        fprintf(os, ",\n");
    }

    fprintf(os, "            method->return_value);\n");

    fprintf(os, "    }\n");
}

void write_provider_source(
    const char* class_name, 
    const string& path,
    const MOF_Class_Decl* class_decl)
{
    FILE* os = fopen(path.c_str(), "wb");

    if (!os)
        err("cannot open %s\n", path.c_str());

    write_file(os, class_name, source_prefix);

    if (class_decl->qual_mask & MOF_QT_ASSOCIATION)
        write_file(os, class_name, association_source);

    write_methods(os, class_name, class_decl, true);
    write_file(os, class_name, source_suffix);
    printf("Created %s\n", path.c_str());

    fclose(os);
}

void write_indication_provider_source(
    const char* class_name, 
    const string& path,
    const MOF_Class_Decl* class_decl)
{
    FILE* os = fopen(path.c_str(), "wb");

    if (!os)
        err("cannot open %s\n", path.c_str());

    write_file(os, class_name, indication_source_prefix);
    write_methods(os, class_name, class_decl, true);
    write_file(os, class_name, source_suffix);
    printf("Created %s\n", path.c_str());

    fclose(os);
}

void generate_provider(const char* class_name)
{
    // Lookup class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
        err("no such class in MOF repository: %s", class_name);

    // Check to see if files already exists.

    string header_file = string(class_name) + "_Provider.h";
    string source_file = string(class_name) + "_Provider.cpp";

    // Write header and source files:

    if (class_decl->qual_mask & MOF_QT_INDICATION)
    {
        write_indication_provider_header(class_name, header_file, class_decl);
        write_indication_provider_source(class_name, source_file, class_decl);
    }
    else
    {
        write_provider_header(class_name, header_file, class_decl);
        write_provider_source(class_name, source_file, class_decl);
    }
}

int load_file(const char* path, string& data)
{
    FILE* is = fopen(path, "rb");

    if (!is)
        return -1;

    char buffer[4097];
    size_t n;

    while ((n = fread(buffer, 1, sizeof(buffer) - 1, is)) > 0)
    {
        buffer[n] = '\0';
        data += buffer;
    }

    fclose(is);
    return 0;
}

int put_file(const char* path, const string& data)
{
    FILE* os = fopen(path, "wb");

    if (!os)
        return -1;

    size_t n;

    for (size_t i = 0; i < data.size(); i++)
        fputc(data[i], os);

    fclose(os);

    printf("Patched %s\n", path);
    return 0;
}

//==============================================================================
//
// Patches
//
//==============================================================================

struct Patch
{
    const char* returns;
    const char* scope;
    const char* func;
    const char* text;
};

const Patch modify_instance_hdr_patch =
{
    "Modify_Instance_Status",
    NULL,
    "modify_instance",
    "Modify_Instance_Status modify_instance(\n"
    "        const <CLASS>* model,\n"
    "        const <CLASS>* instance)"
};

const Patch modify_instance_src_patch =
{
    "Modify_Instance_Status",
    "<CLASS>_Provider",
    "modify_instance",
    "Modify_Instance_Status <CLASS>_Provider::modify_instance(\n"
    "    const <CLASS>* model,\n"
    "    const <CLASS>* instance)"
};

const Patch create_instance_hdr_patch =
{
    "Create_Instance_Status",
    NULL,
    "create_instance",
    "Create_Instance_Status create_instance(\n"
    "        <CLASS>* instance)"
};

const Patch create_instance_src_patch =
{
    "Create_Instance_Status",
    "<CLASS>_Provider",
    "create_instance",
    "Create_Instance_Status <CLASS>_Provider::create_instance(\n"
    "    <CLASS>* instance)"
};

//==============================================================================

void expand(string& text, const string& pattern, const string& replacement)
{
    size_t pos;

    while ((pos = text.find(pattern)) != string::npos)
    {
        text = 
            text.substr(0, pos) + 
            string(replacement) + 
            text.substr(pos + pattern.size());
    }
}

int patch(string& data, const char* cn, const Patch& patch)
{
    string rt = patch.returns;
    string fn = patch.func;
    expand(fn, "<CLASS>", cn);

    const string tmp = data;
    const char* str = tmp.c_str();
    const char* p = str;

    for (;;)
    {
        // return type

        p = strstr(p, rt.c_str());

        if (!p)
            return -1;

        const char* start = p;

        p += rt.size();

        // whitespace

        while (isspace(*p))
            p++;

        if (*p == '\0')
            return -1;

        // scope

        if (patch.scope)
        {
            string sn = patch.scope;
            expand(sn, "<CLASS>", cn);

            // scope

            if (strncmp(p, sn.c_str(), sn.size()) != 0)
                continue;


            p += sn.size();

            // whitespace

            while (isspace(*p))
                p++;

            if (*p == '\0')
                return -1;

            // expect "::"

            if (!(p[0] == ':' && p[1] == ':'))
                continue;

            p += 2;

            // whitespace

            while (isspace(*p))
                p++;

            if (*p == '\0')
                return -1;
        }

        // function name

        if (strncmp(p, fn.c_str(), fn.size()) != 0)
            continue;

        p += fn.size();

        // whitespace

        while (isspace(*p))
            p++;

        if (*p == '\0')
            return -1;

        // '('

        if (*p != '(')
            continue;

        p++;

        // ')'

        while (*p && *p != ')')
            p++;

        if (*p == '\0')
            return -1;

        p++;

        // Perform patch.

        string text = patch.text;
        size_t pos;
        expand(text, "<CLASS>", cn);

        data.erase(start - str, p - start);
        data.insert(start - str, text);

        return 0;
    }

    // Unreachable
    return -1;
}

void patch_err(
    const char* path, string& data, const char* cn, const Patch& pt)
{
    if (patch(data, cn, pt) != 0)
        err("%s: patch failed: failed to find %s()", path, pt.func);
}

void patch_method(
    const char* path, 
    const MOF_Class_Decl* cd, 
    const MOF_Method_Decl* md, 
    string& data,
    bool def)
{
    const char* cn = cd->name;
    const char* mn = md->name;
    const char* in = def ? "" : "    ";
    string rt;
    string sn;
    string fn;
    string text;

    // returns

    rt = "Invoke_Method_Status";

    // scope

    if (def)
        sn = string(cn) + string("_Provider");

    // function

    fn = mn;

    // header

    char buf[1024];

    if (def)
    {
        sprintf(buf, "Invoke_Method_Status %s_Provider::%s(\n", cn, mn);
        text += buf;
    }
    else
    {
        sprintf(buf, "Invoke_Method_Status %s(\n", mn);
        text += buf;
    }

    // This:

    if (!(md->qual_mask & MOF_QT_STATIC))
    {
        sprintf(buf, "%s    const %s* self,\n", in, cn);
        text += buf;
    }

    // Parameters:

    for (MOF_Parameter* p = md->parameters; p; p = (MOF_Parameter*)p->next)
    {
        sprintf(buf, "%s    ", in);
        text += buf;

        if (!(p->qual_mask & MOF_QT_OUT))
        {
            sprintf(buf, "const ");
            text += buf;
        }

        if (p->data_type == TOK_REF)
        {
            if (p->array_index)
            {
                sprintf(buf, "Array<%s*>& %s", p->ref_name, p->name);
                text += buf;
            }
            else
            {
                if (p->qual_mask & MOF_QT_OUT)
                {
                    sprintf(buf, "%s*& %s", p->ref_name, p->name);
                    text += buf;
                }
                else
                {
                    sprintf(buf, "%s* %s", p->ref_name, p->name);
                    text += buf;
                }
            }
        }
        else
        {
            sprintf(buf, "Property<");
            text += buf;

            if (p->array_index)
            {
                sprintf(buf, "Array_");
                text += buf;
            }

            sprintf(buf, "%s>& %s", _to_string(p->data_type), p->name);
            text += buf;
        }

        sprintf(buf, ",\n");
        text += buf;
    }

    // Return value:

    sprintf(buf, "%s    Property<%s>& return_value)",
        in, _to_string(md->data_type));
    text += buf;

    // Patch it:

    {
        Patch pt;
        pt.returns = rt.c_str();

        if (sn.size())
            pt.scope = sn.c_str();
        else
            pt.scope = NULL;

        pt.func = mn;
        pt.text = text.c_str();

        if (patch(data, cn, pt) == 0)
            return;
    }

    // Search for "/*@END@*/" marker.

    size_t pos = data.find(END);

    if (pos == string::npos)
    {
        err("%s: patch failed: please add end-marker (\"%s\") "
            "so genprov will know where to insert new extrinsic methods", 
            path, END);
    }

    if (def)
    {
        text +=
            "\n"
            "{\n"
            "    return INVOKE_METHOD_UNSUPPORTED;\n"
            "}\n";
    }
    else
    {
        text += ";\n";
    }

    text += "\n" + string(in) + string(END);

    data = data.substr(0, pos) + text + data.substr(pos + strlen(END));
}

void patch_methods(
    const char* path, const MOF_Class_Decl* cd, string& data, bool def)
{
    MOF_Feature_Info* p = cd->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
        MOF_Feature* feature = p->feature;

        MOF_Method_Decl* md = dynamic_cast<MOF_Method_Decl*>(feature);

        if (md)
            patch_method(path, cd, md, data, def);
    }
}

void patch_header(const MOF_Class_Decl* cd)
{
    // Load file into memory.

    char path[1024];
    sprintf(path, "%s_Provider.h", cd->name);
    string data;

    if (load_file(path, data) != 0)
        err("failed to patch %s (no such file)", path);

    // Patch provider.

    if (cd->qual_mask & MOF_QT_INDICATION)
    {
    }
    else if (cd->qual_mask & MOF_QT_ASSOCIATION)
    {
        patch_err(path, data, cd->name, modify_instance_hdr_patch);
        patch_err(path, data, cd->name, create_instance_hdr_patch);
    }
    else
    {
        patch_err(path, data, cd->name, modify_instance_hdr_patch);
        patch_err(path, data, cd->name, create_instance_hdr_patch);
    }

    patch_methods(path, cd, data, false);
    put_file(path, data);
}

void patch_source(const MOF_Class_Decl* cd)
{
    // Load file into memory.

    char path[1024];
    sprintf(path, "%s_Provider.cpp", cd->name);
    string data;

    if (load_file(path, data) != 0)
        err("failed to patch %s (no such file)", path);

    // Patch provider.

    if (cd->qual_mask & MOF_QT_INDICATION)
    {
    }
    else if (cd->qual_mask & MOF_QT_ASSOCIATION)
    {
        patch_err(path, data, cd->name, modify_instance_src_patch);
        patch_err(path, data, cd->name, create_instance_src_patch);
    }
    else
    {
        patch_err(path, data, cd->name, modify_instance_src_patch);
        patch_err(path, data, cd->name, create_instance_src_patch);
    }

    patch_methods(path, cd, data, true);
    put_file(path, data);
}

void patch_provider(const char* class_name)
{
    // Find class:

    const MOF_Class_Decl* cd = MOF_Class_Decl::find((char*)class_name);

    if (!cd)
        err("no such class: %s", class_name);

    patch_header(cd);
    patch_source(cd);
}

void genprov(const string& cn)
{
    // Locate provider files.

    bool found = exists(cn + "_Provider.h") && exists(cn + "_Provider.cpp");

    // Patch provider.

    if (found && !force_opt)
        patch_provider(cn.c_str());
    else
    {
        generate_provider(cn.c_str());
    }
}

int main(int argc, char** argv)
{
    const char* arg0 = argv[0];
    vector<string> mof_files;
    set_arg0(argv[0]);

    // Check options:
    int opt;

    while ((opt = getopt(argc, argv, "I:M:fhV")) != -1)
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

                mof_files.push_back(optarg);
                break;
            } 

            case 'f':
                force_opt = true;
                break;

            case 'h':
            {
                fprintf(stderr, (char*)USAGE, argv[0]);
                exit(0);
            }

            case 'V':
            {
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
            }

            default:
                err("unknown option: %c", opt);
                break;
        }
    }

    // Check usage.

    argc -= optind;
    argv += optind;

    if (argc < 1)
    {
        fprintf(stderr, (char*)USAGE, arg0);
        exit(1);
    }

    // Load repository. 

    load_repository(mof_files);

    // Create providers.

    for (int i = 0; i < argc; i++)
        genprov(argv[i]);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genprov/main.cpp,v 1.45 2007/05/01 23:07:20 mbrasher-public Exp $");
