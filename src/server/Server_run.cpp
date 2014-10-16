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

#include "Server.h"
#include "OS.h"

void Server::run()
{
    // Initialize address:

    Sock_Addr addr;
    OS::init_listener_addr(addr, SF_LISTEN_PORT);

    // Create listening socket and make it non-blocking.

    _listen_sock = OS::listener_socket(addr);
    OS::set_blocking(_listen_sock, false);

    // Create accepting threads:

    for (size_t i = 0; i < SF_NUM_ACCEPT_THREADS; i++)
    {
        Thread thread;
        OS::create_thread(thread, Server::accept_thread, this);
    }

    // Wait for all threads to exit:

    OS::exit_thread((void*)0);

    printf("MAIN THREAD EXIT\n");
}
