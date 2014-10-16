/*
**==============================================================================
**
** Copyright (c) 2003 - 2009, Michael Brasher, Karl Schopmeyer
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
#include <cimple/config.h>
#include <pegasus/utils/pegasus.h>
#include <Pegasus/Client/CIMClient.h>
#include <string>
#include <sys/types.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <getopt.h>
#include <cstdarg>
#include <vector>
#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <cimple/cimple.h>
#include <cimple/Provider_Handle.h>
#include <pegasus/utils/Str.h>
#include <util/util.h>
#include "usage.h"

#define REGISTRATION_NAMESPACE "root/PG_InterOp"
#define DEFAULT_PROVIDING_NAMESPACE "root/cimv2"

#define INCOMPATIBLE \
    "provider class not compatible with same class in Pegasus repository: %s. "

using namespace std;
using namespace Pegasus;

const char NO_EMBEDDED_INSTANCES[] =
    "Encountered usage of embedded instances "
    "but CIMPLE not configured with --enable-embedded-instances";

enum UserContext
{
    USER_CONTEXT_REQUESTOR = 2,
    USER_CONTEXT_DESIGNATED = 3,
    USER_CONTEXT_PRIVILEGED = 4,
    USER_CONTEXT_CIMSERVER = 5,
};

static const cimple::Meta_Class* const* _meta_classes = 0;
static size_t _num_meta_classes = 0;

void create_class(
    CIMClient& client,
    const String& ns,
    const cimple::Meta_Class* mc);

void check_class_compatibility(
    CIMClient& client,
    const String& ns,
    const cimple::Meta_Class* mc,
    CIMClass& c);

//------------------------------------------------------------------------------
//
// Options:
//
//------------------------------------------------------------------------------

bool class_opt = false;
bool verbose_opt = false;
bool subclass_opt = false;
bool dump_opt = false;
bool help_opt = false;
bool cmpi_opt = false;
bool pegasus_cxx_opt = false;
bool unregister_opt = false;
bool indirect_opt = false;
Array<String> providing_namespaces;
bool absolute_opt = false;
string user_opt;

//------------------------------------------------------------------------------
//
// g_handle
//
//------------------------------------------------------------------------------

void* g_handle = 0;

//------------------------------------------------------------------------------
//
// print()
//
//------------------------------------------------------------------------------

static void _print_elem(const String& x)
{
    cout << '"' << x << '"';
}

static void _print_elem(Uint16 x)
{
    cout << x;
}

template<class T>
static void _print_value(const CIMValue& v, T*)
{
    if (v.isNull())
    {
        cout << "NULL;";
        return;
    }

    if (v.isArray())
    {
        Array<T> x;
        v.get(x);

        cout << "{";

        for (Uint32 i = 0; i < x.size(); i++)
        {
            _print_elem(x[i]);

            if (i + 1 != x.size())
                cout << ", ";
        }

        cout << "};";
    }
    else
    {
        T x;
        v.get(x);
        _print_elem(x);
        cout << ';';
    }
}

void print(CIMInstance& inst)
{
    cout << "instance of " << inst.getClassName().getString() << endl;
    cout << "{" << endl;

    for (Uint32 i = 0; i < inst.getPropertyCount(); i++)
    {
        CIMProperty prop = inst.getProperty(i);

        // Output the name:

        cout << "    " << prop.getName().getString() << " = ";

        const CIMValue& v = prop.getValue();

        switch (prop.getType())
        {
            case CIMTYPE_STRING:
                _print_value(v, (String*)0);
                break;

            case CIMTYPE_UINT16:
                _print_value(v, (Uint16*)0);
                break;

            default:
                ;
        }

        cout << endl;
    }

    cout << "};\n" << endl;
}

int delete_instance(
    CIMClient& client,
    const char* name_space,
    const char* object_path)
{
    try
    {
        if (verbose_opt)
            printf("delete_instance(%s, %s)\n", name_space, object_path);

        client.deleteInstance(name_space, CIMObjectPath(object_path));

        if (verbose_opt)
            printf("delete_instance(%s, %s): okay\n", name_space, object_path);

        return 0;
    }
    catch (CIMException& e)
    {
        if (verbose_opt)
        {
            printf("delete_instance(%s, %s): error: %s\n",
                name_space, object_path, *cimple::Str(e));
        }

        return -1;
    }
    catch (Exception& e)
    {
        if (verbose_opt)
        {
            printf("delete_instance(%s, %s): error: %s\n",
                name_space, object_path, *cimple::Str(e));
        }

        return -1;
    }
    catch (...)
    {
        if (verbose_opt)
        {
            printf("delete_instance(%s, %s): error: unknown exception\n",
                name_space, object_path);
        }

        return -1;
    }

    // Unreachable!
    return -1;
}

int get_instance(
    CIMClient& client,
    const char* name_space,
    const char* object_path,
    CIMInstance& ci)
{
    try
    {
        if (verbose_opt)
            printf("get_instance(%s, %s)\n", name_space, object_path);

        ci = client.getInstance(name_space, CIMObjectPath(object_path));

        if (verbose_opt)
            printf("get_instance(%s, %s): okay\n", name_space, object_path);

        return 0;
    }
    catch (CIMException& e)
    {
        if (verbose_opt)
        {
            printf("get_instance(%s, %s): error: %s\n",
                name_space, object_path, *cimple::Str(e));
        }

        return -1;
    }
    catch (Exception& e)
    {
        if (verbose_opt)
        {
            printf("get_instance(%s, %s): error: %s\n",
                name_space, object_path, *cimple::Str(e));
        }

        return -1;
    }
    catch (...)
    {
        if (verbose_opt)
        {
            printf("get_instance(%s, %s): error: unknown exception\n",
                name_space, object_path);
        }

        return -1;
    }

    // Unreachable!
    return -1;
}

int create_instance(
    CIMClient& client,
    const char* name_space,
    CIMInstance& ci)
{
    CString cstr = ci.getPath().toString().getCString();
    const char* object_path = cstr;

    try
    {
        if (verbose_opt)
            printf("create_instance(%s, %s)\n", name_space, object_path);

        client.createInstance(name_space, ci);

        if (verbose_opt)
            printf("create_instance(%s, %s): okay\n", name_space, object_path);

        return 0;
    }
    catch (CIMException& e)
    {
        if (verbose_opt)
        {
            printf("create_instance(%s, %s): error: %s\n",
                name_space, object_path, *cimple::Str(e));
        }

        return -1;
    }
    catch (Exception& e)
    {
        if (verbose_opt)
        {
            printf("create_instance(%s, %s): error: %s\n",
                name_space, object_path, *cimple::Str(e));
        }

        return -1;
    }
    catch (...)
    {
        if (verbose_opt)
        {
            printf("create_instance(%s, %s): error: unknown exception\n",
                name_space, object_path);
        }

        return -1;
    }

    // Unreachable!
    return -1;
}

//------------------------------------------------------------------------------
//
// load_file()
//
//------------------------------------------------------------------------------

int load_file(const char* path, string& s)
{
    FILE* is = fopen(path, "rb");

    if (!is)
        return -1;

    s.erase(s.begin(), s.end());
    int c;

    while ((c = fgetc(is)) != EOF)
        s += c;

    fclose(is);
    return 0;
}

//------------------------------------------------------------------------------
//
// load_module()
//
//------------------------------------------------------------------------------

cimple::Registration* load_module(
    const string& path,
    const cimple::Meta_Class* const*& meta_classes,
    size_t& num_meta_classes)
{
    // Open library:

    g_handle = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!g_handle)
        err("cannot load library: %s: %s", path.c_str(), dlerror());

    // Figure out which adapter is being used (pegasus or cmpi).

    if (dlsym(g_handle, "PegasusCreateProvider"))
    {
        pegasus_cxx_opt = true;

        if (!dump_opt)
            printf("Using Pegasus C++ provider interface\n");

        if (!dlsym(g_handle, "PegasusCreateProvider"))
            err("missing PegasusCreateProvider() entry point: %s: %s",
                path.c_str(), dlerror());
    }
    else
    {
        cmpi_opt = true;

        if (!dump_opt)
            printf("Using CMPI provider interface\n");
    }

    // Get symbol:

    const char SYMBOL[] = "cimple_module";
    cimple::Module_Proc module_proc =
        (cimple::Module_Proc)dlsym(g_handle, SYMBOL);

    if (!module_proc)
    {
        err("cannot find symbol \"%s\" in library %s: %s",
            SYMBOL, path.c_str(), dlerror());
    }

    // Call proc:

    cimple::Registration* reg = module_proc();

    // Get the meta-repository

    cimple::Provider_Handle handle(reg);

    const cimple::Meta_Repository* mr = 0;
    cimple::Get_Repository_Status status = handle.get_repository(mr);

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

//------------------------------------------------------------------------------
//
// unregister_provider()
//
//------------------------------------------------------------------------------

void delete_capabilities(
    CIMClient& client,
    const string& module_name,
    const string& provider_name,
    const string& class_name)
{
    char buf[1024];
    sprintf(buf,
        "PG_ProviderCapabilities."
        "ProviderName=\"%s\","
        "ProviderModuleName=\"%s\","
        "CapabilityID=\"%s\"",
        provider_name.c_str(),
        module_name.c_str(),
        class_name.c_str());

    if (!dump_opt)
    {
        delete_instance(client, REGISTRATION_NAMESPACE, buf);
    }
}

void unregister_provider(
    CIMClient& client,
    const string& module_name,
    const string& provider_name,
    const string& class_name,
    const cimple::Meta_Class* meta_class)
{
    if (verbose_opt)
        printf("=== Deleting provider registration instances\n");

    String cn = class_name.c_str();

    // Delete the PG_Provider instance.

    try
    {
        char buf[1024];
        sprintf(buf,
            "PG_Provider.Name=\"%s\","
            "ProviderModuleName=\"%s\"",
            provider_name.c_str(),
            module_name.c_str());

        if (!dump_opt)
        {
            delete_instance(client, REGISTRATION_NAMESPACE, buf);
        }
    }
    catch (...)
    {
#ifdef TRACE
        fprintf(stderr, "ignored: %d\n", __LINE__);
#endif
    }

    // Delete the PG_ProviderCapabilities instance.

    try
    {
        if (subclass_opt)
        {
            for (size_t i = 0; i < _num_meta_classes; i++)
            {
                if (cimple::is_subclass(meta_class, _meta_classes[i]))
                {
                    delete_capabilities(
                        client,
                        module_name,
                        provider_name,
                        _meta_classes[i]->name);
                }
            }
        }
        else
        {
            delete_capabilities(
                client,
                module_name,
                provider_name,
                class_name);
        }
    }
    catch (...)
    {
#ifdef TRACE
        fprintf(stderr, "ignored: %d\n", __LINE__);
#endif
    }
}

//------------------------------------------------------------------------------
//
// unregister_module()
//
//------------------------------------------------------------------------------

void unregister_module(
    CIMClient& client,
    const string& module_name)
{
    if (verbose_opt)
        printf("=== Deleting provider module instance\n");

    // Delete the PG_ProviderModule instance.

    try
    {
        char buf[1024];
        sprintf(buf, "PG_ProviderModule.Name=\"%s\"", module_name.c_str());


        if (!dump_opt)
        {
            delete_instance(client, REGISTRATION_NAMESPACE, buf);
        }
    }
    catch (...)
    {
#ifdef TRACE
        fprintf(stderr, "ignored: %d\n", __LINE__);
#endif
    }
}

//------------------------------------------------------------------------------
//
// get_PG_ProviderModule()
//
//------------------------------------------------------------------------------

int get_PG_ProviderModule(
    CIMClient& client,
    const string& module_name,
    CIMInstance& ci)
{
    char buf[1024];
    sprintf(buf, "PG_ProviderModule.Name=\"%s\"", module_name.c_str());

    return get_instance(client, REGISTRATION_NAMESPACE, buf, ci);
}

//------------------------------------------------------------------------------
//
// _isValidUser()
//
//------------------------------------------------------------------------------

bool _isValidUser(const string& user)
{
    // ATTN: eventually implement this on Linux and Windows.
    return true;
}

//------------------------------------------------------------------------------
//
// make_PG_ProviderModule()
//
//------------------------------------------------------------------------------

CIMInstance make_PG_ProviderModule(
    const string& module_name,
    const string& location)
{
    CIMInstance i("PG_ProviderModule");

    i.addProperty(CIMProperty("Name", String(module_name.c_str())));
    i.addProperty(CIMProperty("Vendor", String("Pegasus")));

    String version;
    String interface_version;

    if (cmpi_opt)
    {
        version = "2.0.0";
        interface_version = "2.0.0";
    }
    else
    {
        version = "2.5.0";
        interface_version = "2.5.0";
    }

    i.addProperty(CIMProperty("Version", version));

    if (cmpi_opt)
    {
        i.addProperty(CIMProperty("InterfaceType", String("CMPI")));
    }
    else if (pegasus_cxx_opt)
    {
        i.addProperty(CIMProperty(
            "InterfaceType", String("C++Default")));
    }
    else
        i.addProperty(CIMProperty("InterfaceType", String("CIMPLE")));

    i.addProperty(CIMProperty("InterfaceVersion", interface_version));
    i.addProperty(CIMProperty("Location", String(location.c_str())));

    // Inject UserContext if any.

    if (user_opt.size())
    {
        // PG_ProviderModule.UserContext:

        Uint16 userContext;

        if (user_opt == "@requestor")
            userContext = USER_CONTEXT_REQUESTOR;
        else if (user_opt == "@privileged")
            userContext = USER_CONTEXT_PRIVILEGED;
        else if (user_opt == "@cimserver")
            userContext = USER_CONTEXT_CIMSERVER;
        else
            userContext = USER_CONTEXT_DESIGNATED;

        i.addProperty(CIMProperty("UserContext", userContext));

        // PG_ProviderModule.DesignatedUserContext:

        if (userContext == USER_CONTEXT_DESIGNATED)
        {
            if (!_isValidUser(user_opt))
            {
                err("user given by -U not a valid system user: %s\n",
                    user_opt.c_str());
            }

            String designatedUserContext = user_opt.c_str();
            i.addProperty(
                CIMProperty("DesignatedUserContext",
                    designatedUserContext));
        }
    }

    return i;
}

//------------------------------------------------------------------------------
//
// compatible_modules()
//
//------------------------------------------------------------------------------

int compatible_property(CIMInstance& x, CIMInstance& y, const String& name)
{
    // Find xp:

    CIMProperty xp;

    try
    {
        xp = x.getProperty(x.findProperty(name));
    }
    catch(...)
    {
        return -1;
    }

    // Find yp:

    CIMProperty yp;

    try
    {
        yp = y.getProperty(y.findProperty(name));
    }
    catch(...)
    {
        return -1;
    }

    if (yp.getName() != xp.getName())
        return -1;

    if (yp.getValue() != xp.getValue())
        return -1;

    return 0;
}

int compatible_modules(CIMInstance& x, CIMInstance& y)
{
    if (compatible_property(x, y, "Name") != 0)
        return -1;

    if (compatible_property(x, y, "Vendor") != 0)
        return -1;

    if (compatible_property(x, y, "Version") != 0)
        return -1;

    if (compatible_property(x, y, "InterfaceType") != 0)
        return -1;

    if (compatible_property(x, y, "InterfaceVersion") != 0)
        return -1;

    if (compatible_property(x, y, "Location") != 0)
        return -1;

    if (user_opt.size())
    {
        if (compatible_property(x, y, "UserContext") != 0)
            return -1;

        if (user_opt != "@requestor" &&
            user_opt != "@privileged" &&
            user_opt != "@cimserver" &&
            compatible_property(x, y, "DesignatedUserContext") != 0)
        {
            return -1;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
//
// register_module()
//
//------------------------------------------------------------------------------

void register_module(
    const char* lib_path,
    const string& short_lib_name,
    const string& module_name)
{
    if (verbose_opt)
        printf("=== Creating PG_ProviderModule\n");

    // Connect to client.

    try
    {
        // Remove old registration instance.

        CIMClient client;

        try
        {
            client.connectLocal();
        }
        catch (...)
        {
            err("failed to connect to local CIM server");
        }

        string location;

        if (absolute_opt)
            location = lib_path;
        else
            location = short_lib_name;

        // Make instance of PG_ProviderModule.

        CIMInstance pmi = make_PG_ProviderModule(module_name, location);

        // If unregister option, unregister module and return now.

        if (unregister_opt)
        {
            unregister_module(client, module_name);
            return;
        }

        // Modify or create PG_ProviderModule instance.

        CIMInstance tci;

        if (get_PG_ProviderModule(client, module_name, tci) == 0)
        {
            if (dump_opt)
                print(pmi);
            else if (compatible_modules(pmi, tci) == 0)
            {
                if (verbose_opt)
                    printf("=== Using existing provider module instance\n");
            }
            else
            {
                unregister_module(client, module_name);

                {
                    if (verbose_opt)
                        printf("=== Creating PG_ProviderModule instance\n");

                    client.createInstance(REGISTRATION_NAMESPACE, pmi);

                    if (verbose_opt)
                        printf("=== Created PG_ProviderModule instance\n");
                }
            }
        }
        else
        {
            if (dump_opt)
                print(pmi);
            else
            {
                if (verbose_opt)
                    printf("=== Creating provider module instance\n");

                client.createInstance(REGISTRATION_NAMESPACE, pmi);

                if (verbose_opt)
                    printf("=== Created provider module instance\n");
            }
        }
    }
    catch (CIMException& e)
    {
        CString msg = e.getMessage().getCString();
        err("unexpected error: %s", (const char*)msg);
    }
    catch (...)
    {
        err("unexpected error");
    }
}

//------------------------------------------------------------------------------
//
// check_cmpi_entry_point()
//
//------------------------------------------------------------------------------

static void check_cmpi_entry_point(
    const char* provider_name,
    const char* provider_type)
{
    char sym_name[1024];

    sprintf(sym_name, "%s_Create_%sMI", provider_name, provider_type);

    void* sym = dlsym(g_handle, sym_name);

    if (!sym)
        err("missing CMPI entry point: \"%s\"\n", sym_name);

    // printf("check_cmpi_entry_point: %s\n", sym_name);
}

//------------------------------------------------------------------------------
//
// compute_closure()
//
//     Compute the closure with respect to the given class. The output includes
//     all classes reachable from this class (via the superclass, references,
//     or methods).
//
//------------------------------------------------------------------------------

void compute_closure(
    const cimple::Meta_Class* mc,
    vector<string>& closure)
{
    // Ignore if already in list (to prevent recursion).

    for (size_t i = 0; i < closure.size(); i++)
    {
        if (mc->name == closure[i])
            return;
    }

    // Add this class to closure.

    closure.push_back(mc->name);

    // Return now unless -f option was given.

    if (!indirect_opt)
        return;

    // Add super class to closure.

    if (mc->super_meta_class)
        compute_closure(mc->super_meta_class, closure);

    // Add any classes reachable via class features to closure.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const cimple::Meta_Feature* mf = mc->meta_features[i];

        if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;
            compute_closure(mr->meta_class, closure);
        }

        if (mf->flags & CIMPLE_FLAG_METHOD)
        {
            const cimple::Meta_Method* mm = (cimple::Meta_Method*)mf;

            for (size_t j = 0; j < mm->num_meta_features; j++)
            {
                const cimple::Meta_Feature* mf = mm->meta_features[j];

                if (mf->flags & CIMPLE_FLAG_REFERENCE)
                {
                    const cimple::Meta_Reference* mr =
                        (cimple::Meta_Reference*)mf;

                    compute_closure(mr->meta_class, closure);
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
//
// delete_class()
//
//------------------------------------------------------------------------------

void delete_class(
    CIMClient& client,
    const String& ns,
    const string& class_name)
{
    try
    {
        if (!dump_opt)
            client.deleteClass(ns, String(class_name.c_str()));
    }
    catch (...)
    {
        return;
    }

    if (!dump_opt)
        printf("Deleted class %s\n", class_name.c_str());
}

//------------------------------------------------------------------------------
//
// uninstall_classes()
//
//------------------------------------------------------------------------------

void uninstall_classes(
    CIMClient& client,
    const cimple::Meta_Class* meta_class)
{
    // Find closure and remove classes with the same prefix as the one
    // installed by this provider (assuming thre prefix is not "CIM_").

    vector<string> closure;
    compute_closure(meta_class, closure);

    string cn = meta_class->name;
    size_t pos = cn.find('_');
    string prefix;

    if (pos != size_t(-1))
        prefix = cn.substr(0, pos);

    if (prefix != "CIM_")
    {
        for (size_t i = 0; i < closure.size(); i++)
        {
            string tmp = closure[i];

            if (tmp.substr(0, 4) == "CIM_")
                continue;

            if (tmp.substr(0, prefix.size()) != prefix)
                continue;

            for (size_t j = 0; j < providing_namespaces.size(); j++)
            {
                delete_class(client, providing_namespaces[Uint32(j)], tmp);
            }
        }
    }
}

//------------------------------------------------------------------------------
//
// register_provider()
//
//------------------------------------------------------------------------------

static void create_capabilities(
    const string& module_name,
    const string& provider_name,
    const string& class_name,
    const cimple::Meta_Class* meta_class,
    CIMClient& client)
{
    String mn = module_name.c_str();
    String pn = provider_name.c_str();
    String cn = class_name.c_str();

    CIMInstance i("PG_ProviderCapabilities");

    i.addProperty(CIMProperty("CapabilityID", cn));
    i.addProperty(CIMProperty("ProviderModuleName", mn));
    i.addProperty(CIMProperty("ProviderName", pn));
    i.addProperty(CIMProperty("ClassName", cn));
    i.addProperty(CIMProperty("Namespaces", providing_namespaces));

    // Set provider type.

    Pegasus::Array<Uint16> providerType;

    // Register provider as one or more of the following types:
    //     - Instance provider
    //     - Indication provider
    //     - Association provider
    //     - Method provider

    if (meta_class->flags & CIMPLE_FLAG_INDICATION)
    {
        // Indication provider:
        providerType.append(4);

        if (verbose_opt)
            printf("=== Registered as indication provider\n");

        if (cmpi_opt)
            check_cmpi_entry_point(provider_name.c_str(), "Indication");
    }
    else
    {
        // Instance provider.
        providerType.append(2);

        if (verbose_opt)
            printf("=== Registered as instance provider\n");

        if (cmpi_opt)
            check_cmpi_entry_point(provider_name.c_str(), "Instance");
    }

    if (meta_class->flags & CIMPLE_FLAG_ASSOCIATION)
    {
        // Association provider.
        providerType.append(3);

        if (verbose_opt)
            printf("=== Registered as association provider\n");

        if (cmpi_opt)
            check_cmpi_entry_point(
                provider_name.c_str(), "Association");
    }

    if (cimple::has_methods(meta_class))
    {
        // Method provider.
        providerType.append(5);

        if (verbose_opt)
            printf("=== Registered as method provider\n");

        if (cmpi_opt)
            check_cmpi_entry_point(provider_name.c_str(), "Method");
    }


    i.addProperty(CIMProperty("ProviderType", providerType));

    // supportedProperties

    CIMValue supportedProperties;
    supportedProperties.setNullValue(CIMTYPE_STRING, true, 0);
    i.addProperty(
        CIMProperty("supportedProperties", supportedProperties));

    // supportedMethods

    CIMValue supportedMethods;
    supportedMethods.setNullValue(CIMTYPE_STRING, true, 0);
    assert(supportedMethods.isNull());
    i.addProperty(
        CIMProperty("supportedMethods", supportedMethods));

    if (dump_opt)
        print(i);

    if (!dump_opt)
    {
        if (verbose_opt)
            printf("Creating PG_ProviderCapabilities instance\n");

        client.createInstance(REGISTRATION_NAMESPACE, i);

        if (verbose_opt)
            printf("Created PG_ProviderCapabilities instance\n");
    }
}

void register_provider(
    const string& module_name,
    const string& provider_name,
    const cimple::Meta_Class* meta_class)
{
    const string& class_name = meta_class->name;

    // Print message:

    if (!dump_opt)
    {
        if (unregister_opt)
            printf("Unregistering ");
        else
            printf("Registering ");

        printf("%s (class %s)\n", provider_name.c_str(), meta_class->name);
    }

    // Process.

    try
    {
        // Remove old registration instances.

        CIMClient client;

        try
        {
            client.connectLocal();
        }
        catch (...)
        {
            err("failed to connect to local CIM server");
        }

        unregister_provider(
            client, module_name, provider_name, class_name, meta_class);

        if (unregister_opt && class_opt)
            uninstall_classes(client, meta_class);

        // Return if unregister option given.

        if (unregister_opt)
            return;

        if (verbose_opt)
            printf("=== Creating provider registration instances\n");

        // Common definitions.

        String mn = module_name.c_str();
        String pn = provider_name.c_str();
        String cn = class_name.c_str();

        // Create PG_Provider instance.

        {
            CIMInstance i("PG_Provider");

            i.addProperty(CIMProperty("Name", pn));
            i.addProperty(CIMProperty("ProviderModuleName", mn));

            if (dump_opt)
                print(i);

            if (!dump_opt)
            {
                if (verbose_opt)
                    printf("Creating PG_Provider instance\n");

                client.createInstance(REGISTRATION_NAMESPACE, i);

                if (verbose_opt)
                    printf("Created PG_Provider instance\n");
            }
        }

        // Create PG_ProviderCapabilities instance.

        if (subclass_opt)
        {
            // With this option, we register the provider to provide all
            // subclasses of this class.

            for (size_t i = 0; i < _num_meta_classes; i++)
            {
                if (cimple::is_subclass(meta_class, _meta_classes[i]))
                {
                    try
                    {
                        create_capabilities(
                            module_name,
                            provider_name,
                            _meta_classes[i]->name,
                            _meta_classes[i],
                            client);
                    }
                    catch (CIMException& e)
                    {
                        char buf[1024];
                        sprintf(buf,
                            "PG_ProviderCapabilities."
                            "ProviderName=\"%s\","
                            "ProviderModuleName=\"%s\","
                            "CapabilityID=\"%s\"",
                            provider_name.c_str(),
                            module_name.c_str(),
                            _meta_classes[i]->name);
                        CString msg = e.getMessage().getCString();
                        err("registration error: %s: %s",
                            buf, (const char*)msg);
                    }
                }
            }
        }
        else
        {
            // Register provider only to provide the single class.

            try
            {
                create_capabilities(
                    module_name,
                    provider_name,
                    class_name,
                    meta_class,
                    client);
            }
            catch (CIMException& e)
            {
                char buf[1024];
                sprintf(buf,
                    "PG_ProviderCapabilities."
                    "ProviderName=\"%s\","
                    "ProviderModuleName=\"%s\","
                    "CapabilityID=\"%s\"",
                    provider_name.c_str(),
                    module_name.c_str(),
                    class_name.c_str());
                CString msg = e.getMessage().getCString();
                err("registration error: %s: %s", buf, (const char*)msg);
            }
        }
    }
    catch (CIMException& e)
    {
        CString msg = e.getMessage().getCString();
        err("registration error: %s", (const char*)msg);
    }
    catch (...)
    {
        err("registration error");
    }
}

//------------------------------------------------------------------------------
//
// get_class()
//
//------------------------------------------------------------------------------

bool get_class(
    CIMClient& client,
    const String& name_space,
    const char* class_name,
    CIMClass& cim_class)
{
    try
    {
        const bool local_only = false;
        const bool include_qualifiers = true;
        cim_class = client.getClass(
            name_space, class_name, local_only, include_qualifiers);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

//------------------------------------------------------------------------------
//
// check_method_compatibility()
//
//------------------------------------------------------------------------------

void check_method_compatibility(
    CIMClient& client,
    const String& ns,
    const cimple::Meta_Class* mc,
    const cimple::Meta_Method* mm,
    CIMMethod& m)
{
    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
        const cimple::Meta_Feature* mf = mm->meta_features[i];

        if (strcmp(mf->name, "return_value") == 0)
            continue;

        Uint32 pos = m.findParameter(mf->name);

        if (pos == (Uint32)-1)
        {
            warn("Parameter not found in Pegasus repository class: %s.%s",
                mm->name, mf->name);
            continue;
        }

        CIMParameter p = m.getParameter(pos);

        if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
        {
            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

            if (p.getType() != CIMTYPE_STRING && p.getType() != CIMTYPE_OBJECT)
            {
                err(INCOMPATIBLE "Parameters have different types: %s().%s",
                    mc->name, mm->name, mr->name);
            }

            Uint32 pos = p.findQualifier("EmbeddedObject");

            if (pos == (Uint32)-1)
            {
                err(INCOMPATIBLE "Parameters have different types: %s",
                    mc->name, mf->name);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
        {
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES

            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

            if (p.getType() != CIMTYPE_STRING && p.getType() !=CIMTYPE_INSTANCE)
            {
                err(INCOMPATIBLE "Parameters have different types: %s",
                    mc->name, mr->name);
            }

            Uint32 pos = p.findQualifier("EmbeddedInstance");

            if (pos == (Uint32)-1)
            {
                err(INCOMPATIBLE "Missing EmbeddedInstance qualifier: %s",
                    mc->name, mf->name);
            }

            try
            {
                String t;
                p.getQualifier(pos).getValue().get(t);

                if (!cimple::eqi(*cimple::Str(t), mr->meta_class->name))
                {
                    err(INCOMPATIBLE "Embedded class name mismatch on %s",
                        mc->name, mf->name);
                }
            }
            catch (...)
            {
                err(INCOMPATIBLE "Unexpected error: %s",
                    mc->name, mf->name);
            }

#else /* !CIMPLE_ENABLE_EMBEDDED_INSTANCES */

            err(NO_EMBEDDED_INSTANCES);

