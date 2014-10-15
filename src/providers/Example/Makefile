TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SHARED_LIBRARY = cmplexample

SOURCES = Example_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS) 

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)


tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
genprov:
