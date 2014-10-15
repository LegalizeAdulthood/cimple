TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SH_LIBRARY = cmplexample

SOURCES = Example_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS) 

reg:
	regmod -c $(TARGET)


tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
genprov:
