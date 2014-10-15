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

#include "UUID.h"
#include "MAC.h"
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// This module implements the DCE UUID variant.
//
//==============================================================================

// Defined by the DCE UUID Variation Specification.
struct DCE
{
    uint32 time_low;
    uint16 time_mid;
    uint16 time_hi_and_version;
    uint8 clock_seq_hi_and_reserved;
    uint8 clock_seq_low;
    uint8 node[6];
};

static uint64 _get_time()
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
    {
        return uint64(-1);
    }

    return (uint64(tv.tv_sec) * 1000000) + uint64(tv.tv_usec);
}

static void _fill_random(void* data, size_t size)
{
    uint8* p = (uint8*)data;
    size_t r = size;

#if defined(CIMPLE_HAVE_DEV_RANDOM)


    int fd = open("/dev/random", O_RDONLY | O_NONBLOCK);
    size_t num_errors = 0;
    const size_t MAX_ERRORS_TOLERATED = 10;

    if (fd >= 0)
    {
        while (r)
        {
            ssize_t n = read(fd, p, r);

            if (n < 1)
            {
                if (++num_errors == MAX_ERRORS_TOLERATED)
                    break;

                if (errno == EAGAIN)
                    continue;

                break;
            }

            r -= n;
            p += n;
        }
    }

    close(fd);

    if (r == 0)
        return;

#endif /* CIMPLE_HAVE_DEV_RANDOM */

    uint64 s1 = get_mac_addr();
    uint64 s2 = _get_time();
    srand(((s1 >> 32) ^ s1 ^ (s2 >> 32)) | s2);

    while (r--)
        *p++ = rand();
}

static void _dce_to_uuid(const DCE& dce, UUID& uuid)
{
    uuid.data[0] = uint8(dce.time_low >> 24);
    uuid.data[1] = uint8(dce.time_low >> 16);
    uuid.data[2] = uint8(dce.time_low >> 8);
    uuid.data[3] = uint8(dce.time_low);
    uuid.data[4] = uint8(dce.time_mid >> 8);
    uuid.data[5] = uint8(dce.time_mid);
    uuid.data[6] = uint8(dce.time_hi_and_version >> 8);
    uuid.data[7] = uint8(dce.time_hi_and_version);
    uuid.data[8] = uint8(dce.clock_seq_hi_and_reserved);
    uuid.data[9] = uint8(dce.clock_seq_low);
    uuid.data[10] = uint8(dce.node[0]);
    uuid.data[11] = uint8(dce.node[1]);
    uuid.data[12] = uint8(dce.node[2]);
    uuid.data[13] = uint8(dce.node[3]);
    uuid.data[14] = uint8(dce.node[4]);
    uuid.data[15] = uint8(dce.node[5]);
}

void create_uuid(UUID& uuid)
{
    const uint16 VERSION = 0001;
    const uint8 RESERVED = 10;

    DCE dce;
    _fill_random(&dce, sizeof(dce)); 

    // Clear and set the 4 MSBs:
    dce.time_hi_and_version &= 0x0FFF;
    dce.time_hi_and_version |= (VERSION << 12);

    // Clear and set the 2 MSBs:
    dce.clock_seq_hi_and_reserved &= 0x3F;
    dce.clock_seq_hi_and_reserved |= (RESERVED << 6);

    _dce_to_uuid(dce, uuid);
}

void uuid_to_string(const UUID& uuid, char str[CIMPLE_UUID_STRING_SIZE])
{
    *str = 0;

    for (size_t i = 0; i < sizeof(uuid.data); i++)
    {
        char buffer[3];
        sprintf(buffer, "%02X", uuid.data[i]);
        strcat(str, buffer);
    }
}

CIMPLE_NAMESPACE_END

