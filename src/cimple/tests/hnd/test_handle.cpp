#include <cimple/cimple.h>
#include "X.h"
#include "Y.h"
#include "A.h"
#include "E.h"
#include "CIM_ComputerSystem.h"

using namespace cimple;

int main()
{
    CIM_ComputerSystem_Ref ccs;

    ccs.print();

    ccs.Name("CS1");
    ccs.CreationClassName("CIM_LinuxComputerSystem");

    ccs.print();

    Y_Ref Left;
    Left.Key(100);

    Y_Ref Right;
    Right.Key(200);

    A_Ref a;
    a.Left(Left);
    a.Right(Right);
    a.print();

    E_Hnd e;
    e.e(Left);
    e.print();

    return 0;
}
