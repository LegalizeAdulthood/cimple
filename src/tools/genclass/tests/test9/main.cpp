#include <cimple/cimple.h>
#include <cassert>
#include "Thing.h"

using namespace cimple;

int main(int argc, char** argv)
{
    //print(&Thing::static_meta_class);
    //Meta_Class* mc = clone(&Thing::static_meta_class);
    Thing* thing = Thing::create(true);
    print(thing);

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test9/main.cpp,v 1.4 2007/03/07 20:25:30 mbrasher-public Exp $");