#endif /* !CIMPLE_ENABLE_EMBEDDED_INSTANCES */
        }
        else if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const cimple::Meta_Property* mp = (const cimple::Meta_Property*)mf;

            if (p.getType() != mp->type)
                err(INCOMPATIBLE "1On this method: %s", mc->name, mm->name);

            if (p.isArray() && mp->subscript == 0)
                err(INCOMPATIBLE "2On this method: %s", mc->name, mm->name);
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

            if (p.getType() != CIMTYPE_REFERENCE)
                err(INCOMPATIBLE "3On this method: %s", mc->name, mm->name);

            String tmp = p.getReferenceClassName().getString();

            if (tmp != mr->meta_class->name)
                err(INCOMPATIBLE "4On this method: %s", mc->name, mm->name);

            // Check compatibility of these reference classes:

            CIMClass cc;

            if (!get_class(client, ns, mr->meta_class->name, cc))
                err("dependent class not found: %s", mr->meta_class->name);

            check_class_compatibility(client, ns, mr->meta_class, cc);
        }
    }
}

//------------------------------------------------------------------------------
//
// check_class_compatibility()
//
//------------------------------------------------------------------------------

void check_class_compatibility(
    CIMClient& client,
    const String& ns,
    const cimple::Meta_Class* mc,
    CIMClass& c)
{
    if (verbose_opt)
        printf("=== Checking class compatibility (%s)\n", mc->name);

    // Check whether they have the same super class.

    if (mc->super_meta_class)
    {
        CString tmp = c.getSuperClassName().getString().getCString();

        if (strcasecmp(mc->super_meta_class->name, tmp) != 0)
        {
            err(INCOMPATIBLE "They have different super classes",
                mc->name);
        }

        CIMClass cc;

        if (!get_class(client, ns, mc->super_meta_class->name, cc))
            err("dependent class not found: %s", mc->super_meta_class->name);

        check_class_compatibility(client, ns, mc->super_meta_class, cc);
    }

    // Check compatibility of each feature.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const cimple::Meta_Feature* mf = mc->meta_features[i];

        // Check only local features:

        if (!mc->locals[i].local)
            continue;

        // If it's a method, process and then short-circuit the remainder.

        if (mf->flags & CIMPLE_FLAG_METHOD)
        {
            Uint32 pos = c.findMethod(mf->name);

            if (pos == (Uint32)-1)
            {
                err(INCOMPATIBLE "Pegasus class has no method called %s",
                    mc->name, mf->name);
            }

            CIMMethod m = c.getMethod(pos);

            const cimple::Meta_Method* mm = (const cimple::Meta_Method*)mf;
            check_method_compatibility(client, ns, mc, mm, m);

            continue;
        }

        // Find corresponding property in Pegasus class.

        Uint32 pos = c.findProperty(mf->name);

        if (pos == (Uint32)-1)
        {
            // ATTN: these are causes by incompatibilities in CIM version.
#if 0
            warn("Warning: feature %s.%s found in CIMPLE meta class but not "
                "in Pegasus repository class", mc->name, mf->name);
#endif
            continue;
        }

        CIMProperty p = c.getProperty(pos);

        // Check feature (object, property, or reference)

        if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
        {
            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

            // Check type.

            if (p.getType() != CIMTYPE_STRING && p.getType() != CIMTYPE_OBJECT)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mr->name);
            }

            // Check EmbeddedObject qualifier:

            Uint32 pos = p.findQualifier("EmbeddedObject");

            if (pos == (Uint32)-1)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mf->name);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
        {
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES

            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

            // Check type.

            if (p.getType() != CIMTYPE_STRING && p.getType() !=CIMTYPE_INSTANCE)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mr->name);
            }

            // Check EmbeddedInstance qualifier:

            Uint32 pos = p.findQualifier("EmbeddedInstance");

            if (pos == (Uint32)-1)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mf->name);
            }

            try
            {
                String t;
                p.getQualifier(pos).getValue().get(t);

                if (!cimple::eqi(*cimple::Str(t), mr->meta_class->name))
                {
                    err(INCOMPATIBLE "Properties have different types: %s",
                        mc->name, mf->name);
                }
            }
            catch (...)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mf->name);
            }
