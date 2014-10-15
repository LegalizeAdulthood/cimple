#include <cimple/version.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>
#include <cimple/cimple.h>
#include <disp/Module.h>

using namespace cimple;

const char* arg0;

int process(const char* path)
{
    printf("%s:\n", path);

    // Open library:

    void* handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);

    if (!handle)
    {
	fprintf(stderr, "%s: %s\n", arg0, dlerror());
	exit(1);
    }

    // Get symbol:

    const char SYMBOL[] = "cimple_module";
    Module_Proc module_proc = (Module_Proc)dlsym(handle, SYMBOL);

    if (!module_proc)
    {
	fprintf(stderr, "%s: %s\n", arg0, dlerror());
	exit(1);
    }

    // Create the module:

    Module* module = new Module(handle, module_proc);
    module->dump();

    return 0;
}

CIMPLE_INJECT_VERSION_TAG;

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
