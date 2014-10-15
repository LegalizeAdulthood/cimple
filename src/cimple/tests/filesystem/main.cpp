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
    Tests the functions in cimple/FileSystem.h.  Note that many of these
    functions are OS dependent so this test provides rapid assurance that
    these functions work on the target OS before they are used in other
    cimple functionality.
*/

#include <cassert>
#include <cctype>
#include <cimple/cimple.h>
#include <cimple/File_Lock.h>

#include <fstream>
#include <iostream>
#include<cstdio>


using namespace cimple;
#ifdef CIMPLE_WINDOWS
# define TST_FILE_SIZE 105
#else
#define TST_FILE_SIZE 99
#endif

void test01()
{
    // test file exists

    assert(FileSystem::exists("Makefile"));
    assert(!FileSystem::exists("blahblah.junk"));

    // test returned size
    uint32 returned_size;
    assert(FileSystem::get_size("testfile.txt", returned_size));
    assert(returned_size == TST_FILE_SIZE);
    assert(!FileSystem::get_size("blahblah.junk", returned_size));

    if (FileSystem::exists("tempTestFile.txt"))
    {
        FileSystem::delete_file("tempTestFile.txt");
    }

    // test stream functions
    std::fstream fs1;
    fs1.open("tempTestFile.txt", (std::ios::out | std::ios::binary));

    if (!fs1)
        assert(false);

    char blah_data[] = "blah blah blah";
    fs1.write(blah_data, sizeof(blah_data) - 1);
    fs1.close();

    assert(FileSystem::delete_file("tempTestFile.txt"));

    // confirm error on delete of non-existent file.

    assert(!FileSystem::delete_file("tempTestFile.txt"));

    // copy file
    assert(FileSystem::copy_file("testfile.txt", "newtempFile.txt"));

    assert(FileSystem::exists("newtempFile.txt"));
    assert(FileSystem::delete_file("newtempFile.txt"));
    assert(!FileSystem::exists("newtempFile.txt"));

    // rename_file

    // test for rename of non-existent old file.  Should fail.
    assert(!FileSystem::rename_file("tempTestFile.txt", "newtempTestFile.txt"));

    // create new  test file with copy and then use as file to rename
    assert(FileSystem::copy_file("testfile.txt", "renameIn.txt"));
    assert(FileSystem::exists("renameIn.txt"));

    assert(FileSystem::rename_file("renameIn.txt", "renameOut.txt"));
    assert(FileSystem::exists("renameOut.txt"));
    assert(FileSystem::delete_file("renameOut.txt"));
    assert(!FileSystem::exists("renameOut.txt"));

    assert(!FileSystem::exists("renameIn.txt"));

    // test to copy over existing file.

    // TBD

    // Test Compare files

    assert(FileSystem::copy_file("testfile.txt", "renameIn.txt"));

    assert(FileSystem::compare_files("testfile.txt", "renameIn.txt"));
    assert(FileSystem::delete_file("renameIn.txt"));

    assert(!FileSystem::compare_files("testfile.txt", "Makefile"));


    // Test Truncate File
    assert(FileSystem::copy_file("testfile.txt", "testtruncate.txt"));

    assert(FileSystem::truncate_file("testtruncate.txt", 50));
    assert(FileSystem::exists("testtruncate.txt"));
    assert(FileSystem::get_size("testtruncate.txt", returned_size));
    assert(returned_size == 50);

    // confirm no change second time.
    assert(FileSystem::truncate_file("testtruncate.txt", 50));
    assert(FileSystem::exists("testtruncate.txt"));
    assert(FileSystem::get_size("testtruncate.txt", returned_size));
    assert(returned_size == 50);

    // test truncate larger than file. Should create new size and zero
    // file the extension.
    assert(FileSystem::truncate_file("testtruncate.txt", 100));
    assert(FileSystem::exists("testtruncate.txt"));
    assert(FileSystem::get_size("testtruncate.txt", returned_size));
    assert(returned_size == 100);

    assert(FileSystem::delete_file("testtruncate.txt"));

    // Finished successfully

    // reconfirm characteristics of original test file

    assert(FileSystem::get_size("testfile.txt", returned_size));
    assert(returned_size == TST_FILE_SIZE);
}
void test02()
{
    const char * fn = "testfile.txt";
    assert(FileSystem::exists(fn));
//  std::ofstream os;
//  os.open(fn);
//  os.write("blahBlah\n",8);
//  os.put('\n');
//
//  std::ifstream fs;
//  Buffer buffer;
//  assert(!FileSystem::get_line(fs, buffer));

    //bool rtn = FileSystem::open_file("testfile.txt", fs, std::ios::in |std::ios::binary);
    //printf("rtn = %s\n", rtn? "true" : "false");
    //assert(FileSystem::open_file("testfile.txt", fs, std::ios::in |std::ios::binary));

    /*****************************/

    // TODO find issue and remove this bypass apr 2010
#ifndef CIMPLE_WINDOWS
    printf("NOTENOTE: TEMP HOLD FOR WINDOWS");
//    return 0;


    /*************************************/
    //fs.open("testfile.txt", (std::ios::in | std::ios::binary));
    fs.open(fn);
    printf("rtn = %s\n", (!!fs? "true" : "false"));
    //assert(!!fs);
    assert(FileSystem::get_line(fs, buffer));
    printf("line %u\n",__LINE__);

    // ERROR FOUND.  doing the following on buffer before first data
    // usage causes a segmentation fault.
    char * str = buffer.data();
    printf("data read in = $s\n", str);
    assert(strcmp(buffer.data(),"one") == 0);

    assert(FileSystem::get_line(fs, buffer));
    assert(strcmp(buffer.data(),"two") == 0);

    printf("line %u\n",__LINE__);
    assert(FileSystem::get_line(fs, buffer));
    assert(strcmp(buffer.data(),"three four") == 0);

    assert(FileSystem::get_line(fs, buffer));
    assert(strcmp(buffer.data(),"five") == 0);

    printf("line %u\n",__LINE__);
    assert(FileSystem::get_line(fs, buffer));

    assert(FileSystem::get_line(fs, buffer));

    // finally get beyond end of file
    assert(!FileSystem::get_line(fs, buffer));

    printf("line %u\n",__LINE__);
    // delete_file test
    //assert(FileSystem::open("tmpfile.txt", fs, std::ios::out |std::ios::binary));
#endif
}

