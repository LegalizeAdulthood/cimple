#include <cimple/config.h>
#include <cassert>
#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <util/util.h>
#include <vector>
#include <string>
#include "usage.h"

using namespace std;

static bool genmak_opt = false;
static bool force_opt = false;
static bool enum_opt = false;
static bool regmod_opt = false;

#if defined(CIMPLE_WINDOWS)

int which(const string& program, string& path)
{
    path.erase(path.begin(), path.end());

    char* sp = getenv("PATH");

    if (!sp)
        return -1;

    sp = strdup(sp);

    for (char* p = strtok(sp, ":"); p; p = strtok(NULL, ";"))
    {
        string tmp = string(p) + string("/") + program;

        if (exists(tmp.c_str()))
        {
            path = tmp;
            return 0;
        }
    }

    return -1;
}

#endif /* CIMPLE_WINDOWS */

static void gen_project(const char* module_name, int argc, char** argv)
{
    // Locate supporting programs.

#if defined(CIMPLE_WINDOWS)

    string genclass;
    string genprov;
    string genmod;
    string genmak;

    if (which("genclass.exe", genclass) != 0)
        err("genclass.exe not found on PATH");

    if (which("genprov.exe", genprov) != 0)
        err("genprov.exe not found on PATH");

    if (which("genmod.exe", genmod) != 0)
        err("genmod.exe not found on PATH");

    if (which("genmak.exe", genmak) != 0)
        err("genmak.exe not found on PATH");

#else /* CIMPLE_WINDOWS */

    string genclass = string(CIMPLE_BINDIR) + "/genclass";
    string genprov = string(CIMPLE_BINDIR) + "/genprov";
    string genmod = string(CIMPLE_BINDIR) + "/genmod";
    string genmak = string(CIMPLE_BINDIR) + "/genmak";

    if (!exists(genclass))
        err("required program missing: %s", genclass.c_str());

    if (!exists(genprov))
        err("required program missing: %s", genprov.c_str());

    if (!exists(genmod))
        err("required program missing: %s", genmod.c_str());

    if (!exists(genmak))
        err("required program missing: %s", genmak.c_str());

#endif /* !CIMPLE_WINDOWS */

    vector<string> sources;

    // Run genclass:
    {
        string cmd = genclass + string(" -r -S");

        if (enum_opt)
            cmd += " -e";

        for (int i = 0; i < argc; i++)
            cmd += string(" ") + string(argv[i]);

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genclass.c_str());

        if (status != 0)
            exit(1);

        // Read source file names from .genclass:
        {
            FILE* is = fopen(".genclass", "r");
            char buffer[1024];

            if (!is)
                err("failed to open .genclass file\n");

            while (fgets(buffer, sizeof(buffer), is) != NULL)
            {
                char* p = buffer;

                while (*p)
                    p++;

                while (p != buffer && isspace(p[-1]))
                    *--p = '\0';

                sources.push_back(buffer);
            }

            fclose(is);
        }
    }

    // Run genprov:
    {
        string cmd = genprov;

        for (int i = 0; i < argc; i++)
            cmd += string(" ") + string(argv[i]);

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genprov.c_str());

        if (status != 0)
            exit(1);

        for (int i = 0; i < argc; i++)
        {
            char buffer[1024];
            sprintf(buffer, "%s_Provider.cpp", argv[i]);
            sources.push_back(buffer);
        }
    }

    // Run genmod:
    {
        string cmd = genmod + string(" ") + string(module_name);

        for (int i = 0; i < argc; i++)
            cmd += string(" ") + string(argv[i]);

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genmod.c_str());

        if (status != 0)
            exit(1);

        sources.push_back("module.cpp");
    }

    // Run genmak:

    if (genmak_opt)
    {
        string cmd = genmak + string(" ");

        if (force_opt)
            cmd += "-f ";

        if (regmod_opt)
            cmd += "-r ";
        
        cmd += string(module_name);

        for (size_t i = 0; i < sources.size(); i++)
            cmd += string(" ") + sources[i];

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genmak.c_str());

        if (status != 0)
            exit(1);
    }
}

int main(int argc, char** argv)
{
    const char* arg0 = argv[0];

    vector<string> mof_files;

    // Check options:

    int opt;

    while ((opt = getopt(argc, argv, "hVmfer")) != -1)
    {
        switch (opt)
        {
            case 'h':
            {
                fprintf(stderr, (char*)USAGE, arg0);
                exit(0);
            }

            case 'V':
            {
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
            }

            case 'm':
            {
                genmak_opt = true;
                break;
            }

            case 'f':
            {
                force_opt = true;
                break;
            }

            case 'e':
            {
                enum_opt = true;
                break;
            }

            case 'r':
            {
                regmod_opt = true;
                break;
            }

            default:
                err("unknown option: %c", opt);
                break;
        }
    }

    // Check usage.

    argc -= optind;
    argv += optind;

    if (argc < 2)
    {
        fprintf(stderr, (char*)USAGE, arg0);
        exit(1);
    }

    // Generate module file.

    gen_project(argv[0], argc - 1, argv + 1);

    return 0;
}
