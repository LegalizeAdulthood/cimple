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

/* test of implementation of the list functions defined in cimple/List.h
*/
#include <cassert>
#include <cstdio>
#include <cimple/List.h>
#include <cimple/Instance.h>
#include <cimple/String.h>

using namespace cimple;

/******************************************************************************
**
**  Class definition to extend list mechanism to test_list that features
**  a list that is ordered on add with order set by the order_value variable
**  in the structure.
**
******************************************************************************/
struct test_elem : public List_Elem
{
    int id;                   // identification variable for each item
    int order_value;          // list assending order per this variable
    String info;              // simply piece of data
};

class test_list
{
public:

    test_list();
    ~test_list();
    // add item to list including id, order, etc.
    void add(int id, int order_value, String& s);
    // remove item from list
    bool remove(int id);
    // return true if item found in list
    bool find(int id);
    // get position of item in list.  one origin so that zero means
    // cannot find
    size_t pos(int id);
    // return true if list empty
    bool empty();
    // return count of items in list
    size_t size();
private:
    List _list;
};

test_list::test_list()
{
}

test_list::~test_list()
{
    for (List_Elem* p = _list.head; p; )
    {
    	List_Elem* next = p->next;
    	delete p;
    	p = next;
    }
}

void test_list::add(int id, int order, String& s)
{
    test_elem* x = new test_elem;
    x->id = id;
    x->order_value = order;
    x->info = s;

    if(!_list.empty())
    {
        // insert in order sequence
        for (List_Elem* p = _list.head; p; p = p->next)
        {
        	if (x->order_value < ((test_elem*)p)->order_value)
        	{
        	    _list.insert_before(p, x);
        	    return;
        	}
        }
    }

    _list.append(x);
}

bool test_list::empty()
{
    return _list.empty();
}

size_t test_list::size()
{
    return _list.size();
}

bool test_list::remove(int id)
{
    for (List_Elem* p = _list.head; p; p = p->next)
    {
    	test_elem* x = (test_elem*)p;
    
    	if (x->id == id)
    	{
    	    // Found!
    	    _list.remove(p);
    	    delete x;
    	    return true;
    	}
    }

    // Not found!
    return false;
}

bool test_list::find(int id)
{
    for (List_Elem* p = _list.head; p; p = p->next)
    {
    	test_elem* x = (test_elem*)p;
    
    	if (x->id == id)
    	{
    	    return true;
    	}
    }

    // Not found!
    return false;
}

size_t test_list::pos(int id)
{
    size_t pos = 1;
    for (List_Elem* p = _list.head; p; p = p->next)
    {
    	test_elem* x = (test_elem*)p;
    
    	if (x->id == id)
    	{
    	    return pos;
    	}
        pos++;
    }

    // Not found!
    return 0;
}

int main(int argc, char** argv)
{
    // Test with Test_list class.

    test_list x;
    assert(x.empty());

    // Add one item. order 3
    String three("Three");
    x.add(1, 3, three);
    assert(!x.empty());
    assert(x.size() == 1);
    assert(x.find(1));
    assert(x.pos(1) == 1);

    // add one item order 1
    String one("one");
    x.add(2, 1, one);
    assert(!x.empty());
    assert(x.size() == 2);
    assert(x.find(1));
    assert(x.find(2));
    assert(x.pos(2) == 1);
    assert(x.pos(1) == 2);

    // add one item, order 4
    String four("four");
    x.add(3, 4, four);
    assert(!x.empty());
    assert(x.size() == 3);
    assert(x.pos(2) == 1);
    assert(x.pos(1) == 2);
    assert(x.pos(3) == 3);

    // add one item, order zero
    // this one should go to the front
    String zero("zero");
    x.add(4, 0, zero);
    assert(!x.empty());
    assert(x.size() == 4);
    assert(x.pos(2) == 2);
    assert(x.pos(1) == 3);
    assert(x.pos(3) == 4);
    assert(x.pos(4) == 1);

    // remove item id 4
    assert(x.remove(4));
    assert(x.size() == 3);
    assert(x.pos(2) == 1);
    assert(x.pos(1) == 2);
    assert(x.pos(3) == 3);

    // remove item id 1
    assert(x.remove(1));
    assert(x.size() == 2);
    assert(x.pos(2) == 1);
    assert(x.pos(1) == 0);
    assert(x.pos(3) == 2);

    assert(!x.remove(1));
    assert(x.remove(2));
    assert(x.remove(3));



    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

