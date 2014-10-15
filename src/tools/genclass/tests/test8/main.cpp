#include <cimple/cimple.h>
#include <cassert>
#include "CIM_Card.h"
#include "CIM_ManagedElement.h"
#include "CIM_ManagedSystemElement.h"
#include "CIM_PhysicalConnector.h"
#include "CIM_PhysicalElement.h"
#include "CIM_PhysicalPackage.h"

using namespace cimple;

void test(const Meta_Class* mc)
{
    Meta_Class* p = clone(mc);
}

int main(int argc, char** argv)
{
    print(&CIM_Card::static_meta_class);
    Meta_Class* mc = clone(&CIM_Card::static_meta_class);
    print(mc);
#if 0
    print(&CIM_ManagedElement::static_meta_class);
    print(&CIM_ManagedSystemElement::static_meta_class);
    print(&CIM_PhysicalConnector::static_meta_class);
    print(&CIM_PhysicalElement::static_meta_class);
    print(&CIM_PhysicalPackage::static_meta_class);
#endif

    return 0;
}

