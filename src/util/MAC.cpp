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

#include "MAC.h"

#if defined(CIMPLE_UNIX)
# include <sys/socket.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <net/if.h>
#elif defined(CIMPLE_WINDOWS)
# include <windows.h>
# include <wincon.h>
# include <stdlib.h>
# include <stdio.h>
#else
# error "unsupported platform"
#endif

CIMPLE_NAMESPACE_BEGIN

static int _get_mac_addr(uint8 addr[6])
{
#if defined(CIMPLE_OS_DARWIN) || defined(CIMPLE_OS_SOLARIS)

/*
ATTN: fix this:
*/

    addr[0] = 0x00;
    addr[1] = 0x11;
    addr[2] = 0x22;
    addr[3] = 0x33;
    addr[4] = 0x44;
    addr[5] = 0x55;

    return 0;

#elif defined(CIMPLE_UNIX)

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

        memcpy(addr, (uint8*)ifr.ifr_addr.sa_data, 6);
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

        addr[0] = astat.adapt.adapter_address[0];
        addr[1] = astat.adapt.adapter_address[1];
        addr[2] = astat.adapt.adapter_address[2];
        addr[3] = astat.adapt.adapter_address[3];
        addr[4] = astat.adapt.adapter_address[4];
        addr[5] = astat.adapt.adapter_address[5];
        return 0;
    }

    return -1;

#endif /* CIMPLE_WINDOWS */
}

uint64 get_mac_addr()
{
    uint8 addr[6];

    if (_get_mac_addr(addr) != 0)
        return uint64(-1);

    uint64 x = 
        (uint64(addr[0]) << 40) |
        (uint64(addr[1]) << 32) |
        (uint64(addr[2]) << 24) |
        (uint64(addr[3]) << 16) |
        (uint64(addr[4]) << 8) |
        uint64(addr[5]);

    return x;
}

CIMPLE_NAMESPACE_END

