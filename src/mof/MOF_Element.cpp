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

#include "MOF_Element.h"

MOF_Element::~MOF_Element()
{

}

void MOF_Element::append(MOF_Element* element)
{
    MOF_ASSERT(this != 0);
    MOF_ASSERT(element != 0);

    for (MOF_Element* p = this; p; p = p->next)
    {
        if (!p->next)
        {
            p->next = element;
            element->next = 0;
            break;
        }
    }
}

size_t MOF_Element::list_size() const
{
    size_t size = 0;

    for (const MOF_Element* p = this; p; p = p->next)
        size++;

    return size;
}

MOF_Element* MOF_Element::clone() const
{
    MOF_ASSERT("not implemented" == 0);
    return 0;
}

MOF_Element* MOF_Element::clone_list() const
{
    MOF_Element* list = 0;

    for (const MOF_Element* p = this; p; p = p->next)
    {
        if (list == 0)
            list = clone();
        else
            list->append(clone());
    }

    return list;
}

void MOF_Element::delete_list()
{
    for (MOF_Element* p = this; p; )
    {
        MOF_Element* next = p->next;
        delete p;
        p = next;
    }
}
