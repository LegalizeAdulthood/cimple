#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s path\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);

        void* handle = dlopen(argv[i], RTLD_NOW | RTLD_GLOBAL);

        if (!handle)
        {
            fprintf(stderr, "%s: cannot load library: %s\n", argv[0], argv[i]);
            fprintf(stderr, "%s\n\n", dlerror());
        }
        else
            dlclose(handle);
    }

    return 0;
}

