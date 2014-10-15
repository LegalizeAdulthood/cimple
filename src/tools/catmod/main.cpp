#include <cimple/cimple.h>
#include <cimple/Provider_Handle.h>
#include <string>
#include <util/util.h>
#include <dlfcn.h>

using namespace std;
using namespace cimple;

//------------------------------------------------------------------------------
//
// load_module()
//
//------------------------------------------------------------------------------

cimple::Registration* load_module(
    const string& path,
    const cimple::Meta_Class* const*& meta_classes,
    size_t& num_meta_classes,
    void*& handle)
{
    // Open library:

    handle = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!handle)
        err("cannot load library: %s: %s", path.c_str(), dlerror());

    // Get symbol:

    const char SYMBOL[] = "cimple_module";
    cimple::Module_Proc module_proc = 
        (cimple::Module_Proc)dlsym(handle, SYMBOL);

    if (!module_proc)
    {
        err("cannot find symbol \"%s\" in library %s: %s", 
            SYMBOL, path.c_str(), dlerror());
    }

    // Call proc:

    cimple::Registration* reg = module_proc();

    // Get the meta-repository

    cimple::Provider_Handle prov_handle(reg);

    const cimple::Meta_Repository* mr = 0;
    cimple::Get_Repository_Status status = prov_handle.get_repository(mr);

    if (mr == 0)
    {
        err("Provider is missing meta class repository. This probably means "
            "the -r option was not used when the provider class was generated "
            "with genclass. Try \"genclass -r <class-name>\" and remember to "
            "link in the repository.cpp that it generates.");
    }

    meta_classes = mr->meta_classes;
    num_meta_classes = mr->num_meta_classes;

    return reg;
}

int main(int argc, char** argv)
{
    set_arg0(argv[0]);

    // Check arguments.

    if (argc != 2)
    {
        fprintf(stderr, "\nUsage: %s PROVIDER-MODULE-LIBRARY\n\n", argv[0]);
        exit(1);
    }

    // Get information from provider.

    const cimple::Meta_Class* const* meta_classes;
    size_t num_meta_classes;
    void* handle;

    cimple::Registration* module = load_module(
        argv[1], meta_classes, num_meta_classes, handle);

    // If no modules in this library.

    if (!module)
        err("module contains no providers: %s", argv[1]);

    // Print out registration information:

    printf("\n=== Providers:\n");

    for (cimple::Registration* p = module; p; p = p->next)
    {
        const char* pt = "instance";

        if (p->meta_class->flags & CIMPLE_FLAG_ASSOCIATION)
        {
            pt = "association";
        }
        else if (p->meta_class->flags & CIMPLE_FLAG_INDICATION)
        {
            pt = "indication";
        }

        printf("    [%s:%s:%s:%s]\n",
            p->module_name, p->provider_name, pt, p->meta_class->name);
    }

    printf("\n=== Entry points:\n");

    if (dlsym(handle, "PegasusCreateProvider"))
    {
        printf("    PegasusCreateProvider()\n");
    }

    for (cimple::Registration* p = module; p; p = p->next)
    {
        const char* pt = "Instance";
        const char* cn = p->meta_class->name;
        const char* pn = p->provider_name;

        if (p->meta_class->flags & CIMPLE_FLAG_ASSOCIATION)
        {
            pt = "Association";
        }
        else if (p->meta_class->flags & CIMPLE_FLAG_INDICATION)
        {
            pt = "Indication";
        }

        {
            char buffer[1024];
            sprintf(buffer, "%s_Create_%sMI", pn, pt);

            if (dlsym(handle, buffer))
                printf("    %s()\n", buffer);

            sprintf(buffer, "%s_Create_MethodMI", pn);

            if (dlsym(handle, buffer))
                printf("    %s()\n", buffer);
        }
    }

    for (cimple::Registration* p = module; p; p = p->next)
    {
        const char* pt = "Instance";
        const char* cn = p->meta_class->name;
        const char* pn = p->provider_name;

        if (p->meta_class->flags & CIMPLE_FLAG_ASSOCIATION)
        {
            pt = "Association";
        }
        else if (p->meta_class->flags & CIMPLE_FLAG_INDICATION)
        {
            pt = "Indication";
        }

        {
            char buffer[1024];
            sprintf(buffer, "%s_Create_%sMI", cn, pt);

            if (dlsym(handle, buffer))
                printf("    %s()\n", buffer);

            sprintf(buffer, "%s_Create_MethodMI", cn);

            if (dlsym(handle, buffer))
                printf("    %s()\n", buffer);
        }
    }

    printf("\n");

    return 0;
}
