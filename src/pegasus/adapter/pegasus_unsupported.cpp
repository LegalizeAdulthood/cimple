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

#define CIMPLE_PEGASUS_UNSUPPORTED
#include "pegasus_unsupported.h"
#include "Pegasus_Thread_Context.h"

CIMPLE_NAMESPACE_BEGIN

namespace pegasus
{
    static Pegasus_Thread_Context* _top()
    {
        Pegasus_Thread_Context* context = 
            (Pegasus_Thread_Context*)Thread_Context::top();
        assert(context != 0);

        return context;
    }

    Pegasus::CIMOMHandle* cimom_handle()
    {
        return _top()->cimom_handle();
    }

    Pegasus::OperationContext* operation_context()
    {
        return _top()->operation_context();
    }
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/adapter/pegasus_unsupported.cpp,v 1.3 2007/03/07 18:42:32 mbrasher-public Exp $");
