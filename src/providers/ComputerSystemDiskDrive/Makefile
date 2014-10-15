TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SH_LIBRARY = cmplcsdd

SOURCES = ComputerSystemDiskDrive_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS) 

reg:
	regmod -c $(TARGET)

genprov:
	genprov -I ../repository -f Example

genclass:
	genclass Example

tests:
	@ $(BIN_DIR)/dlopen $(TARGET)
