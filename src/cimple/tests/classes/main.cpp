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
#include "Everything.h"
#include "EverythingDefaults.h"

using namespace cimple;

int main(int argc, char** argv)
{
    {
        Manager* m1 = Manager::create(true);
        assert(m1->Id.null);
        assert(m1->First.null);
        assert(m1->Last.null);
        assert(m1->Gender.null);
        assert(!m1->Active.null);
        // Not null because the class mof default is not null
        assert(m1->Active.value == true);
        assert(m1->NumEmployees.null);
        assert(m1->Budget.null);
        assert(m1->__name_space == "");


        m1->__name_space = "xyz";

        assert(m1->__name_space == "xyz");
        Manager* m2 = m1->clone();
        assert(identical(m1, m2));
        //print(m1);
    }

    {
        Manager* m = Manager::create();
        m->Id.value = 1234;
        //print(m);
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

        assert(m->__name_space == "root/xyz");
        assert(e->__name_space == "root/abc");
        Employee* eout = link->Emp;
        assert(eout->__name_space == "root/abc");
        assert(eout->Id.value == 1);
        Manager* mout = link->Mgr;
        assert(mout->__name_space == "root/xyz");
        assert(mout->Id.value == 2);

        //print(link);
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

        assert(m->Id.value == 1);
        assert(m->First.value == "Jane");
        assert(m->Last.value == "Do");
        assert(m->Gender.value == 2);
        assert(m->Active.value == true);
        assert(m->NumEmployees.value == 10);
        assert(m->Budget.value == 1000000);
        assert(m->Budget.null == false);

        //print(m);
        m->Budget.set(10000);
        m->Gender.clear();
        assert(m->Budget.value == 10000);
        assert(m->Gender.null);
        //print(m);
    }

    {
        Ref<Manager> m = Manager::create(true);

        // test properties right after create
        assert(m->Id.null);
        assert(m->First.null);
        assert(m->Last.null);
        assert(m->Gender.null);
        assert(m->Active.value == true);
        assert(m->NumEmployees.null);
        assert(m->Budget.null);
        //print(m.ptr());

        // set values into properties
        m->Id.set(1);
        m->First.set("Jane");
        m->Last.set("Do");
        m->Gender.set(2);
        m->Active.set(true);
        m->NumEmployees.set(10);
        m->Budget.set(1000000);
        //print(m.ptr());

        // retest for updated values.
        assert(m->Id.value == 1);
        assert(m->First.value == "Jane");
        assert(m->Last.value == "Do");
        assert(m->Gender.value == 2);
        assert(m->Active.value == true);
        assert(m->NumEmployees.value == 10);
        assert(m->Budget.value == 1000000);
        assert(m->Budget.null == false);
        assert(m->Budget.value == 1000000);
        assert(m->Budget.null == false);

        // test clear function
        m->Budget.set(10000);
        m->Gender.clear();
        assert(m->Budget.value == 10000);
        assert(m->Gender.null);
        // print(m.ptr());
    }

    {
        C* c = C::create(true);
        c->w.set(true);
        c->y.set("hello");
        assert(c->w.value == true);
        assert(!c->w.null);
        assert(!c->y.null);
        assert(c->y.value == "hello");
        assert(c->z.null);
        B* b = reinterpret_cast<B*>(c);
        assert(b->w.value == true);
        assert(!b->w.null);
        assert(!b->y.null);
        assert(b->y.value == "hello");

        b->y.set("goodbye");
        assert(b->y.value == "goodbye");
        assert(c->y.value == "goodbye");
        // NOTE: Class b has no property z. therefore a statement like
        //   assert(b->z.null);
        //will not compile.
        print(c);
        print(b);
    }

    // Test Embedded object. Employee embedded in 
    {
        Employee* e = Employee::create(true);
        e->Id.set(1001);

        // Set the Employee embedded Object into the Indicaiton
        OutOfOfficeNotice* o = OutOfOfficeNotice::create();
        o->employee = e;
        print(o->employee);
        //Employee* eout = o->employee;
        //assert(o->employee.value == e);

        print(o);
    }

    // Tests with the Everything Class that contains all types except
    // embedded
    {
        Everything* e = Everything::create(true);

        // test immediatly after create.
        assert(e->a.null);
        assert(e->b.null);
        assert(e->c.null);
        assert(e->d.null);
        assert(e->e.null);
        assert(e->f.null);
        assert(e->g.null);
        assert(e->h.null);
        assert(e->i.null);
        assert(e->j.null);
        assert(e->k.null);
        assert(e->l.null);
        assert(e->m.null);

        assert(e->aa.null);
        assert(e->bb.null);
        assert(e->cc.null);
        assert(e->dd.null);
        assert(e->ee.null);
        assert(e->ff.null);
        assert(e->gg.null);
        assert(e->hh.null);
        assert(e->ii.null);
        assert(e->jj.null);
        assert(e->kk.null);
        assert(e->ll.null);
        assert(e->mm.null);
    }

    // Tests with the Everything Class that contains all types except
    // embedded
    {
        Datetime dt_interval;
        dt_interval.usec(
            1 * Datetime::DAY +
            2 * Datetime::HOUR + 
            3 * Datetime::MIN +
            4 * Datetime::SEC +
            5 * Datetime::USEC);
        Datetime dt_timestamp;

        EverythingDefaults* e = EverythingDefaults::create(true);
        print(e);
        assert(e->a.value == false);
        assert(e->b.value = 8);
        assert(e->c.value = 32);
        assert(e->d.value == 9999);
        assert(e->e.value == 99999);
        //assert(e->f.value == 2936.88);
        assert(e->g.null);
        assert(e->h.null);
        assert(e->i.value == "hello");
        assert(e->j.value == dt_interval);
        assert(e->k.value == "");
        assert(e->l.value == 0);
        assert(e->m.value == true);

        assert(!e->aa.null);
        assert(e->aa.value == Array<boolean>::make(true, false, true));
        assert(!e->bb.null);
        // the CIMPLE...MIN and MAX are defined in config.h
        assert(e->bb.value == Array<uint8>::make(CIMPLE_UINT8_MIN,
                                                 128,
                                                 CIMPLE_UINT8_MAX));
        assert(!e->cc.null);
        assert(e->cc.value == Array<uint16>::make(CIMPLE_UINT16_MIN,
                                                  1000,
                                                  CIMPLE_UINT16_MAX));
        assert(!e->dd.null);
        assert(e->dd.value ==  Array<uint32>::make(CIMPLE_UINT32_MIN, 
                                                   8192,
                                                   CIMPLE_UINT32_MAX));
        assert(!e->es.null);
        assert(e->es.value ==  Array<sint64>::make(0,
                                               CIMPLE_SINT64_LITERAL(9999999),
                                               CIMPLE_SINT64_MAX));
        // switch to use the following. Note we substitute numeric for
        // symbolic max until we fix problem in compiler.  Problem in 
        // compiler is use of strtoll function for integer conversion that
        // causes max defined in numeric below as maximum allowable
        // in a class default uint64 integer.  This also affects the
        // test in mofe/tests/test12
//      assert(e->es.value ==  Array<sint64>::make(CIMPLE_SINT64_MIN,
//                                             CIMPLE_SINT64_LITERAL(9999999),
//                                             CIMPLE_SINT64_MAX));
        assert(!e->ee.null);
        assert(e->ee.value ==  Array<uint64>::make(CIMPLE_UINT64_MIN,
            CIMPLE_UINT64_LITERAL(9999999),
            CIMPLE_UINT64_LITERAL(9223372036854775807) ));
        assert(!e->ff.null);
        assert(e->ff.value ==  Array<real32>::make(1.5, 1.5));
        assert(!e->gg.null);
        assert(!e->hh.null);
        assert(e->hh.value == Array<char16>::make('A', 'a'));
        assert(!e->ii.null);
        assert(e->ii.value == Array<String>::make("",
                               "abcdefghijklmnopqurstuvwxyz0123456789", 
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                               "!\"#$%\'()*+`-,/:;<=>?@[\\]^_{|}~"));

        assert(!e->jj.null);
        assert(e->jj.value == Array<Datetime>::make(dt_interval, dt_interval));
        assert(e->kk.null);
        assert(e->ll.null);
        assert(e->mm.null);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}

