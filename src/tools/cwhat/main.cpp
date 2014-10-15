#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

const char USAGE[] = "\
\n\
Usage: %s file\n\
\n\
Synopsis:\n\
    This utility searches a file for strings that begin with the pattern\n\
    \"@(%s)\" and end with a null character. These strings are printed to\n\
    standard output. It is similar to the Unix \"what\" utility.\n\
\n\
    CIMPLE injects these strings into programs and libraries, so that useful\n\
    information can be obtained in the field (e.g., version).\n\
\n\
Examples:\n\
\n\
    %% cimple_version libcimple.so\n\
    0.98-beta\n\
\n\
    %% cimple_version genclass\n\
    0.98-beta\n\
\n";

int main(int argc, char** argv)
{
    // Check args.

    if (argc != 2)
    {
        fprintf(stderr, USAGE, argv[0], "#");
        exit(1);
    }

    // Open the input file.

    FILE* fp = fopen(argv[1], "rb");

    if (!fp)
    {
        fprintf(stderr, "%s: failed to open file\n", argv[1]);
        exit(1);
    }

    // Read the file into memory.

    char buf[1024];
    vector<char> v;
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
        v.insert(v.end(), buf, buf + n);

    v.push_back('\0');

    // Close the file:

    fclose(fp);

    // Search for version string.

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

            printf("%s\n", str.c_str());
        }

        n--;
        p++;
    }

    return 0;
}

