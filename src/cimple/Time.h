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

#ifndef _cimple_Time_h
#define _cimple_Time_h

#include "config.h"

/*
ATTN: get rid of this!
*/
#if defined(CIMPLE_PLATFORM_SOLARIS_SPARC_GNU)
# ifdef SEC
#  undef SEC
# endif
#endif

CIMPLE_NAMESPACE_BEGIN

struct CIMPLE_CIMPLE_LINKAGE Time
{
public:

    /// Static constant to define one micosecond as uint64 variable
    static const uint64 USEC;
    /// static constant to define one millisecond as uint64 variable
    static const uint64 MSEC;

    /// static constant to define one second as uint64 variable
    static const uint64 SEC;
    
    /** Returns microseconds elapsed since POSIX epoch (1970).
     * @return uint64 microseconds elapsed sinc POXIX epoch
     */
    static uint64 now();

    /**
     * Sleep the current process/thread for the time defined by the 
     * input variable. 
     * timeout_usec uint64 microseconds to sleep. 
     *  
     * EXAMPLE: 
     * \code 
     *     time::sleep(time::SEC * number_of_Seconds);
     * \endcode
     */
    static void sleep(uint64 timeout_usec);
private:
    // Private constructor to keep user from using constructor
    Time(){};
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Time_h */
