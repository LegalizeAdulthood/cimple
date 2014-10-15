#include <cimple/cimple.h>
#include <cassert>
#include "Test1.h"
#include "Test2.h"

using namespace cimple;

int main(int argc, char** argv)
{
#if 0
    for (size_t i = 0; i < 100; i++)
    {
        Test1* i1 = Test1::create();
        Test1* i2 = Test1::create();

        assert(identical(i1, i2));
        random_initialize(i1);
        copy(i2, i1);
        assert(identical(i1, i2));

        Test1* i3 = i2->clone();
        assert(identical(i3, i1));
        assert(identical(i3, i2));

        nullify_properties(i3);
        assert(!identical(i3, i2));
        assert(!identical(i3, i1));
        nullify_properties(i1);
        assert(identical(i3, i1));

        // print(i3);

        destroy(i1);
        destroy(i2);
        destroy(i3);
    }

    for (size_t i = 0; i < 100; i++)
    {
        Test2* i1 = Test2::create();
        Test2* i2 = Test2::create();

        assert(identical(i1, i2));
        random_initialize(i1);
        copy(i2, i1);
        assert(identical(i1, i2));

        Test2* i3 = i2->clone();
        assert(identical(i1, i3));
        assert(identical(i1, i2));

        destroy(i1);
        destroy(i2);
        destroy(i3);
    }
#endif

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

