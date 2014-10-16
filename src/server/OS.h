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

#ifndef _server_OS_h
#define _server_OS_h

#include <stdio.h>
#include <string.h>
#include <server/Config.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#ifdef SF_NEED_RESTART
# define SF_RESTART(EXPR, RC) while (((RC = (EXPR)) == -1) && (errno == EINTR))
#else
# define SF_RESTART(EXPR, RC) (RC = (EXPR))
#endif

typedef sockaddr_in Sock_Addr;
typedef unsigned int IP_Addr;
typedef int Sock;
typedef unsigned short Port;
typedef pthread_t Thread;
typedef pthread_mutex_t Mutex;
typedef void* (*Thread_Proc)(void* arg);

class OS
{
public:

    static Sock socket();

    static int close(Sock sock);

    static int close_on_exec(Sock sock);

    static ssize_t recv(Sock sock, void* buffer, size_t size);

    static ssize_t send(Sock sock, const void* buffer, size_t size);

    static bool get_blocking(Sock sock);

    static void set_blocking(Sock sock, bool flag);

    static int set_reuse_addr(Sock sock);

    static int set_snd_buf(Sock sock, size_t size);

    static int set_rcv_buf(Sock sock, size_t size);

    static int set_delay(Sock sock, bool flag);

    static int listen(Sock sock);

    static int bind(Sock sock, const Sock_Addr& addr);

    static Sock accept(Sock sock, Sock_Addr& addr);

    static ssize_t recv_n(Sock sock, void* buffer, size_t size);

    static ssize_t send_n(Sock sock, const void* buffer, size_t size);

    static Sock listener_socket(const Sock_Addr& addr);

    static void clear(Sock_Addr& addr);

    static IP_Addr get_ip_addr(const Sock_Addr& addr);

    static Port get_port(const Sock_Addr& addr);

    static void init_listener_addr(Sock_Addr& addr, Port listener_port);

    static int peer_addr(Sock sock, Sock_Addr& addr);

    static int create_thread(Thread& thread, Thread_Proc proc, void* args);

    static void exit_thread(void* return_value);
};

inline bool OS::get_blocking(Sock sock)
{
    return fcntl(sock, F_GETFL, 0) & O_NONBLOCK;
}

inline int OS::set_reuse_addr(Sock sock)
{
    int opt = 1;
    return ::setsockopt(
        sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof opt);
}

inline int OS::set_snd_buf(Sock sock, size_t size)
{
    int tmp = (int)size;
    return setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&tmp, sizeof tmp);
}

inline int OS::set_rcv_buf(Sock sock, size_t size)
{
    int tmp = (int)size;
    return setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&tmp, sizeof tmp);
}

inline int OS::set_delay(Sock sock, bool flag)
{
    // Enable/disable Nagle's algorithm:
    int opt = flag ? 0 : 1;
    return setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&opt, sizeof opt);
}

inline int OS::listen(Sock sock)
{
    int result;
    SF_RESTART(::listen(sock, 5), result);
    return result;
}

inline int OS::bind(Sock sock, const Sock_Addr& addr)
{
    return ::bind(sock, (sockaddr*)(&addr), sizeof addr);
}

inline void OS::clear(Sock_Addr& addr)
{
    bzero(&addr, sizeof(Sock_Addr));
}

inline IP_Addr OS::get_ip_addr(const Sock_Addr& addr)
{
    return ntohl(addr.sin_addr.s_addr);
}

inline Port OS::get_port(const Sock_Addr& addr)
{
    return ntohs(addr.sin_port);
}

inline int OS::peer_addr(Sock sock, Sock_Addr& addr)
{
    socklen_t len = sizeof addr;
    return getpeername(sock, (sockaddr*)&addr, &len);
}

inline int OS::create_thread(Thread& thread, Thread_Proc proc, void* args)
{
    return pthread_create(&thread, NULL, proc, args);
}

inline void OS::exit_thread(void* return_value)
{
    pthread_exit(return_value);
}

#endif /* _server_OS_h */
