#include <cimple/config.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>
#include <cimple/cimple.h>

using namespace cimple;

const char* arg0;

void process(const char* path)
{
    printf("%s:\n", path);

    // Open library:

    void* handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);

    if (!handle)
    {
        fprintf(stderr, "%s: %s\n", arg0, dlerror());
        return;
    }

    // Get symbol:

    const char SYMBOL[] = "cimple_module";
    Module_Proc module_proc = (Module_Proc)dlsym(handle, SYMBOL);

    if (!module_proc)
    {
        fprintf(stderr, "%s: %s\n", arg0, dlerror());
        dlclose(handle);
        return;
    }

    // Dump information about the module.

    for (const Registration* p = (*module_proc)(); p; p = p->next)
        printf("    provider(%s, %s)\n", p->provider_name, p->meta_class->name);

    return;
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s module-library ...\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++)
        process(argv[i]);

    return 0;
}

