#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <cimple/config.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <cctype>

using namespace std;

const char* arg0;

struct File
{
    const char* name;

    // ('p' = program , 'l' = library, 'h' = header)
    int type;
};

static const File _files[] = 
{
#ifdef CIMPLE_WINDOWS
    { "regmod.exe", 'p' },
    { "apriori.exe", 'p' },
    { "catmod.exe", 'p' },
    { "cgenuuid.exe", 'p' },
    { "cimpleinfo.exe", 'p' },
    { "cimplefiles.exe", 'p' },
    { "csleep.exe", 'p' },
    { "cwhat.exe", 'p' },
    { "dlopen.exe", 'p' },
    { "dlsym.exe", 'p' },
    { "file2c.exe", 'p' },
    { "genclass.exe", 'p' },
    { "genclass_test1.exe", 'p' },
    { "genclass_test2.exe", 'p' },
    { "genclass_test3.exe", 'p' },
    { "genclass_test4.exe", 'p' },
    { "genclass_test5.exe", 'p' },
    { "genclass_test6.exe", 'p' },
    { "genclass_test7.exe", 'p' },
    { "genprov.exe", 'p' },
    { "mof2html.exe", 'p' },
    { "mofc.exe", 'p' },
    { "test_array.exe", 'p' },
    { "test_cast.exe", 'p' },
    { "test_class.exe", 'p' },
    { "test_genprov1.exe", 'p' },
    { "test_genprov2.exe", 'p' },
    { "test_join.exe", 'p' },
    { "test_model_path.exe", 'p' },
    { "test_mutex.exe", 'p' },
    { "test_property.exe", 'p' },
    { "test_sizes.exe", 'p' },
    { "test_static.exe", 'p' },
    { "test_string.exe", 'p' },
    { "test_time.exe", 'p' },
    { "cimplecmpiadap.lib", 'l' },
    { "cimplecmpiadap.dll", 'l' },
    { "cimplegencommon_s.a", 'l' },
    { "cimplegencommon.lib", 'l' },
    { "cimplegencommon.dll", 'l' },
    { "cimplemof.lib", 'l' },
    { "cimplemof.dll", 'l' },
    { "cimplepegadap.lib", 'l' },
    { "cimplepegadap.dll", 'l' },
    { "cimple_s.a", 'l' },
    { "cimple.lib", 'l' },
    { "cimple.dll", 'l' },
    { "cimpleutil_s.a", 'l' },
    { "cimpleutil.lib", 'l' },
    { "cimpleutil.dll", 'l' },
    { "cmplarrays.lib", 'l' },
    { "cmplarrays.dll", 'l' },
    { "cmplbug31.lib", 'l' },
    { "cmplbug31.dll", 'l' },
    { "cmplbug.lib", 'l' },
    { "cmplbug.dll", 'l' },
    { "cmplcsdd.lib", 'l' },
    { "cmplcsdd.dll", 'l' },
    { "cmplderivedindic.lib", 'l' },
    { "cmplderivedindic.dll", 'l' },
    { "cmpldiskdrive.lib", 'l' },
    { "cmpldiskdrive.dll", 'l' },
    { "cmplexample.lib", 'l' },
    { "cmplexample.dll", 'l' },
    { "cmplfan.lib", 'l' },
    { "cmplfan.dll", 'l' },
    { "cmpllinuxsysprov.lib", 'l' },
    { "cmpllinuxsysprov.dll", 'l' },
    { "cmplmethods.lib", 'l' },
    { "cmplmethods.dll", 'l' },
    { "cmplmyindic.lib", 'l' },
    { "cmplmyindic.dll", 'l' },
    { "cmplperson2.lib", 'l' },
    { "cmplperson2.dll", 'l' },
    { "cmplperson.lib", 'l' },
    { "cmplperson.dll", 'l' },
    { "cmplrep.lib", 'l' },
    { "cmplrep.dll", 'l' },
    { "cmplsalesman.lib", 'l' },
    { "cmplsalesman.dll", 'l' },
    { "cmplthing.lib", 'l' },
    { "cmplthing.dll", 'l' },
    { "cmplunixusrprov.lib", 'l' },
    { "cmplunixusrprov.dll", 'l' },
    { "cmplupcall2.lib", 'l' },
    { "cmplupcall2.dll", 'l' },
    { "cmplupcall3.lib", 'l' },
    { "cmplupcall3.dll", 'l' },
    { "cmplupcall.lib", 'l' },
    { "cmplupcall.dll", 'l' },
#else /* CIMPLE_WINDOWS */
    { "regmod", 'p' },
    { "apriori", 'p' },
    { "catmod", 'p' },
    { "cgenuuid", 'p' },
    { "cimpleinfo", 'p' },
    { "cimplefiles", 'p' },
    { "csleep", 'p' },
    { "cwhat", 'p' },
    { "dlopen", 'p' },
    { "dlsym", 'p' },
    { "file2c", 'p' },
    { "genclass", 'p' },
    { "genclass_test1", 'p' },
    { "genclass_test2", 'p' },
    { "genclass_test3", 'p' },
    { "genclass_test4", 'p' },
    { "genclass_test5", 'p' },
    { "genclass_test6", 'p' },
    { "genclass_test7", 'p' },
    { "genprov", 'p' },
    { "mof2html", 'p' },
    { "mofc", 'p' },
    { "test_array", 'p' },
    { "test_cast", 'p' },
    { "test_class", 'p' },
    { "test_genprov1", 'p' },
    { "test_genprov2", 'p' },
    { "test_join", 'p' },
    { "test_model_path", 'p' },
    { "test_mutex", 'p' },
    { "test_property", 'p' },
    { "test_sizes", 'p' },
    { "test_static", 'p' },
    { "test_string", 'p' },
    { "test_time", 'p' },
    { "libcimplecmpiadap.so", 'l' },
    { "libcimplecmpiadap.so.1", 'l' },
    { "libcimplegencommon_s.a", 'l' },
    { "libcimplegencommon.so", 'l' },
    { "libcimplegencommon.so.1", 'l' },
    { "libcimplemof.so", 'l' },
    { "libcimplemof.so.1", 'l' },
    { "libcimplepegadap.so", 'l' },
    { "libcimplepegadap.so.1", 'l' },
    { "libcimple_s.a", 'l' },
    { "libcimple.so", 'l' },
    { "libcimple.so.1", 'l' },
    { "libcimpleutil_s.a", 'l' },
    { "libcimpleutil.so", 'l' },
    { "libcimpleutil.so.1", 'l' },
    { "libcmplarrays.so", 'l' },
    { "libcmplarrays.so.1", 'l' },
    { "libcmplbug31.so", 'l' },
    { "libcmplbug31.so.1", 'l' },
    { "libcmplbug.so", 'l' },
    { "libcmplbug.so.1", 'l' },
    { "libcmplcsdd.so", 'l' },
    { "libcmplcsdd.so.1", 'l' },
    { "libcmplderivedindic.so", 'l' },
    { "libcmplderivedindic.so.1", 'l' },
    { "libcmpldiskdrive.so", 'l' },
    { "libcmpldiskdrive.so.1", 'l' },
    { "libcmplexample.so", 'l' },
    { "libcmplexample.so.1", 'l' },
    { "libcmplfan.so", 'l' },
    { "libcmplfan.so.1", 'l' },
    { "libcmpllinuxsysprov.so", 'l' },
    { "libcmpllinuxsysprov.so.1", 'l' },
    { "libcmplmethods.so", 'l' },
    { "libcmplmethods.so.1", 'l' },
    { "libcmplmyindic.so", 'l' },
    { "libcmplmyindic.so.1", 'l' },
    { "libcmplperson2.so", 'l' },
    { "libcmplperson2.so.1", 'l' },
    { "libcmplperson.so", 'l' },
    { "libcmplperson.so.1", 'l' },
    { "libcmplrep.so", 'l' },
    { "libcmplrep.so.1", 'l' },
    { "libcmplsalesman.so", 'l' },
    { "libcmplsalesman.so.1", 'l' },
    { "libcmplthing.so", 'l' },
    { "libcmplthing.so.1", 'l' },
    { "libcmplunixusrprov.so", 'l' },
    { "libcmplunixusrprov.so.1", 'l' },
    { "libcmplupcall2.so", 'l' },
    { "libcmplupcall2.so.1", 'l' },
    { "libcmplupcall3.so", 'l' },
    { "libcmplupcall3.so.1", 'l' },
    { "libcmplupcall.so", 'l' },
    { "libcmplupcall.so.1", 'l' },
#endif /* CIMPLE_WINDOWS */
    { "platform.h", 'h' },
    { "cimple/Array.h", 'h' },
    { "cimple/Array_Impl.h", 'h' },
    { "cimple/Atomic_Counter.h", 'h' },
    { "cimple/Atomic_DARWIN_IX86_GNU.h", 'h' },
    { "cimple/Atomic_DARWIN_PPC_GNU.h", 'h' },
    { "cimple/Atomic.h", 'h' },
    { "cimple/Atomic_LINUX_IA64_GNU.h", 'h' },
    { "cimple/Atomic_LINUX_IX86_GNU.h", 'h' },
    { "cimple/Atomic_LINUX_PPC_GNU.h", 'h' },
    { "cimple/Atomic_LINUX_S390_GNU.h", 'h' },
    { "cimple/Atomic_WIN32_IX86_MSVC.h", 'h' },
    { "cimple/Auto_Mutex.h", 'h' },
    { "cimple/cimom.h", 'h' },
    { "cimple/cimple.h", 'h' },
    { "cimple/Cond.h", 'h' },
    { "cimple/config.h", 'h' },
    { "cimple/Datetime.h", 'h' },
    { "cimple/Error.h", 'h' },
    { "cimple/flags.h", 'h' },
    { "cimple/flavor.h", 'h' },
    { "cimple/Instance.h", 'h' },
    { "cimple/Instance_Map.h", 'h' },
    { "cimple/io.h", 'h' },
    { "cimple/linkage.h", 'h' },
    { "cimple/Magic.h", 'h' },
    { "cimple/Meta_Class.h", 'h' },
    { "cimple/Meta_Feature.h", 'h' },
    { "cimple/Meta_Method.h", 'h' },
    { "cimple/Meta_Property.h", 'h' },
    { "cimple/Meta_Qualifier.h", 'h' },
    { "cimple/Meta_Reference.h", 'h' },
    { "cimple/Meta_Repository.h", 'h' },
    { "cimple/Meta_Value.h", 'h' },
    { "cimple/Mutex.h", 'h' },
    { "cimple/options.h", 'h' },
    { "cimple/platform_DARWIN.h", 'h' },
    { "cimple/platform_DARWIN_IX86_GNU.h", 'h' },
    { "cimple/platform_DARWIN_PPC_GNU.h", 'h' },
    { "cimple/platform_LINUX.h", 'h' },
    { "cimple/platform_LINUX_IA64_GNU.h", 'h' },
    { "cimple/platform_LINUX_IX86_GNU.h", 'h' },
    { "cimple/platform_LINUX_PPC_GNU.h", 'h' },
    { "cimple/platform_LINUX_S390_GNU.h", 'h' },
    { "cimple/platform_LINUX_X86_64_GNU.h", 'h' },
    { "cimple/platform_WIN32_IX86_MSVC.h", 'h' },
    { "cimple/Property.h", 'h' },
    { "cimple/Provider.h", 'h' },
    { "cimple/Provider_Handle.h", 'h' },
    { "cimple/ptr_array.h", 'h' },
    { "cimple/Ref.h", 'h' },
    { "cimple/Registration.h", 'h' },
    { "cimple/scope.h", 'h' },
    { "cimple/String.h", 'h' },
    { "cimple/Strings.h", 'h' },
    { "cimple/Thread_Context.h", 'h' },
    { "cimple/Thread.h", 'h' },
    { "cimple/Time.h", 'h' },
    { "cimple/TSD.h", 'h' },
    { "cimple/Type.h", 'h' },
    { "cimple/version.h", 'h' },
};

