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
    File FileSystem level interfaces, specifically those that might have
    portability options.
*/

#include <cassert>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>
#include "FileSystem.h"
#include <errno.h>

#ifdef CIMPLE_WINDOWS_MSVC
# include <windows.h>
# include <io.h>
# include <fcntl.h>
#endif

CIMPLE_NAMESPACE_BEGIN

using namespace std;
#define TRX printf("TRACE FileSystem %u\n", __LINE__)
//#define TRX

/*
    If file exists, return true
*/
bool FileSystem::exists(const char* path)
{
#ifdef CIMPLE_WINDOWS_MSVC
    return (_access(path, 0) == 0);
#else
    return (access(path, F_OK) == 0);
#endif
}

/**
 * Return the size in bytes of the file
 * @param path - Path to the file
 * @param size - Size in bytes of the file
 * 
 * @return bool true if the operation succeeded
 */
bool FileSystem::get_size(const char * path, uint32& size)
{
    struct stat st;
    if (stat(path, &st) != 0)
        return false;

    size = st.st_size;
    return true;
}

bool FileSystem::get_line(std::istream& is, Buffer& line)
{
    const uint32 buffersize = 1024;
    uint32 gcount = 0;

    line.clear();

    // Read the input line in chunks.  A non-full buffer indicates the end of
    // the line has been reached.
    do
    {
        char input[buffersize];
        // Read up to buffersize-1 char, but stop before consuming nl char
        is.get(input, buffersize);
        gcount = (uint32)is.gcount();
        line.append(input, gcount);

        if (is.rdstate() & std::istream::failbit)
        {
            // Okay if hit newline character without reading data
            is.clear();
            break;
        }
    } while (gcount == buffersize-1);

    if (!is.eof())
    {
        // Consume nl char, get() doesn't
        char c = 0;
        is.get(c);
    }
    return !!is;
}

bool FileSystem::delete_file(const char* file_path)
{
    return unlink(file_path) == 0;
}

bool FileSystem::rename_file(const char* old_path, const char* new_path)
{
#ifdef CIMPLE_WINDOWS_MSVC
    // Windows cannot rename if new path exists.
    if (exists(old_path))
    {
        delete_file(new_path);
    }
#endif 
//  Remember to comment out the above endif   
////// Temp replacement to above shows what is happening because having
//  problems with rename on log file rollover
//  bool rtn = (rename(old_path, new_path) == 0);
//  int error_number = errno;
//  if (!rtn)
//  {
//      printf("FileSystem.cpp: rename funct rtn=%s\n", (rtn? "true" : "false"));
//  }
//  if (!exists(new_path))
//  {
//      printf("FileSystem.cpp: New Path does not exist after rename %s error errno %s \n", new_path,
//             strerror( error_number ));
//  }
//  if (exists(old_path))
//  {
//      printf("FileSystem.cpp: Old Path still exists after rename %s error %s\n", old_path,
//             strerror( error_number));
//  }
//  return rtn;
///////////////// End of temp code
//#else
    return(rename(old_path, new_path) == 0);
// remember to uncoment the following
//#endif        
}

bool FileSystem::copy_file(const char* from_path, const char* to_path)
{
    ifstream is(from_path, std::ios::binary);
    fstream os(to_path, ios::out  | std::ios::binary);

    char c;

    while (is.get(c))
    {
        if (!os.put(c))
            return false;
    }
    return is.eof();
}

// not used
//void FileSystem::translateSlashes(String& path)
//{
//    for (uint32 i = 0; i < path.size(); i++)
//    {
//        if (path[i] == '\\')
//            path.set(i,'/');
//    }
//}
bool FileSystem::compare_files(const char* path1, const char* path2)
{
    uint32 file1_size;
    uint32 file2_size;

    if (!get_size(path1, file1_size))
    {
        return false;
    }
    if (!get_size(path2, file2_size))
    {
        return false;
    }
    if (file1_size != file2_size)
    {
        return false;
    }

    ifstream is1(path1, std::ios::binary);
    ifstream is2(path1, std::ios::binary);

    //is1.open(is1);
    //is2.open(is2);

    char c1;
    char c2;

    while (is1.get(c1) && is2.get(c2))
    {
        if (c1 != c2)
            return false;
    }
    is1.close();
    is2.close();

    return true;
}

bool FileSystem::truncate_file(
    const char* path,
    size_t length)
{
#ifdef CIMPLE_WINDOWS_MSVC
    bool rv = false;
    int fd = open(path, O_RDWR);
    if (fd != -1)
    {
        if (chsize(fd, (long)length) == 0)
            rv = true;

        close(fd);
    }

    return rv;

#elif defined(CIMPLE_UNIX)

    return (truncate(path, length) == 0);

#else
#error "No implementation defined for truncate_File"
#endif
}

CIMPLE_NAMESPACE_END
