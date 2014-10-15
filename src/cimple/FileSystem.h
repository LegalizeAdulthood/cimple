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

#ifndef _cimple_FileSystem_h
#define _cimple_FileSystem_h

#include "config.h"
#include "Buffer.h"
#include "String.h"
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>

# define CIMPLE_STD(X) std::X

CIMPLE_NAMESPACE_BEGIN

struct CIMPLE_CIMPLE_LINKAGE FileSystem
{
public:
    static bool exists(const char* path);
    
    static bool get_size(const char * path, uint32& size);

    static bool get_line(std::istream& is, Buffer& line);

    static bool delete_file(const char* file_path);
    /**
    *   Rename file.  If new name refers to an existing file, it is
    *   removed and replaced with renamed file. If there is no
    *   old_file, nothing is changed.
    *   @param oldPath char* contains name of the file to rename.
    *   @param newPath A String contains name to which to rename old
    *                  file.
        @return bool true if rename operation was
            successful.
    */
    static bool rename_file(const char* old_path, const char* new_path);

    static bool copy_file(const char* from_path, const char* to_path);

    // NOT used commented as of 2.0.18
    //void FileSystem::translateSlashes(String& path);

    static bool compare_files(const char* path1, const char* path2);

    /**
     * Truncate a file to the length defined by the parameter 
     * length. 
     * If the file is larger than length, it is truncated to that 
     * length.  If it is shorter, it is extended and zero filled 
     * @param path char* to path of file to be truncated 
     * @param length size of file after truncation 
     * @return bool true if successful 
     *  
     */
    static bool truncate_file(const char* path, size_t length);
};

inline bool streamOpen(CIMPLE_STD(ifstream)& is, const String& path)
{
    is.open(path.c_str());
    return !!is;
}

inline bool streamOpen(CIMPLE_STD(ofstream)& os, const String& path)
{
    os.open(path.c_str());
    return !!os;
}

inline bool streamOpenAppend(CIMPLE_STD(ofstream)& os, const String& path)
{
    os.open(path.c_str(), CIMPLE_STD(ios::app) );
    return !!os;
}
CIMPLE_NAMESPACE_END

#endif /* _cimple_FileSystem_h */
