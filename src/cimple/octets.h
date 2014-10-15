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

#ifndef _cimple_octets_h
#define _cimple_octets_h

#include "Strings.h"
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

/*  The functions in this file are used to translate between
    OctetStrings as received defined in the CIM Infrastructure
    specification with the OctetString Qualifier and an internal form
    useful for direct access to the data in the OctetString.  Today
    these functions are used only to convert between the array of
    strings form for Octet strings, not the alternate form (array of
    uint8). Note that we handle only single strings.  The mapping of the
    array itself is left to the user.
 */

/** This function converts an octet string to a String object. The #data#
    parameter is a pointer to an octet string with #size# octets.
    This function returns a string that conforms to the following 
    grammar.

        "0x"4*(<hexDigit><hexDigit>)

    For example, the following octet string:

        01 02 03 04

    is encoded as follows ("0x00000008" followed by "01020304").

        0x0000000801020304

    The leading "0x00000008" gives the total number of hex digits in the 
    encoding.

    The empty octet string is encoded as follows.

        0x00000004

    Note that there are a total 4 hex digits in this encoding.
*/
CIMPLE_CIMPLE_LINKAGE String octets_to_string(
    const unsigned char* data, 
    uint32 size);

/** This function converts a String object to an octet string. Note that
    the string must conform to the standard encoding described in
    octets_to_string(). The #str# parameter contains the text string to be 
    converted. Up to #size# octets are written to the #data# parameter.

    This function returns -1 if the string encoding is invalid. Otherwise
    it returns the size of the encoded string.  A return value larger than
    #size# indicates that #data# was too small to receive the resulting 
    octet string. In that case, string_to_octets() will succeed if called 
    again with a #size# parameter that is at least as large as the initial
    return value.
*/
CIMPLE_CIMPLE_LINKAGE ssize_t string_to_octets(
    const String& str, 
    unsigned char* data, 
    uint32 size);

/** This function is a simpler form of string_to_octets(), which leaves
    the resulting octets in an array of unsigned chars. It returns -1 if the
    the string encoding is invalid. Otherwise it returns 0. We recommend that
    the user use this rather than octets_to_string() above because of its
    simpler interface.
*/
CIMPLE_CIMPLE_LINKAGE int string_to_octets(
    const String& str, 
    Array<unsigned char>& octets);

CIMPLE_NAMESPACE_END

#endif /* _cimple_octets_h */
