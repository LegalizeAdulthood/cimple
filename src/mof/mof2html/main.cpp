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

#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <getopt.h>
#include "MOF_Parser.h"

using namespace std;

//------------------------------------------------------------------------------
//
// _process_command_line_options()
//
//      Process argc/argv for command line options. Reorder argv[], placing 
//      the options before the non-options. Returns the index of the first 
//      non-option.
//
//------------------------------------------------------------------------------

static int _process_command_line_options(int& argc, char**& argv)
{
    // Add the current directory to the MOF search path.

    MOF_include_paths[MOF_num_include_paths++] = ".";

    // Gather all the options:

    int opt;

    while ((opt = getopt(argc, argv, "I:dw")) != -1)
    {
        switch (opt)
        {
            case 'I':
            {
                if (!optarg)
                {
                    fprintf(stderr, "missing argument on -I option\n");
                    exit(1);
                }

                if (MOF_num_include_paths == MAX_INCLUDES)
                {
                    fprintf(stderr, "too many -I options\n");
                    exit(1);
                }

                MOF_include_paths[MOF_num_include_paths++] = optarg;
                break;
            }
            case 'd':
            {
                MOF_Options::debug = true;
                break;
            }
            case 'w':
            {
                MOF_Options::warn = true;
                break;
            }
            case '?':
            {
                // Option argument missing!
                return -1;
            }
            default:
            {
                fprintf(stderr, "unknown option: -%c\n", opt);
                break;
            }
        }
    }

    return optind;
}

//------------------------------------------------------------------------------
//
// _print_include_paths()
//
//------------------------------------------------------------------------------

static void _print_include_paths()
{
    for (size_t i = 0; i < MOF_num_include_paths; i++)
        printf("MOF_include_paths[%d]=\"%s\"\n", (int)i, MOF_include_paths[i]);
}

//------------------------------------------------------------------------------
//
// main()
//
//------------------------------------------------------------------------------

#define USAGE "\
\n\
Usage: %s [-Idw] mof-files\n\
\n\
Where:\n\
        -I path -- include path\n\
        -d -- enabled debug printing\n\
        -w -- enable warnings\n\
\n"

static const char* _meta_type_name(const MOF_Class_Decl* cd)
{
    if (cd->qual_mask & MOF_QT_ASSOCIATION)
        return "association";
    else if (cd->qual_mask & MOF_QT_INDICATION)
        return "indication";
    else
        return "class";
}

static void put_string(FILE* os, const char* str)
{
    for (const char* p = str; *p; p++)
    {
        switch (*p)
        {
            case '&':
                fprintf(os, "&amp;");
                break;
            case '<':
                fprintf(os, "&lt;");
                break;
            case '>':
                fprintf(os, "&gt;");
                break;
            case '"':
                fprintf(os, "&quot;");
                break;
            case '\'':
                fprintf(os, "&#39;");
                break;
            default:
                fprintf(os, "%c", *p);
        }
    }
}

static void put_quoted_string(FILE* os, const char* str)
{
    fprintf(os, "&quot;");
    put_string(os, str);
    fprintf(os, "&quot;");
}

static void print_description(FILE* os, const MOF_Qualifier* q)
{
    for (; q; q = (MOF_Qualifier*)q->next)
    {
        if (strcasecmp(q->name, "description") == 0)
        {
            const MOF_Literal* lit = q->params;
            assert(lit->next == 0);
            assert(lit->value_type == TOK_STRING_VALUE);

            put_string(os, lit->string_value);
            printf("\n");
        }
    }
}

static const char* lookup_value_map_element(
    const MOF_Qualifier_Info* info,
    size_t index)
{
    for (; info; info = (MOF_Qualifier_Info*)info->next)
    {
        const MOF_Qualifier* q = info->qualifier;

        if (strcasecmp(q->name, "ValueMap") != 0)
            continue;

        size_t i = 0;

        for (const MOF_Literal* p = q->params; p; p = (MOF_Literal*)p->next)
        {
            if (i == index && p->value_type == TOK_STRING_VALUE)
            {
                return p->string_value;
            }

            i++;
        }
    }

    // Not found!
    return 0;
}

static void print_qualifiers(FILE* os, const MOF_Qualifier_Info* info)
{
    fprintf(os, "<table border=0 width=100%%>\n");

    const MOF_Qualifier_Info* r = info;

    for (; r; r = (MOF_Qualifier_Info*)r->next)
    {
        const MOF_Qualifier* q = r->qualifier;
        fprintf(os, "<tr valign=top>\n");

        // Name:
        fprintf(os, "<td width=25%%>\n");
        fprintf(os, "%s\n", q->name);
        fprintf(os, "</td>\n");

        // Value:
        fprintf(os, "<td width=75%%>\n");

        const MOF_Literal* lit = q->params;

        size_t index = 0;

        for (const MOF_Literal* p = q->params; p; p = (MOF_Literal*)p->next)
        {
            if (p->value_type == TOK_STRING_VALUE)
            {
                if (strcasecmp(q->name, "Values") == 0)
                {
                    put_quoted_string(os, p->string_value);

                    const char* vme = lookup_value_map_element(info, index);

                    if (vme)
                    {
                        fprintf(os, " <b>[");
                        put_string(os, vme);
                        fprintf(os, "]</b>");
                    }
                }
                else
                    put_string(os, p->string_value);
            }
            else if (p->value_type == TOK_INT_VALUE)
            {
                fprintf(os, "%lld", p->int_value);
            }
            else if (p->value_type == TOK_BOOL_VALUE)
            {
                if (p->bool_value)
                    fprintf(os, "TRUE");
                else
                    fprintf(os, "FALSE");
            }

            if (p->next)
            {
                if (strcasecmp(q->name, "Values") == 0)
                    fprintf(os, "<br>");
                else
                    fprintf(os, ", ");
            }

            index++;
        }

        fprintf(os, "</td>\n");

        // Row end!
        fprintf(os, "</tr>\n");
    }

    fprintf(os, "</table>\n");
}

static void print_class_description(FILE* os, const MOF_Qualifier* q)
{
    fprintf(os, "<h2>Description:</h2>\n");

    fprintf(os, "  <table summary=layout border=0 width=\"80%%\">\n");
    fprintf(os, "  <tr>\n");
    fprintf(os, "  <td>\n");
    print_description(os, q);
    fprintf(os, "  </td>\n");
    fprintf(os, "  </tr>\n");
    fprintf(os, "  </table>\n");
}

void print_class_header(FILE* os, const MOF_Class_Decl* cd)
{
    // fprintf(os, "  <center>\n");

    if (cd->super_class)
    {
        fprintf(os, "<h2>%s %s : <a href=%s.html>%s</a></h2>\n", 
            _meta_type_name(cd), cd->name, cd->super_class->name, 
                cd->super_class->name);
    }
    else
    {
        fprintf(os, "          <h2>%s %s</h2>\n", 
            _meta_type_name(cd), cd->name);
    }

    // fprintf(os, "  </center>\n");

    fprintf(os, "  <hr>\n");
}

void print_typo_conventions(FILE* os)
{
    fprintf(os, "<h2>Typographical Conventions:</h2>\n");

    fprintf(os, "<ol>\n");
    fprintf(os, "<li>Inherited properties are <i>italicized</i>.\n");
    fprintf(os, "<li>Local properties are <b>bolded</b>.\n");
    fprintf(os, "<li>Key properties are highlighted in gold\n");
    fprintf(os, "</ol>\n");
}

void gen_class_html(const MOF_Class_Decl* p)
{
    char buffer[1024];
    sprintf(buffer, "%s.html", p->name);
    FILE* os = fopen(buffer, "wb");

    if (!os)
    {
        fprintf(stderr, "error: failed to open %s\n", buffer);
        exit(0);
    }

    fprintf(os, "<head>\n");
    fprintf(os, "  <title>%s</title>\n", p->name);
    fprintf(os, "</head>\n");
    fprintf(os, "<body bgcolor=lightgrey>\n");
    fprintf(os, "  <br>\n");
    print_class_header(os, p);
    fprintf(os, "  <br>\n");
    print_class_description(os, p->qualifiers);
    fprintf(os, "  <h2>Definition:</h2>\n");
    fprintf(os, "  <table summary=\"layout\" border=\"1\" width=\"80%%\"");
    fprintf(os, "    cellpadding=2>");
    fprintf(os, "    <thead>\n");
    fprintf(os, "      <tr>\n");

#if 0
    fprintf(os, "        <th colspan=7 align=center>\n");

    if (p->super_class)
    {
        fprintf(os, "          %s %s : <a href=%s.html>%s</a>\n", 
            _meta_type_name(p), p->name, p->super_class->name, 
                p->super_class->name);
    }
    else
        fprintf(os, "          %s %s\n", _meta_type_name(p), p->name);

    fprintf(os, "        </th>\n");
#endif

    fprintf(os, "      </tr>\n");
    fprintf(os, "      <tr align=left>\n");
    fprintf(os, "        <th>Feature</ht>\n");
    fprintf(os, "        <th>Type</ht>\n");
#if 0
    fprintf(os, "        <th>Property</ht>\n");
#endif
    fprintf(os, "        <th>Class Origin</ht>\n");
#if 0
    fprintf(os, "        <th>Description</ht>\n");
#endif
    fprintf(os, "        <th>Qualifiers</ht>\n");
    fprintf(os, "      </tr>\n");
    fprintf(os, "    </thead>\n");
    fprintf(os, "    <tbody>\n");

    for (
        const MOF_Feature_Info* f = (const MOF_Feature_Info*)p->all_features; 
        f; 
        f = (const MOF_Feature_Info*)f->next)
    {
        fprintf(os, "      <tr valign=top>\n");

        //
        // Name:
        //

        const char* bgcolor = "lightgrey";

        if (f->feature->qual_mask & MOF_QT_KEY)
            bgcolor = "gold";

        if (f->propagated)
        {
            fprintf(os, "        <td bgcolor=%s><i>%s</i></td>\n", 
                bgcolor, f->feature->name);
        }
        else
        {
            fprintf(os, "        <td bgcolor=%s><b>%s</b></td>\n", 
                bgcolor, f->feature->name);
        }

        //
        // Type:
        //

        if (f->feature->type == MOF_FEATURE_PROP)
        {
            const MOF_Property_Decl* pd = (MOF_Property_Decl*)f->feature;
            const char* dt = MOF_Data_Type::to_string(pd->data_type);

            if (pd->array_index == 0)
                fprintf(os, "        <td>%s</td>\n", dt);
            else if (pd->array_index > 0)
                fprintf(os, "        <td>%s[%d]</td>\n", dt, pd->array_index);
            else
                fprintf(os, "        <td>%s[]</td>\n", dt);
        }
        else if (f->feature->type == MOF_FEATURE_REF)
        {
            const MOF_Reference_Decl* rd = (MOF_Reference_Decl*)f->feature;

            fprintf(os, "        <td><a href=%s.html>%s</a></td>\n", 
                rd->class_name, rd->class_name);
        }
        else if (f->feature->type == MOF_FEATURE_METHOD)
        {
            fprintf(os, "        <td>method</td>\n");
        }

#if 0
        //
        // Property
        //

        fprintf(os, "        <td>Property</td>\n");
#endif

        //
        // Class origin
        //

        if (strcmp(f->class_origin->name, p->name) == 0)
            fprintf(os, "        <td>%s</td>\n", f->class_origin->name);
        else
        {
            fprintf(os, "        <td><a href=%s.html>%s</a></td>\n", 
                f->class_origin->name, f->class_origin->name);
        }

        // 
        // Description
        //

#if 0
        fprintf(os, "<td>\n");
        print_description(os, f->feature->qualifiers);
        fprintf(os, "</td>\n");
#endif

        // 
        // Qualifiers
        //

        fprintf(os, "<td>\n");
        print_qualifiers(os, f->feature->all_qualifiers);
        fprintf(os, "</td>\n");

        fprintf(os, "      </tr>\n");
    }

    fprintf(os, "    </tbody>\n");
    fprintf(os, "  </table>\n");
    print_typo_conventions(os);
    fprintf(os, "</body>\n");

    fclose(os);
}

struct Class_Decl
{
    const MOF_Class_Decl* class_decl;
    Class_Decl(const MOF_Class_Decl* cd) : class_decl(cd) { }

    friend int operator<(const Class_Decl& x, const Class_Decl& y)
    {
        return strcmp(x.class_decl->name, y.class_decl->name) < 0;
    }
};

void gen_classname_html_doc()
{
    vector<Class_Decl> classes;

    //
    // Open file:
    //

    const char FILENAME[] = "index.html";
    FILE* os = fopen(FILENAME, "wb");

    if (!os)
    {
        fprintf(stderr, "error: failed to open %s\n", FILENAME);
        exit(0);
    }

    //
    // Generate:
    //

    fprintf(os, "<head>\n");
    fprintf(os, "  <title>CIM Classes</title>\n");
    fprintf(os, "</head>\n");

    fprintf(os, "<body bgcolor=lightgrey>\n");
    fprintf(os, "  <center>\n");
    fprintf(os, "    <h2>CIM Classes</h2>\n");
    fprintf(os, "  </center>\n");
    fprintf(os, "  <hr>\n");
    fprintf(os, "  <br>\n");
    fprintf(os, "  <h2>Classes</h2>\n");

    for (MOF_Class_Decl* p = MOF_Class_Decl::list; 
        p; 
        p = (MOF_Class_Decl*)p->next)
    {
        gen_class_html(p);
        classes.push_back(p);
    }

    sort(classes.begin(), classes.end());

    for (size_t i = 0; i < classes.size(); i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;

        fprintf(os, "  <a href=\"%s.html\">%s (%s)</a>\n", 
            cd->name, cd->name, _meta_type_name(cd));
        fprintf(os, "  <br>\n");
    }

    fprintf(os, "</body>\n");
    fclose(os);
}

int main(int argc, char** argv)
{
    //
    // Process the command line options. Reorders argv[] so that all
    // of the options appear first (before any of the ordinary arguments).
    // Returns 
    //

    int first_non_option_index = _process_command_line_options(argc, argv);

    if (first_non_option_index == -1)
        exit(1);

    //
    // Print includes paths (if -d option given)
    //

    if (MOF_Options::debug)
        _print_include_paths();

    //
    // Check arguments (be sure there are non-option arguments remaining.
    //

    if (first_non_option_index  == argc)
    {
        fprintf(stderr, USAGE, argv[0]);
        exit(1);
    }

    //
    // Process each MOF file:
    //

    for (int i = first_non_option_index; i < argc; i++)
        MOF_parse_file(argv[i]);

    //
    // Print out all the declarations:
    //

    if (MOF_Options::debug)
    {
        MOF_Class_Decl::print_static_list();
        MOF_Instance_Decl::print_static_list();
        MOF_Qualifier_Decl::print_static_list();
    }

    // MOF_Class_Decl::print_nested_refs();

    //
    // Generate class name list:
    //

    gen_classname_html_doc();

    return 0;
}
