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

#ifndef _MOF_Buffer_h
#define _MOF_Buffer_h

#include "MOF_Config.h"

/** Simple dynamic buffer.
*/
class MOF_LINKAGE MOF_Buffer
{
public:

    /** Constructor. 
    */
    MOF_Buffer() : _data(0), _size(0), _capacity(0) { }

    /** Destructor.
    */
    ~MOF_Buffer() { free(_data); }

    /** Reserves memory for capacity bytes (has no effect on size).
    */
    void reserve(size_t capacity);

    /** Appends size bytes to the end of the buffer, increasing the size
        by size bytes.
    */
    void append(const char* data, size_t size);

    /** Appends a single byte to the end of the buffer, increasing the size
        by one.
    */
    void append(const char ch) { append(&ch, 1); }

    /** Returns a pointer to the buffer.
    */
    const char* data() const { return _data; }

    /** Returns the size of the buffer.
    */
    size_t size() const { return _size; }

    /** Returns the capacity of the buffer.
    */
    size_t capacity() const { return _capacity; }

    /** Steals the internal buffer from this instance (helps prevent an
        unecessary allocation in certain cases). After calling this, the
        buffer is empty as though it was freshly constructed.
    */
    char* steal_data();

private:

    /** Keep clients from calling this.
    */
    MOF_Buffer& operator=(const MOF_Buffer&) { return *this; }

    /** Keep clients from calling this.
    */
    MOF_Buffer(const MOF_Buffer&) { }

    char* _data;
    size_t _size;
    size_t _capacity;
};

#endif /* _MOF_Buffer_h */
