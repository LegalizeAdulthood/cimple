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

#ifndef _Subscription_h
#define _Subscription_h

#include <cimple/List.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>

PEGASUS_NAMESPACE_BEGIN

struct Subscription;

struct Subscription : public cimple::List_Elem
{
public:

    Subscription(CIMInstance& provider_, const CIMName& class_name_);

    CIMInstance provider;
    CIMName class_name;
    size_t subscription_count;
    String provider_path;

    void print() const;
};

class Subscription_List
{
public:

    Subscription_List();

    Subscription* find(const CIMName& class_name);

    Subscription* head() { return (Subscription*)_list.head; }

    void append(Subscription* sub) { _list.append(sub); }

    // Decrements the subscription count and removes the subscription if
    // the reference count falls to zero. Returns the new reference count
    // or size_t(-1) if not found.
    size_t dec_and_remove_if_zero(
        const CIMName& class_name, Subscription*& sub);

private:

    cimple::List _list;
};

PEGASUS_NAMESPACE_END

#endif /* _Subscription_h */
