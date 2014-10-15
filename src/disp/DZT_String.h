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

#ifndef _cimple_DZT_String_h
#define _cimple_DZT_String_h

#include <cimple/config.h>

CIMPLE_NAMESPACE_BEGIN

/** This class manages a double-zero-terminated (DZT) string. For example,

	<pre>
	"Monday\0Tuesday\0Wednesday\0Thursday\0Friday\0Saturday\0Sunday\0\0"
	</pre>

    A DZT string is terminated with a double zero character and may contain 
    single zero characters. This scheme is used to compactly represent lists of
    non-empty strings.

    The DZT_String class is mainly used to build up DZT strings. The steal()
    method provides a way to grab the string from the DZT and use it directly.

    DZT strings can be iterated using the DZT::next() method like this:

	<pre>
	const char* dzt_str;
	...
	for (const char* p = dzt_str; p; dzt_next(p))
	{
	    // p points to current element.
	}
	</pre>
*/
class DZT_String
{
public:

    DZT_String();

    DZT_String(const DZT_String& s);

    ~DZT_String();

    void clear();

    const char* str() const;

    size_t size() const;

    size_t capacity() const;

    void reserve(size_t n);

    void assign(const DZT_String& x);

    DZT_String& operator=(const DZT_String& x);

    void append(const char* s);

    void append(const char* s, size_t n);

    char* steal();

private:

    void _assign(const DZT_String& s);

    char* _str;

    // Size (without the DZT).
    size_t _size;

    // Capacity (without the DZT).
    size_t _capacity;
};

inline DZT_String::DZT_String() : _str(0), _size(0), _capacity(0)
{
}

inline DZT_String::~DZT_String()
{
    free(_str);
}

inline const char* DZT_String::str() const
{
    return _str;
}

inline size_t DZT_String::size() const
{
    return _size;
}

inline size_t DZT_String::capacity() const
{
    return _capacity;
}

inline void DZT_String::clear()
{
    free(_str);
    _str = 0;
    _size = 0;
    _capacity = 0;
}

inline DZT_String& DZT_String::operator=(const DZT_String& x)
{
    assign(x);
    return *this;
}

inline void DZT_String::append(const char* s)
{
    append(s, strlen(s));
}

void dzt_next(const char*& str);

CIMPLE_NAMESPACE_END

#endif /* _cimple_DZT_String_h */
