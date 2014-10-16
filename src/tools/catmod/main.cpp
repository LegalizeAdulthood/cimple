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
        fprintf(stderr, "\nUsage: %s PROVIDER-MODULE-LIBRARY\n", argv[0]);
        fprintf(stderr, "Example:\n    catmod libcimpleLamp.so\n\n");
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
