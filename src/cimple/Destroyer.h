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

#ifndef _cimple_Destroyer_h
#define _cimple_Destroyer_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN

/** This class is used to automatically 'destroy' heap objects when it
    goes out of scope. For example,

	<pre>
	char* str = str_clone("hello");
	Destroyer<char> str_destroyer(str);
	</pre>

    A destroy() function must be defined for each type of object it is used
    with. The prototype must be:

	<pre>
	void destroy(T* p);
	</pre>

    For example, for char, the prototype is:

	<pre>
	void destroy(char* p);
	</pre>
*/
template<class T>
class Destroyer
{
public:

    Destroyer(T* p) : _p(p) 
    {
    }

    ~Destroyer() 
    {
	destroyer(_p);
    }

    T* steal()
    {
	T* tmp = _p;
	_p = 0;
	return tmp;
    }

private:

    Destroyer(const Destroyer&);

    Destroyer& operator=(const Destroyer&);

    T* _p;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Destroyer_h */
