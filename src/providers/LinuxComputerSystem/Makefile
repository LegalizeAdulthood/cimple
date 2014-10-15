TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SH_LIBRARY = cmpllinuxsysprov

SOURCES = \
    LinuxComputerSystem_Provider.cpp \
    module.cpp

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

reg:
	$(BIN_DIR)/regmod -c $(TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(TARGET)

genclass:
