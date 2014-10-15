TOP = ../..
include $(TOP)/mak/config.mak

DIRS = \
    All \
    Arrays \
    bug31 \
    CIM_ConcreteJob \
    CIM_DiskDrive \
    ComputerSystemDiskDrive \
    Cross \
    DerivedAssoc \
    DerivedIndication \
    Example \
    Fan \
    Hello \
    Lamp \
    LinuxComputerSystem \
    Methods \
    Methods/foo \
    Methods/foo2 \
    Methods/foo3 \
    Methods/foo4 \
    Methods/foo5 \
    MyIndication \
    OperationException \
    OperationException/testclient \
    Person \
    RefArray \
    Super \
    Thing \
    Upcall \
    XYZ_Lamp \
    All/TestAll \
    Fan/set_speed \
    bug31/meth \
    RefArray/SendRefArray \
    CIM_ConcreteJob/meth \
    Delegate \
    Employee \
    Employee/ci \
    Time \
    Time/InvokeTime \
    Widget

### Not included in normal testing because this is a sfcb only test provider
### right now.
### Widget/modify

## The providers that use Embedded Instance support are only enabled
## if this support is enabled.

ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
    DIRS += Embedded Embedded/TestEmbedded All All/TestAll
endif

include $(TOP)/mak/dir.mak
include ../pegasus/check-pegasus.mak
include ../cmpi/check-cmpi.mak
