#include <cimple/cimple.h>
#include "TheClass.h"

using namespace cimple;

void example()
{
    TheClass* inst = TheClass::create();
    inst->u.value = "hello";
    inst->v.value = 99;
    inst->w.value = true;
    inst->x.value = 1.5;
    inst->y.value.append(1);
    inst->y.value.append(2);
    inst->y.value.append(3);
    uint32 v = inst->v.value;
    destroy(inst);
}
