#include <cimple/config.h>
#include <pegasus/utils/pegasus.h>
#include <pegasus/utils/Containers.h>
#include <pegasus/utils/print.h>
#include <pegasus/utils/Str.h>
#include "Class1.h"
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Assoc1.h"
#include "repository.h"

using namespace Pegasus;
using namespace cimple;

static bool verbose;

const char* ns = "root/cimv2";

void roundtrip(CIMInstance& ci, const Meta_Class* mc)
{
    Instance* inst1 = 0;
    {
        InstanceContainer cont(mc->meta_repository, ns, ci);
        cont.convert(mc, false, inst1);
        assert(inst1);
    }

    CIMInstance ci2(mc->name);
    {
        InstanceContainer cont(mc->meta_repository, ns, ci2);

        if (cont.convert(inst1, 0) != 0)
        {
            assert(0);
        }
    }

    Instance* inst2 = 0;
    {
        InstanceContainer cont(mc->meta_repository, ns, ci2);
        cont.convert(mc, 0, inst2);
    }

    if (verbose)
    {
        printf("Roundtrip instances\n");
        print(inst1);
        print(inst2);
    }


    if (!identical(inst1, inst2))
    {
        print(inst1);
        print(inst2);
        assert(0);
    }

    unref(inst1);
    unref(inst2);
}

void test1()
{
    CIMDateTime now = CIMDateTime::getCurrentDateTime();
    Pegasus::Array<Pegasus::String> p5;
    p5.append("Red");
    p5.append("Green");
    p5.append("Blue");

    CIMInstance ci("Class1");
    ci.addProperty(CIMProperty("p1", Uint32(99)));
    ci.addProperty(CIMProperty("p2", Pegasus::String("Hello")));
    ci.addProperty(CIMProperty("p3", Boolean(false)));
    ci.addProperty(CIMProperty("p4", now));
    ci.addProperty(CIMProperty("p5", p5));
    ci.addProperty(CIMProperty("p6", CIMValue(CIMTYPE_STRING, false)));
    ci.addProperty(CIMProperty("junk", Pegasus::String("No such property")));
    if (verbose)
    {
        printf("Print Pegasus instance\n");
        cimple::print(ci);
    }
    roundtrip(ci, &Class1::static_meta_class);

    InstanceContainer cont(Class1::static_meta_class.meta_repository, ns, ci);
    Instance* tmp = 0;
    cont.convert(&Class1::static_meta_class, 0, tmp);
    assert(tmp);

    Class1* inst = cast<Class1*>(tmp);
    assert(inst != 0);

    // p1:
    assert(inst->p1.value == 99);
    assert(inst->p1.null == false);

    // p2:
    assert(inst->p2.value == "Hello");
    assert(inst->p2.null == false);

    // p3:
    assert(inst->p3.value == false);
    assert(inst->p3.null == false);

    // p5:
    {
        cimple::Array<cimple::String> a;
        a.append("Red");
        a.append("Green");
        a.append("Blue");
        assert(inst->p5.value.size() == 3);
        assert(inst->p5.value == a);
        assert(inst->p5.null == false);
    }

    unref(tmp);
}

void test2()
{
    CIMObjectPath op("Class1.p1=99,p2=\"Hello\",p3=true");

    ObjectPathContainer cont(Class1::static_meta_class.meta_repository, ns, op);
    Instance* tmp = 0;
    cont.convert(&Class1::static_meta_class, CIMPLE_FLAG_KEY, tmp);
    assert(tmp);

    Class1* inst = cast<Class1*>(tmp);
    assert(inst != 0);

    // p1:
    assert(inst->p1.value == 99);
    assert(inst->p1.null == false);

    // p2:
    assert(inst->p2.value == "Hello");
    assert(inst->p2.null == false);

    // p3:
    assert(inst->p3.value == true);
    assert(inst->p3.null == false);

    unref(tmp);
}

