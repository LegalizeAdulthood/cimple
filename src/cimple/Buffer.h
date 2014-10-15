/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006 Michael E. Brasher, K. Schopmeyer
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

#ifndef _cimple_Buffer_h
#define _cimple_Buffer_h

#include "config.h"
#include "linkage.h"
#include <cstdarg>

CIMPLE_NAMESPACE_BEGIN

// enable the diagnostic display of the buffer.  This is a diagnostic
// and disabling this will reduce code slightly.  Comment to remove
#define ENABLE_BUFFER_DIAG

//
// The Buffer class implements a simple array of raw types (types that do
// not require construction and deconstruction). It only implements the
// fundamentals:
//   - Append of simple char, string, and integer elements 
//   - Insert of simple char* elements within the buffer
//   - Removal of simple char* elements within the buffer
//   - Set of a single character with a method set()
//   - Append of complex elements created with either a format or vformat
//     function based on printf format definitions
//   - Management of the capacity (allocated space) for the buffer with
//     functions to reserve, and see (capacity()) the buffer capacity by
//     allocating or reallocating space for the buffer.
//   - Manipulate the data size in the buffer with grow() and resize(). This
//     manipulates the size parameter without adding data so that the user
//     is responsible for constructing the data in the buffer using memcpy,etc.
// 
// Buffer manages the space using the malloc allocator.  It establishes a
// minimum space upon the first insertion of data into the buffer (4096 bytes)
// and expands this if the data input is greater than this size.  The buffer
// space is only allocated when the buffer object is destructed.
// 
// Space for data is allocated using an algorithm that reallocates the
// space if the next append or insert will exceed the current capacity. The
// algorithm doubles the  allocated size each time the capacity is
// exceeded. Note that this algorithm does not take into account very
// large buffers so that if the data size gets into the megabyte range, the
// allocator allocates multiple megabytes of space.
// 
// WARNING: This class tests for out-of-bound conditions on functions involving
// and index into the buffer (insert, remove, [], etc. but simply executes
// a CIMPLE_ASSERT if these conditions are encountered.
//  
// WARNING: This class is intended for internal use within CIMPLE. The
// interface definitions may change so any use by provider writers must
// accept this limitation.
//
class CIMPLE_CIMPLE_LINKAGE Buffer
{
public:

    // constructor. constructs an empty buffer. size() == 0
    Buffer();

    /** 
        Copy constructor. Constructs a buffer and copies the data in
        the  buffer defined by the input variable to the new buffer.
        The data is always copied and any existing data in the to
        buffer destroyed.
    */

    Buffer(const Buffer& x);

    /** destructor. Frees the allocated memory for the buffer
    */
    ~Buffer();

    /** 
        Copy constructor. Copies the data in the buffer x to the
        target buffer. The data is always copied and any existing
        data in the target buffer destroyed. Note that this is a
        real copy and that Buffer does not support smart semantics
        like reference counting, etc.
    */
    Buffer& operator=(const Buffer& x);

    /** 
        Return size of data in the buffer.
        @return count of bytes in the buffer.
    */
    size_t size() const;

    // Return current capacity of buffer.
    size_t capacity() const;

    /**
    *  returns const char* pointing to data component of buffer. this
    *  function applies '\0' at end of buffer
    *  @return char* to data in buffer
    */
    const char* data() const;

    /**
     * Return pointer to data component of buffer.  This function 
     * applies '\0' at end of buffer. 
     * @return char* to data in buffer 
     */
    char* data();

    /**
     * Return pointer to the end of the the buffer (position after 
     * the last character in the buffer). 
     * @return char* 
     */
    const char* end() const;

    char* end();

    /**
     * return a single character from the buffer at position defined 
     * by the input parameter. 
     * @param i position of byte to return. 
     * @return char in position i 
     *  
     */
    char operator[](size_t i) const;

    /**
     * sets a single character into the buffer. 
     * @param i position in which to set the character 
     * #param x character to set into the buffer 
     *  
     * Generates a CIMPLE_ASSERT if i is outside of the capacity of 
     * the buffer. 
     */
    void set(size_t i, char x);

    /**
     * Reserves a defined buffer size by reallocating the buffer 
     * space. If the input parameter is smaller than the current 
     * capacity, nothing is changed.  If larger, the buffer space is
     * reallocated. Data in the buffer is maintained. If the new 
     * capacity is less than the defined minimum capacity, the value 
     * is set to the minimum capacity (a CIMPLE compile time 
     * variable defined in Buffer.cpp);
     * @param capacity new size. 
     */
    void reserve(size_t capacity);

    /**
     * Grows the buffer size by the number of bytes defined by 
     * the input parameter. If the sum of the current buffer size 
     * and input size parameter is greater than the current capacity 
     * it increases the buffer capacity. This does not place any 
     * data into the buffer so the data in the grown space is 
     * undefined. A function such as memcpy must be used to insert 
     * data into the buffer. 
     *  
     * @param size size in bytes to grow the buffer capacity. 
     */
    void grow(size_t size);

    /**
     *  Modifies the size parameter of the buffer.  This function
     *  will not set the size less than the current size. If the
     *  size parameter is greater than the current capacity the
     *  buffer capacity is increased. This function does not place
     *  any data into the buffer so that data in the new space is
     *  undefined. A function such as memcopy must be used to
     *  inserted data into the buffer.
     *  
     *  @param size size in bytes of the size parameter of the
     *              buffer.
     */
    void resize(size_t size);

