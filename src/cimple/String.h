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

#ifndef _cimple_String_h
#define _cimple_String_h

#include <cstring>
#include "config.h"
#include "Atomic.h"
#include "flags.h"
#include "Strings.h"

CIMPLE_NAMESPACE_BEGIN

struct __String_Rep
{
    Atomic refs;
    uint32 size;
    uint32 cap;
    char data[1];
    __String_Rep() { Atomic_create(&refs, 2); }
};
/** 
 * The String class implements strings that are CIM compatible
 * and usable with the CIMPLE String CIM type.  In implements a
 * set of methods to create, manipulate, and convert Strings
 * that can be used increation of CIMPLE instances from CIMPLE
 * instances.
 * 
 */
class CIMPLE_CIMPLE_LINKAGE String
{
public:

    /** 
     * CIMPLE String Constructor. Creates an empty CIMPLE String
     * 
     */
    String();

    /** 
     * Constructs a String with the value of another String.
     * 
     * @param s String from which to copy the value
     */
    String(const String& s);

    /** 
     * Constructs a String from a char* defined C string.
     * 
     * @param s Char* string from which to copy the value.
     */
    String(const char* s);

    /** 
     * Constructs a String from two char* input C string parameters 
     * @param s1 First char* input value
     *  @param s2 Second char* input value
     */
    String(const char* s1, const char* s2);

    /** 
     * Constructs a String from three char* input C string 
     * parameters, appending them into a single String 
     * 
     * @param s1 First char* input value
     * @param s2 Second char* input value
     * @param s3 Third char8 input value
     */
    String(const char* s1, const char* s2, const char* s3);

    /** 
    * Constructs a string with a specified number of characters of
    * the value of a char* parameter.
    * 
    * @param s char* C string from which to take value.
    * @param n size_t value defining the number of characters to be
    *          copied.
    */
    String(const char* s, size_t n);

    /** 
     * String destructor
     * 
     */
    ~String();

    /** 
     * Reserves memory for a specified number of characters in a 
     * String object.  This method does not change the size() of the
     * String or any external behavior. If the size of the String is 
     * already greater than n the mehtod has no effect. The reserve 
     * size for a String is only set for performance reasons 
     * 
     * @param n Numbe of characters the String should be prepared to 
     *          hold.
     */
    void reserve(size_t n);

    /** 
     * Assigns the value of one String to another String.  
     * 
     * @param s String from which to copy the value.
     */
    void assign(const String& s);

    /** 
     * assign the value of a C string to a String 
     * 
     * @param s char* C string from which value is copied
     * @param n Number of characters to copy
     */
    void assign(const char* s, size_t n);

    ///
    void assign(const char* s);

    ///
    void append(const String& s);

    /** 
     * Append a C string to a String
     * 
     * @param s char* from which the characters are copied.
     */
    void append(const char* s);

    /** 
     * Append a specified number of characters from a C string to 
     * a String. 
     * 
     * @param s char8 C string from which the characters are copied
     * @param n size_t Number of characters to copy.
     */
    void append(const char* s, size_t n);

    /** 
     * Append a single character to a String
     * 
     * @param c char representing the character to be appended
     */
    void append(char c);

    /** 
     * Remove a specified number of characters from a String 
     * starting at a specified position in the String 
     * 
     * @param pos size_t position to start removing characters
     * @param n Number of characters to remove
     */
    void remove(size_t pos, size_t n);

    /** 
     * Create a new String that is a substring of a String 
     * containing the characters from a specified position in the 
     * string for up to a specified length. This method executes a 
     * CIMPLE_ASSERT if the parameters request a substring outside 
     * the size of the String. 
     * 
     * @param pos Position in the String to start the substring
     * @param n Number of characters to copy to the new String. This 
     *          parameter is optional. If not defined, returns all
     *          characters to the end of String.
     * 
     * @return String Substring created.
     */
    String substr(size_t pos, size_t n = size_t(-1));

    /** 
     * Assign one String to another.
     * 
     * @param s
     * 
     * @return String&
     */
    String& operator=(const String& s);

    /** 
     * Assign a C string to a String
     * 
     * @param s
     * 
     * @return String&
     */
    String& operator=(const char* s);

    /** 
     * Sets a string to zero length
     * 
     */
    void clear();

    /** 
     * Returns a pointer to the C string representing a String.
     * 
     * @return const char* C string value of the String
     */
    const char* c_str() const;

    /** 
     * Returns the number of characters in a String.
     * 
     * 
     * @return size_t Number of characters in a String
     */
    size_t size() const;

    /** 
     * Determine if a String is empty. 
     * 
     * 
     * @return bool Returns true if the string contains no data, 
     *         else returns false.
     */
    bool empty() const;

    /** 
     * Returns the capacity of the the String.
     * 
     * 
     * @return size_t
     */
    size_t capacity() const;

    /** 
     * Operator to access a particular character of a string. If the 
     * index is greater than than the number of characters in the 
     * String CIMPLE generates a CIMPLE_ASSERT. Please test  String 
     * sizes as part of using this operation. Note that a 
     * CIMPLE_ASSERT generates an assert when CIMPLE_DEBUG is set 
     * but is completely ignored when CIMPLE_DEBUG is not set 
     * 
     * @param i position in the String for the character to be 
     *          accessed (zero origin).
     * 
     * @return char Returns the character specified by the position 
     *         parameter
     */
    char operator[](size_t i) const;

