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

#include <cstdio>
#include "MOF_Parser.h"

using namespace std;

extern FILE* MOF_in;
extern int MOF_parse();

int MOF_line_num = 0;
char* MOF_file_name = 0;
char* MOF_current_dir = 0;

const char* MOF_include_paths[MAX_INCLUDES];
size_t MOF_num_include_paths = 0;

const char* MOF_generate_classes[MAX_GENERATES];
size_t MOF_num_generate_classes = 0;

FILE* MOF_open_file(const char* path, string& full_path)
{
    full_path.erase(full_path.begin(), full_path.end());

    if (*path == '/')
    {
        full_path = path;
        return fopen(path, "rb");
    }

#ifdef MOF_WINDOWS
    // Check for drive letter:
    {

        const char* p = path;
        if (isalpha(p[0]) && p[1] == ':' && (p[2] == '/' || p[2] == '\\'))
        {
            full_path = path;
            return fopen(path, "rb");
        }
    }
#endif

    for (size_t i = 0; i < MOF_num_include_paths; i++)
    {
        string tmp = MOF_include_paths[i];
        tmp += "/";
        tmp += path;

        FILE* is = fopen(tmp.c_str(), "rb");

        if (is)
        {
            full_path = tmp;
            return is;
        }
    }

    // Not found!
    return 0;
}

int MOF_parse_file(const char* mof_file)
{
    // Open MOF file.

    string path;
    MOF_in = MOF_open_file(mof_file, path);

    if (!MOF_in)
    {
        fprintf(stderr, "failed to open \"%s\"\n", mof_file);
        exit(1);
    }

    // Parse the file.

    MOF_line_num = 1;
    MOF_file_name = strdup(path.c_str());
    MOF_parse();

    // Close the file.

    fclose(MOF_in);
    return 0;
}

