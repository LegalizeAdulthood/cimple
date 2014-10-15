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

#ifndef _cimple_util_h
#define _cimple_util_h

#include <string>
#include "crc.h"
#include "UUID.h"
#include "MAC.h"
#include "linkage.h"

CIMPLEUTIL_LINKAGE 
std::string toupper(const char* str);

CIMPLEUTIL_LINKAGE 
bool is_c_ident(const char* str);

CIMPLEUTIL_LINKAGE 
void set_arg0(const char* arg0);

CIMPLEUTIL_LINKAGE 
CIMPLE_PRINTF_ATTR(1, 2)
void err(const char* format, ...);

CIMPLEUTIL_LINKAGE 
void warn(const char* format, ...);

CIMPLEUTIL_LINKAGE 
std::string base_name(const std::string& path);

CIMPLEUTIL_LINKAGE 
bool exists(const std::string& path);

CIMPLEUTIL_LINKAGE 
bool is_dir(const char* path);

CIMPLEUTIL_LINKAGE 
bool is_absolute(const char* path);

CIMPLEUTIL_LINKAGE 
std::string shlib_name(const std::string& name);

CIMPLEUTIL_LINKAGE 
std::string shlib_dir(const std::string& root);

CIMPLEUTIL_LINKAGE 
std::string full_shlib_name(const std::string& root, const std::string& name);

CIMPLEUTIL_LINKAGE 
std::string shlib_basename(const std::string& path);

#endif /* _cimple_util_h */
