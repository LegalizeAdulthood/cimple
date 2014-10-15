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

#include "Link.h"
#include "Manager.h"
#include "C.h"
#include "OutOfOfficeNotice.h"

using namespace cimple;

int main(int argc, char** argv)
{
    {
        Manager* m1 = Manager::create(true);
        m1->__name_space = "xyz";
        Manager* m2 = m1->clone();
        assert(identical(m1, m2));
    }

    {
        Manager* m = Manager::create();
        m->Id.value = 1234;
        // print(m, true);
    }

    {
        Employee* e = Employee::create();
        e->__name_space = "root/abc";
        e->Id.value = 1;

        Manager* m = Manager::create();
        m->__name_space = "root/xyz";
        m->Id.value = 2;

        Link* link = Link::create();
        link->Emp = e;
        link->Mgr = m;

        print(link);
    }

    {
        Manager* m = Manager::create(true);
        m->Id.set(1);
        m->First.set("Jane");
        m->Last.set("Do");
        m->Gender.set(2);
        m->Active.set(true);
        m->NumEmployees.set(10);
        m->Budget.set(1000000);
        print(m);

        assert(m->Budget.value == 1000000);
        assert(m->Budget.null == false);
        m->Gender.clear();
        // print(m);
    }

    {
        Ref<Manager> m = Manager::create(true);
        m->Id.set(1);
        m->First.set("Jane");
        m->Last.set("Do");
        m->Gender.set(2);
        m->Active.set(true);
        m->NumEmployees.set(10);
        m->Budget.set(1000000);
        print(m.ptr());

        assert(m->Budget.value == 1000000);
        assert(m->Budget.null == false);
        m->Gender.clear();
    }

    {
        C* c = C::create(true);
        B* b = reinterpret_cast<B*>(c);
        print(b);
    }

    {
        Employee* e = Employee::create(true);
        e->Id.set(1001);

        OutOfOfficeNotice* o = OutOfOfficeNotice::create();
        o->employee = e;

        print(o);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}

