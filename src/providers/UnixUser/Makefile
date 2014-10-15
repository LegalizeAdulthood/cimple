TOP = ../../..
include $(TOP)/mak/config.mak

ifdef PEGASUS_HOME
include $(TOP)/mak/pegasus.mak
endif

SH_LIBRARY = cmplunixusrprov

INCLUDES += -I../repository

SOURCES = UnixUser_Provider.cpp module.cpp 

LIBRARIES = -lcimple -lcmplrep

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN)/dlopen $(TARGET)

genclass:
