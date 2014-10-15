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

#define _BSD_SOURCE

#include "config.h"
#include "Atomic.h"
#include <sys/types.h>
#include <cctype>
#include <time.h>
#include "Datetime.h"
#include "Time.h"

#ifdef CIMPLE_VXWORKS
# include <sys/times.h>
#else
# include <sys/time.h>
#endif

CIMPLE_NAMESPACE_BEGIN

const uint64 Datetime::USEC = 1;
const uint64 Datetime::MSEC = 1000;
const uint64 Datetime::SEC = 1000000;
const uint64 Datetime::MIN = 60 * SEC;
const uint64 Datetime::HOUR = 60 * MIN;
const uint64 Datetime::DAY = 24 * HOUR;

static bool _str_to_uint32(const char* s, size_t n, uint32& x)
{
    // ATTN: check for overflow!

    x = 0;
    uint32 r = 1;

    for (const char* p = &s[n]; n--; )
    {
        char c = *--p;

        if (!isdigit(c))
            return false;

        x += r * (c - '0');
        r *= 10;
    }

    return true;
}

struct Datetime_Rep
{
    // Reference count.
    Atomic refs;

    // Microseconds since the epoch if timestamp. Otherwise, microseconds 
    // elapsed since an arbitrary time (interval)..
    uint64 usec;

    // For timestamps, this field is the UTC offset in minutes. For intervals,
    // the field is always zero.
    sint32 offset;

    // Non-zero (1) if timestamp. Otherwise, zero.
    uint32 is_timestamp;

    Datetime_Rep() { Atomic_create(&refs, 1); }
    ~Datetime_Rep() { Atomic_destroy(&refs); }
};

static void _ref(const Datetime_Rep* rep)
{
    if (rep)
        Atomic_inc(&((Datetime_Rep*)rep)->refs);
}

static void _unref(const Datetime_Rep* rep)
{
    if (rep && Atomic_dec_and_test(&((Datetime_Rep*)rep)->refs))
        delete (Datetime_Rep*)rep;
}

Datetime::Datetime()
{
    _rep = new Datetime_Rep;
    _rep->usec = 0;
    _rep->offset = 0;
    _rep->is_timestamp = 0;
}

Datetime::Datetime(const Datetime& x)
{
    _ref(_rep = x._rep);
}

Datetime::Datetime(uint64 usec, sint32 offset)
{
    _rep = new Datetime_Rep;
    _rep->usec = usec;
    _rep->offset = offset;
    _rep->is_timestamp = 1;
}

Datetime::Datetime(uint64 usec)
{
    _rep = new Datetime_Rep;
    _rep->usec = usec;
    _rep->offset = 0;
    _rep->is_timestamp = 0;
}

Datetime::Datetime(const char* str)
{
    _rep = new Datetime_Rep;
    _rep->usec = 0;
    _rep->offset = 0;
    _rep->is_timestamp = 1;

    // If this fails, the Datetime() object will be a zero-timestamp.
    set(str);
}

Datetime::~Datetime()
{
    _unref(_rep);
}

Datetime& Datetime::operator=(const Datetime& x)
{
    if (_rep != x._rep)
    {
        _unref(_rep);
        _ref(_rep = x._rep);
    }
    return *this;
}

void Datetime::set(uint64 usec, sint32 offset)
{
    _cow();
    _rep->usec = usec;
    _rep->offset = offset;
    _rep->is_timestamp = 1;
}

void Datetime::set(uint64 usec)
{
    _cow();
    _rep->usec = usec;
    _rep->offset = 0;
    _rep->is_timestamp = 0;
}

void Datetime::clear()
{
    _cow();
    _rep->usec = 0;
    _rep->offset = 0;
    _rep->is_timestamp = 0;
}

bool Datetime::is_interval() const
{
    return _rep->is_timestamp == 0;
}

bool Datetime::is_timestamp() const
{
    return _rep->is_timestamp == 1;
}

uint64 Datetime::usec() const 
{ 
    return _rep->usec; 
}

void Datetime::usec(uint64 usec) 
{ 
    _rep->usec = usec; 
}

sint32 Datetime::offset() const 
{ 
    return _rep->offset; 
}

void Datetime::offset(sint32 offset) 
{ 
    _rep->offset = offset; 
}

void Datetime::ascii(char buffer[Datetime::BUFFER_SIZE], bool prettify) const
{
    if (is_interval())
    {
        const char* STANDARD_FORMAT =  "%08u%02u%02u%02u.%06u:000";
        const char* PRETTY_FORMAT =  "%08u %02u %02u %02u.%06u:000";

        uint32 seconds = uint32((_rep->usec / SEC) % 60);
        uint32 minutes = uint32((_rep->usec / MIN) % 60);
        uint32 hours = uint32((_rep->usec / HOUR) % 24);
        uint32 days = uint32(_rep->usec / DAY);

        sprintf(
            buffer, 
            prettify ? PRETTY_FORMAT : STANDARD_FORMAT,
            days,
            hours,
            minutes,
            seconds,
            uint32(_rep->usec % 1000000));
    }
    else
    {
        const char* STANDARD_FORMAT =  "%04d%02d%02d%02d%02d%02d.%06d%c%03d";
        const char* PRETTY_FORMAT = "%04d/%02d/%02d %02d:%02d:%02d.%06d%c%03d";

        uint32 year = 0;
        uint32 month = 0;
        uint32 day = 0;
        uint32 hours = 0;
        uint32 minutes = 0;
        uint32 seconds = 0;
        uint32 microseconds = 0;
        sint32 utc = 0;

        get_timestamp(
            year, month, day, hours, minutes, seconds, microseconds, utc);

        sprintf(
            buffer,
            prettify ? PRETTY_FORMAT : STANDARD_FORMAT,
            year,
            month,
            day,
            hours,
            minutes,
            seconds,
            microseconds,
            _rep->offset < 0 ? '-' : '+', /* sign */
            utc < 0 ? -utc : utc);
    }
}

