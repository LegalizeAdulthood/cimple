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

#ifndef _cimple_posix_unistd_h
#define _cimple_posix_unistd_h

#include "linkage.h"
#include <io.h>

#define F_OK 00 /* Existence-only */
#define W_OK 02 /* Write-only */
#define R_OK 04 /* Read-only */
#define X_OK R_OK /* Execute (if you can read it you can execute it). */
#define RW_OK 06 /* Read and write */

#define S_ISDIR(mode) ((0040000 & mode) ? 1 : 0)

POSIX_NAMESPACE_BEGIN

POSIX_LINKAGE unsigned int sleep(unsigned int seconds);

POSIX_LINKAGE int chdir(const char* path);

POSIX_LINKAGE char* getcwd(char* buffer, size_t size);

POSIX_NAMESPACE_END


#endif /* _cimple_posix_unistd_h */
