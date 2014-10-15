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
    Test of the io class. Include both single thread function and
    multithread tests.
    TODO: Add test for the ifprintf function.
*/
#include <cassert>
#include <cimple/config.h>
#include <cimple/io.h>
#include <cimple/Thread.h>
#include <cimple/String.h>

#define verbose_test
using namespace cimple;

// Functions to simplify the tests

/* 
    Function created to test the str_vprintf function that is part of
    buffer. 
*/ 
char * str_vprintf_test(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char* rtn;
    rtn = str_vprintf(fmt, ap);
    va_end(ap);
    return(rtn);
}

// String form of vprintf_test. Returns String rather than
// char *
String string_vprintf_test(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    String rtn;
    rtn = string_vprintf(fmt, ap);
    va_end(ap);
    return(rtn);
}

bool _equal(char* data, char * test)
{
    return((strcmp(data, test) == 0)? true : false);
}

bool _equal(String& str, char * test)
{
    return((strcmp(str.c_str(), test) == 0)? true : false);
}

void _cprint(const char* x)
{
#ifdef verbose_test
    printf("%s\n", x);
#endif
}
void _cprint(const String& x)
{
#ifdef verbose_test
    printf("%s\n", x.c_str());
#endif
}

static void* test01(void* arg)
{
    // standard char* strings for test
    char test[] = "abcdefghijklmnopqrstuvwxyz";

    // test str_printf
    {
        char* output;
        output = str_printf("%s", test);
        assert(output != 0);
        _cprint(output);
        assert(_equal(test,output));

        free((void *)output);
    }

    // test str_printf()
    {
        char* output;
        output = str_vprintf_test("%s", test);
        assert(output != 0);
        _cprint(output);

        assert(_equal(test,output));
        free(output);
    }

    // test iprintf
    {
        size_t size;
        size_t level;

        level = 0;
        size = iprintf(level, "%s", test);

        assert(size == 26);

        level = 1;
        size = iprintf(level, "%s", test);
        
    }

    // test string_printf
    {
        String output = string_printf("%s", test);
        assert(_equal(output, test));
    }

    // test string_printf()
    {
        String output = string_vprintf_test("%s", test);
        _cprint(output.c_str());

        assert(_equal(output,test));
    }

    /// TODO Fix this
//  // test istring_printf()
//  {
//      String output;
//      size_t level = 2;
//      istring_printf(output,2,"%s",test);
//      _cprint(output.c_str());
//
//      assert(_equal(output,test));
//  }

    return arg;
}

int main(int argc, char *argv[])
{
    // execute the test in the main thread
    test01((void*)0);

    // Repeat the test in multiple threads

#ifdef CIMPLE_WINDOWS
    printf("\n+++++ Windows passed all tests (%s)\n", argv[0]);
    return 0;
#else
    const size_t N = 32;
    Thread threads[N];

    for (size_t i = 0; i < N; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        int r = Thread::create_joinable(threads[i], test01, strdup(buffer));
        assert(r == 0);
    }

    for (size_t i = 0; i < N; i++)
    {
        // Create corresponding counter for join.
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        // execute the join
        void* value = 0;
        int r = Thread::join(threads[i], value);
        // printf("join[%s][%s]\n", (char*)value, buffer);
        assert(r == 0);

        // test that we have returned the proper arg value
        assert(strcmp(buffer, (char*)value) == 0);
        free(value);
    }
#endif

    printf("\n+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}



