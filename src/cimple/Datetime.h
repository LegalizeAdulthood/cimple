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

CIMPLE_NAMESPACE_BEGIN

/** This class represents either a timestamp or an interval (as specified by 
    the CIM Infrastructure Specification). It encapsulates two members: usec
    and offset. The meaning of these depends on whether it represents a 
    timestamp or an interval.

    For timestamps, usec is the number of microseconds transpired since
    the epoch (January 1970, 00:00:00) in local time and offset is the 
    number of minutes the time is offset from GMT.

    For intervals, usec is the number of microseconds in the interval and
    offset is CIMPLE_SINT32_MAX.

    The is_interval() method is used to determine whether the Datetime
    represents a timestamp or an interval.

    The Datetime::now() method constructs a timestamp with the current 
    time. For example,

    	<pre>
	Datetime dt = Datetime::now();
    	</pre>

    This class was designed to interact easily with the POSIX date/time
    routines. For example, time() obtains the number of seconds transpired
    since the epoch. Multiply this quantity by one million to calculate
    the Datetime usec member. For finer granularity, use gettimeofday().

    This class does not represent time as individual time components
    (i.e., years, months, hours, minutes). Instead time is represented
    by a larger integer that holds the number of microseconds. This makes 
    it easier to find the difference between two times and to compare them.
*/
struct CIMPLE_LIBCIMPLE_LINKAGE Datetime
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

    /** Sets object to represet the zero interval (same as 
        Datetime(0, CIMPLE_SINT32_MAX).
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

    /** Returns true if this object represents an interval (i.e.,
	offset is CIMPLE_SINT32_MAX).
    */
    bool is_interval() const;

    /** Returns true if this object represents a timestamp (i.e.,
	offset is not CIMPLE_SINT32_MAX).
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

	    <pre>
	    ddddddddhhmmss.mmmmmm:000
	    <pre>

	For example,

	    <pre>
	    00000000112233.444444:000
	    <pre>

	Timestamps are formatted like this.

	    <pre>
	    yyyymmddhhmmss.mmmmmmsutc
	    </pre>

	For example,

	    20050710170840.899256+300

	If the prettify flag is true, the format is somewhat more readable.
    */
    void ascii(char buffer[Datetime::BUFFER_SIZE], bool prettify = false) const;

    /** Print object to stream parameter.
    */
    void print(FILE* os = stdout, bool prettify = false);

    /** Factory method that produces the current timestamp().
    */
    static Datetime now();

private:

    /** Microseconds since the epoch if timestamp. Otherwise, this is the
        microseconds elapsed since an arbitrary time.
    */
    uint64 _usec;

    /** For timestamps, this field is the UTC offset in minutes. For intervals,
	the field is equal to CIMPLE_SINT32_MAX.
    */
    sint32 _offset;
};

inline Datetime::Datetime() : _usec(0), _offset(CIMPLE_SINT32_MAX) 
{ 
}

inline Datetime::Datetime(const Datetime& x) 
    : _usec(x._usec), _offset(x._offset)
{
}

inline Datetime::Datetime(uint64 usec, sint32 offset)
    : _usec(usec), _offset(offset)
{
}

inline Datetime::Datetime(uint64 usec)
    : _usec(usec), _offset(CIMPLE_SINT32_MAX)
{
}

inline Datetime& Datetime::operator=(const Datetime& x)
{
    _usec = x._usec;
    _offset = x._offset;
    return *this;
}

inline void Datetime::set(uint64 usec, sint32 offset)
{
    _usec = usec;
    _offset = offset;
}

inline void Datetime::set(uint64 usec)
{
    _usec = usec;
    _offset = CIMPLE_SINT32_MAX;
}

inline void Datetime::clear()
{
    _usec = 0;
    _offset = CIMPLE_SINT32_MAX;
}

inline bool Datetime::is_interval() const
{
    return _offset == CIMPLE_SINT32_MAX;
}

inline bool Datetime::is_timestamp() const
{
    return _offset != CIMPLE_SINT32_MAX;
}

inline uint64 Datetime::usec() const 
{ 
    return _usec; 
}

inline void Datetime::usec(uint64 usec) 
{ 
    _usec = usec; 
}

inline sint32 Datetime::offset() const 
{ 
    return _offset; 
}

inline void Datetime::offset(sint32 offset) 
{ 
    _offset = offset; 
}

inline bool operator==(const Datetime& x, const Datetime& y)
{
    return x.usec() == y.usec() && x.offset() == y.offset();
}

inline void clear(Datetime& x) 
{ 
    x.clear(); 
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Datetime_h */
