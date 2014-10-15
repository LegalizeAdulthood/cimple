#include <cimple/config.h>
#include <cassert>
#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <util/util.h>
#include <vector>
#include <string>
#include "usage.h"

using namespace std;

static void gen_project(const char* module_name, int argc, char** argv)
{
    // Locate supporting programs.

    string genclass = string(CIMPLE_BINDIR) + "/genclass";
    string genprov = string(CIMPLE_BINDIR) + "/genprov";
    string genmod = string(CIMPLE_BINDIR) + "/genmod";

    if (!exists(genclass))
        err("required program missing: %s", genclass.c_str());

    if (!exists(genprov))
        err("required program missing: %s", genprov.c_str());

    if (!exists(genmod))
        err("required program missing: %s", genmod.c_str());

    // Run genclass:
    {
        printf("==== genclass:\n");
        string cmd = genclass + string(" -r");

        for (int i = 0; i < argc; i++)
            cmd += string(" ") + string(argv[i]);

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genclass.c_str());

        if (status != 0)
            exit(1);
    }

    // Run genprov:
    {
        printf("==== genprov:\n");
        string cmd = genprov;

        for (int i = 0; i < argc; i++)
            cmd += string(" ") + string(argv[i]);

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genprov.c_str());

        if (status != 0)
            exit(1);
    }

    // Run genmod:
    {
        printf("==== genmod:\n");
        string cmd = genmod + string(" ") + string(module_name);

        for (int i = 0; i < argc; i++)
            cmd += string(" ") + string(argv[i]);

        int status = system(cmd.c_str());

        if (status == -1)
            err("failed to execute %s", genmod.c_str());

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

    while ((opt = getopt(argc, argv, "hV")) != -1)
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

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genproj/main.cpp,v 1.2 2007/04/18 16:55:54 mbrasher-public Exp $");