void test03()
{
    const char* fn = "test3";
    const char* fn2 = "test3a";
    FILE* file_handle;

    if (FileSystem::exists(fn))
        FileSystem::delete_file(fn);

    if (FileSystem::exists(fn2))
        FileSystem::delete_file(fn2);

    file_handle = fopen(fn, "a");
    assert(file_handle);

    Buffer buffer;

    for (uint32 i = 1 ; i < 2 ; i++)
    {
        buffer.format("%s %u\n", "MessageLine ", i);
    
        fwrite(buffer.data(), buffer.size(), 1, file_handle);
        fflush(file_handle);
    }
    assert(fclose(file_handle) == 0);

    assert(FileSystem::exists(fn));
    assert(FileSystem::rename_file(fn, fn2));
    assert(!FileSystem::exists(fn));
    assert(FileSystem::exists(fn2));
    assert(FileSystem::delete_file(fn2));
}

// test file create/append and rename with filelock
void test04()
{
    const char* fn = ".cimple/messages";
    const char* fn2 = ".cimple/messages.1";
    const char* fnlock = ".cimple/messages.lock";

    FILE* file_handle;
    File_Lock* file_lock;

    if (FileSystem::exists(fn))
        FileSystem::delete_file(fn);

    if (FileSystem::exists(fn2))
        FileSystem::delete_file(fn2);

    file_lock = new File_Lock(fnlock);
    assert(file_lock->okay());

    file_handle = fopen(fn, "a");
    assert(file_handle);

    Buffer buffer;
    for (uint32 i = 1 ; i < 400 ; i++)
    {
        buffer.format("%s %u\n", "MessageLine text that means nothing ", i);
    
        file_lock->lock();
        fwrite(buffer.data(), buffer.size(), 1, file_handle);
        fflush(file_handle);
        file_lock->unlock();
    }
    assert(fclose(file_handle) == 0);
    assert(FileSystem::exists(fn));

    file_lock->lock();
    assert(FileSystem::rename_file(fn, fn2));
    file_lock->unlock();

    assert(!FileSystem::exists(fn));
    assert(FileSystem::exists(fn2));
    //assert(FileSystem::delete_file(fn2));
    delete file_lock ;
}

int main(int argc, char** argv)
{
    //test01();

    //test02();

    //test03();

    test04();


    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
