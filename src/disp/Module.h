/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#ifndef _cimple_Module_h
#define _cimple_Module_h

#include <cimple/config.h>
#include <cimple/Registration.h>
#include <cimple/List.h>
#include "Envelope.h"

CIMPLE_NAMESPACE_BEGIN

class Module
{
public:

    Module(void* handle, Module_Proc proc);

    ~Module();

    Registration* registration() { return _registration; }

    CIMPLE_HIDE void load_providers();

    CIMPLE_HIDE void unload_providers();

    CIMPLE_HIDE Envelope* find_provider(const char* class_name);

    CIMPLE_HIDE List_Elem* envelopes() { return _envelopes.head; }

    void dump() const;

private:

    void* _handle;
    Registration* _registration;
    bool _providers_loaded;
    List _envelopes;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Module_h */
