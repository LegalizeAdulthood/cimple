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
#include <cstdlib>
#include <getopt.h>
#include "MOF_Parser.h"

bool Options_ouput = false;

#define USAGE "\
\n\
Usage: %s [-Idw] mof-files\n\
\n\
Where:\n\
        -I path -- include path\n\
        -d -- enabled debug printing\n\
        -w -- enable warnings\n\
        -o -- display the interemediate output tables\n\
        -h -- display usage message\n\
\n"

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

    while ((opt = getopt(argc, argv, "I:dwoh")) != -1)
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
            case 'o':
            {
                Options_ouput = true;
                break;
            }
            case 'h':
            {
                fprintf(stderr, USAGE, argv[0]);
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

    if (MOF_Options::debug || Options_ouput)
    {
        MOF_Class_Decl::print_static_list();
        MOF_Instance_Decl::print_static_list();
        MOF_Qualifier_Decl::print_static_list();
    }

    // MOF_Class_Decl::print_nested_refs();

    return 0;
}

