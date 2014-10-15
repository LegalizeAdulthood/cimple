#include <cimple/version.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>

CIMPLE_INJECT_VERSION_TAG;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
	fprintf(stderr, "Usage: %s path\n", argv[0]);
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

    return 0;
}
