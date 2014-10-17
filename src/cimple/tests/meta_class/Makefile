TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_meta_class

GENCLASS_SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    Everything.cpp \
    Foo.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Everything CIM_ComputerSystem Foo

val:
	valgrind --tool=memcheck test_meta_class

val2:
	valgrind --tool=memcheck --leak-check=full test_meta_class
