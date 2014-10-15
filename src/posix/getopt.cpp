/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
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

#include <cctype>
#include <cstring>
#include <cstdio>
#include "getopt.h"

POSIX_NAMESPACE_BEGIN

char *optarg = NULL;
int optind = 1;
int opterr = 1;
int optopt = 0;

int getopt(int argc, char** argv, const char* optstring)
{
    for (int i = optind; i < argc; i++)
    {
        char* arg = argv[i];

        // Check for option:

        if (arg[0] == '-' && arg[1] != '\0')
        {
            // Check option and option argument (if any).

            int opt = arg[1];
            const char* p = strchr(optstring, opt);
            optarg = NULL;

            if (p == NULL)
            {
                if (opterr)
                    fprintf(stderr, "%s: invalid option -- %c\n", argv[0], opt);

                optopt = opt;
                opt = '?';
            }
            else if (p[1] == ':')
            {
                if ((optarg = argv[i+1]) == NULL)
                {
                    if (opterr)
                    {
                        fprintf(stderr, 
                            "%s: option requires an argument -- %c\n", 
                            argv[0], opt);
                    }

                    optopt = opt;

                    if (*optstring == ':')
                        opt = ':';
                    else
                        opt = '?';
                }
            }

            // Move arguments leftward to optind.

            int n = optarg ? 2 : 1;

            memmove(
                argv + optind + n, 
                argv + optind, 
                (i - optind) * sizeof(char*));

            argv[optind++] = arg;

            if (optarg)
                argv[optind++] = optarg;

            return opt;
        }
    }

    return -1;
}

POSIX_NAMESPACE_END
