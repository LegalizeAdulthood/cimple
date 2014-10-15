#include <cimple/version.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Repository/CIMRepository.h>
#include <Pegasus/Common/MofWriter.h>
#include <string>
#include <sys/types.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <getopt.h>
#include <cstdarg>
#include <vector>
#include <cstdio>
#include <cimple/cimple.h>
#include <cimple/Provider_Handle.h>
#include <util/util.h>
#include "usage.h"

#define REGISTRATION_NAMESPACE "root/PG_InterOp"
#define DEFAULT_PROVIDING_NAMESPACE "root/cimv2"

#define INCOMPATIBLE \
    "provider class not compatible with Pegasus repository class: %s. "

using namespace std;
using namespace Pegasus;

static const cimple::Meta_Class* const* _meta_classes = 0;
static size_t _num_meta_classes = 0;

void create_class(
    CIMRepository& rep, 
    const String& ns,
    const cimple::Meta_Class* mc);

void check_class_compatibility(
    CIMRepository& rep,
    const String& ns,
    const cimple::Meta_Class* mc, 
    CIMClass& c);

CIMRepository_Mode g_repository_mode;
string g_pegasus_home;
string g_pegasus_repository_dir;
void* g_handle = 0;

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

//------------------------------------------------------------------------------
//
// print()
//
//------------------------------------------------------------------------------

void print(CIMClass& c)
{
#if defined(Pegasus_Buffer_h)
    Buffer out;
    MofWriter::appendClassElement(out, c);
    out.append('\0');
    printf("%s\n", out.getData());
#else
    CIMObject obj(c);
    String str = obj.toString();
    CString cstr = str.getCString();
    printf("%s\n", (const char*)cstr);
#endif
}

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
		printf("[%d]\n", prop.getType());
		assert(0);
	}

	cout << endl;
    }

    cout << "};\n" << endl;
}

//------------------------------------------------------------------------------
//
// validate_paths()
//
//------------------------------------------------------------------------------

