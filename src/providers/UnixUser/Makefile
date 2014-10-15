TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplunixusrprov

INCLUDES += -I../repository

SOURCES = UnixUser_Provider.cpp module.cpp 

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)
