#include <cimple/version.h>
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
#include "source_infix1.h"
#include "source_infix2.h"
#include "source_prefix.h"
#include "indication_header_prefix.h"
#include "indication_header_suffix.h"
#include "indication_source_prefix.h"
#include "indication_source_infix1.h"
#include "indication_source_infix2.h"
#include "module_source.h"
#include "association_header.h"
#include "association_source.h"
#include "association_source_infix1.h"
#include "association_source_infix2.h"

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
	fprintf(os, "%sCIMPLE_HIDE Invoke_Method_Status %s(\n", indent_chars,
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
	    fprintf(os, "%s* %s", p->ref_name, p->name);
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

void write_proc(
    FILE* os,
    const char* class_name, 
    const MOF_Class_Decl* class_decl)
{
    // Determine whether class has any methods.

    bool has_methods = false;

    MOF_Feature_Info* p = class_decl->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
	if (dynamic_cast<MOF_Method_Decl*>(p->feature))
	{
	    has_methods = true;
	    break;
	}
    }

    // Write proc:

    if (!has_methods)
    {
	if (class_decl->qual_mask & MOF_QT_INDICATION)
	    write_file(os, class_name, indication_source_infix1);
	else if (class_decl->qual_mask & MOF_QT_ASSOCIATION)
	    write_file(os, class_name, association_source_infix1);
	else
	    write_file(os, class_name, source_infix1);

	fprintf(os, "}\n");
	return;
    }

    if (class_decl->qual_mask & MOF_QT_INDICATION)
	write_file(os, class_name, indication_source_infix2);
    else if (class_decl->qual_mask & MOF_QT_ASSOCIATION)
	write_file(os, class_name, association_source_infix2);
    else
	write_file(os, class_name, source_infix2);

    p = class_decl->all_features;

    for (; p; p = (MOF_Feature_Info*)p->next)
    {
	MOF_Method_Decl* meth = dynamic_cast<MOF_Method_Decl*>(p->feature);

	if (!meth)
	    continue;

	write_skeleton(os, class_name, meth);
    }

    fprintf(os, "    return -1;\n");
    fprintf(os, "}\n");
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
    write_proc(os, class_name, class_decl);
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
    write_proc(os, class_name, class_decl);
    write_file(os, class_name, source_suffix);
    printf("Created %s\n", path.c_str());

    fclose(os);
}

void generate_module_file(const char* class_name, bool force)
{
    const char MODULE_CPP[] = "module.cpp";

    if (!force)
    {
	if (access(MODULE_CPP, F_OK) == 0)
	    err("%s already exists; use -f to overwrite", MODULE_CPP);
    }

    FILE* os = fopen(MODULE_CPP, "wb");
    write_file(os, class_name, module_source);
    fclose(os);

    printf("Created %s\n", MODULE_CPP);
}

void generate_provider(
    const char* class_name,
    bool module,
    bool force)
{
    // Lookup class.

    const MOF_Class_Decl* class_decl = MOF_Class_Decl::find((char*)class_name);

    if (!class_decl)
	err("no such class in MOF repository: %s", class_name);

    // Check to see if files already exists.

    string header_file = string(class_name) + "_Provider.h";
    string source_file = string(class_name) + "_Provider.cpp";

    if (!force)
    {
	if (access(header_file.c_str(), F_OK) == 0)
	    err("%s already exists; use -f to overwrite", header_file.c_str());

	if (access(source_file.c_str(), F_OK) == 0)
	    err("%s already exists; use -f to overwrite", source_file.c_str());
    }

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

    // Generate the module file:

    if (module)
	generate_module_file(class_decl->name, force);
}

bool is_dir(const string& path)
{
    struct stat st;

    if (stat(path.c_str(), &st) != 0)
        return false;

    return S_ISDIR(st.st_mode);
}

CIMPLE_INJECT_VERSION_TAG;

int main(int argc, char** argv)
{
    vector<string> mof_files;
    set_arg0(argv[0]);

    bool module = false;
    bool force = false;

    // Check options:
    int opt;

    while ((opt = getopt(argc, argv, "I:M:fmhv")) != -1)
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
		force = true;
		break;

            case 'm':
		module = true;
		break;

	    case 'h':
	    {
		fprintf(stderr, (char*)USAGE, argv[0]);
		exit(0);
	    }

	    case 'v':
	    {
		fprintf(stderr, "genprov: version 0.76\n\n");
		exit(0);
	    }

	    default:
		err("unknown option: %c", opt);
		break;
	}
    }

    // Check usage.

    if (argc - optind != 1)
    {
	fprintf(stderr, (char*)USAGE, argv[0]);
	exit(1);
    }

    const char* class_name = argv[optind];

    // Load repository. 

    load_repository(mof_files);

    // Generate provider.

    generate_provider(class_name, module, force);

    return 0;
}