void validate_paths(const string& pegasus_home)
{
    struct Node
    {
	const char* path;
	bool is_dir;
    };

    static const Node paths[] = 
    {
	// FIX: remove root#cimv2 checks:
	{ "", true },
	{ "repository", true },
#if 0
	// Not everybody creates a root/cimv2 namespace.
	{ "repository/root#cimv2", true },
	{ "repository/root#cimv2/instances", true },
	{ "repository/root#cimv2/classes", true },
	{ "repository/root#cimv2/qualifiers", true },
#endif
	{ "repository/root#PG_InterOp", true },
	{ "repository/root#PG_InterOp/instances", true },
	{ "repository/root#PG_InterOp/classes", true },
	{ "repository/root#PG_InterOp/qualifiers", true },
	{ "repository/root", true },
	{ "repository/root/instances", true },
	{ "repository/root/classes", true },
	{ "repository/root/qualifiers", true },
	{ "bin", true },
#ifdef CIMPLE_WINDOWS
	{ "bin/cimserver.exe", false },
	{ "bin/pegcommon.dll", false },
	{ "bin/pegrepository.dll", false },
	{ "bin/pegprovider.dll", false },
#else
	{ "bin/cimserver", false },
	{ "lib/libpegcommon.so", false },
	{ "lib/libpegprovider.so", false },
#endif
	{ "lib", true },
    };
    const size_t num_paths = sizeof(paths) / sizeof(paths[0]);

    for (size_t i = 0; i < num_paths; i++)
    {
	string tmp = pegasus_home + paths[i].path;

	if (paths[i].is_dir)
	{
	    if (!is_dir(tmp.c_str()))
		err("Missing directory: %s\n", tmp.c_str());
	}
	else
	{
	    if (!exists(tmp.c_str()))
		err("Missing file: %s\n", tmp.c_str());
	}
    }
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
// check_pegasus_environment()
//
//------------------------------------------------------------------------------

void check_pegasus_environment(string& pegasus_home)
{
    // Check PEGASUS_HOME environment variable.

    char* tmp = getenv("PEGASUS_HOME");

    if (!tmp)
	err("PEGASUS_HOME environment variable not defined");

    pegasus_home = tmp;

    if (pegasus_home.size() == 0)
	err("PEGASUS_HOME environment variable is empty");

    // Flip backslashes to forward slashes (to accomodate Windows).

    for (size_t i = 0; i < pegasus_home.size(); i++)
    {
	if (pegasus_home[i] == '\\')
	    pegasus_home[i] = '/';
    }

    // Disallow relative paths.

    if (!is_absolute(pegasus_home.c_str()))
	err("PEGASUS_HOME environment variable must denote an absolute path");

    if (pegasus_home[pegasus_home.size()-1] != '/')
	pegasus_home += '/';

    // Validate known paths to directories and files.

    validate_paths(pegasus_home);
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

    // Get the repository

    cimple::Provider_Handle handle(reg);

    const cimple::Meta_Repository* repository = 0;
    cimple::Get_Repository_Status status = handle.get_repository(repository);
    meta_classes = repository->meta_classes;
    num_meta_classes = repository->num_meta_classes;

    return reg;
}

//------------------------------------------------------------------------------
//
// copy_library()
//
//------------------------------------------------------------------------------

void copy_library(
    const char* path)
{
    // Open input file.

    FILE* in = fopen(path, "rb");

    if (!in)
	err("cannot open %s for read", path);

    // Open destination file.

    string to_path = g_pegasus_home + string("/lib/") + base_name(path);

    if (verbose_opt)
	printf("=== Copy provider (%s to %s)\n", path, to_path.c_str());

    FILE* out = fopen(to_path.c_str(), "wb");

    if (!out)
	err("cannot open %s for write", to_path.c_str());

    // Copy one file to the other.

    for (int c; (c = fgetc(in)) != EOF; )
	fputc(c, out);

    fclose(in);
    fclose(out);
}

//------------------------------------------------------------------------------
//
// unregister_provider()
//
//------------------------------------------------------------------------------

void unregister_provider(
    CIMRepository& repository,
    const string& module_name,
    const string& provider_name,
    const string& class_name)
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

	if (verbose_opt)
	    printf("Deleting %s\n", buf);

	repository.deleteInstance(REGISTRATION_NAMESPACE, CIMObjectPath(buf));
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
	char buf[1024];
	sprintf(buf, 
	    "PG_ProviderCapabilities."
	    "ProviderName=\"%s\","
	    "ProviderModuleName=\"%s\","
	    "CapabilityID=\"1\"", 
	    provider_name.c_str(),
	    module_name.c_str());

	if (verbose_opt)
	    printf("Deleting %s\n", buf);

	repository.deleteInstance(REGISTRATION_NAMESPACE, CIMObjectPath(buf));
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
    CIMRepository& repository,
    const string& module_name)
{
    if (verbose_opt)
	printf("=== Deleting provider module instance\n");

    // Delete the PG_ProviderModule instance.

    try
    {
	char buf[1024];
	sprintf(buf, "PG_ProviderModule.Name=\"%s\"", module_name.c_str());

	if (verbose_opt)
	    printf("Deleting %s\n", buf);

	repository.deleteInstance(REGISTRATION_NAMESPACE, CIMObjectPath(buf));
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
// register_module()
//
//------------------------------------------------------------------------------

void register_module(
    const string& short_lib_name,
    const string& module_name)
{
    if (verbose_opt)
	printf("=== Creating provider module instance in Pegasus repository\n");

    // Open repository.

    try
    {
	// Remove old registration instance.

	CIMRepository repository(
	    g_pegasus_repository_dir.c_str(), g_repository_mode);

	string sln = short_lib_name;

	unregister_module(repository, module_name);

	if (unregister_opt)
	    return;

	if (verbose_opt)
	    printf("=== Creating provider module instance\n");

	{
	    CIMInstance i("PG_ProviderModule");

	    if (verbose_opt)
		printf("Creating PG_ProviderModule instance\n");

	    i.addProperty(CIMProperty("Name", String(module_name.c_str())));
	    i.addProperty(CIMProperty("Vendor", String("Pegasus")));
	    i.addProperty(CIMProperty("Version", String("2.0.0")));

	    if (cmpi_opt)
		i.addProperty(CIMProperty("InterfaceType", String("CMPI")));
	    else if (pegasus_cxx_opt)
	    {
		i.addProperty(CIMProperty(
		    "InterfaceType", String("C++Default")));
	    }
	    else
		i.addProperty(CIMProperty("InterfaceType", String("CIMPLE")));

	    i.addProperty(CIMProperty("InterfaceVersion", String("2.0.0")));
	    i.addProperty(CIMProperty("Location", String(sln.c_str())));

	    if (dump_opt)
		print(i);

	    repository.createInstance(REGISTRATION_NAMESPACE, i);
	}
    }
    catch (CIMException& e)
    {
	CString msg = e.getMessage().getCString();
	err("xxx1 unexpected repository error: %s", (const char*)msg);
    }
    catch (...)
    {
	err("xxx2 unexpected repository error");
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
    CIMRepository& rep,
    const String& ns,
    const string& class_name)
{
    try
    {
	rep.deleteClass(ns, String(class_name.c_str()));
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
    CIMRepository& repository,
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
		delete_class(repository, providing_namespaces[j], tmp);
	    }
	}
    }
}

//------------------------------------------------------------------------------
//
// register_provider()
//
//------------------------------------------------------------------------------

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

    // Open repository.

    try
    {
	// Remove old registration instances.

	CIMRepository repository(
	    g_pegasus_repository_dir.c_str(), g_repository_mode);

	unregister_provider(
	    repository, module_name, provider_name, class_name);

	if (unregister_opt && class_opt)
	    uninstall_classes(repository, meta_class);

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

	    if (verbose_opt)
		printf("Creating PG_Provider instance\n");

	    i.addProperty(CIMProperty("Name", pn));
	    i.addProperty(CIMProperty("ProviderModuleName", mn));

	    if (dump_opt)
		print(i);

	    repository.createInstance(REGISTRATION_NAMESPACE, i);
	}

	// Create PG_ProviderCapabilities instance.

	{
	    CIMInstance i("PG_ProviderCapabilities");

	    if (verbose_opt)
		printf("Creating PG_ProviderCapabilities instance\n");

	    i.addProperty(CIMProperty("CapabilityID", String("1")));
	    i.addProperty(CIMProperty("ProviderModuleName", mn));
	    i.addProperty(CIMProperty("ProviderName", pn));
	    i.addProperty(CIMProperty("ClassName", String(cn)));
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

	    repository.createInstance(REGISTRATION_NAMESPACE, i);
	}
    }
    catch (CIMException& e)
    {
	CString msg = e.getMessage().getCString();
	err("xxx3 unexpected repository error: %s", (const char*)msg);
    }
    catch (...)
    {
	err("xxx4 unexpected repository error");
    }
}