static const size_t NUM_FILES = sizeof(_files) / sizeof(_files[0]);

int load_file(const string& path, vector<char>& data)
{
    data.clear();

    FILE* is = fopen(path.c_str(), "rb");

    if (!is)
        return -1;

    size_t n;
    char buffer[4096];

    while ((n = fread(buffer, 1, sizeof(buffer), is)) != 0)
        data.insert(data.end(), buffer, buffer + n);

    fclose(is);
    return 0;
}

ssize_t find_str_nocase(const vector<char>& data, const char* subject)
{
    size_t n = strlen(subject);

    for (size_t i = 0; i < data.size(); i++)
    {
        size_t r = data.size() - i;

        if (n <= r)
        {
            size_t j;

            for (j = 0; j < n; j++)
            {
                if (tolower(subject[j]) != tolower(data[i + j]))
                    break;
            }

            if (j == n)
                return i;
        }
    }

    // Not found!
    return -1;
}

void process(const string& path)
{
    // Skip directories.

    struct stat st;

    if (stat(path.c_str(), &st) != 0)
        return;

    if (S_ISDIR(st.st_mode))
        return;

    // For each candidate file.

    for (size_t i = 0; i < NUM_FILES; i++)
    {
        const File& f = _files[i];

        // See if current file is a suffix of the path.

        const char* p = strstr(path.c_str(), f.name);

        if (!p || strlen(p) != strlen(f.name))
            continue;

        // Load file into memory.

        vector<char> data;

        if (load_file(path, data) != 0)
        {
            continue;
        }

        // Try to get CIMPLE_VERSION tag.

        const char PATTERN[] = "@(#)CIMPLE_VERSION=";

        ssize_t pos = find_str_nocase(data, PATTERN);

        if (pos == -1 || strcmp(f.name, "cimple/version.h") == 0)
        {
            if (find_str_nocase(data, "cimple") == -1)
                continue;

            printf("%s\n", path.c_str());
        }
        else
        {
            printf("%s (%s)\n", path.c_str(), &data[pos + sizeof(PATTERN) - 1]);
        }
    }
}

