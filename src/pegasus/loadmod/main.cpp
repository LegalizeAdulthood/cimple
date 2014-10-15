#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>

using namespace Pegasus;

typedef CIMProvider* (*PegasusCreateProviderProc)(const String& name);

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s provider-path provider-name\n", argv[0]);
        exit(1);
    }

    void* handle = dlopen(argv[1], RTLD_NOW | RTLD_GLOBAL);

    if (!handle)
    {
        fprintf(stderr, "%s: dlopen() failed on %s\n", argv[0], argv[1]);
        exit(1);
    }

    void* symbol = dlsym(handle, "PegasusCreateProvider");

    if (!symbol)
    {
        fprintf(stderr, 
            "%s: dlsym() failed on symbol \"PegasusCreateProvider\"\n", 
            argv[0]);
        exit(1);
    }

    PegasusCreateProviderProc proc = (PegasusCreateProviderProc)symbol;

    CIMProvider* provider = proc(String(argv[2]));

    if (provider == 0)
    {
        fprintf(stderr, "%s: PegasusCreateProvider() returned null\n", argv[0]);
        exit(1);
    }

    CIMOMHandle ch;
    provider->initialize(ch);

    printf("%s: sleeping forever...\n", argv[0]);

    for (;;)
        sleep(1);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/loadmod/main.cpp,v 1.6 2007/03/07 18:50:09 mbrasher-public Exp $");
