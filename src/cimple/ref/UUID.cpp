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
#include <sys/types.h>
#include <sys/time.h>
# include <time.h>

#if defined(CIMPLE_UNIX)
# include <unistd.h>
# include <sys/ioctl.h>
# include <net/if.h>
#elif defined(CIMPLE_UNIX)
# include <windows.h>
# include <wincon.h>
# include <stdlib.h>
# include <stdio.h>
#else
# error "unsupported platform"
#endif

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// This module implements the DCE UUID variant.
//
//==============================================================================

static int _get_mac_addr(uint8 mac[6])
{
#if defined(CIMPLE_UNIX)

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        return -1;

    ifconf ifc;
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;

    if (ioctl(sock, SIOCGIFCONF, &ifc) < 0)
    {
        close(sock);
        return -1;
    }

    for (int i = 0, n = ifc.ifc_len; i < n; i += sizeof(ifreq))
    {
        const ifreq* tmp = (const ifreq*)((char*)ifc.ifc_buf + i);

        if (strncasecmp(tmp->ifr_name, "eth", 3) != 0)
            continue;

        ifreq ifr;
        strncpy(ifr.ifr_name, tmp->ifr_name, IFNAMSIZ);

        if (ioctl(sock, SIOCGIFHWADDR, &ifr) != 0)
        {
            close(sock);
            return 0;
        }

        memcpy(mac, (uint8*)ifr.ifr_addr.sa_data, 6);
        close(sock);
        return 0;
    }

    close(sock);
    return 0;

#elif defined(CIMPLE_WINDOWS)

    struct ASTAT
    {
        ADAPTER_STATUS adapt;
        NAME_BUFFER name_buffer[30];
    };

    ASTAT astat;
    NCB ncb;
    LANA_ENUM lenum;

    // Netbios() enum:

    memset(&ncb, 0, sizeof(ncb));
    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer = (UCHAR *)&lenum;
    ncb.ncb_length = sizeof(lenum);

    if (Netbios(&ncb) != 0)
        return -1;

    for(int i = 0; i < lenum.length; i++)
    {
        // Netbios() reset:

        memset(&ncb, 0, sizeof(ncb));
        ncb.ncb_command = NCBRESET;
        ncb.ncb_lana_num = lenum.lana[i];

        if (Netbios(&ncb) != 0)
            continue;

        // Netbios() stat:

        memset(&ncb, 0, sizeof (ncb));
        ncb.ncb_command = NCBASTAT;
        ncb.ncb_lana_num = lenum.lana[i];
        strcpy((char*)ncb.ncb_callname,  "*               ");
        ncb.ncb_buffer = (unsigned char *)&astat;
        ncb.ncb_length = sizeof(astat);

        if (Netbios(&ncb) != 0)
            continue;

        // Success!!!

        mac[0] = astat.adapt.adapter_address[0];
        mac[1] = astat.adapt.adapter_address[1];
        mac[2] = astat.adapt.adapter_address[2];
        mac[3] = astat.adapt.adapter_address[3];
        mac[4] = astat.adapt.adapter_address[4];
        mac[5] = astat.adapt.adapter_address[5];
        return 0;
    }

    return -1;

#endif /* CIMPLE_WINDOWS */
}

static uint64 _get_gregorian_time()
{
    // Delta in nanoseconds between POSIX epoch (00:00:00 1 Jan 1970) and the
    // Gregorian epoch (00:00:00 15 October 1582).
    const uint64 greg_delta = (uint64(0x01B21DD2) << 32) | uint64(0x13814000);

    struct timeval tv;
    memset(&tv, 0, sizeof(tv));

    if (gettimeofday(&tv, NULL) != 0)
        return uint64(-1);

    return
        (uint64(tv.tv_sec) * 10000000) + 
        (uint64(tv.tv_usec) * 10) +
        greg_delta;
}

int create_uuid(UUID& uuid)
{
    const uint16 DCE_VERSION = 1;

    // Get gregorian epoch time.
    uint64 greg = _get_gregorian_time();

    if (greg == uint64(-1))
        return -1;

    // time_low:
    uuid.time_low = greg;

    // time_mid:
    uuid.time_mid = (greg >> 32) & uint64(0xFFFF);

    // time_hi:
    uuid.time_hi_and_version = (greg >> 48) & uint64(0xFFF);

    // version:
    uuid.time_hi_and_version |= (DCE_VERSION << 12);

    // clock_seq (not implemented so just use a random number).
    srand((unsigned int)time(NULL));
    uint16 clock_seq = rand() & 0x3FFF;

    // clock_seq_low:
    uuid.clock_seq_low = clock_seq;

    // clock_seq_hi:
    uuid.clock_seq_hi_and_reserved = clock_seq >> 8;

    // reserved (set bit 7):
    uuid.clock_seq_hi_and_reserved |= (1 << 7);

    // node:
    if (_get_mac_addr(uuid.node) != 0)
        return -1;

    return 0;
}

void uuid_to_string(const UUID& uuid, char str[CIMPLE_UUID_STRING_SIZE])
{
    sprintf(str, 
        "%02X%02X%02X%02X%02X%02X%02X%02X"
        "%02X%02X%02X%02X%02X%02X%02X%02X",
        uint8(uuid.time_low >> 24),
        uint8(uuid.time_low >> 16),
        uint8(uuid.time_low >> 8),
        uint8(uuid.time_low),
        uint8(uuid.time_mid >> 8),
        uint8(uuid.time_mid),
        uint8(uuid.time_hi_and_version >> 8),
        uint8(uuid.time_hi_and_version),
        uint8(uuid.clock_seq_hi_and_reserved),
        uint8(uuid.clock_seq_low),
        uint8(uuid.node[0]),
        uint8(uuid.node[1]),
        uint8(uuid.node[2]),
        uint8(uuid.node[3]),
        uint8(uuid.node[4]),
        uint8(uuid.node[5]));
}

CIMPLE_NAMESPACE_END
