TOP = ../../..
include $(TOP)/mak/config.mak

ifdef PEGASUS_HOME
include $(TOP)/mak/pegasus.mak
endif

INCLUDES += -I../repository

SH_LIBRARY = cmpllinuxsysprov

SOURCES = \
    LinuxComputerSystem_Provider.cpp \
    module.cpp

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

LIBRARIES = -lcimple -lcmplrep

include $(TOP)/mak/rules.mak

reg:
	$(BIN)/regmod -c $(TARGET)

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
