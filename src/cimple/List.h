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

/** 
 * List class the defines a double-linked list mechanism in 
 * CIMPLE. Note that this class by iteself is incomplete (ex. 
 * there is no standard compare mechanism) and is intended to be 
 * extended by the CIMPLE provider developer for specific 
 * functionality. This class provides the basic structure for 
 * list elements and the methods for inserting, removing, 
 * clearing, get the list size, etc. Examples of the use of the 
 * List class are in the cimple/tests/lists/main.cpp and 
 * cimple/Scheduler.cpp files. 
 *
*/

#ifndef _cimple_List_h
#define _cimple_List_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN

/**
 * Defines the basic structure  of a single element of a list. 
 * The user can create inherited structures incorporating user 
 * data as subclasses of #List_Elem. 
 */
struct List_Elem
{
    List_Elem* prev;
    List_Elem* next;
};

/** 
 * This Class implements a list mechanism within the CIMPLE 
 * environment. The List class includes methods for 
 * inserting #List_Elem entities, removing them, clearing the
 * list, and determing if there are any elements in the list( 
 * #empty) and the number of items in the list. The list is 
 * built as a double linked list mechanism. Note that by itself, 
 * this class is incomplete and is intended to be extended by 
 * the user. Thus, for example, there is no compare function to 
 * find any particlar position in the list. 
 * 
 */
struct CIMPLE_CIMPLE_LINKAGE List
{
    ///
    List() : head(0), tail(0), _size(0) { }

    /** 
     * Clears the list to empty.  Warning. This does not free memory
     * for any items in the list. It simply resets the head and tail
     * to zero indicating that the list is clear
     * 
     */
    void clear() { head = 0; tail = 0; _size = 0; }

    /** 
     * Append an item to the list, i.e. insert it at the tail of the 
     * list. 
     * 
     * @param p List_Elem* pointer to the entity to append to the 
     *          list
     */
    void append(List_Elem* p);

    /** 
     * Prepend an item to the list, i.e. insert it at head of the 
     * list. 
     * 
     * @param p List_Elem* pointer to the entity to prepend to the 
     *          list
     */
    void prepend(List_Elem* p);

    /** 
     * Remove a single item from the list.
     * 
     * @param p List_Elem* pointer to the entity to remove from the 
     *          list
     */
    void remove(List_Elem* p);

    /** 
     * Insert an item at specified point in a list.  Inserts after 
     * the item defined by pos. 
     * 
     * @param pos
     * @param p
     */
    void insert_after(List_Elem* pos, List_Elem* p);

    /** 
     * Insert an item at a specfied point in a list. Inserts before 
     * the defined position. 
     * 
     * @param pos in queue to insert
     * @param p element to insert
     */
    void insert_before(List_Elem* pos, List_Elem* p);

    /** 
     * Determine if the list is empty ( i.e. head of queue == 0)
     * 
     * @return bool
     */
    bool empty() const { return head == 0; }

    /** 
     * Return number of entries in the list
     * @return size_t Number of entries in the queue
     */
    size_t size();

    List_Elem* head;
    List_Elem* tail;

private:

    size_t _size;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_List_h */
