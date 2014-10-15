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

#include "Sockets.h"
#include <cctype>
#include <cstdio>

CIMPLE_NAMESPACE_BEGIN

static const size_t _MAX_OUTSTANDING_CONNECTIONS = 5;

const uint32 Sockets::READ = 1;
const uint32 Sockets::WRITE = 2;
const uint32 Sockets::EXCEPT = 4;
const Sock Sockets::BAD_SOCKET = -1;

static int _close_on_exec(int fd)
{
    return ::fcntl(fd, F_SETFD, ::fcntl(fd, F_GETFD) | FD_CLOEXEC);
}

int Sockets::init_addr(sockaddr_in& addr, const char* host, uint16 port)
{
    memset(&addr, 0, sizeof(addr));

    if (isalpha(host[0]))
    {
	hostent* ent = 0;
	hostent result;
	char data[4096];
	int error_num;

	int status = gethostbyname_r(
	    host, &result, data, sizeof(data), &ent, &error_num);

	if (status != 0 || ent == 0)
	    return -1;

	addr.sin_family = ent->h_addrtype;
	memcpy(&addr.sin_addr, ent->h_addr, ent->h_length);
    }
    else
    {
	addr.sin_addr.s_addr = inet_addr((char*)host);

	if ((int)addr.sin_addr.s_addr == -1)
	    return -1;

	addr.sin_family = AF_INET;
    }   

    addr.sin_port = htons(port);
    return 0;
}

Sock Sockets::socket()
{
    Sock sock;
    CIMPLE_RESTART(::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP), sock);
    _close_on_exec(sock);
    return sock;
}

Sock Sockets::server_socket(const sockaddr_in& addr)
{
    Sock sock;

    if ((sock = Sockets::socket()) == -1)
        return -1;

    if (Sockets::set_reuse_addr(sock) == -1)
        return -1;

    if (Sockets::bind(sock, addr) == -1)
        return -1;

    if (Sockets::listen(sock) == -1)
        return -1;

    return sock;
}

int Sockets::connect(Sock sock, const sockaddr_in& addr)
{
    return ::connect(sock, (sockaddr*)&addr, sizeof addr);
}

int Sockets::listen(Sock sock)
{
    int result;
    CIMPLE_RESTART(::listen(sock, _MAX_OUTSTANDING_CONNECTIONS), result);
    return result;
}

int Sockets::bind(Sock sock, const sockaddr_in& addr)
{
    int result;
    CIMPLE_RESTART(::bind(sock, (sockaddr*)&addr, sizeof(addr)), result);

    if (result != 0)
	return -1;

    if (addr.sin_port == 0)
    {
	socklen_t length = sizeof(addr);

	if (::getsockname(sock, (sockaddr*)&addr, &length) != 0)
	    return -1;
    }

    return 0;
}

Sock Sockets::accept(Sock sock, sockaddr_in& addr)
{
    socklen_t length = sizeof(addr);
    Sock new_sock;
    CIMPLE_RESTART(::accept(sock, (sockaddr*)&addr, &length), new_sock);
    _close_on_exec(new_sock);
    return new_sock;
}

int Sockets::connect(Sock sock, const sockaddr_in& addr, uint64& timeout)
{
    bool blocking = Sockets::get_blocking(sock);
    Sockets::set_blocking(sock, false);

    if (Sockets::connect(sock, addr) == 0)
        return 0;

    if (errno == EINPROGRESS)
    {
        uint32 events = WRITE;

        if (Sockets::wait(sock, events, timeout) != 1)
        {
            Sockets::set_blocking(sock, blocking);
            return -1;
        }

        if (events & WRITE)
        {
            int opt = 0;
            socklen_t n = sizeof(opt);

            if (getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&opt, &n) == 0 &&
                opt == 0)
            {
                Sockets::set_blocking(sock, blocking);
                return 0;
            }
        }
    }

    Sockets::set_blocking(sock, blocking);
    return -1;
}

int Sockets::close(Sock sock)
{
    int result;
    CIMPLE_RESTART(::close(sock), result);
    return result;
}

ssize_t Sockets::send(Sock sock, const void* data, size_t size)
{
    int result;
    CIMPLE_RESTART(::write(sock, data, size), result);

#ifdef BREVITY_ENABLE_SOCKET_TRACING

    if (result > 0)
    {
        FILE* os = fopen("send.trc", "a");

        if (os)
        {
            fwrite(data, 1, result, os);
            fclose(os);
        }
    }

#endif

    if (result == -1)
    {
        if (errno == EAGAIN)
            errno = EWOULDBLOCK;
    }

    return result;
}

ssize_t Sockets::recv(Sock sock, void* data, size_t size)
{
    int result;
    CIMPLE_RESTART(::read(sock, data, size), result);

#ifdef BREVITY_ENABLE_SOCKET_TRACING

    if (result > 0)
    {
        FILE* os = fopen("recv.trc", "a");

        if (os)
        {
            fwrite(data, 1, result, os);
            fclose(os);
        }
    }

#endif

    if (result == -1)
    {
        if (errno == EAGAIN)
            errno = EWOULDBLOCK;
    }

    return result;
}

ssize_t Sockets::recv_n(Sock sock, void* data, size_t size)
{
    size_t r = size;
    char* p = (char*)data;

    if (size == 0)
	return -1;

    while (r)
    {
	ssize_t n = Sockets::recv(sock, p, r);

	if (n == -1)
	{
	    if (errno == EWOULDBLOCK)
	    {
		size_t total = size - r;

		if (total)
		    return total;

		return -1;
	    }
	    else
		return -1;
	}
	else if (n == 0)
	    return size - r;

	r -= n;
	p += n;
    }

    return size - r;
}

ssize_t Sockets::recv_n(
    Sock sock, void* data, size_t size, uint64& timeout)
{
    char* p = (char*)data;
    size_t r = size;

    bool blocking = Sockets::get_blocking(sock);
    Sockets::set_blocking(sock, false);

    while (r)
    {
	uint32 events = 1;
	int count = Sockets::wait(sock, events, timeout);

	if (count == 1 && events & READ)
	{
	    ssize_t n = Sockets::recv_n(sock, p, r);

	    if (n == -1)
	    {
		Sockets::set_blocking(sock, blocking);
		return -1;
	    }

	    if (n == 0)
	    {
		Sockets::set_blocking(sock, blocking);
		return size;
	    }

	    r -= n;
	    p += n;
	}
	else
	{
	    Sockets::set_blocking(sock, blocking);
	    return count;
	}
    }

    Sockets::set_blocking(sock, blocking);
    return size;
}

ssize_t Sockets::send_n(Sock sock, const void* data, size_t size)
{
    size_t r = size;
    char* p = (char*)data;

    while (r)
    {
	ssize_t n = Sockets::send(sock, p, r);

	if (n == -1)
	{
	    if (errno == EWOULDBLOCK)
		return size - r;
	    else 
		return -1;
	}
	else if (n == 0)
	    return size - r;

	r -= n;
	p += n;
    }

    return size - r;
}

ssize_t Sockets::send_n( 
    Sock sock, const void* data, size_t size, uint64& timeout)
{
    const char* p = (const char*)data;
    size_t r = size;

    bool blocking = Sockets::get_blocking(sock);
    Sockets::set_blocking(sock, false);

    while (r)
    {
	uint32 events = WRITE;
	int count = Sockets::wait(sock, events, timeout);

	if (count == 1 && events & WRITE)
	{
	    ssize_t n = Sockets::send_n(sock, p, r);

	    if (n == -1)
	    {
		Sockets::set_blocking(sock, blocking);
		return -1;
	    }

	    if (n == 0)
	    {
		Sockets::set_blocking(sock, blocking);
		return -1;
	    }

	    r -= n;
	    p += n;
	}
	else
	{
	    Sockets::set_blocking(sock, blocking);
	    return count;
	}
    }

    Sockets::set_blocking(sock, blocking);
    return size;
}

bool Sockets::get_blocking(Sock sock)
{
    int flags = fcntl(sock, F_GETFL, 0);
    return flags & O_NONBLOCK ? false : true;
}

int Sockets::set_blocking(Sock sock, bool flag)
{
    int flags = fcntl(sock, F_GETFL, 0);

    if (flag)
	flags &= ~O_NONBLOCK;
    else
	flags |= O_NONBLOCK;

    return fcntl(sock, F_SETFL, flags);
}

int Sockets::wait(Sock sock, uint32& events, uint64& timeout)
{
    fd_set read_set;
    fd_set write_set;
    fd_set except_set;

    if (events & READ)
        FD_SET(sock, &read_set);

    if (events & WRITE)
        FD_SET(sock, &write_set);

    if (events & EXCEPT)
        FD_SET(sock, &except_set);

    events = 0;

    uint64 before = Time::now();

    timeval tv;
    tv.tv_sec = timeout / 1000000;
    tv.tv_usec = timeout % 1000000;

    int result = select(sock, &read_set, &write_set, &except_set, &tv);

    uint64 after = Time::now();
    timeout -= after - before;

    if (result == 1)
    {
	if (FD_ISSET(sock, &read_set))
	    events |= READ;

	if (FD_ISSET(sock, &write_set))
	    events |= WRITE;

	if (FD_ISSET(sock, &except_set))
	    events |= EXCEPT;
    }

    return result;
}

int Sockets::set_reuse_addr(Sock sock)
{
    int opt = 1;
    return ::setsockopt(
        sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
}

int Sockets::set_send_buffer(Sock sock, size_t size)
{
    int tmp = (int)size;
    return setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&tmp, sizeof(tmp));
}

int Sockets::set_delay(Sock sock, bool flag)
{
    int opt = flag ? 0 : 1;
    return setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&opt, sizeof(opt));}

CIMPLE_NAMESPACE_END