void scan(const string& path)
{
    // Open directory.

    DIR* dir = opendir(path.c_str());

    if (dir == NULL)
    {
        fprintf(stderr,
            "%s: warning: cannot open directory: \"%s\"\n", arg0, path.c_str());
        return;
    }

    // For each file in this directory:

    vector<string> paths;
    dirent* ent;
    
    while ((ent = readdir(dir)) != NULL)
    {
        // Skip over "." and ".."

        string name = ent->d_name;

        if (name ==  "." || name == "..")
            continue;

        // Build full path name for this file:

        string fn;
        
        if (path.size() == 1 && path[0] == '/')
            fn = string("/") + name;
        else
            fn = path + string("/") + name;

        // Determine file type (skip soft links and directories).

        struct stat st;

#ifdef CIMPLE_WINDOWS
        if (stat(fn.c_str(), &st) == -1)
#else
        if (lstat(fn.c_str(), &st) == -1)
#endif
        {
            fprintf(stderr, 
                "%s: warning: cannot stat \"%s\"\n", arg0, fn.c_str());
            continue;
        }


        // If it's a directory, save the name:

        if (S_ISDIR(st.st_mode))
            paths.push_back(fn);

        // Skip links.

#ifndef CIMPLE_WINDOWS
        if (S_ISLNK(st.st_mode))
            continue;
#endif

        // Process this file.

        process(fn);
    }

    // Close this directory:

    closedir(dir);

    // Check for files relative to each directory:

    for (size_t i = 0; i < paths.size(); i++)
        scan(paths[i]);
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    /* Usage */

    if (argc != 1 && argc != 2)
    {
        fprintf(stderr, "Usage: %s [path]\n", argv[0]);
        exit(1);
    }

    /* Scan */

    if (argc == 2)
        scan(argv[1]);
    else
        scan(".");

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/cimplefiles/main.cpp,v 1.8 2007/03/07 18:49:10 mbrasher-public Exp $");
