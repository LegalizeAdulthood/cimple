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

#ifndef _cimple_Datetime_h
#define _cimple_Datetime_h

#include "config.h"
#include "String.h"

/*
ATTN: get rid of this!
*/
#if defined(CIMPLE_PLATFORM_SOLARIS_SPARC_GNU)
# ifdef SEC
#  undef SEC
# endif
#endif

CIMPLE_NAMESPACE_BEGIN

/** This class represents either a timestamp or an interval (as specified by 
    the CIM Infrastructure Specification). It encapsulates three members: usec
    offset, and is_timestamp. The meaning of these depends on whether it 
    represents a timestamp or an interval.

    For timestamps, usec is the number of microseconds transpired since
    the epoch (January 1970, 00:00:00) in local time and offset is the 
    number of minutes the time is offset from GMT, and is_timestamp is 1.

    For intervals, usec is the number of microseconds in the interval and
    offset is zero, and is_timestamp is 0.

    The is_timestamp() method returns true if the object represents an
    timestamp. The is_interval() method returns true if the object represents 
    an interval.

    The Datetime::now() method constructs a timestamp with the current 
    time. For example,

        \code
        Datetime dt = Datetime::now();
        \endcode

    This class was designed to interact easily with the POSIX date/time
    routines. For example, time() obtains the number of seconds transpired
    since the epoch. Multiply this quantity by one million to calculate
    the Datetime usec member. For finer granularity, use gettimeofday().

    This class does not represent time as individual time components
    (i.e., years, months, hours, minutes). Instead time is represented
    by a 64-bit integer that holds the number of microseconds. This makes 
    it easier to find the difference between two times and to compare them.
*/
struct CIMPLE_CIMPLE_LINKAGE Datetime
{
    static const uint64 USEC;
    static const uint64 MSEC;
    static const uint64 SEC;
    static const uint64 MIN;
    static const uint64 HOUR;
    static const uint64 DAY;

    enum { BUFFER_SIZE = 32 };

    /** Default constructor.
    */
    Datetime();

    /** Copy constructor.
    */
    Datetime(const Datetime& x);

    /** Initializing constructor (timestamps).
    */
    Datetime(uint64 usec, sint32 offset);

    /** Initializing constructor (intervals).
    */
    Datetime(uint64 usec);

    /** Initializing constructor (character string).
    */
    explicit Datetime(const char* str);

    /** Destructor.
    */
    ~Datetime();

    /** Assignment operator.
    */
    Datetime& operator=(const Datetime& x);

    /** Sets usec and offset members (timestamps).
    */
    void set(uint64 usec, sint32 offset);

    /** Sets usec and offset members (intervals).
    */
    void set(uint64 usec);

    /** Set from a string of the form: "ddddddddhhmmss.mmmmmm:000" or
         yyyymmddhhmmss.mmmmmmsutc. Return true if successful.
    */
    bool set(const char* str);

    /** Sets object to represet the zero interval.
    */
    void clear();

    /** Gets the components of an interval. The behavior is undefined it not
        an interval.
    */
    void get_interval(
        uint32& days, 
        uint32& hours, 
        uint32& minutes, 
        uint32& seconds, 
        uint32& microseconds);

    /** Sets the interval from its components.
    */
    void set_interval(
        uint32 days, 
        uint32 hours, 
        uint32 minutes, 
        uint32 seconds, 
        uint32 microseconds);

    /** Gets the components of a timestamp. The behavior is undefined if not
        a timestamp.
    */
    void get_timestamp(
        uint32& year, 
        uint32& month, 
        uint32& day, 
        uint32& hours, 
        uint32& minutes,
        uint32& seconds,
        uint32& microseconds,
        sint32& utc) const;

    /** Sets the timestamp from components.
    */
    void set_timestamp(
        uint32 year, 
        uint32 month, 
        uint32 day, 
        uint32 hours, 
        uint32 minutes,
        uint32 seconds,
        uint32 microseconds,
        sint32 utc);

    /** Returns true if this object represents an interval.
    */
    bool is_interval() const;

    /** Returns true if this object represents a timestamp.
    */
    bool is_timestamp() const;

    /** Accessor.
    */
    uint64 usec() const;

    /** Modifier.
    */
    void usec(uint64 usec);

    /** Accessor.
    */
    sint32 offset() const;

    /** Modifier.
    */
    void offset(sint32 offset);

    /** Converts to ASCII representation. Intervals are printed with the 
        following format.

            \verbatim
            ddddddddhhmmss.mmmmmm:000
            \endverbatim

        For example,

            \verbatim
            00000000112233.444444:000
            \endverbatim

        Timestamps are formatted like this.

            \verbatim
            yyyymmddhhmmss.mmmmmmsutc
            \endverbatim

        For example,

            \verbatim
            20050710170840.899256+300
            \endverbatim

        If the prettify flag is true, the format is somewhat more readable.
    */
    void ascii(char buffer[Datetime::BUFFER_SIZE], bool prettify = false) const;

    /** Similar to ascii() above, but returns String result.
    */
    String ascii(bool prettify = false) const;

    /** Print object to stream parameter.
    */
    void print(FILE* os = stdout, bool prettify = false) const;

    /** Factory method that produces the current timestamp().
    */
    static Datetime now();

private:

    void _cow();

    struct Datetime_Rep* _rep;
};

inline bool operator==(const Datetime& x, const Datetime& y)
{
    return 
        x.usec() == y.usec() && 
        x.offset() == y.offset() &&
        x.is_timestamp() == y.is_timestamp();
}

inline void __clear(Datetime& x) 
{ 
    x.clear(); 
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Datetime_h */
