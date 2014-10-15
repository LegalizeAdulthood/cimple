TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplfan

SOURCES = \
    repository.cpp \
    Fan.cpp \
    Fan_Provider.cpp \
    module.cpp

LIBRARIES = cimple

LIBRARIES += cimplepegadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

genclass:
	genclass -r Fan

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
