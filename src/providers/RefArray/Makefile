TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SHARED_LIBRARY = cmplrefarrary

SOURCES = RefArray_Provider.cpp module.cpp RefArray.cpp RefArrayParam.cpp repository.cpp

LIBRARIES = cimple

LIBRARIES += cimplepegadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
	genclass -r RefArray