#else /* !CIMPLE_ENABLE_EMBEDDED_INSTANCES */

            err(NO_EMBEDDED_INSTANCES);

#endif /* !CIMPLE_ENABLE_EMBEDDED_INSTANCES */
        }
        else if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const cimple::Meta_Property* mp = (const cimple::Meta_Property*)mf;

            // Check type.

            if (p.getType() != mp->type)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mp->name);
            }

            // Check array info.

            if (p.isArray() && mp->subscript == 0)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mp->name);
            }
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

            // Check type.

            if (p.getType() != CIMTYPE_REFERENCE)
            {
                err(INCOMPATIBLE "Properties have different types: %s",
                    mc->name, mr->name);
            }

            // Check compatibility of these reference classes:

            CIMClass cc;

            if (!get_class(client, ns, mr->meta_class->name, cc))
                err("dependent class not found: %s", mr->meta_class->name);

            check_class_compatibility(client, ns, mr->meta_class, cc);
        }

        if (mf->flags & CIMPLE_FLAG_KEY)
        {
            Uint32 pos = p.findQualifier("key");

            if (pos == (Uint32)-1)
            {
                err(INCOMPATIBLE "Properties are not both keys: %s",
                    mc->name, mf->name);
            }
        }
    }
}

//------------------------------------------------------------------------------
//
// class_exists()
//
//------------------------------------------------------------------------------