//------------------------------------------------------------------------------
//
// get_class()
//
//------------------------------------------------------------------------------

bool get_class(
    CIMRepository& repository,
    const String& name_space,
    const char* class_name,
    CIMClass& cim_class)
{
    try
    {
	const bool local_only = false;
	const bool include_qualifiers = true;
	cim_class = repository.getClass(
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
    CIMRepository& rep,
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

	CIMParameter param = m.getParameter(pos);

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const cimple::Meta_Property* mp = (const cimple::Meta_Property*)mf;

	    if (param.getType() != mp->type)
		err(INCOMPATIBLE "On this method: %s", mc->name, mm->name);

	    if (param.isArray() && mp->subscript == 0)
		err(INCOMPATIBLE "On this method: %s", mc->name, mm->name);
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

	    if (param.getType() != CIMTYPE_REFERENCE)
		err(INCOMPATIBLE "On this method: %s", mc->name, mm->name);

	    String tmp = param.getReferenceClassName().getString();

	    if (tmp != mr->meta_class->name)
		err(INCOMPATIBLE "On this method: %s", mc->name, mm->name);

	    // Check compatibility of these reference classes:

	    CIMClass cc;

	    if (!get_class(rep, ns, mr->meta_class->name, cc))
		err("dependent class not found: %s", mr->meta_class->name);

	    check_class_compatibility(rep, ns, mr->meta_class, cc);
	}
    }
}

//------------------------------------------------------------------------------
//
// check_class_compatibility()
//
//------------------------------------------------------------------------------

