#include <cimple/version.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstdio>
#include <cimple/cimple.h>
#include <cimple/Array.h>
#include <disp/Dispatcher.h>

using namespace cimple;

const char* arg0;

void draw_full_line()
{
    for (size_t i = 0; i < 80; i++)
        putchar('#');

    putchar('\n');
}

void draw_blank_line()
{
    putchar('#');
    putchar('#');
    putchar('\n');
}

void draw_box(const char* message)
{
    draw_full_line();
    draw_blank_line();

    printf("## %s\n", message);

    draw_blank_line();
    draw_full_line();
}

static bool _enum_instances_proc(
    Instance* instance, 
    Enum_Instances_Status status,
    void* client_data)
{
    if (!instance)
        return false;

    print(instance);

    Array<Instance*>* instances = (Array<Instance*>*)client_data;
    instances->append(instance);

    // Keep them coming!
    return true;
}

void enum_instances(
    Dispatcher* disp,
    const Meta_Class* meta_class,
    Array<Instance*>& instances)
{
    instances.clear();

    Instance* model = create(meta_class);

    Status status = disp->enum_instances(
        model, _enum_instances_proc, &instances);

    if (status != STATUS_OK)
        CIMPLE_ASSERT_STATUS(status);

    printf("Enumerated %u instances\n", uint32(instances.size()));
}

void get_instances(
    Dispatcher* disp,
    const Meta_Class* meta_class,
    Array<Instance*>& instances)
{
    size_t count = 0;

    for (size_t i = 0; i < instances.size(); i++)
    {
        Instance* inst = 0;
        Status status = disp->get_instance(instances[i], inst);

        CIMPLE_ASSERT_STATUS(status);
        CIMPLE_ASSERT(inst != 0);

        if (!identical(inst, instances[i]))
        {
            fprintf(stderr, "ERROR: %s: get_instance() failed to obtain the "
                "same instance produced by enum_instance()", arg0);
            exit(1);
        }

        print(inst);
        destroy(inst);
        count++;
    }

    printf("Got %u instances\n", uint32(count));
}

void delete_instances(
    Dispatcher* disp,
    const Meta_Class* meta_class,
    Array<Instance*>& instances)
{
    // Delete all the instances.

    size_t count = 0;

    for (size_t i = 0; i < instances.size(); i++)
    {
        Instance* inst = key_clone(instances[i]);
        de_nullify_properties(inst);

        Status status = disp->delete_instance(inst);

        if (status == STATUS_UNSUPPORTED)
        {
            printf("delete_instance() unsupported\n");
            return;
        }

        CIMPLE_ASSERT_STATUS(status);

        count++;

        destroy(inst);
    }

    // Be sure they are gone.

    Array<Instance*> tmp;
    enum_instances(disp, meta_class, tmp);
    assert(tmp.size() == 0);

    printf("Deleted %u instances\n", uint32(count));
}

void create_instances(
    Dispatcher* disp,
    const Meta_Class* meta_class,
    Array<Instance*>& instances)
{
    // Create all the instances.

    size_t count = 0;

    for (size_t i = 0; i < instances.size(); i++)
    {
        Instance* inst = clone(instances[i]);
        de_nullify_properties(inst);

        Status status = disp->create_instance(inst);

        if (status == STATUS_UNSUPPORTED)
        {
            printf("create_instance() unsupported\n");
            return;
        }

        CIMPLE_ASSERT_STATUS(status);

        count++;

        destroy(inst);
    }

    // Be sure they were created.

    get_instances(disp, meta_class, instances);

    printf("Created %u instances\n", uint32(count));
}

void modify_instances(
    Dispatcher* disp,
    const Meta_Class* meta_class,
    Array<Instance*>& instances)
{
    // Create all the instances.

    size_t count = 0;

    for (size_t i = 0; i < instances.size(); i++)
    {
        Instance* inst = clone(instances[i]);
        de_nullify_properties(inst);

        Status status = disp->modify_instance(inst);

        if (status == STATUS_UNSUPPORTED)
        {
            printf("create_instance() unsupported\n");
            return;
        }

        CIMPLE_ASSERT_STATUS(status);

        count++;

        destroy(inst);
    }

    // We didn't really change them but be sure they have not changed.

    get_instances(disp, meta_class, instances);

    printf("Modified %u instances\n", uint32(count));
}

void process(const char* path, const char* class_name)
{
    // Create the dispatcher:

    Dispatcher* disp = Dispatcher::create(path);

    if (!disp)
    {
        fprintf(stderr, "%s: error in directory: %s: %s\n", arg0, path,
            Error::get());
        exit(1);
    }

    if (disp->num_modules() == 0)
    {
        fprintf(stderr, "%s: no modules found in this directory: %s\n", 
            arg0, path);
        exit(1);
    }

    // Find the meta class:

    const Meta_Class* meta_class = disp->get_meta_class(class_name);

    if (!meta_class)
    {
        fprintf(stderr, "%s: failed to find provider for class: %s\n", 
            arg0, class_name);
        exit(1);
    }

    // Enumerate all instances in the provider.

    draw_box("enum_instances()");
    Array<Instance*> instances;
    enum_instances(disp, meta_class, instances);

    // Get each instance found in the enum_instance() operation above.

    draw_box("get_instances()");
    get_instances(disp, meta_class, instances);

    // Delete all the instances:

    draw_box("delete_instances()");
    delete_instances(disp, meta_class, instances);

    // Create all the instances again:

    draw_box("create_instances()");
    create_instances(disp, meta_class, instances);

    // Modify all the instances.

    draw_box("modify_instances()");
    modify_instances(disp, meta_class, instances);
}

CIMPLE_INJECT_VERSION_TAG;

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s path class\n", argv[0]);
        exit(1);
    }

    process(argv[1], argv[2]);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/testprov/main.cpp,v 1.21 2007/03/07 18:48:55 mbrasher-public Exp $");
