#include <cassert>
#include <cimple/Error.h>

using namespace cimple;

int main(int argc, char** argv)
{
    CIMPLE_ERROR(("The answer is %d", 12));

    assert(Error::get() != 0);

    // printf("[%s]\n", Error::get());

#ifdef CIMPLE_DEBUG
    assert(strcmp(Error::get(), "main(): main.cpp(8): The answer is 12") == 0);
#else
    assert(strcmp(Error::get(), "The answer is 12") == 0);
#endif

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
