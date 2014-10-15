/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#ifndef _cimple_platform_LINUX_IX86_GNU_h
#define _cimple_platform_LINUX_IX86_GNU_h

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#define CIMPLE_HAVE_ZU

#define CIMPLE_HIDE __attribute__((visibility("hidden")))

#define CIMPLE_DEFAULT __attribute__((visibility("default")))

#define CIMPLE_UINT64 unsigned long long

#define CIMPLE_SINT64 signed long long

#define CIMPLE_UNIX

#define CIMPLE_IMPORT

#define CIMPLE_EXPORT

#endif /* _cimple_platform_LINUX_IX86_GNU_h */
