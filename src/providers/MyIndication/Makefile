TOP = ../../..
include $(TOP)/mak/config.mak

ifdef PEGASUS_HOME
include $(TOP)/mak/pegasus.mak
endif

SH_LIBRARY = cmplmyindic

INCLUDES += -I../repository

SOURCES = \
    MyIndication_Provider.cpp \
    module.cpp

LIBRARIES = -lcimple -lcmplrep

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	cimmofl ../repository/MyEmbeddedClass.mof 2> /dev/null
	regmod -c $(TARGET)

genclass:

tests:
	@ $(BIN)/dlopen $(TARGET)
