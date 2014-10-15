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

#ifndef _MOF_Parser_h
#define _MOF_Parser_h

#include "MOF_Config.h"
#include "MOF_Types.h"
#include "MOF_Yacc.h"
#include "MOF_Options.h"
#include <string>
#include <cstdio>
#include <cstdlib>

#define MAX_INCLUDES 2000
#define MAX_GENERATES 2000

MOF_LINKAGE extern int MOF_line_num;
MOF_LINKAGE extern char* MOF_file_name;
MOF_LINKAGE extern char* MOF_current_dir;

MOF_LINKAGE extern const char* MOF_include_paths[MAX_INCLUDES];
MOF_LINKAGE extern size_t MOF_num_include_paths;
MOF_LINKAGE extern const char* MOF_generate_classes[MAX_GENERATES];
MOF_LINKAGE extern size_t MOF_num_generate_classes;
MOF_LINKAGE FILE* MOF_open_file(const char* path, std::string& full_path);
MOF_LINKAGE int MOF_parse_file(const char* mof_file);

#endif /* _MOF_Parser_h */