void test3()
{
    CIMObjectPath left("Class1.p1=100,p2=\"left\",p3=true");
    CIMObjectPath right("Class1.p1=200,p2=\"right\",p3=false");

    CIMInstance ci("Assoc1");
    ci.addProperty(CIMProperty("left", left));
    ci.addProperty(CIMProperty("right", right));
    if (verbose)
    {
        printf("Print Pegasus instance\n");
        cimple::print(ci);
    }
    roundtrip(ci, &Assoc1::static_meta_class);

    InstanceContainer cont(Assoc1::static_meta_class.meta_repository, ns, ci);
    Instance* tmp = 0;
    cont.convert(&Assoc1::static_meta_class, 0, tmp);
    assert(tmp);

    Assoc1* inst = cast<Assoc1*>(tmp);
    assert(inst);

    assert(inst->left);
    assert(inst->left->p1.value == 100);
    assert(inst->left->p1.null == false);
    assert(inst->left->p2.value == "left");
    assert(inst->left->p2.null == false);
    assert(inst->left->p3.value == true);
    assert(inst->left->p3.null == false);

    assert(inst->right);
    assert(inst->right->p1.value == 200);
    assert(inst->right->p1.null == false);
    assert(inst->right->p2.value == "right");
    assert(inst->right->p2.null == false);
    assert(inst->right->p3.value == false);
    assert(inst->right->p3.null == false);

    unref(tmp);
}

void test4()
{
    CIMObjectPath left("Class2.key=100");
    CIMObjectPath right("Class2.key=200");

    CIMInstance ci("Assoc2");
    ci.addProperty(CIMProperty("left", left));
    ci.addProperty(CIMProperty("right", right));
    if (verbose)
    {
        printf("Print Pegasus instance\n");
        cimple::print(ci);
    }
    roundtrip(ci, &Assoc2::static_meta_class);

    InstanceContainer cont(Assoc2::static_meta_class.meta_repository, ns, ci);
    Instance* tmp = 0;
    cont.convert(&Assoc2::static_meta_class, 0, tmp);
    assert(tmp);

    Assoc2* inst = cast<Assoc2*>(tmp);
    assert(inst);

    assert(inst->left);
    assert(inst->left->key.value == 100);
    assert(inst->left->key.null == false);

    assert(inst->right);
    assert(inst->right->key.value == 200);
    assert(inst->right->key.null == false);

    unref(tmp);
}

void test5()
{
    CIMObjectPath op("Class2.key=12345");

    ObjectPathContainer cont(Class2::static_meta_class.meta_repository, ns, op);
    Instance* tmp = 0;
    cont.convert(&Class2::static_meta_class, CIMPLE_FLAG_KEY, tmp);
    assert(tmp);

    Class2* inst = cast<Class2*>(tmp);
    assert(inst);

    assert(inst->key.value == 12345);

    unref(tmp);
}

void test6()
{
    CIMInstance class2("Class2");
    class2.addProperty(CIMProperty("key", Uint32(100)));
    roundtrip(class2, &Class2::static_meta_class);

    CIMInstance class3("Class3");
    class3.addProperty(CIMProperty("key", Uint32(200)));
    class3.addProperty(CIMProperty("embedded", CIMValue(CIMObject(class2))));
    if (verbose)
    {
        printf("test6 Print Pegasus instance\n");
        cimple::print(class2);
        cimple::print(class3);
    }
    roundtrip(class3, &Class3::static_meta_class);

    InstanceContainer cont(
        Class1::static_meta_class.meta_repository, ns, class3);
    Instance* tmp;
    tmp = 0;
    cont.convert(&Class3::static_meta_class, 0, tmp);
    assert(tmp);

    Class3* inst = cast<Class3*>(tmp);
    assert(inst != 0);

    // key:
    assert(inst->key.value == 200);
    assert(inst->key.null == false);

    // embedded:
    {
        assert(inst->embedded);

        Class2* inst2 = cast<Class2*>(inst->embedded);
        assert(inst2);
        assert(inst2->key.value == 100);
        assert(inst2->key.null == false);
    }

    unref(tmp);
}


