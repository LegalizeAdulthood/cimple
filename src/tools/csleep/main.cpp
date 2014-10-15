#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv)
{
    // Check args.

    if (argc != 2)
    {
        fprintf(stderr, "%s seconds\n", argv[0]);
        exit(1);
    }

    // Sleep:

    char* end;
    long sec = strtoul(argv[1], &end, 10);

    if (*end != '\0')
    {
        fprintf(stderr, "%s: bad seconds argument\n", argv[1]);
        exit(1);
    }

    sleep(sec);

    return 0;
}

