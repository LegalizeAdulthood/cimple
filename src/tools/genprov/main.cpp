#include <cimple/config.h>
#include <cimple/Buffer.h>
#include <cassert>
#include <getopt.h>
#include <cctype>
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
static string class_list_file;



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

void format_method_signature(
    cimple::Buffer& out,
    const MOF_Class_Decl* cd, 
    const MOF_Method_Decl* md, 
    bool def)
{
    const char* cn = cd->name;
    const char* mn = md->name;
    const char* in = def ? "" : "    ";

    // header

    if (def)
        out.format("Invoke_Method_Status %s_Provider::%s(\n", cn, mn);
    else
        out.format("Invoke_Method_Status %s(\n", mn);

    // This:

    if (!(md->qual_mask & MOF_QT_STATIC))
        out.format("%s    const %s* self,\n", in, cn);

    // Parameters:

    for (MOF_Parameter* p = md->parameters; p; p = (MOF_Parameter*)p->next)
    {
        out.format("%s    ", in);

        if (!(p->qual_mask & MOF_QT_OUT))
            out.format("const ");

        const char* cn = 0;

        if (p->data_type == TOK_REF)
            cn = p->ref_name;
        else if (p->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            cn = "Instance";
        else 
            cn = get_embedded_class_name(p);

        if (cn)
        {
            if (p->array_index)
                out.format("Property< Array<%s*> >& %s", cn, p->name);
            else
            {
                if (p->qual_mask & MOF_QT_OUT)
                    out.format("%s*& %s", cn, p->name);
                else
                    out.format("%s* %s", cn, p->name);
            }
        }
        else
        {
            const char* dt = _to_string(p->data_type);

            if (p->array_index)
                out.format("Property<Array_%s>& %s", dt, p->name);
            else
                out.format("Property<%s>& %s", dt, p->name);
        }

        out.format(",\n");
    }

    // Return value:

    {
        const char* cn = 0;
        
        if (md->qual_mask & MOF_QT_EMBEDDEDOBJECT)
            cn = "Instance";
        else
            cn = get_embedded_class_name(md);

        if (cn)
            out.format("%s    %s*& return_value)", in, cn);
        else
        {
            const char* dt = _to_string(md->data_type);
            out.format("%s    Property<%s>& return_value)", in, dt);
        }
    }
}

void write_method(
    FILE* os,
    const MOF_Class_Decl* cd,
    const MOF_Method_Decl* md,
    bool def)
{
    if (!def)
        fprintf(os, "    ");

    // Format method signature.

    cimple::Buffer out;
    format_method_signature(out, cd, md, def);
    fprintf(os, "%s", out.data());

    // Write method body.

    if (def)
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
            write_method(os, class_decl, meth, do_definition);
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

    fprintf(os, "// Generated by genprov %s\n", CIMPLE_VERSION_STRING);

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

    fprintf(os, "// Generated by genprov %s\n", CIMPLE_VERSION_STRING);

    write_file(os, class_name, indication_header_prefix);
    write_methods(os, class_name, class_decl, false);
    write_file(os, class_name, indication_header_suffix);
    printf("Created %s\n", path.c_str());

    fclose(os);
}

void write_provider_source(
    const char* class_name, 
    const string& path,
    const MOF_Class_Decl* class_decl)
{
    FILE* os = fopen(path.c_str(), "wb");

    if (!os)
        err("cannot open %s\n", path.c_str());

    fprintf(os, "// Generated by genprov %s\n", CIMPLE_VERSION_STRING);

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

    fprintf(os, "// Generated by genprov %s\n", CIMPLE_VERSION_STRING);

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
    const char* body;
};

const Patch modify_instance_hdr_patch =
{
    "Modify_Instance_Status",
    NULL,
    "modify_instance",
    "Modify_Instance_Status modify_instance(\n"
    "        const <CLASS>* model,\n"
    "        const <CLASS>* instance)",
    0,
};

const Patch modify_instance_src_patch =
{
    "Modify_Instance_Status",
    "<CLASS>_Provider",
    "modify_instance",
    "Modify_Instance_Status <CLASS>_Provider::modify_instance(\n"
    "    const <CLASS>* model,\n"
    "    const <CLASS>* instance)",
    "{\n"
    "    return MODIFY_INSTANCE_UNSUPPORTED;\n"
    "}"
};

const Patch create_instance_hdr_patch =
{
    "Create_Instance_Status",
    NULL,
    "create_instance",
    "Create_Instance_Status create_instance(\n"
    "        <CLASS>* instance)",
    NULL
};

const Patch create_instance_src_patch =
{
    "Create_Instance_Status",
    "<CLASS>_Provider",
    "create_instance",
    "Create_Instance_Status <CLASS>_Provider::create_instance(\n"
    "    <CLASS>* instance)",
    "{\n"
    "    return CREATE_INSTANCE_UNSUPPORTED;\n"
    "}"
};

const Patch enum_associators_hdr_patch =
{
    "Enum_Associators_Status",
    NULL,
    "enum_associators",
    "Enum_Associators_Status enum_associators(\n"
    "        const Instance* instance,\n"
    "        const String& result_class,\n"
    "        const String& role,\n"
    "        const String& result_role,\n"
    "        Enum_Associators_Handler<Instance>* handler)",
    NULL
};

const Patch enum_associators_src_patch =
{
    "Enum_Associators_Status",
    "<CLASS>_Provider",
    "enum_associators",
    "Enum_Associators_Status <CLASS>_Provider::enum_associators(\n"
    "    const Instance* instance,\n"
    "    const String& result_class,\n"
    "    const String& role,\n"
    "    const String& result_role,\n"
    "    Enum_Associators_Handler<Instance>* handler)",
    "{\n"
    "    return ENUM_ASSOCIATORS_UNSUPPORTED;\n"
    "}"
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

int patch(string& data, const char* cn, const Patch& patch, bool def)
{
    string rt = patch.returns;
    string fn = patch.func;
    expand(fn, "<CLASS>", cn);

    const string tmp = data;
    const char* str = tmp.c_str();
    const char* p = str;

    for (;;)
    {
        // Find insertion point for this patch.

        const char* start = p;

        if ((start = strstr(p, rt.c_str())))
        {
            p = start;
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
        else if ((start = strstr(p, END)))
        {
            p = start;
            string text = patch.text;
            expand(text, "<CLASS>", cn);

            if (patch.body)
            {
                text += '\n';
                text += patch.body;
                text += "\n\n";
            }
            else
                text += ";\n\n    ";

            data.insert(p - str, text);
            return 0;
        }
        else
            return -1;
    }

    // Unreachable
    return -1;
}

void patch_err(
    const char* path, 
    string& data, 
    const char* cn, 
    const Patch& pt, 
    bool def)
{
    if (patch(data, cn, pt, def) != 0)
    {
        err("%s: patch failed: please add end-marker (\"%s\") "
            "so genprov will know where to insert new extrinsic methods", 
            path, END);
    }
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

    // returns

    rt = "Invoke_Method_Status";

    // scope

    if (def)
        sn = string(cn) + string("_Provider");

    // function

    fn = mn;

    // Format the method.

    cimple::Buffer out;
    format_method_signature(out, cd, md, def);

    // Patch it:
    {
        Patch pt;
        pt.returns = rt.c_str();

        if (sn.size())
            pt.scope = sn.c_str();
        else
            pt.scope = NULL;

        pt.func = mn;
        pt.text = out.data();

        if (def)
        {
            pt.body = 
                "\n"
                "{\n"
                "    return INVOKE_METHOD_UNSUPPORTED;\n"
                "}";
        }
        else
            pt.body = NULL;

        patch_err(path, data, cn, pt, def);
    }
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
        patch_err(path, data, cd->name, modify_instance_hdr_patch, false);
        patch_err(path, data, cd->name, create_instance_hdr_patch, false);
        patch_err(path, data, cd->name, enum_associators_hdr_patch, false);
    }
    else
    {
        patch_err(path, data, cd->name, modify_instance_hdr_patch, false);
        patch_err(path, data, cd->name, create_instance_hdr_patch, false);
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
        patch_err(path, data, cd->name, modify_instance_src_patch, true);
        patch_err(path, data, cd->name, create_instance_src_patch, true);
        patch_err(path, data, cd->name, enum_associators_src_patch, false);
    }
    else
    {
        patch_err(path, data, cd->name, modify_instance_src_patch, true);
        patch_err(path, data, cd->name, create_instance_src_patch, true);
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

    while ((opt = getopt(argc, argv, "I:M:F:fhV")) != -1)
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

			case 'F':
			 {
                if (!optarg)
                {
                    err("missing argument on -F option");
                    exit(1);
                }

                class_list_file = optarg;
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
    //argc -= optind;
    //argv += optind;

    //if no arguments and no classlist file, error
    // Expect at least one argument or a class_list_file

    if (optind == argc && class_list_file.size() == 0)
    {
        fprintf(stderr,"Error: No arguments and no classlist file.\n");
        fprintf(stderr,"%s",(char*)USAGE, arg0);
        exit(1);
    }
	
    //  Build class list from file and command line input
 
	vector<string> classes;

    // append classes to class list file if -F option

    if (class_list_file.size() != 0)
        load_class_list_file(classes, class_list_file);

    // get classes from command line and append to class list:

    for (int i = optind; i < argc; i++)
        append_unique(classes, argv[i]);

    // Load repository

    load_repository(mof_files);

    // Create providers.
	
	for (int j = 0; j < classes.size(); j++)
        genprov(classes[j]);

    return 0;
}

