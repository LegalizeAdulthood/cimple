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

#include "DZT_String.h"

CIMPLE_NAMESPACE_BEGIN

DZT_String::DZT_String(const DZT_String& x)
{
    _assign(x);
}

void DZT_String::reserve(size_t n)
{
    if (n > _capacity)
    {
	_str = (char*)realloc(_str, n + 2);
	_capacity = n;
    }
}

void DZT_String::assign(const DZT_String& x)
{
    if (&x != this)
    {
	clear();
	_assign(x);
    }
}

void DZT_String::_assign(const DZT_String& x)
{
    if (x._size)
    {
	_size = x._size;
	_capacity = x._size;
	_str = (char*)malloc(_capacity + 2);
	memcpy(_str, x._str, _size);
	_str[_size] = '\0';
	_str[_size + 1] = '\0';
    }
    else
    {
	_str = 0;
	_size = 0;
	_capacity = 0;
    }
}

char* DZT_String::steal()
{
    char* tmp = _str;
    _str = 0;
    _size = 0;
    _capacity = 0;

    return tmp;
}

void DZT_String::append(const char* s, size_t n)
{
#ifdef CIMPLE_DEBUG

    for (size_t i = 0; i < n; i++)
	CIMPLE_ASSERT(s[i] != '\0');

#endif /* CIMPLE_DEBUG */

    if (_size)
    {
	size_t new_size = _size + 1 + n;

	if (new_size > _capacity)
	    reserve(new_size);

	memcpy(_str + 1 + _size, s, n);
	_size = new_size;
    }
    else
    {
	if (n > _capacity)
	    reserve(n);

	memcpy(_str, s, n);
	_size = n;
    }

    _str[_size] = '\0';
    _str[_size + 1] = '\0';
}

void dzt_next(const char*& str)
{
    char* p = strchr(str, '\0');
    CIMPLE_ASSERT(p != 0 && *p == '\0');
    p++;

    if (*p == '\0')
	str = 0;
    else
	str = p;
}

CIMPLE_NAMESPACE_END
