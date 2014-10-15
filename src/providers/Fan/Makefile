TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SHARED_LIBRARY = cmplfan

SOURCES = Fan_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -n root/cimv2 -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
