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

#include <libgen.h>
#include <cassert>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv)
{
    char path1[] = "/";
    char path2[] = "/abc";
    char path3[] = "/abc/";
    char path4[] = ".";
    char path5[] = "abc";
    char path6[] = "abc/xyz";
    char path7[] = "/abc";
    char path8[] = "/abc/xyz/lmnop";
    char path9[] = "/////";
    char path10[] = "/usr/lib";
    char path11[] = "..";

    assert(strcmp(dirname(path1), "/") == 0);
    assert(strcmp(dirname(path2), "/") == 0);
    assert(strcmp(dirname(path3), "/") == 0);
    assert(strcmp(dirname(path4), ".") == 0);
    assert(strcmp(dirname(path5), ".") == 0);
    assert(strcmp(dirname(path6), "abc") == 0);
    assert(strcmp(dirname(path7), "/") == 0);
    assert(strcmp(dirname(path8), "/abc/xyz") == 0);
    assert(strcmp(dirname(path9), "/") == 0);
    assert(strcmp(dirname(path10), "/usr") == 0);
    assert(strcmp(dirname(path11), ".") == 0);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
