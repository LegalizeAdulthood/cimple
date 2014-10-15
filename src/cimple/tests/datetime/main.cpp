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

#include <cassert>
#include <cimple/Datetime.h>
#include <cimple/Time.h>

using namespace cimple;

void check_datetime(const char* str)
{
    Datetime dt(str);
    assert(strcmp(str, dt.ascii().c_str()) == 0);
}

int main(int arc, char** argv)
{
    {
        Datetime dt1 = Datetime::now();
        assert(!dt1.is_interval());
        assert(dt1.is_timestamp());

        char buffer1[32];
        dt1.ascii(buffer1);

        uint32 year;
        uint32 month;
        uint32 day;
        uint32 hours;
        uint32 minutes;
        uint32 seconds;
        uint32 microseconds;
        sint32 utc;
        dt1.get_timestamp(
            year, month, day, hours, minutes, seconds, microseconds, utc);

        char buffer2[Datetime::BUFFER_SIZE];
        sprintf(buffer2, "%04d%02d%02d%02d%02d%02d.%06d%s%03d",
            year, month, day, hours, minutes, seconds, microseconds, 
            utc < 0 ? "" : "+", utc);

        assert(strcmp(buffer1, buffer2) == 0);

        Datetime dt2;

        dt2.set_timestamp(
            year, month, day, hours, minutes, seconds, microseconds, utc);

        dt2.get_timestamp(
            year, month, day, hours, minutes, seconds, microseconds, utc);

        assert(dt2.is_timestamp());
        char buffer3[Datetime::BUFFER_SIZE];
        dt2.ascii(buffer3);

        assert(strcmp(buffer1, buffer3) == 0);
        assert(dt1 == dt2);
    }

    {
        Datetime dt1 = Datetime::now();
        assert(dt1.is_timestamp());
        Time::sleep(1000 * 1000);
        Datetime dt2 = Datetime::now();
        assert(dt2.is_timestamp());
        Datetime diff(dt2.usec() - dt1.usec());
        assert(diff.is_interval());
        uint64 msec = diff.usec() / Datetime::MSEC;
        assert(msec >= 800 && msec <= 1200);
        assert(diff.is_interval());

        char buffer[Datetime::BUFFER_SIZE];
        dt2.ascii(buffer);
        Datetime dt3;
        dt3.set(buffer);

        char buffer2[Datetime::BUFFER_SIZE];
        dt3.ascii(buffer2);

        assert(strcmp(buffer, buffer2) == 0);

        assert(dt2 == dt3);
    }

    {
        Datetime in1;
        in1.usec(
            1 * Datetime::DAY +
            2 * Datetime::HOUR + 
            3 * Datetime::MIN +
            4 * Datetime::SEC +
            5 * Datetime::USEC);
        assert(in1.is_interval());

        uint32 days;
        uint32 hours;
        uint32 minutes;
        uint32 seconds;
        uint32 microseconds;
        in1.get_interval(days, hours, minutes, seconds, microseconds);

        assert(days == 1);
        assert(hours == 2);
        assert(minutes == 3);
        assert(seconds == 4);
        assert(microseconds == 5);

        Datetime in2;
        in2.set_interval(days, hours, minutes, seconds, microseconds);
        assert(in2.is_interval());
        assert(in1 == in2);

        uint32 tdays;
        uint32 thours;
        uint32 tminutes;
        uint32 tseconds;
        uint32 tmicroseconds;
        in1.get_interval(tdays, thours, tminutes, tseconds, tmicroseconds);
        assert(tdays == 1);
        assert(thours == 2);
        assert(tminutes == 3);
        assert(tseconds == 4);
        assert(tmicroseconds == 5);

        char buffer[Datetime::BUFFER_SIZE];
        in1.ascii(buffer, false);

        assert(strcmp(buffer, "00000001020304.000005:000") == 0);

        Datetime in3;
        bool flag = in3.set("00000001020304.000005:000");
        assert(flag);

        char buffer2[Datetime::BUFFER_SIZE];
        in3.ascii(buffer2, false);

        assert(in3 == in1);

        assert(strcmp(buffer, buffer2) == 0);
    }

    Datetime now = Datetime::now();

    check_datetime("20070711110702.264323-300");
    check_datetime("20070101120000.123456-360");

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

