#include "Class3_Hnd.h"
#include "Class1_Hnd.h"
#include "Class2_Hnd.h"
#include "Assoc1_Hnd.h"
#include "Assoc2_Hnd.h"
#include "Successor_Hnd.h"
#include "President_Hnd.h"
#include "Whole_Hnd.h"
#include "SubClass_Hnd.h"

using namespace cimple;

void test1()
{
    assert(sizeof(Class3_Hnd) == sizeof(void*));
    try
    {
        Class3_Hnd class3;
        assert(class3.StringScalar_null() == true);
        class3.StringScalar_value("Hello World");
        assert(!class3.StringScalar_null());
        assert(class3.StringScalar_value() == "Hello World");
        class3.StringScalar_clear();
        assert(class3.StringScalar_null());

        class3.Uint32Scalar_value(99);

        assert(class3.Uint32Scalar_value() == 99);

        // class3.print();

        // class3.StringScalar_value("Hello World");
    }
    catch (Exception& e)
    {
        fprintf(stderr, "error: %s\n", e.message().c_str());
        exit(1);
    }
}

void test2()
{
    Assoc2_Hnd assoc2;

    Class2_Ref left;
    left.Key_value(100);

    Class2_Ref right;
    right.Key_value(200);

    assoc2.Left_value(left);
    assoc2.Right_value(right);

    // assoc2.print();

    Assoc1_Hnd assoc1(assoc2);
    // assoc1.print();

    Assoc2_Hnd tmp(assoc1);
    // tmp.print();
}

void test3()
{
    Assoc1_Hnd assoc1;

    Class2_Ref left;
    left.Key_value(100);

    Class2_Ref right;
    right.Key_value(200);

    assoc1.Left_value(left);
    assoc1.Right_value(right);

    // assoc1.print();

    bool caught = false;

    try
    {
        Assoc2_Hnd assoc2(assoc1);
    }
    catch (Exception& e)
    {
        // printf("%s\n", e.message().c_str());
        caught = true;
    }

    assert(caught);
}

void test4()
{
    President_Hnd pres1;
    pres1.Number_value(1);
    pres1.First_value("George");
    pres1.Last_value("Washington");

    President_Hnd pres2;
    pres2.Number_value(2);
    pres2.First_value("John");
    pres2.Last_value("Adams");

    President_Ref prev(pres1.reference());
    President_Ref next(pres2.reference());
}

void test5()
{
    President_Ref prev;
    prev.Number_value(100);

    President_Ref next;
    next.Number_value(200);

    Successor_Hnd succ;
    succ.Prev_value(prev);
    succ.Next_value(next);
}

void test6()
{
    President_Hnd pres1;
    pres1.Number_value(1);
    pres1.First_value("George");
    pres1.Last_value("Washington");

    President_Hnd pres2 = pres1;
    pres1.Number_value(2);
    pres1.First_value("John");
    pres1.Last_value("Adams");

    //pres1.print();
    //pres2.print();
}

void test7()
{
    SuperClass_Hnd super1;
    SubClass_Hnd sub1;
    SuperClass_Hnd super2(sub1);

    assert(SuperClass_Hnd::is_a(sub1));
    assert(!SubClass_Hnd::is_a(super1));
    assert(SubClass_Hnd::is_a(super2));
}

int main(int argc, char** argv)
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
