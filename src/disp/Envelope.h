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

#ifndef _cimple_Envelope_h
#define _cimple_Envelope_h

#include <cimple/Provider.h>
#include <cimple/Instance.h>
#include <cimple/Registration.h>
#include <cimple/Provider_Handle.h>
#include <cimple/RMutex.h>
#include <cimple/List.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

/** An Envelope is the interface to invoking the operations of a single 
    provider (e.g., get_instance, enum_instances). It invokes the provider
    procedure directly. The envelope synchronizes access to the provider
    through its mutex member (see Envelope::_mutex).
*/
class CIMPLEDISP_LINKAGE Envelope : public List_Elem, public Provider_Handle
{
public:

    Envelope(Registration* reg);

    ~Envelope();

    const char* provider_name() const { return _reg->provider_name; }

    const Meta_Class* meta_class() const { return _reg->meta_class; }

    const char* class_name() const { return _reg->meta_class->name; }

    RMutex& mutex() { return _mutex; }

private:

    Registration* _reg;
    RMutex _mutex;

    friend class Cache;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Envelope_h */
