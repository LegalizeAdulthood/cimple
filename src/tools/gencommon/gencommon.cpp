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
#include <vector>
#include <unistd.h>
#include <string>
#include <dirent.h>
#include <cctype>
#include <util/util.h>
#include "MOF_Parser.h"
#include "gencommon.h"

using namespace std;

size_t find(vector<string>& array, const string& x)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        if (array[i] == x)
            return i;
    }

    return size_t(-1);
}

bool legal_class_name(const string& ident)
{
    const char* p = ident.c_str();

    if (!isalpha(*p) && *p != '_')
        return false;

    while (isalnum(*p) || *p == '_')
        p++;

    return *p == '\0';
}

void append_unique(vector<string>& array, const string& x)
{
    size_t pos = find(array, x);

    if (pos == size_t(-1))
        array.push_back(x);
}

void load_class_list_file(vector<string>& classes, const string& path)
{
    FILE* is = fopen(path.c_str(), "r");

    if (!is)
        err("failed to open \"%s\"", path.c_str());

    char buffer[1024];

    for (int line = 1; fgets(buffer, sizeof(buffer), is) != NULL; line++)
    {
        if (buffer[0] == '#')
            continue;

        char* start = buffer;

        /* Remove leading whitespace. */

        while (isspace(*start))
            start++;

        /* Remove trailing whitespace. */

        char* p = start;

        while (*p)
            p++;

        while (p != start && isspace(p[-1]))
            *--p = '\0';

        /* Skip empty lines. */

        if (*start == '\0')
            continue;

        /* Check whether legal class name. */

        if (!legal_class_name(start))
        {
            err("illegal class name on line %d of %s: \"%s\"",
                line, path.c_str(), start);
        }

        /* Append class to list. */

        append_unique(classes, start);
    }

    fclose(is);
}

static string _schema_mof;

static int _find_schema_mof(const char* path, string& schema_mof, bool verbose)
{
    schema_mof.erase(schema_mof.begin(), schema_mof.end());

    // Look first for file called CIM_Schema.mof.

    {
        string tmp = string(path) + string("/CIM_Schema.mof");
        struct stat st;

        if (stat(tmp.c_str(), &st) == 0)
        {
            schema_mof = tmp;
            return 0;
        }
    }

    // Next Search for a file of the form cimv[0-9]*.mof in this directory
    // which covers the DMTF schemas from about 2.15 to 2.25
    // or cim_schma[0-9.]mof (since about 225 the top level name has been
    // changed to cim_schema_x.yy.z.mof

    DIR* dir = opendir(path);

    if (!dir)
        return -1;

    struct dirent* ent;

    while ((ent = readdir(dir)))
    {
        const char* name = ent->d_name;

        if (strncmp(name, "cimv", 4) == 0)
        {
            const char* p = name + 4;

            while (isdigit(*p))
                p++;

            if (strcmp(p, ".mof") == 0)
            {
                struct stat st;

                string tmp = string(path) + string("/") + string(name);

                if (stat(tmp.c_str(), &st) == 0)
                {
                    schema_mof = tmp;
                    closedir(dir);
                    return 0;
                }
            }
        }
        else if(strncmp(name,"cim_schema_", 11) == 0)
        {
            const char* p = name + 11;

            while (isdigit(*p) || *p == '.')
                p++;

            if (strcmp(p, "mof") == 0)
            {
                struct stat st;

                string tmp = string(path) + string("/") + string(name);

                if (stat(tmp.c_str(), &st) == 0)
                {
                    schema_mof = tmp;
                    closedir(dir);
                    return 0;
                }
            }
        }
    }

    closedir(dir);

    // Not found!
    return -1;
}

void setup_mof_path(bool verbose)
{
    const char* mof_path = getenv("CIMPLE_MOF_PATH");

#if defined(CIMPLE_WINDOWS)
    if (!mof_path)
    {
        err("CIMPLE_MOF_PATH undefined");
    }
#else
    if (!mof_path)
        mof_path = CIMPLE_DEFAULT_SCHEMA;
    if (verbose)
    {
        printf("Using CIMPLE_DEFAULT_SCHEMA = %s\n", mof_path);
    }
#endif

    char* tmp = strdup(mof_path);
    bool found = false;

#if defined(CIMPLE_WINDOWS)
    const char SEP[] = ";";
#else
    const char SEP[] = ":";
#endif

    for (char* p = strtok(tmp, SEP); p; p = strtok(NULL, SEP))
    {
        MOF_include_paths[MOF_num_include_paths++] = strdup(p);

        if (verbose)
            printf("test for mof schema at = %s\n", p);

        if (_find_schema_mof(p, _schema_mof, verbose) == 0)
        {
            if (verbose)
                printf("mof schema %s found.\n", _schema_mof.c_str());

            found = true;
        }

        struct stat st;

        if (stat(p, &st) != 0)
        {
            err("CIMPLE_MOF_PATH specifies a non-existent directory: %s", p);
        }
    }

    free(tmp);

    if (!found)
    {
        err("Failed to find master CIM MOF file on CIMPLE_MOF_PATH. The name "
            "of this file must match \"cimv[0-9]*.mof\",\"CIM_Schema.mof\" "
            "or cim_schema_[0-9.]mof. "
            "CIMPLE_MOF_PATH=%s", mof_path);
    }
}

int find_file(const char* path)
{
    for (size_t i = 0; i < MOF_num_include_paths; i++)
    {
        string full = MOF_include_paths[i];
        full += '/';
        full += path;

        if (access(full.c_str(), F_OK) == 0)
            return 0;
    }

    // Not found!
    return -1;
}

void load_repository(const vector<string>& extra_mof_files, bool verbose)
{
    // Add the current directory to the search path:

    MOF_include_paths[MOF_num_include_paths++] = ".";

    // Setup the MOF path.

    setup_mof_path();

    // Build list of MOF files to parse.

    vector<string> mof_files;
    mof_files.push_back(_schema_mof);

    if (find_file("repository.mof") == 0)
        mof_files.push_back("repository.mof");

    for (size_t i = 0; i < extra_mof_files.size(); i++)
        mof_files.push_back(extra_mof_files[i]);

    // Load repository classes into memory.

    for (size_t i = 0; i < mof_files.size(); i++)
        MOF_parse_file(mof_files[i].c_str());
}