bool class_exists(
    const String& name_space,
    CIMClient& client,
    const char* class_name)
{
    try
    {
        const bool local_only = true;
        const bool include_qualifiers = false;
        CIMClass tmp = client.getClass(
            name_space, class_name, local_only, include_qualifiers);

        return true;
    }
    catch (...)
    {
        return false;
    }
}

//------------------------------------------------------------------------------
//
// add_method()
//
//------------------------------------------------------------------------------

void add_method(
    CIMClient& client,
    const String& ns,
    CIMClass& cc,
    const cimple::Meta_Method* mm)
{
    // Create method.

    CIMMethod cm(mm->name, CIMType(mm->return_type));

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
        const cimple::Meta_Feature* mf = mm->meta_features[i];

        // Handle return value up front:

        if (strcmp(mf->name, "return_value") == 0)
        {
            if (mf->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
            {
                assert(mf->flags & CIMPLE_FLAG_REFERENCE);
                const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

                create_class(client, ns, mr->meta_class);
                CIMQualifier q("EmbeddedInstance",String(mr->meta_class->name));
                cm.addQualifier(q);
            }
            else if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            {
                assert(mf->flags & CIMPLE_FLAG_REFERENCE);
                CIMQualifier q("EmbeddedObject", Boolean(true));
                cm.addQualifier(q);
            }
            continue;
        }

        // Now add current parameter:

        CIMParameter cp;

        if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
        {
            assert(mf->flags & CIMPLE_FLAG_REFERENCE);

            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;
            cp = CIMParameter(mf->name, CIMTYPE_STRING);
            cp.addQualifier(CIMQualifier("EmbeddedObject", Boolean(true)));
        }
        else if (mf->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
        {
            assert(mf->flags & CIMPLE_FLAG_REFERENCE);

            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;
            cp = CIMParameter(mf->name, CIMTYPE_STRING);
            create_class(client, ns, mr->meta_class);
            cp.addQualifier(CIMQualifier(
                "EmbeddedInstance", String(mr->meta_class->name)));
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;
            create_class(client, ns, mr->meta_class);

            bool is_array = mr->subscript != 0;

            cp = CIMParameter(
                mr->name, CIMTYPE_REFERENCE, is_array, 0, mr->meta_class->name);
        }
        else if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const cimple::Meta_Property* mp = (const cimple::Meta_Property*)mf;
            Uint32 array_size = mp->subscript > 0 ? mp->subscript : 0;
            bool is_array = mp->subscript != 0;
            cp = CIMParameter(
                mp->name, CIMType(mp->type), is_array, array_size);
        }

        // Fixup in/out qualifiers on new parameter.

        if (mf->flags & CIMPLE_FLAG_IN)
            cp.addQualifier(CIMQualifier("in", Boolean(true)));
        else
            cp.addQualifier(CIMQualifier("in", Boolean(false)));

        if (mf->flags & CIMPLE_FLAG_OUT)
            cp.addQualifier(CIMQualifier("out", Boolean(true)));

        // Add parameter to list:

        cm.addParameter(cp);
    }

    cc.addMethod(cm);
}

