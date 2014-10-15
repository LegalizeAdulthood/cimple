TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SHARED_LIBRARY = cmplcsdd

SOURCES = ComputerSystemDiskDrive_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS) 

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

genprov:
	genprov -I ../repository -f Example

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
