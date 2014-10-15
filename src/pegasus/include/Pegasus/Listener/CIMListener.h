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

#ifndef _cimple_Pegasus_Listener_Listener_h
#define _cimple_Pegasus_Listener_Listener_h

#include <Pegasus/Common/Config.h>

#ifdef PEGASUS_OS_TYPE_WINDOWS
# define PEGASUS_LISTENER_LINKAGE PEGASUS_IMPORT
#else
# define PEGASUS_LISTENER_LINKAGE
#endif

PEGASUS_NAMESPACE_BEGIN

class PEGASUS_LISTENER_LINKAGE CIMListener
{
public:

    CIMListener(Uint32 port, class SSLContext* context = 0);

    ~CIMListener();

    Uint32 getPortNumber() const;

    class SSLContext* getSSLContext() const;

    void setSSLContext(class SSLContext* context);

    void start();

    void stop();

    Boolean isAlive() const;

    Boolean addConsumer(class CIMIndicationConsumer* consumer);

    Boolean removeConsumer(class CIMIndicationConsumer* consumer);

private:
    CIMListener(const CIMListener&);
    CIMListener& operator=(const CIMListener&);
    void* _rep;
};

PEGASUS_NAMESPACE_END

#endif /* _cimple_Pegasus_Listener_Listener_h */
