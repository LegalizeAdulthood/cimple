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
    Test of the Buffer class
    Executes both a functional test and multithread test of the methods of this 
    class 
*/
#include <cassert>
#include <cimple/config.h>
#include <cimple/Buffer.h>
#include <cimple/Thread.h>
#include <unistd.h>

using namespace cimple;

bool verbose = false;

// Functions to simplify the tests

// compare the Buffer contents to the input string
bool _equal(const Buffer& b, const char* test)
{
    return (strcmp(b.data(), test) == 0)? true : false;
}

// print the current data
void _print(const Buffer& b)
{
    printf("%s\n", b.data());
}

// print the current capacity
void _capacity(const Buffer& b)
{
    printf("capacity = %zu\n", b.capacity());
}

/* 
    Function created to test the vformat function that is part of
    buffer. 
*/ 
size_t vformat_test(Buffer& b, const char* fmt, ...)
{
    size_t size;
    va_list ap;
    va_start(ap, fmt);
    size = b.vformat(fmt, ap);
    va_end(ap);
    return(size);
}
/*
    Append the character define into the buffer the number of times
    defined by count. Used to create large buffers and test capacity limits
*/
void _append_chars(Buffer& b, char x, int count)
{
    for (int i = 0 ; i < count; i++)
    {
        b.append(x);
    }
}

