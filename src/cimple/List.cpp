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

#include "List.h"

CIMPLE_NAMESPACE_BEGIN

void List::prepend(List_Elem* p)
{
    p->next = head;
    p->prev = 0;

    if (head)
        head->prev = p;
    else
        tail = p;

    head = p;

    _size++;
}

void List::append(List_Elem* p)
{
    p->prev = tail;
    p->next = 0;

    if (tail)
        tail->next = p;
    else
        head = p;

    tail = p;
    _size++;
}

void List::remove(List_Elem* p)
{
    if (p->prev)
        p->prev->next = p->next;

    if (p->next)
        p->next->prev = p->prev;

    if (p == head)
        head = p->next;

    if (p == tail)
        tail = p->prev;
    _size--;
}

void List::insert_after(List_Elem* pos, List_Elem* p)
{
    p->prev = pos;
    p->next = pos->next;

    if (pos->next)
        pos->next->prev = p;

    pos->next = p;

    if (pos == tail)
        tail = p;
    _size++;
}

void List::insert_before(List_Elem* pos, List_Elem* p)
{
    p->next = pos;
    p->prev = pos->prev;

    if (pos->prev)
        pos->prev->next = p;

    pos->prev = p;

    if (pos == head)
        head = p;
    _size++;
}

size_t List::size()
{
    return _size;
}
CIMPLE_NAMESPACE_END
