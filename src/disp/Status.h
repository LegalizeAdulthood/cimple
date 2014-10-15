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

#ifndef _cimple_Status_h
#define _cimple_Status_h

#include <cimple/config.h>
#include "linkage.h"

#define CIMPLE_ASSERT_STATUS(status) \
    do \
    { \
	if (status != STATUS_OK) \
	{ \
	    fprintf(stderr, "CIMPLE_ASSERT_STATUS: %s(%d): %s\n", \
		__FILE__, __LINE__, Status_to_string(status)); \
	    exit(1); \
	} \
    } \
    while (0)

CIMPLE_NAMESPACE_BEGIN

/** These are the stasuses returned by the methods of the Dispatcher class.
*/
enum Status
{
    STATUS_OK,
    STATUS_DONE,
    STATUS_FAILED,
    STATUS_NOT_FOUND,
    STATUS_ALREADY_EXISTS,
    STATUS_UNSUPPORTED,
    STATUS_UNKNOWN_CLASS,
    STATUS_UNKNOWN_METHOD,
};

CIMPLEDISP_LINKAGE extern const char* __status_messages[];

inline const char* Status_to_string(Status status)
{
    return __status_messages[int(status)];
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Status_h */