static void* test01(void* arg)
{

    // standard char* strings for test

    const char testconst[] = "abcdefghijklmnopqrstuvwxyz";    
    char test[] = "abcdefghijklmnopqrstuvwxyz";

    size_t min_capacity = 0;

    // Test Buffer()
    {
        Buffer b;
        assert(b.size() == 0);

        // Find the min_capacity returned by basic reserve
        b.append(test, 26);    // capacity only setup after first append
        min_capacity = b.capacity();
        assert(min_capacity = 4096);
#ifdef ENABLE_BUFFER_DIAG
        b.dump();
        //printf("Dump complete\n");
#endif
        if (verbose)
        {
            printf("Step 1\n");
        }
    }

    // Test Buffer(const Buffer&)
    {
        Buffer b1;
        b1.append(testconst, 26);
        assert(b1.size() == 26);
        Buffer b2 = b1;
        assert(b2.size() == 26);
        assert(_equal(b2, testconst));
        assert(strcmp(b2.data(),  testconst) == 0);
        if (verbose)
        {
            printf("step 1\n");
        }
    }

    // Test operator=Buffer& x)
    {
        Buffer b1;
        b1.append(test, 26);
        assert(b1.size() == 26);
        Buffer b2 = b1;
        assert(b2.size() == 26);
        assert(_equal(b2, test));
        assert(strcmp(b2.data(),  test) == 0);
        if (verbose)
        {
            printf("step 2\n");
        }
    }

    // Test integer append functions
    {
        Buffer b;
        b.append("abcd", 4);
        b.append_uint64(uint64(3456789));
        b.append_uint32(uint32(123456));
        b.append_uint16(uint16(1234));
        assert(_equal(b,"abcd34567891234561234")); 
        if (verbose)
        {
            printf("step 3\n");
        }
    }

    // Test char append functions
    {
        Buffer b;
        b.append('x');
        assert(_equal(b,"x"));
        b.append('y');
        assert(_equal(b,"xy"));
        if (verbose)
        {
            printf("step 4\n");
        }
    }

    // Test capacity and reserve() 
    {
        Buffer b;
        ////_capacity()
        assert(b.capacity() ==  0);
        b.reserve(min_capacity);

        ////_capacity();
        assert(b.capacity() ==  min_capacity);

        // confirm that reducing capacity does nothing
        b.reserve(100);

        ////_capacity());
        assert(b.capacity() ==  min_capacity);

        b.reserve(5000);
        assert(b.capacity() ==  5000);
        if (verbose)
        {
            printf("step 5\n");
        }
    }

    // Test append passing current capacity limit specifically
    {
        Buffer b;

        _append_chars(b, '*', (min_capacity -2));
        assert(b.size() == (min_capacity -2));
        assert(b.capacity() ==  min_capacity);
        b.append(test, 26);
        assert(b.size() == (min_capacity - 2) + 26);
        ////_capacity(b);
        assert(b.capacity() ==  min_capacity * 2);
        if (verbose)
        {
            printf("step 6\n");
        }
    }

    // Test initial append passing current capacity limit
    {
        Buffer b;
        _append_chars(b, '*', 6000);
        ////_capacity(b);
        assert(b.capacity() ==  min_capacity * 2);
        if (verbose)
        {
            printf("step 7\n");
        }
    }

    // Test add with format function
    {
        Buffer b;
        b.format("%s%u%s", "abc", (unsigned int)123456, "def");
        ////_print(b);
        _equal(b,"abc123456def");
        if (verbose)
        {
            printf("step 8\n");
        }
    }

    // Test append very large data input to empty buffer
    {
        Buffer b;
        _append_chars(b, '*', 600000);
        assert(b.size() == 600000);
        ////_capacity(b);
        b.append(test, 26);
        size_t bsize = b.size();
        assert(b[bsize-26] == 'a');
        b.remove(0,600000);
        assert(b[0] == 'a');
        assert(b[25] == 'z');
        if (verbose)
        {
            printf("step 9\n");
        }
    }

    // Test insert to an empty buffer
    {
        Buffer b;
        b.insert(0, test, 26);
        assert(b.size() == 26);
        assert(_equal(b, test));
        if (verbose)
        {
            printf("step 10\n");
        }
    }

    // Test insert very large data to empty buffer
    {
        Buffer b;
        _append_chars(b, '*', 600000);
        assert(b.size() == 600000);
        b.append(test, 26);
        assert(b.size() == 600000 + 26);
        ////_capacity(b);
        size_t bsize = b.size();
        ////printf("size = %zu char %c \n", b.size(), b[bsize-26]);
        assert(b[bsize-26] == 'a');
        b.remove(0,600000);
        assert(b[0] == 'a');
        assert(b[25] == 'z');
        if (verbose)
        {
            printf("step 11\n");
        }
    }

    // Test append with format that passes capacity limits
    {
        size_t size;
        Buffer b;
        _append_chars(b, '*', 4094);
        assert(b.capacity() ==  4096);
        size = b.format("%s%u%s", "abc", (unsigned int)123456, "def");
        assert(size == 12);
        assert(b.size() == 4094 + size);
        assert(b.capacity() == 8192);
        if (verbose)
        {
            printf("step 12\n");
        }
    }

    // test clear()
    {
        Buffer b;
        b.append(test, 26);
        assert(b.size() == 26);
        b.clear();
        assert(b.size() == 0);
        if (verbose)
        {
            printf("step 13\n");
        }
    }

    // Test insert and remove
    {
        Buffer b;
        b.append("abcdefgh", 8);
        assert(b.size() == 8);
        assert(_equal(b, "abcdefgh"));

        b.insert(1, "1234" , 4);
        //_print(b);
        assert(b.size() == 12);
        assert(_equal(b, "a1234bcdefgh"));

        b.insert(0,"xyz", 3);
        assert(b.size() == 15);
        assert(_equal(b,"xyza1234bcdefgh"));

        b.insert(15, "!!!", 3);
        assert(b.size() == 18);
        assert(_equal(b,"xyza1234bcdefgh!!!"));
        ///_print(b);

        b.remove(15, 3);
        assert(b.size() == 15);
        assert(_equal(b,"xyza1234bcdefgh"));
        ///_print(b);

        b.remove(0, 3);
        ///_print(b);
        assert(b.size() == 12);
        assert(_equal(b, "a1234bcdefgh"));

        b.remove(0, 0);
        ///_print(b);
        assert(b.size() == 12);
        assert(_equal(b, "a1234bcdefgh"));

        b.remove(1, 4);
        assert(b.size() == 8);
        assert(_equal(b, "abcdefgh"));
        if (verbose)
        {
            printf("step 14\n");
        }
    }

    // Test insert that passes capacity limit
    {
        Buffer b;
        _append_chars(b, '*', 4094);
        assert(b.size() == 4094);
        assert(b.capacity() ==  4096);
        b.insert(0,test,26);
        assert(b.size() == 4094 + 26);
        //// _capacity(b);
        assert(b.capacity() == 8192);

        // remove the '*' characters. to see if the insert was 
        // placed at the proper point
        b.remove(26, 4094);
        assert(b.size() == 26);
        ////_print(b);
        if (verbose)
        {
            printf("step 15\n");
        }
    }

    // Test insert where the insert causes capacity update. establish
    // that insert 0 zero properly moves things
    {
        Buffer b;
        b.append(test, 26);
        while (b.size() < 100000)
        {
            b.insert(0,test,26);
            assert (b.size() % 26 == 0);
        }
        // test for a and z at proper locations
        for (size_t i = 0 ; i < (b.size() - 26) ; i +=26)
        {
            assert(b[i] == 'a');
            assert(b[i+25] == 'z');
        }

        do 
        {
            b.remove(26, 26);
            ////printf("size = %zu\n", b.size());
            assert(b[26] == 'a');
            assert(b[26+25] ==  'z');
        } while (b.size() > 26 * 2);
        if (verbose)
        {
            printf("step 16\n");
        }
    }

    // Test insert where the insert causes capacity update and insert
    // is within the data, not at boundary. Establish
    // that insert within data properly moves things particularly
    // when we cross capacity boundary
    {
        Buffer b;
        b.append(test, 26);
        while (b.size() < 100000)
        {
            // insert before last sequence
            b.insert((b.size() - 26),test,26);
            assert (b.size() % 26 == 0);
        }

        // test for a and z at proper locations
        for (size_t i = 0 ; i < (b.size() - 26) ; i +=26)
        {
            assert(b[i] == 'a');
            assert(b[i+25] == 'z');
        }

        do 
        {
            b.remove(26, 26);
            ////printf("size = %zu\n", b.size());
            assert(b[26] == 'a');
            assert(b[26+25] ==  'z');
        } while (b.size() > 26 * 2);
        if (verbose)
        {
            printf("step 17\n");
        }
    }

    // test appends which attaches a c defined char* string.
    {
        Buffer b;
        b.appends(test);
        assert(b.size() == 26);
        assert(_equal(b,test));
        if (verbose)
        {
            printf("step 18\n");
        }
    }

    // Test [] operator
    {
        Buffer b;
        b.appends(test);
        assert(b[25] == 'z');
        assert(b[1] == 'b');
        assert(b[0] == 'a');
        assert(b[24] == 'y');
        if (verbose)
        {
            printf("step 19\n");
        }
    }

    // Test end() method
    {
        Buffer b;
        b.appends(test);
        char * end = b.end();
        //printf("end len %ld\n", (b.end() - b.data()));
        assert((b.end() - b.data()) == 26);
        if (verbose)
        {
            printf("step 20\n");
        }
    }

    // Test method created using vformat
    {
        Buffer b;
        vformat_test(b, "%s", test);
        assert(b.size() == 26);
        assert(_equal(b, test));
        if (verbose)
        {
            printf("step 21\n");
        }
    }
    
    // Test the vformat crossing capacity limit
    {
        Buffer b;
        _append_chars(b, '*', 4094);
        assert(b.capacity() ==  4096);

        vformat_test(b, "%s", test);
        assert(b.size() == 4094 + 26);
        /////_capacity(b);
        assert(b.capacity() == 8192);
        if (verbose)
        {
            printf("step 22\n");
        }
    }

    // Test append with single character build
    {
        int MAX_SIZE = 500000;
        size_t capacity = 0;
        Buffer b;

        for (int i = 0 ; i < MAX_SIZE ; i++)
        {
            b.append('*');
            if (b.capacity() != capacity)
            {
                ////printf("new capacity = %zd\n", b.capacity());
                capacity = b.capacity();
            }
        }
        if (verbose)
        {
            printf("step 23\n");
        }
    }

    // Test append to create large buffer with char* append
    {
        int MAX_SIZE = 500000;
        size_t capacity = 0;
        Buffer b;

        for (int i = 0 ; i < MAX_SIZE ; i++)
        {
            b.appends(test);
            if (b.capacity() != capacity)
            {
                ////printf("new capacity = %zd\n", b.capacity());
                capacity = b.capacity();
            }
        }
        if (verbose)
        {
            printf("step 24\n");
        }
    }

    // Test append to create large buffer with format
    {
        int MAX_SIZE = 500000;
        size_t capacity = 0;
        size_t size = 0;
        Buffer b;

        for (int i = 0 ; i < MAX_SIZE ; i++)
        {
            b.format("%s%u%s", "abc", (unsigned int)123456, "def");

            // test shows capacity changes when print enabled
            if (b.capacity() != capacity)
            {
                assert(capacity = b.capacity() + min_capacity);
                ////printf("new capacity = %zd\n", b.capacity());
                capacity = b.capacity();
            }
        }

        // test for a and f at proper locations throughout buffer
        for (size_t i = 0 ; i < (b.size() - 12) ; i +=12)
        {
            assert(b[i] == 'a');
            assert(b[i+11] == 'f');
        }
        if (verbose)
        {
            printf("step 25\n");
        }
    }


    // Test append to create large buffer with vformat
    {
        int MAX_SIZE = 500000;
        size_t capacity = 0;
        Buffer b;

        for (int i = 0 ; i < MAX_SIZE ; i++)
        {
            vformat_test(b, "%s", test);

            // test shows capacity changes
            if (b.capacity() != capacity)
            {
                assert(capacity = b.capacity() + min_capacity);
                ////printf("new capacity = %zd\n", b.capacity());
                capacity = b.capacity();
            }
            assert(b.size() % 26 == 0);
        }

        // test for a and z at proper locations
        for (size_t i = 0 ; i < (b.size() - 26) ; i +=26)
        {
            assert(b[i] == 'a');
            assert(b[i+25] == 'z');
        }
    }
    if (verbose)
    {
        printf("step 26\n");
    }
    return arg;
}

int main(int argc, char *argv[])
{
    test01((void*)0);

    // Repeat the test in multiple threads

    const size_t N = 16;
    Thread threads[N];
    if (verbose)
    {
        printf("Repeat test with Multiple %d Threads\n", N);
    }

    // Set up the multiple threads
    for (size_t i = 0; i < N; i++)
    {
        char buffer[64];
        sprintf(buffer, "%d", int(i));
        // TODO Fix This bug
        // this sleep must be used right now at least with windows because
        // we get a failure which means we have some sort of parallels issue
        // with either buffer or threads.
#ifdef CIMPLE_WINDOWS
        sleep(1);
#endif
        int r = Thread::create_joinable(threads[i], test01, strdup(buffer));
        assert(r == 0);
    }

    // for each thread call test01
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

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}