//------------------------------------------------------------------------------
//
// create_class()
//
//------------------------------------------------------------------------------

void create_class(
    CIMClient& client,
    const String& ns,
    const cimple::Meta_Class* mc)
{
    if (class_exists(ns, client, mc->name))
        return;

    if (verbose_opt)
        printf("=== Creating class (%s)\n", mc->name);

    if (!dump_opt)
        printf("Creating class %s (%s)\n", mc->name,
            (const char*)ns.getCString());

    // Create superclass if necessary.

    if (mc->super_meta_class)
        create_class(client, ns, mc->super_meta_class);

    // Now create the class itself.

    try
    {
        // Define the class.

        string super_class_name;

        if (mc->super_meta_class)
            super_class_name = mc->super_meta_class->name;

        CIMClass c(mc->name);

        if (super_class_name.size())
            c.setSuperClassName(String(super_class_name.c_str()));

        // Add assocation qualifier?

        if (mc->flags & CIMPLE_FLAG_ASSOCIATION)
            c.addQualifier(CIMQualifier("Association", Boolean(true)));

        // Add assocation qualifier?

        if (mc->flags & CIMPLE_FLAG_INDICATION)
            c.addQualifier(CIMQualifier("Indication", Boolean(true)));

        // Add properties.

        size_t num_keys = 0;

        for (size_t i = 0; i < mc->num_meta_features; i++)
        {
            const cimple::Meta_Feature* mf = mc->meta_features[i];

            if (mf->flags & CIMPLE_FLAG_METHOD)
                continue;

            if (mf->flags & CIMPLE_FLAG_KEY)
                num_keys++;

            // Ignore non-local feature:

            if (!mc->locals[i].local)
                continue;

            if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
            {
                assert(mf->flags & CIMPLE_FLAG_REFERENCE);
                assert(!(mf->flags & CIMPLE_FLAG_KEY));

                CIMValue v(CIMTYPE_STRING, false, 0);
                CIMProperty p(mf->name, v, 0);

                p.addQualifier(CIMQualifier("EmbeddedObject", Boolean(true)));

                c.addProperty(p);
            }
            else if (mf->flags & CIMPLE_FLAG_EMBEDDED_INSTANCE)
            {
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES

                const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

                assert(mf->flags & CIMPLE_FLAG_REFERENCE);
                assert(!(mf->flags & CIMPLE_FLAG_KEY));

                CIMValue v(CIMTYPE_STRING, false, 0);
                CIMProperty p(mf->name, v, 0);

                create_class(client, ns, mr->meta_class);
                p.addQualifier(CIMQualifier(
                    "EmbeddedInstance", String(mr->meta_class->name)));
                c.addProperty(p);

#else /* !CIMPLE_ENABLE_EMBEDDED_INSTANCES */

                err(NO_EMBEDDED_INSTANCES);

#endif /* !CIMPLE_ENABLE_EMBEDDED_INSTANCES */
            }
            else if (mf->flags & CIMPLE_FLAG_PROPERTY)
            {
                const cimple::Meta_Property* mp = (cimple::Meta_Property*)mf;

                CIMValue v(CIMType(mp->type), Boolean(mp->subscript), 0);
                Uint32 array_size = mp->subscript > 0 ? mp->subscript : 0;
                CIMProperty p(mp->name, v, array_size);

                if (mf->flags & CIMPLE_FLAG_KEY)
                    p.addQualifier(CIMQualifier("Key", Boolean(true)));

                c.addProperty(p);
            }
            else if (mf->flags & CIMPLE_FLAG_REFERENCE)
            {
                const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

                CIMValue v(CIMTYPE_REFERENCE, false, 0);
                CIMProperty p(mf->name, v, 0, mr->meta_class->name);

                if (mf->flags & CIMPLE_FLAG_KEY)
                    p.addQualifier(CIMQualifier("Key", Boolean(true)));

                c.addProperty(p);

                create_class(client, ns, mr->meta_class);
            }
        }

        // Add methods to the class.

        for (size_t i = 0; i < mc->num_meta_features; i++)
        {
            const cimple::Meta_Feature* mf = mc->meta_features[i];

            if (mf->flags & CIMPLE_FLAG_METHOD)
                add_method(client, ns, c, (const cimple::Meta_Method*)mf);
        }

        if (!dump_opt)
            client.createClass(ns, c);
    }
    catch (Exception& e)
    {
        CString msg = e.getMessage().getCString();
        err("failed to create class: %s: %s", mc->name, (const char*)msg);
    }
    catch (...)
    {
        err("failed to create class");
    }
}

