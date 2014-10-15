#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>

void __libcimpleprovmgr();

int main(int argc, char** argv)
{
    //// Check usage

    if (argc != 2)
    {
	fprintf(stderr, "Usage: %s library-path\n", argv[0]);
	exit(1);
    }

    //// Load library

    void* handle = dlopen(argv[1], RTLD_NOW | RTLD_GLOBAL);
    assert(handle != 0);

    /// Load symbol:

    void* sym = dlsym(handle, "PegasusCreateProviderManager");
    assert(sym);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    __libcimpleprovmgr();

    return 0;
}
