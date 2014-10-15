TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplmethods

INCLUDES += -I../repository

SOURCES = Methods_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(TARGET)

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
