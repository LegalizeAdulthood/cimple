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
/*
    This executable generates html output from MOF input to provide a
    displayable form for viewing DMTF mof files.  It was written specifically
    to generate html output for complete DMTF CIM Schemas.
*/

#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <getopt.h>
#include <ctime>
#include "MOF_Parser.h"

using namespace std;

#define USAGE "\
\n\
Usage: %s [-IdwhV] mof-files\n\
    Produces HTML output from CIM MOF input Classes.\n\
    Output produced to current working directory.\n\
\n\
Where:\n\
    -I path    MOF include path\n\
    -d         enabled debug printing\n\
    -w         enable warnings\n\
    -h         display this usage\n\
    -V         display version\n\
    -v string  CIM Version string for index page\n\
\n"

// Appends this subelement to cimple version string since we are going to 
// distribute this program independently so that we can keep subversions within
// a cimple release version. For 
const char* mof2html_ver = "002";

// Options variables
static string cim_version_string_opt = "";

// some useful routines
//

string _toString(vector<string>& strs)
{
    string rtn;
    for (size_t i = 0 ; i < strs.size() ; i++)
    {
        if (i != 0)
        {
            rtn.append(", ");
        }
        rtn.append(strs[i]);
    }
    return(rtn);
}

// generate the number of html line breaks defined by the input count
void gen_html_linebreak(FILE* os, int count)
{
    for (int i = 0 ; i < count ; i++)
    {
        fprintf(os, "  <br>\n");
    }
}

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

    while ((opt = getopt(argc, argv, "I:dwhVv:")) != -1)
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
            case 'h':
            {
                fprintf(stderr, USAGE, argv[0]);
                exit(0);
            }
            case 'v':
            {
                if (!optarg)
                {
                    fprintf(stderr, "missing argument on -v option\n");
                    exit(1);
                }
                cim_version_string_opt = optarg;
                break;
            }
            case 'V':
            {
                printf("%s(%s)\n", CIMPLE_VERSION_STRING, mof2html_ver);
                exit(0);
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


// generate a credit line that defines this program and simplewbem including
// the version of this program
void gen_page_credit(FILE* os)
{
    gen_html_linebreak(os, 1);

    time_t now = time(0);
    char* stime = asctime( localtime(&now) );
    const char* simple_web_site = "simplewbem.org";

    fprintf(os, "<small>Generated by mof2html v.%s(%s). "
            "<a href=\"%s\">%s</a> %s</small>\n",
            CIMPLE_VERSION_STRING, mof2html_ver,
            simple_web_site, simple_web_site, stime);
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
// _meta_type_name() return class type as string
//
//------------------------------------------------------------------------------

static const char* _meta_type_name(const MOF_Class_Decl* cd)
{
    if (cd->qual_mask & MOF_QT_ASSOCIATION)
        return "association";
    else if (cd->qual_mask & MOF_QT_INDICATION)
        return "indication";
    else
        return "class";
}

//------------------------------------------------------------------------------
//
// put_string - output string to file with conversion of html escape char
//
//------------------------------------------------------------------------------
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
            fprintf(os, "\n");
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
//------------------------------------------------------------------------------
//
// open_file - Open a file for output based on the provided name and
// return the FILE handle.  Exit with error if file cannot be opened.
// NOTE: Only serious errors should cause failure to open
//
//------------------------------------------------------------------------------
FILE* open_file(const char* filename)
{
    FILE* os = fopen(filename, "wb");

    if (!os)
    {
        fprintf(stderr, "error: failed to open %s\n", filename);
        exit(1);
    }

    return(os);
}

//------------------------------------------------------------------------------
//
// gen_qualifiers - generate the qualifiers as a table
//
//------------------------------------------------------------------------------
static void gen_qualifiers(FILE* os, const MOF_Qualifier_Info* info)
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

static void gen_class_description(FILE* os, const MOF_Qualifier* q)
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

/*
    return a complete html ref for the html file with the
    same name as the input name.
*/
string html_file_name_href(const char * name)
{
    string rtn("<a href=");
    rtn += name;
    rtn += ".html>";
    rtn += name;
    rtn +="</a>";
    //printf("html_file_name_href %s %s\n",name, rtn.c_str());
    return(rtn);
}
void gen_class_header(FILE* os, const MOF_Class_Decl* cd)
{
    // fprintf(os, "  <center>\n");

    if (cd->super_class)
    {
        fprintf(os, "<h2>%s %s : %s\n", 
            _meta_type_name(cd), cd->name,
            html_file_name_href(cd->super_class->name).c_str());
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

void gen_method_page(const MOF_Class_Decl* p, const MOF_Feature_Info* f)
{
    char buffer[1024];
    sprintf(buffer, "%s%s.html", p->name,f->feature->name);

    FILE* os = open_file(buffer);
    fprintf(os, "<head>\n");
    fprintf(os, "  <title>%s</title>\n", p->name);
    fprintf(os, "</head>\n");
    fprintf(os, "<body bgcolor=lightgrey>\n");
    fprintf(os, "  <br>\n");
	fprintf(os, "Class %s Method %s\n", p->name, f->feature->name);
    fprintf(os, "  <br>\n");

    fprintf(os, "<h2>Description:</h2>\n");

    fprintf(os, "  <table summary=layout border=0 width=\"80%%\">\n");
    fprintf(os, "  <tr>\n");
    fprintf(os, "  <td>\n");
    ///gen_class_description(os, f->qualifiers);
    fprintf(os, "  </td>\n");
    fprintf(os, "  </tr>\n");
    fprintf(os, "  </table>\n");

	// Start table
	// Table has rows for Parameter, Type, Direction, Qualifiers
    fprintf(os, "  <br>\n");
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
    fprintf(os, "        <th>Parameter</ht>\n");
    fprintf(os, "        <th>Type</ht>\n");
#if 0
    fprintf(os, "        <th>Property</ht>\n");
#endif
    fprintf(os, "        <th>Direction</ht>\n");
#if 0
    fprintf(os, "        <th>Description</ht>\n");
#endif
    fprintf(os, "        <th>Qualifiers</ht>\n");
    fprintf(os, "      </tr>\n");
    fprintf(os, "    </thead>\n");
    fprintf(os, "    <tbody>\n");

	// Output table row for each Parameter

	const MOF_Method_Decl* md = f->feature->
	const MOF_Parameter* parameters = md->parameters;

	for (const MOF_Feature_Info* f = (const MOF_Feature_Info*)p->all_features; 
        f; 
        f = (const MOF_Feature_Info*)f->next)
	{
	}

	// end table
    fprintf(os, "    </tbody>\n");
    fprintf(os, "  </table>\n");
    print_typo_conventions(os);

    gen_page_credit(os);
    fprintf(os, "</body>\n");

    fclose(os);
}
//------------------------------------------------------------------------------
//
// gen_class_html - generate the class html output
//                  all info is in the class decl except for the children
//                  class names
//
//------------------------------------------------------------------------------
void gen_class_html(const MOF_Class_Decl* p,
                    const vector<string> children_names)
{
    char buffer[1024];
    sprintf(buffer, "%s.html", p->name);

    FILE* os = open_file(buffer);

    fprintf(os, "<head>\n");
    fprintf(os, "  <title>%s</title>\n", p->name);
    fprintf(os, "</head>\n");
    fprintf(os, "<body bgcolor=lightgrey>\n");
    fprintf(os, "  <br>\n");
    gen_class_header(os, p);
    fprintf(os, "  <br>\n");
    gen_class_description(os, p->qualifiers);
    fprintf(os, "  <br>\n");
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

    // For all Features in the class
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

            fprintf(os, "        <td>%s</td>\n",
                html_file_name_href(rd->class_name).c_str());
        }
        else if (f->feature->type == MOF_FEATURE_METHOD)
        {

            fprintf(os, "        <td><a href=\"%s%s.html\">method</a></td>\n",
					p->name, f->feature->name);
			gen_method_page(p,  f);
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

        // output class origin.  Make href if this not the origin class
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
        gen_qualifiers(os, f->feature->all_qualifiers);
        fprintf(os, "</td>\n");

        fprintf(os, "      </tr>\n");
    }

    fprintf(os, "    </tbody>\n");
    fprintf(os, "  </table>\n");

    // If there are and children, output the names.
    if (children_names.size() != 0)
    {
        fprintf(os, "  <h2>Direct Subclasses:</h2>\n");
    
        // output comma separated list of children class names
        for (size_t i = 0 ; i < children_names.size() ; i++)
        {
            // TODO generalize this with the other href so we have
            // single href output function

            // put comma, space before all entries but first
            fprintf(os,"%s\n",((i != 0)? ", " : ""));

            fprintf(os, "      %s",
                    html_file_name_href(children_names[i].c_str()).c_str());
        }
    }

    print_typo_conventions(os);

    gen_page_credit(os);
    fprintf(os, "</body>\n");

    fclose(os);
}

/* Define a local class declaration structure that includes a pointer to
   the MOF class declaration and any specific operators that would be
   helpful
*/
struct Class_Decl
{
    const MOF_Class_Decl* class_decl;

    // constructor. Saves the * to MOF_Class_Decl in the local structure.
    Class_Decl(const MOF_Class_Decl* cd) : class_decl(cd) { }

    // declare operation < for sort 
    friend int operator<(const Class_Decl& x, const Class_Decl& y)
    {
        return strcmp(x.class_decl->name, y.class_decl->name) < 0;
    }
};
//------------------------------------------------------------------------------
//
// ClassesTable - Structure containing classes 
//
//------------------------------------------------------------------------------
class ClassesTable
{
public:
    ClassesTable();
    ~ClassesTable();

    // copy constructor
    // append a new decl to the table
    void append(const MOF_Class_Decl* cd);
    // find the class named name
    const MOF_Class_Decl* find_class_decl(const char* name);
    // find the superclass named name
    const MOF_Class_Decl* find_super_class_decl(const char* name);
    // sort the table in name order
    void sort_table();
    // find first generation subclasses of the input class name and
    // return in a new ClassesTable
    ClassesTable find_children(const char* name);

private:
    vector<Class_Decl> Class_Decls;
};

ClassesTable::ClassesTable()
{
}
ClassesTable::~ClassesTable()
{
}

void ClassesTable::append(const MOF_Class_Decl* cd)
{
    Class_Decls.push_back(cd);
}

const MOF_Class_Decl* ClassesTable::find_class_decl(const char* class_name)
{
    for (size_t i = 0 ; i < Class_Decls.size() ; i++)
    {
        const MOF_Class_Decl* cd = Class_Decls[i].class_decl;

        if (strcasecmp(class_name, cd->name) == 0)
        {
            //printf("find_class found %s \n", cd->name);
            cd->print();
            return(cd);
        }
    }
    assert(false);
    return(0);
}

const MOF_Class_Decl* ClassesTable::find_super_class_decl(const char* class_name)
{
    for (size_t i = 0 ; i < Class_Decls.size() ; i++)
    {
        const MOF_Class_Decl* cd = Class_Decls[i].class_decl;

        if (strcasecmp(class_name, cd->super_class_name) == 0)
        {
            //printf("find_class found %s \n", cd->name);
            cd->print();
            return(cd);
        }
    }
    assert(false);
    return(0);
}
ClassesTable  ClassesTable::find_children(const char* class_name)
{
    // New vector to contain the children
    ClassesTable children;

    // For all classes where superclass name matches input class_name
    // create a new Class_Decl and put in the children vector
    for (size_t i = 0; i < Class_Decls.size(); i++)
    {
        const MOF_Class_Decl* cd = Class_Decls[i].class_decl;

        if ( (cd->super_class_name != 0) &&
             (strcasecmp(class_name, cd->super_class_name) == 0))
        {
            children.append(cd);
        }
    }

    return(children);
}

void ClassesTable::sort_table()
{
    sort(Class_Decls.begin(), Class_Decls.end());
}

// search the classes array for a particlar class.   
// TODO build this into the struct
const MOF_Class_Decl* find_class_decl(vector<Class_Decl>& classes,
                                      const char* class_name)
{
    for (size_t i = 0 ; i < classes.size() ; i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;

        if (strcasecmp(class_name, cd->name) == 0)
        {
            printf("find_class found %s \n", cd->name);
            cd->print();
            return(cd);
        }
    }
    assert(false);
    return(0);
}

// generate a single class href with the indent defined. This function generates
// the defined indent, the href for the class pointing to the class html, and
// the anchor with the classname.
// If show_metatype is true, it generates the meta_type string.
// If show_superclass is true, the superclass href is also appended. 

void gen_class_href(FILE* os,
                      const MOF_Class_Decl* cd,
                      int level,
                      bool show_metatype,
                      bool show_superclass,
					  const char* treefilename)
{
    // indent the defined number of spaces for each indent level
    // TODO: I think this indent mechanism is font sensitive.  Need
    // to generalize positioning,
    for (int i = 0 ; i < (level - 2) ; i++ )
    {
        fprintf(os, "|&nbsp&nbsp&nbsp&nbsp&nbsp");
    }
    if (level > 0)
    {
        fprintf(os, "|___");
    }

    // print the href and anchor for the defined name
    fprintf(os, "  <a href=\"%s.html\">%s (%s)</a>" 
                "<a name=\"%s\"></a>",
        cd->name, cd->name, 
        ((show_metatype)? _meta_type_name(cd) : ""),
        cd->name);

		if (treefilename != NULL)
		{
			// show link to tree view
			fprintf(os, "<a href=\"%s#%s\">(tree)</a>\n", treefilename,cd->name);
		}
		else
		{
			fprintf(os,"\n");
		}

        // If there is a superclass, append it as another hyperlink
        // TODO: add the meta_type_name to the superclass
        if ( show_superclass && cd->super_class_name != 0)
        {
            fprintf(os, " : <a href=\"#%s\">%s</a>", 
                cd->super_class_name, cd->super_class_name);

        }
	

    fprintf(os, "  <br>\n");
}


/* Find the first generation children of the defined class name
    Returns a new vector containing all first generation children
    Class_Decl's
*/
vector<Class_Decl>  find_children(vector<Class_Decl>& classes,
                                         const char* class_name)
{
    // New vector to contain the children
    vector<Class_Decl> children;

    // For all classes where superclass name matches input class_name
    // create a new Class_Decl and put in the children vector
    for (size_t i = 0; i < classes.size(); i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;

        if ( (cd->super_class_name != 0) &&
             (strcasecmp(class_name, cd->super_class_name) == 0))
        {
            children.push_back(cd);
        }
    }

    return(children);
}

/* Recursive function to generate all the children classes of an input
   class. each call outputs the  level of the hiearchy as an href
   and recalls gen_children to generate the next level. 
*/
void gen_children(FILE* os,
                    vector<Class_Decl>& classes,
                    const char* class_name,
                    int level)
{
    level++;

    vector<Class_Decl> children = find_children(classes, class_name);

    // for each child, print the href and recall print_children to 
    // get the next level.
    for (size_t i = 0 ; i < children.size() ; i++)
    {
        const MOF_Class_Decl* cd = children[i].class_decl;

        gen_class_href(os, cd, level, true, false, NULL);
        gen_children(os, classes,cd->name, level);
    }
}
/*
    Execute Find children and get the names of the children
    classes into a vector of strings.
*/
vector<string> get_children_names(vector<Class_Decl>& classes,
                                    const char* name)
{
    // get class decls for children
    vector<Class_Decl> children = find_children(classes, name);

    // create vector of names of the children

    vector<string> children_names;

    // build string vector of names of children classes
    for (size_t i = 0 ; i < children.size() ; i++)
    {
        const MOF_Class_Decl* cd = children[i].class_decl;
        children_names.push_back(cd->name);
    }
    return(children_names);
}

void gen_list_page_title(FILE* os)
{
    // generate the title string with input cim version
    string title = "CIM Classes";
    if (cim_version_string_opt.size() != 0)
    {
        title.append(" - CIM Model Version(");
        title.append(cim_version_string_opt);
        title.append(")");
    }

    // generate the header section
    fprintf(os, "<head>\n");
    fprintf(os, "  <title>%s</title>\n", title.c_str());
    fprintf(os, "</head>\n");

    // generate the header part of the page body
    // standard with the title string
    fprintf(os, "<body bgcolor=lightgrey>\n");
    fprintf(os, "  <center>\n");
    fprintf(os, "    <h2>%s</h2>\n",title.c_str());
    fprintf(os, "  </center>\n");

    fprintf(os, "  <hr>\n");
    gen_html_linebreak(os, 1);
}

void gen_class_tree_doc(const char* filename,
                  vector<Class_Decl>& classes, 
                  const char* listfilename)
{
    FILE* os = open_file(filename);

    // generate title and header line for the
    // index file with CIM version if it was input.

    gen_list_page_title(os);

    // Generate the first line describing the page and including
    // link to other form of page.
    fprintf(os, "  <big><big><bold>%s</bold></big></big>\n",
                "All Classes Hierarchy(Tree) View -");
    fprintf(os, "  See also the <a href=\"%s\">Alphabetic List View</a>\n",
            listfilename);

    gen_html_linebreak(os, 2);

    // Create class hierarchy tree from the classes vector.
    for (size_t i = 0; i < classes.size(); i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;
        
        // Output for the highest level (no superclass) and call the
        // gen_children function to generate subclasses.
        if (cd->super_class_name == 0)
        {
            gen_class_href(os, cd, 0, true, false, NULL);
            // recall for children with next level.
            gen_children(os, classes, cd->name, 1);
        }
    }
    gen_page_credit(os);
    fprintf(os, "</body>\n");
    fclose(os);
}

void gen_class_list_doc(const char* filename, vector<Class_Decl>&  classes,
                       const char* treefilename)
{
    FILE* os = open_file(filename);
    
    //
    // Generate list file
    //

    // generate title and header lines

    gen_list_page_title(os);

    fprintf(os, "  <big><big><bold>%s</bold></big></big></bold>\n",
                    "All Classes List View -");
    fprintf(os, "  <i><\":\" %s</i>\n",
                    "Classname is superclass> ");
    fprintf(os, " See also the <a href=\"%s\">Class Hierarchy View</a>.\n",
                    treefilename);

    gen_html_linebreak(os, 2);

    // Generate the classes list into the open file.
    // Each entry is classname with hyperlink and superclass name with
    // hyperlink to that entry in the index (if superclass exists)
    for (size_t i = 0; i < classes.size(); i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;
		
        // Output the hyperlink for this class
        gen_class_href(os, cd, 0, true, true, treefilename);
    }

    gen_page_credit(os);
    fprintf(os, "</body>\n");
    fclose(os);
}



// generate association list entry. We do this to have a structure to
// sort.
struct Association_Decl
{
    const MOF_Feature_Info* feature_info;
    const char* classname;
    Association_Decl(const MOF_Feature_Info* fid, char* name ) :
         feature_info(fid), classname(name) { }

    // declare operation < for sort. Sorts on class name
    friend int operator<(const Association_Decl& x, const Association_Decl& y)
    {
        const MOF_Reference_Decl* rdx = (MOF_Reference_Decl*)x.feature_info->feature;
        const MOF_Reference_Decl* rdy = (MOF_Reference_Decl*)y.feature_info->feature;

        return strcmp(rdx->class_name, rdy->class_name) < 0;
    }
};

void gen_association_doc(vector<Class_Decl>& classes, const char* filename)
{
    // Build the association list
    vector<Association_Decl> associations;
    printf("Ref cd->name     rd->class_name    rd->classname     f->feature->name rd->class_decl->name\n");
    for (size_t i = 0 ; i < classes.size() ; i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;
        // build list of children names
        if (cd->qual_mask & MOF_QT_ASSOCIATION)
        {
            for (
                const MOF_Feature_Info* f = (const MOF_Feature_Info*)cd->all_features;
                f;
                f = (const MOF_Feature_Info*)f->next)
            {
                if (f->feature->type == MOF_FEATURE_REF)
                {
                    const MOF_Reference_Decl* rd = (MOF_Reference_Decl*)f->feature;

                    printf("%22s   %22s %22s %22s %22s\n",
                           cd->name,         // this association name
                           rd->class_name,   // reference class name
                           rd->name,         // ????
                           f->feature->name, // name of this feature (role)
                           rd->class_decl->name);
                    associations.push_back(
                        Association_Decl(f,cd->name));
                }
            }
        }
    }
    // sort the class vector into alphabetical order
    sort(associations.begin(), associations.end());
    //printf("assoc feature->name  rd->name       rd->class_name \n");

    FILE* os = open_file(filename);

    // generate title and header lines

    gen_list_page_title(os);

    fprintf(os, "  <big><big><bold>%s</bold></big></big></bold>\n",
                    "All Classes List View -");
    fprintf(os, "  <i><\":\" %s</i>\n",
                    "Classname is superclass> ");
//  fprintf(os, " See also the <a href=\"%s\">Class Hierarchy View</a>.\n",
//                  treefilename);

    gen_html_linebreak(os, 2);
    fprintf(os," out            rd->name              f->feature->name       asswociations[i].classname\n");
    for (size_t i = 0 ; i < associations.size() ; i++)
    {
        const MOF_Feature_Info* f = associations[i].feature_info;
        const MOF_Reference_Decl* rd = (MOF_Reference_Decl*)f->feature;
        char empty[4] = "";
        char* prev_class_name;
        char* out;
        prev_class_name = empty;
        if (strcmp(rd->class_name, prev_class_name) == 0)
        {
            out = empty;
        }
        else
        {
            out = rd->class_name;
        }
        prev_class_name = rd->class_name;

        fprintf(os, "%22s %22s %22s %22s\n", 
                                    out, rd->name, f->feature->name,
                                    associations[i].classname);
    }
}


/* 
    Generate the class docs including:
    - files for each class
    - alphabetic list file
    - tree file
    First moves the MOF structure from the compiler to our own
    Class_Decl and then generates the files from this structure.
*/

void gen_class_html_docs()
{
    // Define files names for index and the tree pages
    const char INDEXFILENAME[] = "index.html";
    const char TREEFILENAME[]="allclasstree.html";
    const char ASSOCDOCNAME[] = "associations.html";

    // Create the classes vector of all of the classes from
    // the MOF_Class_Decl list

    vector<Class_Decl> classes;
    for (MOF_Class_Decl* p = MOF_Class_Decl::list; 
        p; 
        p = (MOF_Class_Decl*)p->next)
    {
        classes.push_back(p);
    }

    // Build all of the class html files
    for (size_t i = 0 ; i < classes.size() ; i++)
    {
        const MOF_Class_Decl* cd = classes[i].class_decl;
        // build list of children names
        vector<string> children = get_children_names(classes,
                                                 cd->name);
        // generate class html page
        gen_class_html(cd, children);
    }

    // sort the class vector into alphabetical order
    sort(classes.begin(), classes.end());

    //generate the association page
    gen_association_doc(classes, ASSOCDOCNAME);

    // generate the alphabetic list of classes (the index file)
    gen_class_list_doc(INDEXFILENAME, classes, TREEFILENAME);

    // generate the  correspondingclass tree page
    gen_class_tree_doc(TREEFILENAME, classes, INDEXFILENAME);
}

//------------------------------------------------------------------------------
//
// main - Process options, generate anything required by options, call parser
// and call function to generate output from parser.
//
//------------------------------------------------------------------------------
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
    // Print include paths (if -d option given)
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
    // Parse each MOF file:
    //

    for (int i = first_non_option_index; i < argc; i++)
        MOF_parse_file(argv[i]);

    // The output for the parser is the intermediate tree structure
    // as defined by the MOF_CLASS_DECL, MOF_INSTANCE_DECL, and
    // MOF_qualifier_Decl structures.
    
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
    // Generate class name list and html page for each mof entry
    // This is, in effect the second phase of a mof compiler, the 
    // compiler generation phase. It uses the structures generated by
    // the parser phase.
    //

    gen_class_html_docs();

    return 0;
}