    /** 
     * Sets input character in the specified index of the String. If 
     * the index is greater than the String size, this method 
     * generates a CIMPLE_ASSERT. 
     * 
     * @param i index within the String in which to insert the 
     *          character.
     * @param c Input character to insert into the String.
     */
    void set(size_t i, char c);

    /** 
     * Test for equality between with another String
     * 
     * @param s String to test against. 
     *  
     * @return bool true if the two Strings are equal.
     */
    bool equal(const String& s) const;

    /** 
     * Test for equality with a C string
     * 
     * @param s
     * 
     * @return bool
     */
    bool equal(const char* s) const;

    /** 
     * Test for equality with a C string for the first n characters 
     * of the String 
     * 
     * @param s
     * @param n
     * 
     * @return bool
     */
    bool equal(const char* s, size_t n) const;

    /** 
     * Test for equality of a substring of the String against an 
     * another C string. 
     * 
     * @param pos
     * @param s
     * @param n
     * 
     * @return bool
     */
    bool equal(size_t pos, const char* s, size_t n) const;

    /** 
     * Test for case insensitive equality with a String
     * 
     * @param s
     * 
     * @return bool
     */
    bool equali(const String& s) const;

    /** 
     * Test for case insensitive equality with a C string.
     * 
     * @param s
     * 
     * @return bool
     */
    bool equali(const char* s) const;

    /** 
     * Test for case insensitive equality with a specified number of 
     * characters of a C string.
     * 
     * @param s
     * @param n
     * 
     * @return bool
     */
    bool equali(const char* s, size_t n) const;

    /** 
     *  Finds the index of the first occurrence of a specified character in
     *   the String. returns -1 if the character is not found.
     * 
     * @param c Charcter to match
     * 
     * @return size_t If the character is found returns the zero 
     *         origin index to the first incidence of the character
     *         in the String. If it is not found, returns -1.
     */
    size_t find(char c) const;

    /** 
     * Finds the index of the first occurence of a specified 
     * character in the String starting at a defined position in the 
     * string. 
     * 
     * @param c Character to match
     * @param n Starting position in the String to test
     * 
     * @return size_t If the character is found returns the zero 
     *         origin index to the first incidence of the character
     *         in the String. If it is not found, returns -1.
     */
    size_t find(char c, size_t n) const;

    /** 
     * Return pointer to substring of C string defined by input 
     * parameter. 
     * 
     * @param s char C string defining substring to be matched.
     * 
     * @return size_t If the substring is found returns the zero 
     *         origin index to the first incidence of the substring
     *         in the String. If it is not found, returns -1
     */
    size_t find(const char* s) const;
    /** 
     * Return pointer to substring of String defined by input 
     * parameter. 
     * 
     * @param s String defining substring to be matched.
     * 
     * @return size_t If the substring is found returns the zero 
     *         origin index to the first incidence of the substring
     *         in the String. If it is not found, returns -1
     */
    size_t find(const String& s) const;

private:
    __String_Rep* _rep;
    static __String_Rep _empty;
    friend void _ref(const __String_Rep* rep);
    friend void _unref(const __String_Rep* rep);
};

/******************************************************************************
**
**  inline definition of those functions that are faster with inline 
**  implementations.
**
*******************************************************************************/
inline String::String() : _rep(&_empty)
{
}

inline String& String::operator=(const String& s)
{
    assign(s);
    return *this;
}

inline String& String::operator=(const char* s)
{
    assign(s);
    return *this;
}

inline const char* String::c_str() const
{
    return _rep->data;
}

inline size_t String::size() const
{
    return _rep->size;
}

inline bool String::empty() const
{
    return _rep->size == 0;
}

inline size_t String::capacity() const
{
    return _rep->cap;
}

inline char String::operator[](size_t i) const
{
    CIMPLE_ASSERT(i <= _rep->size);
    return _rep->data[i];
}

inline bool operator==(const String& s1, const String& s2)
{
    return s1.equal(s2);
}

inline bool operator==(const String& s1, const char* s2)
{
    return s1.equal(s2);
}

inline bool operator==(const char* s1, const String& s2)
{
    return s2.equal(s1);
}

inline bool operator!=(const String& s1, const String& s2)
{
    return !operator==(s1, s2);
}

inline bool operator!=(const String& s1, const char* s2)
{
    return !operator==(s1, s2);
}

inline bool operator!=(const char* s1, const String& s2)
{
    return !operator==(s1, s2);
}

inline bool eqi(const String& s1, const String& s2)
{
    return eqi(s1.c_str(), s2.c_str());
}

inline bool eqi(const String& s1, const char* s2)
{
    return eqi(s1.c_str(), s2);
}

inline bool eqi(const char* s1, const String& s2)
{
    return eqi(s1, s2.c_str());
}

inline void __clear(String& x) 
{ 
    x.clear(); 
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_String_h */
