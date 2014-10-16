#include <cimple/version.h>
#include <cimple/cimple.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

using namespace cimple;

/*
ATTN: cimcgi broken for now since it depends on cimple_repository() entry
point.
*/

// Extend this class so we can squeeze in some client data.
struct CIMCGI_Registration : public Registration
{
    CIMCGI_Registration(
        const char* module_name,
        const char* provider_name,
        Provider_Proc provider_proc,
        const Meta_Class* meta_class,
        Registration*& next,
        const String& path_)
        :
        Registration(
            module_name, provider_name, provider_proc, meta_class, next),
        path(path_)
    {
    }

    String path;
};

static const Meta_Class* _find_class(const char* class_name)
{
    const Meta_Class* const* meta_classes = 0;
    size_t num_meta_classes = 0;
    cimple_repository(meta_classes, num_meta_classes);

    for (size_t i = 0; i < num_meta_classes; i++)
    {
        const Meta_Class* mc = meta_classes[i];

        if (strcasecmp(class_name, mc->name) == 0)
            return mc;
    }

    // Not found!
    return 0;
}

static int set_property(
    Instance* instance, const char* name, const char* value)
{
    const Meta_Property* mp = find_property(instance->meta_class, name);

    if (!mp)
        return -1;

    void* field = (char*)instance + mp->offset;

    if (mp->subscript == 0)
    {
        switch (mp->type)
        {
            case BOOLEAN:
                *((boolean*)field) = strcasecmp(value, "true") == 0;
                break;

            case UINT8:
                *((uint8*)field) = atoi(value);
                break;

            case SINT8:
                *((sint8*)field) = atoi(value);
                break;

            case UINT16:
                *((uint16*)field) = atoi(value);
                break;

            case SINT16:
                *((sint16*)field) = atoi(value);
                break;

            case CHAR16:
                *((char16*)field) = atoi(value);
                break;

            case UINT32:
                *((uint32*)field) = atoi(value);
                break;

            case SINT32:
                *((sint32*)field) = atoi(value);
                break;

            case UINT64:
                *((uint64*)field) = atoll(value);
                break;

            case SINT64:
                *((sint64*)field) = atoll(value);
                break;

            case REAL32:
                *((real32*)field) = atof(value);
                break;

            case REAL64:
                *((real64*)field) = atof(value);
                break;

            case STRING:
                *((String*)field) = value;
                break;

            case DATETIME:
                ((Datetime*)field)->set(value);
                break;
        }
    }
    else
    {
        // ATTN! implement this!
    }

    return 0;
}

static Enum_Instances_Status _enum_instances(
    const CIMCGI_Registration* registration,
    const Instance* model,
    Enum_Instances_Proc proc,
    void* client_data)
{
    // Open pipe to CGI program:

    FILE* os = popen(registration->path.c_str(), "r");

    if (!os)
    {
        fprintf(stderr, "OOPS1\n");
        return ENUM_INSTANCES_FAILED;
    }

    // Convert to CIMPLE instance.

    char buffer[1024];

    Instance* instance = create(registration->meta_class);

    while (fgets(buffer, sizeof(buffer), os) != NULL)
    {
        // Remove trailing newline:

        size_t length = strlen(buffer);

        if (length && buffer[length-1] == '\n')
            buffer[length-1] = '\0';

        // Deliver instance when blank line encountered.

        if (*buffer == '\0')
        {
            proc(instance, ENUM_INSTANCES_OK, client_data);
            instance = create(registration->meta_class);
        }
        else
        {
            char* eq = strchr(buffer, '=');

            if (!eq)
                continue;

            *eq = '\0';

            const char* name = buffer;
            const char* value = eq + 1;

            set_property(instance, name, value);
        }
    }

    // Destroy left-over instance.

    if (instance)
        destroy(instance);

    // Close pipe:

    pclose(os);

    return ENUM_INSTANCES_OK;
}

static int _provider_proc(
    const Registration* registration_,
    int operation,
    void* arg0,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    const CIMCGI_Registration* registration
        = (CIMCGI_Registration*)registration_;

    switch (operation)
    {
        case OPERATION_GET_META_CLASS:
        {
            *((Meta_Class**)arg0) = (Meta_Class*)registration->meta_class;
            return GET_META_CLASS_OK;
        }

        case OPERATION_CREATE_PROVIDER:
            return CREATE_PROVIDER_OK;

        case OPERATION_DESTROY_PROVIDER:
            return DESTROY_PROVIDER_OK;

        case OPERATION_LOAD:
            return LOAD_OK;

        case OPERATION_UNLOAD:
            return UNLOAD_OK;

        case OPERATION_GET_REPOSITORY:
        {
            const Meta_Class* const** meta_classes =
                (const Meta_Class* const**)arg0;

            size_t* num_meta_classes = (size_t*)arg1;

            cimple_repository(*meta_classes, *num_meta_classes);
            return GET_REPOSITORY_OK;
        }

        case OPERATION_GET_INSTANCE:
            return GET_INSTANCE_UNSUPPORTED;

        case OPERATION_ENUM_INSTANCES:
        {
            void* provider = (void*)arg0;
            const Instance* model = (const Instance*)arg1;
            Enum_Instances_Proc proc = (Enum_Instances_Proc)arg2;
            void* client_data = (void*)arg3;

            Enum_Instances_Status status =
                _enum_instances(registration, model, proc, client_data);
            proc((Instance*)0, status, client_data);

            return status;
        }

        case OPERATION_CREATE_INSTANCE:
            return CREATE_INSTANCE_UNSUPPORTED;

        case OPERATION_DELETE_INSTANCE:
            return DELETE_INSTANCE_UNSUPPORTED;

        case OPERATION_MODIFY_INSTANCE:
            return MODIFY_INSTANCE_UNSUPPORTED;

        default:
            return -1;
    }
}

extern "C" Registration* cimple_module()
{
    static Registration* _cimple_registration = 0;

    if (_cimple_registration)
        return _cimple_registration;

    // Open the $CIMCGI directory.

    const char* cimcgi_home = getenv("CIMCGI");

    if (!cimcgi_home)
        return 0;

    DIR* dir = opendir(cimcgi_home);

    if (!dir)
        return 0;

    // Create a registration for each of the providers found in this
    // directory.

    for (dirent* ent = readdir(dir); ent; ent = readdir(dir))
    {
        String name = ent->d_name;

        // Skip current and parent directory.

        if (name == "." || name == "..")
            continue;

        // Build full path name.

        String path(cimcgi_home, "/", name.c_str());
        // Skip directories.

        struct stat st;

        if (stat(path.c_str(), &st) != 0)
            continue;

        if (S_ISDIR(st.st_mode))
            continue;

        // Extract the class name from file name and find it in the repository.

        String class_name = cspn(name, ".");

        const Meta_Class* meta_class = _find_class(class_name.c_str());

        if (!meta_class)
            continue;

        // Create registration for this class.

        String provider_name = cat(class_name, "_Provider");

        Registration* reg = new CIMCGI_Registration(
            "CIMPLE_CIMCGI_Module",
            (const char*)strdup(provider_name.c_str()),
            _provider_proc,
            meta_class,
            _cimple_registration,
            path);
    }

    closedir(dir);

    return _cimple_registration;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimcgi/module.cpp,v 1.7 2007/03/07 20:18:51 mbrasher-public Exp $");
