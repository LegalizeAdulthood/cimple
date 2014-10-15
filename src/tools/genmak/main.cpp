#include <cimple/config.h>
#include <cassert>
#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <string>
#include <unistd.h>
#include <util/util.h>
#include <vector>
#include <string>
#include "usage.h"

using namespace std;

static bool force_opt = false;
static bool cmpi_opt = false;

static bool valid_library_name(const char* path)
{
    const char* p = path;

    for (; *p; p++)
    {
        if (!isalnum(*p) && *p != '_')
            return false;
    }

    return p != path;
}

static void genmak(const char* library_name, int argc, char** argv)
{
    // Check library name:

    if (!valid_library_name(library_name))
        err("Invalid library name: %s", library_name);

    // Refuse to overwrite Makefile unless -f given:

    if (!force_opt && exists("Makefile"))
        err("\"Makefile\" already exists. Use -f to force overwrite");

    // Locate the TOP directory that has the "mak" directory.

    char top[1024];
    sprintf(top, "%s/cimple", CIMPLE_DATADIR);

    if (!exists(top))
        err("missing required directory: \"%s\"", top);

    // Check for config.options file:

    char options[1024];
    sprintf(options, "%s/config.options", top);

    if (!exists(options))
        err("missing required file: \"%s\"", options);

    // Check for mak directory:

    char makdir[1024];
    sprintf(makdir, "%s/mak", top);

    if (!exists(makdir))
        err("missing required directory: \"%s\"", makdir);

    // Open Makefile:

    FILE* out = fopen("Makefile", "wb");

    if (!out)
        err("failed to open \"Makefile\"");

    // Write Makefile contents:

    fprintf(out, "TOP=%s\n", top);
    fprintf(out, "ROOT=.\n");
    fprintf(out, "BINDIR=.\n");
    fprintf(out, "LIBDIR=.\n");
    fprintf(out, "include $(TOP)/mak/config.mak\n");
    fprintf(out, "\n");
    fprintf(out, "SHARED_LIBRARY=%s\n", library_name);

    for (int i = 0; i < argc; i++)
    {
        if (!exists(argv[i]))
            err("source file does not exist: %s\n", argv[i]);

        fprintf(out, "SOURCES += %s\n", argv[i]);
    }

    if (cmpi_opt)
    {
        fprintf(out, "CIMPLE_CMPI_MODULE=1\n");
        fprintf(out, "DEFINES += -DCIMPLE_CMPI_MODULE\n");
        fprintf(out, "LIBRARIES += cimplecmpiadap\n");
    }
    else
    {
        fprintf(out, "CIMPLE_PEGASUS_MODULE=1\n");
        fprintf(out, "DEFINES += -DCIMPLE_PEGASUS_MODULE\n");
        fprintf(out, "LIBRARIES += cimplepegadap\n");
    }

    fprintf(out, "LIBRARIES += cimple\n");

    fprintf(out, "\n");

    fprintf(out, "include $(TOP)/mak/rules.mak\n");

    // Close Makefile:

    fclose(out);

    printf("Created Makefile\n");
}

int main(int argc, char** argv)
{
    const char* arg0 = argv[0];

    // Check options:

    int opt;

    while ((opt = getopt(argc, argv, "fhVC")) != -1)
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

            case 'f':
            {
                force_opt = true;
                break;
            }

            case 'c':
            {
                cmpi_opt = true;
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

    genmak(argv[0], argc - 1, argv + 1);

    return 0;
}