//------------------------------------------------------------------------------
//
// validate_class()
//
//------------------------------------------------------------------------------

void validate_class(
    const String& ns,
    const cimple::Meta_Class* meta_class)
{
    if (verbose_opt)
        printf("=== Validating the Pegasus class\n");

    // Find the class.

    try
    {
        // Connect to CIM serer.

        CIMClient client;

        try
        {
            client.connectLocal();
        }
        catch (...)
        {
            err("failed to connect to local CIM server");
        }

        // Create class:

        if (class_opt)
        {
            // Create provided class.

            create_class(client, ns, meta_class);

            // Create subclasses if requested.

            if (subclass_opt)
            {
                for (size_t i = 0; i < _num_meta_classes; i++)
                {
                    if (cimple::is_subclass(meta_class, _meta_classes[i]))
                        create_class(client, ns, _meta_classes[i]);
                }
            }
        }

        // Be sure the class exists.

        CIMClass c;

        if (!get_class(client, ns, meta_class->name, c))
        {
            err("The Pegasus repository contains no class called \"%s\". "
                "Please add this class to repository or use the -c option.",
                meta_class->name);
        }

        // Check compatibility between meta-data and Pegasus class.

        check_class_compatibility(client, ns, meta_class, c);
    }
    catch (CIMException& e)
    {
        CString msg = e.getMessage().getCString();
        err("error: %s", (const char*)msg);
    }
    catch (...)
    {
        err("error while validating class");
    }
}

