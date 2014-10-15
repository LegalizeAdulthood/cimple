#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s path symbol\n", argv[0]);
        exit(1);
    }

    //
    // Dynamically load the library.
    //

    void* handle = dlopen(argv[1], RTLD_NOW | RTLD_GLOBAL);

    if (!handle)
    {
        fprintf(stderr, "%s: cannot load library: %s\n", argv[0], argv[1]);
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    //
    // Find the entry point.
    //

    void* sym = dlsym(handle, argv[2]);

    if (!sym)
    {
        fprintf(stderr, "%s: cannot find symbol: %s\n", argv[0], argv[2]);
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

#if 0
    typedef void (*Proc)();
    Proc proc = (Proc)sym;
    proc();
#endif

    printf("okay\n");

    return 0;
}

