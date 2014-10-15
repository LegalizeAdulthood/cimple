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

#include "Subscription.h"

using namespace cimple;

PEGASUS_NAMESPACE_BEGIN

//==============================================================================
//
// class Subscription
//
//==============================================================================

Subscription::Subscription(CIMInstance& provider_, const CIMName& class_name_) 
    : provider(provider_), class_name(class_name_), subscription_count(1)
{
    provider_path = provider.getPath().toString();
}

//==============================================================================
//
// class Subscription_List
//
//==============================================================================

Subscription_List::Subscription_List()
{
}

Subscription* Subscription_List::find(const CIMName& class_name)
{
    for (List_Elem* p = _list.head; p; p = p->next)
    {
        Subscription* s = (Subscription*)p;

        if (s->class_name == class_name)
            return s;
    }

    return 0;
}

void Subscription::print() const
{
    std::cout << "Subscription(" << class_name.getString() << ", ";
    std::cout << provider_path << ")" << std::endl;
}

size_t Subscription_List::dec_and_remove_if_zero(
    const CIMName& class_name,
    Subscription*& sub)
{
    sub = 0;

    for (List_Elem* p = _list.head; p; p = p->next)
    {
        Subscription* s = (Subscription*)p;

        if (s->class_name == class_name)
        {
            if (--s->subscription_count == 0)
            {
                _list.remove(s);
                sub = s;
                return 0;
            }

            return s->subscription_count;
        }
    }

    // Not found!
    return (size_t)-1;
}

PEGASUS_NAMESPACE_END
