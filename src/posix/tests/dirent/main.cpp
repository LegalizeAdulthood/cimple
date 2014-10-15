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

#pragma warning(disable : 4786)

#include <dirent.h>
#include <cassert>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    DIR* dir = opendir("dir1");
    assert(dir != NULL);

    dirent* ent;

    vector<string> names;

    while ((ent = readdir(dir)) != NULL)
    {
	string name = ent->d_name;

	if (name == "." || name == ".." || name == "CVS")
	    continue;

	names.push_back(name);
    }

    sort(names.begin(), names.end());

    assert(names.size() == 5);
    assert(names[0] == "a.txt");
    assert(names[1] == "b.txt");
    assert(names[2] == "c");
    assert(names[3] == "d");
    assert(names[4] == "e");

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