//------------------------------------------------------------------------------
//
// _load_class_deps()
//
//------------------------------------------------------------------------------

static void _load_class_deps(const char* lib_path, vector<string>& class_deps)
{
    // Open the input file.

    FILE* fp = fopen(lib_path, "rb");

    if (!fp)
    {
        err("failed to open %s", lib_path);
        exit(1);
    }

    // Read library into memory.

    char buf[1024];
    vector<char> v;
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
        v.insert(v.end(), buf, buf + n);

    v.push_back('\0');

    // Close the file:

    fclose(fp);

    // Search for tags:

    const char* p = &v[0];
    n = v.size();

    while (n)
    {
        if (n >= 4 && p[0] == '@' && p[1] == '(' && p[2] == '#' && p[3] == ')')
        {
            p += 4;
            string str;

            while (n && *p)
            {
                str += p[0];
                n--;
                p++;
            }

            size_t pos = str.find('=');

            if (pos != string::npos)
            {
                string name = str.substr(0, pos);
                string value = str.substr(pos+1);

                // Skip this in case debugger puts #define macro definitions
                // into debugger info.

                if (value.find("#CLASS;") == string::npos &&
                    name == "CLASS_DEPENDENCY")
                {
                    class_deps.push_back(value);
                }
            }
        }

        n--;
        p++;
    }
}

