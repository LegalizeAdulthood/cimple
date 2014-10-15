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

#include <cimple/config.h>
#include "TLS.h"
#include "Auto_Mutex.h"

CIMPLE_NAMESPACE_BEGIN

TLS::TLS() : _initialized(0)
{
}

TLS::~TLS()
{
    Auto_Mutex auto_mutex(_lock);
    pthread_key_delete(_key);
}

void TLS::_create()
{
    // Using double-checked locking pattern. This function must be called
    // like this:
    // 
    //     if (_initialized == 0)
    //         _create();
    //
    // If _initialized is non-zero, we can avoid calling this function
    // altogether.

    Auto_Mutex auto_mutex(_lock);

    if (_initialized == 0)
    {
	if (pthread_key_create(&_key, NULL) != 0)
	    assert(0);

	_initialized = 1;
    }
}

CIMPLE_NAMESPACE_END
