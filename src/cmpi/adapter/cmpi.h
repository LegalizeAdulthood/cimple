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

#ifndef _cimple_cmpi_h
#define _cimple_cmpi_h

#include <cimple/cimple.h>

#if defined(CIMPLE_PLATFORM_LINUX_IX86_GNU)
#   define CMPI_PLATFORM_LINUX_GENERIC_GNU 1
#elif defined(CIMPLE_PLATFORM_LINUX_X86_64_GNU)
#   define CMPI_PLATFORM_LINUX_GENERIC_GNU 1
#elif defined(CIMPLE_PLATFORM_WIN32_IX86_MSVC)
#   define CMPI_PLATFORM_WIN32_IX86_MSVC 1
#elif defined(CIMPLE_PLATFORM_LINUX_PPC_GNU)
#   define CMPI_PLATFORM_LINUX_PPC_GNU 1
#elif defined(CIMPLE_PLATFORM_SOLARIS_SPARC_GNU)
#   define  CMPI_PLATFORM_SOLARIS_SPARC_GNU 1
#endif

#define enumInstances enumerateInstances
#define enumInstanceNames enumerateInstanceNames
#include <cmpidt.h>
#include <cmpift.h>
#include <cmpimacs.h>

#endif /* _cimple_cmpi_h */
