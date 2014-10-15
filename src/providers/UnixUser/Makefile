TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplunixusrprov

INCLUDES += -I../repository

SOURCES = UnixUser_Provider.cpp module.cpp 

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:

reg:
	regmod -c $(TARGET)
