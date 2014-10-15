TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_meta_class

SOURCES =  \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    Foo.cpp \
    Everything.cpp \
    repository.cpp \
    main.cpp

LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:
	$(BIN_DIR)/genclass -r Everything CIM_ComputerSystem Foo

val:
	valgrind --tool=memcheck test_meta_class

val2:
	valgrind --tool=memcheck --leak-check=full test_meta_class
