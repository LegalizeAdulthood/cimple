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

#include <cimple/version.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <unistd.h>
#include <string>
#include <util/util.h>
#include "MOF_Parser.h"
#include "gencommon.h"

using namespace std;

void setup_mof_path()
{
    char* mof_path = getenv("CIMPLE_MOF_PATH");

    if (!mof_path)
    {
	err("please define the CIMPLE_MOF_PATH environment variable. "
	    "It must contain the schema directory (located under the root "
	    "of the CIMPLE distribution). The schema directory is the one "
	    "that contains CIM_Schema.mof.");
	return;
    }

    char* tmp = strdup(mof_path);
    bool schema_mof_found = false;

    for (char* p = strtok(tmp, ":"); p; p = strtok(NULL, ":"))
    {
	MOF_include_paths[MOF_num_include_paths++] = strdup(p);

	string schema_mof = string(p) + string("/CIM_Schema.mof");

	struct stat st;

	if (stat(schema_mof.c_str(), &st) == 0)
	    schema_mof_found = true;
    }

    free(tmp);

    if (!schema_mof_found)
    {
	err("Cannot find CIM_Schema.mof. Please add the directory containing "
	    "this file to the path defined by the CIMPLE_MOF_PATH environment "
	    "variable.");
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

void load_repository(const vector<string>& extra_mof_files)
{
    // Add the current directory to the search path:

    MOF_include_paths[MOF_num_include_paths++] = ".";

    // Setup the MOF path.

    setup_mof_path();

    // Build list of MOF files to parse.

    vector<string> mof_files;
    mof_files.push_back("CIM_Schema.mof");

    if (find_file("repository.mof") == 0)
	mof_files.push_back("repository.mof");

    for (size_t i = 0; i < extra_mof_files.size(); i++)
	mof_files.push_back(extra_mof_files[i]);

    // Load repository classes into memory.

    for (size_t i = 0; i < mof_files.size(); i++)
	MOF_parse_file(mof_files[i].c_str());
}

CIMPLE_INJECT_VERSION_TAG;
