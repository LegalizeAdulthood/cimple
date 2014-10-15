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

#include "unistd.h"
#include <cctype>
#include <cstdio>
#include <windows.h>
#include <io.h>

POSIX_NAMESPACE_BEGIN

unsigned int sleep(unsigned int seconds)
{
    Sleep(seconds * 1000);
    return 0;
}

#if 0
int access(const char* p, int mode)
{
printf("ENTER[%s]\n", p);
    // Fail on empty string.

    if (*p == '\0')
	return -1;

    // Handle path of the form "[A-Z]:/".

    if (isalpha(p[0]) && p[1] == ':' && p[2] == '/' && p[3] == '\0')
	return ::access(p, mode);

    // Handle "/".

    if (p[0] == '/' && p[1] == '\0')
	return ::access(p, mode);

    // Handle paths that do not end with '/'.

    const char* end = p;

    while (*end)
	end++;

    if (*--end != '/')
	return ::access(p, mode);

    // Handle paths that end with '/' (Windows access() fails on these so
    // we must remove the slash).

    char* q = (char*)malloc(end - p + 1);

    if (!q)
	return -1;

    *q = '\0';
    strncat(q, p, end - p);

printf("q[%s]\n", q);

    int rc = ::access(q, mode);

    free(q);

    return rc;
}
#endif

POSIX_NAMESPACE_END