    /**
     * Clears the data from the buffer.  This does not set the 
     * actual data to zero but simply sets the internal size 
     * definition for the buffer to zero. 
     */
    void clear();

    /**
     * Append a single character to the buffer. 
     * @param x char containing the character to be appended to the 
     *          end of the buffer.
     */
    void append(char x);

    /**
     *   Append characters into the buffer from data. The number of
     *   characters is absolutely defined by the size.
     *   @param data char* pointer to data to insert
     *   @param size size_t length to append
     */
    void append(const char* data, size_t size);

    /**
     * Remove a single character from the buffer at the defined 
     * index. Generates CIMPLE_ASSERT if index is out_of_bounds for 
     * the buffer (gt size()) 
     * @param i size_t index defines position in buffer to remove 
     *          character.
     */
    void remove(size_t i);

    /**
     * Remove multiple characters from buffer at defined position. 
     * Generates a CIMPLE_ASSERT if index or index + size are out of 
     * bounds for the buffer (beyond current size() of the buffer). 
     * @param i size_t index to position where characters will be 
     *          removed
     * @param size size_t number of characters to be removed 
     */
    void remove(size_t i, size_t size);

    /**
     * Insert a defined number of characters into the buffer at a 
     * defined position. If the number of characters to be inserted 
     * is more than the current capacilty, the capacity is increased 
     * by reallocating the space for the buffer 
     * @param i size_t position for data to be inserted 
     * @param data char* pointer to the data to be inserted 
     * @param size size_t number of characters to be inserted. 
     */
    void insert(size_t i, const char* data, size_t size);

    /**
     * Append a char* string of characters into the buffer.  Note 
     * that this differs from append in that the length to be 
     * inserted is determined from the input char* string. Executes 
     * the function strlen on the data to determine length so this 
     * can be less efficient that append if there are more 
     * economical ways to determine length. 
     */
    void appends(const char* str);

    CIMPLE_PRINTF_ATTR(2, 3)

    /**
     * Format and append to the buffer the result of the formating 
     * of the format string format and the other parameters. 
     * This is the same structure as the c printf function except 
     * that the output is placed in the buffer. 
     * @param format C format string 
     * @param ... parameters to be formated 
     * @return size_t the number of characters added to the buffer. 
     *  
     */
    size_t format(const char* format, ...);

    /**
     * Format and append characters to the buffer bases on the input 
     * format definition and the va_list parameter. 
     * This would be expected to be used to build new functions that 
     * would generate a va_list. 
     */
    size_t vformat(const char* format, va_list ap);

    /**
     * Append a uint16 integer to the buffer after converting the 
     * integer to a string.  Leading zeros are supressed. 
     * @param x uint16 integer value. 
     */
    void append_uint16(uint16 x);

    /**
     * Append a uint32 integer to the buffer after converting the 
     * integer to a string.  Leading zeros are suppressed. 
     * @param x uint32 integer value. 
     */
    void append_uint32(uint32 x);

    /**
     * Append a uint64 integer to the buffer after converting the 
     * integer to a string.  Leading zeros are suppressed. 
     * @param x uint64 integer value. 
     */
    void append_uint64(uint64 x);

    /**
     * Display the current contents of the buffer in hex and 
     * ascii.  This is a diagnostic tool only 
     */
#ifdef ENABLE_BUFFER_DIAG
    void dump();
#endif

private:
    void _reserve_aux(size_t capacity);
    void _append_aux();

    char* _data;
    size_t _size;
    size_t _cap;
};

inline size_t Buffer::size() const 
{ 
    return _size; 
}

inline size_t Buffer::capacity() const 
{ 
    return _cap; 
}

inline const char* Buffer::data() const 
{
    _data[_size] = '\0';
    return _data; 
}

inline char* Buffer::data() 
{
    _data[_size] = '\0';
    return _data; 
}

inline const char* Buffer::end() const 
{
    return _data + _size;
}

inline char* Buffer::end() 
{
    return _data + _size;
}

inline char Buffer::operator[](size_t i) const
{
    CIMPLE_ASSERT(i < _size);
    return _data[i]; 
}

inline void Buffer::set(size_t i, char x) 
{
    CIMPLE_ASSERT(i < _size);
    _data[i] = x; 
}

inline void Buffer::clear()
{
    _size = 0;
}
// append a single character
inline void Buffer::append(char x)
{
    // if capacity too small, grow by doubling
    if (_size == _cap)
        _append_aux();

    _data[_size++] = x;
}

inline void Buffer::append(const char* data, size_t size)
{
    // if capacity too small, grow with pow_2 to assure
    // we get enough space.
    if(_size + size > _cap)
        _reserve_aux(_size + size);

    memcpy(_data + _size, data, size);
    _size += size;
}

inline void Buffer::appends(const char* str)
{
    append(str, strlen(str));
}

inline void Buffer::remove(size_t i)
{
    remove(i, 1);
}

inline void Buffer::grow(size_t size)
{
    if (_size + size > _cap)
        reserve(_size + size);

    _size += size;
}

inline void Buffer::resize(size_t size)
{
    if (size > _cap)
        reserve(size);

    _size = size;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Buffer_h */
