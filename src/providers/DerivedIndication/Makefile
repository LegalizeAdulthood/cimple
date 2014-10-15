TOP = ../../..
include $(TOP)/mak/config.mak

ifdef PEGASUS_HOME
include $(TOP)/mak/pegasus.mak
endif

SH_LIBRARY = cmplderivedindic

INCLUDES += -I../repository

SOURCES = \
    DerivedIndication_Provider.cpp \
    module.cpp

LIBRARIES = -lcimple -lcmplrep

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -c $(TARGET)

genclass:

tests:
	@ $(BIN)/dlopen $(TARGET)
