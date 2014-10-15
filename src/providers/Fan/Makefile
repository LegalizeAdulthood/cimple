TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SH_LIBRARY = cmplfan

SOURCES = Fan_Provider.cpp module.cpp

LIBRARIES = -lcimple -lcmplrep

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -n root/cimv2 -c $(TARGET)

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
