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

#ifndef _cimple_disp_List_h
#define _cimple_disp_List_h

#include <cimple/config.h>

CIMPLE_NAMESPACE_BEGIN

struct List_Elem
{
    List_Elem* prev;
    List_Elem* next;
};

struct CIMPLE_LIBCIMPLE_LINKAGE List
{
    List() : head(0), tail(0) { }

    void clear() { head = 0; tail = 0; }

    void append(List_Elem* p);

    void prepend(List_Elem* p);

    void remove(List_Elem* p);

    void insert_after(List_Elem* pos, List_Elem* p);

    void insert_before(List_Elem* pos, List_Elem* p);

    bool empty() const { return head == 0; }

    List_Elem* head;
    List_Elem* tail;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_disp_List_h */