//------------------------------------------------------------------------------
//
// main()
//
//------------------------------------------------------------------------------

static const char* arg0;

int main(int argc, char** argv)
{
    arg0 = argv[0];

    // Setup arg0 for warn() and err().

    set_arg0(argv[0]);

    // Extract options:

    int opt;

    while ((opt = getopt(argc, argv, "r:dcvhn:uisaU:V")) != -1)
    {
        switch (opt)
        {
            case 's':
                subclass_opt = true;
                break;

            case 'c':
                class_opt = true;
                break;

            case 'v':
                verbose_opt = true;
                break;

            case 'V':
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
                break;

            case 'd':
                dump_opt = true;
                break;

            case 'n':
                providing_namespaces.append(optarg);
                break;

            case 'a':
                absolute_opt = true;
                break;

            case 'h':
                help_opt = true;
                break;

            case 'u':
                unregister_opt = true;
                break;

            case 'i':
                indirect_opt = true;
                break;

            case 'U':
                user_opt = optarg;
                break;

            default:
            {
                err("unknown option: -%c\n", opt);
                break;
            }
        }
    }

    argc -= optind;
    argv += optind;

    // check arguments.

    if (argc < 1 || help_opt)
    {
        fprintf(stderr, (const char*)USAGE, arg0);
        exit(1);
    }

    // If there were no -n (namespace) options, then use default.

    if (providing_namespaces.size() == 0)
        providing_namespaces.append(DEFAULT_PROVIDING_NAMESPACE);

    const char* lib_path = argv[0];

    // Get class dependency list:

    // ATTN: CIMPLE_CLASS_DEPENENCY macro scheme is broken in cross
    // namespace provider case.

    static vector<string> class_deps;
    _load_class_deps(lib_path, class_deps);

    // Get information from provider.

    cimple::Registration* module = load_module(
        lib_path, _meta_classes, _num_meta_classes);

    // If no modules in this library.

    if (!module)
        err("module contains no providers: %s", lib_path);

    // validate CIMPLE classes against Pegasus classes in each namespace.

    if (!unregister_opt && !dump_opt)
    {
        for (cimple::Registration* p = module; p; p = p->next)
        {
            // Skip class if not included in command line class list (if any).

            if (argc > 1)
            {
                bool found = false;

                for (int i = 1; i < argc; i++)
                {
                    if (strcasecmp(p->meta_class->name, argv[i]) == 0)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                    continue;
            }

            for (size_t i = 0; i < providing_namespaces.size(); i++)
            {
                // Validate and CREATE provided class.

                validate_class(providing_namespaces[Uint32(i)], p->meta_class);
            }
        }

        // Create class dependencies:

        for (size_t i = 0; i < providing_namespaces.size(); i++)
        {
            // Create class dependency.

            for (size_t j = 0; j < class_deps.size(); j++)
            {
                const char* class_name = class_deps[j].c_str();

                const cimple::Meta_Class* mc = cimple::find_meta_class(
                    module->meta_class, class_name);

                if (!mc)
                {
                    err("Unknown class (%s) given by CIMPLE_CLASS_DEPENENCY() "
                        "macro within provider library. Verify that the class "
                        "name is spelled correctly and that genclass was given "
                        "the -r option along with the complete list of "
                        "required classes. To see a complete list of class "
                        "dependencies for your library, use the cwhat "
                        "utility.", class_name);
                }

                validate_class(providing_namespaces[Uint32(i)], mc);
            }
        }
    }

    // Step #5: find short form of library name.

    string short_lib_name = shlib_basename(lib_path);

    // Step #6: register provider module in Pegasus repository.

    string module_name = module->module_name;
    register_module(lib_path, short_lib_name, module_name);

    // Step #7: register provider module Pegasus repository.

    if (argc == 1)
    {
        // Register all providers in the module.

        for (cimple::Registration* p = module; p; p = p->next)
            register_provider(module_name, p->provider_name, p->meta_class);
    }
    else
    {
        // Register selected providers in the module.

        for (int i = 1; i < argc; i++)
        {
            cimple::Registration* reg = 0;

            for (cimple::Registration* p = module; p; p = p->next)
            {
                if (strcasecmp(argv[i], p->meta_class->name) == 0)
                {
                    reg = p;
                    break;
                }
            }

            if (!reg)
            {
                err("Invalid class given as command line argument: %s. "
                    "There is no provider for that class in %s.",
                    argv[i], lib_path);
            }

            register_provider(module_name, reg->provider_name, reg->meta_class);
        }
    }

    return 0;
}

