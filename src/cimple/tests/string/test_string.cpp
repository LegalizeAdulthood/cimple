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

#include <cassert>
#include <cctype>
#include <cimple/String.h>
#include <cimple/Array.h>
#include <cimple/octets.h>

using namespace cimple;

int main(int argc, char** argv)
{
    // String()
    {
        String s;
        assert(s.size() == 0);
        assert(s[0] == '\0');
    }

    // String(const String& s)
    {
        const String s("hello");
        const String t = s;
        assert(s.size() == strlen("hello"));
        assert(s == "hello");
        assert(t.size() == strlen("hello"));
        assert(t == "hello");
    }

    // String(const char*)
    {
        const String s("hello");
        assert(s.size() == strlen("hello"));
        assert(s == "hello");
    }

    // reserve()
    {
        String s;
        s.reserve(100);
        assert(s.size() == 0);
        assert(s.capacity() >= 100);

        String t("hello world");
        assert(t.capacity() >= t.size());
        assert(t.size() == strlen("hello world"));
        t.reserve(500);
        assert(t.capacity() >= t.size());
        assert(t.capacity() >= 500);
        assert(t.size() == strlen("hello world"));
        assert(t == "hello world");
    }

    // assign(const String&)
    {
        String s("this is a test");
        String t;

        t = s;
        assert(s.size() == strlen("this is a test"));
        assert(s == "this is a test");
        assert(t.size() == strlen("this is a test"));
        assert(t == "this is a test");

        s = t;
        assert(s.size() == strlen("this is a test"));
        assert(s == "this is a test");
        assert(t.size() == strlen("this is a test"));
        assert(t == "this is a test");
    }

    // assign(const char*, size_t)
    {
        const char MESSAGE[] = "x";
        const size_t LENGTH = sizeof(MESSAGE) - 1;
        String s;
        s.assign(MESSAGE, LENGTH);
        assert(s.size() == LENGTH);
        assert(s == MESSAGE);

        String t("dummy", 5);
        t.assign(MESSAGE, LENGTH);
        assert(t.size() == LENGTH);
        assert(t == MESSAGE);
    }

    // assign(const char*)
    {
        const char MESSAGE[] = "x";
        const size_t LENGTH = sizeof(MESSAGE) - 1;
        String s;
        s.assign(MESSAGE);
        assert(s.size() == LENGTH);
        assert(s == MESSAGE);

        String t("dummy", 5);
        t.assign(MESSAGE);
        assert(t.size() == LENGTH);
        assert(t == MESSAGE);
    }

    // append(const String&)
    {
        String s;

        s.append(String("xxx"));
        assert(s.size() == 3);
        assert(s == "xxx");

        s.append(String("yyy"));
        assert(s.size() == 6);
        assert(s == "xxxyyy");

        s.append(String("zzz"));
        assert(s.size() == 9);
        assert(s == "xxxyyyzzz");
    }

    // append(const char*)
    {
        String s;

        s.append("xxx");
        assert(s.size() == 3);
        assert(s == "xxx");

        s.append("yyy");
        assert(s.size() == 6);
        assert(s == "xxxyyy");

        s.append("zzz");
        assert(s.size() == 9);
        assert(s == "xxxyyyzzz");
    }

    // append(const char*)
    {
        String s;

        s.append("xxx");
        assert(s.size() == 3);
        assert(s == "xxx");

        s.append("yyy");
        assert(s.size() == 6);
        assert(s == "xxxyyy");

        s.append("zzz");
        assert(s.size() == 9);
        assert(s == "xxxyyyzzz");
    }

    // append(char)
    {
        String s;

        for (int i = 'a'; i <= 'z'; i++)
            s.append(i);

        assert(s.size() == 26);
        assert(s == "abcdefghijklmnopqrstuvwxyz");
    }

    // clear()
    {
        String s("abc");
        String t = s;
        String u = s;

        s.clear();
        assert(t.size() == 3);
        assert(t == "abc");
        assert(t[0] == 'a');
        assert(u.size() == 3);
        assert(u == "abc");
        assert(u[0] == 'a');
        assert(s.size() == 0);
        assert(s[0] == '\0');

        t.clear();
        assert(t.size() == 0);
        assert(t[0] == '\0');
        assert(t == "");
        assert(u.size() == 3);
        assert(u == "abc");
        assert(u[0] == 'a');
        assert(s.size() == 0);
        assert(s == "");
        assert(s[0] == '\0');

        u.clear();
        assert(t.size() == 0);
        assert(t == "");
        assert(t[0] == '\0');
        assert(u.size() == 0);
        assert(u == "");
        assert(u[0] == '\0');
        assert(s.size() == 0);
        assert(s == "");
        assert(s[0] == '\0');
    }

    // c_str()
    {
        String s("abc");
        String t("abc");
        String u("def");
        String v;
        String w("");

        assert(strcmp(s.c_str(), "abc") == 0);
        assert(strcmp(t.c_str(), "abc") == 0);
        assert(strcmp(u.c_str(), "def") == 0);
        assert(strcmp(s.c_str(), t.c_str()) == 0);
        assert(strcmp(s.c_str(), u.c_str()) != 0);
        assert(strcmp(v.c_str(), "") == 0);
        assert(v.c_str()[0] == '\0');
        assert(v[0] == '\0');
        assert(w.size() == 0);
        assert(w[0] == '\0');
        assert(w.c_str()[0] == '\0');
    }

    // set(size_t, char)
    {
        String s("abcdefghijklmnopqrstuvwxyz");

        for (int i = 0; i < 26; i++)
            s.set(i, toupper(s[i]));

        assert(s == "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

    // equal(const String&)
    {
        String t("abc");
        String u("abc");
        String v("def");
        String w("defg");
        String x("");
        String y("");

        assert(t.equal(t));
        assert(u.equal(u));
        assert(v.equal(v));
        assert(w.equal(w));
        assert(x.equal(x));
        assert(y.equal(y));

        assert(t.equal(u));
        assert(u.equal(t));

        assert(!t.equal(v));
        assert(!t.equal(w));
        assert(!t.equal(x));
        assert(!t.equal(y));
        assert(!v.equal(t));
        assert(!w.equal(t));
        assert(!x.equal(t));
        assert(!y.equal(t));

        assert(!v.equal(w));
        assert(!w.equal(v));
        assert(x.equal(y));
        assert(y.equal(x));
    }

    // equal(const char*)
    {
        String t("abc");
        String u("abc");
        String v("def");
        String w("defg");
        String x("");
        String y("");

        assert(t.equal("abc"));
        assert(u.equal("abc"));
        assert(v.equal("def"));
        assert(w.equal("defg"));
        assert(x.equal(""));
        assert(y.equal(""));

        assert(t.equal("abc"));
        assert(u.equal("abc"));

        assert(!t.equal("def"));
        assert(!t.equal("defg"));
        assert(!t.equal(""));
        assert(!t.equal(""));
        assert(!v.equal("abc"));
        assert(!w.equal("abc"));
        assert(!x.equal("abc"));
        assert(!y.equal("abc"));

        assert(!v.equal("defg"));
        assert(!w.equal("def"));
        assert(x.equal(""));
        assert(y.equal(""));
    }

    // equali()
    {
        String s("abc");
        String t("abC");
        String u("ABC");
        String v("xyz");
        String w("");
        String x("");
        assert(s.equali(t));
        assert(s.equali(u));
        assert(!s.equali(v));
        assert(w.equali(x));
        assert(!w.equali(s));
        assert(!w.equali(t));
        assert(!w.equali(v));
    }

    {

        String t;
        const char MESSAGE[] = "hello";
        const size_t LENGTH = sizeof(MESSAGE) - 1;
        String s = String(MESSAGE);
        t = s;
        String u = String(t);

        assert(t.size() == LENGTH);
        assert(t == MESSAGE);
        assert(s.size() == LENGTH);
        assert(s == MESSAGE);
        assert(u.size() == LENGTH);
        assert(u == MESSAGE);

        assert(t[0] == 'h');
        assert(t[1] == 'e');
        assert(t[2] == 'l');
        assert(t[3] == 'l');
        assert(t[4] == 'o');
        assert(t[5] == '\0');

        t.append(" world");
        assert(t.size() == strlen("hello world"));
        assert(t == "hello world");
        assert(s != "hello world");
        assert(s == "hello");
        assert(s.size() == strlen("hello"));

        t.set(0, 'x');
        assert(t == "xello world");
    }

    // find()
    {
        String s("abcXYZabcdefLMNOP");
        
        assert(s.find('a') == 0);
        assert(s.find('X') == 3);
        assert(s.find('P') == (s.size() - 1));
        assert(s.find('a', 4) == 6);
        String def("def");
        assert(s.find(def) == 9);
        assert(s.find("def") == 9);
        assert(s.find("blah") == (size_t)-1);
        String blah("blah");
        assert(s.find(blah) == (size_t)-1);
    }
    // remove()
    {
        String s("abcXYZdefLMNOP");

        s.remove(0,0);
        assert(s.size() == 14);
        assert(s == "abcXYZdefLMNOP");

        s.remove(0, 3);
        assert(s.size() == 11);
        assert(s == "XYZdefLMNOP");

        s.remove(3, 3);
        assert(s.size() == 8);
        assert(s == "XYZLMNOP");

        s.remove(7, 1);
        assert(s.size() == 7);
        assert(s == "XYZLMNO");

        s.remove(0, 1);
        assert(s.size() == 6);
        assert(s == "YZLMNO");

        s.remove(2, size_t(-1));
        assert(s.size() == 2);
        assert(s == "YZ");

        s.remove(2, 0);
        assert(s.size() == 2);
        assert(s == "YZ");

        s.remove(1, 1);
        assert(s.size() == 1);
        assert(s == "Y");

        s.remove(0, 1);
        assert(s.size() == 0);
        assert(s == "");
        assert(s[0] == '\0');

        s.remove(0,0);
        assert(s.size() == 0);
        assert(s == "");
        assert(s[0] == '\0');
    }

    // substr()
    {
        String s("one two three");
        assert(s.substr(0) == "one two three");
        assert(s.substr(0, 3) == "one");
        assert(s.substr(4, 3) == "two");
        assert(s.substr(8, 5) == "three");
        assert(s.substr(0, 0) == "");
        assert(s.substr(13, 0) == "");
    }

    // Array tests:
    {
        Array<String> v;

        v.resize(4);
        assert(v.size() == 4);

        v[0] = String("0");
        v[1] = String("1");
        v[2] = String("2");
        v[3] = String("3");

#if 0
        for (size_t i = 0; i < v.size(); i++)
            printf("[%s]\n", v[i].c_str());
#endif

        v.remove(0, 1);
        v.remove(0, 1);
        v.remove(0, 1);
        v.remove(0, 1);
    }

    // Octet string testing.
    {
        String s = octets_to_string(0, 0);
        assert(s == "0x00000004");
        assert(string_to_octets(s, 0, 0) == 0);
    }
    {
        unsigned char data1[] = { 1, 2, 3, 4 };
        String s = octets_to_string(data1, sizeof(data1));
        assert(s == "0x0000000801020304");

        assert(string_to_octets(s, 0, 0) == 4);
        unsigned char data2[4] = { 0, 0, 0, 0 };
        ssize_t n = string_to_octets(s, data2, sizeof(data2));
        assert(n == sizeof(data1));

        assert(memcmp(data1, data2, sizeof(data1)) == 0);
    }
    {
        unsigned char data1[] = { 1, 2, 3, 4, 5, 6 };
        String s = octets_to_string(data1, sizeof(data1));
        assert(s == "0x0000000A010203040506");
        assert(string_to_octets(s, 0, 0) == 6);
        unsigned char data2[] = { 0, 0, 0, 0, 0, 0 };
        ssize_t n = string_to_octets(s, data2, sizeof(data2));
        assert(n == 6);
        assert(memcmp(data1, data2, sizeof(data1)) == 0);

        Array<uint8> arr;
        assert(string_to_octets(s, arr) != -1);
        assert(memcmp(data1, arr.data(), sizeof(data1)) == 0);
        assert(arr.size() == sizeof(data1));
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