String Datetime::ascii(bool prettify) const
{
    char buffer[Datetime::BUFFER_SIZE];
    ascii(buffer, prettify);
    return String(buffer);
}

void Datetime::get_interval(
    uint32& days, 
    uint32& hours, 
    uint32& minutes, 
    uint32& seconds, 
    uint32& microseconds)
{
    seconds = uint32((_rep->usec / SEC) % 60);
    minutes = uint32((_rep->usec / MIN) % 60);
    hours = uint32((_rep->usec / HOUR) % 24);
    days = uint32(_rep->usec / DAY);
    microseconds = uint32(_rep->usec % 1000000);
}

void Datetime::set_interval(
    uint32 days, 
    uint32 hours, 
    uint32 minutes, 
    uint32 seconds, 
    uint32 microseconds)
{
    _cow();

    _rep->usec = 
        days * DAY +
        hours * HOUR +
        minutes * MIN +
        seconds * SEC +
        microseconds;
    _rep->offset = 0;
    _rep->is_timestamp = 0;
}

void Datetime::get_timestamp(
    uint32& year, 
    uint32& month, 
    uint32& day, 
    uint32& hours, 
    uint32& minutes,
    uint32& seconds,
    uint32& microseconds,
    sint32& utc) const
{
    time_t t = (_rep->usec / 1000000);
    struct tm* tm;

#ifdef CIMPLE_WINDOWS
    tm = localtime(&t);
#else
    struct tm tmp;
    localtime_r(&t, &tmp);
    tm = &tmp;
#endif

    year = tm->tm_year + 1900;
    month = tm->tm_mon + 1;
    day = tm->tm_mday;
    hours = tm->tm_hour;
    minutes = tm->tm_min;
    seconds = tm->tm_sec;
    microseconds = uint32(_rep->usec % 1000000);
    utc = _rep->offset;
}

void Datetime::set_timestamp(
    uint32 year, 
    uint32 month, 
    uint32 day, 
    uint32 hours, 
    uint32 minutes,
    uint32 seconds,
    uint32 microseconds,
    sint32 utc)
{
    _cow();

    struct tm tm;
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hours;
    tm.tm_min = minutes;
    tm.tm_sec = seconds;
    tm.tm_isdst = -1;

    time_t t = mktime(&tm);
    _rep->usec = uint64(t) * uint64(1000000) + microseconds;
    _rep->offset = utc;
    _rep->is_timestamp = 1;
}

void Datetime::print(FILE* os, bool prettify) const
{
    char buffer[32];
    ascii(buffer, prettify);
    fprintf(os, "%s\n", buffer);
}

Datetime Datetime::now()
{
#ifdef CIMPLE_WINDOWS
    struct posix::timeval tv;
#else
    struct timeval tv;
#endif

    struct timezone tz;

    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return Datetime(uint64(0));

    uint64 usec = uint64(tv.tv_sec) * uint64(1000000) + tv.tv_usec;
    sint32 offset = tz.tz_minuteswest;

    return Datetime(usec, -offset);
}

bool Datetime::set(const char* str)
{
    _cow();

    if (strlen(str) != 25)
        return false;

    char sign = str[21];

    if (sign == ':')
    {
        // It's an interval:

        // ddddddddhhmmss.mmmmmm:000

        uint32 days;
        uint32 hours;
        uint32 minutes;
        uint32 seconds;
        uint32 microseconds;

        if (!_str_to_uint32(str, 8, days))
            return false;

        if (!_str_to_uint32(str + 8, 2, hours))
            return false;

        if (!_str_to_uint32(str + 10, 2, minutes))
            return false;

        if (!_str_to_uint32(str + 12, 2, seconds))
            return false;

        if (str[14] != '.')
            return false;

        if (!_str_to_uint32(str + 15, 6, microseconds))
            return false;

        if (str[22] != '0' || str[23] != '0' || str[24] != '0')
            return false;

        set_interval(days, hours, minutes, seconds, microseconds);

        _rep->is_timestamp = 0;
        return true;
    }
    else if (sign == '+' || sign == '-')
    {
        // It's a timestamp.

        // yyyymmddhhmmss.mmmmmmsutc

        uint32 year;
        uint32 month;
        uint32 day;
        uint32 hours;
        uint32 minutes;
        uint32 seconds;
        uint32 microseconds;
        uint32 utc;

        if (!_str_to_uint32(str, 4, year))
            return false;

        if (!_str_to_uint32(str + 4, 2, month))
            return false;

        if (!_str_to_uint32(str + 6, 2, day))
            return false;

        if (!_str_to_uint32(str + 8, 2, hours))
            return false;

        if (!_str_to_uint32(str + 10, 2, minutes))
            return false;

        if (!_str_to_uint32(str + 12, 2, seconds))
            return false;

        if (str[14] != '.')
            return false;

        if (!_str_to_uint32(str + 15, 6, microseconds))
            return false;

        if (!_str_to_uint32(str + 22, 3, utc))
            return false;

        set_timestamp(
            year, month, day, hours, minutes, seconds, microseconds,
            (sign == '+') ? utc : -sint32(utc));

        _rep->is_timestamp = 1;
        return true;
    }

    return false;
}

void Datetime::_cow()
{
    if (Atomic_get(&_rep->refs) != 1)
    {
        Datetime_Rep* rep = new Datetime_Rep;
        rep->usec = _rep->usec;
        rep->offset = _rep->offset;
        rep->is_timestamp = _rep->is_timestamp;
        _unref(_rep);
        _rep = rep;
    }
}

CIMPLE_NAMESPACE_END

