#include <cimple/Provider2.h>
#include "ConcreteAssoc_Handle.h"
#include "CIM_ComputerSystem_Handle.h"

using namespace cimple;

void test1()
{
    try
    {
        ConcreteAssoc_Handle ca1;
        Assoc_Handle a = ca1;
        ConcreteAssoc_Handle ca2(a);
        ConcreteAssoc_Handle ca3(ca1);
        a.print();
        ca1.print();
        ca2.print();
        ca3.print();
    }
    catch (Exception& e)
    {
        fprintf(stderr, "error: %s\n", e.message().c_str());
        exit(1);
    }

    {
        int n = 0;
        int m = 0;
        try
        {
            Assoc_Handle a2;
            n++;
            ConcreteAssoc_Handle ca3(a2);
            n++;
        }
        catch (Exception& e)
        {
            assert(n == 1);
            m++;
        }

        assert(m == 1);
    }
}

typedef Instance_Provider2<CIM_ComputerSystem_Handle> MyProvider;

int main(int argc, char** argv)
{
    test1();
    printf("+++++ passed all tests (%s)\n", argv[0]);

    MyProvider p;
    p.proc(0, 0, 0, 0 , 0, 0, 0, 0, 0, 0);

    return 0;
}
