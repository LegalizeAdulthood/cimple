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

#ifndef _cimple_Auto_Mutex_h
#define _cimple_Auto_Mutex_h

#include "config.h"
#include "Mutex.h"

CIMPLE_NAMESPACE_BEGIN

class Auto_Mutex
{
public:

    Auto_Mutex(Mutex& mutex);

    ~Auto_Mutex();

private:

    Auto_Mutex(const Auto_Mutex&);
    Auto_Mutex& operator=(const Auto_Mutex&);

    Mutex& _mutex;
};

inline Auto_Mutex::Auto_Mutex(Mutex& mutex) : _mutex(mutex) 
{ 
    _mutex.lock(); 
}

inline Auto_Mutex::~Auto_Mutex() 
{ 
    _mutex.unlock(); 
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Auto_Mutex_h */
