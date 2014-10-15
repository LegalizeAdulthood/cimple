TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplunixusrprov

INCLUDES += -I../repository

SOURCES = UnixUser_Provider.cpp module.cpp 

LIBRARIES = cimple cmplrep

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