void check_class_compatibility(
    CIMRepository& rep,
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

	if (!get_class(rep, ns, mc->super_meta_class->name, cc))
	    err("dependent class not found: %s", mc->super_meta_class->name);

	check_class_compatibility(rep, ns, mc->super_meta_class, cc);
    }

    // Check compatibility of each feature.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const cimple::Meta_Feature* mf = mc->meta_features[i];

	// Check only local features:

	if (!cimple::is_local_feature(mc, mf))
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
	    check_method_compatibility(rep, ns, mc, mm, m);

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

	    if (!get_class(rep, ns, mr->meta_class->name, cc))
		err("dependent class not found: %s", mr->meta_class->name);

	    check_class_compatibility(rep, ns, mr->meta_class, cc);
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
    CIMRepository& repository,
    const char* class_name)
{
    try
    {
	const bool local_only = true;
	const bool include_qualifiers = false;
	CIMClass tmp = repository.getClass(
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
    CIMRepository& rep,
    const String& ns,
    CIMClass& cc, 
    const cimple::Meta_Method* mm)
{
    CIMMethod cm(mm->name, CIMType(mm->return_type));

    for (size_t i = 0; i < mm->num_meta_features; i++)
    {
	const cimple::Meta_Feature* mf = mm->meta_features[i];

	if (strcmp(mf->name, "return_value") == 0)
	    continue;

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const cimple::Meta_Property* mp = (const cimple::Meta_Property*)mf;
	    Uint32 array_size = mp->subscript > 0 ? mp->subscript : 0;
	    bool is_array = mp->subscript != 0;
	    CIMParameter param(
		mp->name, CIMType(mp->type), is_array, array_size);

	    if (mp->flags & CIMPLE_FLAG_IN)
		param.addQualifier(CIMQualifier("in", Boolean(true)));

	    if (mp->flags & CIMPLE_FLAG_OUT)
		param.addQualifier(CIMQualifier("out", Boolean(true)));

	    cm.addParameter(param);
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const cimple::Meta_Reference* mr = (cimple::Meta_Reference*)mf;

	    create_class(rep, ns, mr->meta_class);

	    CIMParameter param(
		mr->name, CIMTYPE_REFERENCE, false, 0, mr->meta_class->name);

	    if (mr->flags & CIMPLE_FLAG_IN)
		param.addQualifier(CIMQualifier("in", Boolean(true)));

	    if (mr->flags & CIMPLE_FLAG_OUT)
		param.addQualifier(CIMQualifier("out", Boolean(true)));

	    cm.addParameter(param);
	}
    }

    cc.addMethod(cm);
}

//------------------------------------------------------------------------------
//
// create_class()
//
//------------------------------------------------------------------------------

void create_class(
    CIMRepository& rep,
    const String& ns,
    const cimple::Meta_Class* mc)
{
    if (class_exists(ns, rep, mc->name))
	return;

    if (verbose_opt)
	printf("=== Creating class in Pegasus repository (%s)\n", mc->name);

    if (!dump_opt)
	printf("Creating class %s\n", mc->name);

    // Create superclass if necessary.

    if (mc->super_meta_class)
	create_class(rep, ns, mc->super_meta_class);

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

	    if (mf->flags & CIMPLE_FLAG_KEY)
		num_keys++;

	    // Ignore non-local feature:

	    if (!cimple::is_local_feature(mc, mf))
		continue;

	    if (mf->flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
	    {
		// Translate CIMPLE embedded properties back to strings.

		assert(mf->flags & CIMPLE_FLAG_REFERENCE);
		assert(!(mf->flags & CIMPLE_FLAG_KEY));

		CIMValue v(CIMTYPE_STRING, false, 0);
		CIMProperty p(mf->name, v, 0);
		p.addQualifier(CIMQualifier("EmbeddedObject", Boolean(true)));

		c.addProperty(p);
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

		create_class(rep, ns, mr->meta_class);
	    }
	}

	// Add methods to the class.

	for (size_t i = 0; i < mc->num_meta_features; i++)
	{
	    const cimple::Meta_Feature* mf = mc->meta_features[i];

	    if (mf->flags & CIMPLE_FLAG_METHOD)
		add_method(rep, ns, c, (const cimple::Meta_Method*)mf);
	}

	// Complain if no keys:

	if (!(mc->flags & CIMPLE_FLAG_INDICATION) && num_keys == 0)
	    err("class has no keys: %s", mc->name);

	// Create the class.

	if (dump_opt)
	    print(c);

	rep.createClass(ns, c);
    }
    catch (Exception& e)
    {
	CString msg = e.getMessage().getCString();
	err("failed to create class in Pegasus repository: %s: %s", 
	    mc->name, (const char*)msg);
    }
    catch (...)
    {
	err("failed to create class in Pegasus repository");
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

    // Find the class in the repository.

    try
    {
	// Open repository:

	CIMRepository repository(
	    g_pegasus_repository_dir.c_str(), g_repository_mode);

	// Create class:

	if (class_opt)
	{
	    // Create provided class.

	    create_class(repository, ns, meta_class);

	    // Create subclasses if requested.

	    if (subclass_opt)
	    {
		for (size_t i = 0; i < _num_meta_classes; i++)
		{
		    if (cimple::is_subclass(meta_class, _meta_classes[i]))
			create_class(repository, ns, _meta_classes[i]);
		}
	    }
	}

	// Be sure the class exists.

	CIMClass c;

	if (!get_class(repository, ns, meta_class->name, c))
	{
	    err("The Pegasus repository contains no class called \"%s\". "
		"Please add this class to repository or use the -c option.",
		meta_class->name);
	}

	// Check compatibility between meta-data and Pegasus class.

	check_class_compatibility(repository, ns, meta_class, c);
    }
    catch (CIMException& e)
    {
	CString msg = e.getMessage().getCString();
	err("cannot open repository: %s: %s", 
	    g_pegasus_repository_dir.c_str(), (const char*)msg);
    }
    catch (...)
    {
	err("cannot open repository: %s", g_pegasus_repository_dir.c_str());
    }
}

//------------------------------------------------------------------------------
//
// main()
//
//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    // Setup arg0 for warn() and err().

    set_arg0(argv[0]);

    // Set the default repository mode:

    g_repository_mode.flag = CIMRepository_Mode::NONE;

    // Extract options:

    int opt;

    while ((opt = getopt(argc, argv, "bdcvhn:uis")) != -1)
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

	    case 'd':
		dump_opt = true;
		break;

	    case 'n':
		providing_namespaces.append(optarg);
		break;

	    case 'h':
		help_opt = true;
		break;

	    case 'b':
		g_repository_mode.flag = CIMRepository_Mode::BIN;
		break;

	    case 'u':
		unregister_opt = true;
		break;

	    case 'i':
		indirect_opt = true;
		break;

            default:
            {
                err("unknown option: -%c\n", opt);
                break;
            }
	}
    }

    argc -= optind - 1;
    argv += optind - 1;

    // check arguments.

    if (argc != 2 || help_opt)
    {
	fprintf(stderr, (const char*)USAGE, argv[0]);
	exit(1);
    }

    // Determine the repository mode:

    const char* repository_mode = getenv("PEGASUS_REPOSITORY_MODE");

    if (repository_mode)
    {
	if (strcmp(repository_mode, "BIN") == 0)
	    g_repository_mode.flag = CIMRepository_Mode::BIN;
	else if (strcmp(repository_mode, "XML") != 0)
	{
	    err("Invalid value for PEGASUS_REPOSITORY_MODE "
		"environment variable: %s (must be \"XML\" or \"BIN\")\n", 
		repository_mode);
	}
    }

    // If there were no -n (namespace) options, then use default.

    if (providing_namespaces.size() == 0)
	providing_namespaces.append(DEFAULT_PROVIDING_NAMESPACE);

    const char* lib_path = argv[1];

    // Validate the Pegasus environment.

    check_pegasus_environment(g_pegasus_home);
    g_pegasus_repository_dir = g_pegasus_home + string("/repository/");

    // Get information from provider.

    cimple::Registration* module = load_module(
	lib_path, _meta_classes, _num_meta_classes);

#if 0
    for (size_t i = 0; i < num_meta_classes; i++)
	printf("class[%s]\n", meta_classes[i]->name);
#endif

    // If no modules in this library.

    if (!module)
	err("module contains no providers: %s", lib_path);

    // validate CIMPLE classes against Pegasus classes in each namespace.

    if (!unregister_opt)
    {
	for (cimple::Registration* p = module; p; p = p->next)
	{
	    for (size_t i = 0; i < providing_namespaces.size(); i++)
	    {
		// Create provided class.

		validate_class(providing_namespaces[i], p->meta_class);
	    }

	}
    }

    // Step #4: copy library to Pegasus library directory.

// File already in Pegasus library directory.
#if 0
    copy_library(lib_path);
#endif

    // Step #5: find short form of library name.

    string short_lib_name = shlib_basename(lib_path);

    // Step #6: register provider module Pegasus repository.

    string module_name = module->module_name;
    register_module(short_lib_name, module_name);

    // Step #7: register provider module Pegasus repository.

    for (cimple::Registration* p = module; p; p = p->next)
	register_provider(module_name, p->provider_name, p->meta_class);

    return 0;
}

CIMPLE_INJECT_VERSION_TAG;
