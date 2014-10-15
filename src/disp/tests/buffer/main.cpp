/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include <cassert>
#include <cctype>
#include <disp/Buffer.h>

using namespace cimple;

int main(int argc, char** argv)
{
    Buffer b;
    assert(b.size() == 0);

    b.append("abc", 3);
    assert(b.size() == 3);
    assert(memcmp(b.data(), "abc", b.size()) == 0);

    b.append("wxyz", 4);
    assert(b.size() == 7);
    assert(memcmp(b.data(), "abcwxyz", b.size()) == 0);

    b.insert(0, "lmnop", 5);
    assert(b.size() == 12);
    assert(memcmp(b.data(), "lmnopabcwxyz", b.size()) == 0);

    b.insert(b.size(), "lmnop", 5);
    assert(b.size() == 17);
    assert(memcmp(b.data(), "lmnopabcwxyzlmnop", b.size()) == 0);

    b.remove(0, 1);
    assert(b.size() == 16);
    assert(memcmp(b.data(), "mnopabcwxyzlmnop", b.size()) == 0);

    b.remove(b.size() - 1, 1);
    assert(b.size() == 15);
    assert(memcmp(b.data(), "mnopabcwxyzlmno", b.size()) == 0);

    b.remove(0, 4);
    assert(b.size() == 11);
    assert(memcmp(b.data(), "abcwxyzlmno", b.size()) == 0);

    b.remove(3, 8);
    assert(b.size() == 3);
    assert(memcmp(b.data(), "abc", b.size()) == 0);

    b.remove(0, 3);
    assert(b.size() == 0);

    b.clear();

    const char expect[] = "Today, Mike is 10 years old";
    size_t n = b.appendf("Today, %s is %d years old", "Mike", 10);
    assert(b.size() == n);
    assert(memcmp(expect, b.data(), b.size()) == 0);

    b.clear();
    n = b.appendf("");
    assert(n == 0);
    assert(b.size() == 0);

    n = b.appendf("a");
    assert(n == 1);
    assert(b.size() == 1);

    n = b.appendf("bb");
    assert(n == 2);
    assert(b.size() == 3);

    n = b.appendf("ccc");
    assert(n == 3);
    assert(b.size() == 6);

    n = b.appendf("dddd");
    assert(n == 4);
    assert(b.size() == 10);

    b.append('\0');
    assert(strcmp(b.data(), "abbcccdddd") == 0);

    b.clear();

    Buffer b2;

    for (size_t i = 0; i < 100000; i++)
    {
	char buffer[32];
	int m = sprintf(buffer, "%u", uint32(i));
	b2.append(buffer, m);
	b.appendf("%u", (unsigned int)i);
    }

    assert(b.size() == b2.size());
    assert(memcmp(b.data(), b2.data(), b.size()) == 0);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
