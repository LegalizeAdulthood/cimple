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

#ifndef _cimple_Atomic_h
#define _cimple_Atomic_h

#include "config.h"

#if defined(CIMPLE_PLATFORM_LINUX_IX86_GNU)
# include "Atomic_LINUX_IX86_GNU.h"
#elif defined(CIMPLE_PLATFORM_LINUX_X86_64_GNU)
# include "Atomic_LINUX_IX86_GNU.h"
#elif defined(CIMPLE_PLATFORM_LINUX_IA64_GNU)
# include "Atomic_LINUX_IA64_GNU.h"
#elif defined(CIMPLE_PLATFORM_LINUX_PPC_GNU) || \
    defined(CIMPLE_PLATFORM_LINUX_PPC64_GNU)
# include "Atomic_LINUX_PPC_GNU.h"
#elif defined(CIMPLE_PLATFORM_LINUX_S390_GNU) || \
    defined(CIMPLE_PLATFORM_LINUX_S390X_GNU)
# include "Atomic_LINUX_S390_GNU.h"
#elif defined(CIMPLE_PLATFORM_DARWIN_PPC_GNU)
# include "Atomic_DARWIN_PPC_GNU.h"
#elif defined(CIMPLE_PLATFORM_DARWIN_IX86_GNU)
# include "Atomic_DARWIN_IX86_GNU.h"
#elif defined(CIMPLE_PLATFORM_WIN32_IX86_MSVC) || \
    defined(CIMPLE_PLATFORM_WIN64_X86_64_MSVC)
# include "Atomic_WIN32_IX86_MSVC.h"
#elif defined(CIMPLE_PLATFORM_VXWORKS_XSCALE_GNU)
# include "Atomic_VXWORKS_XSCALE_GNU.h"
#elif defined(CIMPLE_PLATFORM_SOLARIS_SPARC_GNU)
# include "Atomic_SOLARIS_SPARC_GNU.h"
#elif defined(CIMPLE_PLATFORM_SOLARIS_IX86_CC) || \
    defined(CIMPLE_PLATFORM_SOLARIS_X86_64_CC)
# include "Atomic_SOLARIS_IX86_CC.h"
#elif defined(CIMPLE_PLATFORM_SOLARIS_SPARC_CC) || \
    defined(CIMPLE_PLATFORM_SOLARIS_SPARC_64_CC)
# include "Atomic_SOLARIS_SPARC_CC.h"
#else
# error "unsupported platform"
#endif

#endif /* _cimple_Atomic_h */