void test7()
{
    CIMInstance class2("Class2");
    class2.addProperty(CIMProperty("key", Uint32(100)));
    roundtrip(class2, &Class2::static_meta_class);

    CIMInstance class3("Class4");
    class3.addProperty(CIMProperty("key", Uint32(200)));
    class3.addProperty(CIMProperty("embedded", CIMValue(class2)));

    if (verbose)
    {
        printf("Print Pegasus instance\n");
        cimple::print(class2);
        cimple::print(class3);
    }
    roundtrip(class3, &Class3::static_meta_class);

    InstanceContainer cont(
        Class1::static_meta_class.meta_repository, ns, class3);
    Instance* tmp = 0;
    cont.convert(&Class4::static_meta_class, 0, tmp);

    assert(tmp);

    Class4* inst = cast<Class4*>(tmp);
    assert(inst != 0);

    // key:
    assert(inst->key.value == 200);
    assert(inst->key.null == false);

#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
    // embedded:
    {
        assert(inst->embedded);

        Class2* inst2 = cast<Class2*>(inst->embedded);
        assert(inst2);
        assert(inst2->key.value == 100);
        assert(inst2->key.null == false);
    }
#else
    assert(!inst->embedded);
#endif

    unref(tmp);
}



#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
void test8()
{
    Pegasus::Array<Pegasus::CIMInstance> embedded;
    {
        CIMInstance class2("Class2");
        class2.addProperty(CIMProperty("key", Uint32(100)));
        embedded.append(class2);
        roundtrip(class2, &Class2::static_meta_class);
    }
    {
        CIMInstance class2("Class2");
        class2.addProperty(CIMProperty("key", Uint32(200)));
        embedded.append(class2);
        roundtrip(class2, &Class2::static_meta_class);
    }

    CIMValue v(embedded);

    CIMInstance class3("Class5");
    class3.addProperty(CIMProperty("key", Uint32(999)));
    class3.addProperty(CIMProperty("embedded", CIMValue(embedded)));
    if (verbose)
    {
        printf("test8. Print Pegasus instance\n");
        cimple::print(class3);
    }
    roundtrip(class3, &Class5::static_meta_class);

    InstanceContainer cont(
        Class1::static_meta_class.meta_repository, ns, class3);
    Instance* tmp = 0;
    cont.convert(&Class5::static_meta_class, 0, tmp);
    assert(tmp);

    Class5* inst = cast<Class5*>(tmp);
    assert(inst != 0);

    // key:
    assert(inst->key.value == 999);
    assert(inst->key.null == false);

    // embedded:
    {
        assert(inst->embedded.value.size() == 2);

        for (size_t i = 0; i < inst->embedded.value.size(); i++)
        {
            Class2* inst2 = cast<Class2*>(inst->embedded.value[i]);
            assert(inst2);

            if (i == 0)
                assert(inst2->key.value == 100);
            else
                assert(inst2->key.value == 200);

            assert(inst2->key.null == false);
        }
    }

    unref(tmp);
}

#endif /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */

void test9()
{
    CIMObjectPath left("Class2.p1=100,p2=\"left\",p3=true");
    CIMObjectPath right("Class2.p1=200,p2=\"right\",p3=false");

    CIMInstance ci("Assoc1");
    ci.addProperty(CIMProperty("left", left));
    ci.addProperty(CIMProperty("right", right));
    if (verbose)
    {
        printf("Print Pegasus instance\n");
        cimple::print(ci);
    }
    roundtrip(ci, &Assoc1::static_meta_class);

    InstanceContainer cont(Assoc1::static_meta_class.meta_repository, ns, ci);
    Instance* tmp = 0;
    cont.convert(&Assoc1::static_meta_class, 0, tmp);
    assert(tmp);

    unref(tmp);
}

int main(int argc, char** argv)
{
    verbose = getenv("CIMPLE_TEST_VERBOSE") ? true : false;
    try
    {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
        test7();        // test single instance of embedded instances
        test8();        // test array of embedded instances
#endif
        test9();
    }
    catch (Pegasus::Exception& e)
    {
        printf("EXCEPTION [%s]\n", *Str(e));
        assert("unexpected exception" == 0);
    }
    catch (...)
    {
        assert("unexpected exception" == 0);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}
