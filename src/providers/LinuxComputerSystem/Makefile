TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SH_LIBRARY = cmpllinuxsysprov

SOURCES = \
    LinuxComputerSystem_Provider.cpp \
    module.cpp

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

LIBRARIES = cimple cmplrep

include $(TOP)/mak/rules.mak

reg:
	$(BIN)/regmod -c $(TARGET)

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
