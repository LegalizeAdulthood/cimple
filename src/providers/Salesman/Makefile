TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplsalesman

INCLUDES += -I../repository

SOURCES = Salesman_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -c $(TARGET)

genclass:

tests:
