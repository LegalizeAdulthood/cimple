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

#ifndef _brevity_Sockets_h
#define _brevity_Sockets_h

#include <cimple/cimple.h>
#include "linkage.h"
#include "defines.h"
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/tcp.h>

CIMPLE_NAMESPACE_BEGIN

typedef int Sock;

class CIMPLE_BREVITY_LINKAGE Sockets
{
public:

    static const uint32 READ;
    static const uint32 WRITE;
    static const uint32 EXCEPT;
    static const Sock BAD_SOCKET;

    static int init_addr(sockaddr_in& addr, const char* host, uint16 port);

    static Sock socket();

    static Sock server_socket(const sockaddr_in& addr);

    static int listen(Sock sock);

    static int bind(Sock sock, const sockaddr_in& addr);

    static Sock accept(Sock sock, sockaddr_in& addr);

    static int connect(Sock sock, const sockaddr_in& addr);

    static int connect(Sock sock, const sockaddr_in& addr, uint64& timeout);

    static int close(Sock sock);

    static ssize_t recv(Sock sock, void* data, size_t size);

    static ssize_t recv_n(Sock sock, void* data, size_t size);

    static ssize_t recv_n(Sock sock, void* data, size_t size, uint64& timeout);

    static ssize_t send(Sock sock, const void* data, size_t size);

    static ssize_t send_n(Sock sock, const void* data, size_t size);

    static ssize_t send_n(
        Sock sock, const void* data, size_t size, uint64& timeout);

    static bool get_blocking(Sock sock);

    static int set_blocking(Sock sock, bool flag);

    static int wait(Sock sock, uint32& events, uint64& timeout);

    static int set_reuse_addr(Sock sock);

    static int set_send_buffer(Sock sock, size_t size);

    static int set_delay(Sock sock, bool flag);
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_Sockets_h */
